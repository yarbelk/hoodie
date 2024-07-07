#include "hn_subdivision_curve.h"

using namespace godot;

void HNSubdivisionCurve::set_algorithm(const SubdivisionAlgorithm p_value) {
    if (algorithm != p_value) {
        algorithm = p_value;
    }
}

HNSubdivisionCurve::SubdivisionAlgorithm HNSubdivisionCurve::get_algorithm() const {
    return algorithm;
}

void HNSubdivisionCurve::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_algorithm", "value"), &HNSubdivisionCurve::set_algorithm);
    ClassDB::bind_method(D_METHOD("get_algorithm"), &HNSubdivisionCurve::get_algorithm);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "Algorithm", PROPERTY_HINT_ENUM, "Deslauriers_Dubuc", PROPERTY_USAGE_NO_EDITOR), "set_algorithm", "get_algorithm");
}

void HNSubdivisionCurve::_process(const Array &p_inputs) {
    Ref<HoodieGeo> in_hgeo;
    int in_step = 1;

    in_hgeo = p_inputs[0];

    {
        Array a = p_inputs[1];
        in_step = Math::min((int)a[0], 4);
    }

    // Pack points of the primitives
    TypedArray<PackedVector3Array> points_group;
    TypedArray<PackedVector3Array> new_points_group;

    // Pack points from primitives
    points_group = in_hgeo->pack_primitive_points();

    if (get_algorithm() == Deslauriers_Dubuc) {
        for (int s = 0; s < in_step; s++) {
            new_points_group.clear();
            for (int i = 0; i < points_group.size(); i++) {
                PackedVector3Array points = points_group[i];
                // TODO: const PackedVector3Array points = points_group[i];

                PackedVector3Array new_points;
                for (int p = 0; p < points.size() - 1; p++) {
                    new_points.push_back(points[p]);

                    // TODO: implement closed curve by checking if the primitive verts last and first indices are equal.
                    Vector3 a, b, c, d;
                    a = (p - 1) < 0 ? points[0] : points[p - 1]; 
                    b = points[p];
                    c = (p + 1) > (points.size() - 1) ? points[points.size() - 1] : points[p + 1];
                    d = (p + 2) > (points.size() - 1) ? points[points.size() - 1] : points[p + 2];
                    Vector3 new_p;
                    new_p = (-a + 9 * b + 9 * c - d) / 16;
                    new_points.push_back(new_p);
                }

                if (points.size() > 0) {
                    new_points.push_back(points[points.size() - 1]);
                }

                new_points_group.push_back(new_points);
            }

            // Set values for the next step.
            points_group = new_points_group.duplicate(true);
        }
    }

    UtilityFunctions::print("New points group size: " + itos(new_points_group.size()));
    for (int i = 0; i < new_points_group.size(); i++) {
        PackedVector3Array a = new_points_group[i];
        UtilityFunctions::print("npg[" + itos(i) + "]: " + itos(a.size()));
    }

    Ref<HoodieGeo> out_hgeo;
    out_hgeo.instantiate();
    out_hgeo->unpack_primitive_points(new_points_group);

    set_output(0, out_hgeo);
}

String HNSubdivisionCurve::get_caption() const {
    return "Subdivision Curve";
}

int HNSubdivisionCurve::get_input_port_count() const {
    return 2;
}

HoodieNode::PortType HNSubdivisionCurve::get_input_port_type(int p_port) const {
    switch (p_port) {
        case 0:
            return PortType::PORT_TYPE_HGEO;
        case 1:
            return PortType::PORT_TYPE_SCALAR_UINT;
        default:
            return PortType::PORT_TYPE_SCALAR;
    }
}

String HNSubdivisionCurve::get_input_port_name(int p_port) const {
    switch (p_port) {
        case 0:
            return "HGeo";
        case 1:
            return "Step";
        default:
            return "";
    }
}

int HNSubdivisionCurve::get_output_port_count() const {
    return 1;
}

HoodieNode::PortType HNSubdivisionCurve::get_output_port_type(int p_port) const {
    return PortType::PORT_TYPE_HGEO;
}

String HNSubdivisionCurve::get_output_port_name(int p_port) const {
    return "HGeo";
}

int HNSubdivisionCurve::get_property_input_count() const {
    return 2;
}

Variant::Type HNSubdivisionCurve::get_property_input_type(vec_size_t p_prop) const {
    return Variant::INT;
}

Variant HNSubdivisionCurve::get_property_input(vec_size_t p_port) const {
    switch (p_port) {
        case 0:
            return Variant(algorithm);
        default:
            return Variant();
    }
}

void HNSubdivisionCurve::set_property_input(vec_size_t p_prop, Variant p_input) {
    algorithm = (SubdivisionAlgorithm)(int)p_input;
}

Vector<StringName> HNSubdivisionCurve::get_editable_properties() const {
    Vector<StringName> props;
    props.push_back("Algorithm");
    // TODO: VisualShaderNodeIntParameter::get_editable_properties()
    return props;
}

HashMap<StringName, String> HNSubdivisionCurve::get_editable_properties_names() const {
    return HashMap<StringName, String>();
}