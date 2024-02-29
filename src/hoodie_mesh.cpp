#include "hoodie_mesh.h"

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/templates/vector.hpp>

using namespace godot;

TypedArray<Dictionary> HoodieMesh::_get_node_connections() const {
    const Graph *g = &graph;

    TypedArray<Dictionary> ret;
    for (const Connection &E : g->connections) {
        Dictionary d;
        d["l_node"] = E.l_node;
        d["l_port"] = E.l_port;
        d["r_node"] = E.r_node;
        d["r_port"] = E.r_port;
        ret.push_back(d);
    }

    return ret;
}

void HoodieMesh::_queue_update() {
    if (dirty.is_set()) {
        return;
    }

    dirty.set();
    call_deferred(StringName("_update"));
}

void HoodieMesh::_update() {
    if (!dirty.is_set()) {
        return;
    }

    dirty.clear();

    _remove_orphan_surfaces();

    // TODO: the issue is taking track of the previous materials, that now are gone...

    for (const KeyValue<id_t, Node> &E : graph.nodes) {
        E.value.node->set_status(HoodieNode::ProcessStatus::PENDING);
    }

    // Iterate on all output nodes
    for (const KeyValue<id_t, Node> &E : graph.nodes) {
        if (E.value.node->get_output_port_count() != 0) {
            continue;
        }

        bool changed = _update_node(E.key, E.value.node);

        if (!changed) {
            continue;
        }

        String name = String::num_int64(E.key);
        id_t surface_id = surface_find_by_name(name);
        if (surface_id != -1) {
            _remove_surface_dumb(surface_id);
        }

        Variant surface = E.value.node->get_output(0);

        if (surface.get_type() != Variant::ARRAY) {
            UtilityFunctions::print("Output node is not returing a Variant::ARRAY");
        } else {
            Array arr = surface;

            if (arr.size() != ArrayMesh::ARRAY_MAX) {
                UtilityFunctions::print("Output node is not returning a correctly sized array!\n");
            } else if (arr[ArrayMesh::ARRAY_VERTEX].get_type() != Variant::PACKED_VECTOR3_ARRAY) {
                UtilityFunctions::print("Output node array ARRAY_VERTEX is not of POOL_VECTOR3_ARRAY type!\n");
            } else if (((PackedVector3Array)arr[ArrayMesh::ARRAY_VERTEX]).size() == 0) {
                UtilityFunctions::print("No vertices in output node ARRAY_VERTEX array!");
            } else if (arr[ArrayMesh::ARRAY_INDEX].get_type() != Variant::PACKED_INT32_ARRAY) {
                UtilityFunctions::print("No indices in final node ARRAY_INDEX array!");
            } else {
                // TODO: apply material stuff
                // Ref<Material> material;
                int32_t new_surface_id = get_surface_count();
                add_surface_from_arrays(Mesh::PRIMITIVE_TRIANGLES, arr);
                surface_set_name(new_surface_id, name);
            }
        }
    }
    UtilityFunctions::print("Update end. Surface count: ", get_surface_count());
}

// TODO: replace this with surface_remove in Godot 4.3
void HoodieMesh::_remove_orphan_surfaces() {
    // Basically you want to check if there's a node (usually a Output HoodieNode) that generates that surface, giving it its name
    // (e.g. Node name: 0 (it's the id), Surface name: 0)
    // If the node 0 is not there anymore, we need to remove that surface.
    // TODO: implement surface_remove() that will be available in Godot 4.3

    // std::map<id_t, Ref<HoodieNode>>::iterator it;

    // In this array we will store the arrays with which we will reconstruct the surfaces to keep
    Array surf_arrays_to_keep;
    Array surf_names;
    // Iterate over all surfaces
    for (int64_t s = get_surface_count() - 1; s >= 0; s--) {
        String surface_name = surface_get_name(s);
        bool node_found = false;
        // Iterate over all nodes
        for (const KeyValue<id_t, Node> &E : graph.nodes) {
            String node_name = String::num_int64(E.key);
            if (node_name == surface_name) {
                // Found the node with the same name of the surface
                node_found = true;
            }
        }
        if (node_found) {
            // We want to keep this surface, so we store its arrays and name
            surf_arrays_to_keep.push_back(surface_get_arrays(s));
            surf_names.push_back(surface_name);
        }
    }
    // We stored all the surfaces to keep, time to clear...
    clear_surfaces();
    // ...and re-add them!
    for (int64_t i = 0; i < surf_arrays_to_keep.size(); i++) {
        add_surface_from_arrays(Mesh::PRIMITIVE_TRIANGLES, surf_arrays_to_keep[i]);
        surface_set_name(i, surf_names[i]);
    }
}

