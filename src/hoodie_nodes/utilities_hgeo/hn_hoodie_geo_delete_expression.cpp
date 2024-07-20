#include "hn_hoodie_geo_delete_expression.h"

#include <functional>
#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/classes/expression.hpp>

using namespace godot;

void HNHoodieGeoDeleteExpression::set_filter_expression(const String p_value) {
    filter_expression = p_value;
}

String HNHoodieGeoDeleteExpression::get_filter_expression() const {
    return filter_expression;
}

void HNHoodieGeoDeleteExpression::set_target(const Target p_value) {
    target = p_value;
}

HNHoodieGeoDeleteExpression::Target HNHoodieGeoDeleteExpression::get_target() const {
    return target;
}

void HNHoodieGeoDeleteExpression::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_filter_expression", "value"), &HNHoodieGeoDeleteExpression::set_filter_expression);
    ClassDB::bind_method(D_METHOD("get_filter_expression"), &HNHoodieGeoDeleteExpression::get_filter_expression);
    ClassDB::bind_method(D_METHOD("set_target", "value"), &HNHoodieGeoDeleteExpression::set_target);
    ClassDB::bind_method(D_METHOD("get_target"), &HNHoodieGeoDeleteExpression::get_target);

    ADD_PROPERTY(PropertyInfo(Variant::STRING, "Filter", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NO_EDITOR), "set_filter_expression", "get_filter_expression");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "Operation", PROPERTY_HINT_ENUM, "Points,PackedPoints", PROPERTY_USAGE_NO_EDITOR), "set_target", "get_target");

    BIND_ENUM_CONSTANT(Target::Points);
    BIND_ENUM_CONSTANT(Target::PackedPoints);
}

void HNHoodieGeoDeleteExpression::_process(const Array &p_inputs) {
    Ref<HoodieGeo> in_hgeo = p_inputs[0];

    if (in_hgeo.is_null()) { return; }

    Ref<Expression> filter;
    filter.instantiate();

    PackedStringArray filter_params;
    filter_params.push_back("i");
    filter_params.push_back("ptscount");
    for (auto attr : in_hgeo->attributes) {
        filter_params.push_back(attr.key);
    }

    Error f_error = filter->parse(filter_expression, filter_params);
    if (f_error != Error::OK) {
        UtilityFunctions::print("Filter parse NOT OK.");
        return;
    }

    Vector<PackedVector3Array> pts_packs;
    Vector<HashMap<String, Array>> attr_packs;

    Vector<PackedVector3Array> out_pts_packs;
    Vector<HashMap<String, Array>> out_attr_packs;
    Vector<HoodieGeo::Primitive> out_primitives;

    Ref<HoodieGeo> out_hgeo = in_hgeo->duplicate();

    if (target == Target::Points) {
        pts_packs.push_back(in_hgeo->points.duplicate());
        attr_packs.push_back(in_hgeo->duplicate_attributes());
    } else if (target == Target::PackedPoints) {
        pts_packs = in_hgeo->pack_primitive_points();
        attr_packs = in_hgeo->pack_primitive_attributes();
    }

    for (int prim = 0; prim < pts_packs.size(); prim++) {
        PackedVector3Array pts = pts_packs[prim];
        HashMap<String, Array> attributes = attr_packs[prim];

        PackedVector3Array out_pts;
        HashMap<String, Array> out_attributes;

        PackedInt32Array primitive_ids_to_delete;
        HashMap<int, int> ids_map;

        for (int i = 0; i < pts.size(); i++) {
            Array filter_values;
            filter_values.push_back(i);
            filter_values.push_back(pts.size());
            for (auto attr : in_hgeo->attributes) {
                filter_values.push_back(attr.value[i]);
            }

            Variant filter_ret = filter->execute(filter_values);

            if (filter->has_execute_failed()) {
                UtilityFunctions::print("Filter execution failed.");
                return;
            }

            if (!(bool)filter_ret) {
                // Don't delete, hence add to out values.
                out_pts.push_back(pts[i]);

                if (target == Target::Points) {
                    // This map will be used later to update primitives vertices id.
                    ids_map[i] = out_pts.size() - 1;
                }
                
                for (auto attr : attributes) {
                    out_attributes[attr.key].append(attr.value[i]);
                }
            } else {
                primitive_ids_to_delete.push_back(i);
            }
        }

        // Delete primitive vertices
        if (target == Target::Points) {
            for (int p = 0; p < out_hgeo->primitives.size(); p++) {
                PackedInt32Array new_verts;
                for (int i = 0; i < out_hgeo->primitives[p].vertices.size(); i++) {
                    bool found = false;
                    for (int id : primitive_ids_to_delete) {
                        if (out_hgeo->primitives[p].vertices[i] == id) {
                            found = true;
                            break;
                        }
                    }

                    if (!found) {
                        // Take the id from the map, since deletion messes up the id order.
                        new_verts.push_back(ids_map[out_hgeo->primitives[p].vertices[i]]);
                    }
                }

                out_primitives.push_back(new_verts);
            }
        }

        out_attr_packs.push_back(out_attributes);
        out_pts_packs.push_back(out_pts);
    }

    if (target == Target::Points) {
        out_hgeo->attributes = out_attr_packs[0];
        out_hgeo->points = out_pts_packs[0];
        out_hgeo->primitives = out_primitives;
    } else if (target == Target::PackedPoints) {
        out_hgeo->unpack_primitive_points(out_pts_packs);
        out_hgeo->unpack_primitive_attributes(out_attr_packs);
    }

    set_output(0, out_hgeo);
}

