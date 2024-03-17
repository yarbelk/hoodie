#ifndef HOODIE_HNDECOMPOSEMESH_H
#define HOODIE_HNDECOMPOSEMESH_H

#include "hoodie_node.h"

namespace godot
{

class HNDecomposeMesh : public HoodieNode {
    GDCLASS(HNDecomposeMesh, HoodieNode)

private:
    // Input

    // Output
    Array arr_vertex;
    Array arr_normal;
    Array arr_tangent;
    Array arr_color;
    Array arr_tex_uv;
    Array arr_tex_uv2;
    Array arr_custom0;
    Array arr_custom1;
    Array arr_custom2;
    Array arr_custom3;
    Array arr_bones;
    Array arr_weights;
    Array arr_index;

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

#endif // HOODIE_HNDECOMPOSEMESH_H
