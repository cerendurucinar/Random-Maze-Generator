//
// Created by Ceren Duru Cinar on 25.10.2023.
//

#ifndef MAZECELL_H
#define MAZECELL_H

#include <string>
#include <vector>
using namespace std;

class MazeCell{
public:
    long int row, col;
    int u, d, l ,r;
    bool isVisited;
    //vector<MazeCell> neighbors;
    MazeCell(long int row, long int col);
    MazeCell(long int row, long int col, int u, int d, int l , int r);
};

#endif
