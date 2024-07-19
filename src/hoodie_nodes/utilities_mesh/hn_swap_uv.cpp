#include "hn_swap_uv.h"

#include <godot_cpp/classes/array_mesh.hpp>

using namespace godot;

void HNSwapUV::_process(const Array &p_inputs) {
    Ref<HoodieArrayMesh> in_ham = p_inputs[0];

    if (in_ham.is_null()) { return; }

    Ref<HoodieArrayMesh> out_ham = in_ham->duplicate();

    PackedVector2Array uvs = out_ham->array[ArrayMesh::ARRAY_TEX_UV];
    for (int i = 0; i < uvs.size(); i++) {
        Vector2 uv = uvs[i];
        uvs[i].x = uv.y;
        uvs[i].y = uv.x;
    }

    out_ham->array[ArrayMesh::ARRAY_TEX_UV] = uvs;

    set_output(0, out_ham);
}

String HNSwapUV::get_caption() const {
    return "Swap UV";
}

int HNSwapUV::get_input_port_count() const {
    return 1;
}

HoodieNode::PortType HNSwapUV::get_input_port_type(int p_port) const {
    return PortType::PORT_TYPE_MESH;
}

String HNSwapUV::get_input_port_name(int p_port) const {
    return "Mesh";
}

int HNSwapUV::get_output_port_count() const {
    return 1;
}

HoodieNode::PortType HNSwapUV::get_output_port_type(int p_port) const {
    switch (p_port) {
        case 0:
            return PortType::PORT_TYPE_MESH;
        default:
            return PortType::PORT_TYPE_SCALAR;
    }
}

String HNSwapUV::get_output_port_name(int p_port) const {
    switch (p_port) {
        case 0:
            return "Mesh";
        default:
            return "";
    }
}