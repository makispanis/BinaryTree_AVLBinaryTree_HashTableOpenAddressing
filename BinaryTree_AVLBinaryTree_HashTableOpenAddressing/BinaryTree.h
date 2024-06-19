#include <iostream>

using namespace std;

//κομβος του δεντρου
struct node {
	string data;
	node* left;
	node* right;
	int amount;
};
class BinaryTree {
public:
	BinaryTree();
	~BinaryTree();

	void insert(string key);
	void remove(string key);
	node* search(string key);
	void destroy_tree();
	void inorder_print();
	void postorder_print();
	void preorder_print();

private:
	void destroy_tree(node* leaf);
	node* minValueNode(node* node);
	node* remove(node* root, string key);
	void insert(string key, node* leaf);
	node* search(string key, node* leaf);
	void inorder_print(node* leaf);
	void postorder_print(node* leaf);
	void preorder_print(node* leaf);

	node* root;
};
