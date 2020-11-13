#include <bits/stdc++.h>
using namespace std;

struct Node{
	char op;
	int value;
	Node *left, *right;
};

bool is_error = false;

bool is_operator(char c){
	if(c == '+' || c == '-' || c == '*' || c == '/') return true;
	return false;
}

bool is_number(char c){
	if(c >= '0' && c <= '9') return true;
	return false;
}

bool oper_priority(char a, char b){
	if(!b) return true;

	if(a == '+' || a == '-') return true;
	else if(a == '*' || a == '/'){
		if(b == '*' || b == '/') return true;
		else return false;
	}

	return false;
}

Node *node_init(){
	Node *temp = new Node;
	temp -> op = 0;
	temp -> value = 0;
	temp -> left = NULL;
	temp -> right = NULL;
	return temp;
}

Node *build_leaf(string s, bool is_signed){
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

Node *build_node(string s){
	Node *temp = new Node;

	int sub_i = -1;
	int sub_cnt = 0;
	bool check = true;
	for(int64_t i = 1; i < s.length(); i++){
		if(is_operator(s[i])){
			check = false;
			if(s[i] == '-'){
				sub_cnt += 1;
				sub_i = i;
			}
		}
	}

	if(sub_cnt == 1 && sub_i == 1) check = true;

	cout << s << endl;

	if(check){
		if(s[0] == '-') return build_leaf(s, true);
		else if(is_number(s[0])) return build_leaf(s, false);
		else if(s[0] == '(' && s[s.length() - 1] == ')'){
			s.assign(s, 1, s.length() - 2);

			if(s[0] == '-') temp = build_leaf(s, true);
			else if(is_number(s[1])) temp = build_leaf(s, false);

			return temp;
		}
		else{
			is_error = true;
			printf("Illegal input.\n");
			return node_init();
		}
	}

	char it = 0;
	int index = 0;
	stack<char> sta;
	for(int64_t i = 0; i < s.length(); i++){
		if(s[i] == '(') sta.push('(');
		else if(s[i] == ')'){
			if(sta.top() == '(') sta.pop();
			else sta.push(')');
		}
		else if(sta.empty() && is_operator(s[i]) && oper_priority(s[i], it)){
			it = s[i];
			index = i;
		}
	}

	if(is_operator(it)){
		temp->op = s[index];

		string a, b;
		a.assign(s, 0, index);
		b.assign(s, index + 1, s.length());

		if(a[0] == '(' && a[a.length() - 1] == ')')
			a.assign(a, 1, a.length() - 2);
		if(b[0] == '(' && b[b.length() - 1] == ')')
			b.assign(b, 1, b.length() - 2);

		cout << a << " " << b << endl;

		temp -> left = build_node(a);
		temp -> right = build_node(b);
	}

	cout << "\n\n";

	return temp;
}

void posorder_traversal(Node *root){
	if(root){
		posorder_traversal(root -> left);
		posorder_traversal(root -> right);
		if(!root -> op) printf("%d ", root -> value);
		else printf("%c ", root -> op);
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	string formula;
	while(cin >> formula){
		Node *head = build_node(formula);
		posorder_traversal(head);
		printf("\n");
	}
}