#ifndef JATEKMESTER_HPP_INCLUDED
#define JATEKMESTER_HPP_INCLUDED

#include "sudokuboard.hpp"
#include "graphics.hpp"

class JatekMester{
protected:
    SudokuBoard board;
    int width, height;
    bool running;
public:
    JatekMester(int w, int h);
    void run();
};

#endif // JATEKMESTER_HPP_INCLUDED
