#ifndef HOODIE_HNCURVETOPOINTS_H
#define HOODIE_HNCURVETOPOINTS_H

#include "hoodie_node.h"

namespace godot
{

class HNCurveToPoints : public HoodieNode {
    GDCLASS(HNCurveToPoints, HoodieNode)

private:
    // Input

    // Output
    PackedVector3Array points;
    PackedVector3Array tangents;
    PackedVector3Array normals;
    PackedFloat32Array tilts;

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


#endif // HOODIE_HNCURVETOPOINTS_H