#ifndef HOODIE_HOODIEEDITORPLUGIN_H
#define HOODIE_HOODIEEDITORPLUGIN_H

#include "hoodie_mesh.h"
#include "godot_cpp/classes/editor_plugin.hpp"
#include "godot_cpp/classes/h_split_container.hpp"
#include "godot_cpp/classes/v_box_container.hpp"
#include "godot_cpp/classes/h_box_container.hpp"
#include "godot_cpp/classes/scroll_container.hpp"
#include "godot_cpp/classes/menu_button.hpp"
#include "godot_cpp/classes/tab_container.hpp"
#include "godot_cpp/classes/tab_bar.hpp"
#include "godot_cpp/classes/popup_menu.hpp"
#include "godot_cpp/classes/label.hpp"
#include "godot_cpp/classes/graph_edit.hpp"
#include "godot_cpp/classes/graph_node.hpp"
#include "godot_cpp/classes/button.hpp"
#include "godot_cpp/classes/line_edit.hpp"
#include "godot_cpp/classes/spin_box.hpp"
#include "godot_cpp/classes/check_button.hpp"
#include "godot_cpp/classes/editor_spin_slider.hpp"
#include "godot_cpp/classes/editor_property.hpp"
#include "godot_cpp/classes/editor_inspector.hpp"

namespace godot
{

class HoodieEditorPlugin;

class HoodieNodePlugin : public RefCounted {
    GDCLASS(HoodieNodePlugin, RefCounted);

protected:
    HoodieEditorPlugin *hmeditor = nullptr;

protected:
    static void _bind_methods();

    // TODO: GDVIRTUAL2RC(Object *, _create_editor, Ref<Resource>, Ref<VisualShaderNode>)

public:
    void set_editor(HoodieEditorPlugin *p_editor);
    virtual Control *create_editor(const Ref<Resource> &p_parent_resoruce, const Ref<HoodieNode> &p_node);
};

class HoodieGraphPlugin : public RefCounted {
    GDCLASS(HoodieGraphPlugin, RefCounted);

    typedef HoodieNode::id_t id_t;
    typedef HoodieNode::vec_size_t vec_size_t;

private:
    HoodieEditorPlugin *editor = nullptr;

    struct Link {
        HoodieNode *hoodie_node = nullptr;
        GraphElement *graph_element = nullptr;
        HashMap<vec_size_t, Range *> ranges; 
    };

    Ref<HoodieMesh> hoodie_mesh;
    HashMap<id_t, Link> links;
    List<HoodieMesh::Connection> connections;

protected:
    static void _bind_methods();

public:
    void set_editor(HoodieEditorPlugin *p_editor);
    void register_hoodie_mesh(HoodieMesh *p_hoodie_mesh);
    void set_connections(const List<HoodieMesh::Connection> &p_connections);
    void register_link(id_t p_id, HoodieNode *p_hoodie_node, GraphElement *p_graph_element);
    void clear_links();
    void update_node(id_t p_id);
    void update_node_deferred(id_t p_id);
    void add_node(id_t p_id, bool p_just_update);
    void remove_node(id_t p_id, bool p_just_update);
    void connect_nodes(id_t p_l_node, vec_size_t p_l_port, id_t p_r_node, vec_size_t p_r_port);
    void disconnect_nodes(id_t p_l_node, vec_size_t p_l_port, id_t p_r_node, vec_size_t p_r_port);
    void set_node_position(id_t p_id, const Vector2 &p_position);

    void _on_range_value_changed(double p_val, id_t p_id, vec_size_t p_port_id);
    // Used when using editor spin sliders to update a vector input property (e.g. HNInputVector3D)
    void _on_vector_range_value_changed(double p_val, id_t p_id, vec_size_t p_port_id, int p_xyzw);

    HoodieGraphPlugin();
    ~HoodieGraphPlugin();
};

class HoodieControl : public VBoxContainer {
    GDCLASS(HoodieControl, VBoxContainer);

    friend class HoodieGraphPlugin;
    friend class HoodieEditorPlugin;

    typedef HoodieMesh::id_t id_t;
    typedef HoodieMesh::vec_size_t vec_size_t;

    HoodieEditorPlugin *editor;

    HSplitContainer *main_split = nullptr;
    MenuButton *file_menu = nullptr;
    MenuButton *options_menu = nullptr;
    Button *lock_button = nullptr;
    TabContainer *hn_inspector = nullptr;
    GraphEdit *graph_edit = nullptr;
    MenuButton *add_node = nullptr;
    PopupMenu *add_popup = nullptr;

    bool verbose_mode = false;
    bool lock_inspector = false;

    // Point2 saved_node_pos;
    // bool saved_node_pos_dirty = false;

    enum {
        FILE_NEW,
        FILE_PRINTDEBUG,
        OPTIONS_VERBOSE,
    };

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

    void _on_popup_request(const Vector2 &p_position);
    void _menu_item_pressed(int index);
    void _on_lock_toggled(bool toggled_on);

    void _update_options_menu();

    void _node_selected(id_t p_node);
    void _node_deselected(id_t p_node);

	struct CopyItem {
		int id;
		Ref<HoodieNode> node;
		Vector2 position;
		Vector2 size;
		String group_inputs;
		String group_outputs;
		String expression;
		bool disabled = false;
	};

	void _dup_copy_nodes(List<CopyItem> &r_nodes, List<HoodieMesh::Connection> &r_connections);
	void _dup_paste_nodes(List<CopyItem> &r_items, const List<HoodieMesh::Connection> &p_connections, const Vector2 &p_offset, bool p_duplicate);

	void _duplicate_nodes();

	static Vector2 selection_center;
	static List<CopyItem> copy_items_buffer;
	static List<HoodieMesh::Connection> copy_connections_buffer;

