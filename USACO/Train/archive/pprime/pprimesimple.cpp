/*
ID: kondasu1
LANG: C++
TASK: pprime
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <bits/stdc++.h> 
using namespace std;

int A;
int B;

int hA;
int hB;

vector<int> pals;
int power(int n, int j){
	int num = 1;
	for(int i = 0; i < j; i++){
		num *= n;
	}
	return(num);
}

int half(int n){
	return(n / (int) round(power(10, floor(floor(log10(n)+1)/2))));
}

int hToN(int h){
	int n = h;
	int reversedNumber = 0;
	while(n > 0)
    {
        int remainder = n % 10;
        reversedNumber = reversedNumber*10 + remainder;
        n /= 10;
    }
    return h * power(10, floor(log10(h))) + reversedNumber % power(10, floor(log10(h)));
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
	ifstream fin("pprime.in");
	fin >> A >> B;
	fin.close();

	int mB = B;

	if((int) floor(log10(B)) % 2 == 1){
		mB *= 10;
	}

	hA = half(A);
	hB = half(mB);

	cout << hB << endl;

	if(11 >= A && 11 <= B){
		pals.push_back(11);
	}

	for(int i = hA; i <= hB; i++){
		int num = hToN(i);
		if(checkprime(num) && num >= A && num <= B){
			pals.push_back(num);
		}
	}

	sort(pals.begin(), pals.end());

	ofstream fout("pprime.out");

	for(int pal : pals){
		fout << pal << endl;
	}

	fout.close();
	return 0;
}