#include "hn_mesh_cube.h"

#include <godot_cpp/classes/array_mesh.hpp>

using namespace godot;

void HNMeshCube::_process(const Array &p_inputs) {
    float size_x = 1;
    float size_y = 1;
    float size_z = 1;

    int verts_x = 2;
    int verts_y = 2;
    int verts_z = 2;

    if (p_inputs.size() > 0) {
        Array inputs = p_inputs.duplicate();

        if (inputs[0].get_type() == Variant::ARRAY) {
            Array a = inputs[0];
            Vector3 v3;
            v3 = a[0];
            size_x = v3.x;
            size_y = v3.y;
            size_z = v3.z;
        }
        if (inputs[1].get_type() == Variant::ARRAY) {
            Array a = inputs[1];
            verts_x = MAX((int)a[0], verts_x);
        }
        if (inputs[2].get_type() == Variant::ARRAY) {
            Array a = inputs[2];
            verts_y = MAX((int)a[0], verts_y);
        }
        if (inputs[3].get_type() == Variant::ARRAY) {
            Array a = inputs[3];
            verts_z = MAX((int)a[0], verts_z);
        }
    }

    size_x = size_x * 0.5;
    size_y = size_y * 0.5;
    size_z = size_z * 0.5;

    PackedVector3Array vertices;
    PackedVector3Array normals;
    PackedVector2Array uvs;
    PackedInt32Array indices;

    // Vertices
    vertices.resize(24);
    // Front face.
    vertices[0] = Vector3(-size_x, -size_y, size_z);
    vertices[1] = Vector3(size_x, -size_y, size_z);
    vertices[2] = Vector3(size_x, size_y, size_z);
    vertices[3] = Vector3(-size_x, size_y, size_z);
    // Back face.
    vertices[4] = Vector3(-size_x, -size_y, -size_z);
    vertices[5] = Vector3(size_x, -size_y, -size_z);
    vertices[6] = Vector3(size_x, size_y, -size_z);
    vertices[7] = Vector3(-size_x, size_y, -size_z);
    // Top face.
    vertices[8] = Vector3(-size_x, size_y, -size_z);
    vertices[9] = Vector3(size_x, size_y, -size_z);
    vertices[10] = Vector3(size_x, size_y, size_z);
    vertices[11] = Vector3(-size_x, size_y, size_z);
    // Bottom face.
    vertices[12] = Vector3(-size_x, -size_y, -size_z);
    vertices[13] = Vector3(size_x, -size_y, -size_z);
    vertices[14] = Vector3(size_x, -size_y, size_z);
    vertices[15] = Vector3(-size_x, -size_y, size_z);
    // Right face.
    vertices[16] = Vector3(size_x, -size_y, -size_z);
    vertices[17] = Vector3(size_x, size_y, -size_z);
    vertices[18] = Vector3(size_x, size_y, size_z);
    vertices[19] = Vector3(size_x, -size_y, size_z);
    // Left face.
    vertices[20] = Vector3(-size_x, -size_y, -size_z);
    vertices[21] = Vector3(-size_x, size_y, -size_z);
    vertices[22] = Vector3(-size_x, size_y, size_z);
    vertices[23] = Vector3(-size_x, -size_y, size_z);

    // for (int z = 0; z < verts_z; ++z) {
    //     for (int y = 0; y < verts_y; ++y) {
    //         for (int x = 0; x < verts_x; ++x) {
    //             float xf = static_cast<float>(x) / (verts_x - 1);
    //             float yf = static_cast<float>(y) / (verts_y - 1);
    //             float zf = static_cast<float>(z) / (verts_z - 1);

    //             Vector3 vertex = Vector3(xf, yf, zf);
    //             vertices.push_back(vertex);
    //         }
    //     }
    // }

    // Normals
    normals.resize(24);
    Vector3 *norm_write = normals.ptrw();
    Vector3 front_normal = Vector3(0.0, 0.0, 1.0);
    Vector3 back_normal = Vector3(0.0, 0.0, -1.0);
    Vector3 top_normal = Vector3(0.0, 1.0, 0.0);
    Vector3 bottom_normal = Vector3(0.0, -1.0, 0.0);
    Vector3 right_normal = Vector3(1.0, 0.0, 0.0);
    Vector3 left_normal = Vector3(-1.0, 0.0, 0.0);
    std::vector<Vector3> cube_normals = {
        // Front face
        front_normal, front_normal, front_normal, front_normal,
        // Back face
        back_normal, back_normal, back_normal, back_normal,
        // Top face
        top_normal, top_normal, top_normal, top_normal,
        // Bottom face
        bottom_normal, bottom_normal, bottom_normal, bottom_normal,
        // Right face
        right_normal, right_normal, right_normal, right_normal,
        // Left face
        left_normal, left_normal, left_normal, left_normal,
    };
    std::copy(cube_normals.begin(), cube_normals.end(), norm_write);

    // UVs
    uvs.resize(24);
    Vector2 *uvs_write = uvs.ptrw();
    std::vector<Vector2> cube_uvs = {
        // Front face
        Vector2(0.0, 1.0),
        Vector2(1.0, 1.0),
        Vector2(1.0, 0.0),
        Vector2(0.0, 0.0),
        // Back face
        Vector2(0.0, 1.0),
        Vector2(1.0, 1.0),
        Vector2(1.0, 0.0),
        Vector2(0.0, 0.0),
        // Top face
        Vector2(0.0, 1.0),
        Vector2(1.0, 1.0),
        Vector2(1.0, 0.0),
        Vector2(0.0, 0.0),
        // Bottom face
        Vector2(0.0, 1.0),
        Vector2(1.0, 1.0),
        Vector2(1.0, 0.0),
        Vector2(0.0, 0.0),
        // Right face
        Vector2(0.0, 1.0),
        Vector2(1.0, 1.0),
        Vector2(1.0, 0.0),
        Vector2(0.0, 0.0),
        // Left face
        Vector2(0.0, 1.0),
        Vector2(1.0, 1.0),
        Vector2(1.0, 0.0),
        Vector2(0.0, 0.0),
    };
    std::copy(cube_uvs.begin(), cube_uvs.end(), uvs_write);

    // Indices
    indices.resize(36);
    int32_t *idx_write = indices.ptrw();
    std::vector<int32_t> cube_indices = {
        // Front face
        0, 2, 1,
        2, 0, 3,
        // Back face
        4, 5, 6,
        6, 7, 4,
        // Top face
        8, 9, 10,
        10, 11, 8,
        // Bottom face
        14, 13, 12,
        12, 15, 14,
        // Right face
        18, 17, 16,
        16, 19, 18,
        // Left face
        20, 21, 22,
        22, 23, 20
    };
    std::copy(cube_indices.begin(), cube_indices.end(), idx_write);

    out_arr.resize(ArrayMesh::ARRAY_MAX);
    out_arr[ArrayMesh::ARRAY_VERTEX] = vertices;
    out_arr[ArrayMesh::ARRAY_NORMAL] = normals;
    out_arr[ArrayMesh::ARRAY_TEX_UV] = uvs;
    out_arr[ArrayMesh::ARRAY_INDEX] = indices;
}

