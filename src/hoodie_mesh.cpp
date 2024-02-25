#include "hoodie_mesh.h"

using namespace godot;

// typedef uint32_t id_t;
// typedef uint32_t vec_size_t;

void HoodieMesh::trigger_update() {

}

void HoodieMesh::update() {

}

void HoodieMesh::_remove_orphan_surfaces() {

}

void HoodieMesh::_remove_surface_dumb(id_t p_id) {

}

TypedArray<HoodieNode> HoodieMesh::_get_hoodie_nodes() {
    TypedArray<HoodieNode> result;
    for (const KeyValue<id_t, Ref<HoodieNode>>& E: hoodie_nodes) {
        result.push_back(E.value);
    }
    return result;
}

void HoodieMesh::_set_hoodie_nodes(TypedArray<HoodieNode> p_nodes) {
    hoodie_nodes.clear();
    for (int i = 0; i < p_nodes.size(); i++) {
        Ref<HoodieNode> node = p_nodes[i];
        hoodie_nodes[node->get_id()] = node;
    }
}

HoodieMesh::id_t HoodieMesh::add_node(Ref<HoodieNode> p_node) {
    id_t id = id_manager.generateID();
    p_node.ptr()->set_id(id);
    hoodie_nodes[id] = p_node;
    return id;
}

void HoodieMesh::remove_node(id_t p_id) {}

Ref<HoodieNode> HoodieMesh::get_node(id_t p_id) {
    return Ref<HoodieNode>();
}

Vector<HoodieMesh::id_t> HoodieMesh::get_nodes_id_list() {
    return Vector<HoodieMesh::id_t>();
}

void HoodieMesh::add_connection(id_t p_l_node, vec_size_t p_l_socket, id_t p_r_node, vec_size_t p_r_socket) {}
void HoodieMesh::remove_connection(id_t p_l_node, vec_size_t p_l_socket, id_t p_r_node, vec_size_t p_r_socket) {}

Vector<HoodieMesh::Connection> HoodieMesh::get_connections() {
    return Vector<HoodieMesh::Connection>();
}

HoodieMesh::NodeSocketPair HoodieMesh::get_left_socket(HoodieMesh::NodeSocketPair p_right_socket) {
    return HoodieMesh::NodeSocketPair(0, 0);
}

void HoodieMesh::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_get_hoodie_nodes"), &HoodieMesh::_get_hoodie_nodes);
    ClassDB::bind_method(D_METHOD("_set_hoodie_nodes", "nodes"), &HoodieMesh::_set_hoodie_nodes);

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
