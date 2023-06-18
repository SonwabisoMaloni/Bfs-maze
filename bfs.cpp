#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <fstream>

using namespace std;

class World{
public:
    int m,n;
    vector<string> data;
    pair<int,int> start, goal;

    queue<pair<int,int>> q;

    const pair<int, int> munvisited = {-1,-1};
    vector<vector<pair<int, int>>> mParents;

    World(istream &in){
        string line;
        in >> m >> n;
        getline(in, line);

        for(int i = 0; i<m; i++){
            getline(in, line);
            data.push_back(line);

            mParents.emplace_back(n, munvisited);

            auto tmp = line.find('S');
            if(tmp != line.npos){
                start.first = i;
                start.second = tmp;
            }
            tmp = line.find('G');
            if(tmp != line.npos){
                goal.first = i;
                goal.second = tmp;
            }
        }
    }
    void print(){
        for(const string &line : data){
            cout<<line<<endl;
        }
    }
    bool valid(pair<int,int> curr){
        return data[curr.first][curr.second] != 'x';
    }
    bool unvisited(pair<int,int> curr){
        return mParents[curr.first][curr.second] == munvisited;
    }
    void BDF(){
        BDF(start);

        if(q.empty() && unvisited(goal)){
            cout<<"No Path"<<endl;
        }
        else{
            pair<int,int> curr = mParents[goal.first][goal.second];
            while(curr != start){
                data[curr.first][curr.second] = '*';
                curr = mParents[curr.first][curr.second];
            }
        print();
        }

    }
    void BDF(pair<int,int> curr){

        q.push({start.first, start.second});

        while(!q.empty() && unvisited(goal)){
            curr = q.front();
            q.pop();

            for(int i = 0; i<4; i++){
                pair<int, int> down = {curr.first+1, curr.second};
                if(valid(down) && unvisited(down)){
                    
                    mParents[down.first][down.second] = curr;
                    q.push(down);
                }
                pair<int, int> left = {curr.first, curr.second-1};
                if(valid(left) && unvisited(left)){
                    
                    mParents[left.first][left.second] = curr;
                    q.push(left);
                }
                pair<int, int> up = {curr.first-1, curr.second};
                if(valid(up) && unvisited(up)){
                    
                    mParents[up.first][up.second] = curr;
                    q.push(up);
                }
                pair<int, int> right = {curr.first, curr.second+1};
                if(valid(right) && unvisited(right)){
                    
                    mParents[right.first][right.second] = curr;
                    q.push(right);
                }
            }
        }

    }

};

int main(){
    World w(cin);
    w.BDF();
    return 0;
}

