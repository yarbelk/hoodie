#ifndef HOODIE_HOODIEEDITORPLUGIN_H
#define HOODIE_HOODIEEDITORPLUGIN_H

#include "hoodie_mesh.h"
#include "godot_cpp/classes/editor_plugin.hpp"
#include "godot_cpp/classes/h_split_container.hpp"
#include "godot_cpp/classes/v_box_container.hpp"
#include "godot_cpp/classes/h_box_container.hpp"
#include "godot_cpp/classes/menu_button.hpp"
#include "godot_cpp/classes/popup_menu.hpp"
#include "godot_cpp/classes/label.hpp"
#include "godot_cpp/classes/graph_edit.hpp"
#include "godot_cpp/classes/graph_node.hpp"
#include "godot_cpp/classes/button.hpp"

namespace godot
{

// referring to shader_editor_plugin.h .cpp from godot source code
class HoodieEditorPlugin : public EditorPlugin {
    GDCLASS(HoodieEditorPlugin, EditorPlugin);

    Ref<HoodieMesh> hoodie_mesh;

    enum {
        FILE_NEW,
        FILE_PRINTDEBUG
    };

    HSplitContainer *main_split = nullptr;
    // VBoxContainer *left_container = nullptr;
    // Label *label_title = nullptr;
    MenuButton *file_menu = nullptr;
    GraphEdit *graph_edit = nullptr;
    MenuButton *add_node = nullptr;
    PopupMenu *add_popup = nullptr;

    Button *button = nullptr;

    Vector2 place;

    // void _window_changed(bool p_visible);

    void _menu_item_pressed(int index);
    void _add_button_pressed();
    void _add_popup_pressed(int index);

	struct AddOption {
		String name;
		String category;
		String type;
		String description;

		AddOption(const String &p_name = String(), const String &p_category = String(), const String &p_type = String(), const String &p_description = String()) {
			name = p_name;
			type = p_type;
			category = p_category;
			description = p_description;
		}
	};

    Vector<AddOption> add_options;

    void _update_options_menu();

    // Add a node to the HoodieMesh class
    void _add_node(int idx);

protected:
    static void _bind_methods();
    void _notification(int what);

public:
    // virtual String get_name() const override { return "Hoodie"; }
    virtual void _make_visible(bool visible) override;
	virtual void _edit(Object *object) override;
	virtual bool _handles(Object *object) const override;

	// virtual void _set_window_layout(const Ref<ConfigFile> &configuration);
	// virtual void _get_window_layout(const Ref<ConfigFile> &configuration);

	// virtual String _get_unsaved_status(const String &for_scene) const;
	// virtual void _save_external_data();
	// virtual void _apply_changes();

    void add_graph_node();

    HoodieEditorPlugin();
    ~HoodieEditorPlugin();
};
    
} // namespace godot

#endif // HOODIE_HOODIEEDITORPLUGIN_H