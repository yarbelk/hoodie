#ifndef HOODIE_HNDECOMPOSECURVE_H
#define HOODIE_HNDECOMPOSECURVE_H

#include "hoodie_node.h"

namespace godot
{

class HNDecomposeCurve : public HoodieNode {
    GDCLASS(HNDecomposeCurve, HoodieNode)

private:
    // Input

    // Output
    Array out_points;
    Array out_tangents;
    Array out_normals;
    Array out_tilts;
    Array out_lengths;
    Array out_factors;

public:

protected:
    // static void _bind_methods();

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

}

#endif // HOODIE_HNDECOMPOSECURVE_H
