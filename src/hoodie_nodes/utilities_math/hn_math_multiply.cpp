#include "hn_math_multiply.h"

using namespace godot;

void HNMathMultiply::_process(const Array &p_inputs) {
    multiplied_arr.clear();

    if (p_inputs.size() == 0) {
        return;
    }

    Array fac_0 = p_inputs[0].duplicate();
    Array fac_1 = p_inputs[1].duplicate();

    while (fac_0.size() < fac_1.size()) {
        fac_0.push_back(fac_0[fac_0.size() - 1]);
    }

    while (fac_1.size() < fac_0.size()) {
        fac_1.push_back(fac_1[fac_1.size() - 1]);
    }

    for (int i = 0; i < fac_0.size(); i++) {
        const float a = (float)fac_0[i];
        const float b = (float)fac_1[i];
        multiplied_arr.push_back(a * b);
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