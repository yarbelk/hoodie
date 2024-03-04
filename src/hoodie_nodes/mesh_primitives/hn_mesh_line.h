#ifndef HOODIE_HNMESHLINE_H
#define HOODIE_HNMESHLINE_H

#include "hoodie_node.h"

namespace godot
{
    
class HNMeshLine : public HoodieNode {
    GDCLASS(HNMeshLine, HoodieNode)

private:
    // Input
    int count = 1;
    Vector3 start = Vector3(0,0,0);
    Vector3 offset = Vector3(1,0,0);
    // Output
    Array mesh_line;

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

#endif // HOODIE_HNMESHLINE_H