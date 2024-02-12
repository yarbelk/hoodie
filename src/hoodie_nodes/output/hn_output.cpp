#include "hn_output.h"

using namespace godot;

void HNOutput::construct_node_info() {
    set_node_info("Output", "");
}

void HNOutput::construct_property() {}

void HNOutput::construct_sockets() {
    add_socket(Socket(Socket::SocketIO::INPUT,
                      Variant::ARRAY,
                      "Geometry",
                      ""));
}