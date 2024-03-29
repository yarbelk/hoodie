#include "hn_combine_xyz.h"

using namespace godot;

void HNCombineXYZ::_process(const Array &p_inputs) {
    out_xyz.clear();

    if (p_inputs.size() == 0) {
        return;
    }

    Array in_x = p_inputs[0].duplicate();
    Array in_y = p_inputs[1].duplicate();
    Array in_z = p_inputs[2].duplicate();

    int max = MAX(in_x.size(), MAX(in_y.size(), in_z.size()));
    if (in_x.size() < max) {
        in_x.resize(max);
    }
    if (in_y.size() < max) {
        in_y.resize(max);
    }
    if (in_z.size() < max) {
        in_z.resize(max);
    }

    for (int i = 0; i < max; i++) {
        out_xyz.push_back(Vector3((float)in_x[i], (float)in_y[i], (float)in_z[i]));
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