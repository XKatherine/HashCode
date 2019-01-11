/*-- Using b for testing --*/
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
using namespace std;

void findShape(vector<vector<char>>& pattern, vector<vector<int>>& ans, int row, int col, int grd, int rows, int cols){
	vector<pair<int, int>> shape{make_pair(1,2),make_pair(2,1),make_pair(1,3),make_pair(3,1),make_pair(2,2),make_pair(1,5),make_pair(5,1)};
	//Try every shape: from smaller to bigger ones
	for(auto i : shape){
		bool isValid = true;
		int t = 0, m = 0;
		if(i.first+row>rows || i.second+col>cols) continue;
		for(int p=0; p<i.first; p++)
			for(int q=0; q<i.second; q++)
				switch(pattern[p+row][q+col]){
					case 'T': ++t; break;
					case 'M': ++m; break;
					case 'x': isValid = false; break;
				}
		if(isValid && t>=grd && m>=grd){
			for(int p=0; p<i.first; p++){
				for(int q=0; q<i.second; q++){
					pattern[p+row][q+col]='x';
				}
			}
			ans.push_back(vector<int>{row,row+i.first-1,col,col+i.second-1});
			return;
		}
	}
}

vector<vector<int>> algo(vector<vector<char>>& pattern, int grd, int rows, int cols){
	vector<vector<int>> ans;
	for(int i = 0; i<rows; i++)
		for(int j = 0; j<cols; j++)
			if(pattern[i][j] != 'x')
				findShape(pattern,ans,i,j,grd,rows,cols);
	return ans;
}

vector<vector<char>> readFile(char* fileName, int* row, int* col, int* grd, int* cll){
	string line;
	vector<vector<char>> ret;
 	ifstream myfile(fileName);
  	if(myfile.is_open()){
		myfile>>*row>>*col>>*grd>>*cll;
		getline(myfile,line);
    	while(getline(myfile,line)){
			vector<char> v;
			for(auto i : line)
				v.push_back(i);
			ret.push_back(v);
		}
    	myfile.close();
	}
	return ret;
}

int main(int argc, char** argv){
	int row, col, grd, cll;
	vector<vector<char>> matrix = readFile(argv[1], &row, &col, &grd, &cll);
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++)
			cout<<matrix[i][j];
		cout<<endl;
	}
	vector<vector<int>> ans = algo(matrix, grd, row, col);
	cout<<ans.size()<<endl;
	for(auto i : ans){
		for(auto j : i)
			cout<<j<<" ";
		cout<<endl;
	}
}
