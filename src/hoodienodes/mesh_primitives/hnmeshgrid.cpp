#include "hnmeshgrid.h"

using namespace godot;

void HNMeshGrid::construct_node_info() {
    set_node_info("Grid", "");
}

void HNMeshGrid::construct_property() {}

void HNMeshGrid::construct_sockets() {
    add_socket(Socket(Socket::SocketIO::INPUT,
                      Variant::FLOAT,
                      "Size X",
                      "Side length of the plane in the X direction"));
    add_socket(Socket(Socket::SocketIO::INPUT,
                      Variant::FLOAT,
                      "Size Z",
                      "Side length of the plane in the Z direction"));
    add_socket(Socket(Socket::SocketIO::INPUT,
                      Variant::INT,
                      "Vertices X",
                      "Number of vertices in the X direction"));
    add_socket(Socket(Socket::SocketIO::INPUT,
                      Variant::INT,
                      "Vertices Z",
                      "Number of vertices in the Z direction"));
    add_socket(Socket(Socket::SocketIO::OUTPUT,
                      Variant::ARRAY,
                      "Mesh",
                      ""));
    add_socket(Socket(Socket::SocketIO::OUTPUT,
                      Variant::ARRAY,
                      "UV Map",
                      ""));
}
