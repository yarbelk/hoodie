#include "hn_simplify_curve.h"

#include <godot_cpp/classes/geometry2d.hpp>
#include "utils/geo_utils.h"

using namespace godot;

PackedVector3Array HNSimplifyCurve::DouglasPeucker(const PackedVector3Array &p_points, const float epsilon) {
    float dmax = 0;
    int index = 1;
    // Find the farthest points from the first-last points segment.
    for (int i = 1; i < p_points.size() - 1; i++) {
        float distance = GeoUtils::point_segment_distance(p_points[i], p_points[0], p_points[p_points.size() - 1]);

        if (distance > dmax) {
            index = i;
            dmax = distance;
        }
    }

    PackedVector3Array ret;

    // If max distance is greater than epsilon, recursively simplify.
    if (dmax > epsilon) {
        // Recursive call.
        PackedVector3Array rec_ret_1 = DouglasPeucker(p_points.slice(0, index + 1), epsilon);
        PackedVector3Array rec_ret_2 = DouglasPeucker(p_points.slice(index), epsilon);

        // Build the result list.
        ret.append_array(rec_ret_1);
        ret.append_array(rec_ret_2.slice(1));
    } else {
        ret.push_back(p_points[0]);
        ret.push_back(p_points[p_points.size() - 1]);
    }

    return ret;
}

void HNSimplifyCurve::set_algorithm(const Algorithm p_value) {
    if (algorithm != p_value) {
        algorithm = p_value;
    }
}

HNSimplifyCurve::Algorithm HNSimplifyCurve::get_algorithm() const {
    return algorithm;
}

void HNSimplifyCurve::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_algorithm", "value"), &HNSimplifyCurve::set_algorithm);
    ClassDB::bind_method(D_METHOD("get_algorithm"), &HNSimplifyCurve::get_algorithm);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "Algorithm", PROPERTY_HINT_ENUM, "Douglas_Peucker", PROPERTY_USAGE_NO_EDITOR), "set_algorithm", "get_algorithm");
}

void HNSimplifyCurve::_process(const Array &p_inputs) {
    Ref<HoodieGeo> in_hgeo;
    float in_epsilon = 1;

    in_hgeo = p_inputs[0];

    {
        Array a = p_inputs[1];
        in_epsilon = Math::max((float)a[0], 0.0f);
    }

    Geometry2D g2d;

    // Pack points of the primitives
    Vector<PackedVector3Array> points_group;
    Vector<PackedVector3Array> new_points_group;

    // Pack points from primitives
    points_group = in_hgeo->pack_primitive_points();

    if (get_algorithm() == Douglas_Peucker) {
        // https://en.wikipedia.org/wiki/Ramer%E2%80%93Douglas%E2%80%93Peucker_algorithm
        for (int p = 0; p < points_group.size(); p++) {
            new_points_group.push_back(DouglasPeucker(points_group[p], in_epsilon));
        }
    }

    Ref<HoodieGeo> out_hgeo;
    out_hgeo.instantiate();
    out_hgeo->unpack_primitive_points(new_points_group);

    set_output(0, out_hgeo);
}

String HNSimplifyCurve::get_caption() const {
    return "Simplify Curve";
}

int HNSimplifyCurve::get_input_port_count() const {
    return 2;
}

HoodieNode::PortType HNSimplifyCurve::get_input_port_type(int p_port) const {
    switch (p_port) {
        case 0:
            return PortType::PORT_TYPE_HGEO;
        case 1:
            return PortType::PORT_TYPE_SCALAR;
        default:
            return PortType::PORT_TYPE_SCALAR;
    }
}

String HNSimplifyCurve::get_input_port_name(int p_port) const {
    switch (p_port) {
        case 0:
            return "HGeo";
        case 1:
            return "Epsilon";
        default:
            return "";
    }
}

int HNSimplifyCurve::get_output_port_count() const {
    return 1;
}

HoodieNode::PortType HNSimplifyCurve::get_output_port_type(int p_port) const {
    return PortType::PORT_TYPE_HGEO;
}

String HNSimplifyCurve::get_output_port_name(int p_port) const {
    return "HGeo";
}

int HNSimplifyCurve::get_property_input_count() const {
    return 2;
}

Variant::Type HNSimplifyCurve::get_property_input_type(vec_size_t p_prop) const {
    return Variant::INT;
}

Variant HNSimplifyCurve::get_property_input(vec_size_t p_port) const {
    switch (p_port) {
        case 0:
            return Variant(algorithm);
        default:
            return Variant();
    }
}

void HNSimplifyCurve::set_property_input(vec_size_t p_prop, Variant p_input) {
    algorithm = (Algorithm)(int)p_input;
}

Vector<StringName> HNSimplifyCurve::get_editable_properties() const {
    Vector<StringName> props;
    props.push_back("Algorithm");
    // TODO: VisualShaderNodeIntParameter::get_editable_properties()
    return props;
}

HashMap<StringName, String> HNSimplifyCurve::get_editable_properties_names() const {
    return HashMap<StringName, String>();
}