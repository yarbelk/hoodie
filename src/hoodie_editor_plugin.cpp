#include "hoodie_editor_plugin.h"

#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void HoodieEditorPlugin::_menu_item_pressed(int index) {
    switch (index) {
        case FILE_NEW: {
            UtilityFunctions::print("FILE_NEW not implemented.");
        } break;
        case FILE_PRINTDEBUG: {
            HoodieMesh *hm = hoodie_mesh.ptr();
            String debug = "Hoodie Debug Print - ";
            debug += "hoodie_nodes.size() = " + String::num_int64(hm->hoodie_nodes.size());
            debug += "; ";
            debug += "connections.size() = " + String::num_int64(hm->connections.size());
            UtilityFunctions::print(debug);
        } break;
    }
}

void HoodieEditorPlugin::_bind_methods() {}

void HoodieEditorPlugin::_notification(int what) {
    switch (what) {
        case NOTIFICATION_POSTINITIALIZE: {
            file_menu->get_popup()->connect("id_pressed", callable_mp(this, &HoodieEditorPlugin::_menu_item_pressed));
        } break;
    }
}

void HoodieEditorPlugin::_make_visible(bool visible) {
    if (visible) {
        button->show();
        make_bottom_panel_item_visible(main_split);
    } else {
        if (main_split->is_visible_in_tree()) {
            hide_bottom_panel();
        }
        
        button->hide();
    }
}

void HoodieEditorPlugin::_edit(Object *object) {
    UtilityFunctions::print("_edit() called.");
    if (!object) {
        return;
    }

    HoodieMesh *hm = Object::cast_to<HoodieMesh>(object);
    if (hm != nullptr) {
        hoodie_mesh = Ref<HoodieMesh>(hm);
    } else {
        // object is not of type HoodieMesh
    }
}

bool HoodieEditorPlugin::_handles(Object *object) const {
    return Object::cast_to<HoodieMesh>(object) != nullptr;
}

HoodieEditorPlugin::HoodieEditorPlugin() {
    main_split = memnew(HSplitContainer);
    VBoxContainer *vb = memnew(VBoxContainer);
    HBoxContainer *menu_hb = memnew(HBoxContainer);
    vb->add_child(menu_hb);
    file_menu = memnew(MenuButton);
    file_menu->set_text("File");
    file_menu->set_shortcut_context(main_split);
    file_menu->get_popup()->add_item("New", FILE_NEW);
    file_menu->get_popup()->add_item("Print debug", FILE_PRINTDEBUG);
    menu_hb->add_child(file_menu);

    main_split->add_child(vb);
    vb->set_custom_minimum_size(Size2(200, 300));

    graph_edit = memnew(GraphEdit);
    main_split->add_child(graph_edit);

    button = add_control_to_bottom_panel(main_split, "Hoodie");

    _make_visible(false);
}

HoodieEditorPlugin::~HoodieEditorPlugin() {
}