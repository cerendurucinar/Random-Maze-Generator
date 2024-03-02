// Created by Ceren Duru Cinar

#include <iostream>
#include <string>
#include <fstream>
#include "Stack.h"
#include "MazeCell.h"
#include "randgen.h"
#include <vector>
#include <stdlib.h>
#include <sstream>
using namespace std;


void createCells(long int m, long int n, vector<vector<MazeCell>> & mazeCells){
    for (int i = 0; i < m ; i++){
        for (int j = 0; j < n; j++){
            mazeCells[i][j] = MazeCell(i,j);
        }
    }
}


bool checkIndexes(long int m, long int n ,vector<vector<MazeCell>> mazeCells){
    if(m < mazeCells.size() && n < mazeCells[0].size() &&
            m >= 0 && n >= 0 ){
        if (!mazeCells[m][n].isVisited){
            return true;
        }
        else{
            return false;
        }
    }
    return false;
}

void findUnvisitedNeighbors(MazeCell & currentCell ,vector<MazeCell*> & neighbors, vector<vector<MazeCell>> & mazeCells){
    if (checkIndexes(currentCell.row+1, currentCell.col, mazeCells)){
        neighbors.push_back(&mazeCells[currentCell.row+1][currentCell.col]);
    }
    if (checkIndexes(currentCell.row, currentCell.col+1, mazeCells)){
        neighbors.push_back(&mazeCells[currentCell.row][currentCell.col+1]);
    }
    if (checkIndexes(currentCell.row-1, currentCell.col, mazeCells)){
        neighbors.push_back(&mazeCells[currentCell.row-1][currentCell.col]);
    }
    if (checkIndexes(currentCell.row, currentCell.col-1, mazeCells)){
        neighbors.push_back(&mazeCells[currentCell.row][currentCell.col-1]);
    }
}

void findPossibleWays(MazeCell & currentCell ,vector<MazeCell*> & neighbors, vector<vector<MazeCell>> & mazeCells){
    if (currentCell.u == 0 && !mazeCells[currentCell.row+1][currentCell.col].isVisited){
        neighbors.push_back(&mazeCells[currentCell.row+1][currentCell.col]);
    }
    if (currentCell.d == 0 && !mazeCells[currentCell.row-1][currentCell.col].isVisited){
        neighbors.push_back(&mazeCells[currentCell.row-1][currentCell.col]);
    }
    if (currentCell.l == 0 && !mazeCells[currentCell.row][currentCell.col-1].isVisited){
        neighbors.push_back(&mazeCells[currentCell.row][currentCell.col-1]);
    }
    if (currentCell.r == 0 && !mazeCells[currentCell.row][currentCell.col+1].isVisited){
        neighbors.push_back(&mazeCells[currentCell.row][currentCell.col+1]);
    }
}

void knockDownWall(MazeCell & current, MazeCell & next){
    if (next.row - current.row == 1){
        current.u = 0;
        next.d = 0;
    }
    else if (next.col - current.col == 1){
        current.r = 0;
        next.l = 0;
    }
    else if (next.col - current.col == -1){
        current.l = 0;
        next.r = 0;
    }
    else{
        current.d = 0;
        next.u = 0;
    }
}

void parseFileInfo(ifstream & in, int & row, int & col, int & u, int & d,int & l, int & r, string fileLine){
    string col_info = fileLine.substr(2, fileLine.find(" "));
    fileLine = fileLine.substr(fileLine.find(" ")+1);
    string row_info = fileLine.substr(2, fileLine.find(" "));
    fileLine = fileLine.substr(fileLine.find(" ")+1);
    string l_info  = fileLine.substr(2, fileLine.find(" "));
    fileLine = fileLine.substr(fileLine.find(" ")+1);
    string r_info = fileLine.substr(2, fileLine.find(" "));
    fileLine = fileLine.substr(fileLine.find(" ")+1);
    string u_info = fileLine.substr(2, fileLine.find(" "));
    fileLine = fileLine.substr(fileLine.find(" ")+1);
    string d_info = fileLine;
    col = stoi(col_info);
    row = stoi(row_info);
    l = stoi(l_info);
    r = stoi(r_info);
    u = stoi(u_info);
    d = stoi(d_info);
}

