#ifndef HOODIE_HNMESHGRID_H
#define HOODIE_HNMESHGRID_H

#include "hoodie_node.h"

namespace godot
{
    
class HNMeshGrid : public HoodieNode {
    GDCLASS(HNMeshGrid, HoodieNode)
public:
    int get_input_port_count() const override;
	PortType get_input_port_type(int p_port) const override;
	String get_input_port_name(int p_port) const override;

    int get_output_port_count() const override;
	PortType get_output_port_type(int p_port) const override;
	String get_output_port_name(int p_port) const override;
};

} // namespace godot

#endif // HOODIE_HNMESHGRID_H