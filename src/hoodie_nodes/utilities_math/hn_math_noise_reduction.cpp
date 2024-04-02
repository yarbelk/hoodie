#include "hn_math_noise_reduction.h"

using namespace godot;

void HNMathNoiseReduction::_process(const Array &p_inputs) {
    // https://stackoverflow.com/questions/7811761/smoothing-a-2d-line-from-an-array-of-points

    out.clear();

    if (p_inputs.size() == 0) {
        return;
    }

    Array values_arr = p_inputs[0].duplicate();
    PackedFloat32Array values = values_arr;

    Array severity_arr = p_inputs[1].duplicate();
    int severity = 2;
    if (severity_arr.size() > 0) {
        severity = MAX(1, (int)severity_arr[0]);
    }

    bool loop = true;

    // Calculate ping-pong weight values (0->0.5, ..., 0.5->1, ..., 1->0.5)
    PackedFloat32Array weights;
    weights.resize(severity * 2 + 1);
    float weights_sum = 0;
    for (int i = 0; i < weights.size(); i++) {
        float percent = i / (float)(weights.size() - 1);
        weights[i] = 1 - (Math::abs(2 * percent - 1)) * 0.5;
        weights_sum += weights[i];
    }

    for (int i = 0; i < values.size(); i++) {
        // Loop index to avoid out of bounds.
        // int start = (((i - severity) % values.size()) + values.size()) % values.size();
        // int end = (((i + severity) % values.size()) + values.size()) % values.size();

        int start = i - severity;
        int end = i + severity;

        float sum = 0;
        float weighted_sum = 0;
        for (int j = start; j < end; j++) {
            int id = (((j) % values.size()) + values.size()) % values.size();
            sum += values[id];
            // weighted_sum += values[] * weights[j - start];
        }

        float avg = sum / severity * 2;
        // float weightedAverage = (weightedSum) / (weightsSum);
        out.push_back(avg);
    }
}

String HNMathNoiseReduction::get_caption() const {
    return "Math Noise Reduction";
}

int HNMathNoiseReduction::get_input_port_count() const {
    return 2;
}

HoodieNode::PortType HNMathNoiseReduction::get_input_port_type(int p_port) const {
    switch (p_port) {
        case 0:
            return PortType::PORT_TYPE_SCALAR;
        case 1:
            return PortType::PORT_TYPE_SCALAR_UINT;
    }

    return PortType::PORT_TYPE_SCALAR;
}

String HNMathNoiseReduction::get_input_port_name(int p_port) const {
    switch (p_port) {
        case 0:
            return "Values";
        case 1:
            return "Severity";
    }

    return "Value";
}

int HNMathNoiseReduction::get_output_port_count() const {
    return 1;
}

HoodieNode::PortType HNMathNoiseReduction::get_output_port_type(int p_port) const {
    return PortType::PORT_TYPE_SCALAR;
}

String HNMathNoiseReduction::get_output_port_name(int p_port) const {
    return "Values";
}

const Variant HNMathNoiseReduction::get_output(int p_port) const {
    if (p_port == 0) {
        return Variant(out);
    }

    return Variant();
}
