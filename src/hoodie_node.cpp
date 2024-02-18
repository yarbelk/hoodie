#include "hoodie_node.h"

using namespace godot;

void HoodieNode::mark_dirty() {
    dirty = true;
    // TODO: emit_changed?
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

void HoodieNode::construct_property() {}

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

void HoodieNode::construct_sockets() {}

void HoodieNode::_bind_methods() {

}

bool HoodieNode::update(const Array &p_inputs) {
    // TODO: implement update
    return false;
}

HoodieNode::HoodieNode() {
    construct_property();
    construct_sockets();
}
