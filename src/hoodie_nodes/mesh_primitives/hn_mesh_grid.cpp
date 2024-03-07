#include "hn_mesh_grid.h"

#include <godot_cpp/classes/array_mesh.hpp>

using namespace godot;

void HNMeshGrid::_process(const Array &p_inputs) {
    UtilityFunctions::print("HNMeshGrid _process() call.");

    // float& x = default_size.x;
    // float& z = default_size.y;
    float x = 1;
    float z = 1;

    if (p_inputs.size() > 0) {
        if (p_inputs[0].get_type() == Variant::ARRAY) {
            Array a = p_inputs[0];
            x = (float)a[0];
        }
        if (p_inputs[1].get_type() == Variant::ARRAY) {
            Array a = p_inputs[1];
            z = (float)a[0];
        }
    }

    PackedVector3Array vertices;
    PackedInt32Array indices;

    vertices.resize(4);
    vertices[0] = Vector3(0,0,0);
    vertices[1] = Vector3(x,0,0);
    vertices[2] = Vector3(x,0,z);
    vertices[3] = Vector3(0,0,z);

    indices.resize(6);
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 2;
    indices[4] = 3;
    indices[5] = 0;

    surface_arr.resize(ArrayMesh::ARRAY_MAX);
    surface_arr[ArrayMesh::ARRAY_VERTEX] = vertices;
    surface_arr[ArrayMesh::ARRAY_INDEX] = indices;
}

String HNMeshGrid::get_caption() const {
    return "Mesh Grid";
}

int HNMeshGrid::get_input_port_count() const {
    return 4;
}

HNMeshGrid::PortType HNMeshGrid::get_input_port_type(int p_port) const {
    switch (p_port) {
        case 0:
            return PortType::PORT_TYPE_SCALAR;
        case 1:
            return PortType::PORT_TYPE_SCALAR;
        case 2:
            return PortType::PORT_TYPE_SCALAR_INT;
        case 3:
            return PortType::PORT_TYPE_SCALAR_INT;
        default:
            return PortType::PORT_TYPE_SCALAR;
    }
}

String HNMeshGrid::get_input_port_name(int p_port) const {
    switch (p_port) {
        case 0:
            return "Size X";
        case 1:
            return "Size Z";
        case 2:
            return "Vertices X";
        case 3:
            return "Vertices Z";
        default:
            return "";
    }
}

int HNMeshGrid::get_output_port_count() const {
    return 2;
}

HNMeshGrid::PortType HNMeshGrid::get_output_port_type(int p_port) const {
    switch (p_port) {
        case 0:
            return PortType::PORT_TYPE_GEOMETRY;
        case 1:
            return PortType::PORT_TYPE_VECTOR_2D;
        default:
            return PortType::PORT_TYPE_SCALAR;
    }
}

String HNMeshGrid::get_output_port_name(int p_port) const {
    switch (p_port) {
        case 0:
            return "Mesh";
        case 1:
            return "UV Map";
        default:
            return "";
    }
}

const Variant HNMeshGrid::get_output(int p_port) const {
    switch (p_port) {
        case 0:
            return Variant(surface_arr);
        case 1:
            return Variant();
        default:
            return Variant();
    }
}