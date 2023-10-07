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
    if(low<high){
        int middle1 = (low+high)/2;
        int middle2 = middle1+1;
        MergeSortSubVector(data,low,middle1);
        MergeSortSubVector(data,middle2,high);
        Merge(data,low,middle1,middle2,high);
    }  
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    //temp_size
    int L_size = middle1-low+1;
    int R_size = high-middle2+1;
    //creat temp
    vector<int> L_temp(L_size+1); // last one is inf
    vector<int> R_temp(R_size+1); // last one is inf
    //copy to temp
    for (int i=0;i<=L_size-1;i++){
        L_temp[i]=data[low+i]; //from low begain to middle1
    }
    for (int i=0;i<=R_size-1;i++){
        R_temp[i]=data[middle2+i]; //from middle2 begain to high
    }
    //set last element to infinity
    L_temp[L_size] = 9999999;
    R_temp[R_size] = 9999999;
    //merg~
    int L_i=0; //L index
    int R_i=0; //R index
    for (int data_i=low;data_i<=high;data_i++){ //data index from low to high
        if(L_temp[L_i]<=R_temp[R_i]){
            data[data_i]=L_temp[L_i];
            L_i++;
        }
        else{
            data[data_i]=R_temp[R_i];
            R_i++;
        }
    }
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
    int left_index = 2*root+1;
    int right_index = 2*root+2;
    int largest_index = root;
    // if left is bigger
    if (left_index<=heapSize-1 && data[left_index]>data[largest_index]){
        largest_index = left_index;
    }
    // if right is even biger
    if (right_index<=heapSize-1 && data[right_index]>data[largest_index]){
        largest_index = right_index;
    }
    //if left or right any of them biger than root
    if(largest_index != root){
        swap(data[root],data[largest_index]);
        MaxHeapify(data,largest_index);
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for(int root_i = (heapSize/2)-1; root_i>=0; root_i--){ // root_index from size/2 down to 0
        MaxHeapify(data,root_i);
    }
}
