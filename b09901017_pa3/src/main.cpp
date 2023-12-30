#include <cstring>
#include <iostream>
#include <fstream>
#include "../lib/tm_usage.h"
#include <vector>
#include <algorithm>
#include <map>
#include <array>
#include <list>
#include <queue>
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
vector<bool> visited;
bool loop_back_to_this_root = false;
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
void Make_SET(int n_numof_vertax){ //initialize
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
        //cout<<group2<<"!!!!!"<<endl;
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
    //check the result
    // for(const auto& edge : edges) {
    //     std::cout << "Edge from " << edge.v_start << " to " << edge.v_end << " with weight " << edge.weight << std::endl;
    // }
    // ************** sort the input ********************

    // ************** setting root for each ( use makeSET just fine ) ********************
    // vector<int> root(n_numof_vertax);  // V是頂點的數量
    // for(int i = 0; i < n_numof_vertax; ++i) {
    //     root[i] = i;  // 初始時，每個頂點都是自己的根
    // }
    Make_SET(n_numof_vertax);
    // ************** setting root for each ( use makeSET just fine ) ********************

    // ************** greddly go though v-1個 vertex (without chossen int mst than must remove?) ********************
    for(const auto& edge : edges) { //from weight big to low

        int root_start = Find_SET(edge.v_start);
        int root_end = Find_SET(edge.v_end);
        //cout<<edge.v_start <<" belong to "<<root_start<<" , "<<edge.v_end << " belong to "<<root_end<<endl;
        if (root_start!=root_end){ // if not in the same group than union
            UNION(edge.v_start,edge.v_end);// union
            //cout<<"connect "<<edge.v_start<<" to "<<edge.v_end<<endl;
        }
        else{ // in the same group than there is a cycle than get it out print
            removed_edges.push_back({edge.v_start,edge.v_end,edge.weight});
            removed_weight_sum += edge.weight;
        }

    }
    // ************** greddly go though v-1個 vertex (without chossen int mst than must remove?) ********************

}
// ************** use kru alg to find maximum spand tree (edges without chosen will be remove) ********************


// ************** 1. remove edge one by one (greddyly) 2. check if that is OK ? 3. if ok than store in out put if not than put it back********************
// void DFS_visit(int node, vector<int> adj[], int root){
//     visited[node] = true;

//     for(int v : adj[node]){
//         // debug
//         // cout<<"vertex : " <<node<<"'s nigber are : ";
//         // for(int v : adj[node]){
//         //     cout<<v<<", ";
//         // }
//         // cout<<endl;
//         // debug
        
//         if(!visited[v]){ // if this nigber is not vised 
//             //cout<<"visit : "<< v <<endl;
//             DFS_visit(v, adj, root);
//         }
//         if (v==root) {
//                 loop_back_to_this_root = true;
//                 //cout<<"start being true ~~ "<<loop_back_to_this_root<<endl;

//                 return;
//             }
//     }
//     //cout<<"check point~~ "<<root<<endl;
// }

bool BFS(int s, int n, vector<int> adj[])
{
    bool visited[n]; //number of vertices,colored or not
    for (int i = 0; i < n; i++)
        visited[i] = false; //initialize
    queue<int> Q;
    visited[s] = true;
    Q.push(s);
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        for (int i = 0; i < adj[u].size(); i++)
        {
            if (visited[adj[u][i]])
            {
                return true;
            }
            else
            {
                visited[adj[u][i]] = true;
                Q.push(adj[u][i]);
            }
        }
    }
    return false;
}

    // only those who pass the u_remove function is possible for d_remove
