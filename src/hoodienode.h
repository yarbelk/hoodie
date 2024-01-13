#ifndef HOODIE_HOODIENODE_H
#define HOODIE_HOODIENODE_H

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/templates/vector.hpp>

namespace godot
{

class HoodieNode : public Resource {
    GDCLASS(HoodieNode, Resource)

protected:
    struct NodeInfo {
        String name;
        String description;
    };

    struct Property {
        Variant::Type type;
        String hint;

        Property(Variant::Type p_type, String p_hint)
            : type(p_type),
              hint(p_hint) {}
    };

    Property property;

    struct Socket {
        enum SocketIO { INPUT, OUTPUT };
        enum SocketType { ITEM, LIST };

        SocketIO socket_io;
        Variant::Type type;
        String name;
        String description;

        Socket(SocketIO p_socket_io, Variant::Type p_type, String p_name, String p_description)
            : socket_io(p_socket_io),
              type(p_type),
              name(p_name),
              description(p_description) {}
    };

    Vector<Socket> input_sockets;
    Vector<Socket> output_sockets;

public:
    enum ProcessStatus {
		PROCESS_STATUS_PENDING, // all nodes are cleared to this before we update our mesh
		PROCESS_STATUS_INPROGRESS, // a node gets this status when we are in the middle of updating it, helps detect cyclic relationships
		PROCESS_STATUS_UNCHANGED, // a node gets this status once we finish updating and find the node unchanged
		PROCESS_STATUS_CHANGED // a node gets this status once we finish updating at its contents has changed
    };

private:
    NodeInfo node_info;
    Vector2 position;
    ProcessStatus status;
    bool dirty = false;

    void mark_dirty();

protected:
    static void _bind_methods();

public:
    void set_node_info(String p_name, String p_description);
    virtual void construct_node_info();

    String get_node_name();
    String get_node_description();
    Vector2 get_position() const;
    void set_position(Vector2 p_pos);
    ProcessStatus get_status() const;
    void set_status(ProcessStatus p_status);

    // Property stuff
    void set_property(Property &p_property);
    virtual void construct_property();
    // virtual void set_input(Variant p_input);
    // virtual Variant get_input();

    void add_socket(Socket &p_socket);

    virtual void construct_sockets();
    
    Vector<Socket> get_input_sockets() const;
    Vector<Socket> get_output_sockets() const;

    virtual bool update();

    HoodieNode();
};
    
} // namespace godot

#endif // HOODIE_HOODIENODE_H
