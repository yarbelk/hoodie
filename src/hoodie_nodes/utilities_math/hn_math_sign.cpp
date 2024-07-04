#include "hn_math_sign.h"

using namespace godot;

void HNMathSign::_process(const Array &p_inputs) {
    if (p_inputs.size() == 0) {
        return;
    }

    Array out_values;

    Array values_arr = p_inputs[0].duplicate();
    PackedFloat32Array values = values_arr;

    for (int i = 0; i < values.size(); i++) {
        out_values.push_back(Math::sign(values[i]));
    }

    outputs[0] = out_values;
}

String HNMathSign::get_caption() const {
    return "Math Sign";
}

int HNMathSign::get_input_port_count() const {
    return 1;
}

HoodieNode::PortType HNMathSign::get_input_port_type(int p_port) const {
    switch (p_port) {
        case 0:
            return PortType::PORT_TYPE_SCALAR;
    }

    return PortType::PORT_TYPE_SCALAR;
}

String HNMathSign::get_input_port_name(int p_port) const {
    switch (p_port) {
        case 0:
            return "Value";
    }

    return "Value";
}

int HNMathSign::get_output_port_count() const {
    return 1;
}

HoodieNode::PortType HNMathSign::get_output_port_type(int p_port) const {
    return PortType::PORT_TYPE_SCALAR;
}

String HNMathSign::get_output_port_name(int p_port) const {
    return "Value";
}