// TODO: replace this with surface_remove in Godot 4.3
void HoodieMesh::_remove_surface_dumb(id_t p_id) {
    // Basically rebuilds all surface except the one selected
    Array surf_arrays_to_keep;
    Array surf_names;
    for (int64_t s = get_surface_count() - 1; s >= 0; s--) {
        if (s != p_id) {
            surf_arrays_to_keep.push_back(surface_get_arrays(s));
            surf_names.push_back(surface_get_name(s));
        }
    }
    clear_surfaces();
    for (int64_t i = 0; i < surf_arrays_to_keep.size(); i++) {
        add_surface_from_arrays(Mesh::PRIMITIVE_TRIANGLES, surf_arrays_to_keep[i]);
        surface_set_name(i, surf_names[i]);
    }
}

bool HoodieMesh::_update_node(id_t p_id, Ref<HoodieNode> p_node) {
    switch (p_node->get_status())
    {
        case HoodieNode::ProcessStatus::INPROGRESS: 
            UtilityFunctions::print("Found circular dependency in procedural mesh!");
            return false;
        case HoodieNode::ProcessStatus::UNCHANGED:
            UtilityFunctions::print("Node unchanged.");
            return false;
        case HoodieNode::ProcessStatus::CHANGED:
            UtilityFunctions::print("Node already processed.");
            return true;
        case HoodieNode::ProcessStatus::PENDING:
            UtilityFunctions::print("Node status pending: proceeding updating the node (now in progress)...");
            bool updated = false;
            Array inputs;

            p_node->set_status(HoodieNode::ProcessStatus::INPROGRESS);

            for (int i = 0; i < p_node->get_input_port_count(); i++)
            {
                Vector<HoodieMesh::NodePortPair> l_ports = get_left_ports(p_id, i);

                // TODO: implement more than one l_port
                if (l_ports.size() > 1) {
                    UtilityFunctions::print("More than one l_port NOT IMPLEMENTED.");
                    continue;
                } else if (l_ports.size() == 0) {
                    inputs.push_back(Variant());
                    continue;
                }

                // Make sure l_node is valid
                RBMap<id_t, Node>::ConstIterator E = graph.nodes.find(l_ports[0].node);
                if (!E) {
                    UtilityFunctions::print("l_node not found.");
                    continue;
                }

                id_t l_id = E->key;
                Ref<HoodieNode> l_node = E->value.node;

                // Make sure it has been updated
                if (_update_node(l_id, l_node)) {
                    updated = true;
                }

                Variant l_data = l_node->get_output(l_ports[0].port);

                HoodieNode::PortType l_type = l_node->get_output_port_type(l_ports[0].port);
                HoodieNode::PortType r_type = p_node->get_input_port_type(i);

                // TODO: implement data conversion

                if (l_type != r_type) {
                    UtilityFunctions::print("l_node and r_node type don't match!");
                    l_data = Variant();
                }
            }

            if (p_node->update(updated, inputs)) {
                updated = true;
            }

            p_node->set_status(updated ? HoodieNode::ProcessStatus::CHANGED : HoodieNode::ProcessStatus::UNCHANGED);
            
            return updated;
    }
}

