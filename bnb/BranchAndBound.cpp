#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <chrono>
#include "Tree.hpp"
#include "Tree.cpp"
#include "Solution.cpp"

Solution getSchedule(Tree& tree, int option);

int main(int argc, char* argv[]) {

    if(argc < 2) {
        std::cout << "Need algorithm argument: [0-4]" << '\n';
        return -1;
    }

    std::vector<std::string> nodes = {"onnx_1", "muse_1", "emboss_1", "emboss_2", "blur_1", "emboss_3", "vii_1", "blur_2", "wave_1", "blur_3","blur_4", "emboss_4", "onnx_2", "onnx_3", "blur_5", "wave_2", "wave_3", "wave_4", "emboss_5", "onnx_4","emboss_6", "onnx_5", "vii_2", "blur_6", "night_1", "muse_2", "emboss_7", "onnx_6", "wave_5", "emboss_8","muse_3"};
    std::vector<int> dueTimes = {172, 82, 18, 61, 93, 71, 217, 295, 290, 287, 253, 307, 279, 73, 355, 34, 233, 77, 88, 122, 71, 181, 340, 141, 209, 217, 256, 144, 307, 329, 269};
    std::vector<std::vector<int>> edges = {{0, 30},{1, 0},{2, 7},{3, 2},{4, 1},{5, 15},{6, 5},{7, 6},{8, 7},{9, 8},{10, 4},{11, 4},{12, 11},{13, 12},{14, 10},{15, 14},{16, 15},{17, 16},{18, 17},{19, 18},{20, 17},{21, 20},{22, 21},{23, 4},{24, 23},{25, 24},{26, 25},{27, 25},{28, 27},{29, 3},{29, 9},{29, 13},{29, 19},{29, 22},{29, 26},{29, 28}};
    std::unordered_map<std::string, double> myProcessTimes = {{"vii", 21.4742}, {"blur", 6.1270}, {"night", 25.8793}, {"onnx", 3.6659}, {"emboss", 2.1772}, {"muse", 17.5824}, {"wave", 13.9226}};
    std::unordered_map<std::string, double> samProcessTimes = {{"vii", 21.4585}, {"blur", 6.3516}, {"night", 25.4173}, {"onnx", 4.2960}, {"emboss", 2.4991}, {"muse", 17.2882}, {"wave", 13.3728}};
    std::unordered_map<std::string, double> specProcessTimes = {{"vii", 21.0}, {"blur", 6.0}, {"night", 25.0}, {"onnx", 4.0}, {"emboss", 2.0}, {"muse", 17.0}, {"wave", 13.0}};
    
    Tree myTree;
    for(int i = 0; i < nodes.size(); i++) {
        myTree.addNode(nodes[i], i+1, dueTimes[i], samProcessTimes[nodes[i].substr(0,nodes[i].find('_'))]);
    }

    for(auto edge : edges) {
        myTree.addEdge({nodes[edge[1]], nodes[edge[0]]});
    }

    auto start = std::chrono::high_resolution_clock::now();
    Solution schedule = getSchedule(myTree, atoi(argv[1]));
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "BnB runtime: " << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count() << "us \n";

    std::cout << schedule;
    return 0;
}

// this is ugly i know
// bit pointless to use templates since argv is runtime 
Solution getSchedule(Tree& tree, int option) {
    switch(option) {
        case 0:
            return tree.findSchedule();
        case 1:
            return tree.findScheduleAdv<1>();
        case 2:
            return tree.findScheduleAdv<2>();
        case 3:
            return tree.findScheduleAdv<3>();
        case 4:
            return tree.findScheduleAdv<4>();
        default:
            return tree.findSchedule();
    }
}
