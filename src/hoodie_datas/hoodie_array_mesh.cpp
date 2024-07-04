#include "hoodie_array_mesh.h"

#include <godot_cpp/classes/array_mesh.hpp>

using namespace godot;

void HoodieArrayMesh::_bind_methods() {
}

void HoodieArrayMesh::clear() {
    array.clear();
}

HashMap<String, String> HoodieArrayMesh::populate_tab_inspector() const {
    HashMap<String, String> tabs;

    tabs["Vertex"] = array_to_string(array[ArrayMesh::ARRAY_VERTEX]);
    tabs["Normal"] = array_to_string(array[ArrayMesh::ARRAY_NORMAL]);
    tabs["Tangent"] = array_to_string(array[ArrayMesh::ARRAY_TANGENT]);
    tabs["Color"] = array_to_string(array[ArrayMesh::ARRAY_COLOR]);
    tabs["UV"] = array_to_string(array[ArrayMesh::ARRAY_TEX_UV]);
    tabs["UV2"] = array_to_string(array[ArrayMesh::ARRAY_TEX_UV2]);
    tabs["Custom 0"] = array_to_string(array[ArrayMesh::ARRAY_CUSTOM0]);
    tabs["Custom 1"] = array_to_string(array[ArrayMesh::ARRAY_CUSTOM1]);
    tabs["Custom 2"] = array_to_string(array[ArrayMesh::ARRAY_CUSTOM2]);
    tabs["Custom 3"] = array_to_string(array[ArrayMesh::ARRAY_CUSTOM3]);
    tabs["Bones"] = array_to_string(array[ArrayMesh::ARRAY_BONES]);
    tabs["Weights"] = array_to_string(array[ArrayMesh::ARRAY_WEIGHTS]);
    tabs["Index"] = array_to_string(array[ArrayMesh::ARRAY_INDEX]);

    return tabs;
}

Ref<HoodieArrayMesh> HoodieArrayMesh::create_reference(const Array &p_array) {
    Ref<HoodieArrayMesh> ham;
    ham.instantiate();

    ham->array = p_array;

    return ham;
}

HoodieArrayMesh::HoodieArrayMesh() {
    array.resize(ArrayMesh::ARRAY_MAX);
}