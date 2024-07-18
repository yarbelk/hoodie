#ifndef HOODIE_HNHGEOEXPRESSION_H
#define HOODIE_HNHGEOEXPRESSION_H

#include "hoodie_node.h"

namespace godot
{

class HNHoodieGeoVectorExpression : public HoodieNode {
    GDCLASS(HNHoodieGeoVectorExpression, HoodieNode)

public:
    enum Target {
        Points,
        PackedPoints,
    };

private:
    // Input
    String filter_expression = "";
    String expression = "";
    Target target = Points;

public:
    void set_filter_expression(const String p_value);
    String get_filter_expression() const;
    void set_expression(const String p_value);
    String get_expression() const;
    void set_target(const Target p_value);
    Target get_target() const;

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
};

} // namespace godot

VARIANT_ENUM_CAST(HNHoodieGeoVectorExpression::Target);

#endif // HOODIE_HNHGEOEXPRESSION_H