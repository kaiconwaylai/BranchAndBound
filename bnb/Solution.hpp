#pragma once
#include <unordered_map>
#include <memory>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include "Node.hpp"

struct Solution {
    std::vector<Node*> availableNodes = {};
    std::vector<Node*> completedNodes = {};

    double currentTime = 0;
    double currentTardiness = 0;
    bool completed = false;
    int iterations = 0;
    int maxSize;
    static int totalNodes;

    bool checkDependents(Node* node) const;
    void processNode(Node* node);
    void completeSchedule();
    std::vector<int> getSchedule() const;
    friend std::ostream& operator<<(std::ostream& os, Solution& schedule) {
        os << "Cost: " << schedule.currentTardiness << '\n';
        os << "Max queue size: " << schedule.maxSize << '\n';
        os << "Current Iterations: " << schedule.iterations << '\n';
        os << "Proposed Schedule: ";

        std::vector<int> proposedOrder = schedule.getSchedule();
        for(int i = 1; i < proposedOrder.size(); i++) {
            os << proposedOrder[i-1] << ",";
        }
        if(proposedOrder.size() > 0)
            os << proposedOrder.back();
        os << '\n';
    }

    Solution() = default;
    Solution(std::vector<Node*> aN, double cT) : availableNodes(aN.begin(), aN.end()), currentTime(cT) {};
    Solution(const Solution& sln) = default;
};

int Solution::totalNodes = 0;