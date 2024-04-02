#ifndef HOODIE_HNMATHNOISEREDUCTION_H
#define HOODIE_HNMATHNOISEREDUCTION_H

#include "hoodie_node.h"

namespace godot
{
    
class HNMathNoiseReduction : public HoodieNode {
    GDCLASS(HNMathNoiseReduction, HoodieNode)

private:
    // Input

    // Output
    Array out;

public:
	void _process(const Array &p_inputs) override;

    String get_caption() const override;

    int get_input_port_count() const override;
	PortType get_input_port_type(int p_port) const override;
	String get_input_port_name(int p_port) const override;

    int get_output_port_count() const override;
	PortType get_output_port_type(int p_port) const override;
	String get_output_port_name(int p_port) const override;

    const Variant get_output(int p_port) const override;
};

} // namespace godot

#endif // HOODIE_HNMATHNOISEREDUCTION_H
