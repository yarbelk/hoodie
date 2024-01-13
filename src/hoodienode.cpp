#include "hoodienode.h"

using namespace godot;

void HoodieNode::mark_dirty() {
    dirty = true;
    // TODO: emit_changed?
}

void HoodieNode::set_node_info(String p_name, String p_description) {
    node_info = NodeInfo(p_name, p_description);
}

void HoodieNode::set_node_name(String p_name) {
    node_info.name = p_name;
}

String HoodieNode::get_node_name() const {
    return node_info.name;
}

void HoodieNode::set_node_description(String p_description) {
    node_info.description = p_description;
}

String HoodieNode::get_node_description() const {
    return node_info.description;
}

void HoodieNode::set_position(Vector2 p_pos) {
    position = p_pos;
}

Vector2 HoodieNode::get_position() const {
    return position;
}

void HoodieNode::set_status(ProcessStatus p_status) {
    status = p_status;
}

HoodieNode::ProcessStatus HoodieNode::get_status() const {
    return status;
}

void HoodieNode::set_property(Property p_property) {
    property = p_property;
}

Variant::Type HoodieNode::get_property_type() const {
    return property.type;
}

String HoodieNode::get_property_hint() const {
    return property.hint;
}

void HoodieNode::add_socket(Socket &p_socket) {
    if (p_socket.socket_io == Socket::SocketIO::INPUT) {
        input_sockets.push_back(p_socket);
    } else {
        output_sockets.push_back(p_socket);
    }
}

Vector<HoodieNode::Socket> HoodieNode::get_input_sockets() const {
    return input_sockets;
}

Vector<HoodieNode::Socket> HoodieNode::get_output_sockets() const {
    return output_sockets;
}

void HoodieNode::_bind_methods() {

}

HoodieNode::HoodieNode() {
    construct_node_info();
    construct_property();
    construct_sockets();
}