void d_print_removed_edge_for_directed_graph(vector <edge> &edges, vector<int> adj[], int n_numof_vertax, int m_numof_edge){
    // use u_remove function to get posible canidate =>removed_edges
    use_Kruskal_u_maxST_to_print_remove(edges, n_numof_vertax, m_numof_edge);
    // for(const auto& edge : removed_edges) {
    // cout << "Remove Edge from " << edge.v_start << " to " << edge.v_end << " with weight " << edge.weight << endl;
    // } 



    //use BFS to check if this edge will cause a loop (use this edge to loop back to itself(edge.v_start) not DFS has a loop)
     for (const auto& candidate_edge : removed_edges){
    //     //cout<<"candidate edge change "<<endl;
    //     //cout<<"if last edge loop back to it self"<<loop_back_to_this_root<<endl;
    //     //initialize visited
    //     visited.resize(n_numof_vertax);
    //     for (int i = 0; i < visited.size(); i++) {
    //         visited[i] = false;
    //     }
    //     //initialize visited

    //     // from edge.v_start start to DFS
    //     int root = candidate_edge.v_start;
    //     // if from edge.v_start start to DFS and loop_back_to_this_root than this edge remain in output
    //     loop_back_to_this_root = false;
    //     //cout<<"become  flase ~~ "<<loop_back_to_this_root<<endl;
    //     DFS_visit(root, adj, root);
    //     //cout<<"where you go in to if "<<loop_back_to_this_root<<endl;
    //     if(!loop_back_to_this_root ){ //this edge doesn't metter
    //         //cout<<"this edge doesnt metter from"<<candidate_edge.v_start<<"to"<<candidate_edge.v_end<<endl;
    //         //cout<<"!!!!!!!"<<candidate_edge.weight<<endl;
    //         //if(candidate_edge.weight>0){
    //             removed_weight_sum -= candidate_edge.weight;
    //             // remove this candidate edge from removed edge
    //             auto it = remove_if(removed_edges.begin(), removed_edges.end(), 
    //                                 [&candidate_edge](const edge& e) {
    //                                     return e.v_start == candidate_edge.v_start && e.v_end == candidate_edge.v_end;
    //                                 });
    //             removed_edges.erase(it, removed_edges.end());
    //         //} 
    //     }
    //     else{ // if loop back than have to remove it from adj list
    //         adj[candidate_edge.v_start].erase(remove(adj[candidate_edge.v_start].begin(), adj[candidate_edge.v_start].end(), candidate_edge.v_end), adj[candidate_edge.v_start].end());
    //     }


    // }

    //add adjacency list
        adj[candidate_edge.v_start].push_back(candidate_edge.v_end);
        //remained_edges.push_back(removed_edges[i]);
        //check if cycle exist
        if (BFS(candidate_edge.v_start, n_numof_vertax, adj) == true)
        //remove testing edges
        {
            //cout << "fuck" << endl;
            //捨棄那個edge
            // remained_edges.pop_back();
            //移除adjlist
            adj[candidate_edge.v_start].pop_back();
        }
        //keep testing edges
        else
        {
            removed_weight_sum -= candidate_edge.weight;
                // remove this candidate edge from removed edge
                auto it = remove_if(removed_edges.begin(), removed_edges.end(), 
                                    [&candidate_edge](const edge& e) {
                                        return e.v_start == candidate_edge.v_start && e.v_end == candidate_edge.v_end;
                                    });
                removed_edges.erase(it, removed_edges.end());
            //} 
        }
    }

}

// ************** 1. remove edge one by one (greddyly) 2. check if that is OK ? 3. if ok than store in out put if not than put it back********************



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
    // // 檢查文件是否成功打開
    // if (!fin) {
    //     std::cerr << "無法打開文件" << std::endl;
    //     return 1;
    // }

    // // 檢查文件是否為空
    // fin.seekg(0, std::ios::end);
    // if (fin.tellg() == 0) {
    //     std::cerr << "文件是空的" << std::endl;
    //     return 1;
    // }
    fin>>type;
    fin>>n_numof_vertax;
    fin>>m_numof_edge;
    vector <int> adj[n_numof_vertax];  // store nigbers 10/29
    int v_s, v_e, w ; 
    while (fin >> v_s >> v_e >> w){
        edges.push_back({v_s,v_e,w}); 
        adj[v_s].push_back(v_e); //v_end is the nigber of v_start 10/29
    }
    // ************** read the input ********************

    // ************** check the read ********************
    // cout << "Type: " << type << endl;
    // cout << "Number of vertices: " << n_numof_vertax << endl;
    // cout << "Number of edges: " << m_numof_edge << endl;
    // for(const auto& edge : edges) {
    // cout << "Edge from " << edge.v_start << " to " << edge.v_end << " with weight " << edge.weight << endl;
    // }
    // for (int i = 0; i < n_numof_vertax; ++i) { //check the adj list
    //     cout << "v" << (i+1) << " : ";
    //     for (size_t j = 0; j < adj[i].size(); ++j) {
    //         if (j > 0) cout << ",";
    //             cout << adj[i][j];
    //     }
    //     cout << endl;
    // }
    // ************** check the read ********************
    
    // ************** MAIN Function Depart "u" and "d" ********************
    if (type=='u'){
        use_Kruskal_u_maxST_to_print_remove (edges, n_numof_vertax, m_numof_edge);
    }
    else if(type=='d'){
        cout<<"using_d"<<endl;
        d_print_removed_edge_for_directed_graph(edges, adj, n_numof_vertax, m_numof_edge);
    }
    else{
        cout<< " Neither 'u' or 'd' "<<endl;
    }
    
    // ************** MAIN Function Depart "u" and "d" ********************


    //use_Kruskal_u_maxST_to_print_remove (edges, n_numof_vertax, m_numof_edge);
    //d_print_removed_edge_for_directed_graph(edges, adj, n_numof_vertax, m_numof_edge);
     


    // ************** output~~~~~~ ********************
    cout << "Remove_Weight_Sum " << removed_weight_sum << endl;  
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


