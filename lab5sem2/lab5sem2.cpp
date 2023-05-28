#include <iostream>
#include <string>

using namespace std;

struct Node {
    int key;
    string data;
    Node* left;
    Node* right;
};

Node* createNode(int key, const string& data) {
    Node* newNode = new Node;
    newNode->key = key;
    newNode->data = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

Node* insertNode(Node* root, int key, const string& data) {
    if (root == nullptr)
        return createNode(key, data);

    if (key < root->key)
        root->left = insertNode(root->left, key, data);
    else if (key > root->key)
        root->right = insertNode(root->right, key, data);

    return root;
}

Node* searchNode(Node* root, int key) {
    if (root == nullptr || root->key == key)
        return root;

    if (key < root->key)
        return searchNode(root->left, key);
    else
        return searchNode(root->right, key);
}

Node* deleteNode(Node* root, int key) {
    if (root == nullptr)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* minRight = root->right;
        while (minRight->left != nullptr)
            minRight = minRight->left;

        root->key = minRight->key;
        root->data = minRight->data;
        root->right = deleteNode(root->right, minRight->key);
    }

    return root;
}

void deleteTree(Node* root) {
    if (root == nullptr)
        return;

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

void deleteBranch(Node*& root, int key) {
    if (root == nullptr)
        return;

    if (root->key == key) {
        deleteTree(root);
        root = nullptr;
        return;
    }

    if (key < root->key)
        deleteBranch(root->left, key);
    else
        deleteBranch(root->right, key);
}

void displayTree(Node* root, int level = 0) {
    if (root == nullptr)
        return;

    displayTree(root->right, level + 1);

    for (int i = 0; i < level; i++)
        cout << "    ";

    cout << root->key << endl;

    displayTree(root->left, level + 1);
}

int countNodes(Node* root) {
    if (root == nullptr)
        return 0;
    return countNodes(root->left) + countNodes(root->right) + 1;
}

void convertToSortedArray(Node* root, Node** arr, int* index) {
    if (root == nullptr)
        return;
    convertToSortedArray(root->left, arr, index);
    arr[*index] = root;
    (*index)++;
    convertToSortedArray(root->right, arr, index);
}

Node* balanceTree(Node** arr, int start, int end) {
    if (start > end)
        return nullptr;
    int mid = (start + end) / 2;
    Node* root = arr[mid];
    root->left = balanceTree(arr, start, mid - 1);
    root->right = balanceTree(arr, mid + 1, end);
    return root;
}

int main() {
    Node* root = nullptr;

    while (true) {
        cout << "1. Insert Node\n";
        cout << "2. Search Node\n";
        cout << "3. Delete Node\n";
        cout << "4. Delete Branch\n";
        cout << "5. Display Tree\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            int key;
            string data;
            cout << "Enter key: ";
            cin >> key;
            cout << "Enter data: ";
            cin.ignore();
            getline(cin, data);
            root = insertNode(root, key, data);
            cout << "Node inserted successfully.\n";
            break;
        }
        case 2: {
            int key;
            cout << "Enter key to search: ";
            cin >> key;
            Node* foundNode = searchNode(root, key);
            if (foundNode != nullptr) {
                cout << "Found node - Key: " << foundNode->key << ", Data: " << foundNode->data << endl;
            }
            else {
                cout << "Node with key " << key << " not found.\n";
            }
            break;
        }
        case 3: {
            int key;
            cout << "Enter key to delete: ";
            cin >> key;
            root = deleteNode(root, key);
            cout << "Node with key " << key << " deleted.\n";
            break;
        }
        case 4: {
            int key;
            cout << "Enter key to delete branch: ";
            cin >> key;
            deleteBranch(root, key);
            cout << "Branch with key " << key << " deleted.\n";
            break;
        }
        case 5: {
            cout << "Binary Search Tree:\n";
            displayTree(root);
            break;
        }
        case 6:
            deleteTree(root);
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }

        cout << endl;
    }
}