#ifndef HOODIE_HOODIEARRAYMESH_H
#define HOODIE_HOODIEARRAYMESH_H

#include "hoodie_data.h"

namespace godot
{

class HoodieArrayMesh : public HoodieData {
    GDCLASS(HoodieArrayMesh, RefCounted)

public:
    Array array;

protected:
    static void _bind_methods();

public:
    void clear() override;

    Variant duplicate() override;

    HashMap<String, String> populate_tab_inspector() const override;

    static Ref<HoodieArrayMesh> create_reference(const Array &p_array);

    HoodieArrayMesh();
};

} // namespace godot

#endif // HOODIE_HOODIEARRAYMESH_H