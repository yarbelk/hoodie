#ifndef HOODIE_HOODIEMESH_H
#define HOODIE_HOODIEMESH_H

#include "hoodie_id_manager.h"
#include "hoodie_node.h"

#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/templates/rb_map.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/templates/local_vector.hpp>

namespace godot
{

class HoodieMesh : public ArrayMesh {
    GDCLASS(HoodieMesh, ArrayMesh)

    friend class HoodieEditorPlugin;

    typedef HoodieNode::id_t id_t;
    typedef uint32_t vec_size_t;

public:
    struct Connection {
        id_t l_node;
        vec_size_t l_port;
        id_t r_node;
        vec_size_t r_port;

        Connection(id_t p_l_node, vec_size_t p_l_port, id_t p_r_node, vec_size_t p_r_port)
            : l_node(p_l_node),
              l_port(p_l_port),
              r_node(p_r_node),
              r_port(p_r_port) {}
    };

    struct NodePortPair {
        id_t node;
        vec_size_t port;

        NodePortPair() {}
        NodePortPair(id_t p_node, vec_size_t p_port) : node(p_node), port(p_port) {}
    };

private:
    struct Node {
        Ref<HoodieNode> node;
        Vector2 position;
        LocalVector<id_t> prev_connected_nodes;
        LocalVector<id_t> next_connected_nodes;
    };

    struct Graph {
        RBMap<id_t, Node> nodes;
        List<Connection> connections;
    };

    Graph graph;

    TypedArray<Dictionary> _get_node_connections() const;

    Vector2 graph_offset;

    // HoodieIdManager<id_t> id_manager;
    // HashMap<id_t, Ref<HoodieNode>> hoodie_nodes;
    // Vector<Connection> connections;

    mutable SafeFlag dirty;
    void _queue_update();

    void _update();
    // _update utils
    void _remove_orphan_surfaces();
    void _remove_surface_dumb(id_t p_id);

    bool _update_node(id_t p_id, Ref<HoodieNode> p_node);

    TypedArray<HoodieNode> _get_hoodie_nodes();
    void _set_hoodie_nodes(TypedArray<HoodieNode> p_nodes);
    id_t add_node(Ref<HoodieNode> p_node);
    void remove_node(id_t p_id);
    Ref<HoodieNode> get_node(id_t p_id);

    Vector<id_t> get_nodes_id_list() const;
    id_t get_valid_node_id() const;

    void add_connection(id_t p_l_node, vec_size_t p_l_port, id_t p_r_node, vec_size_t p_r_port);
    void remove_connection(id_t p_l_node, vec_size_t p_l_port, id_t p_r_node, vec_size_t p_r_port);
    Vector<Connection> get_connections();

    const Vector<NodePortPair> get_left_ports(id_t p_r_node, vec_size_t p_r_port) const;

protected:
    static void _bind_methods();
	// bool _set(const StringName &p_name, const Variant &p_value);
	// bool _get(const StringName &p_name, Variant &r_ret) const;
	// void _get_property_list(List<PropertyInfo> *p_list) const;

public:
    HoodieMesh();
};
    
} // namespace godot


#endif // HOODIE_HOODIEMESH_H