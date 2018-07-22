#pragma once
#include "SimpleAllocate.h"

namespace TinySTL
{
	template<class T>
	struct AVLTree_Node
	{
		typedef T value_type;
		typedef size_t size_type;
		typedef AVLTree_Node<T> * node_ptr;
		size_type height;
		value_type key;
		node_ptr _left;
		node_ptr _right;
		node_ptr _parent;
		AVLTree_Node()
		{
			_left = nullptr;
			_right = nullptr;
			_parent = nullptr;
		}
	};

	template<class T>
	int Height(AVLTree_Node<T> *r)
	{
		if (r==nullptr)
			return -1;
		return r->height;
	}

	template<class T>
	T max(T a, T b)
	{
		if (a > b)
			return a;
		return b;
	}

	template<class T>
	T abs(T a)
	{
		if (a < 0)
			return -a;
		return a;
	}
	template<class T>
	AVLTree_Node<T> * singleRotateLeft(AVLTree_Node<T>* root);

	template<class T>
	AVLTree_Node<T> * singleRotateRight(AVLTree_Node<T>*root);

	template<class T>
	AVLTree_Node<T>* doubleRotateLeft(AVLTree_Node<T>*root);

	template<class T>
	AVLTree_Node<T>* doubleRotatoRight(AVLTree_Node<T>*root);

	template<class T>
	AVLTree_Node<T>* insertAVLTree(AVLTree_Node<T> *&root, AVLTree_Node<T> *&root, T value);

	template<class T>
	AVLTree_Node<T>* findMin(AVLTree_Node<T> * root);

	template<class T>
	AVLTree_Node<T> Fix(AVLTree_Node<T> root);

	template<class T>
	AVLTree_Node<T>* deleteAVLNode(AVLTree_Node<T> *&root, T value);

	template<class T>
	void MidTraverse(AVLTree_Node<T> *root);

	template<class T>
	AVLTree_Node<T> *findNode(AVLTree_Node<T> *root, T value);

	template<class T>
	AVLTree_Node<T>* findNext(AVLTree_Node<T>*root);

	template<class T>
	AVLTree_Node<T>* findPre(AVLTree_Node<T>*root);

	template<class T>
	AVLTree_Node<T> * singleRotateLeft(AVLTree_Node<T>* root)
	{
		typedef AVLTree_Node<T> * node_ptr;
		node_ptr * tmp = root->_left;	// ��ת�Ĳ���
		root->_left = tmp->_right;
		tmp->_right = root;
		root->height = max<int>(Height(root->_left), Height(root->_right));
		tmp->height = max<int>(Height(tmp->_left), Height(tmp->_right));
		return tmp;
	}

	template<class T>
	AVLTree_Node<T> * singleRotateRight(AVLTree_Node<T>*root)
	{
		typedef AVLTree_Node<T> * node_ptr;
		node_ptr * tmp = root->_right;
		root->_right = tmp->_left;
		tmp->_left = root;
		root->height = max<int>(Height(root->_left), Height(root->_right));
		tmp->height = max<int>(Height(tmp->_left), Height(tmp->_right));
		return tmp;
	}

	template<class T>
	AVLTree_Node<T>* doubleRotateLeft(AVLTree_Node<T>*root)
	{		
		root->_left = singleRotateRight(root->_left);
		return singleRotateLeft(root);
	}

	template<class T>
	AVLTree_Node<T>* doubleRotatoRight(AVLTree_Node<T>*root)
	{
		root->_right = singleRotateLeft(root->right);
		return singleRotateRight(root);
	}

	template<class T>
	AVLTree_Node<T>* insertAVLTree(AVLTree_Node<T> *&root, AVLTree_Node<T> *&root, T value)
	{
		typedef SimpleAllocate<AVLTree_Node<T>> alloc;
		if (root == nullptr)
		{
			root = alloc::allocate(1);
			alloc::construct(root, AVLTree_Node<T>());
			root->key = value;
			root->_parent = parent;
		}
		else
		{
			if (root->key < value)
			{
				root->_left = insertAVLTree(root->_left, root, value);
				if (Height(root->_left) - Height(root->_right) >= 2)
				{
					if (root->_left->key < value)
						root = doubleRotatoLeft(root);
					else
						root = singleRotateLeft(root);
				}				
			}
			else if (root->key > value)
			{
				root->_right = insertAVLTree(root->_right, root, value);
				if (Height(root->_right) - Height(root->_left) >= 2)
				{
					if (root->_right->key < value)
						root = doubleRotatoRight(root);
					else
						root = singleRotateRight(root);
				}
			}
			else
				return root;	// ������
		}
		root->height = max<int>(Height(r->left), Height(r->right)) + 1;
		return root;
	}

	template<class T>
	AVLTree_Node<T>* findMin(AVLTree_Node<T> * root)
	{
		if (root != nullptr)
		{
			while (root->_left != nullptr)
				root = root->_left;
		}
		return root;
	}

