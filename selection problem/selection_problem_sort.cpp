#include <iostream>

void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int the_pivot(int arr[], int& left, int& right){
	int pivot_arr[3];
	pivot_arr[0] = left;
	pivot_arr[1] = (left+right)/2;
	pivot_arr[2] = right;

	if (arr[pivot_arr[0]] > arr[pivot_arr[1]]){
		swap(&pivot_arr[0],&pivot_arr[1]);
	}
	if (arr[pivot_arr[1]] > arr[pivot_arr[2]]){
		swap(&pivot_arr[1],&pivot_arr[2]);
	}
	if (arr[pivot_arr[0]] > arr[pivot_arr[1]]){
		swap(&pivot_arr[0],&pivot_arr[1]);
	}
	return pivot_arr[1];
}

int partition (int arr[], int left, int right)
{	
	
	int pivot_i = the_pivot(arr,left,right);
	int pivot = arr[pivot_i];
	swap(&arr[pivot_i], &arr[right]);
	int i = (left - 1);

	for (int j = left; j <= right - 1; j++)
	{
		if (arr[j] < pivot)
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[right]);
	return (i + 1);
}

void quick_sort(int arr[], int left, int right)
{
	if (left < right)
	{
		int pi = partition(arr, left, right);

		quick_sort(arr, left, pi - 1);
		quick_sort(arr, pi + 1, right);
	}
}

int main()
{
	int num, k;
	scanf("%d%d", &num, &k);
	int *arr;
	arr=(int *)malloc(num*sizeof(int));
	for(int i=0; i<num; i++){
	    scanf("%d", &arr[i]);
	}

	//std::sort(arr,arr+num);

	quick_sort(arr, 0, num - 1);

	printf("%d\n", arr[k-1]);
	return 0;
}