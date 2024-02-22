#include "hn_output.h"

using namespace godot;

int HNOutput::get_input_port_count() const {
    return 1;
}

HNOutput::PortType HNOutput::get_input_port_type(int p_port) const {
    return PortType::PORT_TYPE_ARRAY;
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