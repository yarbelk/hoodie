#include "hn_evenly_spaced_points_curve.h"

#include "utils/geo_utils.h"

using namespace godot;

void HNEvenlySpacedPointsCurve::_process(const Array &p_inputs) {
    Ref<HoodieGeo> in_hgeo;
    float in_distance = 0.01f;

    in_hgeo = p_inputs[0];

    {
        Array a = p_inputs[1];
        if (a.size() > 0) {
            in_distance = Math::max(in_distance, (float)a[0]);
        }
    }

    Vector<PackedVector3Array> packs = in_hgeo->pack_primitive_points();
    Vector<PackedVector3Array> out_packs;

    for (int prim = 0; prim < packs.size(); prim++) {
        out_packs.push_back(GeoUtils::evenly_spaced_points_on_path(packs[prim], in_distance));
    }

    Ref<HoodieGeo> out_hgeo;
    out_hgeo.instantiate();

    out_hgeo->unpack_primitive_points(out_packs);

    set_output(0, out_hgeo);
}

String HNEvenlySpacedPointsCurve::get_caption() const {
    return "Evenly Spaced Points Curve";
}

int HNEvenlySpacedPointsCurve::get_input_port_count() const {
    return 2;
}

HoodieNode::PortType HNEvenlySpacedPointsCurve::get_input_port_type(int p_port) const {
    switch (p_port) {
        case 0:
            return PortType::PORT_TYPE_HGEO;
        case 1:
            return PortType::PORT_TYPE_SCALAR;
        default:
            return PortType::PORT_TYPE_SCALAR;
    }
}

String HNEvenlySpacedPointsCurve::get_input_port_name(int p_port) const {
    switch (p_port) {
        case 0:
            return "HGeo";
        case 1:
            return "Distance";
        default:
            return "";
    }
}

int HNEvenlySpacedPointsCurve::get_output_port_count() const {
    return 1;
}

HoodieNode::PortType HNEvenlySpacedPointsCurve::get_output_port_type(int p_port) const {
    return PortType::PORT_TYPE_HGEO;
}

String HNEvenlySpacedPointsCurve::get_output_port_name(int p_port) const {
    return "HGeo";
}