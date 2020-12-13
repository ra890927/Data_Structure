#include <bits/stdc++.h>
#include <fstream>
#include <stdlib.h>
#include <conio.h>
using namespace std;

#include "BST.h"

void menu(){
	system("cls");
	cout << "_________________________________________________________" << endl;
	cout << "| (1): Search the product and show it's information.    |" << endl;
	cout << "|      Press 'N' can show other products' information.  |" << endl;
	cout << "|      Press 'R' can stop showing products' information.|" << endl;
	cout << "| (2): Import products.                                 |" << endl;
	cout << "|      If the product does not exist, add in the data.  |" << endl;
	cout << "| (3): Delete a product.                                |" << endl;
	cout << "| (4): Export products.                                 |" << endl;
	cout << "| (5): List all product information.                    |" << endl;
	cout << "| (6): Modify the product number.                       |" << endl;
	cout << "| (7): Search for a product with highest price.         |" << endl;
	cout << "| (8): Store product information in file.               |" << endl;
	cout << "| (9): Exit.                                            |" << endl;
	cout << "_________________________________________________________" << endl;
	cout << endl << "Please input the option." << endl;
}

int main(){
	BST T;
	string file_name;

	cout << "Please input the file name." << endl;
	cin >> file_name;
	ifstream pfile(file_name);

	if(pfile.fail()){
		cout << "The file is not exist." << endl;
		return 0;
	}
	else{
		int label, money, amount;
		while(pfile >> label >> money >> amount)
			T.insert(TreeNode(label, money, amount));

		pfile.close();
		cout << "File process done." << endl;
		system("pause");
	}

	int option;
	while(true){
		char ch = 0;
		int label, amount, index;
		TreeNode *node = new TreeNode;

		menu();
		cin >> option;
		switch(option){
			case 1:
				cout << "Please input the product number." << endl;
				cin >> label;
				node = T.search(label);
				
				if(node){
					cout << "The number " << label << " product information: ";
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
				else cout << "The number " << label << " product does not exist." << endl;

				system("pause");
				break;
			case 2:
				cout << "Please input the product number and amount." << endl;
				cin >> label >> amount;

				T.inport(label, amount);
				system("pause");
				break;
			case 3:
				cout << "Please input the product number." << endl;
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
				cout << "Please input the product number and amount." << endl;
				cin >> label >> amount;
				
				T.outport(label, amount);
				system("pause");
				break;
			case 5:
				cout << endl << "All product information:" << endl;
				T.inorder_print();
				system("pause");
				break;
			case 6:
				cout << "Please input the product original number and modified number." << endl;
				cin >> label >> index;
				
				T.modify(label, index);
				system("pause");
				break;
			case 7:
				cout << "The most expensive product's number is " << T.price_search() << "." << endl;
				system("pause");
				break;
			case 8:
				cout << "Please input the file name." << endl;
				cin >> file_name;

				T.data_export(file_name);
				system("pause");
				break;
			case 9:
				T.clear();
				return 0;
			case 10:
				T.levelorder_print();
				system("pause");
				break;
			default:
				cout << "Error option. Please input option again." << endl;
				system("pause");
				break;
		}
	}

	return 0;
}