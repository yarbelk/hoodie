#include "hn_vector_cross.h"

using namespace godot;

void HNVectorCross::_process(const Array &p_inputs) {
    out.clear();

    if (p_inputs.size() == 0) {
        return;
    }

    Array vectors_0_arr = p_inputs[0].duplicate();
    Array vectors_1_arr = p_inputs[1].duplicate();

    while (vectors_0_arr.size() < vectors_1_arr.size()) {
        vectors_0_arr.push_back(vectors_0_arr[vectors_0_arr.size() - 1]);
    }

    while (vectors_1_arr.size() < vectors_0_arr.size()) {
        vectors_1_arr.push_back(vectors_1_arr[vectors_1_arr.size() - 1]);
    }

    for (int i = 0; i < vectors_0_arr.size(); i++) {
        const Vector3 a = (Vector3)vectors_0_arr[i];
        const Vector3 b = (Vector3)vectors_1_arr[i];
        out.push_back(a.cross(b));
    }
}

String HNVectorCross::get_caption() const {
    return "Vector Cross";
}

int HNVectorCross::get_input_port_count() const {
    return 2;
}

HoodieNode::PortType HNVectorCross::get_input_port_type(int p_port) const {
    switch (p_port) {
        case 0:
            return PortType::PORT_TYPE_VECTOR_3D;
        case 1:
            return PortType::PORT_TYPE_VECTOR_3D;
    }

    return PortType::PORT_TYPE_SCALAR;
}

String HNVectorCross::get_input_port_name(int p_port) const {
    switch (p_port) {
        case 0:
            return "Vector3";
        case 1:
            return "Vector3";
    }

    return "Value";
}

int HNVectorCross::get_output_port_count() const {
    return 1;
}

HoodieNode::PortType HNVectorCross::get_output_port_type(int p_port) const {
    return PortType::PORT_TYPE_VECTOR_3D;
}

String HNVectorCross::get_output_port_name(int p_port) const {
    return "Vector3";
}

const Variant HNVectorCross::get_output(int p_port) const {
    if (p_port == 0) {
        return Variant(out);
    }

    return Variant();
}