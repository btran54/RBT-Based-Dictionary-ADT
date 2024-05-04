/***
* Brian Tran
* btran54
* 2024 Winter CSE101 PA8
* Dictionary.cpp
* Dictionary CPP file containing the operation of functions.
***/

#include <iostream>
#include <string>
#include <stdexcept>
#include "Dictionary.h"

#define RED 0
#define BLACK 1

Dictionary::Node::Node(keyType k, valType v) {
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = BLACK;
}

//Dictionary helper functions------------------------------------------------------------------------
void Dictionary::inOrderString(std::string &s, Node* R) const {
    if (R != nil) {
        inOrderString(s, R->left);
		s.append(R->key + " : " + std::to_string(R->val) + "\n");
        inOrderString(s, R->right);
    }

	// else {
	// 	throw std::runtime_error("Dictionary::inOrderString(): Encountered a null pointer.\n");
	// }
}

void Dictionary::preOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        s.append(R->key);

        if (R->color == RED) {
        s.append(" ");
        s.append("(RED)");
        }

        s.append("\n");
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }

	// else {
	// 	throw std::runtime_error("Dictionary::preOrderString(): Encountered a null pointer.\n");
	// }
}

void Dictionary::BST_insert(Node* newNode) {
    Node* parentNode = nil;
    Node* current = root;

    // Find the position to insert the new node
    while (current != nil) {
        parentNode = current;

        if (newNode->key < current->key) {
            current = current->left;
        } 
		
		else {
            current = current->right;
        }
    }

    // Insert the new node
    newNode->parent = parentNode;
    if (parentNode == nil) {
        root = newNode;
    } 
	
	else if (newNode->key < parentNode->key) {
        parentNode->left = newNode;
    } 
	
	else {
        parentNode->right = newNode;
    }

    newNode->left = nil;
    newNode->right = nil;
    newNode->color = RED;
    num_pairs++;
    RB_InsertFixUp(newNode);
}

void Dictionary::preOrderCopy(Node* R, Node* N) {
    if (R != N) {
        setValue(R->key, R->val);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }

	// else {
	// 	throw std::logic_error("Dictionary::preOrderCopy(): Cannot copy node.\n");
	// }
}

void Dictionary::postOrderDelete(Node* R) {
    if (R != nil) {
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete R;
    }

	// else {
	// 	throw std::logic_error("Dictionary::postOrderDelete(): Cannot delete nil node.\n");
	// }
}

Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
    if (R == nil || k == R->key) {
        return R;
    }
	
	else if (k < R->key) {
        return search(R->left, k);
    }
	
	else {
        return search(R->right, k);
    }
}

Dictionary::Node* Dictionary::findMin(Node* R) {
    if (R == nil) {
        return nil;
    }

    Node* min = R;

    while (min->left != nil) {
        min = min->left;
    }

    return min;
}

Dictionary::Node* Dictionary::findMax(Node* R) {
    if (R == nil) {
        return nil;
    }

    Node* max = R;

    while (max->right != nil) {
        max = max->right;
    }

    return max;
}

Dictionary::Node* Dictionary::findNext(Node* N) {
    if (N == nil) {
        return nil;
    }  

    if (N->right != nil) {
        return findMin(N->right);
    } 

    Node* next = N->parent;

    while (next != nil && N == next->right) {
        N = next;
        next = next->parent;
    }

    return next;
}

Dictionary::Node* Dictionary::findPrev(Node* N) {
    if (N == nil) {
        return nil;
    } 

    if (N->left != nil) {
        return findMax(N->left);
    } 

    Node* prev = N->parent;
	
	while (prev != nil && N == prev->left) {
		N = prev;
		prev = prev->parent;
	}

	return prev;
}

// transplant()
// void Dictionary::transplant(Node* R, Node* N) {
// 	if (R->parent == nil) {
// 		root = N;
// 	}

// 	else if (R == R->parent->left) {
// 		R->parent->left = N;
// 	}

// 	else {
// 		R->parent->right = N;
// 	}

// 	if (N != nil) {
// 		N->parent = R->parent;
// 	}
// }


// RBT Helper Functions (Optional) -----------------------------------------
void Dictionary::LeftRotate(Node* N) {
    Node* newNode = N->right;
    N->right = newNode->left;

    if (newNode->left != nil) {
        newNode->left->parent = N;
    }

    newNode->parent = N->parent;

    if (N->parent == nil) {
        root = newNode;
    } 
	
	else if (N == N->parent->left) {
        N->parent->left = newNode;
    } 
	
	else {
        N->parent->right = newNode;
    }

    newNode->left = N;
    N->parent = newNode;
}

void Dictionary::RightRotate(Node* N) {
    Node* newNode = N->left;
    N->left = newNode->right;

    if (newNode->right != nil) {
        newNode->right->parent = N;
    }

    newNode->parent = N->parent;

    if (N->parent == nil) {
        root = newNode;
    } 
	
	else if (N == N->parent->right) {
        N->parent->right = newNode;
    } 
	
	else {
        N->parent->left = newNode;
    }

    newNode->right = N;
    N->parent = newNode;
}

