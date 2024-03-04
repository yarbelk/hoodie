#ifndef HOODIE_HNINPUTCURVE3D_H
#define HOODIE_HNINPUTCURVE3D_H

#include "hoodie_node.h"

#include <godot_cpp/classes/curve3d.hpp>

namespace godot
{
    
class HNInputCurve3D : public HoodieNode {
    GDCLASS(HNInputCurve3D, HoodieNode)

private:
	Ref<Curve3D> curve;
	Array packed_curve;

	void _curve_changed();

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
    String get_property_input_hint(vec_size_t p_prop) const override;
    Variant get_property_input(vec_size_t p_port) const override;
    void set_property_input(vec_size_t p_prop, Variant p_input) override;

    const Variant get_output(int p_port) const override;
};

} // namespace godot

#endif // HOODIE_HNINPUTCURVE3D_H