// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
//  Modify     [2023/9/12 Ming-Bang Fan]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>
#include <random> //for real random
#define ll long long 
// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // cout << "Original data: ";
    // for (int num : data) {
    //     cout << num << " ";
    //     cout << "hahahahahaha"<< " ";
    // }
    // cout << endl;
    for (int i = 1; i < data.size(); ++i) {
        int key = data[i];
        int j = i - 1;
        while (j >= 0 && data[j] > key) {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = key;
    }

}

// Quick sort method
void SortTool::QuickSort(vector<int>& data, int f){
    QuickSortSubVector(data, 0, data.size() - 1, f);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high, const int flag) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    if(low<high){
        int priv_index;
        if(flag == 0){
            priv_index = Partition(data,low,high);
        }
        else{
            priv_index = RandomizedPartition(data,low,high);
        }
        QuickSortSubVector(data,low,priv_index-1,flag);
        QuickSortSubVector(data,priv_index+1,high,flag);
    }
}
    

int SortTool::RandomizedPartition(vector<int>& data, int low, int high){
    // Function : RQS's Partition the vector 
    // TODO : Please complete the function
    std::random_device rd;  // 用于获取真随机数
    std::mt19937 gen(rd()); // 使用 Mersenne Twister 19937 生成器
    std::uniform_int_distribution<> dis(low, high); // 均匀分布 low~high it is cloth regin 
    int random_num = dis(gen);
    
    //print low:0 random~ :740 high:999 
    // std::cout<<"low:"<<low;
    // std::cout<<"   random~ :"<<random_num;
    // std::cout<<"  high:"<<high<<std::endl;
    //print low:0 random~ :31 high:902 

    swap(data[random_num],data[high]);
    return Partition(data,low,high);
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    int priot = data[high]; //last one for mark
    int i = low-1; //indexfor change -1 for later +1

    for (int j = low; j<=high-1; j++){ //j from begin to one before priot
        //swap little one forward
        if (data[j]<=priot){
            i++ ;// insert place +1
            std::swap(data[i],data[j]);
        }
    }

    std::swap(data[i+1],data[high]); //insert privot back
    return i+1 ; //return privot index +1
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
}
