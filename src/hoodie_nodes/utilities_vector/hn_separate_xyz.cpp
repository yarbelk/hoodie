#include "hn_separate_xyz.h"

using namespace godot;

void HNSeparateXYZ::_process(const Array &p_inputs) {
    if (p_inputs.size() == 0) {
        return;
    }

    // Works with vanilla Input Vector3D node
    Array in_arr = p_inputs.duplicate();
    Array in = p_inputs[0];

    if (in.size() == 0) {
        return;
    }

    Array out_x_values;
    Array out_y_values;
    Array out_z_values;

    for (int i = 0; i < in.size(); i++) {
        if (in[i].get_type() == Variant::VECTOR2) {
            Vector2 in_vec = (Vector2)in[i];

            out_x_values.push_back(in_vec.x);
            out_y_values.push_back(in_vec.y);
            out_z_values.push_back(0);
        } else if (in[i].get_type() == Variant::VECTOR3) {
            Vector3 in_vec = (Vector3)in[i];

            out_x_values.push_back(in_vec.x);
            out_y_values.push_back(in_vec.y);
            out_z_values.push_back(in_vec.z);
        }
    }
    
    outputs[0] = out_x_values;
    outputs[1] = out_y_values;
    outputs[2] = out_z_values;
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