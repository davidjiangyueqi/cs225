/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    //outta bound
    if (curDim < 0 || curDim >= Dim) return false;
    if (first[curDim] == second[curDim]) return first < second;
    return first[curDim] < second[curDim];
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double tp_dist = 0;
    double tc_dist = 0;
    for (int i = 0; i < Dim; i++) {
      tp_dist += pow(potential[i] - target[i], 2);
      tc_dist += pow(currentBest[i] - target[i], 2);
    }
    if (tp_dist == tc_dist) return potential < currentBest;
    return tp_dist < tc_dist;
}

//partition
template <int Dim>
int KDTree<Dim>::quickSelectHelper(std::vector<Point<Dim>>& points, int dimension, unsigned left,
                                  unsigned right, int pivotIdx) {
  //select the next index
  Point<Dim> pivotVal = points[pivotIdx];
  //swap
  Point<Dim> temp = points[pivotIdx];
  points[pivotIdx] = points[right];
  points[right] = temp;
  unsigned idx = left;
  //loop thru and move lesser val to left
  for (unsigned i = left; i < right; i++) {
    if (smallerDimVal(points[i], pivotVal, dimension)) {

      //swap and update idx
      temp = points[idx];
      points[idx] = points[i];
      points[i] = temp;
      idx++;
    }
  }
  temp = points[idx];
  points[idx] = points[right];
  points[right] = temp;
  return idx;
}


template <int Dim>
Point<Dim>& KDTree<Dim>::quickSelect(std::vector<Point<Dim>>& points, int dimension, unsigned left,
                                     unsigned right, int median) {
  if (left == right) return points[right];
  //pivot location
  int pivot = quickSelectHelper(points, dimension, left, right, median);
  if (pivot == median) return points[pivot];
  if (median < pivot) {
    return quickSelect(points, dimension, left, pivot - 1, median);
  } else {
    return quickSelect(points, dimension, pivot + 1, right, median);
  }
}



template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::createNodes(std::vector<Point<Dim>>& points,
                                                  int dimension, unsigned left, unsigned right) {
  //implement
  //base case
  if (points.empty() || left < 0 || right >= points.size()) return nullptr;
  if (left > right) return nullptr;
  unsigned median = (left + right) / 2;
  KDTreeNode *newNode = new KDTreeNode(quickSelect(points, dimension % Dim, left, right, median));
  size++;
  dimension++;
  newNode->left = createNodes(points, dimension, left, median - 1);
  newNode->right = createNodes(points, dimension, median + 1, right);
  return newNode;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    size = 0;
    std::vector<Point<Dim>> points;
    points.assign(newPoints.begin(), newPoints.end());
    //call helper pass in left and right pointer
    root = createNodes(points, 0, 0, points.size() - 1);
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  size = other.size;
  copy(this->root, other.root);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if (this != nullptr) clear(root);
  copy(root, rhs);
  size = rhs.size;
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  clear(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    //call recurse helper func
    return neighborHelper(query, root, 0);
}

template <int Dim>
Point<Dim> KDTree<Dim>::neighborHelper(const Point<Dim>& query,
                                      typename KDTree<Dim>::KDTreeNode *current,
                                      int currentDim) const {
  //base case leaf node
  if (current->left == nullptr && current->right == nullptr) {
    return current->point;
  }
  int nextDim = (currentDim + 1) % Dim;
  Point<Dim> curBest = current->point;
  Point<Dim> temp = curBest;
  //true->left 
  bool direction = smallerDimVal(query, curBest, currentDim);
  if ((direction && current->left != nullptr) /*|| (!direction && current->right == nullptr)*/) {
    //traverse to left
    temp = neighborHelper(query, current->left, nextDim);
  } else if ((!direction && current->right != nullptr) /*|| (direction && current->left == nullptr)*/) {
    //traverse to right
    temp = neighborHelper(query, current->right, nextDim);
  }

  //check if found a better option          replace!
  if (shouldReplace(query, curBest, temp)) curBest = temp;
  
  int eucDist = 0;
  //distance(query, curBest);
  for (int i = 0; i < Dim; i++) {
    eucDist += pow(query[i] - curBest[i], 2);
  }
  int dimDist = pow(current->point[currentDim] - query[currentDim], 2);
  //detect red zone and traverse other side
  if (dimDist <= eucDist) {
    //same as above but reverse direction
    if (direction && current->right != nullptr) {
      temp = neighborHelper(query, current->right, nextDim);
      if (shouldReplace(query, curBest, temp)) curBest = temp;
    } else if (!direction && current->left != nullptr) {
      temp = neighborHelper(query, current->left, nextDim);
      if (shouldReplace(query, curBest, temp)) curBest = temp;
    }
  }
  return curBest;

}

//big 5 helper
template<int Dim>
void KDTree<Dim>::clear(KDTreeNode *root) {
  if (root == nullptr) return;
  if (root->left != nullptr) clear(root->left);
  if (root->right != nullptr) clear(root->right);
  delete root;  root = nullptr;
}

template<int Dim>
void KDTree<Dim>::copy(KDTreeNode *lhs, KDTreeNode *rhs) {
  lhs = new KDTreeNode();
  lhs->point = rhs->point;
  copy(lhs->left, rhs->left);
  copy(lhs->right, rhs->right);
}