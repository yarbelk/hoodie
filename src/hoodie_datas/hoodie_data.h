#ifndef HOODIE_HOODIEDATA_H
#define HOODIE_HOODIEDATA_H

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/templates/hash_map.hpp>

namespace godot
{

// Data transferred between nodes in the graph.
class HoodieData : public RefCounted {
    GDCLASS(HoodieData, RefCounted)

protected:
    static void _bind_methods();

public:
    virtual void clear();

    virtual HashMap<String, String> populate_tab_inspector() const;

    static String variant_to_string(const Variant &p_v);
    static String array_to_string(const Array &p_a);

    HoodieData();
};

} // namespace godot

#endif // HOODIE_HOODIEDATA_H