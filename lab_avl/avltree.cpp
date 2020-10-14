/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node *r = t->right;
    Node *rl = r->left;
    r->left = t;
    t->right = rl;
    //update height
    t->height = std::max(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
    r->height = std::max(heightOrNeg1(r->left), heightOrNeg1(r->right)) + 1;
    //new root
    t = r;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node *l = t->left;
    Node *lr = l->right;

    l->right = t;
    t->left = lr;

    t->height = std::max(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
    l->height = std::max(heightOrNeg1(l->left), heightOrNeg1(l->right)) + 1;

    t = l;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if (subtree == nullptr) return;
    int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    
    // right heavy
    if (balance == 2) {
        int RightBal = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
        //stick
        if (RightBal > 0) {
            rotateLeft(subtree);
        } else {
            rotateRightLeft(subtree);
        }
    }

    //left heavy
    else if (balance == -2) {
        int LeftBal = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
        //stick
        if (LeftBal < 0) {
            rotateRight(subtree);
        } else {
            rotateLeftRight(subtree);
        }
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == nullptr) {
        subtree = new Node(key, value);
    }
    else if (subtree->key < key) {
        insert(subtree->right, key, value);
        rebalance(subtree);
    }
    else if (subtree->key > key) {
        insert(subtree->left, key, value);
        rebalance(subtree);
    }
    else if (subtree->key == key) {
        return;
    }
    subtree->height = std::max(heightOrNeg1(subtree->right), heightOrNeg1(subtree->left)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree; subtree = nullptr;
            return;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            //get predecessor
            Node *prede = subtree->left;
            while (prede->right != nullptr) {
                prede = prede->right;
            }
            subtree->key = prede->key;
            subtree->value = prede->value;
            remove (subtree->left, prede->key);
        } else {
            /* one-child remove */
            // your code here
            Node *temp = (subtree->right == nullptr) ? subtree->left : subtree->right;
            *subtree = *temp;
            delete temp;    temp = nullptr;
        }
        // your code here
    }
    subtree->height = std::max(heightOrNeg1(subtree->right), heightOrNeg1(subtree->left)) + 1;
    rebalance(subtree);
}
