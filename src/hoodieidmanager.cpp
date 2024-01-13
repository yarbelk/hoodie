#include "hoodieidmanager.h"
#include <iostream>
#include <limits>

using namespace godot;

template <typename T>
HoodieIdManager<T>::HoodieIdManager() : nextID(0) {
    static_assert(std::is_integral_v<T> && std::is_arithmetic_v<T>, "T must be an integral arithmetic type");
}

template <typename T>
void HoodieIdManager<T>::reset() {
    nextID = 0;
    std::queue<T> empty;
    std::swap(freeIDs, empty);
}

template <typename T>
T HoodieIdManager<T>::generateID() {
    if (nextID == std::numeric_limits<T>::max()) {
            // Handle the case when the maximum ID is reached.
            // You can throw an exception, reset to 0, or take other appropriate action.
            std::cerr << "Maximum ID reached. Resetting to 0." << std::endl;
            nextID = 0;
    }

    if (freeIDs.empty()) {
        return nextID++;
    } else {
        T id = freeIDs.front();
        freeIDs.pop();
        return id;
    }
}

template <typename T>
void HoodieIdManager<T>::releaseID(T p_id) {
    freeIDs.push(p_id);
}

template class HoodieIdManager<uint32_t>;