#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
void find_mps(const vector<int> &chordIndex, vector<vector<int>> &M, vector<vector<bool>> &S, int total_n_points);
void show_ans(int i, int j, const vector<vector<bool>> &S, vector<int> &the_ans, const vector<int> &chordIndex);



int main(int argc, char **argv){

    // open the input file
    fstream fin;
    fin.open(argv[1], fstream::in);
    ///////////////////////////輸入input 有sort的/////////////////////////////////////
    char buffer[290000];
    fin >> buffer;

    int total_n_points = atoi(buffer);
    //處存點點連線的pair
    vector<pair<int, int>> chords; 
    // // 印出總數
    // cout << total_n_points << endl;
    //依次輸入記錄弦(用pair存)
	for(int n = 0; n < total_n_points/2; n++){ 
        // fin >> buffer;
		// chords[n].first = atoi(buffer);
		// fin >> buffer;
		// chords[n].second = atoi(buffer);
		fin >> buffer;
		int a = atoi(buffer);
		fin >> buffer;
		int b = atoi(buffer);
        // 確保是由小到大
        if (a > b) swap(a, b);
        chords.push_back(make_pair(a, b));
        // Sort the chords by their starting point
        sort(chords.begin(), chords.end());
	}
    //印出檢查
	// for(int n = 0; n < total_n_points/2; n++){
	// 	cout << chords[n].first << " " << chords[n].second<< endl;
	// }
    /////////////////////////// 輸入input /////////////////////////////////////

    /////////////////////////// 做DP /////////////////////////////////////
    // 動態規劃數組
    vector<vector<int>> M(total_n_points, vector<int>(total_n_points, 0));  // nxn 表格處存解國 一開始都是0
    // 回溯標記數組
    vector<vector<bool>> S(total_n_points, vector<bool>(total_n_points, false));
    // 結果組數組
    vector<int> the_ans(total_n_points, -1);
    // 先把樹對 一一對應彼此
    vector<int> chordIndex(total_n_points, -1);
    for (const auto &chord : chords) {
        chordIndex[chord.first] = chord.second;
        chordIndex[chord.second] = chord.first;
    }
    find_mps(chordIndex, M, S, total_n_points);
    show_ans(0,total_n_points-1,S,the_ans,chordIndex);      
    //output
    fstream out;
    out.open(argv[2], ios::out);
    out<<M[0][total_n_points-1]<<endl;
    for(int i=0; i<total_n_points; ++i){
        if(the_ans[i]!=-1){
            out<<i<<" "<<the_ans[i]<<endl;
        }
    }

    
}

void find_mps(const vector<int> &chordIndex, vector<vector<int>> &M, vector<vector<bool>> &S, int total_n_points) {
 {
    for(int j=0; j<total_n_points; ++j){
        int k = chordIndex[j];
        for(int i=0; i<j; ++i){
            if(k!=0){ 
                if(i<=k&&k<j&&((M[i][k-1]+1+M[k+1][j-1])>M[i][j-1])){
                    M[i][j]=M[i][k-1]+1+M[k+1][j-1];
                    S[i][j]=true; 
                }
                else{
                    M[i][j]=M[i][j-1];
                    S[i][j]=false;
                }
            }
            //k==0
            else{ 
                if(i<=k&&k<j&&((M[k+1][j-1]+1)>M[i][j-1])){
                    M[i][j]=M[k+1][j-1]+1;
                    S[i][j]=true;
                }
                else{
                    M[i][j]=M[i][j-1];
                    S[i][j]=false;
                }
            }
        }
    }
}
}
void show_ans(int i, int j, const vector<vector<bool>> &S, vector<int> &the_ans, const vector<int> &chordIndex) {
    if(i<j){
        if(S[i][j]==true){
            the_ans[chordIndex[j]]=j;
            show_ans(i,chordIndex[j]-1,S,the_ans,chordIndex);
            show_ans(chordIndex[j]+1,j,S,the_ans,chordIndex);
        }
        else{
            show_ans(i,j-1,S,the_ans,chordIndex);
        }
    } 
}
