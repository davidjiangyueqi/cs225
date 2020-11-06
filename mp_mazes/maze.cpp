#include "maze.h"

#include "dsets.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>
#include <vector>
#include <utility>
#include <unordered_set>
#include <stack>
#include <queue>

SquareMaze::SquareMaze() {
    
    //maze = new std::vector<MazeNode>;
    ConnectivitySet = new DisjointSets();
    //empty maze
    width_ = 0;
    height_ = 0;
}

SquareMaze::~SquareMaze() {
    
    //delete maze;            maze = nullptr;
    delete ConnectivitySet; ConnectivitySet = nullptr;
}

void SquareMaze::makeMaze(int width, int height) {

    width_ = width;
    height_ = height;
    int size = width_ * height;
    //completely disconnected maze with walls everywhere
    ConnectivitySet->addelements(size);
    for (int i = 0; i < size; i++) {
        maze.emplace_back(MazeNode(true, true));
    }
    std::stack<int> TraverseWall;
    TraverseWall.push(0);
    while (!TraverseWall.empty()) {
        // dir = 0 right x coor + 1
        // dir = 1 down  y coor + 1
        // dir = 2 left  x coor - 1
        // dir = 3 up    y coor - 1
        int i = TraverseWall.top();
        TraverseWall.pop();
        int rand = std::rand() % 2;
        if (rand) {
            //attempt to remove right wall
            if ((i + 1) % width_ != 0 && !connected(i, i + 1)) {
                //std::cout << "right " << i << std::endl;
                maze[i].right_ = false;
                TraverseWall.push(i + 1);
                ConnectivitySet->setunion(i, i + 1);
            }
            if (i < width_ * (height_ - 1) && !connected(i, i + width_)) {
                //std::cout << "down " << i << std::endl;
                maze[i].down_ = false;
                TraverseWall.push(i + width_);
                ConnectivitySet->setunion(i, i + width_);
            }
        } else {
            if (i < width_ * (height_ - 1) && !connected(i, i + width_)) {
                //std::cout << "right " << i << std::endl;
                maze[i].down_ = false;
                TraverseWall.push(i + width_);
                ConnectivitySet->setunion(i, i + width_);
            }
            if ((i + 1) % width_ != 0 && !connected(i, i + 1)) {
                //std::cout << "down " << i << std::endl;
                maze[i].right_ = false;
                TraverseWall.push(i + 1);
                ConnectivitySet->setunion(i, i + 1);
            }
        }
    }

}

bool SquareMaze::canTravel(int x, int y, int dir) const {
    // dir = 0 right x coor + 1
    // dir = 1 down  y coor + 1
    // dir = 2 left  x coor - 1
    // dir = 3 up    y coor - 1
    int idx = y * width_ + x;
    switch (dir) {
    //right
    case 0:
        if (x + 1 >= width_) return false;
        return !maze[idx].right_;
    //down
    case 1:
        if (y + 1 >= height_) return false;
        return !maze[idx].down_;
    //left
    case 2:
        if (x <= 0) return false;
        return !maze[idx - 1].right_;
    //up
    case 3:
        if (y <= 0) return false;
        return !maze[idx - width_].down_;
    default:
        break;
    }
    std::cerr << "DIR PARAM ERROR" << std::endl;
    return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    if (dir) maze[width_ * y + x].down_ = exists;
    else maze[width_ * y + x].right_ = exists;
}

std::vector<int> SquareMaze::solveMaze() {

    std::vector<bool> visited;
    std::vector<int> pathTree;
    int size = width_ * height_;
    for (int i = 0; i < size; i++) {
        visited.push_back(false);
        pathTree.push_back(i);
    }
    std::queue<int> TraverseWall;
    //contains idx of mazenode to visit
    TraverseWall.push(0);

    std::pair<int, int> max_idx_dist(0, 0);
    while (!TraverseWall.empty()) {
        int idx = TraverseWall.front();
        TraverseWall.pop();
        visited[idx] = true;
        //check right
        if ((idx + 1) < size && canTravel(idx % width_, idx / width_, 0) && !visited[idx + 1]) {
            TraverseWall.push(idx + 1);
            pathTree[idx + 1] = idx;
        }
        //check down
        if ((idx + width_) < size && canTravel(idx % width_, idx / width_, 1) && !visited[idx + width_]) {
            TraverseWall.push(idx + width_);
            pathTree[idx + width_] = idx;
        }
        //check left
        if ((idx - 1) > 0 && canTravel(idx % width_, idx / width_, 2) && !visited[idx - 1]) {
            TraverseWall.push(idx - 1);
            pathTree[idx - 1] = idx;
        }
        //check up
        if ((idx - width_) > 0 && canTravel(idx % width_, idx / width_, 3) && !visited[idx - width_]) {
            TraverseWall.push(idx - width_);
            pathTree[idx - width_] = idx;
        }
    }
    //calculate max path outcome
    for (int curIdx = size - width_; curIdx < size; curIdx++) {
        int tempIdx = curIdx;
        int step = 0;
        while (tempIdx != 0) {
            step++;
            tempIdx = pathTree[tempIdx];
        }
        //update max distance index
        if (step > max_idx_dist.second) {
            max_idx_dist.first = curIdx;
            max_idx_dist.second = step;
        }
    }

    // dir = 0 right x coor + 1
    // dir = 1 down  y coor + 1
    // dir = 2 left  x coor - 1
    // dir = 3 up    y coor - 1
    //construct solution
    std::vector<int> sol(max_idx_dist.second);
    int tempIdx = max_idx_dist.first;
    while (tempIdx != 0) {
        max_idx_dist.second--;
        //get parent idx of the tree
        //right should push front left
        if (pathTree[tempIdx] == tempIdx + 1) sol[max_idx_dist.second] = 2;
        //down                                            up
        else if (pathTree[tempIdx] == tempIdx + width_) sol[max_idx_dist.second] = 3;
        //left                                            right
        else if (pathTree[tempIdx] == tempIdx - 1) sol[max_idx_dist.second] = 0;
        //up                                              down
        else if (pathTree[tempIdx] == tempIdx - width_) sol[max_idx_dist.second] = 1;
        tempIdx = pathTree[tempIdx];
    }
    return sol;
}

