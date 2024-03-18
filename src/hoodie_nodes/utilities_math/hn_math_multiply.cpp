#include "hn_math_multiply.h"

using namespace godot;

void HNMathMultiply::_process(const Array &p_inputs) {
    UtilityFunctions::print("Math Multiply _process() call.");

    multiplied_arr.clear();

    if (p_inputs.size() == 0) {
        return;
    }

    Array fac_0 = p_inputs[0];
    Array fac_1 = p_inputs[1];

    for (int i = 0; i < fac_0.size(); i++) {
        float safe_fac_1 = 1;
        if (i < fac_1.size()) {
            safe_fac_1 = fac_1[i];
        }
        multiplied_arr.push_back((float)fac_0[i] * safe_fac_1);
    }
}

String HNMathMultiply::get_caption() const {
    return "Math Multiply";
}

int HNMathMultiply::get_input_port_count() const {
    return 2;
}

HNMathMultiply::PortType HNMathMultiply::get_input_port_type(int p_port) const {
    switch (p_port) {
        case 0:
            return PortType::PORT_TYPE_SCALAR;
        case 1:
            return PortType::PORT_TYPE_SCALAR;
    }

    return PortType::PORT_TYPE_SCALAR;
}

String HNMathMultiply::get_input_port_name(int p_port) const {
    switch (p_port) {
        case 0:
            return "Value";
        case 1:
            return "Value";
    }

    return "Value";
}

int HNMathMultiply::get_output_port_count() const {
    return 1;
}

HNMathMultiply::PortType HNMathMultiply::get_output_port_type(int p_port) const {
    return PortType::PORT_TYPE_SCALAR;
}

String HNMathMultiply::get_output_port_name(int p_port) const {
    return "Value";
}

const Variant HNMathMultiply::get_output(int p_port) const {
    if (p_port == 0) {
        return Variant(multiplied_arr);
    }

    return Variant();
}