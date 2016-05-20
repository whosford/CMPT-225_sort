/*
* sort.h
*
*  Created on: Oct 30, 2015
*      Author: Will
*/

#ifndef SORT_H_
#define SORT_H_

#include <vector>

using Val = int;
using Container = std::vector<Val>;
using Iter = long;

int insertionSort(Container& arr, Iter start, Iter end);
int mergeSort(Container& arr, Iter start, Iter end);
int quickSort(Container& arr, Iter start, Iter end);
int shellSort(Container& arr, Iter start, Iter end);

#endif /* SORT_H_ */