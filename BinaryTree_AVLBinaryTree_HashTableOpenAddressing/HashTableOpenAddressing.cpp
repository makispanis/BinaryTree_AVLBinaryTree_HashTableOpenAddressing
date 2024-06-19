#include "HashTableOpenAddressing.h"

//στο κατασκευαστη αρχικοποιειται ο πινακας σε NULL με διπλασιο μεγεθος απο αυτο του πληθους των λεξεων
HashTableOpenAddressing::HashTableOpenAddressing(int k)
{
    capacity = k * 2;

    arr = new hashNode * [capacity];

    for (int i = 0; i < capacity; i++)
        arr[i] = NULL;

    dummy = new hashNode("-");
}

//επιστρεφει ενα hash code για καθε λεξη
int HashTableOpenAddressing::hashCode(string key)
{
    return std::hash<std::string>()(key) % capacity;
}

//εισαγωγη λεξης
void HashTableOpenAddressing::insert(string key)
{
    //αναζητουμε αν η λεξη υπαρχει ηδη στον πινακα
    hashNode* ch = search(key);
    //αν δεν υπαρχει βρισκουμε θεση στο πινακα για την λεξη βαση του linear probing
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
        //αν υπαρχει ηδη απλα αυξανεται το amount της
    {
        ch->amount = ch->amount + 1;
    }

}

//αναζητηση λεξης
hashNode* HashTableOpenAddressing::search(string key)
{
    //αρχικοποιησει μεταβλητων συμφωνα με τη θεση που θα επρεπε να ειναι η λεξη
    //στο πινακα βαση του hash code της
    int hashIndex = hashCode(key);
    int counter = 0;
    //αναζητηση λεξης με linear probing
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

//εμφανιση του περιεχομενου του πινακα
void HashTableOpenAddressing::display()
{
    for (int i = 0; i < capacity; i++)
    {
        if (arr[i] != NULL && (arr[i]->key).compare("-") != 0)
            cout << "key = " << arr[i]->key << endl;
    }
}


