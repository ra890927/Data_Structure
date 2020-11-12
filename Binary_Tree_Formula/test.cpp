#include <bits/stdc++.h>
using namespace std;

int main(){
	string f;
	vector<int> cor;
	cin >> f;

	int i = 0;
	int len = f.length();
	string cor_fla;
	stack<char> option;

	while(i < len){
		if(f[i] >= '0' && f[i] <= '9'){
			int num = 0;
			while(f[i] >= '0' && f[i] <= '9'){
				num *= 10;
				num += f[i] - '0';
				i += 1;
			}

			cor_fla += 'A' + cor.size();
			cor.push_back(num);
			i -= 1;
			cout << num << endl;
		}
		else if(f[i] == '('){
			if(f[i + 1] == '-' && f[i + 2] >= '0' && f[i + 2] <= '9'){
				int num = 0;
				while(f[i] < '0' || f[i] > '9'){
					num *= 10;
					num += f[i] - '0';
					i += 1;
				}

				if(f[i] != ')') continue;
				num *= -1;
				cor_fla += 'A' + cor.size();
				cor.push_back(num);
				i -= 1;
			}
			else option.push('(');
		}
		else if(f[i] == ')'){
			if(!option.empty()){
				while(true){
					char c = option.top();
					option.pop();
					if(c == '(') break;
					cor_fla += c;
				}
			}
		}
		else if(f[i] == '*' || f[i] == '/'){
			if(!option.empty()){
				while(!option.empty() && (option.top() == '*' || option.top() == '/')){
					char c = option.top();
					option.pop();
					cor_fla += c;
				}
			}

			if(f[i] == '*') option.push('*');
			else option.push('/');
		}
		else if(f[i] == '+' || f[i] == '-'){
			if(!option.empty()){
				while(!option.empty() && (option.top() == '+' || option.top() == '-')){
					char c = option.top();
					option.pop();
					cor_fla += c;
				}
			}

			if(f[i] == '+') option.push('+');
			else option.push('-');
		}

		i += 1;
	}

	while(!option.empty()){
		char c = option.top();
		option.pop();
		cor_fla += c;
	}

	cout << cor_fla << endl;
	return 0;
}