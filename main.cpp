//
// Created by Manju Muralidharan on 10/19/25.
// Modified by Bassam Siagian, finished on 11/3/2025
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        // Makes sure 'A' and 'a' are the same symbol
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only alphabetical characters, ignore the spaces, punctuation, etc.
        // Enhances trhe encoding... I think
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nodeCount = 0;
    for (char ch = 'a'; ch <= 'z'; ch++) {
        int index = ch - 'a';
        if (freq[index] > 0) {
            charArr[nodeCount] = ch; // Store actual character
            weightArr[nodeCount] = freq[index]; // Store frequency count
            leftArr[nodeCount] = -1; // Leaf nodes have no left children
            rightArr[nodeCount] = -1; // Leaf nodes have no right children

            nodeCount++; // Move to next slot
        }
    }
    cout << "Created " << nodeCount << " leaf nodes.\n";
    return nodeCount; // return the starting index for new internal nodes
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {
    // TODO:
    // 1. Create a MinHeap object.
    // 2. Push all leaf node indices into the heap.
    // 3. While the heap size is greater than 1:
    //    - Pop two smallest nodes
    //    - Create a new parent node with combined weight
    //    - Set left/right pointers
    //    - Push new parent index back into the heap
    // 4. Return the index of the last remaining node (root)

    MinHeap heap; // 1.
    for (int i = 0; i < nextFree; i++) { // 2.
        heap.push(i, weightArr);
    }

    // Build by combining two least frequent nodes
    // Only until one node remains (root)
    while (heap.size > 1) { // 3.
        // smallest nodes popped, from smallest frequencies
        int left = heap.pop(weightArr);
        int right = heap.pop(weightArr);

        // New internal node made (frequency + child pointers)
        weightArr[nextFree] = weightArr[left] + weightArr[right];
        leftArr[nextFree] = left; // set left child pointer
        rightArr[nextFree] = right; // set right child pointer
        charArr[nextFree] = '\0'; // Internal nodes don't store characters

        //Add new combined node back to heap
        heap.push(nextFree, weightArr);
        nextFree++;
    }
    return heap.pop(weightArr); // placeholder
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    // TODO:
    // Use stack<pair<int, string>> to simulate DFS traversal.
    // Left edge adds '0', right edge adds '1'.
    // Record code when a leaf node is reached.

    // Use stack for iterative
    // Each stack element tracks a node
    stack<pair<int, string>> stk;
    stk.push({root, ""}); // start with empty binary code

    while (!stk.empty()) {
        auto [node, code] = stk.top();
        stk.pop();

        if (charArr[node] != '\0') {
            // leaf node reached, store
            // more frequent characters get shorter due to structure
            int charIndex = charArr[node] - 'a';
            codes[charIndex] = code;
        } else {
            // it's internal node, continue traversal
            // left child traversal adds '0' to current
            if (leftArr[node] != -1) {
                stk.push({leftArr[node], code + "0"});
            }

            if (rightArr[node] != -1) {
                stk.push({rightArr[node], code + "1"});
            }
        }
    }
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    // display the code table
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    // display the encoded binary message by converting to its code
    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        // input character to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // output binary code for each alphabetical char.
        // non-alphabetical skipped
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}