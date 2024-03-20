#include "hn_transform_geometry.h"

#include <godot_cpp/classes/array_mesh.hpp>

using namespace godot;

void HNTransformGeometry::_process(const Array &p_inputs) {
    out.clear();

    if (p_inputs.size() == 0) {
        return;
    }

    out = p_inputs[0].duplicate();
    PackedVector3Array mesh_verts = out[0];

    // Translate, Rotate, Scale
    Array translations = p_inputs[1].duplicate();
    Array rotations = p_inputs[2].duplicate();
    Array scales = p_inputs[3].duplicate();

    Transform3D transform;
    Basis basis;

    Vector3 translation_vector = Vector3(0, 0, 0);
    Quaternion rotation_quaternion;
    Vector3 scale_vector = Vector3(1, 1, 1);

    if (translations.size() > 0) {
        translation_vector = translations[0];
    }

    if (rotations.size() > 0) {
        // rotation_quaternion = ...
    }

    if (scales.size() > 0) {
        scale_vector = scales[0];
    }

    basis = Basis(basis.get_quaternion(), scale_vector);

    transform = Transform3D(basis, translation_vector);

    for (int i = 0; i < mesh_verts.size(); i++) {
        Vector3 v = mesh_verts[i];
        mesh_verts[i] = transform.xform(v);
    }
    
    out[0] = mesh_verts;
}

String HNTransformGeometry::get_caption() const {
    return "Transform Mesh";
}

int HNTransformGeometry::get_input_port_count() const {
    return 4;
}

HNTransformGeometry::PortType HNTransformGeometry::get_input_port_type(int p_port) const {
    switch (p_port) {
        case 0:
            return PortType::PORT_TYPE_GEOMETRY;
        case 1:
            return PortType::PORT_TYPE_VECTOR_3D;
        case 2:
            return PortType::PORT_TYPE_VECTOR_3D;
        case 3:
            return PortType::PORT_TYPE_VECTOR_3D;
    }

    return PortType::PORT_TYPE_SCALAR;
}

String HNTransformGeometry::get_input_port_name(int p_port) const {
    switch (p_port) {
        case 0:
            return "Geometry";
        case 1:
            return "Translation";
        case 2:
            return "Rotation";
        case 3:
            return "Scale";
    }

    return "";
}

int HNTransformGeometry::get_output_port_count() const {
    return 1;
}

HNTransformGeometry::PortType HNTransformGeometry::get_output_port_type(int p_port) const {
    return PortType::PORT_TYPE_GEOMETRY;
}

String HNTransformGeometry::get_output_port_name(int p_port) const {
    return "Geometry";
}

const Variant HNTransformGeometry::get_output(int p_port) const {
    return Variant(out);
}