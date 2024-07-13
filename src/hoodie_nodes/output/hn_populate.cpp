#include "hn_populate.h"

#include <godot_cpp/classes/editor_interface.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include "utils/geo_utils.h"

using namespace godot;

void HNPopulate::set_group_name(const String p_value) {
    group_name = p_value;
}

String HNPopulate::get_group_name() const {
    return group_name;
}

void HNPopulate::set_resource(const Ref<PackedScene> p_value) {
    scene = p_value;
}

Ref<PackedScene> HNPopulate::get_resource() const {
    return scene;
}

void HNPopulate::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_group_name", "value"), &HNPopulate::set_group_name);
    ClassDB::bind_method(D_METHOD("get_group_name"), &HNPopulate::get_group_name);
    ClassDB::bind_method(D_METHOD("set_resource", "value"), &HNPopulate::set_resource);
    ClassDB::bind_method(D_METHOD("get_resource"), &HNPopulate::get_resource);

    ADD_PROPERTY(PropertyInfo(Variant::STRING, "GroupName", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NO_EDITOR), "set_group_name", "get_group_name");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Scene", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NO_EDITOR), "set_resource", "get_resource");
}

void HNPopulate::_process(const Array &p_inputs) {
    Node* scene_root = EditorInterface::get_singleton()->get_edited_scene_root();

    if (scene.is_null()) { return; }
    if (group_name.is_empty()) { return; }

    TypedArray<Node> children = scene_root->get_children();

    Node3D *group_node = nullptr;
    for (int i = 0; i < children.size(); i++) {
        Node3D *child = Object::cast_to<Node3D>(children[i]);
        if (child->get_name() == group_name) {
            group_node = child;
            break;
        }
    }

    if (group_node == nullptr) {
        group_node = memnew(Node3D);
        group_node->set_name(group_name);
        scene_root->add_child(group_node);
        group_node->set_owner(scene_root);
    }

    // Clear group children.
    TypedArray<Node> group_children = group_node->get_children();
    for (int i = 0; i < group_children.size(); i++) {
        Node3D *group_child = Object::cast_to<Node3D>(group_children[i]);
        group_child->queue_free();
    }

    PackedVector3Array in_positions = p_inputs[0];
    PackedVector3Array in_rotations = p_inputs[1];
    PackedVector3Array in_scales = p_inputs[2];

    const int count = Math::max(Math::max(in_positions.size(), in_rotations.size()), in_scales.size());

    for (int i = 0; i < count; i++) {
        Vector3 pos = Vector3(0, 0, 0);
        Vector3 rot = Vector3(0, 0, 0);
        Vector3 scale = Vector3(1, 1, 1);

        if (in_positions.size() > i) {
            pos = in_positions[i];
        } else {
            pos = in_positions[in_positions.size() - 1];
        }

        if (in_rotations.size() > i) {
            rot = in_rotations[i];
        } else {
            rot = in_rotations[in_rotations.size() - 1];
        }

        if (in_scales.size() > i) {
            scale = in_scales[i];
        } else {
            scale = in_scales[in_scales.size() - 1];
        }

        Node3D *instanced_scene = Object::cast_to<Node3D>(scene->instantiate());
        instanced_scene->set_name(itos(i));
        instanced_scene->set_position(pos);
        instanced_scene->set_rotation(rot);
        instanced_scene->set_scale(scale);

        group_node->add_child(instanced_scene);
        instanced_scene->set_owner(scene_root);
    }
}

String HNPopulate::get_caption() const {
    return "Populate";
}

int HNPopulate::get_input_port_count() const {
    return 3;
}

HoodieNode::PortType HNPopulate::get_input_port_type(int p_port) const {
    switch (p_port) {
        case 0:
            return PortType::PORT_TYPE_VECTOR_3D;
        case 1:
            return PortType::PORT_TYPE_VECTOR_3D;
        case 2:
            return PortType::PORT_TYPE_VECTOR_3D;
        default:
            return PortType::PORT_TYPE_SCALAR;
    }
}

String HNPopulate::get_input_port_name(int p_port) const {
    switch (p_port) {
        case 0:
            return "Positions";
        case 1:
            return "Rotations";
        case 2:
            return "Scales";
        default:
            return "";
    }
}

int HNPopulate::get_output_port_count() const {
    return 0;
}

HoodieNode::PortType HNPopulate::get_output_port_type(int p_port) const {
    return PortType::PORT_TYPE_DATA;
}

String HNPopulate::get_output_port_name(int p_port) const {
    return "Data";
}

int HNPopulate::get_property_input_count() const {
    return 2;
}

Variant::Type HNPopulate::get_property_input_type(vec_size_t p_prop) const {
    switch (p_prop) {
        case 0:
            return Variant::STRING;
        case 1:
            return Variant::OBJECT;
        default:
            return Variant::BOOL;
    }
}

Variant HNPopulate::get_property_input(vec_size_t p_port) const {
    switch (p_port) {
        case 0:
            return Variant(group_name);
        case 1:
            return Variant(scene);
        default:
            return Variant();
    }
}

void HNPopulate::set_property_input(vec_size_t p_prop, Variant p_input) {
    switch (p_prop)
    {
        case 0:
            group_name = p_input;
            break;
        case 1:
            scene = p_input;
            break;
        default:
            break;
    }
}

Vector<StringName> HNPopulate::get_editable_properties() const {
    Vector<StringName> props;
    props.push_back("GroupName");
    props.push_back("Scene");
    return props;
}

HashMap<StringName, String> HNPopulate::get_editable_properties_names() const {
    return HashMap<StringName, String>();
}