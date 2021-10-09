#pragma once

template <typename T>
BinNodePosi(T) & BST<T>::search(T const &e) {
	if (!_root || e == _root->data) {
		_hot = NULL; return _root;
	}
	_hot = _root;
	while (true) {
		BinNodePosi(T) & c = _hot->data < e ? _hot->lc : _hot->rc;
		if (!c || e == c->data) return c;
		_hot = c;
	}
}

template <typename T>
BinNodePosi(T) BST<T>::insert(T const & e) {
	BinNodePosi(T) x = search(e); 
	if (x) return x; // no repeated elem
	x = new BinNode<T>(e, _hot);
	_size++; updateHeightAbove(x);
	return x;
}

template <typename T>
bool BST<T>::remove(T const &e) {
	BinNodePosi(T) x = search(e); if (!x) return false;
	removeAt(x, _hot);
	_size--; updateHeightAbove(_hot);
	return true;
}

template <typename T>
static BinNodePosi(T) removeAt(BinNodePosi(T) &x, BinNodePosi(T) &hot) {
	BinNodePosi(T) w = x;
	BinNodePosi(T) succ = NULL;

	if (!HasRChild(*x)) {
		succ = x = x->lc;
	}
	else if (!HasLChild(*x)) {
		succ = x = x->rc;
	}
	else { // have both left child and right child
		w = w->succ(); swap(x->data, w->data); // swap x with its immediate successor
		BinNodePosi(T) u = w->parent;
		((u == x) ? u->rc : u->lc) = succ = w->rc; // w must be the leftmost of x's right subtree
	}

	hot = w->parent;
	if (succ) succ->parent = hot;
	release(w->data); release(w);
	return succ;

}