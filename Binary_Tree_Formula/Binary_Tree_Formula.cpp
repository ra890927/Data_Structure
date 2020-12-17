#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

struct Node{
	char op;
	double value;
	Node *left, *right;
};

//judge whether c is operator or not
bool is_operator(char c){
	if(c == '+' || c == '-' || c == '*' || c == '/') return true;
	return false;
}

//judge whether c is number or not
bool is_number(char c){
	if(c >= '0' && c <= '9') return true;
	return false;
}

//judge +, -, *, / priority
bool oper_priority(char a, char b){
	if(!b) return true;

	//because +, - priority is lower imples +, - have higher level in binary tree
	if(a == '+' || a == '-') return true;
	else if(a == '*' || a == '/'){
		if(b == '*' || b == '/') return true;
		else return false;
	}

	return false;
}

//compute the node
double compute_node(double a, double b, char op){
	switch(op){
		case '+':
			return a + b;
		case '-':
			return a - b;
		case '*':
			return a * b;
		case '/':
			return a / b;
	}

	return 0;
}

//node initialize
Node *node_init(){
	Node *temp = new Node;
	temp -> op = 0;
	temp -> value = 0;
	temp -> left = NULL;
	temp -> right = NULL;
	return temp;
}

//biuld leaf node
Node *build_leaf(string s, bool is_signed){
	//transfer string to int
	int64_t num = 0;
	for(int64_t i = is_signed & 1; i < s.length(); i++){
		num *= 10;
		num += s[i] - '0';
	}

	Node *temp = node_init();
	if(is_signed) temp -> value = -num;
	else temp -> value = num;

	return temp;
}

//build node and link as binary tree
Node *build_node(string s){
	Node *temp = new Node;

	while(s[0] == '(' && s[s.length() - 1] == ')'){
		stack<char> sta;
		for(int64_t i = 0; i < s.length() - 1; i++){
			if(s[i] == '(') sta.push(')');
			else if(s[i] == ')'){
				if(sta.top() == '(') sta.pop();
				else sta.push(')');
			}
		}

		if(sta.empty()) s.assign(s, 1, s.length() - 2);
		else break;
	}

	bool check = true;
	for(int64_t i = 1; i < s.length(); i++)
		if(is_operator(s[i])) check = false;

	//if the string can't be separate
	if(check){
		if(s[0] == '-') return build_leaf(s, true);
		else if(is_number(s[0])) return build_leaf(s, false);
	}

	char it = 0;	//record the separate operator
	int index = 0;	//record the separate operator's index
	string sta;		//record the parentheses completeness
	for(int64_t i = 0; i < s.length(); i++){
		if(s[i] == '(') sta.push_back('(');
		else if(s[i] == ')'){
			if(!sta.empty() && sta[sta.length() - 1] == '(') sta.pop_back();
			else sta.push_back(')');
		}
		else if(sta.empty() && is_operator(s[i]) && oper_priority(s[i], it)){
			it = s[i];
			index = i;
		}
	}

	//if there are no operator can be separate ex.(1+2)
	if(!index){
		s.assign(s, 1, s.length() - 2);
		return build_node(s);
	}

	//build node
	if(is_operator(it)){
		temp->op = s[index];

		//a, b are the substring of s
		string a, b;
		a.assign(s, 0, index);
		b.assign(s, index + 1, s.length());

		temp -> left = build_node(a);
		temp -> right = build_node(b);
		temp -> value = compute_node(temp -> left -> value, temp -> right -> value, temp -> op);
	}

	return temp;
}

//delete binary tree
Node *delete_node(Node *root){
	if(root -> left) root -> left = delete_node(root -> left);
	if(root -> right) root -> right = delete_node(root -> right);
	delete root;
	return NULL;
}

void posorder_traversal(Node *root){
	if(root){
		posorder_traversal(root -> left);
		posorder_traversal(root -> right);
		if(!root -> op){
			if(root -> value < 0) printf("(%.0lf) ", root -> value);
			else printf("%.0lf ", root -> value);
		}
		else printf("%c ", root -> op);
	}
}

