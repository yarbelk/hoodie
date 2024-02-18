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

HoodieMesh::id_t HoodieMesh::add_node(Ref<HoodieNode> p_node) {
    id_t id = id_manager.generateID();
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

}

HoodieMesh::HoodieMesh() {

}
