/*
ID: kondasu1
LANG: C++
TASK: castle
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <unordered_map>
#include <vector>
using namespace std;

int M;
int N;
int castle[50][50][4];
int rooms[50][50];

vector<int> sizes;

int num_rooms = 0;
int slr = 0;
int slr_r1w = 0;
int r1w_i;
int r1w_j;
char r1w_d;

void findroom(int i, int j)
{
	rooms[i][j] = num_rooms;
	if (sizes.size() <= num_rooms)
	{
		sizes.push_back(0);
	}
	sizes[num_rooms] += 1;
	bool last_room = true;
	if (castle[i][j][0] == 0 && castle[i][j - 1][2] == 0 && rooms[i][j - 1] == 0)
	{
		last_room = false;
		findroom(i, j - 1);
	}
	if (castle[i][j][1] == 0 && castle[i + 1][j][3] == 0 && rooms[i + 1][j] == 0)
	{
		last_room = false;
		findroom(i + 1, j);
	}
	if (castle[i][j][2] == 0 && castle[i][j + 1][0] == 0 && rooms[i][j + 1] == 0)
	{
		last_room = false;
		findroom(i, j + 1);
	}
	if (castle[i][j][3] == 0 && castle[i - 1][j][1] == 0 && rooms[i - 1][j] == 0)
	{
		last_room = false;
		findroom(i - 1, j);
	}
	if(last_room){
		num_rooms += 1;
	}
}

int main(void){
	ifstream fin("castle.in");

	fin >> M >> N;

	for(int i = 0; i < M; i++){
		for(int j = 0; j < N; j++){
			int n;
			fin >> n;
			for(int k = 8, l = 1; k >= 1; k /= 2, l++){
				if(n > k){
					castle[i][j][l] = 1;
					n -= k;
				} 
			}
		}
	}

	fin.close();

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (rooms[i][j] == 0)
			{
				findroom(i, j);
			}
		}
	}
	for (int i = 0; i < sizes.size(); i++){
		int new_size = sizes[i];
		if(new_size > slr){
			slr = new_size;
		}
	}
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (castle[i][j][0] == 1 && castle[i][j - 1][2] == 0 && rooms[i][j] != rooms[i][j - 1])
			{
				int new_size = sizes[rooms[i][j]] + sizes[rooms[i][j - 1]];
				if (new_size > slr_r1w)
				{
					slr_r1w = new_size;
					r1w_i = i;
					r1w_j = j;
					r1w_d = 'W';
				}
			}
			if (castle[i][j][1] == 1 && castle[i + 1][j][3] == 0 && rooms[i][j] != rooms[i + 1][j])
			{
				int new_size = sizes[rooms[i][j]] + sizes[rooms[i + 1][j]];
				if (new_size > slr_r1w)
				{
					slr_r1w = new_size;
					r1w_i = i;
					r1w_j = j;
					r1w_d = 'N';
				}
			}
			if (castle[i][j][2] == 1 && castle[i][j + 1][0] == 0 && rooms[i][j] != rooms[i][j + 1])
			{
				int new_size = sizes[rooms[i][j]] + sizes[rooms[i][j + 1]];
				if (new_size > slr_r1w)
				{
					slr_r1w = new_size;
					r1w_i = i;
					r1w_j = j;
					r1w_d = 'E';
				}
			}
			if (castle[i][j][3] == 1 && castle[i - 1][j][1] == 0 && rooms[i][j] != rooms[i - 1][j])
			{
				int new_size = sizes[rooms[i][j]] + sizes[rooms[i - 1][j]];
				if (new_size > slr_r1w)
				{
					slr_r1w = new_size;
					r1w_i = i;
					r1w_j = j;
					r1w_d = 'S';
				}
			}
		}
	}
	ofstream fout("castle.out");
	fout << num_rooms << "\n";
	fout << slr << "\n";
	fout << slr_r1w << "\n";
	fout << r1w_i << " " << r1w_j << " " << r1w_d << "\n";
	fout.close();
	return 0;
}