#ifndef HOODIE_HOODIEMESH_H
#define HOODIE_HOODIEMESH_H

#include "hoodie_id_manager.h"
#include "hoodie_node.h"

#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/templates/vector.hpp>

namespace godot
{

class HoodieMesh : public ArrayMesh {
    GDCLASS(HoodieMesh, ArrayMesh)
    friend class HoodieEditorPlugin;

    typedef uint32_t id_t;
    typedef uint32_t vec_size_t;

    struct NodeSocketPair {
        id_t node;
        vec_size_t socket;

        NodeSocketPair(id_t p_node, vec_size_t p_socket) : node(p_node), socket(p_socket) {}
    };

    struct Connection {
        // Left node id
        id_t l_node;
        // Left socket id
        vec_size_t l_socket;
        // Right node id
        id_t r_node;
        // Right socket id
        vec_size_t r_socket;

        Connection(id_t p_l_node, vec_size_t p_l_socket, id_t p_r_node, vec_size_t p_r_socket)
            : l_node(p_l_node),
              l_socket(p_l_socket),
              r_node(p_r_node),
              r_socket(p_r_socket) {}
    };

    HoodieIdManager<id_t> id_manager;
    HashMap<id_t, Ref<HoodieNode>> hoodie_nodes;
    Vector<Connection> connections;
    bool dirty = false;

    // void trigger_init();
    void trigger_update();
    void update();
    // _update utils
    void _remove_orphan_surfaces();
    void _remove_surface_dumb(id_t p_id);

    id_t add_node(Ref<HoodieNode> p_node);
    void remove_node(id_t p_id);
    Ref<HoodieNode> get_node(id_t p_id);
    Vector<id_t> get_nodes_id_list();

    void add_connection(id_t p_l_node, vec_size_t p_l_socket, id_t p_r_node, vec_size_t p_r_socket);
    void remove_connection(id_t p_l_node, vec_size_t p_l_socket, id_t p_r_node, vec_size_t p_r_socket);
    Vector<Connection> get_connections();

    NodeSocketPair get_left_socket(NodeSocketPair p_right_socket);

protected:
    static void _bind_methods();
    // TODO: _set _get _get_property_list
	// bool _set(const StringName &p_name, const Variant &p_value);
	// bool _get(const StringName &p_name, Variant &r_ret) const;
	// void _get_property_list(List<PropertyInfo> *p_list) const;

public:
    HoodieMesh();
};
    
} // namespace godot


#endif // HOODIE_HOODIEMESH_H