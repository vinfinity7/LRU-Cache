# Who-LU?

## Project Overview

**Who-LU?** is a C++ program implementing two caching mechanisms:
- Least Recently Used (LRU) Cache
- Least Frequently Used (LFU) Cache

Both caches utilize combinations of different data structures to store data and speed up future requests. The LRU cache keeps the most recently accessed elements, while the LFU cache maintains the least frequently accessed elements.

## Table of Contents

- [Algorithm](#algorithm)
- [Data Structures](#data-structures)
- [Time Complexity](#time-complexity)
- [Space Complexity](#space-complexity)
- [Applications](#applications)
- [Code Overview](#code-overview)
- [Setup and Usage](#setup-and-usage)
- [Example Usage](#example-usage)

## Algorithm

### LRU Cache

The LRU (Least Recently Used) Cache ensures that the most recently accessed elements are kept readily available. When the cache exceeds its limit, the least recently used elements are discarded.

#### Key Points:
- **Most recent element is brought to the top**: Elements accessed or added most recently are moved to the front of the list.
- **Element that exceeds the limit is dropped out**: If the cache exceeds its defined maximum size, the least recently used element (at the end of the list) is removed.

### LFU Cache

The LFU (Least Frequently Used) Cache ensures that the least frequently accessed elements are removed when the cache exceeds its limit.

#### Key Points:
- **Least frequently used element is removed**: Elements that are accessed the least frequently are removed first.
- **Frequency list**: Maintains elements sorted by their access frequency.

## Data Structures

### LRU Cache

#### Doubly Linked List
A doubly linked list is used to keep track of the order of usage of the elements.

#### Binary Search Tree (BST)
A binary search tree is used to maintain the elements in a sorted manner and provides efficient search operations.

### LFU Cache

#### Doubly Linked List
A doubly linked list keeps track of the order of usage of the elements within each frequency bucket.

#### Hash Map
A hash map provides quick access to elements and their frequencies.

#### Frequency List
A frequency list maintains elements sorted by their access frequency.

## Time Complexity

### LRU Cache

- **Searching an element in BST**: `O(log n)`
- **Inserting a new element in linked list**: `O(1)`
- **Deleting the last element in linked list**: `O(1)`

### LFU Cache

- **Searching an element in Hash Map**: `O(1)`
- **Inserting a new element in Hash Map**: `O(1)`
- **Deleting an element in Hash Map**: `O(1)`

## Space Complexity

- **Space Complexity**: `O(n)`, where `n` is the number of elements in the cache.

## Applications

The caches can be used in various applications where maintaining the most or least recently/frequently accessed elements is beneficial, such as:
- WhatsApp Chat history (LRU)
- Recently used apps on smartphones (LRU)
- Caching in web browsers (LFU)
- Database page replacement algorithms (LFU)

## Code Overview

### Structure Definitions

#### LRU Cache

##### ListNode

Represents a node in the doubly linked list.

```cpp
struct ListNode {
    std::string name;
    ListNode* prev;
    ListNode* next;
};
```

##### TreeNode

Represents a node in the binary search tree.

```cpp
struct TreeNode {
    std::string name;
    ListNode* address;
    TreeNode* lchild;
    TreeNode* rchild;
};
```

#### LFU Cache

##### ListNode

Represents a node in the doubly linked list.

```cpp
struct ListNode {
    std::string name;
    int frequency;
    ListNode* prev;
    ListNode* next;
};
```

### Functions

#### LRU Cache Functions

- **insert_list**: Inserts a new element at the front of the list.
- **delete_last_list**: Deletes the last element from the list.
- **print**: Prints the elements of the list.
- **insert_bst**: Inserts a new element into the BST.
- **height**: Computes the height of the BST.
- **pred**: Finds the predecessor node in the BST.
- **succ**: Finds the successor node in the BST.
- **delete_bst**: Deletes an element from the BST.
- **search_bst**: Searches for an element in the BST.

#### LFU Cache Functions

- **insert_list**: Inserts a new element into the LFU cache.
- **display**: Displays the elements in the LFU cache.

### Main Function

The main function provides a menu-driven interface to add new contacts and display the chat list.

```cpp
int main() {
    cout << "Choose Cache Type:\n1. LRU Cache\n2. LFU Cache\n--> ";
    int cacheType;
    cin >> cacheType;

    if (cacheType == 1) {
        // LRU Cache
        cout << " * * * CHAT LIST (LRU) * * * " << endl;

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
                    insert_list(name);
                    root = insert_bst(root, name, head);
                    length++;

                    if (length > MAX) {
                        root = delete_bst(root, tail->name);
                        delete_last_list();
                        length--;
                    }
                } else {
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
    } else if (cacheType == 2) {
        // LFU Cache
        LFUCache cache(MAX);

        cout << " * * * CHAT LIST (LFU) * * * " << endl;

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
                cache.insert_list(name);
            } else if (choice == 2) {
                cache.display();
            } else {
                break;
            }

            cout << "------------------------------------------------------" << endl;
        }
    }

    return 0;
}
```

## Setup and Usage

### Prerequisites

- C++ compiler (e.g., `g++`)

### Compilation

To compile the program, use the following command:

```sh
g++ -o frequently_contacted frequently_contacted.cpp
```

### Running the Program

To run the program, use the following command:

```sh
./frequently_contacted
```

### Menu Options

1. **Add new contact**: Allows you to add a new contact to the chat list.
2. **Display Chat List**: Displays the current chat list.
3. **Exit**: Exits the program.

## Example Usage

Upon running the program, you will see the following menu:

```
Choose Cache Type:
1. LRU Cache
2. LFU Cache
--> 
```

- Select option `1` to use LRU Cache.
- Select option `2` to use LFU Cache.

### LRU Cache Interaction

```
 * * * CHAT LIST (LRU) * * * 
Choose an option -
1. Add new contact
2. Display Chat List
3. Exit
--> 1
------------------------------------------------------
Enter new contact: Homelander
------------------------------------------------------
Choose an option -
1. Add new contact
2. Display Chat List
3. Exit
--> 1
------------------------------------------------------
Enter new contact: Deep
------------------------------------------------------
Choose an option -
1. Add new contact
2. Display Chat List
3. Exit
--> 2
------------------------------------------------------
Chat History - 
Deep
Homelander
------------------------------------------------------
Choose an option -
1. Add new contact
2. Display Chat List
3. Exit
--> 3
------------------------------------------------------
```

### LFU Cache Interaction

```
 * * * CHAT LIST (LFU) * * * 
Choose an option -
1. Add new contact
2. Display Chat List
3. Exit
--> 1
------------------------------------------------------
Enter new contact: Homelander
------------------------------------------------------
Choose an option -
1.

 Add new contact
2. Display Chat List
3. Exit
--> 1
------------------------------------------------------
Enter new contact: Deep
------------------------------------------------------
Choose an option -
1. Add new contact
2. Display Chat List
3. Exit
--> 2
------------------------------------------------------
Chat History - 
Homelander (Frequency: 1)
Deep (Frequency: 1)
------------------------------------------------------
Choose an option -
1. Add new contact
2. Display Chat List
3. Exit
--> 3
------------------------------------------------------
```

This example shows adding two contacts (`Homelander` and `Deep`) and displaying the chat list, which lists `Homelander` and `Deep` with their respective access frequencies in LFU cache.