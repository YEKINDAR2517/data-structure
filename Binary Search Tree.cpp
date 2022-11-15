#ifndef __COMPLEX__
#define __COMPLEX__

//#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//���ڵ�Ķ���
class Node {
public:
	char value;//�ڵ��д����Ԫ��
	Node* left;//ָ��ýڵ������
	Node* right;//ָ��ýڵ���Һ���

	Node(char c) {
		value = c;
		left = NULL;
		right = NULL;
	}
};

//�������Ķ���
class Tree {
private:
	Node* root;//���ڵ�
	int depth;//�����������
	int size;
	int width;
	int* count;

	//ͨ��ǰ���������������
	Node* create(Node* node) {
		char c;
		cin.get(c);
		if (c == '#') {
			node = NULL;
		}
		else {
			node = new Node(c);
			node->left = create(node->left);//����������
			node->right = create(node->right);//����������
		}
		return node;
	}

	//���������Ԫ��
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

	//�������������
	void medium_traversal(Node* node) {
		if (node != NULL)
		{
			medium_traversal(node->left);
			cout << node->value;
			medium_traversal(node->right);
		}
	}

	////�������������
	//void level_traversal(Node* node) {
	//	queue q(size);//�ѽ�����ڶ�����
	//	q.enqueue(node);
	//	while (q.size != 0) {
	//		Node* n = q.dequeue();
	//		cout << n->value;
	//		if (n->left != NULL) q.enqueue(n->left);//ͬһ�����������������ֵ
	//		if (n->right != NULL) q.enqueue(n->right);
	//	}
	//}

	//��ö����������
	int get_depth(Node* node) {
		int d1, d2;
		if (node == NULL) return 0;
		d1 = get_depth(node->left);//��������������
		d2 = get_depth(node->right);//��������������
		if (d1 > d2) return d1 + 1;
		else return d2 + 1;//��������������ȵĽϴ�ֵ��1(��Ҫ���ϸ����)
	}

	////�ǵݹ�ʵ���������������
	//void medium_traversal(Node* node) {
	//	stack s(size);//ջ�д�Ž��
	//	Node* p = node;
	//	while (p != NULL || s.top != 0) {
	//		if (p != NULL) {
	//			s.push(p);
	//			p = p->left;//�Ȱ�����������ջ��
	//		}
	//		else {
	//			Node* q = s.pop();
	//			cout << q->value;
	//			p = q->right;
	//		}
	//	}
	//}

	//ɾ�����node��������
	void delete_Node(Node* node) {
		if (node == NULL) return;
		delete_Node(node->left); //ɾ��������
		delete_Node(node->right);//ɾ��������
		free(node);
	}

	//ɾ��valueΪc�Ľ��node��������
	void remove(Node*& node, char c) {
		if (node == NULL)
			return;

		if (node->value == c) {  //��node��valueΪ��Ҫɾ����Ԫ�� �����ɾ��
			delete_Node(node);   //ɾ���������ڵ�
			node = NULL;         //��nodeָ��NULL
		}
		if (node != NULL) {		 //�ٴν���һ���жϵ�node��Ϊ��ʱ��������ִ��
			remove(node->left, c);
			remove(node->right, c);
		}
	}


	//������Ŀ��
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

	//����������
	int get_depth() {
		return depth;
	}

	//������Ŀ��
	int get_width() {
		get_width(root,0);
		for (int i = 0; i < 100; i++) {
			if (count[i] > width){
				width = count[i];
			}	
		}
		return width;
	}

	//�Ӹ��ڵ㿪ʼ���Ԫ��
	void add(char e) {
		root = add(root, e);
	}

	//�Ӹ��ڵ㿪ʼ����������
	void create() {
		root = create(root);
	}

	//�Ӹ��ڵ㿪ʼ�������
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