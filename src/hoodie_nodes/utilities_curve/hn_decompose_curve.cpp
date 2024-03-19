#include "hn_decompose_curve.h"

using namespace godot;

void HNDecomposeCurve::_process(const Array &p_inputs) {
    UtilityFunctions::print("Decompose Mesh _process() call.");

    out_points.clear();
    out_tangents.clear();
    out_normals.clear();
    out_tilts.clear();
    out_lengths.clear();
    out_factors.clear();

    if (p_inputs.size() == 0) {
        return;
    }

    Array inputs = p_inputs;

    Array in_0 = inputs[0];

    // TODO: unnecessary step?
    Array in_points = in_0[0];
    Array in_tangents = in_0[1];
    Array in_normals = in_0[2];
    Array in_tilts = in_0[3];
    Array in_lenghts = in_0[4];
    Array in_factors = in_0[5];

    out_points = in_points;
    out_tangents = in_tangents;
    out_normals = in_normals;
    out_tilts = in_tilts;
    out_lengths = in_lenghts;
    out_factors = in_factors;
}

String HNDecomposeCurve::get_caption() const {
    return "Decompose Curve";
}

int HNDecomposeCurve::get_input_port_count() const {
    return 1;
}

HNDecomposeCurve::PortType HNDecomposeCurve::get_input_port_type(int p_port) const {
    return PortType::PORT_TYPE_CURVE;
}

String HNDecomposeCurve::get_input_port_name(int p_port) const {
    return "Curve3D";
}

int HNDecomposeCurve::get_output_port_count() const {
    return 6;
}

HNDecomposeCurve::PortType HNDecomposeCurve::get_output_port_type(int p_port) const {
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

String HNDecomposeCurve::get_output_port_name(int p_port) const {
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

const Variant HNDecomposeCurve::get_output(int p_port) const {
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