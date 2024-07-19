#ifndef HOODIE_MESHUTILS_H
#define HOODIE_MESHUTILS_H

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/templates/vector.hpp>

namespace godot
{

class MeshUtils {
public:
static Array join_meshes(const Vector<Array> &p_meshes);
};
    
} // namespace godot


#endif // HOODIE_MESHUTILS_H