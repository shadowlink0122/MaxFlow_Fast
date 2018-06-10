#include <iostream>
#include <vector>
#include <queue>
using namespace std;

static const int MAX = 100000;
static const int INF = 1e+9 + 7;
struct edge{int to,cap,rev;};
vector<edge> graph[MAX];
int level[MAX];
int iter[MAX];

void add_edge(int from,int to,int cap){
  graph[from].push_back((edge){ to , cap , (int)graph[to].size() });
  graph[to].push_back((edge){ from , 0 , (int)graph[from].size() - 1});
}

void bfs(int s){
  memset(level,-1,sizeof(level));
  queue<int> que;
  level[s] = 0;
  que.push(s);

  while(!que.empty()){
    int v = que.front();que.pop();
    for(int i = 0;i < graph[v].size();i++){
      edge &e = graph[v][i];
      if(e.cap > 0 && level[e.to] < 0){
        level[e.to] = level[v] + 1;
        que.push(e.to);
      }
    }
  }
}

int dfs(int v,int t,int f){
  if(v == t)return f;
  for(int &i = iter[v];i < graph[v].size();i++){
    edge &e = graph[v][i];
    if(e.cap > 0 && level[v] < level[e.to]){
      int d = dfs(e.to ,t ,min(f,e.cap));
      if(d > 0){
        e.cap -= d;
        graph[e.to][e.rev].cap += d;
        return d;
      }
    }
  }
  return 0;
}

int max_flow(int s,int t){
  int flow = 0;
  for(;;){
    bfs(s);
    if(level[t] < 0)return flow;
    memset(iter,0,sizeof(iter));
    int f;
    while((f = dfs(s,t,INF)) > 0){
      flow += f;
    }
  }
}

int main(){
  return 0;
}