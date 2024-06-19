#include "BinaryTreeAVL.h"
#include<iostream>

using namespace std;

//������������ ��� ����� �� NULL
BinaryTreeAVL::BinaryTreeAVL() {
    root = NULL;
}

//��������� �� ������
void BinaryTreeAVL::makeEmpty(node2* leaf)
{
    if (leaf == NULL)
        return;
    makeEmpty(leaf->left);
    makeEmpty(leaf->right);
    delete leaf;
}

//�������� �����
node2* BinaryTreeAVL::insert(string key, node2* leaf)
{
    if (leaf == NULL)
    {
        leaf = new node2;
        leaf->data = key;
        leaf->amount = 1;
        leaf->height = 0;
        leaf->left = leaf->right = NULL;
        //�� � ���� ����� ������������� ��� �� ���� ��� ������ ���� ����
        //������� �� amount ���
    }
    else if (key.compare(leaf->data) == 0)
    {
        leaf->amount = leaf->amount + 1;
        //�� � ���� ����� ������������� ��������� ��� ���� ��� ������
        //���� �� ��������� ��� �������� ��������� ��� ����������� �� ��������� ���
    }
    else if (key.compare(leaf->data) < 0)
    {
        leaf->left = insert(key, leaf->left);
        if (height(leaf->left) - height(leaf->right) == 2)
        {
            if (key.compare(leaf->left->data) < 0)
                leaf = singleRightRotate(leaf);
            else
                leaf = doubleRightRotate(leaf);
        }
    }
    //�� � ���� ����� ������������� ���������� ��� ���� ��� ������
    //���� �� ��������� ��� ���� ��������� ��� ����������� �� ��������� ���
    else if (key.compare(leaf->data) > 0)
    {
        leaf->right = insert(key, leaf->right);
        if (height(leaf->right) - height(leaf->left) == 2)
        {
            if (key.compare(leaf->right->data) > 0)
                leaf = singleLeftRotate(leaf);
            else
                leaf = doubleLeftRotate(leaf);
        }
    }
    leaf->height = max(height(leaf->left), height(leaf->right)) + 1;
    return leaf;
}

//������������� ��� ����� ���������� �� ���� ��� �����
//����������� �� ��������� ���
node2* BinaryTreeAVL::singleRightRotate(node2*& leaf)
{
    if (leaf->left != NULL) {
        node2* u = leaf->left;
        leaf->left = u->right;
        u->right = leaf;
        leaf->height = max(height(leaf->left), height(leaf->right)) + 1;
        u->height = max(height(u->left), leaf->height) + 1;
        return u;
    }
    return leaf;
}

//������������� ��� �������� ���������� �� ���� ��� �����
//����������� �� ��������� ���
node2* BinaryTreeAVL::singleLeftRotate(node2*& leaf)
{
    if (leaf->right != NULL) {
        node2* u = leaf->right;
        leaf->right = u->left;
        u->left = leaf;
        leaf->height = max(height(leaf->left), height(leaf->right)) + 1;
        u->height = max(height(leaf->right), leaf->height) + 1;
        return u;
    }
    return leaf;
}

//������������� ����� �������� ����������
node2* BinaryTreeAVL::doubleLeftRotate(node2*& leaf)
{
    leaf->right = singleRightRotate(leaf->right);
    return singleLeftRotate(leaf);
}

//������������� ����� ����� ����������
node2* BinaryTreeAVL::doubleRightRotate(node2*& leaf)
{
    leaf->left = singleLeftRotate(leaf->left);
    return singleRightRotate(leaf);
}

//������� ������������ ����� ���� ������
node2* BinaryTreeAVL::findMin(node2* leaf)
{
    if (leaf == NULL)
        return NULL;
    else if (leaf->left == NULL)
        return leaf;
    else
        return findMin(leaf->left);
}

//������� ��������� ����� ���� ������
node2* BinaryTreeAVL::findMax(node2* leaf)
{
    if (leaf == NULL)
        return NULL;
    else if (leaf->right == NULL)
        return leaf;
    else
        return findMax(leaf->right);
}

