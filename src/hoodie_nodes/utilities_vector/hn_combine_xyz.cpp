#include "hn_combine_xyz.h"

using namespace godot;

void HNCombineXYZ::_process(const Array &p_inputs) {
    out_xyz.clear();

    if (p_inputs.size() == 0) {
        return;
    }

    Array in_x = p_inputs[0];
    Array in_y = p_inputs[1];
    Array in_z = p_inputs[2];

    // if Vector2 else Vector3.
    if (in_z.size() == 0) {
        out_xyz.push_back(Vector3((float)in_x[0], (float)in_y[0], 0));
    } else {
        out_xyz.push_back(Vector3((float)in_x[0], (float)in_y[0], (float)in_z[0]));
    }
}

String HNCombineXYZ::get_caption() const {
    return "Combine XYZ";
}

int HNCombineXYZ::get_input_port_count() const {
    return 3;
}

HNCombineXYZ::PortType HNCombineXYZ::get_input_port_type(int p_port) const {
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

String HNCombineXYZ::get_input_port_name(int p_port) const {
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

int HNCombineXYZ::get_output_port_count() const {
    return 1;
}

HNCombineXYZ::PortType HNCombineXYZ::get_output_port_type(int p_port) const {
    return PortType::PORT_TYPE_VECTOR_3D;
}

String HNCombineXYZ::get_output_port_name(int p_port) const {
    return "Vector3D";
}

const Variant HNCombineXYZ::get_output(int p_port) const {
    return Variant(out_xyz);
}