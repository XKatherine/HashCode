#include<iostream>
#include<vector>
#include<fstream>
#include<string>
using namespace std;

void algo(vector<string> pattern){}

vector<string> readFile(char* fileName, int* row, int* col, int* grd, int* cll){
	string line;
	vector<string> ret;
 	ifstream myfile(fileName);
  	if(myfile.is_open()){
		myfile>>*row>>*col>>*grd>>*cll;
		getline(myfile,line);
    	while(getline(myfile,line))
			ret.push_back(line);
    	myfile.close();
  	}
	return ret;
}

int main(int argc, char** argv){
	int row, col, grd, cll;
	vector<string> matrix = readFile(argv[1], &row, &col, &grd, &cll);
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++)
			cout<<matrix[i][j];
		cout<<endl;
	}
}
