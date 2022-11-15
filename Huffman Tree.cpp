#include<iostream>
using namespace std;

//栈的定义
class stack{
public:
	int top;//栈顶
	int* arr;//存放数据
	int size;//栈内数据的数量
	
	stack(){
		top=0;
		arr=new int[26];
		size = 0;
	}
	
	~stack(){
		delete[] arr;
	}
	
	void push(int a){//数据入栈
		arr[top]=a;
		top++;
		size++;
	}
	
	void pop(){//数据出栈
		top--;
		size--;
	}
};

//哈夫曼树的定义
class Huffman_Tree {
private:
	//节点的定义
	class Node {
	public:
		int weight;//权值
		char data;//字母
		Node* left;//左孩子
		Node* right;//右孩子

		Node() {
			weight = 0;
			left = NULL;
			right = NULL;
			data = '{';//'{'的ascii码为123,比'z'大
		}

		Node(int w) {
			weight = w;
			left = NULL;
			right = NULL;
			data = '{';
		}
		
	};

	//记录每个字母的数据
	class character {
	public:
		int size;//每个字母出现的次数
		int* code;//每个字母的哈夫曼编码 
		int code_size;//每个字母的哈夫曼编码长度

		character() {
			size = 0;
			code = new int[26];
			code_size = 0;
		}

		~character() {
			delete[] code;
		}
	};

	Node* root;//根节点
	character* letters;//记录字符串中出现的字母的个数,以及各个字母的编码
	stack s;//通过栈实现哈夫曼编码
	int* code;//code为该哈夫曼树的哈夫曼编码
	int code_length;//该哈夫曼树的哈夫曼编码长度

	//得到某一字母的哈夫曼编码
	void set_code(character* letters,int n) {
		for (int i=0;i<s.size;i++) {
			letters[n].code[i] = s.arr[i];//将当前栈内的编码复制
		}
		letters[n].code_size = s.size;//该字母的哈夫曼编码即为当前栈的长度
	}

	//将原字符串转化为哈夫曼编码并输出
	void print(char* s, int len) {
		int i = 0;
		for (int k = 0; k < len; k++) {
			if (s[k] >= 'a' && s[k] <= 'z') {
				for (int j = 0; j < letters[s[k] - 'a'].code_size; j++) {
					cout << letters[s[k] - 'a'].code[j];
					code[i]= letters[s[k] - 'a'].code[j];
					i++;
				}
			}
			else if (s[k] >= 'A' && s[k] <= 'Z') {
				for (int j = 0; j < letters[s[k] - 'A'].code_size; j++) {
					cout << letters[s[k] - 'A'].code[j];
					code[i] = letters[s[k] - 'A'].code[j];
					i++;
				}
			}
		}
		code_length = i;
		cout << endl;
	}

	//在类型为Node*的数组arr中找出权值最小的节点(权值相同时,字母小的优先,且按照先后顺序)
	Node* select_min(Node** arr, int n) {//n为arr的长度
		Node* min_node = NULL;
		int min = 0, min_index = 0;
		for (int i = 0; i < n; i++) {
			if (min == 0 && arr[i] != NULL) {
				min = arr[i]->weight;
				min_index = i;
				i++;
			}
			if (i < n) {
				if (arr[i] != NULL && arr[i]->weight != 0 && arr[i]->weight <= min) {
					if ((arr[i]->weight == min && arr[i]->data < arr[min_index]->data) || (arr[i]->weight < min)) {
						min_index = i;
						min = arr[i]->weight;
					}
				}
			}
		}
		min_node = arr[min_index];
		arr[min_index] = NULL;

		return min_node;
	}

	//创建哈夫曼树
	void create(Node** arr, int n) {//arr中存放了n个节点
		int len = n;//len为arr中非零元素的个数
		char d = '{';
		Node* min1 = NULL, * min2 = NULL, * r = NULL;

		while (len > 1) {//当数组中仅剩一个元素时退出循环
			//找出当前最小的两个权值(min1<=min2)
			min1 = select_min(arr, n);
			len--;
			min2 = select_min(arr, n);
			len--;

			r = new Node(min1->weight + min2->weight);
			r->data = d;//多个初始节点合成的节点的data+1,以区分先后顺序
			d++;
			r->left = min1;
			r->right = min2;

			int i = 0;
			while (arr[i] != NULL) {
				i++;
			}//arr[i]==NULL则退出循环
			arr[i] = r;
			len++;
		}

		root = r;
	}

	//从某一节点开始转化为哈夫曼编码
	void encode(Node* node) {
		if(node==NULL) return;
		if(node->data>='a' && node->data<='z') {
			set_code(letters,node->data-'a');
		}
		if (node->data >= 'A' && node->data <= 'Z') {
			set_code(letters,node->data-'A');
		}
		if(node->left!=NULL){
			s.push(0);
			encode(node->left);
		}
		if(node->right!=NULL){
			s.push(1);
			encode(node->right);
		}
		s.pop();
	}

	//从根节点开始转化为哈夫曼编码
	void encode() {
		encode(root);
	}

	//将哈夫曼编码解码(不区分大小写)
	void decode() {
		int i = 0;
		while (i<code_length) {
			Node* node = root;
			while (1) {
				if (code[i] == 0) {
					node = node->left;
					i++;
				}
				else if (code[i] == 1) {
					node = node->right;
					i++;
				}

				if (node->left == NULL && node->right == NULL) {
					cout << node->data;
					break;
				}
			}
		}
	}

public:
	Huffman_Tree() {
		root = NULL;
		letters = new character[26];
		code = new int[10000];
		code_length = 0;
	}

	//实现所需操作
	void operation() {
		cout << "请输入输入一个字符串(仅由大小写英文字母构成且长度不超过360,至少包含2种字母):" << endl;

		char a;//a接受输入的字母
		char* s=new char[360]{ '0' };//s记录输入的字符串
		int kinds = 0, num = 0;//kinds为输入的字母种类个数,num为输入的字母总个数
		//输入字母,并记录每个字母的个数以及输入的字母的种类
		while (1) {
			int i = 0;
			while (num <= 360) {
				a = cin.get();
				if (a == '\n') break;

				if (a >= 'a' && a <= 'z') {
					if (letters[int(a - 'a')].size == 0) kinds++;
					letters[int(a - 'a')].size++;
					num++;
				}
				else if (a >= 'A' && a <= 'Z') {
					if (letters[int(a - 'A')].size == 0) kinds++;
					letters[int(a - 'A')].size++;
					num++;
				}

				s[i] = a;
				i++;
			}

			if (kinds >= 2) break;
			cout << "输入的字符串只包含一种字母,请重新输入:" << endl;
		}
		
		//arr是指针数组,保存每个树节点的指针
		Node** arr = new Node * [kinds];
		int j = 0;
		for (int i = 0; i < 26; i++) {
			if (letters[i].size != 0) {
				arr[j] = new Node(letters[i].size);
				arr[j]->data = 'a' + i;
				j++;
			}
		}

		create(arr, kinds);//创建哈夫曼树
		encode();//进行哈夫曼编码
		print(s,num);//输出哈夫曼编码
		decode();//将哈夫曼编码解码(不区分大小写)
		
		delete[] arr;
		delete[] s;
	}

	~Huffman_Tree() {
		delete[] letters;
		delete[] code;
	}
};

int main()
{
	Huffman_Tree T;//新建一个哈夫曼树对象
	T.operation();//调用operation函数

	return 0;
}
