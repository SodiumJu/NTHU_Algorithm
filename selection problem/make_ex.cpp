#include <fstream>
#include <vector>
#include <iostream>
#include <cstdlib> /* related to random */
using namespace std;

void create_random_example(int sample_size, int int_max, int int_min ){
	int file_n=3;
	srand( time(NULL) );
	int k;
	ofstream outfile;
	string file_name;
	int rand_int;

	for (int f = 1; f < file_n+1; f++){
		file_name=to_string(sample_size)+"_"+to_string(f)+".txt";
		k = (rand() % (sample_size - 1 + 1)) + 1;
		outfile.open(file_name, ios::out);
		outfile << sample_size << " " << k << std::endl;
		for (int i = 0; i < sample_size; i++) {
			rand_int=(rand()%(int_max - int_min + 1)) + int_min;
			outfile << rand_int << std::endl;
		}
		outfile.close();
	}
	

}

int main()
{
	int n_lower, n_higher; //Constraints for n
	int int_max, int_min; // Each positive integer number in the input data is between 1 and 1,000,000.
	//n_lower=10000;
	//n_higher=30000;
	int n;
	int_min=1;
	int_max=1000000;

	scanf("%d", &n);
	create_random_example(n,int_max,int_min);
	return 0;
}
