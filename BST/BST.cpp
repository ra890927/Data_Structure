#include <bits/stdc++.h>
#include <fstream>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
using namespace std;

#include "BST.h"

void menu(){
	system("cls");
	cout << "=========================================================" << endl;
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
	cout << "| (8): Save information in another file and exit.       |" << endl;
	cout << "| (9): Exit and Save.                                   |" << endl;
	cout << "=========================================================" << endl;
	cout << endl << "Please input the option." << endl;
}

int main(){
	BST T;
	string file_name, name;

	while(true){
		system("cls");
		cout << "Please input the file name." << endl;
		cin >> file_name;
		ifstream pfile(file_name);

		if(pfile.fail()){
			system("cls");
			cout << "====== The file open error. ======" << endl;
			sleep(1.5);
			continue;
		}
		else{
			system("cls");
			cout << "The file open success." << endl;
			int label, money, amount;
			while(pfile >> label >> money >> amount)
				T.insert(TreeNode(label, money, amount));

			pfile.close();
			cout << endl << "====== File process done. ======" << endl;
			sleep(1.5);
			break;
		}
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
				system("cls");
				cout << "====== Option 1: search product ======" << endl << endl;
				cout << "Please input the product number." << endl;
				cin >> label;
				node = T.search(label);
				
				if(node){
					//cout << "The number " << label << " product information: ";
					node->print();

					while(T.successor(node)){
						if(_kbhit()){
							ch = _getch();
							if(ch == 110){
								cout << "Next product:" << endl;
								node = T.successor(node);
								node -> print();

								if(T.successor(node) == NULL){
									cout << "This is the last product." << endl;
									break;
								}
							}
							else if(ch == 114) break;
						}
					}
				}
				else cout << "The number " << label << " product does not exist." << endl;

				cout << endl << "============ Option 1 end ============" << endl;
				system("pause");
				break;
			case 2:
				system("cls");
				cout << "====== Option 2: inport product ======" << endl << endl;
				cout << "Please input the product number and amount." << endl;
				cin >> label >> amount;
				T.inport(label, amount);
				cout << endl << "============ Option 2 end ============" << endl;
				system("pause");
				break;
			case 3:
				system("cls");
				cout << "====== Option 3: delete product ======" << endl << endl;
				cout << "Please input the product number." << endl;
				cin >> label;
				
				node = T.search(label);
				if(node != NULL){
					T.remove(label);
					cout << "The product has been removed." << endl;
				}
				else cout << "The product does not exist" << endl;

				cout << endl << "============ Option 3 end ============" << endl;
				system("pause");
				break;
			case 4:
				system("cls");
				cout << "====== Option 4: export product ======" << endl << endl;
				cout << "Please input the product number and amount." << endl;
				cin >> label >> amount;
				T.outport(label, amount);
				cout << endl << "============ Option 4 end ============" << endl;
				system("pause");
				break;
			case 5:
				system("cls");
				cout << "====== Option 5: print product  ======" << endl << endl;
				cout << endl << "All product information:" << endl;
				T.inorder_print();
				cout << endl << "============ Option 5 end ============" << endl;
				system("pause");
				break;
			case 6:
				system("cls");
				cout << "====== Option 6: modify product ======" << endl << endl;
				cout << "Please input the product original number and modified number." << endl;
				cin >> label >> index;
				T.modify(label, index);
				cout << endl << "============ Option 6 end ============" << endl;
				system("pause");
				break;
			case 7:
				system("cls");
				cout << "====== Option 7: search expensive product ======" << endl << endl;
				if(T.empty()) cout << "The database is empty." << endl;
				else T.price_search();
				cout << endl << "================= Option 7 end =================" << endl;
				system("pause");
				break;
			case 8:
				system("cls");
				cout << "====== Option 8: save in file ======" << endl << endl;
				cout << "Please input the file name." << endl;
				cin >> name;
				T.data_export(name);
				cout << endl << "=========== Program end  ===========" << endl;
				return 0;
			case 9:
				system("cls");
				T.data_export(file_name);
				cout << endl << "====== Program end ====== " << endl;
				return 0;
			default:
				cout << "Error option. Please input option again." << endl;
				system("pause");
				break;
		}
	}

	return 0;
}