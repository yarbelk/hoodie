#ifndef HOODIE_HNMESHGRID_H
#define HOODIE_HNMESHGRID_H

#include "hoodienode.h"

namespace godot
{
    
class HNMeshGrid : public HoodieNode {
    GDCLASS(HNMeshGrid, HoodieNode)
public:
    virtual void construct_node_info();
    virtual void construct_property();
    virtual void construct_sockets();
};

} // namespace godot

#endif // HOODIE_HNMESHGRID_H