#include "hn_separate_xyz.h"

using namespace godot;

void HNSeparateXYZ::_process(const Array &p_inputs) {
    out_x.clear();
    out_y.clear();
    out_z.clear();

    if (p_inputs.size() == 0) {
        return;
    }

    // Works with vanilla Input Vector3D node
    Array in_arr = p_inputs;
    Array in = p_inputs[0];

    Array in_arr_vectors = in_arr[0];

    if (in_arr_vectors.size() == 0) {
        return;
    }

    // Works with vanilla Input Vector3D node
    if (in.size() == 0) {
        return;
    }

    if (in[0].get_type() == Variant::VECTOR2) {
        Vector2 in_vec = (Vector2)in[0];

        out_x.push_back(in_vec.x);
        out_y.push_back(in_vec.y);
        out_z.push_back(0);
    } else if (in[0].get_type() == Variant::VECTOR3) {
        Vector3 in_vec = (Vector3)in[0];

        out_x.push_back(in_vec.x);
        out_y.push_back(in_vec.y);
        out_z.push_back(in_vec.z);
    }
}

String HNSeparateXYZ::get_caption() const {
    return "Separate XYZ";
}

int HNSeparateXYZ::get_input_port_count() const {
    return 1;
}

HNSeparateXYZ::PortType HNSeparateXYZ::get_input_port_type(int p_port) const {
    return PortType::PORT_TYPE_VECTOR_3D;
}

String HNSeparateXYZ::get_input_port_name(int p_port) const {
    return "Vector3D";
}

int HNSeparateXYZ::get_output_port_count() const {
    return 3;
}

HNSeparateXYZ::PortType HNSeparateXYZ::get_output_port_type(int p_port) const {
    switch (p_port) {
        case 0:
            return PortType::PORT_TYPE_SCALAR;
        case 1:
            return PortType::PORT_TYPE_SCALAR;
        case 2:
            return PortType::PORT_TYPE_SCALAR;
    }

    return PortType::PORT_TYPE_SCALAR;
}

String HNSeparateXYZ::get_output_port_name(int p_port) const {
    switch (p_port) {
        case 0:
            return "X";
        case 1:
            return "Y";
        case 2:
            return "Z";
    }

    return "";
}

const Variant HNSeparateXYZ::get_output(int p_port) const {
    switch (p_port) {
        case 0:
            return Variant(out_x);
        case 1:
            return Variant(out_y);
        case 2:
            return Variant(out_z);
    }

    return Variant();
}