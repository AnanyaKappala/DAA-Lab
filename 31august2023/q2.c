/* Huffman coding assigns variable length codewords to fixed length input
characters based on their frequencies or probabilities of occurrence. Given a set of characters
along with their frequency of occurrences, write a c program to construct a Huffman tree.
Note#

• Declare a structure SYMBOL having members alphabet and frequency. Create a Min-
Priority Queue, keyed on frequency attributes.

• Create an array of structures where size=number of alphabets.
Input:
Enter the number of distinct alphabets: 6
Enter the alphabets: a b c d e f
Enter its frequencies: 45 13 12 16 9 5
Output:
In-order traversal of the tree (Huffman): a c b f e d*/
#include <stdio.h>
#include <stdlib.h>

// Structure for a symbol
struct SYMBOL {
    char alphabet;
    int frequency;
};

// Structure for a node in the Huffman tree
struct Node {
    struct SYMBOL symbol;
    struct Node *left, *right;
};

// Structure for a Min-Priority Queue
struct MinPriorityQueue {
    int size;
    struct Node **array;
};

// Function to create a new node
struct Node* createNode(struct SYMBOL symbol) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->symbol = symbol;
    node->left = node->right = NULL;
    return node;
}

// Function to create a Min-Priority Queue
struct MinPriorityQueue* createQueue(int capacity) {
    struct MinPriorityQueue* queue = (struct MinPriorityQueue*)malloc(sizeof(struct MinPriorityQueue));
    queue->size = 0;
    queue->array = (struct Node**)malloc(capacity * sizeof(struct Node*));
    return queue;
}

// Function to swap two nodes
void swapNodes(struct Node** a, struct Node** b) {
    struct Node* temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify function for Min-Heap
void minHeapify(struct MinPriorityQueue* queue, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    
    if (left < queue->size && queue->array[left]->symbol.frequency < queue->array[smallest]->symbol.frequency)
        smallest = left;
    
    if (right < queue->size && queue->array[right]->symbol.frequency < queue->array[smallest]->symbol.frequency)
        smallest = right;
    
    if (smallest != index) {
        swapNodes(&queue->array[index], &queue->array[smallest]);
        minHeapify(queue, smallest);
    }
}

// Function to build a Min-Priority Queue
struct MinPriorityQueue* buildMinPriorityQueue(struct SYMBOL symbols[], int numSymbols) {
    struct MinPriorityQueue* queue = createQueue(numSymbols);
    
    for (int i = 0; i < numSymbols; ++i)
        queue->array[i] = createNode(symbols[i]);
    
    queue->size = numSymbols;
    
    for (int i = numSymbols / 2 - 1; i >= 0; --i)
        minHeapify(queue, i);
    
    return queue;
}

// Function to extract the minimum node from Min-Priority Queue
struct Node* extractMin(struct MinPriorityQueue* queue) {
    struct Node* temp = queue->array[0];
    queue->array[0] = queue->array[queue->size - 1];
    --queue->size;
    minHeapify(queue, 0);
    return temp;
}

// Function to insert a new node into Min-Priority Queue
void insertNode(struct MinPriorityQueue* queue, struct Node* node) {
    ++queue->size;
    int i = queue->size - 1;
    while (i && node->symbol.frequency < queue->array[(i - 1) / 2]->symbol.frequency) {
        queue->array[i] = queue->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    queue->array[i] = node;
}

// Function to build Huffman tree
struct Node* buildHuffmanTree(struct SYMBOL symbols[], int numSymbols) {
    struct Node *left, *right, *top;
    struct MinPriorityQueue* queue = buildMinPriorityQueue(symbols, numSymbols);
    
    while (queue->size > 1) {
        left = extractMin(queue);
        right = extractMin(queue);
        
        top = createNode((struct SYMBOL){'$', left->symbol.frequency + right->symbol.frequency});
        top->left = left;
        top->right = right;
        
        insertNode(queue, top);
    }
    
    return extractMin(queue);
}

// Function to perform in-order traversal of Huffman tree
void inorderTraversal(struct Node* root) {
    if (root) {
        inorderTraversal(root->left);
        printf("%c ", root->symbol.alphabet);
        inorderTraversal(root->right);
    }
}

int main() {
    int numSymbols;
    printf("Enter the number of distinct alphabets: ");
    scanf("%d", &numSymbols);
    
    struct SYMBOL symbols[numSymbols];
    
    printf("Enter the alphabets: ");
    for (int i = 0; i < numSymbols; ++i)
        scanf(" %c", &symbols[i].alphabet);
    
    printf("Enter its frequencies: ");
    for (int i = 0; i < numSymbols; ++i)
        scanf("%d", &symbols[i].frequency);
    
    struct Node* root = buildHuffmanTree(symbols, numSymbols);
    
    printf("Output:\nIn-order traversal of the tree (Huffman): ");
    inorderTraversal(root);
    
    return 0;
}
