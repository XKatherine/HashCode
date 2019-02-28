#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include<queue>
#include<unordered_map>
using namespace std;

typedef pair<int, int> pi;

class Cmp{
public:
    bool operator() (pi l, pi r) const {
        return l.second > r.second;
    }
};

struct Video {
    int id, size;
    Video(int i, int s) : id(i), size(s) {}
};

struct Cache {
    int id, cap;
    unordered_map<int, int> videos;
    Cache(int i, int c) : id(i), cap(c) {}
};

struct Endpoint {
    int L, K, id;
    priority_queue<pi, vector<pi>, Cmp> cachesConnected;
    Endpoint(int i, int L, int K, priority_queue<pi, vector<pi>, Cmp>& c) : id(i), L(L), K(K), cachesConnected(c) {}
};

struct Request {
    int num;
    int video;
    int endpoint;
    Request(int v, int e, int n) : video(v), endpoint(e), num(n) {}
    
    friend bool operator< (Request l, Request r){
        return l.num < r.num;
    }
};

class Solution {
public:
    int V, E, R, C, X;
    int score = 0;
    int totalRequest = 0;
    int used = 0;
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
                priority_queue<pi, vector<pi>, Cmp> m;
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
                
                requests.push(Request(v, c, s));
                totalRequest += s;
            }

            file.close();
        }
    }
    
    void solve() {
        while(!requests.empty()) {
            Endpoint cur = endpoints[requests.top().endpoint];
            Video video = videos[requests.top().video];
            int num = requests.top().num;
            requests.pop();
            
            while(!cur.cachesConnected.empty()) {
                int cache = cur.cachesConnected.top().first;
                if (caches[cache].videos.find(video.id) != caches[cache].videos.end()) {
                    score +=  num * (cur.L - cur.cachesConnected.top().second);
                    break;
                }else if(caches[cache].cap >= video.size) {
                    caches[cache].cap -= video.size;
                    score +=  num * (cur.L - cur.cachesConnected.top().second);
                    if(caches[cache].videos.size() == 0) used++;
                    caches[cache].videos[video.id] = 1;
                    break;
                }
                
                cur.cachesConnected.pop();
            }
        }
        cout << score / totalRequest * 1000 <<endl;
        
        output();
    }
    
    void output(){
        ofstream outfile;
        outfile.open("out.txt");
        outfile << used << endl;
        for(auto i : caches){
            if(i.videos.size() > 0){
                outfile << i.id;
                for(auto it = i.videos.begin(); it != i.videos.end(); ++it){
                    outfile << " " << it->first;
                }
                outfile << endl;
            }
        }
        outfile.close();
    }

};


int main(int argc, char** argv) {
    Solution s(argv[1]);
    s.solve();
    
    return 0;
}
