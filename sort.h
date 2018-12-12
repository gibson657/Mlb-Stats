#pragma once

#include <functional>
#include <cstring>
#include "MLB_Stats.h"

// if Sort is < it is going down if not its going up
template<typename T, typename M, typename Comp>
void insertionSort(T* arr, int length, M T::* field, Comp&& comp)
{
	for (int i = 1; i < length; i++)
	{
		int j = i;

		/* Move elements of arr[0..i-1], that are
		   greater than key, to one position ahead
		   of their current position */
		while (j > 0 && comp(arr[j - 1].*field, arr[j].*field))
		{
			T temp = arr[j - 1];
			arr[j - 1] = arr[j];
			arr[j] = temp;
			j = j - 1;
		}
	}
}

// if Sort is < it is going down if not its going up
template<typename T, typename M, typename Comp>
void insertionSort(T* arr, int* years, int length, M T::* field, Comp&& comp)
{
	for (int i = 1; i < length; i++)
	{
		int j = i;

		/* Move elements of arr[0..i-1], that are
		   greater than key, to one position ahead
		   of their current position */
		while (j > 0 && comp(arr[j - 1].*field, arr[j].*field))
		{
			mlb_stats temp = arr[j - 1];
			arr[j - 1] = arr[j];
			arr[j] = temp;

			int temp_year = years[j - 1];
			years[j - 1] = years[j];
			years[j] = temp_year;

			j = j - 1;
		}
	}
}

template<typename T, typename M, typename Comp>
void merge(T* arr, int l, int m, int r, M T::* field, Comp&& comp)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	// create temp arrays /
	T*L = new T[n1];
	T*R = new T[n2];


	/* Copy data to temp arrays L[] and R[]*/
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray
	j = 0; // Initial index of second subarray
	k = l; // Initial index of merged subarray
	while (i < n1 && j < n2)
	{
		if (comp(L[i].*field, R[j].*field))
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there
	   are any */
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	   are any */
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}

	delete[]L;
	delete[]R;
}

/*l is for left index and r is right index of the
   sub-array of arr to be sorted*/
   // if Sort is < it is going down if not its going up
template<typename T, typename M, typename Comp>
void mergeSort(T* arr, int l, int r, M T::* field, Comp&& comp)
{
	if (l < r)
	{
		// Same as (l+r)/2, but avoids overflow for 
		// large l and h 
		int m = l + (r - l) / 2;

		// Sort first and second halves 
		mergeSort(arr, l, m, field, comp);
		mergeSort(arr, m + 1, r, field, comp);

		merge(arr, l, m, r, field, comp);
	}
}

// if Sort is < it is going down if not its going up
template<typename T, typename M, typename Comp>
void mergeSort(T* arr, int length, M T::* field, Comp&& comp)
{
	// Same as (l+r)/2, but avoids overflow for 
	// large l and h 
	int m = length / 2;

	// Sort first and second halves 
	mergeSort(arr, 0, m, field, comp);
	mergeSort(arr, m + 1, length, field, comp);

	merge(arr, 0, m, length, field, comp);
}

template<typename T, typename M, typename Comp>
void merge(T* arr, int* years, int l, int m, int r, M T::* field, Comp&& comp)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	// create temp arrays /
	T*L = new T[n1];
	T*R = new T[n2];
	int* L_years = new int[n1];
	int* R_years = new int[n2];

	/* Copy data to temp arrays L[] and R[]*/
	for (i = 0; i < n1; i++)
	{
		L[i] = arr[l + i];
		L_years[i] = years[l + i];
	}

	for (j = 0; j < n2; j++)
	{
		R[j] = arr[m + 1 + j];
		R_years[j] = years[m + 1 + j];
	}

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray
	j = 0; // Initial index of second subarray
	k = l; // Initial index of merged subarray
	while (i < n1 && j < n2)
	{
		if (comp(L[i].*field, R[j].*field))
		{
			arr[k] = L[i];
			years[k] = L_years[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			years[k] = R_years[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there
	   are any */
	while (i < n1)
	{
		arr[k] = L[i];
		years[k] = L_years[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	   are any */
	while (j < n2)
	{
		arr[k] = R[j];
		years[k] = R_years[j];
		j++;
		k++;
	}

	delete[] L;
	delete[] R;
	delete[] L_years;
	delete[] R_years;
}

/*l is for left index and r is right index of the
   sub-array of arr to be sorted*/
   // if Sort is < it is going down if not its going up
template<typename T, typename M, typename Comp>
void mergeSort(T* arr, int* years, int l, int r, M T::* field, Comp&& comp)
{
	if (l < r)
	{
		// Same as (l+r)/2, but avoids overflow for 
		// large l and h 
		int m = l + (r - l) / 2;

		// Sort first and second halves 
		mergeSort(arr, years, l, m, field, comp);
		mergeSort(arr, years, m + 1, r, field, comp);

		merge(arr, years, l, m, r, field, comp);
	}
}

// if Sort is < it is going down if not its going up
template<typename T, typename M, typename Comp>
void mergeSort(T* arr, int* years, int length, M T::* field, Comp&& comp)
{
	// Same as (l+r)/2, but avoids overflow for 
	// large l and h 
	int m = length / 2;

	// Sort first and second halves 
	mergeSort(arr, years, 0, m, field, comp);
	mergeSort(arr, years, m + 1, length, field, comp);

	merge(arr, years, 0, m, length, field, comp);
}
