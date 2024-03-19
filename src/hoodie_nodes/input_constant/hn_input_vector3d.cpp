#include "hn_input_vector3d.h"

using namespace godot;

void HNInputVector3D::set_x_value(const float p_value) {
    vector_val.x = p_value;
}

float HNInputVector3D::get_x_value() const {
    return vector_val.x;
}

void HNInputVector3D::set_y_value(const float p_value) {
    vector_val.y = p_value;
}

float HNInputVector3D::get_y_value() const {
    return vector_val.y;
}

void HNInputVector3D::set_z_value(const float p_value) {
    vector_val.z = p_value;
}

float HNInputVector3D::get_z_value() const {
    return vector_val.z;
}

void HNInputVector3D::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_x_value", "value"), &HNInputVector3D::set_x_value);
    ClassDB::bind_method(D_METHOD("get_x_value"), &HNInputVector3D::get_x_value);
    ClassDB::bind_method(D_METHOD("set_y_value", "value"), &HNInputVector3D::set_y_value);
    ClassDB::bind_method(D_METHOD("get_y_value"), &HNInputVector3D::get_y_value);
    ClassDB::bind_method(D_METHOD("set_z_value", "value"), &HNInputVector3D::set_z_value);
    ClassDB::bind_method(D_METHOD("get_z_value"), &HNInputVector3D::get_z_value);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "x_value", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NO_EDITOR), "set_x_value", "get_x_value");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "y_value", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NO_EDITOR), "set_y_value", "get_y_value");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "z_value", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NO_EDITOR), "set_z_value", "get_z_value");
}

void HNInputVector3D::_process(const Array &p_inputs) {
    Vector3 x = vector_val;

    value_arr.clear();
    value_arr.push_back(x);
}

String HNInputVector3D::get_caption() const {
    return "Vector3D";
}

int HNInputVector3D::get_input_port_count() const {
    return 0;
}

HNInputVector3D::PortType HNInputVector3D::get_input_port_type(int p_port) const {
    return PortType::PORT_TYPE_SCALAR;
}

String HNInputVector3D::get_input_port_name(int p_port) const {
    return "";
}

int HNInputVector3D::get_output_port_count() const {
    return 1;
}

HNInputVector3D::PortType HNInputVector3D::get_output_port_type(int p_port) const {
    return PortType::PORT_TYPE_VECTOR_3D;
}

String HNInputVector3D::get_output_port_name(int p_port) const {
    return "Vector3D";
}

int HNInputVector3D::get_property_input_count() const {
    return 3;
}

Variant::Type HNInputVector3D::get_property_input_type(vec_size_t p_prop) const {
    return Variant::FLOAT;
}

Variant HNInputVector3D::get_property_input(vec_size_t p_port) const {
    switch (p_port) {
        case 0:
            return Variant(get_x_value());
        case 1:
            return Variant(get_y_value());
        case 2:
            return Variant(get_z_value());
    }
}

void HNInputVector3D::set_property_input(vec_size_t p_prop, Variant p_input) {
    switch (p_prop) {
        case 0:
            vector_val.x = p_input;
        case 1:
            vector_val.y = p_input;
        case 2:
            vector_val.z = p_input;
    }
}

Vector<StringName> HNInputVector3D::get_editable_properties() const {
    Vector<StringName> props;
    props.push_back("x_value");
    props.push_back("y_value");
    props.push_back("z_value");
    return props;
}

HashMap<StringName, String> HNInputVector3D::get_editable_properties_names() const {
    return HashMap<StringName, String>();
}

const Variant HNInputVector3D::get_output(int p_port) const {
    if (p_port == 0) {
        return Variant(value_arr);
    }

    return Variant();
}