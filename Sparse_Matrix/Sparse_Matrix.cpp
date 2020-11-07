#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <bits/stdc++.h>
using namespace std;

struct Matrix{
	int size, N, M;
	string name;
	vector<int> m[3];
};

map<string, bool> name_check;

Matrix matrix_init(int N, int M){
	Matrix mat;
	mat.N = N;
	mat.M = M;
	mat.size = 0;
	mat.name = "error";

	for(int i = 0; i < N; i++){
		mat.size += 1;
		mat.m[0].push_back(i);
		mat.m[1].push_back(i);
		mat.m[2].push_back(1);
	}

	return mat;
}

Matrix set_matrix(int N, int M, int option){
	int temp;
	Matrix mat;

	while(true){
		printf("Please input the name of the matrix.\n");
		cin >> mat.name;
		auto it = name_check.find(mat.name);
		if(it != name_check.end() && option == 1)
			printf("Sorry. Your input of name is used.\n");
		else{
			if(option == 1) name_check[mat.name] = true;
			break;
		}
	}

	printf("Please input the elements of matrix\n");

	mat.size = 0;
	mat.N = N, mat.M = M;

	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			cin >> temp;
			if(temp){
				mat.size += 1;
				mat.m[0].push_back(i);
				mat.m[1].push_back(j);
				mat.m[2].push_back(temp);
			}
		}
	}

	if(mat.size != mat.m[0].size())
		return matrix_init(N, M);
	return mat;
}

void print_matrix(Matrix mat){
	if(mat.size == 0){
		for(int i = 0; i < mat.N; i++){
			for(int j = 0; j < mat.M; j++)
				printf("0 ");
			printf("\n");
		}
		return;
	}

	int index = 0;
	int p = mat.m[0][0];
	int q = mat.m[1][0];
	int r = mat.m[2][0];
	for(int i = 0; i < mat.N; i++){
		for(int j = 0; j < mat.M; j++){
			if(p == i && q == j){
				printf("%d ", r);
				index++;
				p = mat.m[0][index];
				q = mat.m[1][index];
				r = mat.m[2][index];
			}
			else
				printf("0 ");
		}
		printf("\n");
	}
}

Matrix matrix_transpose(Matrix mat){
	Matrix reverse;
	reverse.N = mat.M;
	reverse.M = mat.N;
	reverse.size = mat.size;
	reverse.name = mat.name;

	int temp[reverse.N][reverse.M];
	memset(temp, 0, sizeof(temp));

	for(int i = 0; i < mat.size; i++){
		int p = mat.m[0][i];
		int q = mat.m[1][i];
		int r = mat.m[2][i];
		temp[q][p] = r;
	}

	for(int i = 0; i < reverse.N; i++){
		for(int j = 0; j < reverse.M; j++){
			if(temp[i][j]){
				reverse.m[0].push_back(i);
				reverse.m[1].push_back(j);
				reverse.m[2].push_back(temp[i][j]);
			}
		}
	}

	return reverse;
}

void matrix_addition(Matrix A, Matrix B){
	if(A.N != B.N || A.M != B.M){
		printf("Error. Two matrices have different size.\n");
		return;
	}

	Matrix add;
	add.size = 0;
	add.N = A.N;
	add.M = A.M;
	int p = 0, q = 0;
	for(int i = 0; i < add.N; i++){
		for(int j = 0; j < add.M; j++){
			if(A.m[0][p] == i && A.m[1][p] == j && B.m[0][q] == i && B.m[1][q] == j){
				int res = A.m[2][p] + B.m[2][q];
				if(res){
					add.size += 1;
					add.m[0].push_back(i);
					add.m[1].push_back(j);
					add.m[2].push_back(res);
					p++, q++;
				}
			}
			else if(A.m[0][p] == i && A.m[1][p] == j){
				add.size += 1;
				add.m[0].push_back(i);
				add.m[1].push_back(j);
				add.m[2].push_back(A.m[2][p]);
				p++;
			}
			else if(B.m[0][q] == i && B.m[1][q] == j){
				add.size += 1;
				add.m[0].push_back(i);
				add.m[1].push_back(j);
				add.m[2].push_back(B.m[2][q]);
				q++;
			}
		}
	}

	if(add.size != add.m[0].size()){
		printf("Error\n");
		return;
	}
	print_matrix(add);
}

void corret_print_submatrix(Matrix mat){
	vector<int> row, col;
	int k;
	string s;
	stringstream ss;
	printf("Please input the rols\n");
	cin >> s;
	ss << s;
	while(ss >> k) row.push_back(k);
	ss.clear();

	printf("Please input the cols\n");
	cin >> s;
	ss << s;
	while(ss >> k) col.push_back(k);
	ss.clear();

	Matrix sub;
	sub.size = 0;
	sub.N = mat.N - row.size();
	sub.M = mat.M - col.size();

	int row_index = 0;
	int col_index = 0;
	for(int i = 0; i < mat.size; i++){
		if(mat.m[0][i] != row[row_index] && mat.m[1][i] != col[col_index]){
			sub.size += 1;
			sub.m[0].push_back(mat.m[0][i]);
			sub.m[1].push_back(mat.m[1][i]);
			sub.m[2].push_back(mat.m[2][i]);
		}
		else if(mat.m[1][i] > col[col_index]) col_index += 1;
		else if(mat.m[0][i] > row[row_index]){
			row_index += 1;
			col_index = 0;
		}
	}

	if(sub.size != sub.m[0].size()){
		printf("Error\n");
		return;
	}
	
	print_matrix(sub);
}

