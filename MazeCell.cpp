//
// Created by Ceren Duru Cinar on 25.10.2023.
//

#include "MazeCell.h"
#include <vector>

MazeCell::MazeCell(long int r, long int c){
    row = r;
    col = c;
    u = 1;
    d = 1;
    r = 1;
    l = 1;
    isVisited = false;
}

MazeCell::MazeCell(long int row_info, long int col_info, int u_info, int d_info, int l_info , int r_info){
    row = row_info;
    col = col_info;
    u = u_info;
    d = d_info;
    r = r_info;
    l = l_info;
    isVisited = false;
}



