/*
ID: kondasu1
LANG: C++
TASK: pprime
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
using namespace std;

int A;
int B;

int dA;
int dB;

vector<int> pals;

vector<int> digits(int i){
	int d;
	while(i>0){
		i /= 10
		d += 1
	}
	return d;
}

int digToInt(vector<int> digits){
	int num = 0;
	for(int i = 0; i < digits.size(); i++){
		num += digits[i] + pow(i, 10);
	}
	return num;
}

bool checkprime(int pal){
	bool isPrime = true;
	if(pal % 2 == 0){
		isPrime = false;
	}
	if(pal % 3 == 0){
		isPrime = false;
	}
	for(int i = 5; i*i < pal; i+=6){
		if(i % pal == 0){
			isPrime = false;
		}
		if(!isPrime){
			break
		}
	}
	for(int i = 7; i*i < pal; i+=6){
		if(i % pal == 0){
			isPrime = false;
		}
		if(!isPrime){
			break
		}
	}
	return isPrime;
}

void solve(vector<int> digits, int len){
	int size = digits.size();
	if(size == len){
		num = digToInt(digits);
		if(checkprime(num)){
			pals.push_back(num);
		}
	}else{
		if(size == 0){
			for(int i = 1; i <= 9; i+=2){
				digits.push_back(i);
				solve(digits, len);
				digits.pop_back();
			}
		}else{ 
			for(int i = 0; i <= 9; i++){
				digits.push_back(i);
				solve(digits, len);
				digits.pop_back();
			}
		}
	}
}

int main(void){

	ifstream fin("pprime.in");
	fin >> A >> B;
	fin.close();

	dA = digits(A) + 1;
	dB = digits(B) + 1;
	if(dA % 2 == 0){
		dA += 1;
	}
	if(dB % 2 == 0){
		dB -= 3;
	}
	nDA /= 2;
	nDB /= 2;

	solve()

	ofstream fout("pprime.out");

	fout.close();
	return 0;
}