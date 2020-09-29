/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(nullptr);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  while (head_ != nullptr) {
    pop_front();
  }
  tail_ = nullptr;
  length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  /*
  comment out given code i don't want to use
  
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;
  
  if (head_ != NULL) {
    head_ -> prev = newNode;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
  }
  */
  ListNode* newNode = new ListNode(ndata);
  if (empty()) {
    head_ = newNode;
    head_->next = nullptr;
    tail_ = newNode;
    tail_->prev = nullptr;
  } else {
    newNode->next = head_;
    head_->prev = newNode;
    head_ = newNode;
    head_->prev = nullptr;
  }
  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode* newNode = new ListNode(ndata);
  newNode->next = nullptr;
  if (empty()) {
    newNode->prev = nullptr;
    head_ = newNode;
    tail_ = newNode;
  } else {
    tail_->next = newNode;
    newNode->prev = tail_;
    tail_ = newNode;
  }
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode * curr = start;

  if (start == nullptr) {
    return start;
  }
  if (length_ < splitPoint || splitPoint < 1) {
    return start;
  }
  for (int i = 0; i < splitPoint; i++) {
    curr = curr->next;
  }

  if (curr != nullptr) {
      curr->prev->next = nullptr;
      tail_ = curr->prev;
      curr->prev = nullptr;
      return curr;
  }

  return nullptr;

}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  ListNode* current = head_;
  if (head_ == nullptr) return;
  int remainderLength = length_;
  while (remainderLength / 3 >= 1) {
    
    //node to add to the last of the 3
    ListNode* temp = current;
    current = current->next;        //move to second element in group
    current->prev = temp->prev;     //fix prev pointer of second node
    if (current->prev != nullptr) {
      current->prev->next = current;//fix next pointer of 0 node
    }                                 
    current = current->next;        //move to third element in group
    //append temp node to group
    temp->next = current->next;     //added node's next point to original 3->next
    temp->prev = current;           //added node's prev point 3
    current->next = temp;           //node 3's next point to added node
    current = current->next;
    if (temp->next != nullptr) {
      temp->next->prev = temp;
    }
    if (remainderLength == length_) {
      head_ = current->prev->prev;
    } else if (remainderLength - 3 == 0) {
      tail_ = current;
    }
    current = current->next;
    remainderLength -= 3;
  }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  if (startPoint == nullptr || endPoint == nullptr) return;
  if (startPoint == endPoint) return;
  ListNode* current = startPoint;
  ListNode* beforeStart = current->prev;
  ListNode* temp = current->next;
  current->next = endPoint->next;
  current->prev = temp;
  current = temp;
  while (current != endPoint) {
    temp = current->next;
    current->next = current->prev;
    current->prev = temp;
    current = temp;
  }
  
  endPoint->next = endPoint->prev;
  endPoint->prev = beforeStart;
  if (head_ != startPoint) {
    beforeStart->next = current;
  }
  if (tail_ != endPoint) {
    startPoint->next->prev = startPoint;
  }
  if (head_ == startPoint) {
    head_ = endPoint;
  }
  if (tail_ == endPoint) {
    tail_ = startPoint;
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  if (n > length_) return;
  ListNode* revStart = head_;
  ListNode* revEnd = head_;
  while (revStart != nullptr) {
    int i = 1;
    while (i < n) {
      if (revEnd != tail_) {
        revEnd = revEnd->next;
      }
      i++;
    }
    reverse(revStart, revEnd);
    revStart = revStart->next;
    revEnd = revStart;
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  if (first == nullptr && second != nullptr) {
    return second;
  }
  if (second == nullptr && first != nullptr) {
    return first;
  }
  ListNode* head = nullptr;
  if (first->data < second->data) {
    head = first;
    first = first->next;
  } else {
    head = second;
    second = second->next;
  }
  ListNode* current = head;
  while (first != nullptr && second != nullptr) {
    if (first->data < second->data) {
      current->next = first;
      first->prev = current;
      first = first->next;
    } else {
      current->next = second;
      second->prev = current;
      second = second->next;
    }
    current = current->next;
  }

  if (first == nullptr && second != nullptr) {
    current->next = second;
    second->prev = current;
  }
  if (second == nullptr && first != nullptr) {
    current->next = first;
    first->prev = current;
  }
  return head;
  
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  //base case
  if (start->next == nullptr) {
    return start;
  }
  int curLength = chainLength / 2;
  ListNode* secondHalf = split(start, curLength);
  //further split the first and second half of the list
  start = mergesort(start, curLength);
  secondHalf = mergesort(secondHalf, curLength + chainLength % 2);

  return merge(start, secondHalf);
}

template <typename T>
void List<T>::pop_front() {
  if (head_ == nullptr) {
      return;
    }
    ListNode* temp = head_;
    if (temp->next == nullptr) {
      head_ = nullptr;
      tail_ = nullptr;
    } else {
      head_ = temp->next;
      head_->prev = nullptr;
    }
    delete temp;
    length_--;
}

template <typename T>
void List<T>::pop_back() {
  if (tail_ != nullptr) {
    ListNode* temp = tail_;
    tail_ = temp->prev;
    tail_->next = nullptr;
    delete temp;
    length_--;
  }
}
