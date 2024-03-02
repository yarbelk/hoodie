#include "hoodie_editor_plugin.h"

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/editor_undo_redo_manager.hpp>
// #include <godot_cpp/classes/undo_redo.hpp>

using namespace godot;

HoodieGraphPlugin::HoodieGraphPlugin() {
}

void HoodieGraphPlugin::_bind_methods() {
    ClassDB::bind_method(D_METHOD("add_node", "id", "just_update"), &HoodieGraphPlugin::add_node);
    ClassDB::bind_method(D_METHOD("remove_node", "id", "just_update"), &HoodieGraphPlugin::remove_node);
    ClassDB::bind_method(D_METHOD("set_node_position", "id", "position"), &HoodieGraphPlugin::set_node_position);
}

void HoodieGraphPlugin::set_editor(HoodieEditorPlugin *p_editor) {
    editor = p_editor;
}

void HoodieGraphPlugin::register_hoodie_mesh(HoodieMesh *p_hoodie_mesh) {
    hoodie_mesh = Ref<HoodieMesh>(p_hoodie_mesh);
}

void HoodieGraphPlugin::register_link(id_t p_id, HoodieNode *p_hoodie_node, GraphElement *p_graph_element) {
    links.insert(p_id, { p_hoodie_node, p_graph_element });
}

void HoodieGraphPlugin::clear_links() {
    links.clear();
}

void HoodieGraphPlugin::update_node(id_t p_id) {
}

void HoodieGraphPlugin::update_node_deferred(id_t p_id) {
}

void HoodieGraphPlugin::add_node(id_t p_id, bool p_just_update) {
    if (!hoodie_mesh.is_valid()) {
        return;
    }
    HoodieGraphPlugin *graph_plugin = editor->get_graph_plugin();
    if (!graph_plugin) {
        return;
    }

    // HoodieNode *hn = hoodie_node.ptr();
    Ref<HoodieNode> hoodie_node = hoodie_mesh->get_node(p_id);

	static const Color type_color[] = {
		Color(0.38, 0.85, 0.96), // scalar (float)
		Color(0.49, 0.78, 0.94), // scalar (int)
		Color(0.20, 0.88, 0.67), // scalar (uint)
		Color(0.74, 0.57, 0.95), // vector2
		Color(0.84, 0.49, 0.93), // vector3
		Color(1.0, 0.125, 0.95), // vector4
		Color(0.55, 0.65, 0.94), // boolean
		Color(0.96, 0.66, 0.43), // transform
		Color(1.0, 1.0, 0.0), // sampler
	};

    GraphNode *graph_node = memnew(GraphNode);
    graph_node->set_title(hoodie_node->get_caption() + String(" [") + String::num_int64(hoodie_node->id) + String("]"));

    graph_node->connect("delete_request", callable_mp(editor, &HoodieEditorPlugin::_delete_node_request).bind(hoodie_node->get_id()), CONNECT_DEFERRED);

    if (p_just_update) {

    } else {
        register_link(p_id, hoodie_node.ptr(), graph_node);
    }

    graph_node->set_resizable(false);
    graph_node->set_custom_minimum_size(Size2(200, 0));

    graph_node->set_position_offset(hoodie_mesh->get_node_position(p_id));

    graph_node->set_name(itos(p_id));

    graph_node->connect("dragged", callable_mp(editor, &HoodieEditorPlugin::_node_dragged).bind(p_id));

    int j = 0;
    for (int i = 0; i < hoodie_node->get_output_port_count(); i++)
    {
        HBoxContainer *hb = memnew(HBoxContainer);
        Label *label = memnew(Label);
        label->set_text(hoodie_node->get_output_port_name(i));
        label->set_horizontal_alignment(HORIZONTAL_ALIGNMENT_RIGHT);
        label->set_vertical_alignment(VERTICAL_ALIGNMENT_CENTER);
        label->set_h_size_flags(Control::SIZE_EXPAND_FILL);
        hb->add_child(label);
        graph_node->add_child(hb);

        int port_type = 0;
        graph_node->set_slot(i, false, port_type, type_color[0], true, port_type, type_color[0]);
        j++;
    }

    for (int i = 0; i < hoodie_node->get_input_port_count(); i++)
    {
        HBoxContainer *hb = memnew(HBoxContainer);
        Label *label = memnew(Label);
        label->set_text(hoodie_node->get_input_port_name(i));
        label->set_horizontal_alignment(HORIZONTAL_ALIGNMENT_LEFT);
        label->set_vertical_alignment(VERTICAL_ALIGNMENT_CENTER);
        label->set_h_size_flags(Control::SIZE_EXPAND_FILL);
        hb->add_child(label);
        graph_node->add_child(hb);

        int port_type = 0;
        graph_node->set_slot(j, true, port_type, type_color[0], false, port_type, type_color[0]);
        j++;
    }

    editor->graph_edit->add_child(graph_node);
}

