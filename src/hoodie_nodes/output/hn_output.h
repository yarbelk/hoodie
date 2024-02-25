#ifndef HOODIE_HNOUTPUT_H
#define HOODIE_HNOUTPUT_H

#include "hoodie_node.h"

namespace godot
{
    
class HNOutput : public HoodieNode {
    GDCLASS(HNOutput, HoodieNode)
public:
    int get_input_port_count() const override;
	PortType get_input_port_type(int p_port) const override;
	String get_input_port_name(int p_port) const override;

    int get_output_port_count() const override;
	PortType get_output_port_type(int p_port) const override;
	String get_output_port_name(int p_port) const override;
};

} // namespace godot

#endif // HOODIE_HNOUTPUT_H