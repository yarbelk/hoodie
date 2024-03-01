#ifndef HOODIE_HNINPUTCURVE3D_H
#define HOODIE_HNINPUTCURVE3D_H

#include "hoodie_node.h"

namespace godot
{
    
class HNInputCurve3D : public HoodieNode {
    GDCLASS(HNInputCurve3D, HoodieNode)

public:
	// bool update(bool p_inputs_updated, const Array &p_inputs) override;

	void _process(const Array &p_inputs) override;

    String get_caption() const override;

    int get_input_port_count() const override;
	PortType get_input_port_type(int p_port) const override;
	String get_input_port_name(int p_port) const override;

    int get_output_port_count() const override;
	PortType get_output_port_type(int p_port) const override;
	String get_output_port_name(int p_port) const override;
};

} // namespace godot

#endif // HOODIE_HNINPUTCURVE3D_H