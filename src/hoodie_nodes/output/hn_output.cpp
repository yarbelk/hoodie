#include "hn_output.h"

#include <godot_cpp/classes/array_mesh.hpp>

using namespace godot;

void HNOutput::_process(const Array &p_inputs) {
    UtilityFunctions::print("Output _process() call.");

    // TODO: optimize output _process function

    output_arr.clear();
    output_arr.resize(ArrayMesh::ARRAY_MAX);

    if (p_inputs.size() > 0) {
        if (p_inputs[0].get_type() == Variant::ARRAY) {
            Array surface = p_inputs[0];

            output_arr[Mesh::ARRAY_VERTEX] = surface[Mesh::ARRAY_VERTEX];
            output_arr[Mesh::ARRAY_NORMAL] = surface[Mesh::ARRAY_NORMAL];
            output_arr[Mesh::ARRAY_TANGENT] = surface[Mesh::ARRAY_TANGENT];
            output_arr[Mesh::ARRAY_COLOR] = surface[Mesh::ARRAY_COLOR];
            output_arr[Mesh::ARRAY_TEX_UV] = surface[Mesh::ARRAY_TEX_UV];
            output_arr[Mesh::ARRAY_TEX_UV2] = surface[Mesh::ARRAY_TEX_UV2];
            output_arr[Mesh::ARRAY_BONES] = surface[Mesh::ARRAY_BONES];
            output_arr[Mesh::ARRAY_WEIGHTS] = surface[Mesh::ARRAY_WEIGHTS];
            output_arr[Mesh::ARRAY_INDEX] = surface[Mesh::ARRAY_INDEX];
        }
    }
}

String HNOutput::get_caption() const {
    return "Output";
}

int HNOutput::get_input_port_count() const {
    return 1;
}

HNOutput::PortType HNOutput::get_input_port_type(int p_port) const {
    return PortType::PORT_TYPE_GEOMETRY;
}

String HNOutput::get_input_port_name(int p_port) const {
    return "Geometry";
}

int HNOutput::get_output_port_count() const {
    return 0;
}

HNOutput::PortType HNOutput::get_output_port_type(int p_port) const {
    return PortType::PORT_TYPE_SCALAR;
}

String HNOutput::get_output_port_name(int p_port) const {
    return "";
}

const Variant HNOutput::get_output(int p_port) const {
    if (p_port == 0) {
        return Variant(output_arr);
    }

    return Variant();
}