#ifndef HOODIE_GEOUTILS_H
#define HOODIE_GEOUTILS_H

#include <godot_cpp/classes/resource.hpp>

namespace godot
{

class GeoUtils {
public:
static float point_segment_distance(const Vector3 &p, const Vector3 &a, const Vector3 &b);

static PackedFloat32Array progressive_path_distances(const PackedVector3Array &p_points);

static Vector3 vec2_to_vec3(const Vector2 &p_vec2, const bool p_xz);
static PackedVector3Array vec2_arr_to_vec3_arr(const PackedVector2Array &p_vec2_arr, const bool p_xz);

static Vector2 vec3_to_vec2(const Vector3 &p_vec3, const bool p_xz);
static PackedVector2Array vec3_arr_to_vec2_arr(const PackedVector3Array &p_vec3_arr, const bool p_xz);
};
    
} // namespace godot


#endif // HOODIE_GEOUTILS_H