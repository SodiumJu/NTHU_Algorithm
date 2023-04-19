#include <fstream>  
#include <vector>    
#include <iostream>
#include <cstdlib> /* related to random */
#include <ctime>   /* related to time */
#include <chrono>

//#define INT_MAX 2147483647

using namespace std;
using namespace chrono;

string file_name;

void swap(int* x, int* y) 
{ 
    int temp; 
    temp = *x; 
    *x = *y; 
    *y = temp; 
} 

void print_route(ofstream& outfile,vector<int>& arr){
	outfile << "Solution : 0";
	for(int i=0; i<arr.size(); i++){
		outfile << " - " << arr[i];
	}
	outfile << " - 0" << endl;
}

void print_matrix(vector<vector<int> > matrix){

	for(int i=0; i<matrix.size(); i++){
		for(int j=0; j<matrix.size(); j++){
			cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}
}

void print_matrix_to_file(ofstream& outfile,vector<vector<int> > matrix){

	for(int i=0; i<matrix.size(); i++){
		for(int j=0; j<matrix.size(); j++){
			outfile << matrix[i][j] << "\t";
		}
		outfile << endl;
	}
}

vector<vector<int> > creat_random_matrix(int dim){
	srand( time(NULL) );
	int x = (rand()%99)+1;
	vector<int> tmp;
	vector<vector<int> > matrix;

	for(int i =0; i<dim; i++){

		tmp.clear();
		for(int j=0; j<dim; j++){
			if(i==j){
				tmp.push_back(-1);
			}else{
				tmp.push_back(x);
				x = (rand()%99)+1;
			}
		}
		matrix.push_back(tmp);
	}
	return matrix;
}

vector<vector<int> > read_matrix(){
	int dim;
	vector<vector<int> > matrix;
	int input;
	cin >> dim;
	vector<int> temp;

	for(int i=0; i<dim; i++){
		temp.clear();
		for(int j=0; j<dim; j++){
			cin >> input;
			temp.push_back(input);
			//cout << input << " ";
		}
		//cout << endl;
		matrix.push_back(temp);
	}
	//print_matrix(matrix);
	return matrix;
}

vector<int> create_arr(int n){
	vector<int> arr;
	for(int i=1; i<n; i++){
		arr.push_back(i);
	}
	return arr;

}

void permutations(vector<vector<int> >& sol,vector<int> arr, int i, int n)
{
    // base condition
    if (i == n - 1)
    {
    	/*for(int k =0; k<arr.size();k++){
    		cout << arr[k] << " ";
    	}
        cout << endl;*/
        sol.push_back(arr);
        return;
    } 
    // process each character of the remaining string
    for (int j = i; j < n; j++)
    {
        // swap character at index `i` with the current character
        swap(arr[i], arr[j]);        
        // recur for substring `str[i+1, n-1]`
        permutations(sol, arr, i + 1, n);
        // backtrack (restore the string to its original state)
        swap(arr[i], arr[j]);
    }
}

void brute_force(vector<vector<int> >& matrix,vector<int>& nodes, int& min_cost, vector<int>& bf_s){
	int cost=INT_MAX;
	int temp=0;
	int index;
	vector<vector<int> > Solu;
	permutations(Solu,nodes, 0, nodes.size());

	for(int i =0; i<Solu.size(); i++){
		temp=matrix[0][Solu[i][0]];
		for(int j=0;j<(Solu[i].size()-1);j++){
			temp=temp+matrix[Solu[i][j]][Solu[i][j+1]];
		}
		temp=temp+matrix[Solu[i][Solu[i].size()-1]][0];
		if(temp<cost){
			index=i;
			cost=temp;
		}
		temp=0;
	}
	
	bf_s=Solu[index];
	min_cost=cost;
}

int find_LB(vector<vector<int> >& matrix_tmp, int& size){
	int min = INT_MAX;
	int tot_LB = 0;

	for(int i=0; i<size; i++){
	    for (int k=0; k<size; k++){
	        if (matrix_tmp[i][k]<min && i != k){
	            min = matrix_tmp[i][k];
	        }
	    }
	    for (int k=0; k<size; k++){
	    	if (i != k){
	            matrix_tmp[i][k]=(matrix_tmp[i][k]-min);
	        }	    	
	    }
	    tot_LB=tot_LB+min;
	    min = INT_MAX;
	}
    return tot_LB;
}

//Global variables
vector<int> final_path;
int fianl_cost=INT_MAX;
//Global variables

void recur_B_B(vector<vector<int> >& matrix_tmp ,vector<bool> visited, vector<int> path, int& size, int LB){
	//print_route(path);
	int tmp_cost=0;
	int curr_node=path.back();
	//cout << "curr node:" << curr_node << endl;
	if(path.size()==size){
		tmp_cost=LB+matrix_tmp[curr_node][0];
		//cout << "tmp: " << tmp_cost << endl;
		if(tmp_cost<fianl_cost){
			fianl_cost=tmp_cost;
			//cout << "final cost:" << fianl_cost << endl;
			final_path=path;			
		}
	}else{
		for(int k=1; k<size; k++){
			//cout << "tmp: " << tmp_cost << endl;
			if(visited[k]==false){
				//cout << k << " " << endl;
				tmp_cost=LB+matrix_tmp[curr_node][k];

				if(tmp_cost<fianl_cost){
					path.push_back(k);
					visited[k]=true;
					recur_B_B(matrix_tmp, visited, path, size, tmp_cost);
					visited[k]=false;
					path.pop_back();
				}
			}
		}
	}
}

void B_B(vector<vector<int> >& matrix){

	//Initialize global variables
	final_path.clear();
	fianl_cost=INT_MAX;	

	int size=matrix.size();
	vector<vector<int> > reduced_M(matrix);
	int tot_LB=find_LB(reduced_M, size);
	
	//print_matrix(reduced_M);

	vector<int> path;
	path.push_back(0);
	//vector<bool> visited;
	vector<bool> visited(size, false);

	visited[0]=true;
	recur_B_B(reduced_M,visited,path,size,tot_LB);
	
	final_path.erase(final_path.begin());
	

}

void Conclude_BF(vector<vector<int> >& matrix){
	ofstream outfile;
	outfile.open("BF.txt", ios::out);
	int min_cost=INT_MAX;
	vector<int> bf_s;
	vector<int> nodes=create_arr(matrix.size());
	high_resolution_clock::time_point bf_start = high_resolution_clock::now();
	brute_force(matrix, nodes, min_cost, bf_s);
	high_resolution_clock::time_point bf_end = high_resolution_clock::now();
	print_route(outfile,bf_s); 
	outfile << "Cost     : " << min_cost << endl;
	duration<double> bf_time_span = duration_cast<duration<double> >(bf_end - bf_start);
	outfile << "Time     : " << bf_time_span.count() << " s" << endl;
	outfile.close();
}

void Conclude_BB(vector<vector<int> >& matrix){
	ofstream outfile;
	outfile.open("BB.txt", ios::out);
	high_resolution_clock::time_point bb_start = high_resolution_clock::now();
	B_B(matrix);
	high_resolution_clock::time_point bb_end = high_resolution_clock::now();
	print_route(outfile,final_path);	
	outfile << "Cost     : " << fianl_cost << endl;
	duration<double> bb_time_span = duration_cast<duration<double> >(bb_end - bb_start);
	outfile << "Time     : " << bb_time_span.count() << " s" << endl;
	outfile.close();
}

void Conclusion(ofstream& outfile,vector<vector<int> >& matrix){
	print_matrix_to_file(outfile,matrix);
	//Brute Force Method--->
	int min_cost=INT_MAX;
	vector<int> bf_s;
	vector<int> nodes=create_arr(matrix.size());
	high_resolution_clock::time_point bf_start = high_resolution_clock::now();
	brute_force(matrix, nodes, min_cost, bf_s);
	high_resolution_clock::time_point bf_end = high_resolution_clock::now();
	outfile << "---Brute Force Method---" << endl;
	print_route(outfile,bf_s); 
	outfile << "Cost     : " << min_cost << endl;
	duration<double> bf_time_span = duration_cast<duration<double> >(bf_end - bf_start);
	outfile << "Time     : " << bf_time_span.count() << " s" << endl;
	//Branch & Bound Method--->
	high_resolution_clock::time_point bb_start = high_resolution_clock::now();
	B_B(matrix);
	high_resolution_clock::time_point bb_end = high_resolution_clock::now();
	outfile << "---Branch and Bound Method---" << endl;	
	print_route(outfile,final_path);	
	outfile << "Cost     : " << fianl_cost << endl;
	duration<double> bb_time_span = duration_cast<duration<double> >(bb_end - bb_start);
	outfile << "Time     : " << bb_time_span.count() << " s" << endl;
	outfile << "-----------------------------" << endl;
}

void Conclude_inputMatrix(){ //Get the solutions for cin matrix

	vector<vector<int> > matrix = read_matrix();
	Conclude_BF(matrix);
	Conclude_BB(matrix);
}

void print_err(){
	cout << "Input parameters error." << endl;
}

void run_random_example(int sample_size, int citys_range_min, int citys_range_max){
	ofstream outfile;
	string file_name;
	vector<vector<int> > matrix;
	for(int k=citys_range_min; k<=citys_range_max; k++){
		//for each dimension, creating one log file
		file_name=to_string(k)+"x"+to_string(k)+"mat_BF+BB.txt";
		outfile.open(file_name, ios::out);
		for(int i=0; i<sample_size; i++){
			matrix=creat_random_matrix(k);
			Conclusion(outfile,matrix);
			
		}
		outfile.close();
	}
}

int main(int argc, char* argv[]) 
{	
	int sample_size;
	int citys_range_min;
	int citys_range_max;
	int arg1;
	int arg2;
	int arg3;
	if(argc==1){
		cout << "Using the cin mode." << endl;
		cout << "Using '<' to read the input file." << endl;
		Conclude_inputMatrix();
	}else if(argc==4){
		arg1=stof(argv[1]);
		arg2=stof(argv[2]);
		arg3=stof(argv[3]);
		if((arg1<1) || (arg2<2) || (arg3<arg2) ){
			print_err();
		}else{
			sample_size=arg1;
			citys_range_min=arg2;
			citys_range_max=arg3;
			run_random_example(sample_size, citys_range_min, citys_range_max);
		}
		
	}else{
		cout << "The number of parameters is incorrect." << endl;
	}
	
	//vector<vector<int> > test_mat=creat_random_matrix(6);
	//print_matrix(test_mat);

}