void print_submatrix(Matrix mat, int row, int col){
	if(row < -1 || row >= mat.N || col < -1 || col >= mat.M){
		printf("Error operation.\n");
		return;
	}
	if(row == -1 && col == -1){
		print_matrix(mat);
		return;
	}

	Matrix sub;
	sub.size = 0;
	if(row > -1) sub.N = mat.N - 1;
	else sub.N = mat.N;
	if(col > -1) sub.M = mat.M - 1;
	else sub.M = mat.M;

	for(int i = 0; i < mat.size; i++){
		if(mat.m[0][i] == row || mat.m[1][i] == col) continue;

		if(mat.m[0][i] < row && mat.m[1][i] < col){
			sub.size += 1;
			sub.m[0].push_back(mat.m[0][i]);
			sub.m[1].push_back(mat.m[1][i]);
			sub.m[2].push_back(mat.m[2][i]);
		}
		else if(mat.m[0][i] < row && mat.m[1][i] > col){
			sub.size += 1;
			sub.m[0].push_back(mat.m[0][i]);
			sub.m[1].push_back(mat.m[1][i] - 1);
			sub.m[2].push_back(mat.m[2][i]);
		}
		else if(mat.m[0][i] > row && mat.m[1][i] < col){
			sub.size += 1;
			sub.m[0].push_back(mat.m[0][i] - 1);
			sub.m[1].push_back(mat.m[1][i]);
			sub.m[2].push_back(mat.m[2][i]);
		}
		else if(mat.m[0][i] > row && mat.m[1][i] > col){
			sub.size += 1;
			sub.m[0].push_back(mat.m[0][i] - 1);
			sub.m[1].push_back(mat.m[1][i] - 1);
			sub.m[2].push_back(mat.m[2][i]);
		}
	}

	if(sub.size != sub.m[0].size()){
		printf("Error\n");
		return;
	}
	
	print_matrix(sub);
}

Matrix matrix_multiple(Matrix A, Matrix B){
	Matrix ans;
	if(A.M != B.N){
		printf("The matrix A and B are not suitable the multiplication.\n");
		return matrix_init(A.N, B.M);
	}

	ans.size = 0;
	ans.N = A.N;
	ans.M = B.M;
	B = matrix_transpose(B);

	for(int i = 0; i < A.N; i++){
		for(int j = 0; j < B.N; j++){
			int p = -1, pe = A.size, q = -1, qe = B.size;
			for(int k = 0; k < A.size; k++){
				if(p == -1 && A.m[0][k] == i) p = k;
				else if(p != -1 && A.m[0][k] != i){
					pe = k;
					break;
				}
			}
			for(int k = 0; k < B.size; k++){
				if(q == -1 && B.m[0][k] == j) q = k;
				else if(q != -1 && B.m[0][k] != j){
					qe = k;
					break;
				}
			}

			int sum = 0;
			for(int k = 0; k < A.M; k++){
				if(p == -1 || q == -1 || p >= pe || q >= qe) break;

				if(A.m[1][p] == k && B.m[1][q] == k)
					sum += A.m[2][p++] * B.m[2][q++];
				else if(A.m[1][p] == k)
					p++;
				else if(B.m[1][q] == k)
					q++;
			}

			if(sum){
				ans.size += 1;
				ans.m[0].push_back(i);
				ans.m[1].push_back(j);
				ans.m[2].push_back(sum);
			}
		}
	}

	return ans;
}

void matrix_fastpower(Matrix base, int k){
	if(base.N != base.M){
		printf("The matrix is not a square matrix.\n");
		return;
	}

	Matrix ans = matrix_init(base.N, base.M);

	while(k){
		if(k & 1) ans = matrix_multiple(ans, base);
		base = matrix_multiple(base, base);
		k >>= 1;
	}

	print_matrix(ans);
}

