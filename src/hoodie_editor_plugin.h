#ifndef HOODIE_HOODIEEDITORPLUGIN_H
#define HOODIE_HOODIEEDITORPLUGIN_H

#include "godot_cpp/classes/editor_plugin.hpp"
#include "godot_cpp/classes/h_split_container.hpp"
#include "godot_cpp/classes/v_box_container.hpp"
#include "godot_cpp/classes/h_box_container.hpp"
#include "godot_cpp/classes/menu_button.hpp"
#include "godot_cpp/classes/popup_menu.hpp"
#include "godot_cpp/classes/label.hpp"
#include "godot_cpp/classes/graph_edit.hpp"
#include "godot_cpp/classes/button.hpp"

namespace godot
{

// referring to shader_editor_plugin.h .cpp from godot source code
class HoodieEditorPlugin : public EditorPlugin {
    GDCLASS(HoodieEditorPlugin, EditorPlugin);

    HSplitContainer *main_split = nullptr;
    // VBoxContainer *left_container = nullptr;
    // Label *label_title = nullptr;
    MenuButton *file_menu = nullptr;
    GraphEdit *graph_edit = nullptr;

    Button *button = nullptr;

    // void _window_changed(bool p_visible);

protected:
    static void _bind_methods();

public:
    // virtual String get_name() const override { return "Hoodie"; }
    // virtual void _make_visible(bool visible);
	// virtual void _edit(Object *object);
	// virtual bool _handles(Object *object) const;

	// virtual void _set_window_layout(const Ref<ConfigFile> &configuration);
	// virtual void _get_window_layout(const Ref<ConfigFile> &configuration);

	// virtual String _get_unsaved_status(const String &for_scene) const;
	// virtual void _save_external_data();
	// virtual void _apply_changes();

    HoodieEditorPlugin();
    ~HoodieEditorPlugin();
};
    
} // namespace godot

#endif // HOODIE_HOODIEEDITORPLUGIN_H