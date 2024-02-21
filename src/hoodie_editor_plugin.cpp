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

void HoodieEditorPlugin::_add_button_pressed() {
    place = Vector2(10.0, 50.0);
}

void HoodieEditorPlugin::_add_popup_pressed(int index) {
    
}

void HoodieEditorPlugin::_update_options_menu() {
    add_popup->clear();

    for (int i = 0; i < add_options.size(); i++) {
        String path = add_options[i].category + String("/") + add_options[i].name;
        PackedStringArray subfolders = path.split("/");

        PopupMenu *popup = add_popup;

        // E.g. Mesh/Primitive/Grid
        for (int j = 0; j < subfolders.size() - 1; j++) {
            String j_name = subfolders[j];
            if (!popup->has_node(j_name)) {
                PopupMenu *new_popup = memnew(PopupMenu);
                new_popup->set_name(j_name);
                new_popup->connect("id_pressed", callable_mp(this, &HoodieEditorPlugin::_add_node));
                popup->add_child(new_popup);
                popup->add_submenu_item(j_name, j_name);
            }
            popup = popup->get_node<PopupMenu>(j_name);
        }
        popup->add_item(subfolders[subfolders.size() - 1], i);
    }
}

void HoodieEditorPlugin::_add_node(int idx) {
    // TODO: godot source code visual_shader_editor_plugin.cpp _add_node()
    UtilityFunctions::print("HoodieEditorPlugin::_add_node() called.");
    Ref<HoodieNode> hnode;
    Variant v = ClassDB::instantiate(StringName(add_options[idx].type));
    HoodieNode *hn = Object::cast_to<HoodieNode>(v);
    hnode = Ref<HoodieNode>(hn);
    hoodie_mesh.ptr()->add_node(hnode);
}

void HoodieEditorPlugin::_bind_methods() {}

void HoodieEditorPlugin::_notification(int what) {
    switch (what) {
        case NOTIFICATION_POSTINITIALIZE: {
            file_menu->get_popup()->connect("id_pressed", callable_mp(this, &HoodieEditorPlugin::_menu_item_pressed));
            add_node->connect("pressed", callable_mp(this, &HoodieEditorPlugin::_add_button_pressed));
            add_popup->connect("id_pressed", callable_mp(this, &HoodieEditorPlugin::_add_popup_pressed));

            _update_options_menu();
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

    add_node = memnew(MenuButton);
    add_node->set_text("Add node...");
    graph_edit->get_menu_hbox()->add_child(add_node);
    graph_edit->get_menu_hbox()->move_child(add_node, 0);

    add_popup = add_node->get_popup();

	///////////////////////////////////////
	// HOODIE NODES TREE OPTIONS
	///////////////////////////////////////

    // INPUT

    add_options.push_back(AddOption("Input Curve3D", "Input", "HNInputCurve3D"));

    // MESH

    add_options.push_back(AddOption("Mesh Grid", "Mesh/Primitives", "HNMeshGrid"));

    // OUTPUT

    add_options.push_back(AddOption("Output", "Output", "HNOutput"));

    ///////////////////////////////////////

    button = add_control_to_bottom_panel(main_split, "Hoodie");

    _make_visible(false);
}

HoodieEditorPlugin::~HoodieEditorPlugin() {
}