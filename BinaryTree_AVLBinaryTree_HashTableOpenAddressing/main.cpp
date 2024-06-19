#include <BinaryTree.h>
#include <BinaryTreeAVL.h>
#include <HashTableOpenAddressing.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <chrono>
#include <sstream>

using namespace std::chrono;
using namespace std;

//η main του προγραμματος
int main() {
    cout << "Program started. Please wait... " << endl;
    //αρχικοποιηση απαραιτητων μεταβλητων
    std::ifstream file("small-file.txt");
    std::string linestr;
    int words = 0;
    int count = 0;
    int index = 0;
    string* q = new string[5000];

    //διαβαζουμε τις λεξεις του κειμενου για να τις μετρησουμε
    while (std::getline(file, linestr, ' ')) {
        // Process linestr (e.g., eliminate punctuation marks, isolate words)
        std::string chars = ";?_,./-01234567[]89''()':#!";
        for (int i = 0; i < chars.length(); i++) {
            linestr.erase(std::remove(linestr.begin(), linestr.end(), chars[i]), linestr.end());
        }
        if (!linestr.empty()) {
            words = words + 1;
        }
    }
    file.clear();
    file.seekg(0, ios::beg);

    //δημιουργια των δεικτων των τριων δομων του προγραμμματος
    BinaryTree* tree = new BinaryTree();
    BinaryTreeAVL* tree2 = new BinaryTreeAVL();
    HashTableOpenAddressing* t = new HashTableOpenAddressing(words);

    //διαβαζουμε τις λεξεις του κειμενου τις επεξεργαζομαστε καταλληλα
    //και τις εισαγουμε και στις τρεις δομες μας.
    //επισης εισαγουμε 5000 λεξεις (μια λεξη ανα δεκα) στο συνολο q που θα
    //χρησιμοποιησουμε παρακατω για τις αναζητησεις
    while (std::getline(file, linestr, ' ')) {
        std::stringstream ss(linestr);
        while (std::getline(ss, linestr, '\n')) {
            // Process linestr (e.g., eliminate punctuation marks, isolate words)
            std::string chars = ";?_,./!-01234*567[]89()':#<>{}!";
            for (int i = 0; i < chars.length(); i++) {
                linestr.erase(std::remove(linestr.begin(), linestr.end(), chars[i]), linestr.end());
            }
            if (!linestr.empty())
            {
                count = count + 1;
                if (count % 10 == 0 && index < 5000)
                {
                    q[index] = linestr;
                    index = index + 1;
                }
                tree->insert(linestr);
                tree2->insert(linestr);
                t->insert(linestr);
            }



        }

    }

    //αναζητηση λεξεων στο binary tree,εμφανιση της καθε λεξης και το πληθος της στη δομη και καταμετρηση χρονου αποκρισης
    cout << "Binary Tree: " << endl;
    cout << "-------------------------------------------" << endl;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < 5000; i++)
    {
        cout << q[i] << " -> appears " << tree->search(q[i])->amount << " times" << endl;
        //tree->search(q[i]);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);


    //αναζητηση λεξεων στο avl tree,εμφανιση της καθε λεξης και το πληθος της στη δομη και καταμετρηση χρονου αποκρισης
    cout << "AVL Tree: " << endl;
    cout << "-------------------------------------------" << endl;
    auto start2 = high_resolution_clock::now();
    for (int i = 0; i < 5000; i++)
    {
        cout << q[i] << " -> appears " << tree2->search(q[i])->amount << " times" << endl;
        //tree2->search(q[i]);
    }
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<milliseconds>(stop2 - start2);




    //αναζητηση λεξεων στο hash table,εμφανιση της καθε λεξης και το πληθος της στη δομη και καταμετρηση χρονου αποκρισης
    cout << "Hash Table: " << endl;
    cout << "-------------------------------------------" << endl;
    auto start3 = high_resolution_clock::now();
    for (int i = 0; i < 5000; i++)
    {
        cout << q[i] << " -> appears " << t->search(q[i])->amount << " times" << endl;
        //t->search(q[i]);
    }
    auto stop3 = high_resolution_clock::now();
    auto duration3 = duration_cast<milliseconds>(stop3 - start3);



    cout << "-------------------------------------------" << endl;
    //εμφανιση των χρονων(σε microseconds) που χρειαστηκε η καθε δομη για να ανταποκριθει
    cout << "Binary Tree: " << duration.count() << " milliseconds" << endl;
    cout << "AVL Tree:    " << duration2.count() << " milliseconds" << endl;
    cout << "Hash Table:  " << duration3.count() << " milliseconds" << endl;

    cout << endl << "End of Program. Press a key to exit." << endl;
    getchar();

}

