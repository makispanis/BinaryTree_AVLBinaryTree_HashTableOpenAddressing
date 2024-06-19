#include "HashTableOpenAddressing.h"

//��� ������������ �������������� � ������� �� NULL �� �������� ������� ��� ���� ��� ������� ��� ������
HashTableOpenAddressing::HashTableOpenAddressing(int k)
{
    capacity = k * 2;

    arr = new hashNode * [capacity];

    for (int i = 0; i < capacity; i++)
        arr[i] = NULL;

    dummy = new hashNode("-");
}

//���������� ��� hash code ��� ���� ����
int HashTableOpenAddressing::hashCode(string key)
{
    return std::hash<std::string>()(key) % capacity;
}

//�������� �����
void HashTableOpenAddressing::insert(string key)
{
    //���������� �� � ���� ������� ��� ���� ������
    hashNode* ch = search(key);
    //�� ��� ������� ��������� ���� ��� ������ ��� ��� ���� ���� ��� linear probing
    if (ch == NULL)
    {
        hashNode* temp = new hashNode(key);
        int hashIndex = hashCode(key);
        while (arr[hashIndex] != NULL && (arr[hashIndex]->key).compare(key) != 0 && (arr[hashIndex]->key).compare("-") != 0)
        {
            hashIndex++;
            hashIndex %= capacity;
        }


        arr[hashIndex] = temp;
        arr[hashIndex]->amount = 1;
    }
    else
        //�� ������� ��� ���� ��������� �� amount ���
    {
        ch->amount = ch->amount + 1;
    }

}

//��������� �����
hashNode* HashTableOpenAddressing::search(string key)
{
    //������������� ���������� ������� �� �� ���� ��� �� ������ �� ����� � ����
    //��� ������ ���� ��� hash code ���
    int hashIndex = hashCode(key);
    int counter = 0;
    //��������� ����� �� linear probing
    while (arr[hashIndex] != NULL)
    {
        int counter = 0;
        if (counter++ > capacity)
            return NULL;
        if ((arr[hashIndex]->key).compare(key) == 0)
            return arr[hashIndex];
        hashIndex++;
        hashIndex %= capacity;
    }
    return NULL;

}

//�������� ��� ������������ ��� ������
void HashTableOpenAddressing::display()
{
    for (int i = 0; i < capacity; i++)
    {
        if (arr[i] != NULL && (arr[i]->key).compare("-") != 0)
            cout << "key = " << arr[i]->key << endl;
    }
}