void HoodieGraphPlugin::remove_node(id_t p_id, bool p_just_update) {
    // if (hoodie_mesh->graph.nodes.has(p_id)) {
    if (links.has(p_id)) {
        Node *graph_edit_node = links[p_id].graph_element->get_parent();
        graph_edit_node->remove_child(links[p_id].graph_element);
        memdelete(links[p_id].graph_element);
        if (!p_just_update) {
            links.erase(p_id);
        }
    }
}

void HoodieGraphPlugin::set_node_position(id_t p_id, const Vector2 &p_position) {
    if (links.has(p_id)) {
        links[p_id].graph_element->set_position_offset(p_position);
    }
}

HoodieGraphPlugin::~HoodieGraphPlugin() {
}

///////////////////

void HoodieEditorPlugin::_menu_item_pressed(int index) {
    switch (index) {
        case FILE_NEW: {
            UtilityFunctions::print("FILE_NEW not implemented.");
        } break;
        case FILE_PRINTDEBUG: {
            HoodieMesh *hm = hoodie_mesh.ptr();
            String debug = "Hoodie Debug Print - ";
            debug += "hoodie_nodes.size() = " + String::num_int64(hm->graph.nodes.size());
            debug += "; ";
            debug += "connections.size() = " + String::num_int64(hm->graph.connections.size());
            UtilityFunctions::print(debug);
            /*
            for (const KeyValue<HoodieMesh::id_t, HoodieMesh::Node> &E : hm->graph.nodes) {
                E.value.node->update(true, Array());
            }
            */
        } break;
    }
}

void HoodieEditorPlugin::_add_button_pressed() {
    place = Vector2(10.0, 50.0);
}

void HoodieEditorPlugin::_add_popup_pressed(int index) {
}

void HoodieEditorPlugin::_update_nodes() {
    // TODO: implement _update_nodes()
}

void HoodieEditorPlugin::_update_graph() {
    // TODO: implement _update_graph()
    if (updating) {
        return;
    }

    if (hoodie_mesh.is_null()) {
        return;
    }

    // graph_edit->set_scroll_offset();

    graph_edit->clear_connections();
    // Remove all nodes.
    for (int i = 0; i < graph_edit->get_child_count(); i++) {
        if (Object::cast_to<GraphElement>(graph_edit->get_child(i))) {
            Node *node = graph_edit->get_child(i);
            graph_edit->remove_child(node);
            memdelete(node);
            i--;
        }
    }

    List<HoodieMesh::Connection> node_connections;
    // hoodie_mesh->get_node_connections()
    // graph_plugin->sete_connections();

    Vector<id_t> nodes = hoodie_mesh->get_nodes_id_list();

    graph_plugin->clear_links();
    
    for (int n_i = 0; n_i < nodes.size(); n_i++) {
        graph_plugin->add_node(nodes[n_i], false);
    }

    for (const HoodieMesh::Connection &E : node_connections) {
        id_t l_node = E.l_node;
        id_t l_port = E.l_port;
        id_t r_node = E.r_node;
        id_t r_port = E.r_port;

        // graph_edit->connect_node()
    }
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
    Ref<HoodieNode> hnode;
    Variant v = ClassDB::instantiate(StringName(add_options[idx].type));
    HoodieNode *hn = Object::cast_to<HoodieNode>(v);
    hnode = Ref<HoodieNode>(hn);
    id_t valid_id = hoodie_mesh->get_valid_node_id();
    hoodie_mesh.ptr()->add_node(hnode, place, valid_id);
    // add_graph_node(hnode, add_options[idx], valid_id, false);
    graph_plugin->add_node(valid_id, false);
}

