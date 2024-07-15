#include "hn_connect_points.h"

#include <godot_cpp/classes/array_mesh.hpp>

using namespace godot;

void HNConnectPoints::_process(const Array &p_inputs) {
    Ref<HoodieGeo> in_geo = p_inputs[0];
    TypedArray<bool> filter;

    {
        Array a = p_inputs[1];
        if (a.size() > 0) {
            filter = a;
        } else {
            filter.push_back(true);
        }
    }

    const int pts_size = in_geo.ptr()->points.size();

    while (filter.size() < pts_size) {
        filter.push_back(filter[filter.size() - 1]);
    }

    Vector<HoodieGeo::Primitive> primitives;
    PackedInt32Array vertices;

    int prim_counter = 0;
    for (int i = 0; i < pts_size; i++) {
        if (filter[i]) {
            if (i == 0) {
                vertices.append(0);
                vertices.append(1);
            } else {
                if (vertices.size() != 0 && vertices[vertices.size() - 1] != i) {
                    vertices.append(i);
                }

                if (i < pts_size - 1) {
                    vertices.append(i + 1);
                } else {
                    vertices.append(0);
                }
            }
        } else {
            if (i == 0) {
                continue;
            }

            primitives.push_back(HoodieGeo::Primitive(vertices));
            vertices.clear();

            vertices.push_back((i + 1) % pts_size);

            prim_counter++;
        }
    }

    primitives.push_back(HoodieGeo::Primitive(vertices));

    Ref<HoodieGeo> r_hgeo = HoodieGeo::create_reference(in_geo->points, primitives);
    r_hgeo->attributes = in_geo->attributes;

    outputs[0] = r_hgeo;
}

String HNConnectPoints::get_caption() const {
    return "Connect Points";
}

int HNConnectPoints::get_input_port_count() const {
    return 2;
}

HoodieNode::PortType HNConnectPoints::get_input_port_type(int p_port) const {
    switch (p_port) {
        case 0:
            return PortType::PORT_TYPE_HGEO;
        case 1:
            return PortType::PORT_TYPE_BOOLEAN;
        default:
            return PortType::PORT_TYPE_BOOLEAN;
    }
}

String HNConnectPoints::get_input_port_name(int p_port) const {
    switch (p_port) {
        case 0:
            return "Geo";
        case 1:
            return "Filter";
        default:
            return "";
    }
}

int HNConnectPoints::get_output_port_count() const {
    return 1;
}

HoodieNode::PortType HNConnectPoints::get_output_port_type(int p_port) const {
    return PortType::PORT_TYPE_HGEO;
}

String HNConnectPoints::get_output_port_name(int p_port) const {
    return "Geo";
}