#ifndef HOODIE_HNMESHGRID_H
#define HOODIE_HNMESHGRID_H

#include "hoodie_node.h"

namespace godot
{
    
class HNMeshGrid : public HoodieNode {
    GDCLASS(HNMeshGrid, HoodieNode)

private:
    Array surface_arr;

public:
    static Array generate_plane(const float x_length, const float y_length, const int x_subs, const int y_subs, const Transform3D frame, const int id_offset = 0);

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

#endif // HOODIE_HNMESHGRID_H