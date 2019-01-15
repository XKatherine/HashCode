#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
using namespace std;

class Car{
public:

};



vector<vector<int>> readFile(char* fileName, int& R, int& C, int& F, int& N, int& B, int& T){
	string line;
	vector<vector<int>> ret;
	ifstream myFile(fileName);
	if(myFile.is_open()){
		myFile>>R>>C>>F>>N>>B>>T;
		getline(myFile,line);
		while(getline(myfile,line)){
			int n;
			vector<int> v;
			istringstream is(line);
			while(is>>n) v.push_back(n);
			ret.push_back(v);
		}
		myFile.close();
	}
	return ret;
}

int main(int argc, char** argv){
	int R, C, F, N, B, T;
	//R - rows; C - cols; F - fleet; N - rides; B - bonus; T - steps 
	vector<vector<int>> rides = readFile(argv[1], R, C, F, N, B, T); 
}