void Dictionary::RB_InsertFixUp(Node* N) {
    while (N->parent->color == RED) {
        Node* grandparent = N->parent->parent;
        Node* siblingNode = (N->parent == grandparent->left) ? grandparent->right : grandparent->left;

        if (siblingNode->color == RED) {
            // Case 1: Sibling node is red
            N->parent->color = BLACK;
            siblingNode->color = BLACK;
            grandparent->color = RED;
            N = grandparent;
        } 
		
		else {
            // Case 2: Sibling node is black
            if (N == N->parent->right && N->parent == grandparent->left) {
                // Case 2a: N is a right child, and parent is a left child
                LeftRotate(N->parent);
                N = N->left;
            } 
			
			else if (N == N->parent->left && N->parent == grandparent->right) {
                // Case 2b: N is a left child, and parent is a right child
                RightRotate(N->parent);
                N = N->right;
            }

            // Case 3: Recolor and rotate
            N->parent->color = BLACK;
            grandparent->color = RED;
            if (N == N->parent->left) {
                RightRotate(grandparent);
            } 
			
			else {
                LeftRotate(grandparent);
            }
        }
    }
	
    root->color = BLACK;  // Root must be black
}

void Dictionary::RB_Transplant(Node* u, Node* v) {
    if (u->parent == nil) {
        root = v;
    } 
	
	else if (u == u->parent->left) {
        u->parent->left = v;
    } 
	
	else {
        u->parent->right = v;
    }

    v->parent = u->parent;
}


void Dictionary::RB_DeleteFixUp(Node* N) {
    while (N != root && N->color == BLACK) {
        Node* parentOfN = N->parent;
        Node* sibling = (N == parentOfN->left) ? parentOfN->right : parentOfN->left;

        if (sibling->color == RED) {
            // Case 1: Sibling node is red
            parentOfN->color = RED;
            sibling->color = BLACK;

            if (N == parentOfN->left) {
                LeftRotate(parentOfN);
                sibling = parentOfN->right;
            } 
			
			else {
                RightRotate(parentOfN);
                sibling = parentOfN->left;
            }
        }

        if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
            // Case 2: Sibling node is black, and both its children are black
            sibling->color = RED;
            N = parentOfN;
        } 
		
		else {
            // Case 3: Sibling node is black, and at least one child is red
            if (N == parentOfN->left) {

                if (sibling->right->color == BLACK) {
                    // Case 3a: Sibling's right child is black
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    RightRotate(sibling);
                    sibling = parentOfN->right;
                }

                // Case 3b: Sibling's right child is red
                sibling->color = parentOfN->color;
                parentOfN->color = BLACK;
                sibling->right->color = BLACK;
                LeftRotate(parentOfN);
                N = root;
            } 
			
			else {

                if (sibling->left->color == BLACK) {
                    // Case 3a: Sibling's left child is black
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    LeftRotate(sibling);
                    sibling = parentOfN->left;
                }

                // Case 3b: Sibling's left child is red
                sibling->color = parentOfN->color;
                parentOfN->color = BLACK;
                sibling->left->color = BLACK;
                RightRotate(parentOfN);
                N = root;
            }
        }
    }
	
    N->color = BLACK;  // N must be black
}

void Dictionary::RB_Delete(Node* N) {
    Node* A = N;
    Node* B;

    int originalColor = A->color;
    if (N->left == nil) {
        B = N->right;
        RB_Transplant(N, N->right);
    } 
	
	else if(N->right == nil) {
        B = N->left;
        RB_Transplant(N, N->left);
    }
	
	else {
        A = findMin(N->right);
        originalColor = A->color;
        B = A->right;

        if (A->parent == N) {
            B->parent = A;
        } 
		
		else {
            RB_Transplant(A, A->right);
            A->right = N->right;
            A->right->parent = A;
        }

        RB_Transplant(N, A);
        A->left = N->left;
        A->left->parent = A;
        A->color = N->color;
    }

    if (originalColor == BLACK) {
        RB_DeleteFixUp(B);
    }
}

//Class constructors & destructors-----------------------------------------------------------
Dictionary::Dictionary() {
    nil = new Node("random", 999);
	// nil->left = nil;
	// nil->right = nil;
	// nil->parent = nil;
	// root = nil;
	// root->left = nil;
	// root->right = nil;
	// root->parent = nil;
    root = nil;
    current = nil;
    num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D) {
    nil = new Node("random", 999);
	// nil->left = nil;
	// nil->right = nil;
	// nil->parent = nil;
	// root = nil;
	// root->left = nil;
	// root->right = nil;
	// root->parent = nil;
    root = nil;
    current = nil;
    num_pairs = 0;
    this->preOrderCopy(D.root, D.nil);
}

Dictionary::~Dictionary() {
    postOrderDelete(root);
    delete nil;
}

//Access functions-----------------------------------------------------------------------------------------
int Dictionary::size() const {
	if (num_pairs < 0) {
	throw std::logic_error("Dictionary::size(): Invalid number of pairs.\n");
	}

    return num_pairs;
}

