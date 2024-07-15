#include "hn_curve_sweep.h"

#include <godot_cpp/classes/array_mesh.hpp>
#include "utils/geo_utils.h"

using namespace godot;

void HNCurveSweep::set_flip(const bool p_value) {
    flip = p_value;
}

bool HNCurveSweep::get_flip() const {
    return flip;
}

void HNCurveSweep::set_u_distance(const bool p_value) {
    u_distance = p_value;
}

bool HNCurveSweep::get_u_distance() const {
    return u_distance;
}

void HNCurveSweep::set_v_distance(const bool p_value) {
    v_distance = p_value;
}

bool HNCurveSweep::get_v_distance() const {
    return v_distance;
}

void HNCurveSweep::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_flip", "value"), &HNCurveSweep::set_flip);
    ClassDB::bind_method(D_METHOD("get_flip"), &HNCurveSweep::get_flip);
    ClassDB::bind_method(D_METHOD("set_u_distance", "value"), &HNCurveSweep::set_u_distance);
    ClassDB::bind_method(D_METHOD("get_u_distance"), &HNCurveSweep::get_u_distance);
    ClassDB::bind_method(D_METHOD("set_v_distance", "value"), &HNCurveSweep::set_v_distance);
    ClassDB::bind_method(D_METHOD("get_v_distance"), &HNCurveSweep::get_v_distance);

    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "Flip", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NO_EDITOR), "set_flip", "get_flip");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "UDistance", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NO_EDITOR), "set_u_distance", "get_u_distance");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "VDistance", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NO_EDITOR), "set_v_distance", "get_v_distance");
}

void HNCurveSweep::_process(const Array &p_inputs) {
    Ref<HoodieGeo> curve = p_inputs[0];
    Ref<HoodieGeo> profile = p_inputs[1];
    bool closed = false;

    if (curve.is_null() || profile.is_null()) {
        return;
    }

    const int shape_size = profile->points.size();
    const int shape_verts_size = shape_size + (closed ? 1 : 0);
    const int path_size = curve->points.size();
    const int total_verts = shape_verts_size * path_size;
    const int total_indices = 2 * 3 * (path_size - 1) * (shape_verts_size - 1);

    // Check stuff.
    if (path_size <= 1) {
        UtilityFunctions::push_warning(get_class(), " node: Path has not enough points (needs at least 2).");
        return;
    }
    if (shape_size <= 1) {
        UtilityFunctions::push_warning(get_class(), " node: Shape has not enough points (needs at least 2).");
        return;
    }
    if (closed && (shape_size == 2)) {
        UtilityFunctions::push_warning(get_class(), " node: Shape has not enough points to be closed (needs at least 3).");
        return;
    }

    // Mesh values?
    PackedVector3Array vertices;
    PackedVector3Array normals;
    PackedFloat32Array tangents;
    PackedVector2Array uvs;
    PackedInt32Array indices;

    // Surface Arrays resize
    vertices.resize(total_verts);
    normals.resize(total_verts);
    tangents.resize(total_verts * 4);
    uvs.resize(total_verts);
    indices.resize(total_indices);

    PackedVector3Array curve_pos = curve->points;
    PackedVector3Array profile_pos = profile->points;

    PackedVector3Array curve_tan;
    PackedVector3Array curve_nor;
    PackedFloat32Array curve_tilt;

    if (curve.ptr()->attributes.has("T")) {
        curve_tan = curve.ptr()->attributes["T"];
    } else {
        curve_tan.resize(path_size);
        for (int i = 0; i < path_size - 1; i++) {
            curve_tan[i] = curve_pos[i + 1] - curve_pos[i];
        }
        // TODO: if the path is closed, the tangent should point towards the first point.
        curve_tan[path_size - 1] = curve_tan[path_size - 2];
    }

    if (curve.ptr()->attributes.has("N")) {
        curve_nor = curve.ptr()->attributes["N"];
    } else {
        curve_nor.resize(path_size);
        curve_nor.fill(Vector3(0.0, 1.0, 0.0));
    }

    if (curve.ptr()->attributes.has("Tilt")) {
        curve_tilt = curve.ptr()->attributes["Tilt"];
    } else {
        curve_tilt.resize(path_size);
        curve_tilt.fill(0.0);
    }

    // Shape Length
    float shape_length = 0;
    {
        Vector3 prev_pt = profile_pos[0];
        for (int j = 1; j < shape_verts_size; j++)
        {
            Vector3 pt = profile_pos[j%shape_size];
            shape_length += (pt - prev_pt).length();
            prev_pt = pt;
        }
    }

    // Will contain the quads resulting from the sweep.
    Vector<HoodieGeo::Primitive> out_primitives;

    // If there are no primitives just connect all the points in a chain.
    if (curve->primitives.size() == 0) {
        PackedInt32Array vertices;
        for (int i = 0; i < curve->points.size(); i++) {
            vertices.push_back(i);
        }
        curve->primitives.push_back(HoodieGeo::Primitive(vertices));
    }

    for (int i = 0; i < curve->primitives.size(); i++) {
        PackedInt32Array in_verts = curve->primitives[i].vertices;

        PackedVector3Array in_points;
        for (int v : in_verts) {
            in_points.push_back(curve_pos[v]);
        }

        // Calculate path progressive distance for UV U purpose.
        PackedFloat32Array u_distances = GeoUtils::progressive_path_distances(in_points);
        PackedFloat32Array v_distances = GeoUtils::progressive_path_distances(profile_pos);

        // Extrusion
        // Each quad is a primitive
        int triangle_index = 0;
        for (int j = 0; j < in_verts.size(); j++) {
            int p = in_verts[j];
            // Construct frame with vectors taken from the Curve3D and tilt.
            Transform3D frame;

            if (j == in_verts.size() - 1 && in_verts.size() > 1) {
                curve_tan[p] = curve_tan[in_verts[j - 1]];
            }

            frame = Transform3D(-curve_tan[p].cross(curve_nor[p]).normalized(), curve_nor[p], curve_tan[p], curve_pos[p]);
            frame.rotate_basis(frame.basis.get_column(2), curve_tilt[p]);

            // Populate arrays
            for (int s = 0; s < shape_verts_size; s++)
            {
                HoodieGeo::Primitive prim;
                PackedInt32Array prim_ids;
                prim_ids.resize(4);

                int index = p * shape_verts_size + s;
                vertices[index] = frame.xform(profile_pos[s]);
                normals[index] = curve_nor[p];

                float uv_u = get_u_distance() ? u_distances[j] : p;
                float uv_v = get_v_distance() ? v_distances[s] : s;
                uvs[index] = Vector2(uv_u, uv_v);
                
                if (j > in_verts.size() - 2) continue;
                if (s > shape_verts_size - 2) continue;

                int id = p * shape_verts_size + s;

                if (flip) {
                    prim_ids[0] = id;
                    prim_ids[1] = id + 1;
                    prim_ids[2] = id + shape_verts_size;
                    prim_ids[3] = id + shape_verts_size + 1;
                } else {
                    prim_ids[0] = id + shape_verts_size + 1;
                    prim_ids[1] = id + 1;
                    prim_ids[2] = id + shape_verts_size;
                    prim_ids[3] = id;
                }

                prim.vertices = prim_ids;
                out_primitives.push_back(prim);
            }
        }
    }

    Ref<HoodieGeo> r_hgeo = HoodieGeo::create_reference(vertices, out_primitives);
    r_hgeo->attributes["N"] = normals;
    r_hgeo->attributes["UV"] = uvs;

    outputs[0] = r_hgeo;
}

