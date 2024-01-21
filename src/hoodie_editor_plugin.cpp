#include "hoodie_editor_plugin.h"

using namespace godot;

void HoodieEditorPlugin::_bind_methods() {}

HoodieEditorPlugin::HoodieEditorPlugin() {
    main_split = memnew(HSplitContainer);
    VBoxContainer *vb = memnew(VBoxContainer);
    HBoxContainer *menu_hb = memnew(HBoxContainer);
    vb->add_child(menu_hb);
    file_menu = memnew(MenuButton);
    file_menu->set_text("File");
    file_menu->set_shortcut_context(main_split);
    file_menu->get_popup()->add_item("New", 0);
    file_menu->get_popup()->add_item("Test", 1);
    menu_hb->add_child(file_menu);

    main_split->add_child(vb);
    vb->set_custom_minimum_size(Size2(200, 300));

    graph_edit = memnew(GraphEdit);
    main_split->add_child(graph_edit);

    button = add_control_to_bottom_panel(main_split, "Hoodie");
}

HoodieEditorPlugin::~HoodieEditorPlugin() {}