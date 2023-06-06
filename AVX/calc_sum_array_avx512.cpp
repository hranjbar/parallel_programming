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

	__m512i sumx = _mm512_set_epi32(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	__m512i numx;
	for (unsigned int i = 0; i < SIZE; i += 16)
	{
		numx = _mm512_load_si512((__m512i const *)(nums + i));
		sumx = _mm512_add_epi32(numx, sumx);
	}

	int sums[16];
//	_mm512_storeu_si512((__m512i *)sums, sumx);
	int tot = 0;
/*	for (unsigned int i = 0; i < 16; i++)
	{
		tot += sums[i];
	}
*/
	auto end = chrono::high_resolution_clock::now();
	auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - beg).count();
	cout << "AVX total: " << tot << ", " << elapsed << " ms\n";
	return 0;
}