void preorder_traversal(Node *root){
	if(root){
		if(!root -> op){
			if(root -> value < 0) printf("(%.0lf) ", root -> value);
			else printf("%.0lf ", root -> value);
		}
		else printf("%c ", root -> op);
		preorder_traversal(root -> left);
		preorder_traversal(root -> right);
	}
}

void inorder_traversal(Node *root){
	if(root){
		preorder_traversal(root -> left);
		if(!root -> op){
			if(root -> value < 0) printf("(%.0lf) ", root -> value);
			else printf("%.0lf ", root -> value);
		}
		else printf("%c ", root -> op);
		preorder_traversal(root -> right);
	}
}

void traversal_node(Node *root, int mode){
	if(mode == 1){
		printf("The inorder traversal is : ");
		inorder_traversal(root);
	}
	if(mode == 2){
		printf("The posorder traversal is : ");
		posorder_traversal(root);
	}
	if(mode == 3){
		printf("The preorder traversal is : ");
		preorder_traversal(root);
	}

	printf("\n");
}

bool check_formula(string s){
	char pre = 0;
	string sta;
	bool is_illegal = true;

	if(is_operator(s[0])){
		printf("First character an operator\n");
		is_illegal = false;
	}
	if(is_operator(s[s.length() - 1])){
		printf("Last character an operator\n");
		is_illegal = false;
	}

	for(int64_t i = 0; i < s.length(); i++){
		if(s[i] == '(') sta.push_back('(');
		if(s[i] == ')'){
			if(sta[sta.length() - 1] == '(') sta.pop_back();
			else sta.push_back(')');
		}

		if(pre == '(' && s[i] == ')'){
			printf("Left parenthesis followed by a right parenthesis\n");
			is_illegal = false;
		}
		else if(pre == ')' && s[i] == '('){
			printf("Right parenthesis followed by a left parenthesis\n");
			is_illegal = false;
		}
		else if(!is_operator(s[i]) && !is_number(s[i]) && s[i] != '(' && s[i] != ')'){
			printf("Illegal character\n");
			is_illegal = false;
		}
		else if(pre == ')' && !is_operator(s[i]) && s[i] != ')'){
			printf("Right parenthesis followed by an identifier\n");
			is_illegal = false;
		}
		else if(pre == '(' && is_operator(s[i]) && s[i] != '-'){
			printf("Left parenthesis followed by an operator\n");
			is_illegal = false;
		}
		else if(is_operator(pre) && is_operator(s[i])){
			printf("Operator followed by an operator\n");
			is_illegal = false;
		}
		else if(is_number(pre) && s[i] == '('){
			printf("Identifier followed by a left parenthesis\n");
			is_illegal = false;
		}
		else if(is_operator(pre) && s[i] == ')'){
			printf("Operator followed by a right parenthesis\n");
			is_illegal = false;
		}

		pre = s[i];
	}

	if(!sta.empty()){
		if(sta[sta.length() - 1] == '('){
			printf("Unmatched left parenthesis\n");
			is_illegal = false;
		}
		else{
			printf("Unmatched right parenthesis\n");
			is_illegal = false;
		}
	}

	return is_illegal;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	HANDLE h;
	string formula;
	do{
		h = GetStdHandle(STD_INPUT_HANDLE);
		if(WaitForSingleObject(h, 0) == WAIT_OBJECT_0){
			system("cls");
			printf("Please input the formula.\n");
			cin >> formula;

			if(check_formula(formula)){
				Node *head = build_node(formula);
				
				printf("\n");
				traversal_node(head, 2);
				printf("\n");
				
				printf("= %.2lf\n\n", head -> value);

				delete_node(head);
			}
		}
	}while(GetAsyncKeyState(VK_ESCAPE) == 0);

	return 0;
}