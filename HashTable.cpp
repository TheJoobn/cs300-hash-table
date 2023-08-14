//============================================================================
// Name        : HashTable.cpp
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
/* Author:     : Jaden Knutson

Description: Hash Table Bids –  
    The given program is a C++ implementation of a hash table with chaining. 
    It includes header files, global definitions, and a structure to hold bid information. 
    The program defines a class called `HashTable`. 
    The class has methods to insert a bid, print all bids, remove a bid, and search for a bid based on its bidId. 

    The program also includes additional functions to: 
            display a bid, 
            load bids from a CSV file into the hash table, 
            and convert a string to a double. 

    The main function provides a menu-driven interface to interact with the hash table, including options to: 
            load bids, 
            display all bids, 
            find a bid, 
            remove a bid, 
            and exit the program.

    I have added in menu options 6 and 7 so the user can choose between the two bid files.
            Option 6 - Switches the load directory to: eBid_Monthly_Sales.csv
            Option 7 - Switches the load directory to: eBid_Monthly_Sales_Dec_2016.csv
                        - Once the new directory is switched, the user can reload by entering "1" and can now sort/display the new file.

File Names:
        //eBid_Monthly_Sales.csv		   - 12023  lines
        //eBid_Monthly_Sales_Dec_2016.csv  - 76	    line
        /*HashTableFinal.exe eBid_Monthly_Sales.csv - pass file name to program directly as a paramete at the command line or
                                                    - OR pass a bidld after the file name */

/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/
#include <algorithm>
#include <climits>
#include <iostream>
#include <string> // atoi
#include <time.h>
#include "CSVparser.hpp"
using namespace std;
//============================================================================
// Global definitions visible to all methods and classes
//============================================================================
const unsigned int DEFAULT_SIZE = 179;
//------------------------------------------------------------------
int numBidsLoaded = 0;//ADDED THIS <--------
//------------------------------------------------------------------
// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};
//------------------------------------------------------------------
void displayBid(Bid bid);//ADDED THIS <--------
/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/









//============================================================================
// Hash Table class definition
/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/
//Define a class containing data members and methods to implement a hash table with chaining.
class HashTable {
private:
    // Define structures to hold bids
    struct Node {
        Bid bid;
        unsigned int key;
        Node* next;

        // default constructor
        Node() {
            key = UINT_MAX;
            next = nullptr;
        }
        // initialize with a bid
        Node(Bid aBid) : Node() {
            bid = aBid;
        }
        // initialize with a bid and a key
        Node(Bid aBid, unsigned int aKey) : Node(aBid) {
            key = aKey;
        }
    };

    vector<Node> nodes;
    unsigned int tableSize = DEFAULT_SIZE;
    unsigned int hash(int key);

public:
    HashTable();
    HashTable(unsigned int size);
    virtual ~HashTable();
    void Insert(Bid bid);
    void PrintAll();
    void Remove(string bidId);
    Bid Search(string bidId);
};
/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/










/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/
//Default constructor - VIDEO CHECKED
HashTable::HashTable() {
    // FIXME (1): Initialize the structures used to hold bids
    nodes.resize(tableSize); // Resize the nodes vector to match the table size
}
//============================================================================
//============================================================================
//Constructor for specifying size of the table - VIDEO CHECKED
HashTable::HashTable(unsigned int size) {
    // invoke local tableSize to size with this->
    this->tableSize = size;

    // resize nodes vector to size
    nodes.resize(size);
}
//============================================================================
//============================================================================
//Destructor - VIDEO CHECKED
HashTable::~HashTable() {
    // FIXME (2): Implement logic to free storage when class is destroyed
    nodes.erase(nodes.begin()); // Clear the nodes vector to free the storage
}
//============================================================================
//============================================================================
//Calculate the hash value of a given key - VIDEO CHECKED
unsigned int HashTable::hash(int key) {
    // FIXME (3): Implement logic to calculate a hash value
    // return key modulo tableSize
    return key % tableSize; // Use the modulo operator to calculate the hash value
}
//============================================================================
//============================================================================
//Insert a bid - VIDEO CHECKED
void HashTable::Insert(Bid bid) {
    // FIXME (5): Implement logic to insert a bid
    // create the key for the given bid
    unsigned key = hash(atoi(bid.bidId.c_str())); // Calculate the hash value using bid's bidId

    // retrieve node using key
    Node* node = &(nodes.at(key));

    // if no entry found for the key
    if (node == nullptr) {
        Node* newNode = new Node(bid, key);
        nodes.insert(nodes.begin() + key, (*newNode));
    }
    // else if node is not used
    else {
        if (node->key == UINT_MAX) {
            // assign old node key to UINT_MAX, set it to key, set old node to bid, and set old node next to null pointer
            node->key = key;
            node->bid = bid;
            node->next = nullptr;
        }
        // else find the next open node
        else {
            while (node->next != nullptr) {
                node = node->next;
            }
            // add new newNode to the end
            node->next = new Node(bid, key);
        }
    }
}
//============================================================================
//============================================================================
//Print all bids - VIDEO CHECKED
void HashTable::PrintAll() {
    // FIXME (6): Implement logic to print all bids
    // For each node from begin to end, iterate
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        // If the key is not equal to UINT_MAX
        if (it->key != UINT_MAX) {
            // Output the key, bidID, title, amount, and fund
            cout << "Key " << it->key << ": " << it->bid.bidId << " | " << it->bid.title << " | " << it->bid.fund << endl;

            // Move to the next node
            Node* node = it->next;
            while (node != nullptr) {
                // Output the key, bidID, title, amount, and fund
                cout << "    " << node->key << ": " << node->bid.bidId
                     << " | " << node->bid.title << " | " << node->bid.amount
                     << " | " << node->bid.fund << endl;
                node = node->next;
            }
        }
    }
}
//============================================================================
//============================================================================
//Remove a bid - VIDEO CHECKED
    // FIXME (7): Implement logic to remove a bid
    // set key equal to hash atoi bidId cstring
    // erase node at the beginning of key
