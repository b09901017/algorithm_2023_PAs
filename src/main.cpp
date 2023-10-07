// **************************************************************************
//  File       [main.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The main program of 2019 fall Algorithm PA1]
//  Modify     [2020/9/15 Mu-Ting Wu]
//  Modify     [2023/9/12 Ming-Bang Fan]
//  ./NTU_sort -IS 1000.case2.in output
//  in PA1 ~ type make and type ./bin/NTU_sort -IS inputs/1000.case2.in output
//  ./bin/NTU_sort -IS inputs/1000.case2.in outputs/1000.case2.out
// **************************************************************************

#include <cstring>
#include <iostream>
#include <fstream>
#include "../lib/tm_usage.h"
#include "sort_tool.h"
#define ll long long 

using namespace std;

void help_message() {
    cout << "usage: NTU_sort -[IS|MS|QS|HS] <input_file> <output_file>" << endl;
    cout << "options:" << endl;
    cout << "   IS - Insersion Sort" << endl;
    cout << "   MS - Merge Sort" << endl;
    cout << "   QS - Quick Sort" << endl;
    cout << "   RQS - Randomized Quick Sort" << endl;
    cout << "   HS - Heap Sort" << endl;
}

int main(int argc, char* argv[])
{
    if(argc != 4) {
       help_message();
       return 0;
    }
    CommonNs::TmUsage tmusg;
    CommonNs::TmStat stat;

    //////////// read the input file /////////////
    
    char buffer[200];
    fstream fin(argv[2]);
///// for~~debug
// if (!fin) {
//     cerr << "Error: Unable to open input file." << endl;
//     return 1;
// }

// // 以下代码用于检查数据加载情况
// int lineCount = 0;


// while (fin.getline(buffer, 200)) {
//     lineCount++;
// }

// cout << "Number of lines read from input file: " << lineCount << endl;
// ///// for~~debug

    fstream fout;
    fout.open(argv[3],ios::out);
    fin.getline(buffer,200);
    fin.getline(buffer,200);
    int junk,num;
    vector<int> data;
    while (fin >> junk >> num)
        data.push_back(num); // data[0] will be the first data. 
        cout<<num<<endl;                     // data[1] will be the second data and so on.

////// for debug insure output got the num from input
// ifstream checkFile(argv[3]);
// if (checkFile) {
//     cout << "Output file exists and is not empty." << endl;
// } else {
//     cout << "Output file does not exist or is empty." << endl;
// }
//////for debug insure output got the num from input

    //////////// the sorting part ////////////////
    tmusg.periodStart();
    SortTool NTUSortTool; 

    if(!strcmp(argv[1],"-QS")) {
        NTUSortTool.QuickSort(data,0);
    }
    else if(!strcmp(argv[1],"-RQS")) {
        NTUSortTool.QuickSort(data,1);
    }
    else if(!strcmp(argv[1],"-IS")) {
        NTUSortTool.InsertionSort(data);
    }
    else if(!strcmp(argv[1],"-MS")) {
        NTUSortTool.MergeSort(data);
    }
    else if(!strcmp(argv[1],"-HS")) {
        NTUSortTool.HeapSort(data);
    }
    else {
        help_message();
        return 0;
    }
    tmusg.getPeriodUsage(stat);
    cout <<"The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << endl;
    cout <<"memory: " << stat.vmPeak << "KB" << endl; // print peak memory
    //////////// write the output file ///////////
    fout << "# " << data.size() << " data points" <<endl;
    fout << "# index number" << endl;
    for (int i = 0; i < data.size(); i++)
        fout << i << " " <<data[i] << endl;
    fin.close();
    fout.close();
    return 0;
}