String HNHoodieGeoDeleteExpression::get_caption() const {
    return "HGeo Delete Expr";
}

int HNHoodieGeoDeleteExpression::get_input_port_count() const {
    return 1;
}

HoodieNode::PortType HNHoodieGeoDeleteExpression::get_input_port_type(int p_port) const {
    switch (p_port) {
        case 0:
            return PortType::PORT_TYPE_HGEO;
        default:
            return PortType::PORT_TYPE_SCALAR;
    }
}

String HNHoodieGeoDeleteExpression::get_input_port_name(int p_port) const {
    switch (p_port) {
        case 0:
            return "HGeo";
        default:
            return "Data";
    }
}

int HNHoodieGeoDeleteExpression::get_output_port_count() const {
    return 1;
}

HoodieNode::PortType HNHoodieGeoDeleteExpression::get_output_port_type(int p_port) const {
    return PortType::PORT_TYPE_HGEO;
}

String HNHoodieGeoDeleteExpression::get_output_port_name(int p_port) const {
    return "HGeo";
}

int HNHoodieGeoDeleteExpression::get_property_input_count() const {
    return 2;
}

Variant::Type HNHoodieGeoDeleteExpression::get_property_input_type(vec_size_t p_prop) const {
    switch (p_prop) {
        case 0:
            return Variant::STRING;
        case 1:
            return Variant::STRING;
        case 2:
            return Variant::INT;
        default:
            return Variant::INT;
    }
}

Variant HNHoodieGeoDeleteExpression::get_property_input(vec_size_t p_port) const {
    switch (p_port) {
        case 0:
            return Variant(filter_expression);
        case 1:
            return Variant(target);
        default:
            return Variant();
    }
}

void HNHoodieGeoDeleteExpression::set_property_input(vec_size_t p_prop, Variant p_input) {
    switch (p_prop) {
        case 0:
            filter_expression = (String)p_input;
            break;
        case 1:
            target = (Target)(int)p_input;
            break;
        default:
            return;
    }
}

Vector<StringName> HNHoodieGeoDeleteExpression::get_editable_properties() const {
    Vector<StringName> props;
    props.push_back("Filter");
    props.push_back("Operation");
    return props;
}

HashMap<StringName, String> HNHoodieGeoDeleteExpression::get_editable_properties_names() const {
    return HashMap<StringName, String>();
}