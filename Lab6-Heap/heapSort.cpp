// heapSort.cpp file
// Description: This file implements is to implement heap sort algorithm.
// Author: Shixi Chen(Ethan)
// Creation date: Feb 28, 2020

#include "iostream"

using namespace std;

void heapify(int tree[], int size, int i);
inline void printList(int list[], int size);

/**
 * Modify the input array to form max heap
 * @param tree, array
 * @param n, size of the array
 */
void buildMaxHeap(int tree[], int n){
    int lastNode = n - 1;
    int parent = (lastNode - 1) / 2;
    for (int i = parent; i >= 0; --i) {
        heapify(tree, n, i);
    }
}

/**
 * Max heap sorting algorithm
 * @param tree, array
 * @param size, size of the array
 */
void heapSort(int tree[], int size){
    //Build a max heap
    buildMaxHeap(tree, size);
    for (int i = size - 1; i >= 0; --i) {
        swap(tree[i], tree[0]);
        //Maintain Heap feature
        heapify(tree, i, 0);
    }
}

int main(){
    //Test case 1
    int list1[] = {3, -1, 9, 11, 2, 66, 13, 66, -4, -13, 1, 12};
    int size1 = sizeof(list1) / sizeof(int);
    cout << "Before sorted: ";
    printList(list1, size1);
    heapSort(list1, size1);
    cout << "After sorted: ";
    printList(list1, size1);
    cout << endl;

    //Test case 2:
    int list2[] = {6, 9, -5, 0, -11, 22, -99, 03, 11, 1, 2, 3, -22, -1};
    int size2 = sizeof(list2) / sizeof(int);
    cout << "Before sorted: ";
    printList(list2, size2);
    heapSort(list2, size2);
    cout << "After sorted: ";
    printList(list2, size2);
    cout << endl;

    //Test case 3
    int list3[] = {7, 1, -8, -168, 11, 22, 33, -8, -1, 9, 44, 23, 45, 67, 31, 12};
    int size3 = sizeof(list3) / sizeof(int);
    cout << "Before sorted: ";
    printList(list3, size3);
    heapSort(list3, size3);
    cout << "After Sorted: ";
    printList(list3, size3);

    return 0;
}

/**
 * Modify the input array to construct a max heap. (Top-down)
 * @param tree, array
 * @param size, size of the array
 * @param i, node index
 */
void heapify(int tree[], int size, int i){
    if(i >= size) return;
    int leftChild = 2 * i + 1;
    int rightChild = leftChild + 1;
    int max = i;
    //Determine the max between two child and parent
    if(tree[leftChild] > tree[max] && leftChild < size){
        max = leftChild;
    }
    if(tree[rightChild] > tree[max] && rightChild < size)
        max = rightChild;
    //If child is greater than parent
    if(max != i){
        swap(tree[max], tree[i]);
        //Heapify the tree recursively(Top-Down)
        heapify(tree, size, max);
    }

}

/**
 * Print the array in a good-looking way
 * @param list, array
 * @param size, size of the array
 */
inline void printList(int list[], int size){
    cout << "[";
    for (int i = 0; i < size; ++i) {
        if(i == size - 1) cout << list[i];
        else cout << list[i] << ", ";
    }
    cout << "]" << endl;

}
