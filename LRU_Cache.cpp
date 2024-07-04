/*
NAME OF THE PROJECT : FrequentlyContacted

ALGORITHM USED : LRU (Least Recently Used) Cache

CACHE : -> Stores data to speed up future requests
        -> May be a previous computaion or redundant copy of the data
        
LRU CACHE : -> Most recent element is brought to the top
            -> Element that exceeds the limit is dropped out

DATA STRUCTURES : -> Doubly Linked List
                  -> Binary Search Tree

TIME COMPLEXITY : -> Searching element in BST - O(log n)
                  -> Inserting new element in linked list - O(1)
                  -> Deleting last element in linked list - O(1)

SPACE COMPLEXITY : O(n)

APPLICATIONS : -> WhatsApp Chat history
               -> Recently used apps on smartphone
               -> Notification Panel
*/

#include <bits/stdc++.h>

#define MAX 5
int length = 0;

// Use the std namespace
using namespace std;

// DOUBLY LINKED LIST

struct ListNode {
    string name;
    ListNode* prev;
    ListNode* next;
};

ListNode* head = nullptr;
ListNode* tail = nullptr;

void insert_list(const string& name) {
    ListNode* temp = new ListNode{name, nullptr, nullptr};

    if (head == nullptr) {
        head = temp;
        tail = temp;
    } else {
        temp->next = head;
        head->prev = temp;
        head = temp;
    }
}

void delete_last_list() {
    ListNode* del = tail;
    tail = tail->prev;
    if (tail) tail->next = nullptr;
    delete del;
}

void print(ListNode* p) {
    while (p != nullptr) {
        cout << p->name << endl;
        p = p->next;
    }
}

// BINARY SEARCH TREE

struct TreeNode {
    string name;
    ListNode* address;
    TreeNode* lchild;
    TreeNode* rchild;
};

TreeNode* root = nullptr;

TreeNode* insert_bst(TreeNode* t, const string& name, ListNode* address) {
    if (t == nullptr) {
        TreeNode* temp = new TreeNode{name, address, nullptr, nullptr};
        return temp;
    }
    if (name < t->name) {
        t->lchild = insert_bst(t->lchild, name, address);
    } else if (name > t->name) {
        t->rchild = insert_bst(t->rchild, name, address);
    }
    return t;
}

int height(TreeNode* t) {
    if (t == nullptr) return 0;
    int x = height(t->lchild);
    int y = height(t->rchild);
    return max(x, y) + 1;
}

TreeNode* pred(TreeNode* t) {
    while (t != nullptr && t->rchild != nullptr) {
        t = t->rchild;
    }
    return t;
}

TreeNode* succ(TreeNode* t) {
    while (t != nullptr && t->lchild != nullptr) {
        t = t->lchild;
    }
    return t;
}

TreeNode* delete_bst(TreeNode* t, const string& name) {
    if (t == nullptr) return t;

    if (name > t->name) {
        t->rchild = delete_bst(t->rchild, name);
    } else if (name < t->name) {
        t->lchild = delete_bst(t->lchild, name);
    } else {
        if (t->lchild == nullptr && t->rchild == nullptr) {
            delete t;
            t = nullptr;
        } else if (t->lchild != nullptr && t->rchild != nullptr) {
            if (height(t->lchild) > height(t->rchild)) {
                TreeNode* temp = pred(t->lchild);
                t->name = temp->name;
                t->address = temp->address;
                t->lchild = delete_bst(t->lchild, temp->name);
            } else {
                TreeNode* temp = succ(t->rchild);
                t->name = temp->name;
                t->address = temp->address;
                t->rchild = delete_bst(t->rchild, temp->name);
            }
        } else {
            TreeNode* temp = t;
            t = (t->lchild != nullptr) ? t->lchild : t->rchild;
            delete temp;
        }
    }
    return t;
}

TreeNode* search_bst(TreeNode* t, const string& name) {
    if (t == nullptr) return nullptr;
    if (t->name == name) return t;
    else if (t->name > name) return search_bst(t->lchild, name);
    else return search_bst(t->rchild, name);
}

int main() {
    cout << " * * * CHAT LIST * * * " << endl;

    // MENU
    while (true) {
        int choice;
        cout << "Choose an option -" << endl;
        cout << "1. Add new contact" << endl;
        cout << "2. Display Chat List" << endl;
        cout << "3. Exit" << endl;
        cout << "--> ";
        
        cin >> choice;
        cout << "------------------------------------------------------" << endl;

        if (choice == 1) {
            cout << "Enter new contact: ";
            string name;
            cin >> name;

            TreeNode* check = search_bst(root, name);

            if (check == nullptr) {
                // Element is not present in the BST
                insert_list(name);
                root = insert_bst(root, name, head);
                length++;

                if (length > MAX) {
                    // Delete last element
                    root = delete_bst(root, tail->name);
                    delete_last_list();
                    length--;
                }
            } else {
                // Element is already present in the BST
                ListNode* add_node = check->address;

                if (add_node == head)
                    continue;

                else if (add_node == tail) {
                    delete_last_list();
                    insert_list(name);
                    check->address = head;
                } else {
                    add_node->prev->next = add_node->next;
                    add_node->next->prev = add_node->prev;
                    delete add_node;
                    insert_list(name);
                    check->address = head;
                }
            }
        } else if (choice == 2) {
            cout << "Chat History - " << endl;
            print(head);
        } else {
            break;
        }

        cout << "------------------------------------------------------" << endl;
    }

    return 0;
}
