#ifndef HOODIE_HOODIENODE_H
#define HOODIE_HOODIENODE_H

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/templates/vector.hpp>

namespace godot
{

class HoodieNode : public Resource {
    GDCLASS(HoodieNode, Resource)
    friend class HoodieGraphPlugin;
    friend class HoodieEditorPlugin;
    friend class HoodieMesh;

    // typedef uint32_t id_t;
    typedef int id_t;

protected:
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
    enum PortType {
		PORT_TYPE_SCALAR,
		PORT_TYPE_SCALAR_INT,
		PORT_TYPE_SCALAR_UINT,
		PORT_TYPE_VECTOR_2D,
		PORT_TYPE_VECTOR_3D,
		PORT_TYPE_VECTOR_4D,
		PORT_TYPE_BOOLEAN,
        PORT_TYPE_ARRAY,
        PORT_TYPE_MAX,
    };

    enum ProcessStatus {
		PENDING, // all nodes are cleared to this before we update our mesh
		INPROGRESS, // a node gets this status when we are in the middle of updating it, helps detect cyclic relationships
		UNCHANGED, // a node gets this status once we finish updating and find the node unchanged
		CHANGED, // a node gets this status once we finish updating at its contents has changed
    };

private:
    Property property;
    Vector<Socket> input_sockets;
    Vector<Socket> output_sockets;

    ProcessStatus status;
    bool dirty = false;

    void mark_dirty();

protected:
    static void _bind_methods();

public:
    void set_status(const ProcessStatus &p_status);
    ProcessStatus get_status() const;

    // Property stuff
    void set_property(const Property &p_property);
    Variant::Type get_property_type() const;
    String get_property_hint() const;
    virtual void construct_property();
    // virtual void set_input(Variant p_input);
    // virtual Variant get_input();

    // void add_socket(Socket &p_socket);
    // Vector<Socket> get_input_sockets() const;
    // Vector<Socket> get_output_sockets() const;

    // virtual void construct_sockets();
    
    virtual bool update(bool p_inputs_updated, const Array &p_inputs);

    virtual void _process(const Array &p_inputs);

    virtual String get_caption() const;

	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

    virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

    virtual const Variant get_output(int p_port) const;

    HoodieNode();
};
    
} // namespace godot

#endif // HOODIE_HOODIENODE_H
