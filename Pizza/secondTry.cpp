/*-- Using b for testing --*/
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<queue>
#include<map>
using namespace std;

struct Shape{
	int height, length, area;
	Shape(int h, int l):height(h),length(l),area(h*l){}

	friend bool operator<(Shape s1, Shape s2){
    	if(s1.area==s2.area) return s1.area<s2.area;
    	return s1.area<s2.area;
	}
};

void findShape(vector<vector<char>>& pattern, map<int,vector<pair<int, int>>>& ans, int row, int col, int grd, int cll, int rows, int cols){
	priority_queue<Shape> shape;
	if(grd==0) shape.push(Shape(1,1));
	else if(grd>0)
		for(int r=1; r<=cll; r++)
			for(int c=1; r*c<=cll; c++)
				shape.push(Shape(r,c));
	//Try every shape: from smaller to bigger ones
	vector<pair<int,int>> v;
	while(!shape.empty()){
		int r = shape.top().height;
		int c = shape.top().length;
		shape.pop();
		int t = 0, m = 0;
		if(r+row>rows || c+col>cols) continue;
		for(int p=0; p<r; p++)
			for(int q=0; q<c; q++)
				switch(pattern[p+row][q+col]){
					case 'T': ++t; break;
					case 'M': ++m; break;
				}
		if(t>=grd && m>=grd){
			v.push_back(make_pair(r,c));
		}
	}
	if(v.size()>0)
		ans.insert(make_pair(row*cols+col,v));
}

int select(int idx, map<int,vector<pair<int,int>>> shapes, int rows, int cols, vector<int> selected){
	if(idx == rows*cols) return 0;
	vector<pair<int,int>> pool = shapes[idx];//choices to choose
	int max = select(idx+1, shapes, rows, cols, selected), max_idx = -1;
	if(find(selected.begin(), selected.end(), idx) != selected.end() && pool.size()==0) return max;
	for(int i=0; i<pool.size(); ++i){
		bool isValid = true;
		for(int r=0; r<pool[i].first; r++)
			for(int c=0; c<pool[i].second; c++)
				if(find(selected.begin(), selected.end(), idx+r*cols+c) != selected.end())
					isValid = false;
		if(!isValid) continue;
		vector<int> tempSelected(selected);
		for(int r=0; r<pool[i].first; r++)
			for(int c=0; c<pool[i].second; c++)
				tempSelected.push_back(r*cols+c+idx);
		int score = pool[i].first*pool[i].second+select(idx+1, shapes, rows, cols, tempSelected);
		if(score>max){
			max = score;
			max_idx = i;
		}
	}
	if(max_idx > -1){
		for(int r=0; r<pool[max_idx].first; r++)
			for(int c=0; c<pool[max_idx].second; c++)
				selected.push_back(r*cols+c+idx);
	}
	return max;
}

int algo(vector<vector<char>>& pattern, int grd, int cll, int rows, int cols){
	map<int,vector<pair<int,int>>> ans;
	for(int i = 0; i<rows; i++)
		for(int j = 0; j<cols; j++)
			findShape(pattern,ans,i,j,grd,cll,rows,cols);
	vector<int> selected;
	int idx = 0;//index of ans
	return select(idx,ans,rows,cols,selected);
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
	int ans = algo(matrix, grd, cll, row, col);

	/*
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
	*/
	cout<<ans<<endl;
	/*
	cout<<ans.size()<<endl;
	for(auto i : ans){
		for(auto j : i)
			cout<<j<<" ";
		cout<<endl;
	}
	*/
}
