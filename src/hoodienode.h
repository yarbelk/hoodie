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

        NodeInfo() {}
        NodeInfo(String p_name, String p_description) : name(p_name), description(p_description) {}
    };

    struct Property {
        Variant::Type type;
        String hint;

        Property() {}
        Property(Variant::Type p_type, String p_hint) : type(p_type), hint(p_hint) {}
    };

    struct Socket {
        enum SocketIO { INPUT, OUTPUT };

        SocketIO socket_io;
        Variant::Type type;
        String name;
        String description;

        Socket() {}
        Socket(SocketIO p_socket_io, Variant::Type p_type, String p_name, String p_description)
            : socket_io(p_socket_io),
              type(p_type),
              name(p_name),
              description(p_description) {}
    };

public:
    enum ProcessStatus {
		PENDING, // all nodes are cleared to this before we update our mesh
		INPROGRESS, // a node gets this status when we are in the middle of updating it, helps detect cyclic relationships
		UNCHANGED, // a node gets this status once we finish updating and find the node unchanged
		CHANGED // a node gets this status once we finish updating at its contents has changed
    };

private:
    NodeInfo node_info;
    Property property;
    Vector<Socket> input_sockets;
    Vector<Socket> output_sockets;

    Vector2 position;

    ProcessStatus status;
    bool dirty = false;

    void mark_dirty();

protected:
    static void _bind_methods();

public:
    void set_node_info(String p_name, String p_description);
    void set_node_name(String p_name);
    String get_node_name() const;
    void set_node_description(String p_description);
    String get_node_description() const;

    virtual void construct_node_info();

    void set_position(Vector2 p_pos);
    Vector2 get_position() const;
    void set_status(ProcessStatus p_status);
    ProcessStatus get_status() const;

    // Property stuff
    void set_property(Property p_property);
    Variant::Type get_property_type() const;
    String get_property_hint() const;
    virtual void construct_property();
    // virtual void set_input(Variant p_input);
    // virtual Variant get_input();

    void add_socket(Socket &p_socket);
    Vector<Socket> get_input_sockets() const;
    Vector<Socket> get_output_sockets() const;

    virtual void construct_sockets();
    
    virtual bool update(const Array &p_inputs);

    HoodieNode();
};
    
} // namespace godot

#endif // HOODIE_HOODIENODE_H