void HashTable::Remove(string bidId) {
    // FIXME (7): Implement logic to remove a bid
    // Set key equal to the hash of bidId converted to an integer
    unsigned int key = hash(atoi(bidId.c_str()));

    // Find the node at the beginning of key
    Node* node = &(nodes.at(key));
    if (node->key != UINT_MAX) {
        // If the node at the beginning of key matches the bidId, remove it
        if (node->bid.bidId.compare(bidId) == 0) {
            // Remove this node
            std::cout << "remove top nodes for " << bidId << std::endl;
            if (node->next == nullptr) {
                // If there are no other nodes, mark the key as empty
                node->key = UINT_MAX;
                return;
            }
            else {
                // If there are other nodes, replace the current node with the next node
                nodes.at(key) = *(node->next);
                return;
            }
        }
        else {
            // If the first node doesn't match bidId, search for the matching node in the linked list
            Node *cur = node->next;
            Node *pre = node;
            while (cur != nullptr) {
                if (cur->bid.bidId.compare(bidId) == 0) {
                    // Delete this node
                    pre->next = cur->next;
                    delete cur;
                    cur = nullptr;
                    return;
                }
                pre = cur;
                cur = cur->next;
            }
        }
    }
}

//============================================================================
//============================================================================
//Search for the specified bidId - VIDEO CHECKED
Bid HashTable::Search(string bidId) {
    Bid bid;

    // FIXME (8): Implement logic to search for and return a bid
    unsigned int key = hash(atoi(bidId.c_str())); // Create the key for the given bid by converting bidId to an integer and calculating the hash value
    Node* node = &(nodes.at(key)); // Get the node corresponding to the key from the nodes vector

    // Check if the first node matches the bidId
    if (node != nullptr && node->key != UINT_MAX && node->bid.bidId.compare(bidId) == 0) {
        return node->bid;  // If the current node matches the bidId, return it
    }
    // If no entry found for the key
    if (node == nullptr || node->key == UINT_MAX) {
        return bid;  // Return an empty bid
    }
    while (node != nullptr) {
        // If the current node matches the bidId, return it
        if (node->key != UINT_MAX && node->bid.bidId.compare(bidId) == 0) {
            return node->bid;
        }
        node = node->next;  // Move to the next node
    }
    return bid;  // Return an empty bid if no matching bid is found
}
/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/









//============================================================================
// Static methods used for testing
/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/
//Display the bid information to the console (std::out)
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | " << bid.fund << endl;
    return;
}
//============================================================================
//============================================================================
 //Load a CSV file containing bids into a container
 //@param csvPath the path to the CSV file to load
 //@return a container holding all the bids read

void loadBids(string csvPath, HashTable* hashTable) {
    cout << endl;
    cout << "Loading CSV file " << csvPath << endl;
    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);
//------------------------------------------------------------------
    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        //cout << c << " | ";   turning off as it is not seen in example output
    }
    //cout << "" << endl;