void HoodieEditorPlugin::_node_dragged(const Vector2 &p_from, const Vector2 &p_to, id_t p_node) {
    drag_buffer.push_back({ p_node, p_from, p_to });
    if (!drag_dirty) {
        call_deferred(StringName("_nodes_dragged"));
    }
    drag_dirty = true;
}

void HoodieEditorPlugin::_nodes_dragged() {
    drag_dirty = false;

    EditorUndoRedoManager *undo_redo = get_undo_redo();
    undo_redo->create_action("Node(s) Moved");

    for (const DragOp &E : drag_buffer) {
        undo_redo->add_do_method(hoodie_mesh.ptr(), "set_node_position", E.node, E.to);
        undo_redo->add_undo_method(hoodie_mesh.ptr(), "set_node_position", E.node, E.from);
        undo_redo->add_do_method(graph_plugin.ptr(), "set_node_position", E.node, E.to);
        undo_redo->add_undo_method(graph_plugin.ptr(), "set_node_position", E.node, E.from);
    }

    drag_buffer.clear();
    undo_redo->commit_action();
}

void HoodieEditorPlugin::_delete_nodes(const List<id_t> &p_nodes) {
    EditorUndoRedoManager *undo_redo = get_undo_redo();

    // TODO: implement connections

    for (const id_t &F : p_nodes) {
        Ref<HoodieNode> node = hoodie_mesh->get_node(F);

        undo_redo->add_do_method(hoodie_mesh.ptr(), "remove_node", F);
        undo_redo->add_do_method(graph_plugin.ptr(), "remove_node", F, false);
        undo_redo->add_undo_method(hoodie_mesh.ptr(), "add_node", node, hoodie_mesh->get_node_position(F), F);
        undo_redo->add_undo_method(graph_plugin.ptr(), "add_node", F, false);
    }
}

void HoodieEditorPlugin::_delete_node_request(id_t p_node) {
    Ref<HoodieNode> node = hoodie_mesh->get_node(p_node);

    List<id_t> to_erase;
    to_erase.push_back(p_node);

    EditorUndoRedoManager *undo_redo = get_undo_redo();
    undo_redo->create_action("Delete HoodieNode");
    _delete_nodes(to_erase);
    undo_redo->commit_action();
}

void HoodieEditorPlugin::_delete_nodes_request(const TypedArray<StringName> &p_nodes) {
    List<id_t> to_erase;

    if (!p_nodes.is_empty()) {
        for (int i = 0; i < p_nodes.size(); i++) {
            id_t id = p_nodes[i].operator String().to_int();
            to_erase.push_back(id);
        }
    }

    if (to_erase.is_empty()) {
        return;
    }

    // FIXME: UndoRedo mismatch error.
    // Look at: https://github.com/godotengine/godot-proposals/discussions/7168
    // and: https://github.com/Zylann/godot_voxel/blob/57baa553221aeff45be3ff46caa3261819a473bd/editor/graph/voxel_generator_graph_undo_redo_workaround.h#L10
    EditorUndoRedoManager *undo_redo = get_undo_redo();
    undo_redo->create_action("Delete HoodieNode(s)");
    _delete_nodes(to_erase);
    undo_redo->commit_action();
}

void HoodieEditorPlugin::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_nodes_dragged"), &HoodieEditorPlugin::_nodes_dragged);
}

