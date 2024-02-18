#include "hn_input_curve_3d.h"

using namespace godot;

void HNInputCurve3D::construct_property() {
    set_property(Property(Variant::OBJECT, "Curve3D"));
}

void HNInputCurve3D::construct_sockets() {
    add_socket(Socket(Socket::SocketIO::OUTPUT,
                      Variant::PACKED_VECTOR3_ARRAY,
                      "Points",
                      ""));
    add_socket(Socket(Socket::SocketIO::OUTPUT,
                      Variant::PACKED_VECTOR3_ARRAY,
                      "Tangents",
                      ""));
    add_socket(Socket(Socket::SocketIO::OUTPUT,
                      Variant::PACKED_VECTOR3_ARRAY,
                      "Normals",
                      ""));
    add_socket(Socket(Socket::SocketIO::OUTPUT,
                      Variant::PACKED_FLOAT32_ARRAY,
                      "Tilts",
                      ""));
}