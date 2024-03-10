#include "hn_input_vector3d.h"

using namespace godot;

void HNInputVector3D::_process(const Array &p_inputs) {
    UtilityFunctions::print("HNInputValue _process() call.");

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
    return 1;
}

Variant::Type HNInputVector3D::get_property_input_type(vec_size_t p_prop) const {
    return Variant::VECTOR3;
}

Variant HNInputVector3D::get_property_input(vec_size_t p_port) const {
    return Variant(vector_val);
}

void HNInputVector3D::set_property_input(vec_size_t p_prop, Variant p_input) {
    vector_val = (Vector3)p_input;
}

const Variant HNInputVector3D::get_output(int p_port) const {
    if (p_port == 0) {
        return Variant(value_arr);
    }

    return Variant();
}