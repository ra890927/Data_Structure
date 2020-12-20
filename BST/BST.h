#include <bits/stdc++.h>
#include <conio.h>
#include <fstream>

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

	void print(){
		cout << "number is " << label << endl;
		cout << "price is " << money << endl;
		cout << "amount is " << amount << endl << endl;
	}
	void copy(TreeNode &other){
		label = other.label;
		money = other.money;
		amount = other.amount;
	}

	friend class BST;
};

class BST{
private:
	TreeNode *root;
	TreeNode* left_most(TreeNode *node);
	TreeNode* right_most(TreeNode *node);
	void _clear(TreeNode *node);

public:
	BST(): root(NULL){};

	TreeNode* successor(TreeNode *node);
	TreeNode* search(int label);
	int price_search();
	void insert(TreeNode node);
	void remove(int label);
	void inport(int label, int amount);
	void outport(int label, int amount);
	void modify(int original, int modified);
	void inorder_print();
	void inorder_print(TreeNode *current);
	void levelorder_print();
	void data_export(string file_name);
	void clear();
	bool empty();
};

bool BST::empty(){
	if(root == NULL) return true;
	return false;
}

void BST::clear(){
	if(!empty()) _clear(root);
	root = NULL;
}

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

		if(current.money > price){
			label = current.label;
			price = current.money;
		}

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

	if(cur != NULL){
		cur -> amount += insert_node -> amount;
		return;
	}

	insert_node -> parent = pre;

	if(pre == NULL)
		this -> root = insert_node;
	else if(insert_node -> label < pre -> label)
		pre -> leftchild = insert_node;
	else
		pre -> rightchild = insert_node;
}

void BST::inport(int label, int amount){
	TreeNode *node = search(label);

	cout << endl;
	if(node != NULL){
		node -> amount += amount;
		cout << "The product has been inported." << endl;
		cout << "The number " << label << " product amount: " << node -> amount - amount << " -> " << node -> amount << endl;
	}
	else{
		int money;
		cout << "The product does not exist." << endl;
		cout << "Please input the product's price." << endl;
		cin >> money;
		insert(TreeNode(label, money, amount));
		cout << "The product has been add in the database." << endl;
	}
}

void BST::outport(int label, int amount){
	TreeNode *node = search(label);

	cout << endl;
	if(node != NULL){
		if(node -> amount >= amount){
			node -> amount -= amount;
			cout << "The product has been export." << endl;
			cout << "The number " << label << " product amount: " << node -> amount + amount << " -> " << node -> amount << endl;
		}
		else cout << "The product's amount is not enough." << endl;
	}
	else cout << "The product does not exit." << endl;
}

void BST::modify(int original, int modified){
	TreeNode *node = search(modified);

	cout << endl;
	if(node != NULL){
		cout << "The product " << modified << " has existed." << endl;
		return;
	}

	node = search(original);
	if(node != NULL){
		insert(TreeNode(modified, node -> money, node -> amount));
		remove(original);
		cout << "The product's number " << original << " has been edit as " << modified << "." << endl;
	}
	else cout << "The product does not exist." << endl;
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
	TreeNode *parent = new TreeNode;
	TreeNode *child = new TreeNode;

	if(del == NULL) return;

	if(del -> leftchild == NULL || del -> rightchild == NULL)
		parent = del;
	else
		parent = successor(del);

	if(parent -> leftchild != NULL)
		child = parent -> leftchild;
	else
		child = parent -> rightchild;

	if(child != NULL) child -> parent = parent -> parent;

	if(parent -> parent == NULL)
		this -> root = parent;
	else if(parent == parent -> parent -> leftchild)
		parent -> parent -> leftchild = child;
	else
		parent -> parent -> rightchild = child;

	if(parent != del) del -> copy(*parent);
	if(parent == root) root = NULL;

	delete parent;
}

TreeNode* BST::successor(TreeNode *current){
	if(current == NULL) return NULL;

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
	if(root == NULL){
		cout << "BST is empty." << endl;
		return;
	}

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

void BST::data_export(string file_name){
	ofstream pfile(file_name, ios::trunc);

	if(pfile.fail()){
		cout << "The file open error." << endl;
		return;
	}

	queue<TreeNode> que;

	que.push(*root);
	while(!que.empty()){
		TreeNode current = que.front();
		que.pop();

		pfile << current.label << " " << current.money << " " << current.amount << endl;

		if(current.leftchild) que.push(*current.leftchild);
		if(current.rightchild) que.push(*current.rightchild);
	}

	pfile.close();
	cout << "The product data has been export to " << file_name << "." << endl;
	return;
}

void BST::_clear(TreeNode *node){
	if(node -> leftchild) _clear(node -> leftchild);
	if(node -> rightchild) _clear(node -> rightchild);

	delete node;
	return;
}