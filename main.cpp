/*
* main.cpp
*
*  Created on: Oct 30, 2015
*      Author: Will
*/
#include <algorithm>
#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "sort.h"

using std::cout;
using std::endl;
using std::exception;
using std::left;
using std::right;
using std::setw;
using std::string;

// If necessary, set to the path for your test*.txt files
// Must either be empty or a path ending with "/"
const string dir{ "" };

// Formatting of output: Field widths
constexpr int fileWidth{ 11 }; // Width of file name field
constexpr int sizeWidth{ 4 };  // Width of file size field
constexpr int countWidth{ 5 }; // Width of comparison count field

enum class Sort { Insertion, Quick, Merge, Shell, Stl };

void doSort(const char* sortName, Sort sort);
void runTest(const char* file, Sort sort);
Container readFile(string infile);
string sorted(Container arr);
string contains(Container arr, Container arrOrig);
void sortTestResult(Container arr, Sort sort);

/*
Call the STL sort algorithm.

Compare using a lamba-expression with a by-reference capture of `count` to
count comparisons.

Index-based version ignores start and end parameters.
*/

int stlSort(Container& arr, Iter start, Iter end)
{
	int count{ 0 };
	std::sort(arr.begin(), arr.end(), [&count](const Val& a, const Val& b) { count++; return a < b; });
	return count;
}

/*
To add a new sort type:
0. Add the sort routine to this file (not sort.cpp)
1. Add an identifier to type `enum class Sort`
2. Add a call to doSort() from `main`
3. Add an entry to the switch statement in `sortTestResult`

To add a new test:
0. Add a call to `runTest` in `doSort`.
*/
int main()
{
	doSort("INSERTION SORT", Sort::Insertion);
	doSort("QUICKSORT", Sort::Quick);
	doSort("MERGESORT", Sort::Merge);
	doSort("SHELL SORT", Sort::Shell);
	doSort("STL SORT", Sort::Stl);

	return 0;
}

// Run all tests on a given sort
void doSort(const char* sortName, Sort sort)
{
	cout << sortName << endl << "---------" << endl;

	runTest("sorted.txt", sort);
	runTest("random1.txt", sort);
	runTest("random2.txt", sort);
	runTest("reverse.txt", sort);
	runTest("multiples.txt", sort);
	runTest("empty.txt", sort);
	runTest("svalue.txt", sort);
	runTest("pairs.txt", sort);

	cout << endl;
}

// Run a specified sort on a specified file
void runTest(const char* file, Sort sort)
{
	cout << setw(fileWidth) << left << file << ": ";
	Container arr = readFile(file);
	sortTestResult(arr, sort);
}

// Test that result is correct
void sortTestResult(Container arr, Sort sort)
{
	Container copy{ arr };

	cout << "n = " << setw(sizeWidth) << right << arr.size();
	switch (sort) {
	case Sort::Insertion:
		cout << ", comparisons = " << setw(countWidth) << right << insertionSort(arr, 0, arr.size());
		break;
	case Sort::Merge:
		cout << ", comparisons = " << setw(countWidth) << right << mergeSort(arr, 0, arr.size());
		break;
	case Sort::Quick:
		cout << ", comparisons = " << setw(countWidth) << right << quickSort(arr, 0, arr.size());
		break;
	case Sort::Shell:
		cout << ", comparisons = " << setw(countWidth) << right << shellSort(arr, 0, arr.size());
		break;
	case Sort::Stl:
		cout << ", comparisons = " << setw(countWidth) << right << stlSort(arr, 0, arr.size());
		break;
	}
	cout << "; " << contains(arr, copy);
	cout << "; " << sorted(arr) << endl;
}

// Open a file of Vals and read the contents into a Container
// PRE: the file contains values separated by white space
// RETURNS: Container with the contents of infile
Container readFile(string infile)
{
	std::ifstream ist(dir + infile);
	// Check if file opened correctly
	if (ist.fail())
		throw std::runtime_error(infile + " not found");

	Val val{};
	Container result{};
	while (ist >> val) {
		result.push_back(val);
	}
	return result;
}

// Check if a Container is in ascending order
// RETURNS: string saying whether arr is in ascending order
string sorted(Container arr)
{
	// Special case the empty array because arr.size() is UNSIGNED,
	// thus arr.size()-1 == std::numeric_limits<decltype(arr.size())>::max()
	// rather than -1
	if (arr.size() == 0)
		return "sorted correctly";
	// Check to see each element i <= element i+1
	for (int i{ 0 }; i < arr.size() - 1; i++) {
		if (arr[i] > arr[i + 1]) {
			std::ostringstream ss{};
			ss << "sorted INCORRECTLY---first out of order value was arr[" << i << "]=" << arr[i];
			return ss.str();
		}
	}
	return "sorted correctly";
}

// Check if arr contains arrOrig
// PRE: arr and arrOrig are the same size (neither necessarily sorted)
// RETURNS: string saying whether arr contains all values in arrOrig
string contains(Container arr, Container arrOrig)
{
	// Check to see each element of arrOrig is in arr1
	for (int i{ 0 }; i < arrOrig.size(); ++i) {
		if (std::find(arr.begin(), arr.end(), arrOrig[i]) == arr.end()) {
			std::ostringstream ss{};
			ss << "values were INCORRECT---original value arr[" << i << "]=" << arrOrig[i] << " not in sorted output";
			return ss.str();
		}
	}
	return "values were correct";
}