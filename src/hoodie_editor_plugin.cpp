#include "hoodie_editor_plugin.h"

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/editor_undo_redo_manager.hpp>

using namespace godot;

HoodieGraphPlugin::HoodieGraphPlugin() {
}

void HoodieGraphPlugin::_bind_methods() {
    ClassDB::bind_method(D_METHOD("update_node", "id"), &HoodieGraphPlugin::update_node);
    ClassDB::bind_method(D_METHOD("add_node", "id", "just_update"), &HoodieGraphPlugin::add_node);
    ClassDB::bind_method(D_METHOD("remove_node", "id", "just_update"), &HoodieGraphPlugin::remove_node);
    ClassDB::bind_method(D_METHOD("connect_nodes"), &HoodieGraphPlugin::connect_nodes);
    ClassDB::bind_method(D_METHOD("disconnect_nodes"), &HoodieGraphPlugin::disconnect_nodes);
    ClassDB::bind_method(D_METHOD("set_node_position", "id", "position"), &HoodieGraphPlugin::set_node_position);
}

void HoodieGraphPlugin::set_editor(HoodieEditorPlugin *p_editor) {
    editor = p_editor;
}

void HoodieGraphPlugin::register_hoodie_mesh(HoodieMesh *p_hoodie_mesh) {
    hoodie_mesh = Ref<HoodieMesh>(p_hoodie_mesh);
}

void HoodieGraphPlugin::set_connections(const List<HoodieMesh::Connection> &p_connections) {
    connections = p_connections;
}

void HoodieGraphPlugin::register_link(id_t p_id, HoodieNode *p_hoodie_node, GraphElement *p_graph_element) {
    links.insert(p_id, { p_hoodie_node, p_graph_element });
}

void HoodieGraphPlugin::clear_links() {
    links.clear();
}

void HoodieGraphPlugin::update_node(id_t p_id) {
    if (!links.has(p_id)) {
        return;
    }
    remove_node(p_id, true);
    add_node(p_id, true);
}

void HoodieGraphPlugin::update_node_deferred(id_t p_id) {
    call_deferred(StringName("update_node"), p_id);
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
		Color(0.70, 0.70, 0.70), // scalar (float)
		Color(0.37, 0.62, 0.38), // scalar (int)
		Color(0.17, 0.66, 0.19), // scalar (uint)
		Color(0.46, 0.46, 1.00), // vector2
		Color(0.46, 0.46, 1.00), // vector3
		Color(0.46, 0.46, 1.00), // vector4
		Color(0.80, 0.65, 0.84), // boolean
		Color(0.78, 0.78, 0.16), // color
		Color(0.34, 0.65, 1.00), // string
		Color(0.00, 0.84, 0.64), // geometry
		Color(0.00, 0.00, 0.00), // array
		Color(1.0, 1.0, 0.0), // max
	};

    GraphNode *graph_node = memnew(GraphNode);
    graph_node->set_title(hoodie_node->get_caption() + String(" [") + String::num_int64(p_id) + String("]"));

    graph_node->connect("delete_request", callable_mp(editor, &HoodieEditorPlugin::_delete_node_request).bind(p_id), CONNECT_DEFERRED);

    if (p_just_update) {
        Link &link = links[p_id];

        link.graph_element = graph_node;
    } else {
        register_link(p_id, hoodie_node.ptr(), graph_node);
    }

    graph_node->set_resizable(false);
    graph_node->set_custom_minimum_size(Size2(200, 0));

    graph_node->set_position_offset(hoodie_mesh->get_node_position(p_id));

    graph_node->set_name(itos(p_id));

    graph_node->connect("dragged", callable_mp(editor, &HoodieEditorPlugin::_node_dragged).bind(p_id));

    int j = 0;

    // Adding Output ports.
    for (int i = 0; i < hoodie_node->get_output_port_count(); i++)
    {
        HoodieNode::PortType port_output = hoodie_node->get_output_port_type(i);

        HBoxContainer *hb = memnew(HBoxContainer);
        Label *label = memnew(Label);
        label->set_text(hoodie_node->get_output_port_name(i));
        label->set_horizontal_alignment(HORIZONTAL_ALIGNMENT_RIGHT);
        label->set_vertical_alignment(VERTICAL_ALIGNMENT_CENTER);
        label->set_h_size_flags(Control::SIZE_EXPAND_FILL);
        hb->add_child(label);
        graph_node->add_child(hb);

        int port_type = 0;
        graph_node->set_slot(i, false, port_type, type_color[0], true, port_type, type_color[port_output]);
        j++;
    }

    // Adding Input ports.
    for (int i = 0; i < hoodie_node->get_input_port_count(); i++)
    {
        HoodieNode::PortType port_input = hoodie_node->get_input_port_type(i);

        HBoxContainer *hb = memnew(HBoxContainer);
        Label *label = memnew(Label);
        label->set_text(hoodie_node->get_input_port_name(i));
        label->set_horizontal_alignment(HORIZONTAL_ALIGNMENT_LEFT);
        label->set_vertical_alignment(VERTICAL_ALIGNMENT_CENTER);
        label->set_h_size_flags(Control::SIZE_EXPAND_FILL);
        hb->add_child(label);
        graph_node->add_child(hb);

        int port_type = 0;
        graph_node->set_slot(j, true, port_type, type_color[port_input], false, port_type, type_color[0]);
        j++;
    }

    // Adding Properties fields.
    VBoxContainer *props_vb = memnew(VBoxContainer);
    for (int i = 0; i < hoodie_node->get_property_input_count(); i++) {
        switch (hoodie_node->get_property_input_type(i)) {
            case Variant::FLOAT:
                EditorSpinSlider *ess = memnew(EditorSpinSlider);
                props_vb->add_child(ess);
                ess->set_custom_minimum_size(Size2(65, 0));
                ess->set_h_size_flags(Control::SIZE_EXPAND_FILL);
                ess->set_step(0.01);
                ess->set_hide_slider(true);
                ess->set_allow_greater(true);
                ess->set_allow_lesser(true);
                ess->connect("value_changed", callable_mp(this, &HoodieGraphPlugin::_on_range_value_changed).bind(p_id, i));
                Link &link = links[p_id];
                link.ranges[i] = ess;
                break;
        }
    }
    graph_node->add_child(props_vb);

    editor->graph_edit->add_child(graph_node);
}

