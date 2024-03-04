#include "hn_input_value.h"

using namespace godot;

void HNInputValue::_process(const Array &p_inputs) {
    UtilityFunctions::print("HNInputValue _process() call.");

    // float x = 20.0;
    float x = float_val;

    value_arr.clear();
    value_arr.push_back(x);
}

String HNInputValue::get_caption() const {
    return "Value";
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

void HNInputValue::set_property_input(vec_size_t p_prop, Variant &p_input) {
    float_val = (float)p_input;
}

const Variant HNInputValue::get_output(int p_port) const {
    if (p_port == 0) {
        return Variant(value_arr);
    }

    return Variant();
}