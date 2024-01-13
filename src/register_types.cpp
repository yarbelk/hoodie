#include "register_types.h"

#include "hoodiemesh.h"
#include "hoodienode.h"
#include "hoodienodes/input/hninputcurve3d.h"
#include "hoodienodes/mesh_primitives/hnmeshgrid.h"
#include "hoodienodes/output/hnoutput.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

void initialize_hoodie_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	ClassDB::register_class<HoodieMesh>();
	ClassDB::register_class<HoodieNode>();
	ClassDB::register_class<HNInputCurve3D>();
	ClassDB::register_class<HNMeshGrid>();
	ClassDB::register_class<HNOutput>();
}

void uninitialize_hoodie_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
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