#pragma once

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "dsets.h"

#include <string>
#include <vector>
#include <utility>

struct MazeNode {
    /* Single Maze Node */
    MazeNode(bool down, bool right) {
        down_ = down;
        right_ = right;
    }
    //true->wall false->no_wall
    bool down_;
    bool right_;
};

class SquareMaze {

    public:
        SquareMaze();
        ~SquareMaze();
        void makeMaze(int width, int height);
        bool canTravel(int x, int y, int dir) const;
        void setWall(int x, int y, int dir, bool exists);
        std::vector<int> solveMaze();
        cs225::PNG* drawMaze() const;
        cs225::PNG* drawMazeWithSolution();
    private:
        //dimension of the maze
        int width_;
        int height_;
        std::vector<MazeNode> maze;
        DisjointSets *ConnectivitySet;

        bool connected(int idx1, int idx2);
        
};