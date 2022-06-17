#include <iostream>
#include <stdlib.h>
#include <vector>
#include <list>
#include <queue>
using namespace std;

class Graph{
private:
    vector< list<int> > G;
    int *color,             // 0:白色, 1:灰色, 2:黑色
        *distance,          
        *predecessor,
        *discover,
        *finish;
public:
    Graph(){};           
    Graph(int N){        
        G.resize(6);
    };
    void Add(int, int);
    void BFS(int);
    void DFS(int);
    void DFSVisit(int, int&);

};

void Graph::Add(int from, int to){
    G[from].push_back(to);
}

void Graph::BFS(int s){

    color = new int[6];
    predecessor = new int[6];
    distance = new int[6];
    int* doutput = new int[6];
    int d=0;
    cout << "BFS:\nvisit order:[";

    for (int i = 0; i < 6; i++) {  
        color[i] = 0;                       
        predecessor[i] = -1;                
        distance[i] = INT_MAX;          
    }                                  
    queue<int> q;
    color[s] = 1;                   
    distance[s] = 0;                
    predecessor[s] = -1;            
    q.push(s);
    while (!q.empty()) {
        int u = q.front();                 
        q.pop();
	for(list<int>::iterator v = G[u].begin(); v != G[u].end(); v++){
		if(color[*v] == 0){
			color[*v] = 1;
			distance[*v] = distance[u]+1;
			predecessor[*v] = u;
			q.push(*v);
		}
	}
	if(d!=0) cout << ", ";
	cout << "'" << char(u+65) << "'";        
        doutput[d] = distance[u];
	d++;
	color[u] = 2;   
    }	    
    cout << "]\nminimum distance: [";
    for(int i=0;i<6;i++){
	    cout << doutput[i];
	    if(i!=5) cout << ",";
    }
    cout << "]\n";
}
void Graph::DFS(int s){
    color = new int[6];         
    discover = new int[6];
    finish = new int[6];
    predecessor = new int[6];

    for (int i = 0; i < 6; i++) { 
        color[i] = 0;
        discover[i] = 0;
        finish[i] = 0;
        predecessor[i] = -1;
    }
    int time=0;
    for (int i = 0; i < 6; i++) {
        if (color[s] == 0) {          
            DFSVisit(s, time);
        }
    }
    cout << "\nDFS:\nvisit order: [";
    int f=0, t=0;
    while(f<6){
	for(int i=0;i<6;i++){
		if(discover[i] == t){
			cout << "'" << char(i+65) << "'";
			if(f!=5) cout << ", ";
			else cout << "]\n";
			f++;
		}
	}
	t++;
    }
}

void Graph::DFSVisit(int u, int &time){   
    color[u] = 1;                         
    discover[u] = ++time;                 
    for (list<int>::iterator v = G[u].begin(); v != G[u].end(); v++) { 
        if (color[*v] == 0) {               
            predecessor[*v] = u;       
            DFSVisit(*v, time);             
	}
    }
    color[u] = 2;                      
    finish[u] = ++time;                
}

int main(){
    Graph G(6);    
    G.Add(0, 1);G.Add(0, 3);G.Add(0, 4);
    G.Add(1, 0);G.Add(1, 2);
    G.Add(2, 1);G.Add(2, 4);
    G.Add(3, 0);G.Add(3, 4);
    G.Add(4, 0);G.Add(4, 3);G.Add(4, 5);G.Add(4, 2);
    G.Add(5, 4);
    G.BFS(0);   
    G.DFS(0);
    return 0;
}
