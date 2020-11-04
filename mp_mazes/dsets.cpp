#include "dsets.h"

#include <iostream>
#include <string>
#include <vector>

void DisjointSets::addelements(int num) {
    
    for (int i = 0; i < num; i++) {
        _elems.push_back(-1);
    }
}

int  DisjointSets::find(int elem) {
    
    //base case root
    if (_elems[elem] < 0) return elem;
    //recurse up
    int root = find(_elems[elem]);
    _elems[elem] = root;
    return root;
}

void DisjointSets::setunion(int a, int b) {

    //find root of the 2 set
    while (_elems[a] > -1) a = _elems[a];
    while (_elems[b] > -1) b = _elems[b];

    int new_height_ = _elems[a] + _elems[b];
    //a shorter
    if (_elems[a] > _elems[b]) {
        _elems[a] = b;
        _elems[b] = new_height_;
    } else {
        _elems[b] = a;
        _elems[a] = new_height_;
    }
}

int DisjointSets::size(int elem) {

    while (_elems[elem] > -1) elem = _elems[elem];
    return _elems[elem] * (-1);
}
