#include<iostream>
using namespace std;

//ջ�Ķ���
class stack{
public:
	int top;//ջ��
	int* arr;//�������
	int size;//ջ�����ݵ�����
	
	stack(){
		top=0;
		arr=new int[26];
		size = 0;
	}
	
	~stack(){
		delete[] arr;
	}
	
	void push(int a){//������ջ
		arr[top]=a;
		top++;
		size++;
	}
	
	void pop(){//���ݳ�ջ
		top--;
		size--;
	}
};

//���������Ķ���
class Huffman_Tree {
private:
	//�ڵ�Ķ���
	class Node {
	public:
		int weight;//Ȩֵ
		char data;//��ĸ
		Node* left;//����
		Node* right;//�Һ���

		Node() {
			weight = 0;
			left = NULL;
			right = NULL;
			data = '{';//'{'��ascii��Ϊ123,��'z'��
		}

		Node(int w) {
			weight = w;
			left = NULL;
			right = NULL;
			data = '{';
		}
		
	};

	//��¼ÿ����ĸ������
	class character {
	public:
		int size;//ÿ����ĸ���ֵĴ���
		int* code;//ÿ����ĸ�Ĺ��������� 
		int code_size;//ÿ����ĸ�Ĺ��������볤��

		character() {
			size = 0;
			code = new int[26];
			code_size = 0;
		}

		~character() {
			delete[] code;
		}
	};

	Node* root;//���ڵ�
	character* letters;//��¼�ַ����г��ֵ���ĸ�ĸ���,�Լ�������ĸ�ı���
	stack s;//ͨ��ջʵ�ֹ���������
	int* code;//codeΪ�ù��������Ĺ���������
	int code_length;//�ù��������Ĺ��������볤��

	//�õ�ĳһ��ĸ�Ĺ���������
	void set_code(character* letters,int n) {
		for (int i=0;i<s.size;i++) {
			letters[n].code[i] = s.arr[i];//����ǰջ�ڵı��븴��
		}
		letters[n].code_size = s.size;//����ĸ�Ĺ��������뼴Ϊ��ǰջ�ĳ���
	}

	//��ԭ�ַ���ת��Ϊ���������벢���
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

	//������ΪNode*������arr���ҳ�Ȩֵ��С�Ľڵ�(Ȩֵ��ͬʱ,��ĸС������,�Ұ����Ⱥ�˳��)
	Node* select_min(Node** arr, int n) {//nΪarr�ĳ���
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

	//������������
	void create(Node** arr, int n) {//arr�д����n���ڵ�
		int len = n;//lenΪarr�з���Ԫ�صĸ���
		char d = '{';
		Node* min1 = NULL, * min2 = NULL, * r = NULL;

		while (len > 1) {//�������н�ʣһ��Ԫ��ʱ�˳�ѭ��
			//�ҳ���ǰ��С������Ȩֵ(min1<=min2)
			min1 = select_min(arr, n);
			len--;
			min2 = select_min(arr, n);
			len--;

			r = new Node(min1->weight + min2->weight);
			r->data = d;//�����ʼ�ڵ�ϳɵĽڵ��data+1,�������Ⱥ�˳��
			d++;
			r->left = min1;
			r->right = min2;

			int i = 0;
			while (arr[i] != NULL) {
				i++;
			}//arr[i]==NULL���˳�ѭ��
			arr[i] = r;
			len++;
		}

		root = r;
	}

	//��ĳһ�ڵ㿪ʼת��Ϊ����������
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

	//�Ӹ��ڵ㿪ʼת��Ϊ����������
	void encode() {
		encode(root);
	}

	//���������������(�����ִ�Сд)
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

	//ʵ���������
	void operation() {
		cout << "����������һ���ַ���(���ɴ�СдӢ����ĸ�����ҳ��Ȳ�����360,���ٰ���2����ĸ):" << endl;

		char a;//a�����������ĸ
		char* s=new char[360]{ '0' };//s��¼������ַ���
		int kinds = 0, num = 0;//kindsΪ�������ĸ�������,numΪ�������ĸ�ܸ���
		//������ĸ,����¼ÿ����ĸ�ĸ����Լ��������ĸ������
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
			cout << "������ַ���ֻ����һ����ĸ,����������:" << endl;
		}
		
		//arr��ָ������,����ÿ�����ڵ��ָ��
		Node** arr = new Node * [kinds];
		int j = 0;
		for (int i = 0; i < 26; i++) {
			if (letters[i].size != 0) {
				arr[j] = new Node(letters[i].size);
				arr[j]->data = 'a' + i;
				j++;
			}
		}

		create(arr, kinds);//������������
		encode();//���й���������
		print(s,num);//�������������
		decode();//���������������(�����ִ�Сд)
		
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
	Huffman_Tree T;//�½�һ��������������
	T.operation();//����operation����

	return 0;
}
