/*
ID: kondasu1
LANG: C++
TASK: ariprog
*/

#include <iostream>
#include <fstream>
#include <list> 
#include <iterator>
#include <set>
#include <cmath>
#include <utility>  
#include <experimental/iterator>
using namespace std;

int N, M;
bool check(int a, int b, bool bisquares[]){
	for(int n = 0; n < N; ++n){
		if(!bisquares[a + n * b]){
			return false;
		}
	}
	return true;
}

int main(void){
	ifstream fin("ariprog.in");
	
	fin >> N;
	fin >> M;
	
	fin.close();

	bool bisquares[M*M*2+1] = {false};
	for(int i = 0; i <= M; ++i){
		for(int j = i; j <= M; ++j){
			bisquares[(i * i + j * j)] = true;
		}
	}

	ofstream fout("ariprog.out");

	list<int> bisquaresList;
	int a = 0;
	while(a <= M*M*2){
		if(bisquares[a]){
			bisquaresList.push_back(a);
		}
		a += 1;
	}

	int num_sol = 0;
	int b = 1;
	while((N - 1) * b <= M*M*2){
		for(int a : bisquaresList){
			if(a + (N - 1) * b <= M*M*2 && check(a, b, bisquares)){
				fout << a << " " << b << "\n";
				num_sol += 1;
			}
		}
		b += 1;
	}
	if(num_sol == 0){
		fout << "NONE\n";
	}
	
	fout.close();
	return 0;
}