void HoodieEditorPlugin::_notification(int what) {
    switch (what) {
        case NOTIFICATION_POSTINITIALIZE: {
            graph_edit->connect("delete_nodes_request", callable_mp(this, &HoodieEditorPlugin::_delete_nodes_request));

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
    if (!object) {
        return;
    }

    HoodieMesh *hm = Object::cast_to<HoodieMesh>(object);

    bool changed = false;
    if (hm) {
        if (hoodie_mesh.is_null()) {
            changed = true;
        } else {
            if (hoodie_mesh.ptr() != hm) {
                changed = true;
            }
        }
        hoodie_mesh = Ref<HoodieMesh>(hm);
        graph_plugin->register_hoodie_mesh(hoodie_mesh.ptr());

        _update_nodes();
    } else {
        if (hoodie_mesh.is_valid()) {
            // hoodie_mesh->disconnect_changed
        }
        hoodie_mesh.unref();
    }

    if (hoodie_mesh.is_null()) {
        // hide();
    } else {
        if (changed) {
            // _update_varying_tree();
			// _update_options_menu();
			// _update_preview();
			_update_graph();
        }
    }
}

bool HoodieEditorPlugin::_handles(Object *object) const {
    return Object::cast_to<HoodieMesh>(object) != nullptr;
}

/*
void HoodieEditorPlugin::add_graph_node(Ref<HoodieNode> &hoodie_node, const AddOption &option, id_t p_id, bool p_just_update) {
// void HoodieGraphPlugin::add_node(id_t p_id, bool p_just_update) {
    // HoodieNode *hn = hoodie_node.ptr();
    Ref<HoodieNode> hoodie_node = hoodie_mesh->get_node(p_id);

	static const Color type_color[] = {
		Color(0.38, 0.85, 0.96), // scalar (float)
		Color(0.49, 0.78, 0.94), // scalar (int)
		Color(0.20, 0.88, 0.67), // scalar (uint)
		Color(0.74, 0.57, 0.95), // vector2
		Color(0.84, 0.49, 0.93), // vector3
		Color(1.0, 0.125, 0.95), // vector4
		Color(0.55, 0.65, 0.94), // boolean
		Color(0.96, 0.66, 0.43), // transform
		Color(1.0, 1.0, 0.0), // sampler
	};

    GraphNode *graph_node = memnew(GraphNode);
    graph_node->set_title(option.name + String(" [") + String::num_int64(hn->id) + String("]"));

    graph_node->connect("delete_request", callable_mp(this, &HoodieEditorPlugin::_delete_node_request).bind(hoodie_node->get_id()), CONNECT_DEFERRED);

    graph_node->set_resizable(false);
    graph_node->set_custom_minimum_size(Size2(200, 0));

    graph_node->set_name(itos(p_id));

    int j = 0;
    for (int i = 0; i < hn->get_output_port_count(); i++)
    {
        HBoxContainer *hb = memnew(HBoxContainer);
        Label *label = memnew(Label);
        label->set_text(hn->get_output_port_name(i));
        label->set_horizontal_alignment(HORIZONTAL_ALIGNMENT_RIGHT);
        label->set_vertical_alignment(VERTICAL_ALIGNMENT_CENTER);
        label->set_h_size_flags(Control::SIZE_EXPAND_FILL);
        hb->add_child(label);
        graph_node->add_child(hb);

        int port_type = 0;
        graph_node->set_slot(i, false, port_type, type_color[0], true, port_type, type_color[0]);
        j++;
    }

    for (int i = 0; i < hn->get_input_port_count(); i++)
    {
        HBoxContainer *hb = memnew(HBoxContainer);
        Label *label = memnew(Label);
        label->set_text(hn->get_input_port_name(i));
        label->set_horizontal_alignment(HORIZONTAL_ALIGNMENT_LEFT);
        label->set_vertical_alignment(VERTICAL_ALIGNMENT_CENTER);
        label->set_h_size_flags(Control::SIZE_EXPAND_FILL);
        hb->add_child(label);
        graph_node->add_child(hb);

        int port_type = 0;
        graph_node->set_slot(j, true, port_type, type_color[0], false, port_type, type_color[0]);
        j++;
    }

    graph_edit->add_child(graph_node);
}
*/

/*
void HoodieEditorPlugin::remove_graph_node(id_t p_id, bool p_just_update) {
    if (hoodie_mesh->graph.nodes.has(p_id)) {
        graph_edit->remove_child()
        memdelete()
    }
}
*/

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

    graph_plugin.instantiate();
    graph_plugin->set_editor(this);
}