cs225::PNG* SquareMaze::drawMaze() const {

    std::pair <int, int> dimension(width_ * 10 + 1, height_ * 10 + 1);
    cs225::PNG* result = new cs225::PNG(dimension.first, dimension.second);
    //draw boundary
    for (int x = 10; x < dimension.first; x++) {
        cs225::HSLAPixel &curPixel = result->getPixel(x, 0);
        curPixel.l = 0;
    }
    for (int y = 0; y < dimension.second; y++) {
        cs225::HSLAPixel &curPixel = result->getPixel(0, y);
        curPixel.l = 0;
    }
    for (int y = 0; y < height_; y++) {
        for (int x = 0; x < width_; x++) {
            if (maze[y * width_ + x].right_) {
                //draw right wall
                for (int i = 0; i <= 10; i++) {
                    cs225::HSLAPixel &curPixel = result->getPixel((x + 1) * 10, y * 10 + i);
                    curPixel.l = 0;
                }
            }
            if (maze[y * width_ + x].down_) {
                //draw vertical wall
                for (int i = 0; i <= 10; i++) {
                    cs225::HSLAPixel &curPixel = result->getPixel(x * 10 + i, (y + 1) * 10);
                    curPixel.l = 0;
                }
            }
        }
    }
    return result;
}

cs225::PNG* SquareMaze::drawMazeWithSolution() {

    // dir = 0 right x coor + 1
    // dir = 1 down  y coor + 1
    // dir = 2 left  x coor - 1
    // dir = 3 up    y coor - 1
    cs225::PNG *InitialMaze = drawMaze();
    std::vector<int> solution = solveMaze();
    //start point           x, y
    std::pair<int, int> cur(5, 5);
    for (const auto i : solution) {
        //case right
        if (i == 0) {
            for (int j = 0; j < 10; j++) {
                cs225::HSLAPixel &curPixel = InitialMaze->getPixel(cur.first, cur.second);
                //draw dot
                curPixel.h = 0;
                curPixel.s = 1;
                curPixel.l = 0.5;
                cur.first++;
            }
        }
        //case down
        else if (i == 1) {
            for (int j = 0; j < 10; j++) {
                cs225::HSLAPixel &curPixel = InitialMaze->getPixel(cur.first, cur.second);
                //draw
                curPixel.h = 0;
                curPixel.s = 1;
                curPixel.l = 0.5;
                cur.second++;
            }
        }
        //case left
        else if (i == 2) {
            for (int j = 0; j < 10; j++) {
                cs225::HSLAPixel &curPixel = InitialMaze->getPixel(cur.first, cur.second);
                //draw
                curPixel.h = 0;
                curPixel.s = 1;
                curPixel.l = 0.5;
                cur.first--;
            }
        }
        //case up
        else if (i == 3) {
            for (int j = 0; j < 10; j++) {
                cs225::HSLAPixel &curPixel = InitialMaze->getPixel(cur.first, cur.second);
                //draw
                curPixel.h = 0;
                curPixel.s = 1;
                curPixel.l = 0.5;
                cur.second--;
            }
        }
    }
    cs225::HSLAPixel &curPixel = InitialMaze->getPixel(cur.first, cur.second);
    curPixel.h = 0;
    curPixel.s = 1;
    curPixel.l = 0.5;

    // whiten exit
    //TODO: POTENTIAL BOUNDARY ERROR
    cur.first = cur.first / 10 * 10;    //round
    for (int k = 1; k < 10; k++) {
        cs225::HSLAPixel &curPixel = InitialMaze->getPixel(k + cur.first, height_ * 10);
        curPixel.a = 1;
        curPixel.l = 1;
    }
    return InitialMaze;
}

//helpers
//check if two nodes are connected
bool SquareMaze::connected(int idx1, int idx2) {
    return ConnectivitySet->find(idx1) == ConnectivitySet->find(idx2);
}