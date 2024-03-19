#include "hn_repeat_data.h"

using namespace godot;

void HNRepeatData::_process(const Array &p_inputs) {
    out_repeated.clear();

    if (p_inputs.size() == 0) {
        return;
    }

    Array inputs = p_inputs;

    Array in_data = inputs[0];
    Array in_count = inputs[1];

    int count = MAX(0, (int)in_count[0]);

    for (int i = 0; i < in_data.size(); i++) {
        for (int j = 0; j < count; j++) {
            out_repeated.push_back(in_data[i]);
        }
    }
}

String HNRepeatData::get_caption() const {
    return "Repeat Data";
}

int HNRepeatData::get_input_port_count() const {
    return 2;
}

HNRepeatData::PortType HNRepeatData::get_input_port_type(int p_port) const {
    switch (p_port) {
        case 0:
            return PortType::PORT_TYPE_DATA;
        case 1:
            return PortType::PORT_TYPE_SCALAR_UINT;
    }

    return PortType::PORT_TYPE_SCALAR;
}

String HNRepeatData::get_input_port_name(int p_port) const {
    switch (p_port) {
        case 0:
            return "Data";
        case 1:
            return "Count";
    }

    return "";
}

int HNRepeatData::get_output_port_count() const {
    return 1;
}

HNRepeatData::PortType HNRepeatData::get_output_port_type(int p_port) const {
    return PortType::PORT_TYPE_DATA;
}

String HNRepeatData::get_output_port_name(int p_port) const {
    return "Data";
}

const Variant HNRepeatData::get_output(int p_port) const {
    return Variant(out_repeated);
}