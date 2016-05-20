/*
* sort.cpp
*
*  Created on: Oct 30, 2015
*      Author: Will
*/

#include <vector>
#include "sort.h"

int insertionSort(Container& arr, Iter start, Iter end)
{
	int cur, j, count = 0;

	if (arr.size() > 1) {
		for (int i = start + 1; i <= end - 1; i++) {
			cur = arr[i];
			j = i - 1;
			while (j >= 0 && arr[j] > cur) {
				arr[j + 1] = arr[j];
				j = j - 1;
				arr[j + 1] = cur;
				count++;
			}
			count++;
		}
	}

	return count;
}

void merge(Container& arr, Container& S1, Container& S2, int& count)
{
	arr.clear();

	int i, j, k;
	for (i = 0, j = 0, k = 0; i < S1.size() && j < S2.size(); k++) {
		if (S1.at(i) <= S2.at(j)) {
			arr.push_back(S1.at(i));
			i++;
		}
		else if (S1.at(i) > S2.at(j)) {
			arr.push_back(S2.at(j));
			j++;
		}
		count++;
		k++;
	}

	while (i < S1.size()) { arr.push_back(S1.at(i)); i++; }

	while (j < S2.size()) { arr.push_back(S2.at(j)); j++; }
}

int mergeSplit(Container& arr, int& count)
{
	if (arr.size() > 1) {
		Container S1(arr.begin(), arr.begin() + arr.size() / 2);
		mergeSplit(S1, count);
		Container S2(arr.begin() + arr.size() / 2, arr.end());
		mergeSplit(S2, count);
		merge(arr, S1, S2, count);
	}

	return count;
}

int mergeSort(Container& arr, Iter start, Iter end)
{
	int count = 0;
	int size = end - start;
	if (size > 1) { count = mergeSplit(arr, count); }

	return count;
}

void swap(Val& a, Val& b)
{
	Val temp = a;
	a = b;
	b = temp;
}

Iter pivot(Container& arr, Iter beg, Iter last, Val pVal, int& comparisons)
{
	for (Iter j = beg; j < last; j++) {
		if (arr[j] <= pVal) {
			if (arr[j] < arr[beg])
				swap(arr[j], arr[beg]);
			beg++;
		}
		else
			swap(arr[beg], arr[j]);
		comparisons++;
	}
	if (pVal != arr[beg]) { swap(arr[last], arr[beg]); }
	comparisons++;

	return beg;
}

int quickSort(Container& arr, Iter start, Iter end)
{
	if (arr.size() == 0 || arr.size() == 1) { int c = 0; return c; }

	static int comp;
	int size = arr.size();

	if (start == 0 && end == size) { comp = 0; }

	Iter i = start, r = end - 1;

	if (i < r) {
		Val pivotVal = arr[r];
		int comparisons = 0;
		i = pivot(arr, i, r, pivotVal, comparisons);
		comp += comparisons;
		quickSort(arr, start, i);
		quickSort(arr, i + 1, end);
	}
	return comp;
}

int shellSort(Container& arr, Iter start, Iter end)
{
	int count = 0;
	int gap, i, j, size;
	Val temp;

	size = arr.size();

	if (size > 1) {
		for (gap = size / 2; gap > 0; gap /= 2) {
			for (i = gap; i < size; i++) {
				temp = arr[i];
				for (j = i; j >= gap; j -= gap) {
					if (temp < arr[j - gap]) { count++; arr[j] = arr[j - gap]; }
					else { count++; break; }
				}
				arr[j] = temp;
			}
		}
	}

	return count;
}