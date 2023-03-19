/*
ID: kondasu1
LANG: C++
TASK: sprime
*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int N;

int pd1[4] = {2, 3, 5, 7};

int power(int x, int y){
	int n = 1;
	for(int i = 0; i < y; i++){
		n*=x;
	}
	return n;
}

bool checkprime(int pal){
	bool isPrime = true;
	if(pal % 2 == 0){
		isPrime = false;
	}
	if(pal % 3 == 0){
		isPrime = false;
	}
	for(int i = 5; i*i <= pal; i+=6){
		if(pal % i == 0){
			isPrime = false;
		}
		if(!isPrime){
			break;
		}
	}
	for(int i = 7; i*i <= pal; i+=6){
		if(pal % i == 0){
			isPrime = false;
		}
		if(!isPrime){
			break;
		}
	}
	return isPrime;
}

int main(void){
	ifstream fin("sprime.in");
	fin >> N;
	fin.close();

	int num = 0;
	vector<int> prevlayer = {0};
	for(int i = 0; i < N; i++){
		vector<int> newlayer = {};
		for(int num : prevlayer){
			if(i == 0){
				for(int j = 0; j < 4; j++){
					newlayer.push_back(pd1[j] * power(10, N - 1) + num);
				}
			}else{
				for(int j = 1; j <= 9; j+=2){
					int p = power(10, N - i - 1);
					int n = j * p + num;
					if(checkprime(n/p)){
						newlayer.push_back(n);	
					}
				}
			}
		}
		prevlayer = newlayer;
	}


	ofstream fout("sprime.out");

	for(int sp: prevlayer){
		fout << sp << endl;
	}

	fout.close();
}