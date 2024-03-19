#include "hn_curve_to_points.h"

using namespace godot;

void HNCurveToPoints::_process(const Array &p_inputs) {
    // TODO: implement curve_to_points _process
}

String HNCurveToPoints::get_caption() const {
    return "Value";
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
    return 4;
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
        default:
            return PortType::PORT_TYPE_SCALAR;
    }
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
        default:
            return "";
    }
}

const Variant HNCurveToPoints::get_output(int p_port) const {
    switch (p_port) {
        case 0:
            return Variant(points);
        case 1:
            return Variant(tangents);
        case 2:
            return Variant(normals);
        case 3:
            return Variant(tilts);
        default:
            return Variant();
    }
}