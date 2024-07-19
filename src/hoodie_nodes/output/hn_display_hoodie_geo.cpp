#include "hn_display_hoodie_geo.h"

#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/classes/sphere_mesh.hpp>
#include "utils/mesh_utils.h"

using namespace godot;

void HNDisplayHoodieGeo::_process(const Array &p_inputs) {
    Ref<HoodieGeo> in_hgeo = p_inputs[0];
    float in_size = 0.4f;

    {
        Array a = p_inputs[1];
        if (a.size() > 0) {
            in_size = (float)a[0];
        }
    }

    if (in_hgeo.is_null()) { return; }

    Vector<Array> point_meshes;
    Vector<Ref<ArrayMesh>> line_meshes;

    Vector<PackedVector3Array> in_pts_packs;
    in_pts_packs.push_back(in_hgeo->points);

    for (int prim = 0; prim < in_pts_packs.size(); prim++) {
        PackedVector3Array pts = in_pts_packs[prim];

        for (int i = 0; i < pts.size(); i++) {
            Ref<SphereMesh> pt_mesh;
            pt_mesh.instantiate();
            pt_mesh->set_radial_segments(4);
            pt_mesh->set_rings(1);
            pt_mesh->set_radius(in_size);
            pt_mesh->set_height(in_size * 2);

            Array arr = pt_mesh->get_mesh_arrays();
            PackedVector3Array vs = arr[ArrayMesh::ARRAY_VERTEX];
            for (int v = 0; v < vs.size(); v++) {
                vs[v] += pts[i];
            }
            arr[ArrayMesh::ARRAY_VERTEX] = vs;

            point_meshes.push_back(arr);
        }
    }

    Ref<HoodieArrayMesh> out_ham;
    out_ham.instantiate();
    out_ham->array = MeshUtils::join_meshes(point_meshes);

    set_output(0, out_ham);
}

String HNDisplayHoodieGeo::get_caption() const {
    return "Display HGeo";
}

int HNDisplayHoodieGeo::get_input_port_count() const {
    return 2;
}

HoodieNode::PortType HNDisplayHoodieGeo::get_input_port_type(int p_port) const {
    switch (p_port) {
        case 0:
            return PortType::PORT_TYPE_HGEO;
        case 1:
            return PortType::PORT_TYPE_SCALAR;
        default:
            return PortType::PORT_TYPE_SCALAR;
    }
}

String HNDisplayHoodieGeo::get_input_port_name(int p_port) const {
    switch (p_port) {
        case 0:
            return "HGeo";
        case 1:
            return "Size";
        default:
            return "";
    }
}

int HNDisplayHoodieGeo::get_output_port_count() const {
    return 1;
}

HoodieNode::PortType HNDisplayHoodieGeo::get_output_port_type(int p_port) const {
    switch (p_port) {
        default:
            return PortType::PORT_TYPE_MESH;
    }
}

String HNDisplayHoodieGeo::get_output_port_name(int p_port) const {
    switch (p_port) {
        default:
            return "Mesh";
    }
}