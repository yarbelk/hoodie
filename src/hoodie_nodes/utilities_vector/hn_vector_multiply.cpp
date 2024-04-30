#include "hn_vector_multiply.h"

using namespace godot;

void HNVectorMultiply::_process(const Array &p_inputs) {
    if (p_inputs.size() == 0) {
        return;
    }

    Array vectors_arr = p_inputs[0].duplicate();
    Array fac_arr = p_inputs[1].duplicate();

    while (vectors_arr.size() < fac_arr.size()) {
        vectors_arr.push_back(vectors_arr[vectors_arr.size() - 1]);
    }

    while (fac_arr.size() < vectors_arr.size()) {
        fac_arr.push_back(fac_arr[fac_arr.size() - 1]);
    }

    Array out_values;

    for (int i = 0; i < vectors_arr.size(); i++) {
        const Vector3 a = (Vector3)vectors_arr[i];
        const float b = (float)fac_arr[i];
        out_values.push_back(a * b);
    }

    outputs[0] = out_values;
}

String HNVectorMultiply::get_caption() const {
    return "Vector Multiply";
}

int HNVectorMultiply::get_input_port_count() const {
    return 2;
}

HoodieNode::PortType HNVectorMultiply::get_input_port_type(int p_port) const {
    switch (p_port) {
        case 0:
            return PortType::PORT_TYPE_VECTOR_3D;
        case 1:
            return PortType::PORT_TYPE_SCALAR;
    }

    return PortType::PORT_TYPE_SCALAR;
}

String HNVectorMultiply::get_input_port_name(int p_port) const {
    switch (p_port) {
        case 0:
            return "Vector3";
        case 1:
            return "Value";
    }

    return "Value";
}

int HNVectorMultiply::get_output_port_count() const {
    return 1;
}

HoodieNode::PortType HNVectorMultiply::get_output_port_type(int p_port) const {
    return PortType::PORT_TYPE_VECTOR_3D;
}

String HNVectorMultiply::get_output_port_name(int p_port) const {
    return "Value";
}