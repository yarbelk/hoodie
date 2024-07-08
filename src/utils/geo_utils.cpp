#include "geo_utils.h"

using namespace godot;

float GeoUtils::point_segment_distance(const Vector3 &p, const Vector3 &a, const Vector3 &b) {
    // https://paulbourke.net/geometry/pointlineplane/

    if (b - a == Vector3(0, 0, 0)) {
        return (a - p).length();
    }

    float u = ((p.x - a.x) * (b.x - a.x) + (p.y - a.y) * (b.y - a.y) + (p.z - a.z) * (b.z - a.z)) / (b - a).length_squared();

    if (u < 0) {
        return (a - p).length();
    } else if (u > 1) {
        return (b - p).length();
    }

    Vector3 intersection = a + u * (b - a);

    return (intersection - p).length();
}

PackedFloat32Array GeoUtils::progressive_path_distances(const PackedVector3Array &p_points) {
    PackedFloat32Array distances;
    distances.resize(p_points.size());

    float dist = 0;
    Vector3 prev_pt = p_points[0];

    for (int j = 1; j < distances.size(); j++) {
        dist += (p_points[j] - prev_pt).length();
        distances[j] = dist;
        prev_pt = p_points[j];
    }

    return distances;
}

Vector3 GeoUtils::vec2_to_vec3(const Vector2 &p_vec2, const bool p_xz) {
    Vector3 ret;

    if (!p_xz) {
        ret = Vector3(p_vec2.x, p_vec2.y, 0);
    } else {
        ret = Vector3(p_vec2.x, 0, p_vec2.y);
    }

    return ret;
}

PackedVector3Array GeoUtils::vec2_arr_to_vec3_arr(const PackedVector2Array &p_vec2_arr, const bool p_xz) {
    PackedVector3Array ret;
    ret.resize(p_vec2_arr.size());

    for (int i = 0; i < p_vec2_arr.size(); i++) {
        ret[i] = vec2_to_vec3(p_vec2_arr[i], p_xz);
    }

    return ret;
}

Vector2 GeoUtils::vec3_to_vec2(const Vector3 &p_vec3, const bool p_xz = false) {
    Vector2 ret;

    if (!p_xz) {
        ret = Vector2(p_vec3.x, p_vec3.y);
    } else {
        ret = Vector2(p_vec3.x, p_vec3.z);
    }

    return ret;
}

PackedVector2Array GeoUtils::vec3_arr_to_vec2_arr(const PackedVector3Array &p_vec3_arr, const bool p_xz = false) {
    PackedVector2Array ret;
    ret.resize(p_vec3_arr.size());

    for (int i = 0; i < p_vec3_arr.size(); i++) {
        ret[i] = vec3_to_vec2(p_vec3_arr[i], p_xz);
    }

    return ret;
}