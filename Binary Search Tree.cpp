#ifndef __COMPLEX__
#define __COMPLEX__

//#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//树节点的定义
class Node {
public:
	char value;//节点中储存的元素
	Node* left;//指向该节点的左孩子
	Node* right;//指向该节点的右孩子

	Node(char c) {
		value = c;
		left = NULL;
		right = NULL;
	}
};

//二叉树的定义
class Tree {
private:
	Node* root;//根节点
	int depth;//二叉树的深度
	int size;
	int width;
	int* count;

	//通过前序遍历创建二叉树
	Node* create(Node* node) {
		char c;
		cin.get(c);
		if (c == '#') {
			node = NULL;
		}
		else {
			node = new Node(c);
			node->left = create(node->left);//构造左子树
			node->right = create(node->right);//构造右子树
		}
		return node;
	}

	//向树中添加元素
	Node* add(Node* node, char e) {
		if (node == NULL) {
			size++;
			return new Node(e);
		}
		if (e < node->value) {
			node->left = add(node->left, e);
		}else if (e > node->value) {
			node->right = add(node->right, e);
		}
		return node;
	}

	//中序遍历二叉树
	void medium_traversal(Node* node) {
		if (node != NULL)
		{
			medium_traversal(node->left);
			cout << node->value;
			medium_traversal(node->right);
		}
	}

	////层序遍历二叉树
	//void level_traversal(Node* node) {
	//	queue q(size);//把结点存放在队列中
	//	q.enqueue(node);
	//	while (q.size != 0) {
	//		Node* n = q.dequeue();
	//		cout << n->value;
	//		if (n->left != NULL) q.enqueue(n->left);//同一层先输出左子树的数值
	//		if (n->right != NULL) q.enqueue(n->right);
	//	}
	//}

	//获得二叉树的深度
	int get_depth(Node* node) {
		int d1, d2;
		if (node == NULL) return 0;
		d1 = get_depth(node->left);//获得左子树的深度
		d2 = get_depth(node->right);//获得右子树的深度
		if (d1 > d2) return d1 + 1;
		else return d2 + 1;//返回左右子树深度的较大值加1(需要加上父结点)
	}

	////非递归实现中序遍历二叉树
	//void medium_traversal(Node* node) {
	//	stack s(size);//栈中存放结点
	//	Node* p = node;
	//	while (p != NULL || s.top != 0) {
	//		if (p != NULL) {
	//			s.push(p);
	//			p = p->left;//先把左子树放入栈中
	//		}
	//		else {
	//			Node* q = s.pop();
	//			cout << q->value;
	//			p = q->right;
	//		}
	//	}
	//}

	//删除结点node及其子树
	void delete_Node(Node* node) {
		if (node == NULL) return;
		delete_Node(node->left); //删除左子树
		delete_Node(node->right);//删除右子树
		free(node);
	}

	//删除value为c的结点node及其子树
	void remove(Node*& node, char c) {
		if (node == NULL)
			return;

		if (node->value == c) {  //若node的value为想要删除的元素 则进行删除
			delete_Node(node);   //删除包括根节点
			node = NULL;         //让node指向NULL
		}
		if (node != NULL) {		 //再次进行一次判断当node不为空时继续向下执行
			remove(node->left, c);
			remove(node->right, c);
		}
	}


	//获得树的宽度
	void get_width(Node* node,int level) {
		if (node == NULL)  return;
		count[level]++;
		get_width(node->left, level + 1);
		get_width(node->right, level + 1);
	}

public:
	Tree() {
		root = NULL;
		depth = 0;
		size = 0;
		width = 0;
		count = new int[100]{ 0 };
	}

	//获得树的深度
	int get_depth() {
		return depth;
	}

	//获得树的宽度
	int get_width() {
		get_width(root,0);
		for (int i = 0; i < 100; i++) {
			if (count[i] > width){
				width = count[i];
			}	
		}
		return width;
	}

	//从根节点开始添加元素
	void add(char e) {
		root = add(root, e);
	}

	//从根节点开始创建二叉树
	void create() {
		root = create(root);
	}

	//从根节点开始中序遍历
	void medium_traversal() {
		medium_traversal(root);
		cout << endl;
	}
};

int main()
{
	Tree t;
	t.create();
	t.medium_traversal();
	cout << t.get_width() << endl;
	return 0;
}







#endif