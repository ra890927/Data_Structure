# Data_Structure Hw08 Readme

# 作業程式碼
- [**BST.cpp**](https://github.com/ra890927/Data_Structure/blob/master/BST/BST.cpp)
- [**BST.h**](https://github.com/ra890927/Data_Structure/blob/master/BST/BST.h)

## class TreeNode
```cpp
class TreeNode{
private:
    int label;
    int money;
    int amount;
    
    TreeNode *leftchild;
    TreeNode *rightchild;
    TreeNode *parent;
public:
    TreeNode(): label(0), money(0), amount(0),
                leftchild(NULL), rightchild(NULL), parent(NULL){};
    TreeNode(int label, int money, int amount):
                label(label), money(money), amount(amount),
                leftchild(NULL), rightchild(NULL), parent(NULL){};

    friend class BST;
}
```

```cpp
class BST{
private:
    root;
    TreeNode* left_most(TreeNode *node);
public:
    BST(): root(NULL){};
    
    TreeNode* successor(TreeNode *node);
	TreeNode* search(int label);
	void price_search();
	void insert(TreeNode node);
	void remove(int label);
	void inport(int label, int amount);
	void outport(int label, int amount);
	void modify(int original, int modified);
	void inorder_print();
	void data_export(string file_name);
	bool empty();
}
```

## 介面設計

![](https://i.imgur.com/PgOO9XV.png)

- 一開始先輸入檔案名稱
- 會進入上面那個頁面
- 輸入選項

## Function

### empty()
```cpp
bool BST::empty(){
    if(root == NULL) return true;
    return false;
}
```

### insert(TreeNode node)
```cpp
void BST::insert(TreeNode node){
    TreeNode *cur = NULL;    //紀錄當前的節點
    TreeNode *pre = NULL;    //紀錄當前節點的父節點
    TreeNode *insert_node = new TreeNode(node.label, node.money, node.amount);
    
    cur = root;
    while(cur != NULL){
        pre = cur;
        if(insert_node -> label < cur -> label)
            cur = cur -> leftchild;
        else
            cur = cur -> rightchild;
    }

    //如果要插入的節點已經存在，增加這個節點數量
    if(cur != NULL){
        cur -> amount += insert_node -> amount;
        return;
    }

    insert_node -> parent = pre;

    if(pre == NULL)
        this -> root = insert_node;    //如果沒有父節點，更新樹根
    else if(insert_node -> label < pre -> label)
        pre -> leftchild = insert_node;    //更新父節點的左右節點
    else
        pre -> rightchild = insert_node;
}
```

### left_most(TreeNode *current)
```cpp
TreeNode* BST::left_most(TreeNode *current){
    while(current -> leftchild != NULL)
        current = current -> leftchild;

    return current;
}
```

### successor(TreeNode *current)
```cpp
TreeNode* BST::successor(TreeNode *current){
    if(current == NULL) return NULL;

    if(current -> rightchild)    //如果有右節點，回傳右節點的最左節點
        return left_most(current -> rightchild);

    TreeNode *successor = current -> parent;    //如果沒有的話往父節點去找
    while(successor != NULL && current == successor -> rightchild){    //尋找還沒走過的父節點
        current = successor;
        successor = successor -> parent;
    }

    return successor;
}
```

### remove(int label)
```cpp
void BST::remove(int label){
    TreeNode *del = search(label);    //要修改的點
    TreeNode *parent = new TreeNode;  //要刪除的點
    TreeNode *child = new TreeNode;   //移動的點的子節點

    if(del == NULL) return;
    //如果只有一個子節點的話，紀錄要刪除的點
    if(del -> leftchild == NULL || del -> rightchild == NULL)
        parent = del;
    else
        parent = successor(del);    //兩個子節點的話去找右邊最小的節點
    //紀錄子節點
    if(parent -> leftchild != NULL)
        child = parent -> leftchild;
    else
        child = parent -> rightchild;
    //更新子節點的parent指標
    if(child != NULL) child -> parent = parent -> parent;
    //如果刪除的點是根節點，更新根結點為child
    if(parent -> parent == NULL)
        this -> root = child;
    else if(parent == parent -> parent -> leftchild)
        parent -> parent -> leftchild = child;    //要刪除的點是左節點的話，更新父節點的左節點
    else
        parent -> parent -> rightchild = child;   //要刪除的點是右節點的話，更新父節點的右節點

    if(parent != del) del -> copy(*parent);    //更新要修改的節點

    delete parent;    //刪除節點
}
```

### data_export(string file_name)
```cpp
void BST::data_export(string file_name){
    if(empty()){
        cout << "The database is empty." << endl;
        return;
    }

    ofstream pfile(file_name, ios::trunc);    //開寫檔

    if(pfile.fail()){
        cout << "The file open error." << endl;
        return;
    }

    queue<TreeNode> que;    //宣告一個佇列

    que.push(*root);
    while(!que.empty()){
        TreeNode current = que.front();
        que.pop();

        pfile << current.label << " " << current.money << " " << current.amount << endl;

        if(current.leftchild) que.push(*current.leftchild);    //按照preorder順序丟進queue裡面
        if(current.rightchild) que.push(*current.rightchild);
    }

    pfile.close();
    cout << "The product data has been export to " << file_name << "." << endl;
    return;
}
```