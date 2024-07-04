#include "hn_input_string.h"

using namespace godot;

void HNInputString::set_string_value(const String p_value) {
    string_val = p_value;
}

String HNInputString::get_string_value() const {
    return string_val;
}

void HNInputString::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_string_value", "value"), &HNInputString::set_string_value);
    ClassDB::bind_method(D_METHOD("get_string_value"), &HNInputString::get_string_value);

    ADD_PROPERTY(PropertyInfo(Variant::STRING, "string_value", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NO_EDITOR), "set_string_value", "get_string_value");
}

void HNInputString::_process(const Array &p_inputs) {
    set_output(0, string_val);
}

String HNInputString::get_caption() const {
    return "Input String";
}

int HNInputString::get_input_port_count() const {
    return 0;
}

HoodieNode::PortType HNInputString::get_input_port_type(int p_port) const {
    return PortType::PORT_TYPE_SCALAR;
}

String HNInputString::get_input_port_name(int p_port) const {
    return "";
}

int HNInputString::get_output_port_count() const {
    return 1;
}

HoodieNode::PortType HNInputString::get_output_port_type(int p_port) const {
    return PortType::PORT_TYPE_STRING;
}

String HNInputString::get_output_port_name(int p_port) const {
    return "Value";
}

int HNInputString::get_property_input_count() const {
    return 1;
}

Variant::Type HNInputString::get_property_input_type(vec_size_t p_prop) const {
    return Variant::STRING;
}

Variant HNInputString::get_property_input(vec_size_t p_port) const {
    return Variant(string_val);
}

void HNInputString::set_property_input(vec_size_t p_prop, Variant p_input) {
    string_val = (String)p_input;
}

Vector<StringName> HNInputString::get_editable_properties() const {
    Vector<StringName> props;
    props.push_back("string_value");
    return props;
}

HashMap<StringName, String> HNInputString::get_editable_properties_names() const {
    return HashMap<StringName, String>();
}