void HoodieGraphPlugin::remove_node(id_t p_id, bool p_just_update) {
    if (links.has(p_id)) {
        Node *graph_edit_node = links[p_id].graph_element->get_parent();
        graph_edit_node->remove_child(links[p_id].graph_element);
        memdelete(links[p_id].graph_element);
        if (!p_just_update) {
            links.erase(p_id);
        }
    }
}

void HoodieGraphPlugin::connect_nodes(id_t p_l_node, vec_size_t p_l_port, id_t p_r_node, vec_size_t p_r_port) {
    GraphEdit *graph = editor->graph_edit;
    if (!graph) {
        return;
    }

    if (hoodie_mesh.is_valid()) {
        graph->connect_node(itos(p_l_node), p_l_port, itos(p_r_node), p_r_port);
        connections.push_back({ p_l_node, p_l_port, p_r_node, p_r_port });
    }
}

void HoodieGraphPlugin::disconnect_nodes(id_t p_l_node, vec_size_t p_l_port, id_t p_r_node, vec_size_t p_r_port) {
    GraphEdit *graph = editor->graph_edit;
    if (!graph) {
        return;
    }

    if (hoodie_mesh.is_valid()) {
        graph->disconnect_node(itos(p_l_node), p_l_port, itos(p_r_node), p_r_port);

        for (const List<HoodieMesh::Connection>::Element *E = connections.front(); E; E = E->next()) {
            if (E->get().l_node == p_l_node && E->get().l_port == p_l_port && E->get().r_node == p_r_node && E->get().r_port == p_r_port) {
                connections.erase(E);
                break;
            }
        }
    }
}

void HoodieGraphPlugin::set_node_position(id_t p_id, const Vector2 &p_position) {
    if (links.has(p_id)) {
        links[p_id].graph_element->set_position_offset(p_position);
    }
}