//��������� �����
node2* BinaryTreeAVL::search(string key, node2* leaf) {
    if (leaf != NULL) {
        //�� � ���� ����� ������������� ��� �� ���� ��� ������
        //���������� �� ������
        if (key.compare(leaf->data) == 0) {
            return leaf;
        }
        //�� � ���� ����� ������������� ��������� ��� ���� ��� ������
        //���� ��������� ��� �������� ��������� ���
        if (key.compare(leaf->data) < 0) {
            return search(key, leaf->left);
            //������ ��������� ��� ���� ��������� ���
        }
        else {
            return search(key, leaf->right);
        }
        //�� � ���� ��� ������ ���������� NULL
    }
    else {
        return NULL;
    }
}

node2* BinaryTreeAVL::remove(string key, node2* leaf)
{
    node2* temp;


    // Element not found
    if (leaf == NULL)
        return NULL;
    // Searching for element
    else if (key.compare(leaf->data) < 0)
        leaf->left = remove(key, leaf->left);
    else if (key.compare(leaf->data) > 0)
        leaf->right = remove(key, leaf->right);
    else if (key.compare(leaf->data) == 0 && leaf->amount > 1)
        leaf->amount = leaf->amount - 1;
    // Element found
    // With 2 children
    else if (leaf->left && leaf->right)
    {
        temp = findMin(leaf->right);
        leaf->data = temp->data;
        leaf->right = remove(leaf->data, leaf->right);
    }
    // With one or zero child
    else
    {
        temp = leaf;
        if (leaf->left == NULL)
            leaf = leaf->right;
        else if (leaf->right == NULL)
            leaf = leaf->left;
        delete temp;
    }
    if (leaf == NULL)
        return leaf;

    leaf->height = max(height(leaf->left), height(leaf->right)) + 1;

    // If node is unbalanced
    // If left node is deleted, right case
    if (height(leaf->left) - height(leaf->right) == -2)
    {
        // right right case
        if (height(leaf->right->right) - height(leaf->right->left) == 1)
            return singleLeftRotate(leaf);
        // right left case
        else
            return doubleLeftRotate(leaf);
    }
    // If right node is deleted, left case
    else if (height(leaf->right) - height(leaf->left) == 2)
    {
        // left left case
        if (height(leaf->left->left) - height(leaf->left->right) == 1) {
            return singleRightRotate(leaf);
        }
        // left right case
        else
            return doubleRightRotate(leaf);
    }
    return leaf;
}

//���������� �� ���� ��� �������
int BinaryTreeAVL::height(node2* leaf)
{
    return (leaf == NULL ? -1 : leaf->height);
}

//���������� �� ������� ����� ������ ��� ��� ���������� ���� ������
int BinaryTreeAVL::getBalance(node2* leaf)
{
    if (leaf == NULL)
        return 0;
    else
        return height(leaf->left) - height(leaf->right);
}

//inorder print
void BinaryTreeAVL::inorder_print(node2* leaf)
{
    if (leaf == NULL)
        return;
    inorder_print(leaf->left);
    cout << leaf->data << ",";
    inorder_print(leaf->right);
}

//�������� �����
void BinaryTreeAVL::insert(string key)
{
    root = insert(key, root);
}

//��������� �����
node2* BinaryTreeAVL::search(string key) {
    return search(key, root);
}

//�������� �����
void BinaryTreeAVL::remove(string key)
{
    root = remove(key, root);
}

//inorder print
void BinaryTreeAVL::inorder_print()
{
    inorder_print(root);
    cout << endl;
}

//preorder print
void BinaryTreeAVL::preorder_print() {
    preorder_print(root);
    cout << "\n";
}

//preorder print
void BinaryTreeAVL::preorder_print(node2* leaf) {
    if (leaf != NULL) {
        cout << leaf->data << ",";
        inorder_print(leaf->left);
        inorder_print(leaf->right);
    }
}

//postorder print
void BinaryTreeAVL::postorder_print() {
    postorder_print(root);
    cout << "\n";
}

//postorder print
void BinaryTreeAVL::postorder_print(node2* leaf) {
    if (leaf != NULL) {
        inorder_print(leaf->left);
        inorder_print(leaf->right);
        cout << leaf->data << ",";
    }
}
