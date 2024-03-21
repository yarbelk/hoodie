#include "register_types.h"

#ifdef TOOLS_ENABLED
#include "hoodie_editor_plugin.h"
#endif // TOOLS_ENABLED

#include "hoodie_mesh.h"
#include "hoodie_node.h"
#include "hoodie_nodes/curve_operations/hn_curve_to_mesh.h"
#include "hoodie_nodes/curve_operations/hn_curve_to_points.h"
#include "hoodie_nodes/geometry_operations/hn_transform_geometry.h"
#include "hoodie_nodes/input/hn_input_curve_3d.h"
#include "hoodie_nodes/input_constant/hn_input_integer.h"
#include "hoodie_nodes/input_constant/hn_input_value.h"
#include "hoodie_nodes/input_constant/hn_input_vector3d.h"
#include "hoodie_nodes/mesh_primitives/hn_mesh_circle.h"
#include "hoodie_nodes/mesh_primitives/hn_mesh_cube.h"
#include "hoodie_nodes/mesh_primitives/hn_mesh_grid.h"
#include "hoodie_nodes/mesh_primitives/hn_mesh_line.h"
#include "hoodie_nodes/utilities_data/hn_repeat_data.h"
#include "hoodie_nodes/utilities_math/hn_math_multiply.h"
#include "hoodie_nodes/utilities_mesh/hn_compose_mesh.h"
#include "hoodie_nodes/utilities_mesh/hn_decompose_mesh.h"
#include "hoodie_nodes/utilities_vector/hn_combine_xyz.h"
#include "hoodie_nodes/utilities_vector/hn_separate_xyz.h"
#include "hoodie_nodes/utilities_vector/hn_combine_xy.h"
#include "hoodie_nodes/utilities_vector/hn_separate_xy.h"
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
		ClassDB::register_class<HNTransformGeometry>();
		ClassDB::register_class<HNInputCurve3D>();
		ClassDB::register_class<HNInputInteger>();
		ClassDB::register_class<HNInputValue>();
		ClassDB::register_class<HNInputVector3D>();
		ClassDB::register_class<HNMeshCircle>();
		ClassDB::register_class<HNMeshCube>();
		ClassDB::register_class<HNMeshGrid>();
		ClassDB::register_class<HNMeshLine>();
		ClassDB::register_class<HNRepeatData>();
		ClassDB::register_class<HNMathMultiply>();
		ClassDB::register_class<HNComposeMesh>();
		ClassDB::register_class<HNDecomposeMesh>();
		ClassDB::register_class<HNCombineXY>();
		ClassDB::register_class<HNCombineXYZ>();
		ClassDB::register_class<HNSeparateXY>();
		ClassDB::register_class<HNSeparateXYZ>();
		ClassDB::register_class<HNOutput>();

		// Setup engine after classes are registered.
		// This is necessary when using GDExtension because classes can't be instantiated until they are registered.
		// Example: create singletons, load static resources
		// run tests?
	}

#ifdef TOOLS_ENABLED
	if (p_level == MODULE_INITIALIZATION_LEVEL_EDITOR) {
		// In GDExtension we have to explicitely register all classes deriving from Object even if they are not exposed
		ClassDB::register_internal_class<HoodieNodePlugin>();
		ClassDB::register_internal_class<HoodieGraphPlugin>();
		ClassDB::register_internal_class<HoodieControl>();
		ClassDB::register_internal_class<HoodieEditorPlugin>();
		ClassDB::register_internal_class<HoodieNodePluginDefault>();
		ClassDB::register_internal_class<HoodieNodePluginInputEditor>();
		ClassDB::register_internal_class<HoodieNodePluginDefaultEditor>();

		EditorPlugins::add_by_type<HoodieEditorPlugin>();
	}
#endif // TOOLS_ENABLED
}

void uninitialize_hoodie_module(ModuleInitializationLevel p_level) {
	if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {

	}

#ifdef TOOLS_ENABLED
	if (p_level == MODULE_INITIALIZATION_LEVEL_EDITOR) {

	}
#endif // TOOLS_ENABLED
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