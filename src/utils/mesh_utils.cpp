#include "mesh_utils.h"

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/array_mesh.hpp>

using namespace godot;

Array MeshUtils::join_meshes(const Vector<Array> &p_meshes) {
    PackedVector3Array out_mesh_verts;
    PackedVector3Array out_mesh_norms;
    PackedVector2Array out_mesh_uvs;
    PackedInt32Array out_mesh_idx;

    for (int m = 0; m < p_meshes.size(); m++) {
        Array m_mesh = p_meshes[m];

        PackedVector3Array mesh_verts = m_mesh[ArrayMesh::ARRAY_VERTEX];
        PackedVector3Array mesh_norms = m_mesh[ArrayMesh::ARRAY_NORMAL];
        PackedVector2Array mesh_uvs = m_mesh[ArrayMesh::ARRAY_TEX_UV];
        PackedInt32Array mesh_idx = m_mesh[ArrayMesh::ARRAY_INDEX];

        PackedVector3Array new_verts;
        PackedVector3Array new_norms;
        PackedVector2Array new_uvs;
        PackedInt32Array new_idx;

        for (int i = 0; i < mesh_verts.size(); i++) {
            Vector3 v = mesh_verts[i];
            new_verts.push_back(v);

            if (mesh_norms.size() > 0) {
                Vector3 n = mesh_norms[i];
                new_norms.push_back(n);
            }

            if (mesh_uvs.size() > 0) {
                Vector2 uv = mesh_uvs[i];
                new_uvs.push_back(uv);
            }
        }

        for (int i = 0; i < mesh_idx.size(); i++) {
            new_idx.push_back(mesh_idx[i] + mesh_verts.size() * m);
        }

        out_mesh_verts.append_array(new_verts);
        out_mesh_norms.append_array(new_norms);
        out_mesh_uvs.append_array(new_uvs);
        out_mesh_idx.append_array(new_idx);
    }

    Array out_mesh;
    out_mesh.resize(ArrayMesh::ARRAY_MAX);
    out_mesh[ArrayMesh::ARRAY_VERTEX] = out_mesh_verts;
    out_mesh[ArrayMesh::ARRAY_NORMAL] = out_mesh_norms;
    out_mesh[ArrayMesh::ARRAY_TEX_UV] = out_mesh_uvs;
    out_mesh[ArrayMesh::ARRAY_INDEX] = out_mesh_idx;

    return out_mesh;
}