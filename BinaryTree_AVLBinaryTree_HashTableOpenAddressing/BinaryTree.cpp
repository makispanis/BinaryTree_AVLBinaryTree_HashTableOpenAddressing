#include "BinaryTree.h"

//����������� ��� ����� �� NULL
BinaryTree::BinaryTree() {
	root = NULL;
}

//destructor ��� �������
BinaryTree::~BinaryTree() {
	destroy_tree();
}
//public remove �������
void BinaryTree::remove(string key)
{
	root = remove(root, key);
}

//��������� ��� ������������� ������
node* BinaryTree::minValueNode(node* node)
{
	struct node* current = node;


	while (current && current->left != NULL)
		current = current->left;

	return current;
}

//�������� �����
node* BinaryTree::remove(node* root, string key)
{
	if (root == NULL)
		return root;

	// �� � ���� ��� ����� �� ��������� ����� ������������� ��������� ��� ���� ��� �����,
	// ���� ��������� ��� �������� ���������
	if (key.compare(root->data) < 0)
		root->left = remove(root->left, key);

	// �� � ���� ��� ����� �� ��������� ����� ������������� ���������� ��� ���� ��� �����,
	// ���� ��������� ��� ���� ���������
	else if (key.compare(root->data) > 0)
		root->right = remove(root->right, key);

	//� ���� ������� ������������ ��� ��� ����� ��������� �� amount ���
	else if (key.compare(root->data) == 0 && root->amount > 1)
		root->amount = root->amount - 1;
	// �� � ���� ����� ���� �� �� ���� ���� ���� �����
	//��� ������ �� ���������
	else
	{
		// ������ �� ��� � ������ �����
		if (root->left == NULL)
		{
			node* temp = root->right;
			delete(root);
			return temp;
		}
		else if (root->right == NULL)
		{
			node* temp = root->left;
			delete(root);
			return temp;
		}


		//������ �� ��� ������: ��������� ��� inorder �������(� ����������
		//��� ���� ���������)
		node* temp = minValueNode(root->right);

		//��������� ������������ ��� inorder �������� �� ���� �� �����
		root->data = temp->data;

		// ��������� inorder ��������
		root->right = remove(root->right, temp->data);
	}
	return root;
}

//���������� �������� ���� ������
void BinaryTree::destroy_tree(node* leaf) {
	if (leaf != NULL) {
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		delete leaf;
	}
}

//�������� �����
void BinaryTree::insert(string key, node* leaf) {
	//�� � ���� ������� ��� ��������� �� amount ���
	if (key.compare(leaf->data) == 0) {
		leaf->amount = leaf->amount + 1;
		// �� � ���� ��� ����� ��������� ����� ������������� ��������� ��� ���� ��� ������,
		// ���� �� �������� ��� �������� ��� ���������
	}
	else if (key.compare(leaf->data) < 0) {
		if (leaf->left != NULL) {
			insert(key, leaf->left);
		}
		else {
			leaf->left = new node;
			leaf->left->data = key;
			leaf->left->amount = 1;
			leaf->left->left = NULL;
			leaf->left->right = NULL;
		}
		// �� � ���� ��� ����� ��������� ����� ������������� ���������� ��� ���� ��� ������,
	// ���� �� �������� ��� ���� ��� ���������
	}
	else if (key.compare(leaf->data) > 0) {
		if (leaf->right != NULL) {
			insert(key, leaf->right);
		}
		else {
			leaf->right = new node;
			leaf->right->data = key;
			leaf->right->amount = 1;
			leaf->right->right = NULL;
			leaf->right->left = NULL;
		}
	}

}

//public insert �������
void BinaryTree::insert(string key) {
	if (root != NULL) {
		insert(key, root);
	}
	else {
		root = new node;
		root->data = key;
		root->amount = 1;
		root->left = NULL;
		root->right = NULL;
	}
}

//��������� �����
node* BinaryTree::search(string key, node* leaf) {
	if (leaf != NULL) {
		// �� � ���� ��� ����������� ����� ������������� ���� �� ���� ��� ������,
		// ���� ������������ � ������� ��� ������
		if (key.compare(leaf->data) == 0) {
			return leaf;
		}
		// �� � ���� ��� ����������� ����� ������������� ��������� ��� ���� ��� ������,
		// ���� ��������� ��� �������� ���������
		if (key.compare(leaf->data) < 0) {
			return search(key, leaf->left);
			// �� � ���� ��� ����������� ����� ������������� ���������� ��� ���� ��� �����,
			// ���� ��������� ��� ���� ���������
		}
		else {
			return search(key, leaf->right);
		}
	}
	else {
		//�� ��� ������ ���������� NULL
		return NULL;
	}
}

//public search �������
node* BinaryTree::search(string key) {
	return search(key, root);
}

//����� �� ������ ��������� �� ������ �� ������ ��� ����� ��� �������
void BinaryTree::destroy_tree() {
	destroy_tree(root);
}
//public inorder print method
void BinaryTree::inorder_print() {
	inorder_print(root);
	cout << "\n";
}

//inorder print
void BinaryTree::inorder_print(node* leaf) {
	if (leaf != NULL) {
		inorder_print(leaf->left);
		cout << leaf->data << ",";
		inorder_print(leaf->right);
	}
}

//public postorder print method
void BinaryTree::postorder_print() {
	postorder_print(root);
	cout << "\n";
}

//postorder print
void BinaryTree::postorder_print(node* leaf) {
	if (leaf != NULL) {
		inorder_print(leaf->left);
		inorder_print(leaf->right);
		cout << leaf->data << ",";
	}
}

//public preorder print method
void BinaryTree::preorder_print() {
	preorder_print(root);
	cout << "\n";
}

//oreorder print
void BinaryTree::preorder_print(node* leaf) {
	if (leaf != NULL) {
		cout << leaf->data << ",";
		inorder_print(leaf->left);
		inorder_print(leaf->right);
	}
}
