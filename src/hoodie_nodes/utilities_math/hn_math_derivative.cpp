#include "hn_math_derivative.h"

using namespace godot;

void HNMathDerivative::_process(const Array &p_inputs) {
    if (p_inputs.size() == 0) {
        return;
    }

    Array values_arr = p_inputs[0].duplicate();
    PackedFloat32Array values = values_arr;

    float delta = 1.0;

    Array out_values;

    for (int i = 0; i < values.size(); i++) {
        int next_i;
        if (i == values.size() - 1) {
            next_i = 0;
        } else {
            next_i = i + 1;
        }
        float d = (values[next_i] - values[i]) / delta;
        out_values.push_back(d);
    }

    outputs[0] = out_values;
}

String HNMathDerivative::get_caption() const {
    return "Math Derivative";
}

int HNMathDerivative::get_input_port_count() const {
    return 1;
}

HoodieNode::PortType HNMathDerivative::get_input_port_type(int p_port) const {
    switch (p_port) {
        case 0:
            return PortType::PORT_TYPE_SCALAR;
    }

    return PortType::PORT_TYPE_SCALAR;
}

String HNMathDerivative::get_input_port_name(int p_port) const {
    switch (p_port) {
        case 0:
            return "Values";
    }

    return "Value";
}

int HNMathDerivative::get_output_port_count() const {
    return 1;
}

HoodieNode::PortType HNMathDerivative::get_output_port_type(int p_port) const {
    return PortType::PORT_TYPE_SCALAR;
}

String HNMathDerivative::get_output_port_name(int p_port) const {
    return "Values";
}