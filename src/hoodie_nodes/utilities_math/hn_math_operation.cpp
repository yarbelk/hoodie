#include "hn_math_operation.h"

#include <functional>
#include <godot_cpp/classes/array_mesh.hpp>

using namespace godot;

void HNMathOperation::set_operation(const Operation p_value) {
    operation = p_value;
}

HNMathOperation::Operation HNMathOperation::get_operation() const {
    return operation;
}

void HNMathOperation::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_operation", "value"), &HNMathOperation::set_operation);
    ClassDB::bind_method(D_METHOD("get_operation"), &HNMathOperation::get_operation);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "Operation", PROPERTY_HINT_ENUM, "Sum,Subtract,Multiply,Divide", PROPERTY_USAGE_NO_EDITOR), "set_operation", "get_operation");

    BIND_ENUM_CONSTANT(Operation::Sum);
    BIND_ENUM_CONSTANT(Operation::Subtract);
    BIND_ENUM_CONSTANT(Operation::Multiply);
    BIND_ENUM_CONSTANT(Operation::Divide);
}

void HNMathOperation::_process(const Array &p_inputs) {
    PackedFloat32Array in_1 = p_inputs[0];
    PackedFloat32Array in_2 = p_inputs[1];

    if (in_1.size() < 1) {
        in_1.push_back(0);
    }

    if (in_2.size() < 1) {
        in_2.push_back(0);
    }

    const int count = Math::max(in_1.size(), in_2.size());

    while (in_1.size() < count) {
        in_1.push_back(in_1[in_1.size() - 1]);
    }

    while (in_2.size() < count) {
        in_2.push_back(in_2[in_2.size() - 1]);
    }

    bool no_divide = false;
    for (int i = 0; i < count; i++) {
        float f_2 = in_2[i];
        if (f_2 == 0) {
            no_divide = true;
        }
    }

    std::function<float(float, float)> op;

    switch(operation) {
        case Sum:
            op = [] (float f_1, float f_2) { return f_1 + f_2; };
            break;
        case Subtract:
            op = [] (float f_1, float f_2) { return f_1 - f_2; };
            break;
        case Multiply:
            op = [] (float f_1, float f_2) { return f_1 * f_2; };
            break;
        case Divide:
            if (no_divide) { return; }
            op = [] (float f_1, float f_2) { return f_1 / f_2; };
            break;
    }

    PackedFloat32Array out_value;
    out_value.resize(count);

    for (int i = 0; i < count; i++) {
        out_value[i] = op(in_1[i], in_2[i]);
    }

    set_output(0, out_value);
}

String HNMathOperation::get_caption() const {
    return "Math Operation";
}

int HNMathOperation::get_input_port_count() const {
    return 2;
}

HoodieNode::PortType HNMathOperation::get_input_port_type(int p_port) const {
    switch (p_port) {
        case 0:
            return PortType::PORT_TYPE_SCALAR;
        case 1:
            return PortType::PORT_TYPE_SCALAR;
        default:
            return PortType::PORT_TYPE_SCALAR;
    }
}

String HNMathOperation::get_input_port_name(int p_port) const {
    switch (p_port) {
        case 0:
            return "Value";
        case 1:
            return "Value";
        default:
            return "";
    }
}

int HNMathOperation::get_output_port_count() const {
    return 1;
}

HoodieNode::PortType HNMathOperation::get_output_port_type(int p_port) const {
    return PortType::PORT_TYPE_SCALAR;
}

String HNMathOperation::get_output_port_name(int p_port) const {
    return "Value";
}

int HNMathOperation::get_property_input_count() const {
    return 1;
}

Variant::Type HNMathOperation::get_property_input_type(vec_size_t p_prop) const {
    return Variant::INT;
}

Variant HNMathOperation::get_property_input(vec_size_t p_port) const {
    return Variant(operation);
}

void HNMathOperation::set_property_input(vec_size_t p_prop, Variant p_input) {
    operation = (Operation)(int)p_input;
}

Vector<StringName> HNMathOperation::get_editable_properties() const {
    Vector<StringName> props;
    props.push_back("Operation");
    return props;
}

HashMap<StringName, String> HNMathOperation::get_editable_properties_names() const {
    return HashMap<StringName, String>();
}