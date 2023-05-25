#include<iostream> 
#include<chrono>
#include<immintrin.h>

using namespace std;

#define SIZE 400'000'000
int nums[SIZE];

int main () {
	for (unsigned int i = 0; i < SIZE; ++i)
	{
		nums[i] = 1;
	}
	auto beg = chrono::high_resolution_clock::now();

	__m256i sumx = _mm256_set_epi32(0, 0, 0, 0, 0, 0, 0, 0);
	__m256i numx;
	for (unsigned int i = 0; i < SIZE; i += 8)
	{
		numx = _mm256_load_si256((__m256i const *)(nums + i));
		sumx = _mm256_add_epi32(numx, sumx);
	}

	int sums[8];
	_mm256_storeu_si256((__m256i *)sums, sumx);
	int tot = 0;
	for (unsigned int i = 0; i < 8; i++)
	{
		tot += sums[i];
	}

	auto end = chrono::high_resolution_clock::now();
	auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - beg).count();
	cout << "AVX total: " << tot << ", " << elapsed << " ms\n";
	return 0;
}