TypedArray<HoodieNode> HoodieMesh::_get_hoodie_nodes() {
    TypedArray<HoodieNode> result;
    for (const KeyValue<id_t, Node> &E : graph.nodes) {
        result.push_back(E.value.node);
    }
    return result;
}

void HoodieMesh::_set_hoodie_nodes(TypedArray<HoodieNode> p_nodes) {
    graph.nodes.clear();
    for (int i = 0; i < p_nodes.size(); i++) {
        Ref<HoodieNode> node = p_nodes[i];
        graph.nodes[node->get_id()].node = node;
    }
}

HoodieMesh::id_t HoodieMesh::add_node(Ref<HoodieNode> p_node) {
    id_t id = get_valid_node_id();
    ERR_FAIL_COND(graph.nodes.has(id));
    p_node->set_id(id);
    graph.nodes[id].node = p_node;
    return id;
}

void HoodieMesh::remove_node(id_t p_id) {}

Ref<HoodieNode> HoodieMesh::get_node(id_t p_id) {
    return Ref<HoodieNode>();
}

Vector<HoodieMesh::id_t> HoodieMesh::get_nodes_id_list() const {
    Vector<id_t> ret;
    for (const KeyValue<id_t, HoodieMesh::Node> &E : graph.nodes) {
        ret.push_back(E.key);
    }

    return ret;
}

HoodieMesh::id_t HoodieMesh::get_valid_node_id() const {
    return graph.nodes.size() ? MAX(1, graph.nodes.back()->key() + 1) : 1;
}

void HoodieMesh::add_connection(id_t p_l_node, vec_size_t p_l_port, id_t p_r_node, vec_size_t p_r_port) {
}

void HoodieMesh::remove_connection(id_t p_l_node, vec_size_t p_l_port, id_t p_r_node, vec_size_t p_r_port) {
}

Vector<HoodieMesh::Connection> HoodieMesh::get_connections() {
    return Vector<HoodieMesh::Connection>();
}

const Vector<HoodieMesh::NodePortPair> HoodieMesh::get_left_ports(id_t p_r_node, vec_size_t p_r_port) const {
    size_t max = graph.connections.size();
    if (max == 0) {
        return Vector<HoodieMesh::NodePortPair>();
    }

    Vector<HoodieMesh::NodePortPair> vec;

    for (size_t i = max - 1; i >= 0 && i < max; i--) {
        Connection c = graph.connections[i];
        if ((c.r_node == p_r_node) && (c.r_port == p_r_port)) {
            vec.push_back(HoodieMesh::NodePortPair(c.l_node, c.l_port));
        }
    }
    
    return vec;
}

void HoodieMesh::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_get_hoodie_nodes"), &HoodieMesh::_get_hoodie_nodes);
    ClassDB::bind_method(D_METHOD("_set_hoodie_nodes", "nodes"), &HoodieMesh::_set_hoodie_nodes);

    ClassDB::bind_method(D_METHOD("_update"), &HoodieMesh::_update);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "_data", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NO_EDITOR | PROPERTY_USAGE_INTERNAL), "_set_hoodie_nodes", "_get_hoodie_nodes");
}

/*
bool HoodieMesh::_set(const StringName &p_name, const Variant &p_value) {
    PackedStringArray components = String(p_name).split("/", true, 2);
    if (components.size() >= 2 && components[0].begins_with("hoodie_node_") && components[0].trim_prefix("hoodie_node_").is_valid_int()) {
        id_t point_index = components[0].trim_prefix("hoodie_node_").to_int();
        String property = components[1];
        if ()
    }
    return false;
}

bool HoodieMesh::_get(const StringName &p_name, Variant &r_ret) const {
    PackedStringArray components = String(p_name).split("/", true, 2);
    if (components.size() >= 2 && components[0].begins_with("hoodie_node_") && components[0].trim_prefix("hoodie_node_").is_valid_int()) {
        
    }
    return false;
}
*/

HoodieMesh::HoodieMesh() {

}
