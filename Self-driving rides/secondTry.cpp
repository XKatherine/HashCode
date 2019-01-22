#include<iostream>
#include<cmath>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include<queue>
using namespace std;

struct Ride{
	pair<int, int> start;//start point
	pair<int, int> end;//end point
	int et;//earlist start time
	int lt;//latest end time
	int path;
	int no; //# of ride
	Ride(vector<int> v) : start(make_pair(v[0], v[1])), end(make_pair(v[2], v[3])), et(v[4]), lt(v[5]), path(abs(v[3]-v[1])+abs(v[2]-v[0])), no(v[6]) {}  
	
	friend bool operator< (Ride l, Ride r){
		if(l.et == r.et) return l.et < r.et;
		return l.et < r.et;
	}
};

struct Car{
	int endTime;//endtime of the last journey
	pair<int, int> location; // current location
	vector<int> ride;
	Car(int e, int r, int c) : endTime(e), location(make_pair(r,c)) {}
};

int isAvailable(vector<Car>& cars, Ride r, int B){
	//from the current position to the start point
	int min = INT_MAX;
	int car = -1;
	for(int i = 0; i < cars.size(); i++){
		int starttime = cars[i].endTime + abs(cars[i].location.first-r.start.first) + abs(cars[i].location.second-r.start.second);
		if(starttime < r.et){
			if(min < 0 || r.et - starttime < min){
				car = i;
				min = r.et - starttime;
			}
		}else if(starttime == r.et){
			car = i;
			break;
		}else if(starttime <= r.lt - r.path){
			if(car == -1 || (min < 0 && r.et - starttime > min)){
				car = i;
				min = r.et - starttime;
			}
		}
	}
	if(car == -1) return 0;
	cars[car].endTime = r.et - min + r.path;
	cars[car].location = r.end;
	cars[car].ride.push_back(r.no);
	return min >= 0 ? B + r.path : r.path;
}

//return scores
int algo(priority_queue<Ride>& rides, vector<Car>& cars, int R, int C, int F, int N, int B, int T){ 
	//cars vector store from what time the car is available and their location
	int score = 0;
	for(int i = 0; i < F; i++)
		cars.push_back(Car(0,0,0));
	while(!rides.empty()){
		Ride r = rides.top();
		score += isAvailable(cars, r, B);
		rides.pop();
	}
	return score;
}

priority_queue<Ride> readFile(char* fileName, int& R, int& C, int& F, int& N, int& B, int& T){
	string line;
	//vector<vector<int>> ret;
	priority_queue<Ride> ret;
	ifstream myFile(fileName);
	if(myFile.is_open()){
		myFile>>R>>C>>F>>N>>B>>T;
		getline(myFile,line);
		int i = 0;
		while(getline(myFile,line)){
			int n;
			vector<int> v;
			istringstream is(line);
			while(is>>n) v.push_back(n);
			v.push_back(i++);
			Ride r(v);
			//cout<<"R"<<r.no<<": "<<r.path<<endl;
			ret.push(r);
		}
		myFile.close();
	}
	return ret;
}

int main(int argc, char** argv){
	vector<Car> cars;
	int R, C, F, N, B, T;
	int i = 0;
	//R - rows; C - cols; F - fleet; N - rides; B - bonus; T - steps 
	priority_queue<Ride> rides = readFile(argv[1], R, C, F, N, B, T); 

	int score = algo(rides, cars, R, C, F, N, B, T);
	for(Car c : cars){
		cout<<++i<<" ";
		for(int n : c.ride)
			cout<<n<<" ";
		cout<<endl;
	}
	cout<<score<<endl;
}