int main() {
    long int k, m, n, rand_idx;
    RandGen rand;
    cout << "Enter the number of mazes: ";
    cin >> k;
    cout << "Enter the number of rows and columns (M and N): ";
    cin >> m >> n;
    ofstream out;
    ifstream in;

    for (int i = 1; i <= k; i++ ){
        string filename = "maze_" + to_string(i) + ".txt";
        int visited_count = 0;
        vector< vector<MazeCell> > mazeCells(m, vector<MazeCell>(n, MazeCell(0,0)));
        createCells(m,n,mazeCells);
        Stack<MazeCell> mazeStack = Stack<MazeCell>();
        MazeCell currentCell = mazeCells[0][0];
        currentCell.isVisited = true;
        visited_count+= 1;
        mazeCells[0][0].isVisited = true;
        mazeStack.push(currentCell);
        while (!mazeStack.isEmpty()){
            mazeStack.topAndPop(currentCell);
            vector<MazeCell *> neighbors;
            findUnvisitedNeighbors(currentCell,neighbors,mazeCells);
            if (neighbors.size() != 0){
                rand_idx = rand.RandInt(neighbors.size());
               // MazeCell nextCell = mazeCells[neighbors[rand_idx]->row][neighbors[rand_idx]->col];
                MazeCell nextCell = *neighbors[rand_idx];
                knockDownWall(currentCell, nextCell);
                knockDownWall(mazeCells[currentCell.row][currentCell.col], mazeCells[nextCell.row][nextCell.col]);
                mazeCells[neighbors[rand_idx]->row][neighbors[rand_idx]->col].isVisited = true;
                visited_count+= 1;
                nextCell.isVisited = true;
                mazeCells[nextCell.row][nextCell.col].isVisited = true;
                mazeStack.push(currentCell);
                mazeStack.push(nextCell);
            }
        }

        out.open(filename);
        out << m << " " << n << "\n";
        for (int i= 0; i < mazeCells.size(); i++){
            for (int j = 0; j < mazeCells[0].size(); j++){
                out << "x=" << j << " y=" << i << " l=" << mazeCells[i][j].l << " r=" << mazeCells[i][j].r <<
                " u=" << mazeCells[i][j].u << " d=" << mazeCells[i][j].d << "\n";
            }
        }
        out.close();
    }
    cout << "All mazes are generated.";

    cout<< "\n";
    int mazeId, entry_row, entry_col, exit_row, exit_col;
    cout << "Enter a maze ID between 1 to " << k << " inclusive to find a path: ";
    cin >> mazeId;
    cout << "Enter x and y coordinates of the entry points (x,y) or (column,row): ";
    cin >> entry_col >> entry_row;
    cout << "Enter x and y coordinates of the exit points (x,y) or (column,row): ";
    cin >> exit_col >> exit_row;
    string inFile = "maze_" + to_string(mazeId) + ".txt";
    in.open(inFile.c_str());
    string line;
    stringstream ss(line);
    vector< vector<MazeCell> > mazeCells(m, vector<MazeCell>(n, MazeCell(0,0)));
    if (in.is_open()){
        getline(in, line);
        while (getline(in,line) && line.length() != 0){
            string row_info, col_info, l_info, r_info, u_info, d_info;
            long int row, col;
            int u, r, l, d;
            col = stoi(line.substr(2, line.find(" ")-2));
            line = line.substr(line.find(" ")+1);
            row = stoi(line.substr(2, line.find(" ")-2));
            line = line.substr(line.find(" ")+1);
            l  = stoi(line.substr(2, line.find(" ")-2));
            line = line.substr(line.find(" ")+1);
            r = stoi(line.substr(2, line.find(" ")-2));
            line = line.substr(line.find(" ")+1);
            u = stoi(line.substr(2, line.find(" ")-2));
            line = line.substr(line.find(" ")+1);
            d = stoi(line.substr(2));
            /*
            col = stoi(col_info.substr(2));row = stoi(row_info.substr(2));
            l = stoi(l_info.substr(2));r = stoi(r_info.substr(2));
            u = stoi(u_info.substr(2));d = stoi(d_info.substr(2));
             */
            mazeCells[row][col] = MazeCell(row, col, u, d, l, r);
        }
    }
    in.close();
    Stack<MazeCell> mazeStack = Stack<MazeCell>();
    string outFileName = "maze_" + to_string(mazeId) + "_path_" + to_string(entry_col) +"_" +
            to_string(entry_row) + "_" + to_string(exit_col) + "_" + to_string(exit_row) + ".txt";
    out.open(outFileName);
    MazeCell currentCell = mazeCells[entry_row][entry_col];
    currentCell.isVisited = true;
    mazeCells[entry_row][entry_col].isVisited = true;
    mazeStack.push(currentCell);
    while (currentCell.row != exit_row || currentCell.col != exit_col){
        mazeStack.topAndPop(currentCell);
        vector<MazeCell *> neighbors;
        findPossibleWays(currentCell, neighbors, mazeCells);
        if (neighbors.size() != 0){
            rand_idx = rand.RandInt(neighbors.size());
            MazeCell nextCell = mazeCells[neighbors[rand_idx]->row][neighbors[rand_idx]->col];
            //out << currentCell.col << " " << currentCell.row << endl;
            nextCell.isVisited = true;
            mazeCells[nextCell.row][nextCell.col].isVisited = true;
            mazeStack.push(currentCell);
            mazeStack.push(nextCell);
        }

    }
    mazeStack.topAndPop(currentCell);
    Stack<MazeCell> printStack;
    while (!mazeStack.isEmpty()){
        mazeStack.topAndPop(currentCell);
        printStack.push(currentCell);
    }
    while (!printStack.isEmpty()){
        printStack.topAndPop(currentCell);
        out << currentCell.col << " " << currentCell.row << endl;
    }
}




