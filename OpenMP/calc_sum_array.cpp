#include<iostream> 
#include<chrono>
#include<omp.h>

using namespace std;

#define SIZE 400'000'000
#define NUM_CORES 8
int nums[SIZE];

int main () {
	for (unsigned int i = 0; i < SIZE; ++i)
	{
		nums[i] = 1;
	}
	auto beg = chrono::high_resolution_clock::now();
	omp_set_num_threads(NUM_CORES);
	int tot = 0, sum = 0;
#pragma omp parallel firstprivate(sum)
	{
		unsigned int tid = omp_get_thread_num();
		unsigned int low = tid * SIZE / NUM_CORES;
		unsigned int high = low + SIZE / NUM_CORES;
		for (unsigned int i = low; i < high; ++i)
		{
			sum += nums[i];
		}
#pragma omp critical
		{
			tot += sum;
		}
 
	}
	auto end = chrono::high_resolution_clock::now();
	auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - beg).count();
	cout << "OpenMP total: " << tot << ", " << elapsed << " ms\n";
	return 0;
}
