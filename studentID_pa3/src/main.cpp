#include <cstring>
#include <iostream>
#include <fstream>
#include "../lib/tm_usage.h"
#include <vector>
#include <algorithm>
#include <map>
#include <array>
#include <list>
using namespace std;

// ************** define input variable ********************
char type ;
int n_numof_vertax;
int m_numof_edge;
struct edge
{
    int v_start;
    int v_end;
    int weight;
};
vector <edge> edges;
//output varible
int removed_weight_sum = 0;
vector <edge> removed_edges;
// ************** define input variable ********************


// ************** for sort ~~ ********************
bool compareByWeight(const edge& a, const edge& b){
        return a.weight > b.weight; // 按權重降序排序
    }
// ************** for sort ~~ ********************


// ************** use kru alg to find maximum spand tree (edges without chosen will be remove) ********************

// ************** Union By Rank O(m) ********************
vector<int> Panents ; vector<int> Ranks;
void Make_SET(){ //initialize
    Panents.resize(n_numof_vertax); Ranks.resize(n_numof_vertax); //contro size
    for (int i=0;i<n_numof_vertax;i++){Panents[i]=i ; Ranks[i]=0;}
}
int Find_SET(int v){ // if x!=x.p => x.p=FindSET(x.p) return x.p
    if(v!=Panents[v]) 
        Panents[v] = Find_SET(Panents[v]);
    return Panents[v];
}
void LINK(int group1, int group2){
    if(Ranks[group1] > Ranks[group2]) // small group link to the big one
        Panents[group2] = group1;
    else{
        Panents[group1] = group2;     // otherwise 1 link to 2
        if (Ranks[group1] == Ranks[group2]) //moreover if 1==2 expect link 1 to 2 also 2.rank+1 
            Ranks[group2]++;
    }   
}
void UNION(int group1, int group2){  // Finial~ UNION function
    LINK(Find_SET(group1), Find_SET(group2));
}
// ************** Union By Rank O(m) ********************

void use_Kruskal_u_maxST_to_print_remove (vector <edge> &edges, int n_numof_vertax, int m_numof_edge){

    // ************** sort the input ********************
    // 使用 Lambda 表達式進行排序
    std::sort(edges.begin(), edges.end(), [](const edge& a, const edge& b) {
        return a.weight > b.weight;
    });
    // check the result
    // for(const auto& edge : edges) {
    //     std::cout << "Edge from " << edge.v_start << " to " << edge.v_end << " with weight " << edge.weight << std::endl;
    // }
    // ************** sort the input ********************

    // ************** setting root for each ( use makeSET just fine ) ********************
    // vector<int> root(n_numof_vertax);  // V是頂點的數量
    // for(int i = 0; i < n_numof_vertax; ++i) {
    //     root[i] = i;  // 初始時，每個頂點都是自己的根
    // }
    Make_SET();
    // ************** setting root for each ( use makeSET just fine ) ********************

    // ************** greddly go though v-1個 vertex (without chossen int mst than must remove?) ********************
    for(const auto& edge : edges) { //from weight big to low

        int root_start = Find_SET(edge.v_start);
        int root_end = Find_SET(edge.v_end);

        if (root_start!=root_end){ // if not in the same group than union
            UNION(root_start,root_end);// union
        }
        else{ // in the same group than there is a cycle than get it out print
            removed_edges.push_back({edge.v_start,edge.v_end,edge.weight});
            removed_weight_sum += edge.weight;
        }
    }
    // ************** greddly go though v-1個 vertex (without chossen int mst than must remove?) ********************

}
// ************** use kru alg to find maximum spand tree (edges without chosen will be remove) ********************



// ************** help message ********************
void help_message() {
    cout << "./bin/cb inputs/public_case_n.in outputs/case_n for run " << endl;
    cout << "checker/pa3_checker inputs/public_case_n.in outputs/case_n for check" << endl;
}
// ************** help message ********************


// ************** ! ! ! main ! ! ! ********************
int main(int argc, char* argv[])
{
    if(argc != 3) {
       help_message();
       return 0;
    }
    CommonNs::TmUsage tmusg;
    CommonNs::TmStat stat;
    tmusg.periodStart();


    // ************** read the input ********************
    fstream fin(argv[1]);
    fin>>type;
    fin>>n_numof_vertax;
    fin>>m_numof_edge;
    int v_s, v_e, w ; 
    while (fin >> v_s >> v_e >> w){
        edges.push_back({v_s,v_e,w}); 
    }
    // ************** read the input ********************

    // ************** check the read ********************
    // cout << "Type: " << type << endl;
    // cout << "Number of vertices: " << n_numof_vertax << endl;
    // cout << "Number of edges: " << m_numof_edge << endl;
    // for(const auto& edge : edges) {
    // cout << "Edge from " << edge.v_start << " to " << edge.v_end << " with weight " << edge.weight << endl;
    // }
    // ************** check the read ********************
    

    use_Kruskal_u_maxST_to_print_remove (edges, n_numof_vertax, m_numof_edge);
    cout << "Remove_Weight_Sum " << removed_weight_sum << endl;   


    // ************** output~~~~~~ ********************
    fstream fout;
    fout.open(argv[2],ios::out);
    fout << removed_weight_sum << endl;
    for (int i = 0; i < removed_edges.size(); i++)
    {
        fout << removed_edges[i].v_start << " " << removed_edges[i].v_end << " " << removed_edges[i].weight << endl;
    }
    // ************** output~~~~~~ ********************

    // ************** print runing time and space ********************
    tmusg.getPeriodUsage(stat);
    cout <<"The total CPU time: " << (stat.uTime + stat.sTime) / 60000000.0 << " min" << endl;
    cout <<"memory: " << stat.vmPeak/(1024.0*1024.0) << " GB" << endl; // print peak memory
    // ************** print runing time and space ********************

}


