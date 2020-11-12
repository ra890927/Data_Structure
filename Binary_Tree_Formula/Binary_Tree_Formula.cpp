#include <bits/stdc++.h>
using namespace std;

struct Node{
	char op = 0;
	int value;
	Node *left, *right;
};

vector<int> cor;

bool is_operator(char c){
	if(c == '+' || c == '-' || c == '*' || c == '/') return true;
	return false;
}

Node *build_leaf(string s){
	int64_t num = 0;
	for(int64_t i = 0; i < s.length(); i++){
		num *= 10;
		num += s[i] - '0';
	}

	Node *temp = new Node;
	temp -> value = num;
	temp -> left = NULL;
	temp -> right = NULL;
	return temp;
}

Node *build_node(string s){
	Node *temp = new Node;

	bool check = true;
	for(int64_t i = 0; i < s.length(); i++)
		if(is_operator(s[i])) check = false;
	if(check) return build_leaf(s);

	stack<char> sta;
	for(int64_t i = 0; i < s.length(); i++){
		if(s[i] == '(') sta.push('(');
		else if(s[i] == ')'){
			if(sta.top() == '(') sta.pop();
			else sta.push(')');
		}
		else if(sta.empty() && is_operator(s[i])){
			temp->op = s[i];
			string a, b;
			a.assign(s, 0, i);
			b.assign(s, i + 1, s.length());
			if(a[0] == '(' && a[a.length() - 1] == ')')
				a.assign(a, 1, a.length() - 2);
			if(b[0] == '(' && b[b.length() - 1] == ')')
				b.assign(b, 1, b.length() - 2);
			cout << a << " " << b << endl;
			temp -> left = build_node(a);
			temp -> right = build_node(b);
		}
	}

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
		Node *head =  build_node(formula);
		posorder_traversal(head);
	}
}