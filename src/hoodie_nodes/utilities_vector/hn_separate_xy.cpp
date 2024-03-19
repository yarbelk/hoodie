#include "hn_separate_xy.h"

using namespace godot;

void HNSeparateXY::_process(const Array &p_inputs) {
    out_x.clear();
    out_y.clear();

    if (p_inputs.size() == 0) {
        return;
    }

    Array in_arr = p_inputs;

    Array in_arr_vectors = in_arr[0];

    if (in_arr_vectors.size() == 0) {
        return;
    }

    for (int i = 0; i < in_arr_vectors.size(); i++) {
        Vector2 in_vec = (Vector2)in_arr_vectors[i];

        out_x.push_back(in_vec.x);
        out_y.push_back(in_vec.y);
    }
}

String HNSeparateXY::get_caption() const {
    return "Separate XY";
}

int HNSeparateXY::get_input_port_count() const {
    return 1;
}

HNSeparateXY::PortType HNSeparateXY::get_input_port_type(int p_port) const {
    return PortType::PORT_TYPE_VECTOR_2D;
}

String HNSeparateXY::get_input_port_name(int p_port) const {
    return "Vector2D";
}

int HNSeparateXY::get_output_port_count() const {
    return 2;
}

HNSeparateXY::PortType HNSeparateXY::get_output_port_type(int p_port) const {
    switch (p_port) {
        case 0:
            return PortType::PORT_TYPE_SCALAR;
        case 1:
            return PortType::PORT_TYPE_SCALAR;
    }

    return PortType::PORT_TYPE_SCALAR;
}

String HNSeparateXY::get_output_port_name(int p_port) const {
    switch (p_port) {
        case 0:
            return "X";
        case 1:
            return "Y";
    }

    return "";
}

const Variant HNSeparateXY::get_output(int p_port) const {
    switch (p_port) {
        case 0:
            return Variant(out_x);
        case 1:
            return Variant(out_y);
    }

    return Variant();
}