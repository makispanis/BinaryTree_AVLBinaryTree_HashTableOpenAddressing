#include <iostream>

using namespace std;

//���� ��� ������
struct hashNode {
    string key;
    int amount;
    hashNode(string key)
    {
        this->key = key;
    }
};


class HashTableOpenAddressing
{
public:
    void insert(string key);
    hashNode* search(string key);
    void display();
    HashTableOpenAddressing(int);

protected:

private:
    hashNode** arr;
    int capacity;
    hashNode* dummy;
    int hashCode(string key);


};



