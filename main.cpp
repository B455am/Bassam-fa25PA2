//
// Created by Manju Muralidharan on 10/19/25.
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
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
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
            charArr[nodeCount] = ch;
            weightArr[nodeCount] = freq[index];
            leftArr[nodeCount] = -1;
            rightArr[nodeCount] = -1;

            nodeCount++;
        }
    }
    cout << "Created " << nodeCount << " leaf nodes.\n";
    return nodeCount;
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


    while (heap.size > 1) { // 3.
        // smallest nodes popped
        int left = heap.pop(weightArr);
        int right = heap.pop(weightArr);

        // New parent node created
        weightArr[nextFree] = weightArr[left] + weightArr[right];
        leftArr[nextFree] = left;
        rightArr[nextFree] = right;
        charArr[nextFree] = '\0';

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

    stack<pair<int, string>> stk;
    stk.push({root, ""});

    while (!stk.empty()) {
        auto [node, code] = stk.top();
        stk.pop();

        if (charArr[node] != '\0') {
            int charIndex = charArr[node] - 'a';
            codes[charIndex] = code;
        } else {
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
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}