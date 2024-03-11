#ifndef HOODIE_HNINPUTINTEGER_H
#define HOODIE_HNINPUTINTEGER_H

#include "hoodie_node.h"

namespace godot
{

class HNInputInteger : public HoodieNode {
    GDCLASS(HNInputInteger, HoodieNode)

private:
    // Input
    int int_val = 1;
    // Output
    Array value_arr;

public:
    void set_int_value(const int p_value);
    int get_int_value() const;

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

    const Variant get_output(int p_port) const override;
};
    
} // namespace godot


#endif // HOODIE_HNINPUTINTEGER_H