String HNMeshCube::get_caption() const {
    return "Cube";
}

int HNMeshCube::get_input_port_count() const {
    return 4;
}

HNMeshCube::PortType HNMeshCube::get_input_port_type(int p_port) const {
    switch (p_port) {
        case 0:
            return PortType::PORT_TYPE_VECTOR_3D;
        case 1:
            return PortType::PORT_TYPE_SCALAR_UINT;
        case 2:
            return PortType::PORT_TYPE_SCALAR_UINT;
        case 3:
            return PortType::PORT_TYPE_SCALAR_UINT;
    }

    return PortType::PORT_TYPE_SCALAR;
}

String HNMeshCube::get_input_port_name(int p_port) const {
    switch (p_port) {
        case 0:
            return "Size";
        case 1:
            return "Vertices X";
        case 2:
            return "Vertices Y";
        case 3:
            return "Vertices Z";
        default:
            return "";
    }
}

int HNMeshCube::get_output_port_count() const {
    return 1;
}

HNMeshCube::PortType HNMeshCube::get_output_port_type(int p_port) const {
    return PortType::PORT_TYPE_GEOMETRY;
}

String HNMeshCube::get_output_port_name(int p_port) const {
    return "Mesh";
}

const Variant HNMeshCube::get_output(int p_port) const {
    return Variant(out_arr);
}