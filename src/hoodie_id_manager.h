#ifndef HOODIE_HOODIEIDMANAGER_H
#define HOODIE_HOODIEIDMANAGER_H    

#include <queue>
// #include <type_traits>

namespace godot {
    
// TODO: when you reload the file in godot, you need to take into account all the already created nodes
// and their IDs...

template <typename T>
class HoodieIdManager {

    T nextID;
    std::queue<T> freeIDs;

public:
    void reset();
    T generateID();
    void releaseID(T p_id);

    HoodieIdManager();
};

}

#endif // HOODIE_HOODIEIDMANAGER_H
