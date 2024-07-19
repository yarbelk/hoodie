#include "hn_decompose_hoodie_geo.h"

#include <godot_cpp/classes/array_mesh.hpp>

using namespace godot;

void HNDecomposeHoodieGeo::_process(const Array &p_inputs) {
    Ref<HoodieGeo> in_hgeo = p_inputs[0];

    if (in_hgeo.is_null()) { return; }

    set_output(0, in_hgeo->points);
}

String HNDecomposeHoodieGeo::get_caption() const {
    return "Decompose HGeo";
}

int HNDecomposeHoodieGeo::get_input_port_count() const {
    return 1;
}

HoodieNode::PortType HNDecomposeHoodieGeo::get_input_port_type(int p_port) const {
    return PortType::PORT_TYPE_HGEO;
}

String HNDecomposeHoodieGeo::get_input_port_name(int p_port) const {
    return "HGeo";
}

int HNDecomposeHoodieGeo::get_output_port_count() const {
    return 1;
}

HoodieNode::PortType HNDecomposeHoodieGeo::get_output_port_type(int p_port) const {
    switch (p_port) {
        case 0:
            return PortType::PORT_TYPE_VECTOR_3D;
        default:
            return PortType::PORT_TYPE_SCALAR;
    }
}

String HNDecomposeHoodieGeo::get_output_port_name(int p_port) const {
    switch (p_port) {
        case 0:
            return "Points";
        default:
            return "";
    }
}