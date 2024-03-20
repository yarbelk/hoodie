#include "hn_curve_to_points.h"

using namespace godot;

void HNCurveToPoints::_process(const Array &p_inputs) {
    out_points.clear();
    out_tangents.clear();
    out_normals.clear();
    out_tilts.clear();
    out_lengths.clear();
    out_factors.clear();

    if (p_inputs.size() == 0) {
        return;
    }

    Array in_0 = p_inputs[0].duplicate();

    out_points = in_0[0];
    out_tangents = in_0[1];
    out_normals = in_0[2];
    out_tilts = in_0[3];
    out_lengths = in_0[4];
    out_factors = in_0[5];
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

const Variant HNCurveToPoints::get_output(int p_port) const {
    switch (p_port) {
        case 0:
            return Variant(out_points);
        case 1:
            return Variant(out_tangents);
        case 2:
            return Variant(out_normals);
        case 3:
            return Variant(out_tilts);
        case 4:
            return Variant(out_lengths);
        case 5:
            return Variant(out_factors);
    }

    return Variant();
}