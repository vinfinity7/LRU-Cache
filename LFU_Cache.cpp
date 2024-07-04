/*
NAME OF THE PROJECT : FrequentlyContactedLFU

ALGORITHM USED : LFU (Least Frequently Used) Cache

CACHE : -> Stores data to speed up future requests
        -> May be a previous computation or redundant copy of the data

LFU CACHE : -> Least frequently used element is removed when the cache exceeds its limit

DATA STRUCTURES : -> Doubly Linked List
                  -> Hash Map
                  -> Frequency List

TIME COMPLEXITY : -> Searching element in Hash Map - O(1)
                  -> Inserting new element in Hash Map - O(1)
                  -> Deleting element in Hash Map - O(1)

SPACE COMPLEXITY : O(n)

APPLICATIONS : -> Caching in web browsers
               -> Database page replacement algorithms
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX 5

struct ListNode
{
    string name;
    int frequency;
    ListNode *prev;
    ListNode *next;
};

class LFUCache
{
private:
    unordered_map<string, ListNode *> nodeMap;
    unordered_map<int, list<ListNode *>> freqMap;
    int minFreq;
    int size;
    int capacity;

public:
    LFUCache(int cap) : capacity(cap), size(0), minFreq(0) {}

    void insert_list(const string &name)
    {
        if (capacity == 0)
            return;

        if (nodeMap.find(name) != nodeMap.end())
        {
            ListNode *node = nodeMap[name];
            freqMap[node->frequency].remove(node);
            if (freqMap[node->frequency].empty())
            {
                freqMap.erase(node->frequency);
                if (node->frequency == minFreq)
                    minFreq++;
            }
            node->frequency++;
            freqMap[node->frequency].push_back(node);
        }
        else
        {
            if (size == capacity)
            {
                ListNode *node = freqMap[minFreq].front();
                freqMap[minFreq].pop_front();
                nodeMap.erase(node->name);
                if (freqMap[minFreq].empty())
                {
                    freqMap.erase(minFreq);
                }
                delete node;
                size--;
            }
            ListNode *newNode = new ListNode{name, 1, nullptr, nullptr};
            nodeMap[name] = newNode;
            freqMap[1].push_back(newNode);
            minFreq = 1;
            size++;
        }
    }

    void display()
    {
        cout << "Chat History - " << endl;
        for (auto &it : freqMap)
        {
            auto freq = it.first;
            auto nodeList = it.second;
            for (auto &node : nodeList)
            {
                cout << node->name << " (Frequency: " << node->frequency << ")" << endl;
            }
        }
    }
};

int main()
{
    LFUCache cache(MAX);

    cout << " * * * CHAT LIST * * * " << endl;

    // MENU
    while (true)
    {
        int choice;
        cout << "Choose an option -" << endl;
        cout << "1. Add new contact" << endl;
        cout << "2. Display Chat List" << endl;
        cout << "3. Exit" << endl;
        cout << "--> ";

        cin >> choice;
        cout << "------------------------------------------------------" << endl;

        if (choice == 1)
        {
            cout << "Enter new contact: ";
            string name;
            cin >> name;
            cache.insert_list(name);
        }
        else if (choice == 2)
        {
            cache.display();
        }
        else
        {
            break;
        }

        cout << "------------------------------------------------------" << endl;
    }

    return 0;
}
