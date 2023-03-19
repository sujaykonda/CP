/*
ID: kondasu1
LANG: C++
TASK: milk3
*/

#include <iostream>
#include <fstream>
#include <set>
#include <string>
using namespace std;

int A, B, C;
bool allstates[21][21][21] = {false};
bool allsol[21];
void solve(int state[3]){
	// Check repeating state
	if(allstates[state[0]][state[1]][state[2]]){
		return;	
	}
	else{
		allstates[state[0]][state[1]][state[2]] = true;
		// Check if state is a solution
		if(state[0] == 0){
			allsol[state[2]] = true;
		}
		int size[3] = {A, B, C};
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				if(state[i] != 0 && i != j){
					int ogI = state[i];
					int ogJ = state[j];
					state[j] = state[i] + state[j];
					state[i] = state[j] - size[j];
					if(state[j] > size[j]){
						state[j] = size[j];
					} 
					if(state[i] < 0){
						state[i] = 0;
					}
					solve(state);
					state[i] = ogI;
					state[j] = ogJ;
				}
			}
		}
	}
}

int main(void){
	ifstream fin("milk3.in");
	fin >> A >> B >> C;

	int curr_state[3] = {0, 0, C};

	solve(curr_state);

	ofstream fout("milk3.out");

	string final_ans = "";

	for(int i = 0; i < 21; i++){
		if(allsol[i]){
			final_ans += to_string(i) + " ";
		}
	}
	final_ans.pop_back();
	fout << final_ans << "\n";
}