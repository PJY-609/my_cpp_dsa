#pragma once

#include "../bintree/BinTree.h"

// BinTree ~= List
// BST ~= BinTree + Sorted Vector

// Inorder of BST is an order array

// do not contain identical elements

// Expected height of BST ~ O(sqrt(n))
// n nodes can form S(n) BSTs, S(n) = catalan(n)

// BBST: Balanced BST
// Tree height does not (asymtotically) exceed O(logn)

// Unbalanced BST --rotation--> Balanced BST
// rotation ~ O(logn) or even O(1)


template <typename T>
class BST : public BinTree<T> {
protected:
	BinNodePosi(T) _hot;
public:
	BinNodePosi(T)& search(T const &e); // O(h), h = height of BST
	BinNodePosi(T) insert(T const &e);
	bool remove(T const &e);

};

#include "../bst/BST_Implementation.h"