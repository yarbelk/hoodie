#include "hoodie_data.h"

using namespace godot;

void HoodieData::_bind_methods() {
}

void HoodieData::clear() {
}

Variant HoodieData::duplicate() {
    return Variant();
}

HashMap<String, String> HoodieData::populate_tab_inspector() const {
    return HashMap<String, String>();
}

String HoodieData::variant_to_string(const Variant &v) {
    String s;

    switch (v.get_type()) {
        case Variant::Type::BOOL:
            {
                bool val = (bool)v;
                s = val ? "True" : "False";
            }
            break;
        case Variant::Type::INT:
            {
                int val = (int)v;
                s = itos(val);
            }
            break;
        case Variant::Type::STRING:
            {
                String val = (String)v;
                s = val;
            }
            break;
        case Variant::Type::FLOAT:
            {
                float f = (float)v;
                s = String::num(f, 3);
            }
            break;
        case Variant::Type::VECTOR4:
            {
                Vector4 vec = v;
                String vec_string = "( ";
                vec_string += String::num(vec.x, 3) + " , ";
                vec_string += String::num(vec.y, 3) + " , ";
                vec_string += String::num(vec.z, 3) + " , ";
                vec_string += String::num(vec.w, 3) + " )";
                s = vec_string;
            }
            break;
        case Variant::Type::VECTOR3:
            {
                Vector3 vec = v;
                String vec_string = "( ";
                vec_string += String::num(vec.x, 3) + " , ";
                vec_string += String::num(vec.y, 3) + " , ";
                vec_string += String::num(vec.z, 3) + " )";
                s = vec_string;
            }
            break;
        case Variant::Type::VECTOR2:
            {
                Vector2 vec = v;
                String vec_string = "( ";
                vec_string += String::num(vec.x, 3) + " , ";
                vec_string += String::num(vec.y, 3) + " )";
                s = vec_string;
            }
            break;
    }

    return s;
}

String HoodieData::array_to_string(const Array &p_a) {
    String s_array;

    for (int i = 0; i < p_a.size(); i++) {
        s_array += "[" + itos(i) + "] ";
        s_array += variant_to_string(p_a[i]) + "\n";
    }

    return s_array;
}

HoodieData::HoodieData() {
}