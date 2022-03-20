#ifndef VIEW_H
#define VIEW_H
#include "controller.h"
#include "component.h"
#include <iostream>
#include <vector>
#include <string>

class View {
    std::vector<std::string> t;
    std::vector<std::string> vl;
    std::vector<std::string> vt;
    std::vector<std::string> e;

    public:
    View(Controller& con);
    void printBoard(Controller& con); //prints the current board
};

#endif