bool Dictionary::contains(keyType k) const {
    Node *rootSearch = search(root, k);

    if (rootSearch != nil) {
        return true;
    } 
	
	else {
        return false;
    }
}

valType& Dictionary::getValue(keyType k) const {
    if (!contains(k)) {
        throw std::logic_error("Dictionary::getValue(): key " + k + " DNE.\n");
    }
    
    Node* N = search(root, k);
    
    if (N == nil) {
        throw std::logic_error("Dictionary::getValue(): key " + k + " DNE.\n");
    }
    
    return N->val;
}

bool Dictionary::hasCurrent() const {
    if (current != nil) {
        return true;
    } 
	
	else {
        return false;
    }
}

keyType Dictionary::currentKey() const {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary::currentKey(): Current is undefined.\n");
    }

    return current->key;
}

valType& Dictionary::currentVal() const {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary::currentVal(): Current is undefined.\n");
    }

    return current->val;
}

//Manipulation procedures-----------------------------------------------------------------------------------------------------
void Dictionary::clear() {
    postOrderDelete(root);
    root = nil;
    current = nil;
    num_pairs = 0;
}

void Dictionary::setValue(keyType k, valType v) { 
    Node* parentNode = nil;
    Node* successor = root;

    while (successor != nil) {
        parentNode = successor;

        if (k < successor->key) {
            successor = successor->left;
        } 
		
		else if(k > successor->key) {
            successor = successor->right;
        } 
		
		else {
            successor->val = v;
            return;
        }
    }

    Node* newNode = new Node(k, v);
	// newNode->parent = parentNode;
    // newNode->left = nil;
    // newNode->right = nil;

    if (parentNode == nil) {
        newNode->parent = nil;
        newNode->left = nil;
        newNode->right = nil;
        root = newNode;
    } 
	
	else if (k < parentNode->key) {
        parentNode->left = newNode;
        newNode->parent = parentNode;
        newNode->left = nil;
        newNode->right = nil;
    } 
	
	else {
        parentNode->right = newNode;
        newNode->parent = parentNode;
        newNode->left = nil;
        newNode->right = nil;
    }

    newNode->color = RED;
    RB_InsertFixUp(newNode);
    num_pairs++;
}  

void Dictionary::remove(keyType k) { 
    if (!contains(k)) {
        throw std::logic_error("Dictionary: remove(): key " + k + " DNE.\n");
    }

    Node* rootNode = search(root, k);

    if(current == rootNode) {
        current = nil;
    }

    RB_Delete(rootNode);
    num_pairs--;
    delete rootNode; 
}

void Dictionary::begin() {
    if (num_pairs != 0) {
        current = findMin(root);
    }

	// else {
	// 	throw std::logic_error("Dictionary::begin(): Invalid number of pairs.\n");
	// }
}

void Dictionary::end() {
    if (num_pairs != 0) {
        current = findMax(root);
    }

	// else {
	// 	throw std::logic_error("Dictionary::end(): Invalid number of pairs.\n");
	// }
}

void Dictionary::next() {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary::next(): Current is undefined.\n");
    }

    current = findNext(current);
}

void Dictionary::prev() {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary::prev(): Current is undefined.\n");
    }

    current = findPrev(current);
}

//Other functions---------------------------------------------------------------------------------------
std::string Dictionary::to_string() const {
    std::string s = "";
    inOrderString(s, root);
    return s;
}

std::string Dictionary::pre_string() const {
    std::string s = "";
    preOrderString(s, root);
    return s;
}

bool Dictionary::equals(const Dictionary& D) const {

    // std::stack<Node*> stackA, stackB;
    // Node* currA = root, *currB = D.root;

    // while (currA != nil || currB != nil || !stackA.empty() || !stackB.empty()) {

    //     while (currA != nil && currB != nil) {
    //         stackA.push(currA);
    //         stackB.push(currB);
    //         currA = currA->left;
    //         currB = currB->left;
    //     }

    //     if (currA != currB) {
    //         return false;
    //     }

    //     currA = stackA.top();
    //     stackA.pop();
    //     currB = stackB.top();
    //     stackB.pop();

    //     if (currA->key != currB->key || currA->val != currB->val) {
    //         return false;
    //     }

    //     currA = currA->right;
    //     currB = currB->right;
    // }

    // return true;

    std::string A = to_string();
    std::string B = D.to_string();

    if(num_pairs == D.num_pairs && A == B) {
        return true;
    } 
	
	else {
        return false;
    }
}

//Overloaded oeprators-----------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& stream, Dictionary& D) {
    return stream << D.Dictionary::to_string();
}

bool operator==(const Dictionary& A, const Dictionary& B) {
	if (A.num_pairs == 0 && B.num_pairs == 0) {
		return true;
	}

    return A.Dictionary::equals(B);
}

Dictionary& Dictionary::operator=(const Dictionary& D) {
    if(this != &D) {
        Dictionary temp = D;

        std::swap(nil, temp.nil);
        std::swap(root, temp.root);
        std::swap(current, temp.current);
        std::swap(num_pairs, temp.num_pairs);
    }
    return *this;
}