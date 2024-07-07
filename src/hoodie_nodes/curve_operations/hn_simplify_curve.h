#ifndef HOODIE_HNSIMPLIFYCURVE_H
#define HOODIE_HNSIMPLIFYCURVE_H

#include "hoodie_node.h"

namespace godot
{

class HNSimplifyCurve : public HoodieNode {
    GDCLASS(HNSimplifyCurve, HoodieNode)

public:
    enum Algorithm {
        Douglas_Peucker
    };

private:
    // Input
    Algorithm algorithm = Douglas_Peucker;

public:
    void set_algorithm(const Algorithm p_value);
    Algorithm get_algorithm() const;

protected:
    static void _bind_methods();

public:
    static PackedVector3Array DouglasPeucker(const PackedVector3Array &p_points, const float epsilon);

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

VARIANT_ENUM_CAST(HNSimplifyCurve::Algorithm);

#endif // HOODIE_HNSIMPLIFYCURVE_H