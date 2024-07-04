#ifndef HOODIE_HOODIEVARIANT_H
#define HOODIE_HOODIEVARIANT_H

#include "hoodie_data.h"

namespace godot
{

class HoodieVariant : public HoodieData {
    GDCLASS(HoodieVariant, RefCounted)

public:
    Variant value;

protected:
    static void _bind_methods();

public:
    void clear() override;
    HashMap<String, String> populate_tab_inspector() const override;
};

} // namespace godot

#endif // HOODIE_HOODIEVARIANT_H