	template<class T>
	AVLTree_Node<T> Fix(AVLTree_Node<T> root)
	{
		if (Height(root->_left) > Height(root->_right))
		{
			//K2����ӵ�����ӵĸ߶ȴ���K2������ӵ��Ҷ��ӵĸ߶�, ִ������ת, ����ִ����-��˫��ת
			if (Height(root->_left->_left) > Height(root->_left->_right))
				root = singleRotateLeft(root);
			else if (Height(root->_left->_left) < Height(root->_left->_right))
				root = doubleRotatoRight(root);
		}
		else if (Height(root->_left) < Height(root->_right))
		{
			//K2�Ҷ��ӵ��Ҷ��ӵĸ߶ȴ���K2���Ҷ��ӵ�����ӵĸ߶�, ִ���ҵ���ת, ����ִ����-��˫��ת
			if (Height(root->_right->_right) > Height(root->_right->_left))
				root = singleRotateRight(root);
			else if (Height(root->_right->_right) < Height(root->_right->_left))
				root = doubleRotatoRight(root);
		}

		return root;
	}

	template<class T>
	AVLTree_Node<T>* deleteAVLNode(AVLTree_Node<T> *&root, AVLTree_Node<T>*parent, T value)
	{
		typedef SimpleAllocate<AVLTree_Node<T>> alloc;
		AVLTree_Node<T> * ptr;
		if (root == nullptr)
			return nullptr;
		// �ҵ���ǰ�ڵ�
		if (root->key == value)
		{
			if (root->_left && root->_right)
			{
				ptr = findMin(root->_right);
				root->key = ptr->key;
				r->_right = deleteAVLNode(root->_right, root->key);
			}
			else
			{
				ptr = root;
				if (r->_left != nullptr)
				{
					root = root->_left;
					root->_parent = parent;
				}					
				else if (r->_right != nullptr)
				{
					root = root->_right;
					root->_parent = parent;
				}									
				alloc::destroy(ptr);
				alloc::deallocate(ptr);
				prt = nullptr;
			}			
		}
		else
		{
			if (root->key < value)
				root->_right = deleteAVLNode(root->_right, value);
			else
				root->_left = deleteAVLNode(root->_left, value);
		}
		if (root)
		{
			root->height = max<int>(Height(root->_left), Height(root->_right)) + 1;
			if (abs<int>(Height(root->_left) - Height(root->_right))>=2)
			{
				root = Fix(root);
				root->height = max<int>(Height(root->_left), Height(root->_right)) + 1;
			}
		}
		return root;
	}

	template<class T>
	void MidTraverse(AVLTree_Node<T> *root)
	{
		if (root == nullptr)
			return;
		MidTraverse(root->_left);
		cout << root->key << " ";
		MidTraverse(root->_right);
	}

	template<class T>
	AVLTree_Node<T> *findNode(AVLTree_Node<T> *root, T value)
	{
		if (root == nullptr)
			return nullptr;
		if (value == root->key)
			return root;
		if (value < root->key)
			return findNode(root->_left, value);
		else
			return findNode(root->_right, value);
	}

	template<class T>
	AVLTree_Node<T>* findNext(AVLTree_Node<T>*root)
	{
		if (root == nullptr)
			return root;
		if (root->_right != nullptr)
		{
			// �ҵ�����ڵ�
			root = root->_right;
			while (root->_left)
				root = root->_left;
			return root;
		}
		else
		{
			// �ҵ��Ǹ��ڵ�����ӽڵ�ĵ�һ��
			while (root->_parent && root->_parent->_right == root)
				root = root->_parent;
			return root->_parent;
		}
	}

	template<class T>
	AVLTree_Node<T>* findPre(AVLTree_Node<T>*root)
	{
		if (root == nullptr)
			return root;
		if (root->_left != nullptr)
		{
			// �ҵ����ҽڵ�
			root = root->_left;
			while (root->_right)
				root = root->_right;
			return root;
		}
		else
		{
			while (root->_parent && root->_parent->_left == root)
				root = root->_parent;
			return root->_parent;
		}
	}

	template<class T>
	struct AVLTree_Node_Iterator
	{
		typedef T value_type;
		typedef AVLTree_Node<T> * node_ptr;
		typedef AVLTree_Node<T> node_type;
		AVLTree_Node_Iterator<T> operator++(int);		// ����
		AVLTree_Node_Iterator<T> operator++();
		AVLTree_Node_Iterator<T> operator--(int);
		AVLTree_Node_Iterator<T> operator--();
		AVLTree_Node_Iterator(node_ptr it) :ptr(it) {}
		node_ptr ptr;
		bool operator ==(const AVLTree_Node_Iterator<T> & a)
		{
			return ptr == a.ptr;
		}
		bool operator !=(const AVLTree_Node_Iterator<T> & a)
		{
			return ptr != a.ptr;
		}
		value_type operator*()
		{
			return ptr->key;
		}
	};


	template<class T>
	AVLTree_Node_Iterator<T> AVLTree_Node_Iterator<T>::operator++(int)
	{
		auto res = ptr;
		ptr = findNext(ptr);
		return AVLTree_Node_Iterator<T>(res);
	}

	template<class T>
	AVLTree_Node_Iterator<T> AVLTree_Node_Iterator<T>::operator++()
	{
		ptr = findNext(ptr);
		return *this;
	}

	template<class T>
	AVLTree_Node_Iterator<T> AVLTree_Node_Iterator<T>::operator--(int)
	{
		auto res = ptr;
		ptr = findPre(ptr);
		return AVLTree_Node_Iterator<T>(res);
	}

	template<class T>
	AVLTree_Node_Iterator<T> AVLTree_Node_Iterator<T>::operator--()
	{
		ptr = findPre(ptr);
		return *this;
	}

}