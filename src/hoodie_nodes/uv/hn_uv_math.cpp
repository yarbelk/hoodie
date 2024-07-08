#include "hn_uv_math.h"

#include <functional>
#include <godot_cpp/classes/array_mesh.hpp>

using namespace godot;

void HNUVMath::set_operation(const Operation p_value) {
    operation = p_value;
}

HNUVMath::Operation HNUVMath::get_operation() const {
    return operation;
}

void HNUVMath::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_operation", "value"), &HNUVMath::set_operation);
    ClassDB::bind_method(D_METHOD("get_operation"), &HNUVMath::get_operation);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "Operation", PROPERTY_HINT_ENUM, "Sum,Subtract,Multiply,Divide", PROPERTY_USAGE_NO_EDITOR), "set_operation", "get_operation");

    BIND_ENUM_CONSTANT(Operation::Sum);
    BIND_ENUM_CONSTANT(Operation::Subtract);
    BIND_ENUM_CONSTANT(Operation::Multiply);
    BIND_ENUM_CONSTANT(Operation::Divide);
}

void HNUVMath::_process(const Array &p_inputs) {
    Ref<HoodieGeo> in_hgeo = p_inputs[0];
    PackedVector2Array in_values = p_inputs[1].duplicate();

    PackedVector2Array uvs;

    if (in_hgeo->attributes.has("UV")) {
        uvs = in_hgeo->attributes["UV"].duplicate();
    } else {
        return;
    }

    const int count = in_hgeo->attributes["UV"].size();

    Vector2 last_val = in_values[in_values.size() - 1];
    while (in_values.size() < count) {
        in_values.push_back(last_val);
    }

    bool no_divide = false;
    for (int i = 0; i < count; i++) {
        Vector2 vec = in_values[i];
        if (vec.x == 0 || vec.y == 0) {
            no_divide = true;
        }
    }

    std::function<Vector2(Vector2, Vector2)> op;

    switch(operation) {
        case Sum:
            op = [] (Vector2 vec1, Vector2 vec2) { return vec1 + vec2; };
            break;
        case Subtract:
            op = [] (Vector2 vec1, Vector2 vec2) { return vec1 - vec2; };
            break;
        case Multiply:
            op = [] (Vector2 vec1, Vector2 vec2) { return Vector2(vec1.x * vec2.x, vec1.y * vec2.y); };
            break;
        case Divide:
            if (no_divide) return;
            op = [] (Vector2 vec1, Vector2 vec2) { return Vector2(vec1.x / vec2.x, vec1.y / vec2.y); };
            break;
    }

    for (int i = 0; i < count; i++) {
        uvs[i] = op(uvs[i], in_values[i]);
    }

    Ref<HoodieGeo> out_hgeo = HoodieGeo::create_reference(in_hgeo->points.duplicate(), in_hgeo->primitives.duplicate());
    out_hgeo->attributes = in_hgeo->attributes;
    out_hgeo->attributes["UV"] = uvs;

    set_output(0, out_hgeo);
}

String HNUVMath::get_caption() const {
    return "UV Math";
}

int HNUVMath::get_input_port_count() const {
    return 2;
}

HoodieNode::PortType HNUVMath::get_input_port_type(int p_port) const {
    switch (p_port) {
        case 0:
            return PortType::PORT_TYPE_HGEO;
        case 1:
            return PortType::PORT_TYPE_VECTOR_2D;
        default:
            return PortType::PORT_TYPE_SCALAR;
    }
}

String HNUVMath::get_input_port_name(int p_port) const {
    switch (p_port) {
        case 0:
            return "HGeo";
        case 1:
            return "Value";
        default:
            return "";
    }
}

int HNUVMath::get_output_port_count() const {
    return 1;
}

HoodieNode::PortType HNUVMath::get_output_port_type(int p_port) const {
    return PortType::PORT_TYPE_HGEO;
}

String HNUVMath::get_output_port_name(int p_port) const {
    return "HGeo";
}

int HNUVMath::get_property_input_count() const {
    return 1;
}

Variant::Type HNUVMath::get_property_input_type(vec_size_t p_prop) const {
    return Variant::INT;
}

Variant HNUVMath::get_property_input(vec_size_t p_port) const {
    return Variant(operation);
}

void HNUVMath::set_property_input(vec_size_t p_prop, Variant p_input) {
    operation = (Operation)(int)p_input;
}

Vector<StringName> HNUVMath::get_editable_properties() const {
    Vector<StringName> props;
    props.push_back("Operation");
    return props;
}

HashMap<StringName, String> HNUVMath::get_editable_properties_names() const {
    return HashMap<StringName, String>();
}