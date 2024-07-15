#include "hn_join_hoodie_geo.h"

#include <godot_cpp/classes/array_mesh.hpp>

using namespace godot;

void HNJoinHoodieGeo::_process(const Array &p_inputs) {
    Ref<HoodieGeo> in_1 = p_inputs[0];
    Ref<HoodieGeo> in_2 = p_inputs[1];

    Ref<HoodieGeo> out_hgeo = in_1->duplicate();

    out_hgeo->points.append_array(in_2->points.duplicate());

    for (auto attr : in_2->attributes) {
        if (out_hgeo->attributes.has(attr.key)) {
            out_hgeo->attributes[attr.key].append_array(attr.value.duplicate());
        } else {
            Variant value = attr.value[0];

            Array def_array;
            def_array.resize(attr.value.size());
            def_array.fill(value);

            out_hgeo->attributes[attr.key].append_array(def_array);
            out_hgeo->attributes[attr.key].append_array(attr.value.duplicate());
        }
    }

    const int pts_size = in_1->points.size();
    for (auto prim : in_2->primitives) {
        PackedInt32Array new_verts;
        new_verts.resize(prim.vertices.size());

        for (int i = 0; i < new_verts.size(); i++) {
            new_verts[i] = prim.vertices[i] + pts_size;
        }

        out_hgeo->primitives.append(HoodieGeo::Primitive(new_verts));
    }

    set_output(0, out_hgeo);
}

String HNJoinHoodieGeo::get_caption() const {
    return "Join Hoodie Geo";
}

int HNJoinHoodieGeo::get_input_port_count() const {
    return 2;
}

HoodieNode::PortType HNJoinHoodieGeo::get_input_port_type(int p_port) const {
    switch (p_port) {
        case 0:
            return PortType::PORT_TYPE_HGEO;
        case 1:
            return PortType::PORT_TYPE_HGEO;
        default:
            return PortType::PORT_TYPE_DATA;
    }
}

String HNJoinHoodieGeo::get_input_port_name(int p_port) const {
    switch (p_port) {
        case 0:
            return "HGeo";
        case 1:
            return "HGeo";
        default:
            return "";
    }
}

int HNJoinHoodieGeo::get_output_port_count() const {
    return 1;
}

HoodieNode::PortType HNJoinHoodieGeo::get_output_port_type(int p_port) const {
    return PortType::PORT_TYPE_HGEO;
}

String HNJoinHoodieGeo::get_output_port_name(int p_port) const {
    return "Geo";
}