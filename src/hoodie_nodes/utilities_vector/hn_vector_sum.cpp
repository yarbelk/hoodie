#include "hn_vector_sum.h"

using namespace godot;

void HNVectorSum::_process(const Array &p_inputs) {
    if (p_inputs.size() == 0) {
        return;
    }

    Array v_0_arr = p_inputs[0].duplicate();
    Array v_1_arr = p_inputs[1].duplicate();

    while (v_0_arr.size() < v_1_arr.size()) {
        v_0_arr.push_back(v_0_arr[v_0_arr.size() - 1]);
    }

    while (v_1_arr.size() < v_0_arr.size()) {
        v_1_arr.push_back(v_1_arr[v_1_arr.size() - 1]);
    }

    Array out_values;

    for (int i = 0; i < v_0_arr.size(); i++) {
        const Vector3 a = (Vector3)v_0_arr[i];
        const Vector3 b = (Vector3)v_1_arr[i];
        out_values.push_back(a + b);
    }

    outputs[0] = out_values;
}

String HNVectorSum::get_caption() const {
    return "Vector Sum";
}

int HNVectorSum::get_input_port_count() const {
    return 2;
}

HoodieNode::PortType HNVectorSum::get_input_port_type(int p_port) const {
    switch (p_port) {
        case 0:
            return PortType::PORT_TYPE_VECTOR_3D;
        case 1:
            return PortType::PORT_TYPE_VECTOR_3D;
    }

    return PortType::PORT_TYPE_SCALAR;
}

String HNVectorSum::get_input_port_name(int p_port) const {
    switch (p_port) {
        case 0:
            return "Vector3";
        case 1:
            return "Vector3";
    }

    return "Value";
}

int HNVectorSum::get_output_port_count() const {
    return 1;
}

HoodieNode::PortType HNVectorSum::get_output_port_type(int p_port) const {
    return PortType::PORT_TYPE_VECTOR_3D;
}

String HNVectorSum::get_output_port_name(int p_port) const {
    return "Value";
}