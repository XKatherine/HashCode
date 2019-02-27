#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include<queue>
using namespace std;

struct Video {
    int id, size;
    Video(int i, int s) : id(i), size(s) {}
};

struct Cache {
    int id, cap;
    Cache(int i, int c) : id(i), cap(c) {}
};

struct Endpoint {
    int L, K, id;
    priority_queue<int, int> cachesConnected;
    Endpoint(int i, int L, int K, priority_queue<int, int>& c) : id(i), L(L), K(K), cachesConnected(c) {}
};

struct Request {
    int num;
    Video video;
    Endpoint endpoint;
    Request(Video v, Endpoint e, int n) : video(v), endpoint(e), num(n) {}
    
    friend bool operator< (Request & l, Request & r){
        return l.num < r.num;
    }
};

class Solution {
public:
    int V, E, R, C, X;
    int score = 0;
    vector<Video> videos;
    vector<Cache> caches;
    vector<Endpoint> endpoints;
    priority_queue<Request> requests;
    
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
                caches.push_back(Cache(i, X));
 
            //Video Line
            getline(file, line);
            istringstream isV(line);
            for(int i = 0; i < V; ++i) {
                int n;
                isV >> n;
                videos.push_back(Video(i, n));
            }

            //Endpoints
            for(int i = 0; i < E; ++i) {
                int L, K;
                priority_queue<int, int> m;
                getline(file, line);
                istringstream is(line);
                is >> L >> K;
                
                for(int j = 0; j < K; ++j){
                    int c, l;
                    getline(file, line);
                    istringstream isC(line);
                    isC >> c >> l;
                    m.push(make_pair(c, l));
                }
                
                endpoints.push_back(Endpoint(i, L, K, m));
            }
            
            //Requests
            for(int i = 0; i < R; ++i){
                int v, c, s;
                getline(file, line);
                istringstream is(line);
                is >> v >> c >> s;
                
                requests.push(Request(videos[v], endpoints[c], s));
            }

            file.close();
        }
    }
    
    void solve() {
        while(!requests.empty()){
            cout<<requests.top().num<<endl;
            requests.pop();
        }
    }

};


int main(int argc, char** argv) {
    Solution s(argv[1]);
    s.solve();
    
    return 0;
}
