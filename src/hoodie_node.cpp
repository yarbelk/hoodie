#include "hoodie_node.h"

#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void HoodieNode::mark_dirty() {
    dirty = true;
    // TODO: emit_changed?
}

void HoodieNode::set_status(const ProcessStatus &p_status) {
    status = p_status;
}

HoodieNode::ProcessStatus HoodieNode::get_status() const {
    return status;
}

// TODO: delete this
/* void HoodieNode::set_property(const Property &p_property) {
    property = p_property;
}

Variant::Type HoodieNode::get_property_type() const {
    return property.type;
}

String HoodieNode::get_property_hint() const {
    return property.hint;
}

void HoodieNode::construct_property() {
} */

void HoodieNode::_bind_methods() {
    ClassDB::bind_method(D_METHOD("mark_dirty"), &HoodieNode::mark_dirty);
    ClassDB::bind_method(D_METHOD("set_property_input", "id", "value"), &HoodieNode::set_property_input);
}

bool HoodieNode::update(bool p_inputs_updated, const Array &p_inputs) {
    bool updated = dirty || p_inputs_updated;
    dirty = false;

    if (updated) {
        _process(p_inputs);
    }

    return updated;
}

void HoodieNode::_process(const Array &p_inputs) {
}

String HoodieNode::get_caption() const {
    return "Hoodie Node";
}

int HoodieNode::get_input_port_count() const {
    return 0;
}

HoodieNode::PortType HoodieNode::get_input_port_type(int p_port) const {
    return PortType::PORT_TYPE_SCALAR;
}

String HoodieNode::get_input_port_name(int p_port) const {
    return "";
}

int HoodieNode::get_output_port_count() const {
    return 0;
}

HoodieNode::PortType HoodieNode::get_output_port_type(int p_port) const {
    return PortType::PORT_TYPE_SCALAR;
}

String HoodieNode::get_output_port_name(int p_port) const {
    return "";
}

int HoodieNode::get_property_input_count() const {
    return 0;
}

Variant::Type HoodieNode::get_property_input_type(vec_size_t p_prop) const {
    return Variant::NIL;
}

String HoodieNode::get_property_input_hint(vec_size_t p_prop) const {
    return "";
}

Variant HoodieNode::get_property_input(vec_size_t p_port) const {
    return Variant();
}

void HoodieNode::set_property_input(vec_size_t p_prop, Variant p_input) {
}

Vector<StringName> HoodieNode::get_editable_properties() const {
    return Vector<StringName>();
}

HashMap<StringName, String> HoodieNode::get_editable_properties_names() const {
    return HashMap<StringName, String>();
}

const Variant HoodieNode::get_output(int p_port) const {
    return Variant();
}

bool HoodieNode::is_output_port_connected(vec_size_t p_port) const {
    if (connected_output_ports.has(p_port)) {
        return connected_output_ports[p_port];
    }
    return false;
}

void HoodieNode::set_output_port_connected(vec_size_t p_port, bool p_connected) {
    connected_output_ports[p_port] = p_connected;
}

bool HoodieNode::is_input_port_connected(vec_size_t p_port) const {
    if (connected_input_ports.has(p_port)) {
        return connected_input_ports[p_port];
    }
    return false;
}

void HoodieNode::set_input_port_connected(vec_size_t p_port, bool p_connected) {
    connected_input_ports[p_port] = p_connected;
}

HoodieNode::HoodieNode() {
}
