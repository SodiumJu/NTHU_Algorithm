#include <fstream>  
#include <vector>    
#include <iostream>
#include <cstdlib> /* related to random */
#include <ctime>   /* related to time */
#include <chrono>

using namespace std;
using namespace chrono;

int main(int argc, char* argv[]) 
{	
	int range=20000;
	string out_file;
	ofstream outfile;

	if(argc==2){
		int id;
		int size=stof(argv[1]);
		int tem;
		
		out_file="input_"+to_string(size)+".txt";
		outfile.open(out_file, ios::out);
		id=rand()%size + 1;
		outfile <<size<<" " << id <<endl;
		for(int i=0; i<size; i++){
			tem=rand()%range + 1;
			outfile << tem;
			if(i!=(size-1)){
				outfile << " ";
			}
		}
		
	}else{
		cout << "The number of parameters is incorrect." << endl;
	}
	return 0;
}