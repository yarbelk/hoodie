#include "hoodie_variant.h"

using namespace godot;

void HoodieVariant::clear() {
    value.clear();
}

HashMap<String, String> HoodieVariant::populate_tab_inspector() const {
    HashMap<String, String> tabs;

    switch (value.get_type())
    {
    case Variant::ARRAY:
        {
            tabs[""] = array_to_string(value);
        }
        break;
    default:
        {
            tabs[""] = variant_to_string(value);
        }
        break;
    }

    return tabs;
}