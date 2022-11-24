#pragma once
#include <vector>
#include <string>

struct Node {
    Node(std::string nm, int id, int dT, double pT) : name(nm), id(id), dueTime(dT), processTime(pT) {}
    std::string name;
    int id;
    double processTime;
    int dueTime;
    std::vector<Node*> children;
    std::vector<Node*> dependent;
};
