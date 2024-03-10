#include "register_types.h"

// https://github.com/Zylann/godot_voxel/blob/f14552ea8ae9dfd54ea9b988dc205837bcfffdda/register_types.cpp

#include "hoodie_editor_plugin.h"
#include "hoodie_mesh.h"
#include "hoodie_node.h"
#include "hoodie_nodes/curve_operations/hn_curve_to_mesh.h"
#include "hoodie_nodes/curve_operations/hn_curve_to_points.h"
#include "hoodie_nodes/input/hn_input_curve_3d.h"
#include "hoodie_nodes/input_constant/hn_input_value.h"
#include "hoodie_nodes/input_constant/hn_input_integer.h"
#include "hoodie_nodes/mesh_primitives/hn_mesh_grid.h"
#include "hoodie_nodes/mesh_primitives/hn_mesh_line.h"
#include "hoodie_nodes/output/hn_output.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

void initialize_hoodie_module(ModuleInitializationLevel p_level) {
	if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
		ClassDB::register_class<HoodieMesh>();
		ClassDB::register_abstract_class<HoodieNode>();
		ClassDB::register_class<HNCurveToMesh>();
		ClassDB::register_class<HNCurveToPoints>();
		ClassDB::register_class<HNInputCurve3D>();
		ClassDB::register_class<HNInputValue>();
		ClassDB::register_class<HNInputInteger>();
		ClassDB::register_class<HNMeshGrid>();
		ClassDB::register_class<HNMeshLine>();
		ClassDB::register_class<HNOutput>();

		// Setup engine after classes are registered.
		// This is necessary when using GDExtension because classes can't be instantiated until they are registered.
		// Example: create singletons, load static resources
		// run tests?
	}

// TODO: how to manage TOOLS_ENABLED? is it necessary?
// #ifdef TOOLS_ENABLED
	if (p_level == MODULE_INITIALIZATION_LEVEL_EDITOR) {
		// In GDExtension we have to explicitely register all classes deriving from Object even if they are not exposed
		ClassDB::register_internal_class<HoodieGraphPlugin>();
		ClassDB::register_internal_class<HoodieEditorPlugin>();

		EditorPlugins::add_by_type<HoodieEditorPlugin>();
	}
// #endif
}

void uninitialize_hoodie_module(ModuleInitializationLevel p_level) {
	if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {

	}

	if (p_level == MODULE_INITIALIZATION_LEVEL_EDITOR) {

	}
}

extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT hoodie_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

	init_obj.register_initializer(initialize_hoodie_module);
	init_obj.register_terminator(uninitialize_hoodie_module);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}