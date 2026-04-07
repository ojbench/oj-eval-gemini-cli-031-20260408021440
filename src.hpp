#ifndef PYLIST_H
#define PYLIST_H

#include <iostream>
#include <vector>
#include <memory>

class pylist {
private:
    bool is_int;
    int int_val;
    std::shared_ptr<std::vector<pylist>> list_val;

public:
    pylist() : is_int(false), int_val(0), list_val(std::make_shared<std::vector<pylist>>()) {}
    
    pylist(int v) : is_int(true), int_val(v), list_val(nullptr) {}

    void append(const pylist &x) {
        if (!is_int && list_val) {
            list_val->push_back(x);
        }
    }

    pylist pop() {
        if (!is_int && list_val && !list_val->empty()) {
            pylist back = list_val->back();
            list_val->pop_back();
            return back;
        }
        return pylist();
    }

    pylist &operator[](size_t i) {
        return (*list_val)[i];
    }

    const pylist &operator[](size_t i) const {
        return (*list_val)[i];
    }

    operator int() const {
        return int_val;
    }

    std::ostream &print(std::ostream &os, std::vector<const std::vector<pylist>*>& visited) const {
        if (is_int) {
            os << int_val;
        } else {
            for (auto ptr : visited) {
                if (ptr == list_val.get()) {
                    os << "[...]";
                    return os;
                }
            }
            visited.push_back(list_val.get());
            os << "[";
            for (size_t i = 0; i < list_val->size(); ++i) {
                if (i > 0) os << ", ";
                (*list_val)[i].print(os, visited);
            }
            os << "]";
            visited.pop_back();
        }
        return os;
    }

    friend std::ostream &operator<<(std::ostream &os, const pylist &ls) {
        std::vector<const std::vector<pylist>*> visited;
        return ls.print(os, visited);
    }
};

#endif //PYLIST_H
