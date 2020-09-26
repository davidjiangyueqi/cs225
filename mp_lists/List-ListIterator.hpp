
class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
  private:
    ListNode* position_;

  public:
    ListIterator() : position_(NULL) { }
    ListIterator(ListNode* x) : position_(x) { }

    // Pre-Increment, ++iter
    ListIterator& operator++() {
        // TODO: graded in MP3.1
        if (position_ != nullptr) {
            position_ = position_->next;
        }
        return *this;
    }
    
    // Post-Increment, iter++
    ListIterator operator++(int) {
        // TODO: graded in MP3.1
        ListNode* temp = position_;
        if (temp != nullptr) {
            position_ = position_->next;
        }        
        return ListIterator(temp);
    }

    // Pre-Decrement, --iter
    ListIterator& operator--() {
        // TODO: graded in MP3.1
        if (position_ != nullptr) {
            position_ = position_->prev;
        }
        return *this;
    }

    // Post-Decrement, iter--
    ListIterator operator--(int) {
        // TODO: graded in MP3.1
        ListNode* temp = position_;
        if (temp != nullptr) {
            position_ = position_->prev;
        }
        return ListIterator(temp);
    }

    bool operator!=(const ListIterator& rhs) {
        // TODO: graded in MP3.1
        if (position_ != rhs.position_) {
            return true;
        }
        //if have the same size
        // auto current = begin();
        // auto rhs_current = rhs.begin();
        // while (current != end()) {
        //     if (*current.data != *rhs_current.data) {
        //         return true;
        //     }
        //     ++current;
        //     ++rhs_current;
        // }
        return false;
    }

    bool operator==(const ListIterator& rhs) {
        return !(*this != rhs);
    }

    const T& operator*() {
        return position_->data;
    }

    const T* operator->() {
        return &(position_->data);
    }
};
