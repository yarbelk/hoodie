#include "hn_offset_curve_2d.h"

#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/classes/geometry2d.hpp>
#include "utils/geo_utils.h"

using namespace godot;

void HNOffsetCurve2D::set_polygon(const bool p_value) {
    polygon = p_value;
}

bool HNOffsetCurve2D::get_polygon() const {
    return polygon;
}

void HNOffsetCurve2D::set_xz(const bool p_value) {
    xz = p_value;
}

bool HNOffsetCurve2D::get_xz() const {
    return xz;
}

void HNOffsetCurve2D::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_polygon", "value"), &HNOffsetCurve2D::set_polygon);
    ClassDB::bind_method(D_METHOD("get_polygon"), &HNOffsetCurve2D::get_polygon);
    ClassDB::bind_method(D_METHOD("set_xz", "value"), &HNOffsetCurve2D::set_xz);
    ClassDB::bind_method(D_METHOD("get_xz"), &HNOffsetCurve2D::get_xz);

    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "Polygon", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NO_EDITOR), "set_polygon", "get_polygon");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "XZ", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NO_EDITOR), "set_xz", "get_xz");
}

void HNOffsetCurve2D::_process(const Array &p_inputs) {
    Ref<HoodieGeo> in_hgeo;
    double in_delta = 1.0;

    in_hgeo = p_inputs[0];

    {
        Array a = p_inputs[1];
        in_delta = a[0];
    }

    Geometry2D g2d;
    TypedArray<PackedVector2Array> offset;

    if (!get_polygon()) {
        offset = g2d.offset_polyline(GeoUtils::vec3_arr_to_vec2_arr(in_hgeo->points, get_xz()), in_delta, Geometry2D::JOIN_SQUARE, Geometry2D::END_ROUND);
    } else {
        offset = g2d.offset_polygon(GeoUtils::vec3_arr_to_vec2_arr(in_hgeo->points, get_xz()), in_delta);
    }

    PackedVector2Array offset_points;
    Vector<HoodieGeo::Primitive> primitives;

    int counter = 0;
    for (int i = 0; i < offset.size(); i++) {
        PackedVector2Array o = offset[i];
        offset_points.append_array(o);

        PackedInt32Array vertices;
        vertices.resize(o.size());

        for (int v = 0; v < o.size(); v++) {
            vertices[v] = counter++;
        }

        primitives.push_back(HoodieGeo::Primitive(vertices));
    }

    Ref<HoodieGeo> out_hgeo = HoodieGeo::create_reference(GeoUtils::vec2_arr_to_vec3_arr(offset_points, get_xz()), primitives);

    set_output(0, out_hgeo);
}

String HNOffsetCurve2D::get_caption() const {
    return "Offset Curve 2D";
}

int HNOffsetCurve2D::get_input_port_count() const {
    return 2;
}

HoodieNode::PortType HNOffsetCurve2D::get_input_port_type(int p_port) const {
    switch (p_port) {
        case 0:
            return PortType::PORT_TYPE_HGEO;
        case 1:
            return PortType::PORT_TYPE_SCALAR;
        default:
            return PortType::PORT_TYPE_SCALAR;
    }
}

String HNOffsetCurve2D::get_input_port_name(int p_port) const {
    switch (p_port) {
        case 0:
            return "HGeo";
        case 1:
            return "Offset";
        default:
            return "";
    }
}

int HNOffsetCurve2D::get_output_port_count() const {
    return 1;
}

HoodieNode::PortType HNOffsetCurve2D::get_output_port_type(int p_port) const {
    return PortType::PORT_TYPE_HGEO;
}

String HNOffsetCurve2D::get_output_port_name(int p_port) const {
    return "HGeo";
}

int HNOffsetCurve2D::get_property_input_count() const {
    return 2;
}

Variant::Type HNOffsetCurve2D::get_property_input_type(vec_size_t p_prop) const {
    return Variant::BOOL;
}

Variant HNOffsetCurve2D::get_property_input(vec_size_t p_port) const {
    switch (p_port) {
        case 0:
            return Variant(polygon);
        case 1:
            return Variant(xz);
        default:
            return Variant();
    }
}

void HNOffsetCurve2D::set_property_input(vec_size_t p_prop, Variant p_input) {
    xz = (bool)p_input;
}

Vector<StringName> HNOffsetCurve2D::get_editable_properties() const {
    Vector<StringName> props;
    props.push_back("Polygon");
    props.push_back("XZ");
    // TODO: VisualShaderNodeIntParameter::get_editable_properties()
    return props;
}

HashMap<StringName, String> HNOffsetCurve2D::get_editable_properties_names() const {
    return HashMap<StringName, String>();
}