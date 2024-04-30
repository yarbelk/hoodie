#ifndef HOODIE_HNMESHLINE_H
#define HOODIE_HNMESHLINE_H

#include "hoodie_node.h"

namespace godot
{
    
class HNMeshLine : public HoodieNode {
    GDCLASS(HNMeshLine, HoodieNode)

public:
    static PackedVector3Array generate_line(const float p_length, const int p_subdivisions);

public:
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

#endif // HOODIE_HNMESHLINE_H