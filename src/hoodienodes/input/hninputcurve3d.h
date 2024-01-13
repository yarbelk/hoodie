#ifndef HOODIE_HNINPUTCURVE3D_H
#define HOODIE_HNINPUTCURVE3D_H

#include "hoodienode.h"

namespace godot
{
    
class HNInputCurve3D : public HoodieNode {
    GDCLASS(HNInputCurve3D, HoodieNode)
public:
    virtual void construct_node_info();
    virtual void construct_property();
    virtual void construct_sockets();
};

} // namespace godot

#endif // HOODIE_HNINPUTCURVE3D_H