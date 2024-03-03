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

void HoodieNode::set_property(const Property &p_property) {
    property = p_property;
}

Variant::Type HoodieNode::get_property_type() const {
    return property.type;
}

String HoodieNode::get_property_hint() const {
    return property.hint;
}

void HoodieNode::construct_property() {
}

void HoodieNode::_bind_methods() {
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
    UtilityFunctions::print("Base HoodieNode _process() call.");
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

const Variant HoodieNode::get_output(int p_port) const {
    return Variant();
}

HoodieNode::HoodieNode() {
}
