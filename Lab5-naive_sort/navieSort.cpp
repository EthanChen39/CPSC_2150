#include "iostream"
#include "climits"
#include <cmath>

using namespace std;

void naiveSort(int data[], int size);

int main() {
    //Test case 1
    int nums[] = {8, 20, 0, 7, 2, 9, 9, 11, 12};
    int size = sizeof(nums)/ sizeof(int);
    cout << "Before sorted: ";
    for (int i = 0; i < size; ++i) {
        cout << nums[i] <<  " ";
    }cout << endl;
    naiveSort(nums, size);
    cout << "After sorted: ";
    for (int i = 0; i < size; ++i) {
        cout << nums[i] << " ";
    }
    cout << endl << endl;
    //Test case 2
    int nums2[] = {-1, -5, -6, 22, 77, 2, 99, -34, 10, 7};
    int size2 = sizeof(nums2)/ sizeof(int);
    cout << "Before sorted: ";
    for (int i = 0; i < size2; ++i) {
        cout << nums2[i] <<  " ";
    }cout << endl;
    naiveSort(nums2, size2);
    cout << "After sorted: ";
    for (int i = 0; i < size2; ++i) {
        cout << nums2[i] << " ";
    }cout << endl;


}

void naiveSort(int data[], int size){
    //Initialize all the variables
    int h = (int)(ceil(log2(size)) + 1);//height of the tree
    int numberOfLeaves = pow(2, h-1);
    int k;
    int temp = numberOfLeaves;
    int** binaryTree = new int*[h];


    //Construct a tree structure by using dynamic array
    for (int i = 0; i < h; ++i) {
        binaryTree[i] = new int[temp];
        temp /= 2;
    }
    //Insert all the element from data[] to the leave of the tree
    for (k = 0; k < size; ++k) {
        binaryTree[0][k] = data[k];
    }
    //Assign the rest of the empty spots with INT_MAX
    while(k < numberOfLeaves)
        binaryTree[0][k++] = INT_MAX;


    for (int m = 0; m < size; ++m) {
        //Populate the tree and find min
        int temp1 = numberOfLeaves;
        for (int height = 0; height < h - 1; ++height) {
            int parentIndex = 0;
            for (int childIndex = 0; childIndex < temp1; childIndex += 2, parentIndex++) {
                if (binaryTree[height][childIndex] < binaryTree[height][childIndex + 1]) {
                    binaryTree[height + 1][parentIndex] = binaryTree[height][childIndex];
                } else {
                    binaryTree[height + 1][parentIndex] = binaryTree[height][childIndex + 1];
                }
            }
            temp1 /= 2;
        }
        int root = binaryTree[h-1][0];
        //Replace the min value that found above with INT_MAX
        //Linear search
        for (int i = 0; i < numberOfLeaves; ++i) {
            if(binaryTree[0][i] == root){
                binaryTree[0][i] = INT_MAX;
                break;
            }
        }


        //assign the root to the original data
        data[m] = root;
    }

    //Delete the tree - free the memory
    delete [] binaryTree;


}