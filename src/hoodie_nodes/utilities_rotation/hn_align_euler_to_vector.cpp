#include "hn_align_euler_to_vector.h"

#include <godot_cpp/classes/array_mesh.hpp>

using namespace godot;

void HNAlignEulerToVector::set_axis(const AxisXYZ p_value) {
    axis = p_value;
}

HNAlignEulerToVector::AxisXYZ HNAlignEulerToVector::get_axis() const {
    return axis;
}

void HNAlignEulerToVector::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_axis", "value"), &HNAlignEulerToVector::set_axis);
    ClassDB::bind_method(D_METHOD("get_axis"), &HNAlignEulerToVector::get_axis);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "Axis", PROPERTY_HINT_ENUM, "X,Y,Z", PROPERTY_USAGE_NO_EDITOR), "set_axis", "get_axis");

    BIND_ENUM_CONSTANT(AxisXYZ::X);
    BIND_ENUM_CONSTANT(AxisXYZ::Y);
    BIND_ENUM_CONSTANT(AxisXYZ::Z);
}

void HNAlignEulerToVector::_process(const Array &p_inputs) {
    PackedVector3Array rotations;
    PackedFloat32Array factors;
    PackedVector3Array vectors;

    PackedVector3Array out_rotations;

    out.clear();

    if (p_inputs.size() == 0) {
        return;
    }

    // Input arrays initialization
    rotations = p_inputs[0].duplicate();
    factors = p_inputs[1].duplicate();
    vectors = p_inputs[2].duplicate();

    Vector3 axis_vec;
    Vector3 target_vec;
    Vector3 cross;

    switch(axis) {
        case X:
            axis_vec = Vector3(1,0,0);
            break;
        case Y:
            axis_vec = Vector3(0,1,0);
            break;
        case Z:
            axis_vec = Vector3(0,0,1);
            break;
    }

    int count = MAX(rotations.size(), MAX(factors.size(), vectors.size()));

    for (int i = 0; i < count; i++) {
        target_vec = vectors[MIN(i, vectors.size() - 1)];

        target_vec.normalize();
        cross = axis_vec.cross(target_vec);
        float angle = Math::acos(axis_vec.dot(target_vec));

        float factor = 1;
        if (factors.size() > 0) {
            factor = factors[MIN(i, factors.size() - 1)];
        }

        angle = Math::lerp_angle(0, angle, factor);

        Quaternion rot_quat = Quaternion(cross, angle);
        Vector3 euler_rot = rot_quat.get_euler_xyz();

        out.push_back(euler_rot);
    }
}

String HNAlignEulerToVector::get_caption() const {
    return "Align Euler to Vector";
}

int HNAlignEulerToVector::get_input_port_count() const {
    return 3;
}

HoodieNode::PortType HNAlignEulerToVector::get_input_port_type(int p_port) const {
    switch (p_port) {
        case 0:
            return PortType::PORT_TYPE_VECTOR_3D;
        case 1:
            return PortType::PORT_TYPE_SCALAR;
        case 2:
            return PortType::PORT_TYPE_VECTOR_3D;
        default:
            return PortType::PORT_TYPE_SCALAR;
    }
}

String HNAlignEulerToVector::get_input_port_name(int p_port) const {
    switch (p_port) {
        case 0:
            return "Rotation";
        case 1:
            return "Factor";
        case 2:
            return "Vector";
        default:
            return "";
    }
}

int HNAlignEulerToVector::get_output_port_count() const {
    return 1;
}

HoodieNode::PortType HNAlignEulerToVector::get_output_port_type(int p_port) const {
    return PortType::PORT_TYPE_VECTOR_3D;
}

String HNAlignEulerToVector::get_output_port_name(int p_port) const {
    return "Rotation";
}

int HNAlignEulerToVector::get_property_input_count() const {
    return 1;
}

Variant::Type HNAlignEulerToVector::get_property_input_type(vec_size_t p_prop) const {
    return Variant::INT;
}

Variant HNAlignEulerToVector::get_property_input(vec_size_t p_port) const {
    return Variant(axis);
}

void HNAlignEulerToVector::set_property_input(vec_size_t p_prop, Variant p_input) {
    axis = (AxisXYZ)(int)p_input;
}

Vector<StringName> HNAlignEulerToVector::get_editable_properties() const {
    Vector<StringName> props;
    props.push_back("Axis");
    // TODO: VisualShaderNodeIntParameter::get_editable_properties()
    return props;
}

HashMap<StringName, String> HNAlignEulerToVector::get_editable_properties_names() const {
    return HashMap<StringName, String>();
}

const Variant HNAlignEulerToVector::get_output(int p_port) const {
    return Variant(out);
}