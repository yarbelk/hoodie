#include "hn_input_value.h"

using namespace godot;

void HNInputValue::set_float_value(const float p_value) {
    float_val = p_value;
}

float HNInputValue::get_float_value() const {
    return float_val;
}

void HNInputValue::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_float_value", "value"), &HNInputValue::set_float_value);
    ClassDB::bind_method(D_METHOD("get_float_value"), &HNInputValue::get_float_value);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "float_value", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NO_EDITOR), "set_float_value", "get_float_value");
}

void HNInputValue::_process(const Array &p_inputs) {
    float x = float_val;

    value_arr.clear();
    value_arr.push_back(x);
}

String HNInputValue::get_caption() const {
    return "Input Value";
}

int HNInputValue::get_input_port_count() const {
    return 0;
}

HNInputValue::PortType HNInputValue::get_input_port_type(int p_port) const {
    return PortType::PORT_TYPE_SCALAR;
}

String HNInputValue::get_input_port_name(int p_port) const {
    return "";
}

int HNInputValue::get_output_port_count() const {
    return 1;
}

HNInputValue::PortType HNInputValue::get_output_port_type(int p_port) const {
    return PortType::PORT_TYPE_SCALAR;
}

String HNInputValue::get_output_port_name(int p_port) const {
    return "Value";
}

int HNInputValue::get_property_input_count() const {
    return 1;
}

Variant::Type HNInputValue::get_property_input_type(vec_size_t p_prop) const {
    return Variant::FLOAT;
}

Variant HNInputValue::get_property_input(vec_size_t p_port) const {
    return Variant(float_val);
}

void HNInputValue::set_property_input(vec_size_t p_prop, Variant p_input) {
    float_val = (float)p_input;
}

Vector<StringName> HNInputValue::get_editable_properties() const {
    Vector<StringName> props;
    props.push_back("float_value");
    return props;
}

HashMap<StringName, String> HNInputValue::get_editable_properties_names() const {
    return HashMap<StringName, String>();
}

const Variant HNInputValue::get_output(int p_port) const {
    if (p_port == 0) {
        return Variant(value_arr);
    }

    return Variant();
}