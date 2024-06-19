#ifndef BINARYTREEAVL_H
#define BINARYTREEAVL_H
#include <iostream>

using namespace std;

//κομβος του δεντρου
struct node2
{
    string data;
    node2* left;
    node2* right;
    int height;
    int amount;
};

class BinaryTreeAVL
{
public:
    void insert(string key);
    void remove(string key);
    node2* search(string key);
    void inorder_print();
    void preorder_print();
    void postorder_print();
    BinaryTreeAVL();


protected:

private:
    void makeEmpty(node2* leaf);
    node2* insert(string key, node2* leaf);
    node2* singleRightRotate(node2*& leaf);
    node2* singleLeftRotate(node2*& leaf);
    node2* doubleLeftRotate(node2*& leaf);
    node2* doubleRightRotate(node2*& leaf);
    node2* search(string key, node2* leaf);
    node2* findMin(node2* leaf);
    node2* findMax(node2* leaf);
    int height(node2* leaf);
    int getBalance(node2* leaf);
    void inorder_print(node2* leaf);
    void preorder_print(node2* leaf);
    void postorder_print(node2* leaf);
    node2* remove(string key, node2* leaf);
    node2* root;

};

#endif // BINARYTREEAVL_H
