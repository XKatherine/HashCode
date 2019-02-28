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
    vector<pi> cachesConnected;
    Endpoint(int i, int L, int K, vector<pi> c) : id(i), L(L), K(K), cachesConnected(c) {}
};

struct Request {
    int id;
    int num;
    int video;
    int endpoint;
    Request(int i, int v, int e, int n) : id(i), video(v), endpoint(e), num(n) {}
    
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
                vector<pi> m;
                getline(file, line);
                istringstream is(line);
                is >> L >> K;
                
                for(int j = 0; j < K; ++j){
                    int c, l;
                    getline(file, line);
                    istringstream isC(line);
                    isC >> c >> l;
                    m.push_back(make_pair(c, l));
                }
                
                endpoints.push_back(Endpoint(i, L, K, m));
            }
            
            
            //Requests
            for(int i = 0; i < R; ++i){
                int v, c, s;
                getline(file, line);
                istringstream is(line);
                is >> v >> c >> s;
                
                requests.push_back(Request(i, v, c, s));
                totalRequest += s;
 
            }
            
            file.close();
        }
    }
    
    void solve() {
        calScore();
    }
    
    void output() {
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
    
    void calScore() {
        for(int cache_id = 0; cache_id < caches.size(); ++cache_id){
            unordered_map<int, int> video_value;
            unordered_map<int, vector<int>> video_requests;
            for(int i = 0; i < requests.size(); ++i){
                vector<pi> v = endpoints[requests[i].endpoint].cachesConnected;
                for(auto it = v.begin(); it != v.end(); it++)
                    if(it->first == cache_id){
                        video_value[requests[i].video] += requests[i].num * (endpoints[requests[i].endpoint].L - it->second);
                        video_requests[requests[i].video].push_back(requests[i].id);
                        break;
                    }
            }
            
            if(video_value.size() == 0)
                continue;
            
            vector<pair<int, int>> video_value_v;
            for(auto it = video_value.begin(); it != video_value.end(); it++)
                video_value_v.push_back(make_pair(it->first, it->second));
            
            vector<vector<int>> d(video_value_v.size()+1, vector<int>(X+1, 0));
            
            for(int video_ind = 1; video_ind <= video_value_v.size(); video_ind++) {
                int actual_video_id = video_value_v[video_ind-1].first;
                for(int cap = 1; cap <= X; cap++){
                    if(videos[actual_video_id].size > cap)
                        d[video_ind][cap] = d[video_ind-1][cap];
                    else
                        d[video_ind][cap] = max(d[video_ind-1][cap], d[video_ind-1][cap-videos[actual_video_id].size] + video_value[actual_video_id]);
                }
            }
            
            int video_ind = (int)video_value_v.size();
            int cap = X;
            while(video_ind > 0 && cap > 0){
                while(video_ind > 0 && d[video_ind][cap] == d[video_ind-1][cap]) --video_ind;
                
                if(video_ind == 0) break;
                
                int actual_video_id = video_value_v[video_ind-1].first;
                for(int i = 0; i < video_requests[actual_video_id].size(); ++i){
                    //search
                    for(auto it = requests.begin(); it != requests.end(); ++it)
                        if(it->id == video_requests[actual_video_id][i]){
                            requests.erase(it);
                            break;
                        }
                }
                --video_ind;
                cap -= videos[actual_video_id].size;
            }
            
            score += d[video_value_v.size()][X];
            
            
            
            
        }
        cout << score / totalRequest * 1000 << endl;
    }
    
};


int main(int argc, char** argv) {
    Solution s(argv[1]);
    s.solve();
    
    return 0;
}
