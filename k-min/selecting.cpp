#include <fstream>  
#include <vector>    
#include <iostream>
#include <cstdlib> /* related to random */
#include <ctime>   /* related to time */
#include <chrono>

using namespace std;
using namespace chrono;


//int num_size;
int id;
int num_size;
int* num_arr;

bool name_with_size=false;

int* read_input_file(ifstream& inFile){
		
	int temp;
	int* array;

	inFile >> num_size >> id;
	cout << "Integers size:" << num_size << endl;
	array = new int [num_size];
	cout << "Selecting index: " << id << endl;
	for(int i=0; i<num_size; i++){
		inFile >> temp;
		array[i]=temp;
	}
	return array;
}

void print_array(int *arr){
	for(int i=0; i<num_size; i++){
		cout << arr[i] << " ";
	}
	cout << endl;
}


void copy_arr(int* original_ar, int* copy_ar, int size){
	for(int i=0; i<size; i++){
		copy_ar[i]=original_ar[i];
	}
}

//for quick sort

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition (int* arr, int low, int high)
{
    int pivot = arr[high]; // pivot
    int i = (low - 1); 
 
    for (int j = low; j <= high - 1; j++)
    {        
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quick_sort(int* arr, int low, int high){
	if (low < high)
    {
        int pivot = partition(arr, low, high);
 
        quick_sort(arr, low, pivot - 1);
        quick_sort(arr, pivot + 1, high);
    }
}

void QS(int* arr){
    string outQS;
    if(name_with_size){
        outQS=to_string(num_size)+"_QS.txt";
    }else{
        outQS="QS.txt";
    }
	ofstream outfile;
	high_resolution_clock::time_point qs_start = high_resolution_clock::now();
	quick_sort(arr, 0, (num_size-1) );
	high_resolution_clock::time_point qs_end = high_resolution_clock::now();
	duration<double> qs_time_span = duration_cast<duration<double> >(qs_end - qs_start);
	outfile.open(outQS, ios::out);
	outfile << arr[(id-1)] << endl;
	outfile << qs_time_span.count() << endl;

	//print_array(arr);
	outfile.close();
    cout << "QS" << endl;
    cout << arr[(id-1)] << endl;
    cout << qs_time_span.count() << endl;
}
//for quick sort

//for prune & search

void insertionSort(int* arr, int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int partition(int* arr, int l, int r, int med)
{
	//finding median index
    int i;
    for (i=l; i<r; i++)
        if (arr[i] == med)
           break;
    swap(&arr[i], &arr[r]);
  
    // Standard partition algorithm
    i = l;
    for (int j = l; j <= r - 1; j++)
    {
        if (arr[j] <= med)
        {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[r]);
    return i;
}

int find_med(int* arr, int n)
{
    insertionSort(arr, n);  // Only five elements, 
    // so I use insertion sort->O(25(n/5))
    return arr[n/2];   // Return middle element
}

int prune_search(int* arr, int l, int r, int k)
{
	int n = r-l+1; // Number of elements in arr[l..r]
    // If k is smaller than number of elements in array
    if (k > 0 && k <= n)
    {
        /*if(n<=5){
        	insertionSort(arr+l, n);
        	return arr[(k-1)];
        }*/
  
        // Divide arr[] in groups of size 5, calculate median
        // of every group and store it in median[] array.
        int i;
        int median[(n+4)/5]; // There will be floor((n+4)/5) groups;
        for (i=0; i<n/5; i++){
            median[i] = find_med(arr+l+i*5, 5);
        }

        if (i*5 < n) //For last group with less than 5 elements
        {
            median[i] = find_med(arr+l+i*5, n%5); 
            i++;
        }    
  		int medOfMed;
        // Find median of all medians using recursive call.
        // If median[] has only one element, 
        // then no need of recursive call
  		if(i==1){
  			medOfMed=median[i-1];
  		}else{
  			medOfMed=prune_search(median, 0, i-1, i/2);
  		}
        // Partition the array around a random element and
        // get position of pivot element in sorted array
        int pos = partition(arr, l, r, medOfMed);
  
        // If position is same as k
        if (pos-l == k-1)
            return arr[pos];
        if (pos-l > k-1)  // If position is more, recur for left
            return prune_search(arr, l, pos-1, k);
  
        // Else recur for right subarray
        return prune_search(arr, pos+1, r, k-pos+l-1);
    }
  
    // If k is more than number of elements in array
    return -1;
}

void PS(int* arr){
    string outPS;
	if(name_with_size){
        outPS=to_string(num_size)+"_PS.txt";
    }else{
        outPS="PS.txt";
    }
	ofstream outfile;
	high_resolution_clock::time_point ps_start = high_resolution_clock::now();
	int ans=prune_search(arr, 0, (num_size-1) , id);
	high_resolution_clock::time_point ps_end = high_resolution_clock::now();
	duration<double> ps_time_span = duration_cast<duration<double> >(ps_end - ps_start);
	outfile.open(outPS, ios::out);
	outfile << ans << endl;
	outfile << ps_time_span.count() << endl;

	//print_array(arr);
	outfile.close();
    cout << "PS" << endl;
    cout << ans << endl;
    cout << ps_time_span.count() << endl;

}
//for prune & search

int main(int argc, char* argv[]) 
{	
	string input_file;
	if(argc==2 || argc==3){
		input_file=argv[1];
        if(argc==3){
            string par2=argv[2];
            if(par2=="n"){
                name_with_size=true;
            }
        }
		ifstream inFile(input_file);
		num_arr=read_input_file(inFile);
		//print_array(num_arr);
		int* copy_array = new int [num_size];
		copy_arr(num_arr,copy_array, num_size);
		//print_array(copy_array);
		QS(num_arr);
        cout <<"---"<<endl;
		//print_array(copy_array);
		PS(copy_array);
        cout << endl;
		//int* test_arr=copy_array+3;
		//print_array(copy_array);
		//cout << test_arr[0] << endl;
    }else{
		cout << "The number of parameters is incorrect." << endl;
	}
	return 0;
}