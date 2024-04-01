#include "hn_points_curvature.h"

#include <godot_cpp/classes/array_mesh.hpp>

using namespace godot;

void HNPointsCurvature::_process(const Array &p_inputs) {
    PackedVector3Array verts;
    PackedVector3Array up_vecs;

    out.clear();

    if (p_inputs.size() > 0) {
        if (p_inputs[0].get_type() == Variant::ARRAY) {
            Array a = p_inputs[0];
            if (a.size() > 0) {
                verts = a;
            }
        }
        if (p_inputs[1].get_type() == Variant::ARRAY) {
            Array a = p_inputs[1];
            if (a.size() > 0) {
                up_vecs = a;
            }
        }
    } else {
        return;
    }

    up_vecs.resize(verts.size());

    PackedFloat32Array curvature_values;
    curvature_values.resize(verts.size());

    // Calculate curvature and triangle area
    // https://hratliff.com/posts/2019/02/curvature-of-three-points/
    // https://math.stackexchange.com/questions/128991/how-to-calculate-the-area-of-a-3d-triangle
    for (int i = 0; i < verts.size(); i++) {
        Vector3 a;
        Vector3 b = verts[i];
        Vector3 c;

        if (i == 0) {
            a = verts[verts.size() - 1];
        } else {
            a = verts[i - 1];
        }

        if (i == verts.size() - 1) {
            c = verts[0];
        } else {
            c = verts[i + 1];
        }

        Vector3 bc = c - b;
        Vector3 ba = a - b;
        Vector3 ca = a - c;

        Vector3 cross = ba.cross(bc);

        float area = cross.length() * 0.5;

        float signed_angle = ba.signed_angle_to(bc, up_vecs[i]);
        float sign = Math::sign(signed_angle);

        float curvature = sign * (4 * area) / (bc.length() * ba.length() * ca.length());

        curvature_values[i] = curvature;
    }

    // out.push_back(curvature_values);
    out.append_array(curvature_values);
}

String HNPointsCurvature::get_caption() const {
    return "Points Curvature";
}

int HNPointsCurvature::get_input_port_count() const {
    return 2;
}

HoodieNode::PortType HNPointsCurvature::get_input_port_type(int p_port) const {
    switch (p_port) {
        case 0:
            return PortType::PORT_TYPE_VECTOR_3D;
        case 1:
            return PortType::PORT_TYPE_VECTOR_3D;
        default:
            return PortType::PORT_TYPE_SCALAR;
    }
}

String HNPointsCurvature::get_input_port_name(int p_port) const {
    switch (p_port) {
        case 0:
            return "Points";
        case 1:
            return "Up Vectors";
        default:
            return "";
    }
}

int HNPointsCurvature::get_output_port_count() const {
    return 1;
}

HoodieNode::PortType HNPointsCurvature::get_output_port_type(int p_port) const {
    return PortType::PORT_TYPE_SCALAR;
}

String HNPointsCurvature::get_output_port_name(int p_port) const {
    return "Curvature";
}

const Variant HNPointsCurvature::get_output(int p_port) const {
    return Variant(out);
}