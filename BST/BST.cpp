#include <bits/stdc++.h>
#include <fstream>
#include <stdlib.h>
#include <conio.h>
using namespace std;

class BST;
class TreeNode{
private:
	TreeNode *leftchild;
	TreeNode *rightchild;
	TreeNode *parent;
	int label;
	int money;
	int amount;

public:
	TreeNode(): leftchild(NULL), rightchild(NULL), parent(NULL), label(0), money(0), amount(0){};
	TreeNode(int label, int money, int amount): leftchild(NULL), rightchild(NULL), parent(NULL), label(label), money(money), amount(amount){};	

	void print(){ cout << label << " " << money << " " << amount << endl; }

	friend class BST;
};

class BST{
private:
	TreeNode *root;
	TreeNode* left_most(TreeNode *node);
	TreeNode* right_most(TreeNode *node);
	TreeNode* successor(TreeNode* node);

public:
	BST(): root(NULL){};

	TreeNode* search(int label);
	int price_search();
	void insert(TreeNode node);
	void remove(int label);
	void inorder_print();
	void inorder_print(TreeNode *current);
	void levelorder_print();
	void data_export();
};

TreeNode* BST::search(int label){
	TreeNode *current = root;

	while(current != NULL && current -> label != label){
		if(current -> label > label)
			current = current -> leftchild;
		else
			current = current -> rightchild;
	}

	return current;
}

int BST::price_search(){
	int label, price = 0;
	queue<TreeNode> que;

	que.push(*root);
	while(!que.empty()){
		TreeNode current = que.front();
		que.pop();

		if(current.money > price) label = current.label;

		if(current.leftchild) que.push(*current.leftchild);
		if(current.rightchild) que.push(*current.rightchild);
	}

	return label;
}

void BST::insert(TreeNode node){
	TreeNode *cur = NULL;
	TreeNode *pre = NULL;
	TreeNode *insert_node = new TreeNode(node.label, node.money, node.amount);

	cur = root;
	while(cur != NULL){
		pre = cur;
		if(insert_node -> label < cur -> label)
			cur = cur -> leftchild;
		else
			cur = cur -> rightchild;
	}

	insert_node -> parent = pre;

	if(pre == NULL)
		this -> root = insert_node;
	else if(insert_node -> label < pre -> label)
		pre -> leftchild = insert_node;
	else
		pre -> rightchild = insert_node;
}

TreeNode* BST::left_most(TreeNode *current){
	while(current -> leftchild != NULL)
		current = current -> leftchild;

	return current;
}

TreeNode* BST::right_most(TreeNode *current){
	while(current -> rightchild != NULL)
		current = current -> rightchild;

	return current;
}

void BST::remove(int label){
	TreeNode *del = search(label);
	TreeNode *child = new TreeNode;

	if(del == NULL) return;

	if(del -> leftchild)
		child = right_most(del -> leftchild);
	else
		child = left_most(del -> rightchild);

	child -> parent = del -> parent;
	child -> leftchild = del -> leftchild;
	child -> rightchild = del -> rightchild;

	delete del;
}

TreeNode* BST::successor(TreeNode *current){
	if(current -> rightchild)
		return left_most(current -> rightchild);

	TreeNode *successor = current -> parent;
	while(successor != NULL && current == successor -> rightchild){
		current = successor;
		successor = successor -> parent;
	}

	return successor;
}

void BST::inorder_print(){
	TreeNode *current = new TreeNode;
	current = left_most(root);

	while(current != NULL){
		(*current).print();
		current = successor(current);
	}
}

void BST::inorder_print(TreeNode *current){
	char ch = 0;
	current = successor(current);
	while(current != NULL){
		(*current).print();
		current = successor(current);

		if(_kbhit()){
			ch = _getch();
			if(ch == 114) break;
		}
	}
}

void BST::levelorder_print(){
	queue<TreeNode> que;

	que.push(*root);
	while(!que.empty()){
		TreeNode node = que.front();
		que.pop();

		node.print();
		if(node.leftchild) que.push(*node.leftchild);
		if(node.rightchild) que.push(*node.rightchild);
	}
}

int main(){
	BST T;
	fstream pfile;
	string file_name;
	
	//cout << "Please input the file name." << endl;
	//cin >> file_name;
	pfile.open("product.txt", ios::in);

	if(pfile.fail()){
		cout << "The file is not exist." << endl;
		return 0;
	}
	else{
		int label, money, amount, index;
		while(pfile >> label >> money >> amount)
			T.insert(TreeNode(label, money, amount));

		pfile.close();
		cout << "File process done." << endl;
		system("pause");
		T.inorder_print();
	}

	int option;
	while(true){
		char ch = 0;
		int label, money, amount;
		TreeNode *node = new TreeNode;

		system("cls");
		cout << "Please input the option." << endl;
		cin >> option;
		switch(option){
			case 1:
				cin >> label;
				node = T.search(label);
				
				if(node){
					node->print();
					cout << endl;

					while(true){
						if(_kbhit()){
							ch = _getch();
							if(ch == 110) T.inorder_print(node);
							break;
						}
					}
				}
				else cout << "The label " << label << "does not exist." << endl;

				system("pause");
				break;
			case 2:
				cin >> label >> money >> amount;
				node = T.search(label);

				if(node != NULL){
					node -> amount += 1;
					cout << "The product has been inport." << endl;
				}
				else{
					T.insert(TreeNode(label, money, amount));
					cout << "The product has been add in the database." << endl;
				}

				system("pause");
				break;
			case 3:
				cin >> label;
				node = T.search(label);

				if(node != NULL){
					T.remove(label);
					cout << "The product has been removed." << endl;
				}
				else cout << "The product does not exist" << endl;

				system("pause");
				break;
			case 4:
				cin >> label >> amount;
				node = T.search(label);

				if(node != NULL){
					if(node -> amount > 0){
						node -> amount -= 1;
						cout << "The product has been export." << endl;
					}
					else cout << "The product's amount is not enough." << endl;
				}
				else cout << "The product does not exit." << endl;

				system("pause");
				break;
			case 5:
				T.inorder_print();
				system("pause");
				break;
			case 6:
				cin >> label >> index;
				node = T.search(label);

				if(node != NULL){
					T.insert(index, node -> money, node -> amount);
					T.remove(label);
					cout << "The product's label" << label << "has been edit as " << index << "." << endl;
				}
				else cout << "The product does not exist." << endl;

				system("pause");
				break;
			case 7:
				cout << "The most expensive product's label is " << T.price_search() << endl;
				system("pause");
				break;
			case 8:
				cin >> file_name;
				pfile.open(file_name, ios::out);

				if(pfile.fail()) cout << "The file open error." << endl;
		}
	}

	return 0;
}