//------------------------------------------------------------------
    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {
            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

     //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;
            // push this bid to the end
            hashTable->Insert(bid);
//------------------------------------------------------------------
            numBidsLoaded++;//ADDED THIS <-------- counts bids loaded
//------------------------------------------------------------------
        }
    }
    catch (csv::Error& e) {
        std::cerr << e.what() << std::endl;
    }
}
//============================================================================
//============================================================================
// Simple C function to convert a string to a doublE after stripping out unwanted characters
// credit: http://stackoverflow.com/a/24875936
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end()); // Remove the specified character from the string
    return atof(str.c_str()); // Convert the modified string to a double
}
/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/











/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/
/* ░██████╗████████╗░█████╗░██████╗░████████╗      ███╗░░░███╗░█████╗░██╗███╗░░██╗
   ██╔════╝╚══██╔══╝██╔══██╗██╔══██╗╚══██╔══╝      ████╗░████║██╔══██╗██║████╗░██║
   ╚█████╗░░░░██║░░░███████║██████╔╝░░░██║░░░      ██╔████╔██║███████║██║██╔██╗██║
   ░╚═══██╗░░░██║░░░██╔══██║██╔══██╗░░░██║░░░      ██║╚██╔╝██║██╔══██║██║██║╚████║
   ██████╔╝░░░██║░░░██║░░██║██║░░██║░░░██║░░░      ██║░╚═╝░██║██║░░██║██║██║░╚███║
   ╚═════╝░░░░╚═╝░░░╚═╝░░╚═╝╚═╝░░╚═╝░░░╚═╝░░░      ╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═╝╚═╝░░╚══╝  - The one and only main() method*
/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/
int main(int argc, char* argv[]) {
//------------------------------------------------------------------
    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98129";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98129";
    }
//============================================================================
    // Define a timer variable
    clock_t ticks;

    // Define a hash table to hold all the bids
    HashTable* bidTable;
    Bid bid;
    bidTable = new HashTable();
//============================================================================
    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
/*================================================================================================================================*/
 //ADDED OPTION 6 AND 7        
        cout << "  6. Switch load designation to: eBid_Monthly_Sales.csv" << endl;
        cout << "  7. Switch load designation to: eBid_Monthly_Sales_Dec_2016.csv (default)" << endl;
/*================================================================================================================================*/
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cout << endl;
//============================================================================
        switch (choice) {
//------------------------------------------------------------------
        case 1:
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bidTable);
      
            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "Bids Loaded: " << numBidsLoaded << endl; //ADDED THIS <--------
            cout << "Time: " << ticks << " Clock Ticks" << endl;
            cout << "Time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;
//------------------------------------------------------------------
        case 2:
            bidTable->PrintAll();
            break;
//------------------------------------------------------------------
        case 3:
            ticks = clock();
            bid = bidTable->Search(bidKey);
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            }
            else {
                cout << "Bid Id " << bidKey << " not found." << endl;
            }
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;
//------------------------------------------------------------------
        case 4:
            bidTable->Remove(bidKey);
            break;
/*================================================================================================================================*/
//NEW MENU OPTION        
        case 6:
            csvPath = "eBid_Monthly_Sales.csv";
            cout << "You've switched the load designation to: eBid_Monthly_Sales.csv" << endl;
            cout << "Please Re-Load the bids." << endl;
            cout << endl;
            break;
//------------------------------------------------------------------
//NEW MENU OPTION   
            /* Option 7 - Changes the designated load file to eBid_Monthly_Sales_Dec_2016.csv */
        case 7:
            csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
            cout << "You've switched the load designation to: eBid_Monthly_Sales_Dec_2016.csv" << endl;
            cout << "Please Re-Load the bids." << endl;
            cout << endl;
            break;
        }//End Switch-Case

//ADDED BLANK LINES
    cout << "---" << endl << endl;
/*================================================================================================================================*/
    }
    cout << "Good bye." << endl;
    return 0;
}
/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/
  /*███████╗███╗░░██╗██████╗░      ███╗░░░███╗░█████╗░██╗███╗░░██╗
    ██╔════╝████╗░██║██╔══██╗      ████╗░████║██╔══██╗██║████╗░██║
    █████╗░░██╔██╗██║██║░░██║      ██╔████╔██║███████║██║██╔██╗██║
    ██╔══╝░░██║╚████║██║░░██║      ██║╚██╔╝██║██╔══██║██║██║╚████║
    ███████╗██║░╚███║██████╔╝      ██║░╚═╝░██║██║░░██║██║██║░╚███║
    ╚══════╝╚═╝░░╚══╝╚═════╝░      ╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═╝╚═╝░░╚══╝*/
/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/