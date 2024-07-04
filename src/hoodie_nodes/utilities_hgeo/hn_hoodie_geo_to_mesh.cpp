#include "hn_hoodie_geo_to_mesh.h"

#include <godot_cpp/classes/array_mesh.hpp>

using namespace godot;

void HNHoodieGeoToMesh::_process(const Array &p_inputs) {
    if (p_inputs.size() == 0) {
        return;
    }

    Ref<HoodieGeo> in_hgeo = p_inputs[0];

    Ref<HoodieArrayMesh> ham = HoodieArrayMesh::create_reference(in_hgeo->to_mesh());

    set_output(0, ham);
}

String HNHoodieGeoToMesh::get_caption() const {
    return "Hoodie Geo To Mesh";
}

int HNHoodieGeoToMesh::get_input_port_count() const {
    return 1;
}

HoodieNode::PortType HNHoodieGeoToMesh::get_input_port_type(int p_port) const {
    return PortType::PORT_TYPE_HGEO;
}

String HNHoodieGeoToMesh::get_input_port_name(int p_port) const {
    return "HGeo";
}

int HNHoodieGeoToMesh::get_output_port_count() const {
    return 1;
}

HoodieNode::PortType HNHoodieGeoToMesh::get_output_port_type(int p_port) const {
    return PortType::PORT_TYPE_MESH;
}

String HNHoodieGeoToMesh::get_output_port_name(int p_port) const {
    return "Mesh";
}