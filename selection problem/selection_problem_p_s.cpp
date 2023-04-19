#include <iostream>
#include <algorithm>

int Median(int elements[], int n)
{
	std::sort(elements, elements+n);
	return elements[n/2];
}

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int partition(int elements[], int front, int tail, int x)
{

	int i;
	for (i=front; i<tail; i++){
		if (elements[i] == x)
		break;
	}		
	swap(&elements[i], &elements[tail]);

	// Standard partition algorithm
	i = front;
	for (int j = front; j <= tail - 1; j++)
	{
		if (elements[j] <= x)
		{
			swap(&elements[i], &elements[j]);
			i++;
		}
	}
	swap(&elements[i], &elements[tail]);
	return i;
}

int kth_smallest(int elements[], int front, int tail, int k)
{
	int len = tail-front+1; // Number of elements
	if ((k > 0) && (k <= len))
	{

		int i;
		//int median_array[(len+4)/5];
		int *median_array;
		median_array=(int *)malloc(((len+4)/5)*sizeof(int));
		int Med_med;

		for (i=0; i<len/5; i++)
			median_array[i] = Median(elements+front+i*5, 5);
		if (i*5 < len) //The last group
		{
			median_array[i] = Median(elements+front+i*5, len%5);
			i++;
		}

		if(i==1){
			Med_med=median_array[i-1];
		}else{
			Med_med=kth_smallest(median_array, 0, i-1, i/2);
		}

		int pos = partition(elements, front, tail, Med_med);

		if (pos-front == k-1){
			return elements[pos];
		}
		if (pos-front > k-1){
			return kth_smallest(elements, front, pos-1, k);
		}

		return kth_smallest(elements, pos+1, tail, k-pos+front-1);
	}

	return -1;
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

	/*printf("print input array\n");
	for (int i = 0; i < num; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	printf("---\n");*/
	printf("%d\n", kth_smallest(arr, 0, num-1, k));
	return 0;
}
