#include <unordered_map>
#include <memory>
#include <vector>
#include <string>
#include <unordered_set>
#include "Tree.hpp"
#include <set>
#include <algorithm>
#include <iostream>
#include <queue>
#include <array>

template<typename T, typename Cmp, int size = 99999999>
class FixedPQ {
public:
    void push(T item) {
        pq.insert(item);

        if(pq.size() > size) {
            pq.erase(prev(pq.end()));
        }
    }

    T top() const {
        return *pq.begin();
    }

    void pop() {
        pq.erase(pq.begin());
    }

    size_t pqSize() {
        return pq.size();
    }

    std::set<T,Cmp>& getContainer() {
        return pq;
    }

    FixedPQ(Cmp func) : pq(func) {};


private:
    std::set<T,Cmp> pq;
};