void HoodieGraphPlugin::_on_range_value_changed(double p_val, id_t p_id, vec_size_t p_prop_id) {
    Link &link = links[p_id];
    link.hoodie_node->set_property_input(p_prop_id, Variant(p_val));
    link.hoodie_node->mark_dirty();
    editor->hoodie_mesh->_queue_update();
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

    // TODO: graph_edit->set_scroll_offset();

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
    hoodie_mesh->get_node_connections(&node_connections);
    graph_plugin->set_connections(node_connections);

    Vector<id_t> nodes = hoodie_mesh->get_nodes_id_list();

    graph_plugin->clear_links();
    
    for (int n_i = 0; n_i < nodes.size(); n_i++) {
        graph_plugin->add_node(nodes[n_i], false);
    }

    for (const HoodieMesh::Connection &E : node_connections) {
        id_t l_node = E.l_node;
        vec_size_t l_port = E.l_port;
        id_t r_node = E.r_node;
        vec_size_t r_port = E.r_port;

        graph_edit->connect_node(itos(l_node), l_port, itos(r_node), r_port);
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

void HoodieEditorPlugin::_connection_request(const String &p_from, int p_from_index, const String &p_to, int p_to_index) {
    id_t l_node = p_from.to_int();
    vec_size_t l_port = p_from_index;
    id_t r_node = p_to.to_int();
    vec_size_t r_port = p_to_index;

    if (!hoodie_mesh->can_connect_nodes(l_node, l_port, r_node, r_port)) {
        return;
    }

    EditorUndoRedoManager *undo_redo = get_undo_redo();
    undo_redo->create_action("HoodieNode(s) Connected");

    List<HoodieMesh::Connection> conns;
    hoodie_mesh->get_node_connections(&conns);

    for (const HoodieMesh::Connection &E : conns) {
        if (E.r_node == r_node && E.r_port == r_port) {
            undo_redo->add_do_method(hoodie_mesh.ptr(), "disconnect_nodes", E.l_node, E.l_port, E.r_node, E.r_port);
            undo_redo->add_undo_method(hoodie_mesh.ptr(), "connect_nodes", E.l_node, E.l_port, E.r_node, E.r_port);
            undo_redo->add_do_method(graph_plugin.ptr(), "disconnect_nodes", E.l_node, E.l_port, E.r_node, E.r_port);
            undo_redo->add_undo_method(graph_plugin.ptr(), "connect_nodes", E.l_node, E.l_port, E.r_node, E.r_port);
        }
    }

    undo_redo->add_do_method(hoodie_mesh.ptr(), "connect_nodes", l_node, l_port, r_node, r_port);
    undo_redo->add_undo_method(hoodie_mesh.ptr(), "disconnect_nodes", l_node, l_port, r_node, r_port);
    undo_redo->add_do_method(graph_plugin.ptr(), "connect_nodes", l_node, l_port, r_node, r_port);
    undo_redo->add_undo_method(graph_plugin.ptr(), "disconnect_nodes", l_node, l_port, r_node, r_port);
    undo_redo->add_do_method(graph_plugin.ptr(), "update_node", r_node);
    undo_redo->add_undo_method(graph_plugin.ptr(), "update_node", r_node);
    undo_redo->commit_action();
}

void HoodieEditorPlugin::_disconnection_request(const String &p_from, int p_from_index, const String &p_to, int p_to_index) {
    graph_edit->disconnect_node(p_from, p_from_index, p_to, p_to_index);

    id_t l_node = p_from.to_int();
    vec_size_t l_port = p_from_index;
    id_t r_node = p_to.to_int();
    vec_size_t r_port = p_to_index;

    EditorUndoRedoManager *undo_redo = get_undo_redo();
    undo_redo->create_action("HoodieNode(s) Disconnected");
    undo_redo->add_do_method(hoodie_mesh.ptr(), "disconnect_nodes", l_node, l_port, r_node, r_port);
    undo_redo->add_undo_method(hoodie_mesh.ptr(), "connect_nodes", l_node, l_port, r_node, r_port);
    undo_redo->add_do_method(graph_plugin.ptr(), "disconnect_nodes", l_node, l_port, r_node, r_port);
    undo_redo->add_undo_method(graph_plugin.ptr(), "connect_nodes", l_node, l_port, r_node, r_port);
    undo_redo->add_do_method(graph_plugin.ptr(), "update_node", r_node);
    undo_redo->add_undo_method(graph_plugin.ptr(), "update_node", r_node);
    undo_redo->commit_action();
}

void HoodieEditorPlugin::_delete_nodes(const List<id_t> &p_nodes) {
    List<HoodieMesh::Connection> conns;
    hoodie_mesh->get_node_connections(&conns);

    EditorUndoRedoManager *undo_redo = get_undo_redo();

    for (const id_t &F : p_nodes) {
        Ref<HoodieNode> node = hoodie_mesh->get_node(F);

        undo_redo->add_do_method(hoodie_mesh.ptr(), "remove_node", F);
        undo_redo->add_do_method(graph_plugin.ptr(), "remove_node", F, false);
        undo_redo->add_undo_method(hoodie_mesh.ptr(), "add_node", node, hoodie_mesh->get_node_position(F), F);
        undo_redo->add_undo_method(graph_plugin.ptr(), "add_node", F, false);
    }

    for (const id_t &F : p_nodes) {
        for (const HoodieMesh::Connection &E : conns) {
            if (E.l_node == F || E.r_node == F) {
                undo_redo->add_do_method(graph_plugin.ptr(), "disconnect_nodes", E.l_node, E.l_port, E.r_node, E.r_port);
            }
        }
    }

    List<HoodieMesh::Connection> used_conns;
    for (const id_t &F : p_nodes) {
        for (const HoodieMesh::Connection &E : conns) {
            if (E.l_node == F || E.r_node == F) {
                bool cancel = false;
                for (List<HoodieMesh::Connection>::Element *R = used_conns.front(); R; R = R->next()) {
                    if (R->get().l_node == E.l_node && R->get().l_port == E.l_port && R->get().r_node == E.r_node && R->get().r_port == E.r_port) {
                        cancel = true; // to avoid ERR_ALREADY_EXISTS warning
                        break;
                    }
                }
                if (!cancel) {
                    undo_redo->add_undo_method(hoodie_mesh.ptr(), "connect_nodes", E.l_node, E.l_port, E.r_node, E.r_port);
                    undo_redo->add_undo_method(graph_plugin.ptr(), "connect_nodes", E.l_node, E.l_port, E.r_node, E.r_port);
                    used_conns.push_back(E);
                }
            }
        }
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
            graph_edit->connect("connection_request", callable_mp(this, &HoodieEditorPlugin::_connection_request), CONNECT_DEFERRED);
            graph_edit->connect("disconnection_request", callable_mp(this, &HoodieEditorPlugin::_disconnection_request), CONNECT_DEFERRED);
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

    add_options.push_back(AddOption("Input Value", "Input/Constant", "HNInputValue"));

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