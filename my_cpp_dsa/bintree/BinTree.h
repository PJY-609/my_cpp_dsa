#pragma once

/* Tree */
/*
 edge(e) and node(n)
 e = (n - 1) ~ O(n)

  Tree vs Graph
  In a tree there exist only one path between any two vertices,
  whereas a graph can have unidirectional and bidirectional paths between the nodes.

  path(v) ~ v ~ subtree(v)
  the path from root to v = v = the subtree of v

  depth(v) = |path(v)|

  height(v) = height(subtree(v))

 height of tree
 height(T) >= height(v) + depth(v)

 BinTree and Multi Branch Tree
 Left-child Right-sibling representation
*/

/* BinTree */
/*
 node n and height h
 h < n < 2^(h + 1)

*/

#include "../bintree/BinNode.h"

template <typename T> class BinTree {
protected:
	int _size; BinNodePosi(T) _root;
	virtual int updateHeight(BinNodePosi(T) x);
	void updateHeightAbove(BinNodePosi(T) x);
public:
	BinTree() : _size(0), _root(NULL) {}
	~BinTree() { if (_size > 0) remove(_root); }

	BinNodePosi(T) root() const { return _root; }
	int size() const { return _size; }
	bool empty() const { return !_root; }

	BinNodePosi(T) insertAsRoot(T const &e);

	BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const &e);
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const &e);

	BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &S);
	BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* &S);

	int remove(BinNodePosi(T) x);
	BinTree<T>* secede(BinNodePosi(T) x);

	template <typename VST> void travPre(VST &visit) { if (_root) _root->travPre(visit); }
	template <typename VST> void travIn(VST &visit) { if (_root) _root->travIn(visit); }
	template <typename VST> void travPost(VST &visit) { if (_root) _root->travPost(visit); }
	template <typename VST> void travLevel(VST &visit) { if (_root) _root->travLevel(visit); }

};

#include "../bintree/BinTree_Implementation.h"

// BinTree reconstruction
// [PreOrder/PostOrder] + InOrder