#include "hn_curve_to_points.h"

using namespace godot;

void HNCurveToPoints::_process(const Array &p_inputs) {
    if (p_inputs.size() == 0) {
        return;
    }

    Array in_0 = p_inputs[0].duplicate();

    outputs[0] = in_0[0];
    outputs[1] = in_0[1];
    outputs[2] = in_0[2];
    outputs[3] = in_0[3];
    outputs[4] = in_0[4];
    outputs[5] = in_0[5];
}

String HNCurveToPoints::get_caption() const {
    return "Curve to Points";
}

int HNCurveToPoints::get_input_port_count() const {
    return 1;
}

HNCurveToPoints::PortType HNCurveToPoints::get_input_port_type(int p_port) const {
    return PortType::PORT_TYPE_CURVE;
}

String HNCurveToPoints::get_input_port_name(int p_port) const {
    return "Curve3D";
}

int HNCurveToPoints::get_output_port_count() const {
    return 6;
}

HNCurveToPoints::PortType HNCurveToPoints::get_output_port_type(int p_port) const {
    switch (p_port) {
        case 0:
            return PortType::PORT_TYPE_VECTOR_3D;
        case 1:
            return PortType::PORT_TYPE_VECTOR_3D;
        case 2:
            return PortType::PORT_TYPE_VECTOR_3D;
        case 3:
            return PortType::PORT_TYPE_SCALAR;
        case 4:
            return PortType::PORT_TYPE_SCALAR;
        case 5:
            return PortType::PORT_TYPE_SCALAR;
    }

    return PortType::PORT_TYPE_SCALAR;
}

String HNCurveToPoints::get_output_port_name(int p_port) const {
    switch (p_port) {
        case 0:
            return "Points";
        case 1:
            return "Tangents";
        case 2:
            return "Normals";
        case 3:
            return "Tilts";
        case 4:
            return "Lengths";
        case 5:
            return "Factors";
    }

    return "";
}