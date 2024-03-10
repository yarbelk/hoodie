#include "hn_input_integer.h"

using namespace godot;

void HNInputInteger::_process(const Array &p_inputs) {
    UtilityFunctions::print("HNInputInteger _process() call.");

    int x = int_val;

    value_arr.clear();
    value_arr.push_back(x);
}

String HNInputInteger::get_caption() const {
    return "Value";
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

const Variant HNInputInteger::get_output(int p_port) const {
    if (p_port == 0) {
        return Variant(value_arr);
    }

    return Variant();
}