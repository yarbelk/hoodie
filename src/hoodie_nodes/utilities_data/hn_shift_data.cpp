#include "hn_shift_data.h"

#include <godot_cpp/classes/array_mesh.hpp>

using namespace godot;

void HNShiftData::_process(const Array &p_inputs) {
    Array in_data = p_inputs[0];
    int in_offset = 0;

    {
        Array a = p_inputs[1];
        if (a.size() > 0) {
            in_offset = a[0];
        }
    }

    if (in_data.size() < 1) { return; }

    Array shifted;
    shifted.resize(in_data.size());

    for (int i = 0; i < in_data.size(); i++) {
        int n = in_data.size();
        int a = i + in_offset;

        a = ((a % n) + n) % n;

        shifted[i] = in_data[a];
    }

    set_output(0, shifted);
}

String HNShiftData::get_caption() const {
    return "Shift Data";
}

int HNShiftData::get_input_port_count() const {
    return 2;
}

HoodieNode::PortType HNShiftData::get_input_port_type(int p_port) const {
    switch (p_port) {
        case 0:
            return PortType::PORT_TYPE_DATA;
        case 1:
            return PortType::PORT_TYPE_SCALAR_INT;
        default:
            return PortType::PORT_TYPE_SCALAR;
    }
}

String HNShiftData::get_input_port_name(int p_port) const {
    switch (p_port) {
        case 0:
            return "Data";
        case 1:
            return "Offset";
        default:
            return "";
    }
}

int HNShiftData::get_output_port_count() const {
    return 1;
}

HoodieNode::PortType HNShiftData::get_output_port_type(int p_port) const {
    return PortType::PORT_TYPE_DATA;
}

String HNShiftData::get_output_port_name(int p_port) const {
    return "Data";
}