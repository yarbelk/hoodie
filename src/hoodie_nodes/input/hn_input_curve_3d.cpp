#include "hn_input_curve_3d.h"

using namespace godot;

void HNInputCurve3D::_curve_changed() {
    mark_dirty();
}

void HNInputCurve3D::_process(const Array &p_inputs) {
    PackedVector3Array points;
    PackedVector3Array tangents;
    PackedVector3Array normals;
    PackedFloat32Array tilts;
    PackedFloat32Array lengths;
    PackedFloat32Array factors;

    points.resize(0);
    tangents.resize(0);
    normals.resize(0);
    tilts.resize(0);
    lengths.resize(0);
    factors.resize(0);

    packed_curve.clear();

    if (curve.is_valid()) {
        points = curve->get_baked_points();

        const int p_size = points.size();
        if (p_size == 0) {
            return;
        }

        normals = curve->get_baked_up_vectors();

        // Calculate tangents
        PackedVector3Array ts;
        if (points.size() < 2) {
            ts.push_back(normals[0]);
        } else {
            for (int i = 0; i < points.size(); i++)
            {
                Vector3 origin, next;
                origin = points[i];
                next = points[i == points.size() - 1 ? i-1 : i+1];
                Vector3 t = (next - origin).normalized();
                ts.push_back(t);
            }
        }
        tangents = ts;

        // TODO: implement normals

        tilts = curve->get_baked_tilts();

        // Length of the curve at that point (from the start).
        float curve_length = 0;
        lengths.push_back(curve_length);
        {
            Vector3 prev_pt = points[0];
            for (int i = 1; i < points.size(); i++) {
                Vector3 pt = points[i];
                curve_length += (pt - prev_pt).length();
                prev_pt = pt;

                lengths.push_back(curve_length);
            }
        }

        // Factors: float 0 to 1
        for (int i = 0; i < points.size(); i++) {
            factors.push_back((float)i / (p_size - 1));
        }
    }

    packed_curve.push_back(points);
    packed_curve.push_back(tangents);
    packed_curve.push_back(normals);
    packed_curve.push_back(tilts);
    packed_curve.push_back(lengths);
    packed_curve.push_back(factors);
}

String HNInputCurve3D::get_caption() const {
    return "Input Curve 3D";
}

int HNInputCurve3D::get_input_port_count() const {
    return 0;
}

HNInputCurve3D::PortType HNInputCurve3D::get_input_port_type(int p_port) const {
    return PortType::PORT_TYPE_SCALAR;
}

String HNInputCurve3D::get_input_port_name(int p_port) const {
    return "";
}

int HNInputCurve3D::get_output_port_count() const {
    return 1;
}

HNInputCurve3D::PortType HNInputCurve3D::get_output_port_type(int p_port) const {
    return PortType::PORT_TYPE_CURVE;
}

String HNInputCurve3D::get_output_port_name(int p_port) const {
    return "Curve3D";
}

int HNInputCurve3D::get_property_input_count() const {
    return 1;
}

Variant::Type HNInputCurve3D::get_property_input_type(vec_size_t p_prop) const {
    return Variant::OBJECT;
}

String HNInputCurve3D::get_property_input_hint(vec_size_t p_prop) const {
    return "Curve3D";
}

Variant HNInputCurve3D::get_property_input(vec_size_t p_port) const {
    if (curve.is_valid()) {
        return Variant(curve);
    }
    return Variant();
}

void HNInputCurve3D::set_property_input(vec_size_t p_prop, Variant p_input) {
    if (p_input.get_type() != Variant::OBJECT) {
        return;
    }

    Ref<Curve3D> new_curve = p_input;
    if (new_curve.is_null()) {
        return;
    } else if (new_curve->get_class() != "Curve3D") {
        return;
    }

    // Disconnect from the old...
    if (curve.is_valid()) {
        curve->disconnect("changed", callable_mp((HoodieNode*)this, &HNInputCurve3D::mark_dirty));
        curve->disconnect("changed", callable_mp((Object*)this, &HNInputCurve3D::emit_signal<>).bind("changed"));
    }

    // and update
    curve = new_curve;

    // Connect to the new
    if (curve.is_valid()) {
        curve->connect("changed", callable_mp((HoodieNode*)this, &HNInputCurve3D::mark_dirty));
        curve->connect("changed", callable_mp((Object*)this, &HNInputCurve3D::emit_signal<>).bind("changed"));
    }

    mark_dirty();
    emit_signal("changed");
}

const Variant HNInputCurve3D::get_output(int p_port) const {
    return Variant(packed_curve);
}