#include "hoodienode.h"

using namespace godot;

void HoodieNode::add_socket(Socket &p_socket) {
    if (p_socket.socket_io == Socket::SocketIO::INPUT) {
        input_sockets.push_back(p_socket);
    } else {
        output_sockets.push_back(p_socket);
    }
}

HoodieNode::HoodieNode() {
    construct_sockets();
}