/*
 * rho.c
 *
 * Implementation of Pollard's Rho method in C++.
 *
 * The references I found online when searching for this name
 * were all to integer factorisation.
 *
 * The below implementation, by contrast, finds a repeated integer
 * in an array of length n + 1 containing integers in [1..n],
 * in linear time with O(n) space complexity, where the array is
 * read-only.
 *
 * Evidently there is a connection between integer factorisation and
 * finding duplicates which escapes me.
 */

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cassert>

using namespace std;

#define INPUT_SIZE_MIN 5
#define INPUT_SIZE_MAX 10

static unsigned int rand_between(unsigned int lo, unsigned int hi)
{
	return lo + rand() / (RAND_MAX / (hi - lo + 1) + 1);
}

static void make_input(unsigned int **arr, size_t *size)
{
	*size= rand_between(INPUT_SIZE_MIN, INPUT_SIZE_MAX);
	*arr = new unsigned int[*size];
	for (unsigned int i = 0; i < *size; i++) {
		(*arr)[i] = rand_between(1, *size - 1);
	}
}

static void show_arr(const unsigned int *arr, size_t size) {
	cout << "arr[" << size << "] = [";
	if (size--) {
		cout << *(arr++);
	}
	while (size--) {
		cout << ", " << *(arr++);
	}
	cout << "]" << endl;
}

static unsigned int rho(const unsigned int *arr, size_t size)
{
	unsigned int a, b;

	a = arr[arr[size - 1] - 1];
	b = arr[size - 1];
	while (a != b) {
		a = arr[arr[a - 1] - 1];
		b = arr[b - 1];
	}

	a = size;
	while (a != b) {
		a = arr[a - 1];
		b = arr[b - 1];
	}

	return a;
}

static void check_dup(const unsigned int *arr, size_t size, unsigned int dup)
{
	size_t count = 0;
	for (unsigned int i = 0; i < size; i++) {
		if (arr[i] == dup) {
			count++;
		}
	}
	cout << dup << " occurs " << count << " times." << endl;
	assert(count > 0);
}

int main(int argc, char **argv)
{
	srandom(time(NULL));
	size_t size;
	unsigned int *arr;
	make_input(&arr, &size);
	show_arr(arr, size);
	unsigned int dup = rho(arr, size);
	check_dup(arr, size, dup);
	delete [] arr;

	return EXIT_SUCCESS;
}