int main(){
	vector<Matrix> arr;

	while(true){
		Matrix A, B;
		int N, M, K, option;
		string name, name1, check;
		vector<Matrix>::iterator it;

		system("cls");
		printf(" ________________________________________________\n\n");
		printf("| (1): Set up the matrix and record it.          |\n");
		printf("| (2): Print the matrix which is recorded.       |\n");
		printf("| (3): Print the submatrix.                      |\n");
		printf("| (4): Transpose the matrix.                     |\n");
		printf("| (5): Add two matrices.                         |\n");
		printf("| (6): Computing the power k of matrix.          |\n");
		printf("| (7): Remove the set matrix                     |\n");
		printf("| (8): End up the program.                       |\n");
		printf(" ________________________________________________\n");
		printf("\n");

		if(arr.size()){
			printf("Now you have the matrices.\n");
			for(int i = 0; i < arr.size(); i++)
				cout << arr[i].name << endl;
		}

		printf("\nPlease input the option(1 - 8).\n");
		cin >> option;
		switch(option){
			case 1:
				//set up matrix
				printf("Please input the size of matrix. (1 - 1000)\n");
				cin >> N >> M;
				A = set_matrix(N, M, 1);
				if(A.name == "error"){
					printf("Error set matrix.\n");
					return 0;
				}
				else arr.push_back(A);
				break;
			case 2:
				//print matrix
				printf("Please input the name of matrix.\n");
				cin >> name;
				for(Matrix &temp : arr){
					if(name == temp.name){
						print_matrix(temp);
						system("pause");
						break;
					}
				}
				break;
			case 3:
				//print submatrix
				printf("Have you set up the matrix before operating? (yes or no)\n");
				cin >> check;
				if(check == "yes"){
					printf("Please input the name of matrix.\n");
					cin >> name;
					for(Matrix &temp : arr)
						if(name == temp.name) A = temp;
					printf("Your choose matrix.\n");
					print_matrix(A);
					printf("\n");
					/*printf("Please input the row number ans col number.\n");
					cin >> row >> col;
					print_submatrix(arr[u], row, col);*/
					corret_print_submatrix(A);
					system("pause");
				}
				else if(check == "no"){
					printf("Please input the size of matrix. (1 - 1000)\n");
					cin >> N >> M;
					A = set_matrix(N, M, 3);

					/*int row, col;
					printf("Please input the row number ans col number.\n");
					cin >> row >> col;
					print_submatrix(A, row, col);*/
					corret_print_submatrix(A);
					system("pause");
				}
				break;
			case 4:
				//matrix reverse
				printf("Have you set up the matrix before operating? (yes or no)\n");
				cin >> check;
				if(check == "yes"){
					printf("Please input the name of matrix.\n");
					cin >> name;
					for(Matrix &temp : arr)
						if(name == temp.name) A = temp;
					printf("Your choose matrix.\n");
					print_matrix(A);
					printf("\n");
					Matrix reverse = matrix_transpose(A);
					print_matrix(reverse);
					system("pause");
				}
				else if(check == "no"){
					printf("Please input the size of matrix. (1 - 1000)\n");
					cin >> N >> M;
					A = set_matrix(N, M, 4);

					A = matrix_transpose(A);
					print_matrix(A);
					system("pause");
				}
				break;
			case 5:
				//matrix addition
				printf("Have you set up the matrix before operating? (yes or no)\n");
				cin >> check;
				if(check == "yes"){
					int u, v;
					printf("Please input the name of matrix 1.\n");
					cin >> name;
					for(int i = 0; i < arr.size(); i++)
						if(name == arr[i].name) u = i;
					printf("Please input the name of matrix 2.\n");
					cin >> name;
					for(int i = 0; i < arr.size(); i++)
						if(name == arr[i].name) v = i;

					printf("Your choose matrices.\n");
					print_matrix(arr[u]);
					printf("\n");
					print_matrix(arr[v]);
					printf("\n");
					matrix_addition(arr[u], arr[v]);
					system("pause");
				}
				else if(check == "no"){
					printf("Please input the size of matrix 1. (1 - 1000)\n");
					cin >> N >> M;
					A = set_matrix(N, M, 5);
					printf("Please input the size of matrix 2. (1 - 1000)\n");
					cin >> N >> M;
					B = set_matrix(N, M, 5);
					matrix_addition(A, B);
					system("pause");
				}
				break;
			case 6:
				//matrix fastpower
				printf("Have you set up the matrix before operating? (yes or no)\n");
				cin >> check;
				if(check == "yes"){
					printf("Please input the name of matrix.\n");
					cin >> name;
					printf("Please input the power number of matrix(1 - 100).\n");
					cin >> K;

					for(Matrix &temp : arr)
						if(name == temp.name) A = temp;
					printf("Your choose matrix.\n");
					print_matrix(A);
					printf("\n");
					matrix_fastpower(A, K);
					system("pause");
				}
				else if(check == "no"){
					printf("Please input the size of matrix(1 - 1000) and the power number of matrix(1 - 100).\n");
					cin >> N >> M >> K;
					A = set_matrix(N, M, 6);
					matrix_fastpower(A, K);
					system("pause");
				}
				break;
			case 7:
				//remove matrix
				if(!arr.size()){
					printf("The array is empty\n");
					system("pause");
					break;
				}

				printf("Please input the name of matrix that you want to remove.\n");
				cin >> name;

				K = 0;
				it = arr.begin();
				while(it != arr.end()){
					if(name == it -> name){
						K = 1;
						it = arr.erase(it);
						break;
					}
					else it++;
				}

				if(!K) printf("Your input matrix does not exist.\n");
				else printf("Done\n");
				system("pause");
				break;
			case 8:
				return 0;
			default:
				printf("Wrong input.\n");
		}
	}

	return 0;
}