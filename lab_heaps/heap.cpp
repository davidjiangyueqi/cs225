
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    return currentIdx * 2;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    return currentIdx * 2 + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    return currentIdx / 2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    return currentIdx * 2 + 1< _elems.size();
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // Update to return the index of the child with highest priority
    // as defined by higherPriority()
    size_t right = currentIdx * 2 + 1;
    size_t left = currentIdx * 2;
    if (right >= _elems.size()) return left;
    if (higherPriority(_elems[left], _elems[right])) return left;
    return right;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    //remove
    if (!hasAChild(currentIdx)) return;
    if (currentIdx * 2 >= _elems.size()) return;
    size_t child_ = maxPriorityChild(currentIdx);

    //child < current then heapify down
    if (higherPriority(_elems[child_], _elems[currentIdx])) {
    	std::swap(_elems[child_], _elems[currentIdx]);
    	heapifyDown(child_);
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // Depending on your implementation, this function may or may
    //   not need modifying
    _elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) 
{
    _elems = {T()};
    for (auto elem : elems) {
        _elems.push_back(elem);
    }
    for (size_t i = _elems.size() - 1; i > 0; i--) {
        heapifyDown(i);
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    if (empty()) return T();
    //get root
    T temp = _elems[1];
    std::swap(_elems[1], _elems.back());
    _elems.pop_back();
    heapifyDown(1);
    return temp;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    //return root
    return _elems[1];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    _elems.push_back(elem);
    heapifyUp(_elems.size() - 1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    // root start at 1
    size_t to_update = idx;
    _elems[to_update] = elem;
    if (!higherPriority(elem, _elems[parent(to_update)])) heapifyDown(to_update);
    else heapifyUp(to_update);
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    return _elems.size() <= 1;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
