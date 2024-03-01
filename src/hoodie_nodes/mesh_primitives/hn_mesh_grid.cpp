#include "hn_mesh_grid.h"

using namespace godot;

String HNMeshGrid::get_caption() const {
    return "Mesh Grid";
}

int HNMeshGrid::get_input_port_count() const {
    return 4;
}

HNMeshGrid::PortType HNMeshGrid::get_input_port_type(int p_port) const {
    switch (p_port) {
        case 0:
            return PortType::PORT_TYPE_SCALAR;
        case 1:
            return PortType::PORT_TYPE_SCALAR;
        case 2:
            return PortType::PORT_TYPE_SCALAR_INT;
        case 3:
            return PortType::PORT_TYPE_SCALAR_INT;
        default:
            return PortType::PORT_TYPE_SCALAR;
    }
}

String HNMeshGrid::get_input_port_name(int p_port) const {
    switch (p_port) {
        case 0:
            return "Size X";
        case 1:
            return "Size Z";
        case 2:
            return "Vertices X";
        case 3:
            return "Vertices Z";
        default:
            return "";
    }
}

int HNMeshGrid::get_output_port_count() const {
    return 2;
}

HNMeshGrid::PortType HNMeshGrid::get_output_port_type(int p_port) const {
    switch (p_port) {
        case 0:
            return PortType::PORT_TYPE_ARRAY;
        case 1:
            return PortType::PORT_TYPE_ARRAY;
        default:
            return PortType::PORT_TYPE_SCALAR;
    }
}

String HNMeshGrid::get_output_port_name(int p_port) const {
    switch (p_port) {
        case 0:
            return "Mesh";
        case 1:
            return "UV Map";
        default:
            return "";
    }
}