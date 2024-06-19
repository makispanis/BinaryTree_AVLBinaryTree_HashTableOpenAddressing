#include "BinaryTree.h"

//αρχικοποιση της ριζας σε NULL
BinaryTree::BinaryTree() {
	root = NULL;
}

//destructor του δεντρου
BinaryTree::~BinaryTree() {
	destroy_tree();
}
//public remove μεθοδος
void BinaryTree::remove(string key)
{
	root = remove(root, key);
}

//αναζητηση του αριστεροτερου φυλλου
node* BinaryTree::minValueNode(node* node)
{
	struct node* current = node;


	while (current && current->left != NULL)
		current = current->left;

	return current;
}

//διαγραφη λεξης
node* BinaryTree::remove(node* root, string key)
{
	if (root == NULL)
		return root;

	// αν η λεξη που ειναι να διαγραφει ειναι λεξικογραφικα μικροτερη απο αυτη της ριζας,
	// τοτε βρισκεται στο αριστερο υποδεντρο
	if (key.compare(root->data) < 0)
		root->left = remove(root->left, key);

	// αν η λεξη που ειναι να διαγραφει ειναι λεξικογραφικα μεγαλυτερη απο αυτη της ριζας,
	// τοτε βρισκεται στο δεξι υποδεντρο
	else if (key.compare(root->data) > 0)
		root->right = remove(root->right, key);

	//η λεξη υπαρχει περισσοτερες απο μια φορες μειωνεται το amount της
	else if (key.compare(root->data) == 0 && root->amount > 1)
		root->amount = root->amount - 1;
	// αν η λεξη ειναι ιδια με τη ριζα τοτε αυτη ειναι
	//που πρεπει να διαγραφει
	else
	{
		// κομβος με ενα η κανενα παιδι
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


		//κομβος με δυο παιδια: παιρνουμε τον inorder διαδοχο(ο μικροτερος
		//στο δεξι υποδεντρο)
		node* temp = minValueNode(root->right);

		//αντιγραφη περιεχομενου του inorder διαδοχου σε αυτο το κομβο
		root->data = temp->data;

		// διαγραφει inorder διαδοχου
		root->right = remove(root->right, temp->data);
	}
	return root;
}

//αναδρομικη διαγραφη καθε κομβου
void BinaryTree::destroy_tree(node* leaf) {
	if (leaf != NULL) {
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		delete leaf;
	}
}

//εισαγωγη λεξης
void BinaryTree::insert(string key, node* leaf) {
	//αν η λεξη υπαρχει ηδη αυξανεται το amount της
	if (key.compare(leaf->data) == 0) {
		leaf->amount = leaf->amount + 1;
		// αν η λεξη που ειναι εισαγεται ειναι λεξικογραφικα μικροτερη απο αυτη του δεικτη,
		// τοτε θα εισαγθει στο αριστερο του υποδεντρο
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
		// αν η λεξη που ειναι εισαγεται ειναι λεξικογραφικα μεγαλυτερη απο αυτη του δεικτη,
	// τοτε θα εισαγθει στο δεξι του υποδεντρο
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

//public insert μεθοδος
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

//αναζητηση λεξης
node* BinaryTree::search(string key, node* leaf) {
	if (leaf != NULL) {
		// αν η λεξη που αναζητειται ειναι λεξικογραφικα ιδια με αυτη του δεικτη,
		// τοτε επιστρεφεται ο δεικτης του κομβου
		if (key.compare(leaf->data) == 0) {
			return leaf;
		}
		// αν η λεξη που αναζητειται ειναι λεξικογραφικα μικροτερη απο αυτη του δεικτη,
		// τοτε βρισκεται στο αριστερο υποδεντρο
		if (key.compare(leaf->data) < 0) {
			return search(key, leaf->left);
			// αν η λεξη που αναζητειται ειναι λεξικογραφικα μεγαλυτερη απο αυτη της ριζας,
			// τοτε βρισκεται στο δεξι υποδεντρο
		}
		else {
			return search(key, leaf->right);
		}
	}
	else {
		//αν δεν βρεθει επιστροφει NULL
		return NULL;
	}
}

//public search μεθοδος
node* BinaryTree::search(string key) {
	return search(key, root);
}

//καλει τη μεθοδο διαγραφης με ορισμα το δεικτη της ριζας του δεντρου
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