String HNCurveSweep::get_caption() const {
    return "Curve Sweep";
}

int HNCurveSweep::get_input_port_count() const {
    return 3;
}

HoodieNode::PortType HNCurveSweep::get_input_port_type(int p_port) const {
    switch (p_port) {
        case 0:
            return PortType::PORT_TYPE_HGEO;
        case 1:
            return PortType::PORT_TYPE_HGEO;
        case 2:
            return PortType::PORT_TYPE_BOOLEAN;
        default:
            return PortType::PORT_TYPE_SCALAR;
    }
}

String HNCurveSweep::get_input_port_name(int p_port) const {
    switch (p_port) {
        case 0:
            return "Curve";
        case 1:
            return "Profile";
        case 2:
            return "Closed";
        default:
            return "";
    }
}

int HNCurveSweep::get_output_port_count() const {
    return 1;
}

HoodieNode::PortType HNCurveSweep::get_output_port_type(int p_port) const {
    return PortType::PORT_TYPE_HGEO;
}

String HNCurveSweep::get_output_port_name(int p_port) const {
    return "Geo";
}

int HNCurveSweep::get_property_input_count() const {
    return 2;
}

Variant::Type HNCurveSweep::get_property_input_type(vec_size_t p_prop) const {
    switch (p_prop) {
        case 0:
            return Variant::BOOL;
        case 1:
            return Variant::BOOL;
        case 2:
            return Variant::BOOL;
        default:
            return Variant::BOOL;
    }
}

Variant HNCurveSweep::get_property_input(vec_size_t p_port) const {
    switch (p_port) {
        case 0:
            return Variant(flip);
        case 1:
            return Variant(u_distance);
        case 2:
            return Variant(v_distance);
        default:
            return Variant();
    }
}

void HNCurveSweep::set_property_input(vec_size_t p_prop, Variant p_input) {
    switch (p_prop)
    {
        case 0:
            flip = (bool)p_input;
            break;
        case 1:
            u_distance = (bool)p_input;
            break;
        case 2:
            v_distance = (bool)p_input;
            break;
        default:
            break;
    }
}

Vector<StringName> HNCurveSweep::get_editable_properties() const {
    Vector<StringName> props;
    props.push_back("Flip");
    props.push_back("UDistance");
    props.push_back("VDistance");
    // TODO: VisualShaderNodeIntParameter::get_editable_properties()
    return props;
}

HashMap<StringName, String> HNCurveSweep::get_editable_properties_names() const {
    return HashMap<StringName, String>();
}