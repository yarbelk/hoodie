#ifndef HOODIE_HNPOPULATE_H
#define HOODIE_HNPOPULATE_H

#include "hoodie_node.h"

#include <godot_cpp/classes/packed_scene.hpp>

namespace godot
{

class HNPopulate : public HoodieNode {
    GDCLASS(HNPopulate, HoodieNode)

private:
    // Input
    String group_name;
    Ref<PackedScene> scene;

public:
    void set_group_name(const String p_value);
    String get_group_name() const;
    void set_resource(const Ref<PackedScene> p_value);
    Ref<PackedScene> get_resource() const;

protected:
    static void _bind_methods();

public:
    void _process(const Array &p_inputs) override;

    String get_caption() const override;

    int get_input_port_count() const override;
	PortType get_input_port_type(int p_port) const override;
	String get_input_port_name(int p_port) const override;

    int get_output_port_count() const override;
	PortType get_output_port_type(int p_port) const override;
	String get_output_port_name(int p_port) const override;

    int get_property_input_count() const override;
    Variant::Type get_property_input_type(vec_size_t p_prop) const override;
    Variant get_property_input(vec_size_t p_port) const override;
    void set_property_input(vec_size_t p_prop, Variant p_input) override;

    Vector<StringName> get_editable_properties() const override;
    HashMap<StringName, String> get_editable_properties_names() const override;

    bool has_button() const override;
};
    
} // namespace godot


#endif // HOODIE_HNPOPULATE_H