/*
ID: kondasu1
LANG: C++
TASK: numtri
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bits/stdc++.h> 
using namespace std;
#define MAX_R 1005

int R;

int tri[MAX_R][MAX_R];

int dp[MAX_R][MAX_R];

int max(int a, int b)
{
  return a > b ? a : b;
}

int solve(int i, int j, int end){
	if(dp[i][j] != -1)
  	{
    	return dp[i][j];
  	}
  	else if(i <= end)
  	{
    	return dp[i][j] = tri[i][j] + max(solve(i+1,j,end), solve(i+1,j+1,end));
  	}
  	else
  	{
    	return 0;
  	}
}

int main(void){

	ifstream fin("numtri.in");
	
	fin >> R;

	memset(dp, -1, sizeof dp);

	for(int i = 1; i <= R; i++){
		for(int j = 1; j <= i; j++){
			int num;
			fin >> num;
			tri[i][j] = num;
		}
	}

	ofstream fout("numtri.out");

	fout << solve(1, 1, R) << "\n"; 

}