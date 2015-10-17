#include "BST.h"
#include <string>
#include <iostream>

BST::BST() {
    root = NULL;
}

BST::~BST() {
	while (root != NULL) {
		remove(root->k);
	}
	delete root;
	root = NULL; 
}

BSTNode::BSTNode() {
    k = -1;
    v = "";
    left = NULL;
    right = NULL;
}

BSTNode::BSTNode(int myK, string myV) {
    k = myK;
    v = myV;
    left = NULL;
    right = NULL;
}

/***
 * Return the number of items currently in the BST.
 ***/
unsigned long BST::size(){
    return sizeHelper(root);
}

unsigned long BST::sizeHelper(BSTNode* r){
    if (r == NULL) {
        return 0;
    }
    return 1 + sizeHelper(r->left) + sizeHelper(r->right);
}


/***
 * Add a new entry with key k and value v.
 * If an item with key k already exists, overwrite it.
 ***/
void BST::insert(int k, string v){
    root = insertHelper(root, k, v);
}

BSTNode* BST::insertHelper(BSTNode* r, int k, string v){
    if (r == NULL) {
        r = new BSTNode(k, v);
    } else if (r->k > k) {
        r->left = insertHelper(r->left, k, v);
    } else if (r->k < k) {
        r->right = insertHelper(r->right, k, v);
    } else { // (r->k == k)
		r->v = v;
	}
    return r;
}


/***
 * Remove the entry with key k.
 * If there is no such item, do nothing.
 ***/
void BST::remove(int k){
    root = removeHelper(root, k);
}

BSTNode* BST::removeHelper(BSTNode* r, int k){
    if (r == NULL) {
        return r;
    } else if (r->k > k) {
        r->left = removeHelper(r->left, k);
    } else if (r->k < k) {
        r->right = removeHelper(r->right, k);
    } else { // (r->k == k)
        // Leaf node
        if (r->left == NULL && r->right == NULL) {
            delete r;
            r = NULL;
        } else if (r->left == NULL) { // Right child only
            BSTNode* n = r->right;
            r->k = r->right->k;
			r->v = r->right->v;
			r->left = r->right->left;
			r->right = r->right->right;
            delete n;
        } else { // Two children or left child only
            BSTNode* n = max(r->left);
            r->k = n->k;
            r->v = n->v;
            r->left = removeHelper(r->left, n->k);
        }
    }
    return r;
}


/***
 * Return the value of the entry with key k.
 * If there is no such item, throw an exception.
 ***/
string BST::find(int k){
    BSTNode* n = findHelper(root, k);
    if(n == NULL) {
        cout << "There is no entry with key " << k << "!" << endl;
        throw 10;
    }
    return n->v;
}

BSTNode* BST::findHelper(BSTNode* r, int k){
    if (r == NULL) {
        return NULL;
    } else if (r->k > k) {
        return findHelper(r->left, k);
    } else if (r->k < k) {
        return findHelper(r->right, k);
    }
    return r;
}


/***
 * Return true if there is an entry with key k in the BST.
 * If not, return false.
 ***/
bool BST::intExists(int k){
    if (findHelper(root, k) == NULL) {
        return false;
    } 
    return true;
}

/***
 * If any of the entries in the BST has a key greater than k,
 * return the smallest such key.
 * If not, return k.
 ***/
int BST::next(int k){
	BSTNode* n = nextHelper(root, k);
	if (n == NULL) {
		return k;
	}
	return n->k;
}

/* If there is a key in the set that is > k, return the node containing the first such key. 
 * If not, return NULL. 
 */
BSTNode* BST::nextHelper(BSTNode* r, int k){
	if (r == NULL) {
		return NULL;
	}

	if (k < r->k) {
		if ((r->left != NULL) && (k >= max(r->left)->k)) {
			return r;
		} else {
			return nextHelper(r->left, k);
		}
	} else if (k == r->k) {
		if (r->right == NULL) {
			return NULL;
		} else {
			return min(r->right);
		}
	} else { // k > r->k
		return nextHelper(r->right, k);
	}
}



/***
 * If any of the entries in the BST has a key smaller than k,
 * return the greatest such key.
 * If not, return k.
 ***/
int BST::prev(int k){
	BSTNode* n = prevHelper(root, k);
	if (n == NULL) {
		return k;
	}
	return n->k;
}

/* If there is a key in the set that is < k, return the node containing the first such key. 
 * If not, return NULL. 
 */
BSTNode* BST::prevHelper(BSTNode* r, int k) {
	if (r == NULL) {
		return NULL;
	}

	if (k > r->k) {
		if ((r->right != NULL) && (k <= min(r->right)->k)) {
			return r;
		} else {
			return prevHelper(r->right, k);
		}
	} else if (k == r->k) {
		if (r->left == NULL) {
			return NULL;
		} else {
			return max(r->left);
		}
	} else { // k < r->k
		return prevHelper(r->left, k);
	}
}


/***
 * The following additional functions print the tree using
 * pre-order, in-order, and post-order traversals, respectively.
 * Print each entry r using the statement:
 *   cout << "(" << r->k << "," << r->v << ") "{ }
 ***/
void BST::printPreOrder() {
    printPreOrderHelper(root);
}

void BST::printPreOrderHelper(BSTNode* r) {
    if(r != NULL) {
        cout << "(" << r->k << ", " << r->v << ") ";
        printPreOrderHelper(r->left);
        printPreOrderHelper(r->right);
    }
}


void BST::printInOrder() {
    printInOrderHelper(root);
}

void BST::printInOrderHelper(BSTNode* r) {
    if(r != NULL) {
        printInOrderHelper(r->left);
        cout << "(" << r->k << ", " << r->v << ") ";
        printInOrderHelper(r->right);
    }
}


void BST::printPostOrder() {
    printPostOrderHelper(root);
}

void BST::printPostOrderHelper(BSTNode* r) {
    if(r != NULL) {
        printPostOrderHelper(r->left);
        printPostOrderHelper(r->right);
        cout << "(" << r->k << ", " << r->v << ") ";
    }
}


/***
 * Find the item in the sub-tree rooted at r which has the smallest key.
 ***/
BSTNode* BST::min(BSTNode* r) {
	if (r == NULL) {
		return NULL;
	} else if (r->left == NULL) {
        return r;
    }  
	return min(r->left);
}


/***
 * Find the item in the sub-tree rooted at r which has the largest key.
 ***/
BSTNode* BST::max(BSTNode* r){
    if (r == NULL) {
		return NULL;
	} else if (r->right == NULL) {
        return r;
    }
    return max(r->right);
}
