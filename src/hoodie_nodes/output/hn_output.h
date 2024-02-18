#ifndef HOODIE_HNOUTPUT_H
#define HOODIE_HNOUTPUT_H

#include "hoodie_node.h"

namespace godot
{
    
class HNOutput : public HoodieNode {
    GDCLASS(HNOutput, HoodieNode)
public:
    virtual void construct_property();
    virtual void construct_sockets();
};

} // namespace godot

#endif // HOODIE_HNOUTPUT_H