#include "hn_output.h"

using namespace godot;

String HNOutput::get_caption() const {
    return "Output";
}

int HNOutput::get_input_port_count() const {
    return 1;
}

HNOutput::PortType HNOutput::get_input_port_type(int p_port) const {
    return PortType::PORT_TYPE_GEOMETRY;
}

String HNOutput::get_input_port_name(int p_port) const {
    return "Geometry";
}

int HNOutput::get_output_port_count() const {
    return 0;
}

HNOutput::PortType HNOutput::get_output_port_type(int p_port) const {
    return PortType::PORT_TYPE_SCALAR;
}

String HNOutput::get_output_port_name(int p_port) const {
    return "";
}