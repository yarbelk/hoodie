#ifndef HOODIE_HOODIEMESH_H
#define HOODIE_HOODIEMESH_H

#include "hoodie_node.h"

#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/templates/rb_map.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/templates/local_vector.hpp>
#include <godot_cpp/classes/material.hpp>

namespace godot
{

class HoodieMesh : public ArrayMesh {
    GDCLASS(HoodieMesh, ArrayMesh)

    friend class HoodieGraphPlugin;
    friend class HoodieControl;
    friend class HoodieEditorPlugin;

public:
    typedef HoodieNode::id_t id_t;
    typedef HoodieNode::vec_size_t vec_size_t;

    struct Connection {
        id_t l_node;
        vec_size_t l_port;
        id_t r_node;
        vec_size_t r_port;

        Connection()
            : l_node(0),
              l_port(0),
              r_node(0),
              r_port(0) {}

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

    // Store materials for undo redo purposes.
    RBMap<id_t, Ref<Material>> materials;

    bool verbose_mode = false;

    mutable SafeFlag dirty;
    void _queue_update();

    void _update();
    // _update utils.
    void _remove_orphan_surfaces();
    void _remove_surface_dumb(id_t p_id);

    bool _update_node(id_t p_id, Ref<HoodieNode> p_node);

    TypedArray<HoodieNode> _get_hoodie_nodes();
    void _set_hoodie_nodes(TypedArray<HoodieNode> p_nodes);
    void add_node(const Ref<HoodieNode> &p_node, const Vector2 &p_position, id_t p_id);
    void set_node_position(id_t p_id, const Vector2 &p_position);

    void remove_node(id_t p_id);

public:
    Vector2 get_node_position(id_t p_id) const;
    Ref<HoodieNode> get_node(id_t p_id) const;

    Vector<id_t> get_nodes_id_list() const;
    id_t get_valid_node_id() const;

    const Vector<NodePortPair> get_left_ports(id_t p_r_node, vec_size_t p_r_port) const;

protected:
    static void _bind_methods();

	bool _set(const StringName &p_name, const Variant &p_value);
	bool _get(const StringName &p_name, Variant &r_ret) const;
	void _get_property_list(List<PropertyInfo> *p_list) const;

public:
    bool is_nodes_connected_relatively(const Graph *p_graph, id_t p_node, id_t p_target) const;
	bool can_connect_nodes(id_t p_from_node, vec_size_t p_from_port, id_t p_to_node, vec_size_t p_to_port) const;
    Error connect_nodes(id_t p_from_node, vec_size_t p_from_port, id_t p_to_node, vec_size_t p_to_port);
    void disconnect_nodes(id_t p_from_node, vec_size_t p_from_port, id_t p_to_node, vec_size_t p_to_port);
    void connect_nodes_forced(id_t p_from_node, vec_size_t p_from_port, id_t p_to_node, vec_size_t p_to_port);
    bool is_port_types_compatible(int p_a, int p_b) const;

    // void rebuild();
    void get_node_connections(List<Connection> *r_connections) const;

    bool get_verbose_mode() const;
    void set_verbose_mode(bool p_mode);

    void set_graph_offset(const Vector2 &p_offset);
    Vector2 get_graph_offset() const;

    HoodieMesh();
};
    
} // namespace godot


#endif // HOODIE_HOODIEMESH_H