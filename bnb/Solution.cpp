#include "Solution.hpp"

bool Solution::checkDependents(Node* node) const {
    for(auto dN : node->dependent) {
        if(std::find(completedNodes.begin(), completedNodes.end(), dN) == completedNodes.end()) {
            return false;
        }
    }
    return true;
}

void Solution::processNode(Node* node) {
    completedNodes.push_back(node);
    availableNodes.erase(std::find(availableNodes.begin(), availableNodes.end(), node));
    
    for(auto child : node->children) {
        if (std::find(availableNodes.begin(), availableNodes.end(), child) == availableNodes.end() 
            && std::find(completedNodes.begin(), completedNodes.end(), child) == completedNodes.end()
            && checkDependents(child)) {
            availableNodes.push_back(child);
        }
    }
    currentTardiness += std::max(0.0, currentTime - node->dueTime);
    currentTime -= node->processTime;

    completed = completedNodes.size() == totalNodes;
}

void Solution::completeSchedule() {
    auto cmp = [](Node* l, Node* r) {
        return l->dueTime > r->dueTime;
    };
    while(!completed) {
        std::sort(std::begin(availableNodes), std::end(availableNodes), cmp);
        for(auto node : availableNodes) {
            if(checkDependents(node)) {
                processNode(node);
                break;
            }
        }
    }
}

std::vector<int> Solution::getSchedule() const {
    std::vector<int> proposedOrder;
    for(auto node : completedNodes) {
        proposedOrder.push_back(node->id);
    }
    std::reverse(std::begin(proposedOrder), std::end(proposedOrder));
    return proposedOrder;
}