	void _clear_copy_buffer();
	void _copy_nodes(bool p_cut);
	void _paste_nodes(bool p_use_custom_position = false, const Vector2 &p_custom_position = Vector2());

    void _populate_hoodie_node_tab_inspector(id_t p_node);
    void _depopulate_hoodie_node_tab_inspector();

protected:
    static void _bind_methods();
    void _notification(int what);

public:
    void set_editor(HoodieEditorPlugin *p_editor);

    HoodieControl();
};

class HoodieEditorPlugin : public EditorPlugin {
    GDCLASS(HoodieEditorPlugin, EditorPlugin);

    friend class HoodieGraphPlugin;
    friend class HoodieControl;

    typedef HoodieNode::id_t id_t;
    typedef HoodieMesh::vec_size_t vec_size_t;

    Ref<HoodieMesh> hoodie_mesh;

    HoodieControl *hoodie_control = nullptr;
    // HSplitContainer *main_split = nullptr;
    // MenuButton *file_menu = nullptr;
    // MenuButton *options_menu = nullptr;
    // Button *lock_button = nullptr;
    // TabContainer *hn_inspector = nullptr;
    // GraphEdit *graph_edit = nullptr;
    // MenuButton *add_node = nullptr;
    // PopupMenu *add_popup = nullptr;

    Point2 saved_node_pos;
    bool saved_node_pos_dirty = false;

    Button *button = nullptr;

    // void _window_changed(bool p_visible);

    void _update_nodes();
    void _update_graph();

    // Add a node to the HoodieMesh class
    void _add_node(int idx);

	struct DragOp {
		id_t node = 0;
		Vector2 from;
		Vector2 to;
	};
	List<DragOp> drag_buffer;
    bool drag_dirty = false;
	void _node_dragged(const Vector2 &p_from, const Vector2 &p_to, id_t p_node);
    void _nodes_dragged();
    bool updating = false;

	void _connection_request(const String &p_from, int p_from_index, const String &p_to, int p_to_index);
	void _disconnection_request(const String &p_from, int p_from_index, const String &p_to, int p_to_index);

    void _scroll_changed(const Vector2 &p_scroll);

    void _delete_nodes(const List<HoodieMesh::id_t> &p_nodes);
    void _delete_node_request(HoodieMesh::id_t p_node);
    void _delete_nodes_request(const TypedArray<StringName> &p_nodes);

    void _change_node_property(id_t p_id, vec_size_t p_prop_id, Variant p_val);

    // plugins purpose is for showing custom properties UI in hoodie graph nodes.
    Vector<Ref<HoodieNodePlugin>> plugins;
    Ref<HoodieGraphPlugin> graph_plugin;

protected:
    static void _bind_methods();
    void _notification(int what);

public:
    void add_plugin(const Ref<HoodieNodePlugin> &p_plugin);
    void remove_plugin(const Ref<HoodieNodePlugin> &p_plugin);

    HoodieGraphPlugin *get_graph_plugin() { return graph_plugin.ptr(); }

    // virtual String get_name() const override { return "Hoodie"; }
    virtual void _make_visible(bool visible) override;
	virtual void _edit(Object *object) override;
	virtual bool _handles(Object *object) const override;

	// virtual void _set_window_layout(const Ref<ConfigFile> &configuration);
	// virtual void _get_window_layout(const Ref<ConfigFile> &configuration);

	// virtual String _get_unsaved_status(const String &for_scene) const;
	// virtual void _save_external_data();
	// virtual void _apply_changes();

    // void add_graph_node(Ref<HoodieNode> &hoodie_node, const AddOption &option, id_t p_id, bool p_just_update);
    // void remove_graph_node(id_t p_id, bool p_just_update);

    // void edit(HoodieMesh *p_hoodie_mesh);

    void print_debug();

    HoodieEditorPlugin();
};

// A RefCounted that creates a Control
class HoodieNodePluginDefault : public HoodieNodePlugin {
    GDCLASS(HoodieNodePluginDefault, HoodieNodePlugin);

public:
    virtual Control *create_editor(const Ref<Resource> &p_parent_resource, const Ref<HoodieNode> &p_node) override;
};

class HoodieNodePluginInputEditor : public Label {
    GDCLASS(HoodieNodePluginInputEditor, Label)

    HoodieEditorPlugin *editor = nullptr;
    // TODO: Ref<HoodieNodeParameterRef> parameter_ref;

public:
    void _notification(int p_what);
    void setup(HoodieEditorPlugin *p_editor);

protected:
    static void _bind_methods();
};

class HoodieNodePluginDefaultEditor : public VBoxContainer {
    GDCLASS(HoodieNodePluginDefaultEditor, VBoxContainer);

    HoodieEditorPlugin *editor = nullptr;
    Ref<HoodieMesh> parent_resource;
    int node_id = 0;

protected:
    static void _bind_methods();

public:
    void _property_changed(const Variant &p_value, const String &p_property, Control *p_property_control, const String &p_field, bool p_changing);
    void _node_changed();
    void _resource_selected(const String &p_path, Ref<Resource> p_resource);
    void _open_inspector(Ref<Resource> p_resource);

    bool updating = false;
    Ref<HoodieNode> node;
    Vector<Control *> properties;
    Vector<Label *> prop_names;

    void _show_prop_names(bool p_show);
    void setup(HoodieEditorPlugin *p_editor, Ref<HoodieMesh> p_parent_resource, Vector<Control *> p_properties, const Vector<StringName> &p_names, const HashMap<StringName, String> &p_overrided_names, Ref<HoodieNode> p_node);
};

    
} // namespace godot

#endif // HOODIE_HOODIEEDITORPLUGIN_H
