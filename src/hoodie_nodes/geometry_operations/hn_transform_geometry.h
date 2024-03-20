#ifndef HOODIE_HNTRANSFORMGEOMETRY_H
#define HOODIE_HNTRANSFORMGEOMETRY_H

#include "hoodie_node.h"

namespace godot
{

class HNTransformGeometry : public HoodieNode {
    GDCLASS(HNTransformGeometry, HoodieNode)

private:
    // Input

    // Output
    Array out;

public:
    static Quaternion from_euler(const Vector3 &p_euler);

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

#endif // HOODIE_HNTRANSFORMGEOMETRY_H
