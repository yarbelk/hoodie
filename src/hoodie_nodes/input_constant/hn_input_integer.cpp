#include "hn_input_integer.h"

using namespace godot;

void HNInputInteger::set_int_value(const int p_value) {
    int_val = p_value;
}

int HNInputInteger::get_int_value() const {
    return int_val;
}

void HNInputInteger::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_int_value", "value"), &HNInputInteger::set_int_value);
    ClassDB::bind_method(D_METHOD("get_int_value"), &HNInputInteger::get_int_value);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "int_value", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NO_EDITOR), "set_int_value", "get_int_value");
}

void HNInputInteger::_process(const Array &p_inputs) {
    int x = int_val;

    value_arr.clear();
    value_arr.push_back(x);
}

String HNInputInteger::get_caption() const {
    return "Input Integer";
}

int HNInputInteger::get_input_port_count() const {
    return 0;
}

HNInputInteger::PortType HNInputInteger::get_input_port_type(int p_port) const {
    return PortType::PORT_TYPE_SCALAR;
}

String HNInputInteger::get_input_port_name(int p_port) const {
    return "";
}

int HNInputInteger::get_output_port_count() const {
    return 1;
}

HNInputInteger::PortType HNInputInteger::get_output_port_type(int p_port) const {
    return PortType::PORT_TYPE_SCALAR_INT;
}

String HNInputInteger::get_output_port_name(int p_port) const {
    return "Integer";
}

int HNInputInteger::get_property_input_count() const {
    return 1;
}

Variant::Type HNInputInteger::get_property_input_type(vec_size_t p_prop) const {
    return Variant::INT;
}

Variant HNInputInteger::get_property_input(vec_size_t p_port) const {
    return Variant(int_val);
}

void HNInputInteger::set_property_input(vec_size_t p_prop, Variant p_input) {
    int_val = (int)p_input;
}

Vector<StringName> HNInputInteger::get_editable_properties() const {
    Vector<StringName> props;
    props.push_back("int_value");
    // TODO: VisualShaderNodeIntParameter::get_editable_properties()
    return props;
}

HashMap<StringName, String> HNInputInteger::get_editable_properties_names() const {
    return HashMap<StringName, String>();
}

const Variant HNInputInteger::get_output(int p_port) const {
    if (p_port == 0) {
        return Variant(value_arr);
    }

    return Variant();
}