#pragma once
#include "Tree.hpp"
#include <set>
#include <algorithm>
#include <iostream>
#include <queue>
#include "FixedSizePQ.cpp"
#include <fstream>

void Tree::addNode(const std::string& name, int id, int dueTime, double processTime) {
    if(!nodes.count(name)) {
        nodes.emplace(name, std::make_shared<Node>(name, id, dueTime, processTime));
    } else {
        nodes[name]->dueTime = dueTime;
    }
}

void Tree::addEdge(const std::vector<std::string>& edge) {
    nodes[edge[0]]->children.push_back(nodes[edge[1]].get());
    nodes[edge[1]]->dependent.push_back(nodes[edge[0]].get());
}

void Tree::findRoots() {
    std::unordered_set<std::string> seen;
    for(auto it = nodes.begin(); it != nodes.end(); it++) {
        auto node = it->second.get();
        for(auto child : node->children) {
            seen.insert(child->name);
        }
    }
    for(auto it = nodes.begin(); it != nodes.end(); it++) {
        if(!seen.count(it->first)) {
            roots.push_back(it->second.get());
        }
    }
}

double Tree::shortestPossTime() const {
    double totalTime = 0;
    for(auto it = nodes.begin(); it != nodes.end(); it++) {
        totalTime += it->second->processTime;
    }
    return totalTime;
}

template<typename T>
int SearchForSolution(T& solutions, double maxCost = 99999999, int iterationLimit = 999999) {
    int iterations = 0;
    std::size_t maxSz = 0;

    //should be size() but avoided implementing it for my FixedPQ 
    while(solutions.pqSize() && !(solutions.top().completed) && iterations < iterationLimit) {
        iterations++; 
        maxSz = maxSz > solutions.pqSize() ? maxSz : solutions.pqSize();
        auto bestSoln = solutions.top(); solutions.pop();

        for(auto node : bestSoln.availableNodes) {
            auto newSoln = bestSoln;
            newSoln.processNode(node);
            if(newSoln.currentTardiness < maxCost) {
                newSoln.maxSize = maxSz;
                solutions.push(newSoln);
            }
        }

    }
    return iterations;
}

template<typename T>
int SearchForSolutionPrint(std::ofstream& of, int globIts, T& solutions, double maxCost = 99999999, int iterationLimit = 999999) {
    int iterations = 0;
    std::size_t maxSz = 0;

    //should be size() but avoided implementing it for my FixedPQ 
    while(solutions.pqSize() && !(solutions.top().completed) && iterations < iterationLimit) {
        iterations++; 
        maxSz = maxSz > solutions.pqSize() ? maxSz : solutions.pqSize();
        auto bestSoln = solutions.top(); solutions.pop();
        of << bestSoln;
        of << "Iteration: " << iterations + globIts << '\n';
        for(auto node : bestSoln.availableNodes) {
            auto newSoln = bestSoln;
            newSoln.processNode(node);
            if(newSoln.currentTardiness < maxCost) {
                newSoln.maxSize = maxSz;
                solutions.push(newSoln);
            }
        }

    }
    return iterations;
}

Solution Tree::findSchedule() {
    if(roots.size() == 0) {
        findRoots();
        if(roots.size() == 0) {
            throw "No entry point available";
        }
    }

    Solution::totalNodes = nodes.size();

    auto cmp = [](const Solution& l, const Solution& r) {
        return l.currentTardiness <= r.currentTardiness;
    };
    FixedPQ<Solution, decltype(cmp)>  solutions(cmp);
    solutions.push(Solution{roots, shortestPossTime()});
    std::ofstream myfile;
    int iterations = SearchForSolution(solutions, 30000, 30000);
    auto bestSolution = solutions.top();

    if(!bestSolution.completed) {
        bestSolution.completeSchedule();
    }

    bestSolution.iterations = iterations;
    return bestSolution;
}

//had plans to make if statements constexpr but took it out cos of compiler warning cba to specify c++ version
// no point it being a template like this tbh
template<int n>
Solution Tree::findScheduleAdv() {
    if(roots.size() == 0) {
        findRoots();
        if(roots.size() == 0) {
            throw "No entry point available";
        }
    }

    Solution::totalNodes = nodes.size();
    int iterations = 0;

    auto cmp = [](const Solution& l, const Solution& r) {
        return l.currentTardiness/l.completedNodes.size() <= r.currentTardiness/r.completedNodes.size();
    }; 

    FixedPQ<Solution, decltype(cmp), 1000> solutions(cmp);
    FixedPQ<Solution, decltype(cmp), 1000> completeSolutions(cmp);

    Solution bestSolution;
    solutions.push(Solution{roots, shortestPossTime()});
    if (n == 1) {
        iterations = SearchForSolution(solutions);
        auto best = solutions.top();
        completeSolutions.push(best);
    } else if (n == 2) {
        while(completeSolutions.pqSize() != 1000) { 
            iterations += SearchForSolution(solutions);
            auto best = solutions.top(); solutions.pop();
            completeSolutions.push(best);
        }
    } else if (n == 3) {
        double maxCost = 999999;
        while(completeSolutions.pqSize() < 1000 && iterations < 30000) { 
            iterations += SearchForSolution(solutions, maxCost, 30000);
            if(solutions.pqSize() < 1) {
                break;
            }
            auto best = solutions.top(); solutions.pop();
            completeSolutions.push(best);
            maxCost = std::min(maxCost, best.currentTardiness);
        }
    } else if (n == 4) {
        double maxCost = 999999;
        while(completeSolutions.pqSize() < 1000 && iterations < 30000) { 
            iterations += SearchForSolution(solutions, maxCost, 100);
            if(solutions.pqSize() < 1) {
                break;
            }
            auto best = solutions.top(); solutions.pop();
            completeSolutions.push(best);
            maxCost = std::min(maxCost, best.currentTardiness);
        }
    }
    bestSolution = completeSolutions.top();
    bestSolution.iterations = iterations;
    if(!bestSolution.completed) {
        bestSolution.completeSchedule();
    }

    return bestSolution;
}

