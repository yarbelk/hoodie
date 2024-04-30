#include "hn_decompose_mesh.h"

#include <godot_cpp/classes/array_mesh.hpp>

using namespace godot;

void HNDecomposeMesh::_process(const Array &p_inputs) {
    Array surface = p_inputs[0];

    outputs[0] = surface[ArrayMesh::ARRAY_VERTEX];
    outputs[1] = surface[ArrayMesh::ARRAY_NORMAL];
    outputs[2] = surface[ArrayMesh::ARRAY_TANGENT];
    outputs[3] = surface[ArrayMesh::ARRAY_COLOR];
    outputs[4] = surface[ArrayMesh::ARRAY_TEX_UV];
    outputs[5] = surface[ArrayMesh::ARRAY_TEX_UV2];
    outputs[6] = surface[ArrayMesh::ARRAY_CUSTOM0];
    outputs[7] = surface[ArrayMesh::ARRAY_CUSTOM1];
    outputs[8] = surface[ArrayMesh::ARRAY_CUSTOM2];
    outputs[9] = surface[ArrayMesh::ARRAY_CUSTOM3];
    outputs[10] = surface[ArrayMesh::ARRAY_BONES];
    outputs[11] = surface[ArrayMesh::ARRAY_WEIGHTS];
    outputs[12] = surface[ArrayMesh::ARRAY_INDEX];
}

String HNDecomposeMesh::get_caption() const {
    return "Decompose Mesh";
}

int HNDecomposeMesh::get_input_port_count() const {
    return 1;
}

HNDecomposeMesh::PortType HNDecomposeMesh::get_input_port_type(int p_port) const {
    return PortType::PORT_TYPE_MESH;
}

String HNDecomposeMesh::get_input_port_name(int p_port) const {
    return "Mesh";
}

int HNDecomposeMesh::get_output_port_count() const {
    return 13;
}

HNDecomposeMesh::PortType HNDecomposeMesh::get_output_port_type(int p_port) const {
    switch (p_port) {
        case 0:
            return PortType::PORT_TYPE_VECTOR_3D;
        case 1:
            return PortType::PORT_TYPE_VECTOR_3D;
        case 2:
            return PortType::PORT_TYPE_VECTOR_3D;
        case 3:
            return PortType::PORT_TYPE_VECTOR_4D;
        case 4:
            return PortType::PORT_TYPE_VECTOR_2D;
        case 5:
            return PortType::PORT_TYPE_VECTOR_2D;
        case 6:
            return PortType::PORT_TYPE_SCALAR_INT;
        case 7:
            return PortType::PORT_TYPE_SCALAR_INT;
        case 8:
            return PortType::PORT_TYPE_SCALAR_INT;
        case 9:
            return PortType::PORT_TYPE_SCALAR_INT;
        case 10:
            return PortType::PORT_TYPE_SCALAR;
        case 11:
            return PortType::PORT_TYPE_SCALAR;
        case 12:
            return PortType::PORT_TYPE_SCALAR_INT;
    }

    return PortType::PORT_TYPE_SCALAR;
}

String HNDecomposeMesh::get_output_port_name(int p_port) const {
    switch (p_port) {
        case 0:
            return "Vertex";
        case 1:
            return "Normal";
        case 2:
            return "Tangent";
        case 3:
            return "Color";
        case 4:
            return "Tex UV";
        case 5:
            return "Tex UV 2";
        case 6:
            return "Custom 0";
        case 7:
            return "Custom 1";
        case 8:
            return "Custom 2";
        case 9:
            return "Custom 3";
        case 10:
            return "Bones";
        case 11:
            return "Weights";
        case 12:
            return "Index";
    }

    return "";
}