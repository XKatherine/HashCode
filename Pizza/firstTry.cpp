/*-- Using b for testing --*/
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<cmath>
#include<queue>
using namespace std;

struct Shape{
	int height, length, area;
	Shape(int h, int l):height(h),length(l),area(h*l){}

	friend bool operator<(Shape s1, Shape s2){
    	if(s1.area==s2.area) return s1.area<s2.area;
    	return s1.area<s2.area;
	}
};

void findShape(vector<vector<char>>& pattern, vector<vector<int>>& ans, int row, int col, int grd, int cll, int rows, int cols){
	priority_queue<Shape> shape;
	if(grd==0) shape.push(Shape(1,1));
	else if(grd>0)
		for(int r=1; r<=cll; r++)
			for(int c=1; r*c<=cll; c++)
				shape.push(Shape(r,c));
	//Try every shape: from smaller to bigger ones
	while(!shape.empty()){
		int r = shape.top().height;
		int c = shape.top().length;
		shape.pop();
		bool isValid = true;
		int t = 0, m = 0;
		if(r+row>rows || c+col>cols) continue;
		for(int p=0; p<r; p++)
			for(int q=0; q<c; q++)
				switch(pattern[p+row][q+col]){
					case 'T': ++t; break;
					case 'M': ++m; break;
					case 'x': isValid = false; break;
				}
		if(isValid && t>=grd && m>=grd){
			for(int p=0; p<r; p++)
				for(int q=0; q<c; q++)
					pattern[p+row][q+col]='x';
			ans.push_back(vector<int>{row,col,row+r-1,col+c-1});
			return;
		}
	}
}

vector<vector<int>> algo(vector<vector<char>>& pattern, int grd, int cll, int rows, int cols){
	vector<vector<int>> ans;
	for(int i = 0; i<rows; i++)
		for(int j = 0; j<cols; j++)
			if(pattern[i][j] != 'x')
				findShape(pattern,ans,i,j,grd,cll,rows,cols);
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
	vector<vector<int>> ans = algo(matrix, grd, cll, row, col);

  	ofstream outfile;
  	outfile.open("out.txt");
  	outfile<<ans.size()<<endl;
	for(auto i : ans){
		for(auto j : i)
			outfile<<j<<" ";
		outfile<<endl;
	}
  	outfile.close();

  	return 0;
}
