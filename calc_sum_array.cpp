#include<iostream> 
#include<chrono>

using namespace std;

#define SIZE 400'000'000
int nums[SIZE];

int main () {
	for (unsigned int i = 0; i < SIZE; ++i)
	{
		nums[i] = 1;
	}
	auto beg = chrono::high_resolution_clock::now();
	int tot = 0;
	for (unsigned int i = 0; i < SIZE; ++i)
	{
		tot += nums[i];
	}
	auto end = chrono::high_resolution_clock::now();
	auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - beg).count();
	cout << "serial total: " << tot << ", " << elapsed << " ms\n";
	return 0;
}
