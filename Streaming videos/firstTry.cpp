#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include<map>
using namespace std;

struct Video {
	int id, size;
	Video(int id, int size) : id(id), size(size) {}
};

struct Cache {
	int id, cap;
	Cache(int id, int cap) : id(id), cap(cap) {}
};

struct Endpoint {
	int L, K;
	map<Cache, int> cachesConnected;
	Endpoint(int L, int K, map<Cache, int>& c) : L(L), K(K), cachesConnected(c) {}
};

struct Request {
	int num;
	Video video;
	Endpoint endpoint;
	Request(Video v, Endpoint e, int n) : nums(n), video(v), endpoint(e) {}
};

class Solution {
public:
	int V, E, R, C, X;
	vector<Video> videos;
	vector<Cache> caches;
	vector<Endpoint> endpoints;
	vector<Request> requests;

	Solution(char* fileName) {
		ifstream file(fileName);
		if(file.is_open()){
			string line;
			getline(file, line);
			istringstream is(line);

			//First Line
			is >> V >> E >> R >> C >> X;

			//Cache Init
			for(int i = 0; i < C; ++i)
				caches.push_back(i, X);

			//Video Line
			int n;
			getline(file, line);
			istringstream isV(line);
			for(int i = 0; i < V; ++i) {
				isV >> n;
				videos.push_back(Video(i, n));
			}

			//Endpoints
			for(int i = 0; i < E; ++i) {
				int L, K;
				map<Cahce, int> m;
				getline(file, line);
				istringstream is(line);
				is >> L >> K;

				for(int i = 0; i < K; ++i){
					int c, l;
					getline(file, line);
					istringstream isC(line);
					isC >> c >> l;
					map[caches[c]] = l;
				}

				endpoints.push_back(Endpoint(L, K, m));
			}

			//Requests
			for(int i = 0; i < R; ++i){
				int v, c, s;
				getline(file, line);
				istringstream is(line);
				is >> v >> c >> s;

				requests.push_back(Request(videos(v), caches(c), s));
			}

			file.close();
		}

	}
};


int main(int argc, char** argv) {
	Solution s(argv[1]);
	//s.print();
	
	return 0;
}
