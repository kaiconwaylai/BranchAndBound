#pragma once
#include <unordered_map>
#include <memory>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include "Solution.hpp"
#include "Node.hpp"

class Tree {
public:
    void addEdge(const std::vector<std::string>& edge);
    void addNode(const std::string& name, int id, int dueTime, double processTime);
    Solution findSchedule();
    template<int n>
    Solution findScheduleAdv();

private:
    void findRoots();
    double shortestPossTime() const;
    double lowerBoundTime(std::vector<Node*> next) const;
    std::vector<Node*> roots = {};
    std::unordered_map<std::string, std::shared_ptr<Node>> nodes;
};