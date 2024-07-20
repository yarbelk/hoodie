#include "hn_points_distance.h"

#include <godot_cpp/classes/array_mesh.hpp>

using namespace godot;

void HNPointsDistance::_process(const Array &p_inputs) {
    PackedVector3Array in_a = p_inputs[0];
    PackedVector3Array in_b = p_inputs[1];

    if (in_a.size() == 0) { return; }
    if (in_b.size() == 0) { return; }

    if (in_a.size() != in_b.size()) { return; }

    in_b.resize(in_a.size());

    PackedFloat32Array distances;
    distances.resize(in_a.size());

    for (int i = 0; i < in_a.size(); i++) {
        Vector3 a = in_a[i];
        Vector3 b = in_b[i];

        distances[i] = (b - a).length();
    }

    outputs[0] = distances;
}

String HNPointsDistance::get_caption() const {
    return "Points Distance";
}

int HNPointsDistance::get_input_port_count() const {
    return 2;
}

HoodieNode::PortType HNPointsDistance::get_input_port_type(int p_port) const {
    switch (p_port) {
        case 0:
            return PortType::PORT_TYPE_VECTOR_3D;
        case 1:
            return PortType::PORT_TYPE_VECTOR_3D;
        default:
            return PortType::PORT_TYPE_VECTOR_3D;
    }
}

String HNPointsDistance::get_input_port_name(int p_port) const {
    switch (p_port) {
        case 0:
            return "Points";
        case 1:
            return "Points";
        default:
            return "";
    }
}

int HNPointsDistance::get_output_port_count() const {
    return 1;
}

HoodieNode::PortType HNPointsDistance::get_output_port_type(int p_port) const {
    return PortType::PORT_TYPE_SCALAR;
}

String HNPointsDistance::get_output_port_name(int p_port) const {
    return "Distance";
}