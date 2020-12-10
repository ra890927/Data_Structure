#include <bits/stdc++.h>
#include <fstream>
#include <stdlib.h>
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
	void insert(int label, int money, int amount);
	void remove(int label);
	void inorder_print();
	void _inorder_print(TreeNode *current);
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

void BST::insert(int label, int money, int amount){
	TreeNode *cur = NULL;
	TreeNode *pre = NULL;
	TreeNode *insert_node = new TreeNode(label, money, amount);

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

TreeNode* BST::left_most(TreeNode *node){
	TreeNode *cur = root;

	while(cur -> leftchild != NULL)
		cur = cur -> leftchild;

	return cur;
}

TreeNode* BST::right_most(TreeNode *node){
	TreeNode *cur = root;

	while(cur -> rightchild != NULL)
		cur = cur -> rightchild;

	return cur;
}

void BST::remove(int label){
	TreeNode *del = search(label);
	TreeNode *child = new TreeNode;

	if(del -> leftchild)
		child = right_most(del -> leftchild);
	else
		child = left_most(del -> rightchild);

	child -> parent = del -> parent;
	child -> leftchild = del -> leftchild;
	child -> rightchild = del -> rightchild;

	delete del;
}

TreeNode* BST::successor(TreeNode *node){
	if(node -> rightchild != NULL)
		return left_most(node -> rightchild);

	TreeNode *new_node = node -> parent;
	//cout << "test" << new_node -> label << " " << new_node -> money << " " << new_node -> amount << endl;
	while(new_node != NULL && node == new_node -> rightchild){
		node = new_node;
		new_node = new_node -> parent;
	}

	return new_node;
}

void BST::inorder_print(){
	//_inorder_print(root);
	TreeNode *cur = new TreeNode;
	cur = left_most(root);
	while(cur){
		cout << cur -> label << " " << cur -> money << " " << cur -> amount << endl;
		cur = successor(cur);
	}
}

void BST::_inorder_print(TreeNode *current){
	if(current){
		_inorder_print(current -> leftchild);
		cout << current -> label << " " << current -> money << " " << current -> amount << endl;
		_inorder_print(current -> rightchild);
	}
}

int main(){
	BST T;
	fstream pfile;
	string file_name;
	
	cout << "Please input the file name." << endl;
	cin >> file_name;
	pfile.open(file_name, ios::in);

	if(pfile.fail()){
		cout << "The file is not exist." << endl;
		return 0;
	}
	else{
		int label, money, amount;
		while(pfile >> label >> money >> amount)
			T.insert(label, money, amount);

		T.inorder_print();
	}

	pfile.close();

	return 0;
}