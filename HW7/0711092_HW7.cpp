#include <iostream>
#include <stdlib.h>
#include <vector>
#include <list>
#include <queue>
#include <climits>
using namespace std;

class graph{
	private:
		int vt;
    		vector< list<int> > g;
    		int *c, *dis,*prd,*dvr,*fh;
	public:
		graph():vt(0){};           
    		graph(int N):vt(N){        
        	g.resize(vt);
    		};
    		void add(int, int);
    		void BFS(int);
    		void DFS(int);
    		void DFSVisit(int, int&);
};

void graph::add(int f, int t){
    g[f].push_back(t);
}

void graph::BFS(int N){

    c = new int[vt];prd = new int[vt];dis= new int[vt];
    int *doutput = new int[vt];
    int d=0;
    cout << "BFS:"<<endl;
    cout << "visit order:[";

    for (int i = 0; i < vt; i++) {  
        c[i] = 0;                       
        prd[i] = -1;                
        dis[i] = INT_MAX;          
    }                                  
    queue<int> q;
    c[N] = 1;                   
    dis[N] = 0;                
    prd[N] = -1;            
    q.push(N);
    while (!q.empty()) {
        int u = q.front();                 
        q.pop();
	for(list<int>::iterator v = g[u].begin(); v != g[u].end(); v++){
		if(c[*v] == 0){
			c[*v] = 1;
			dis[*v] = dis[u]+1;
			prd[*v] = u;
			q.push(*v);
		}
	}
	if(d!=0) cout << ",";
	cout << "'" << char(u+65) << "'";        
        doutput[d] = dis[u];
	d++;
	c[u] = 2;   
    }	    
    cout << "]"<<endl;
    cout <<"minimum distance: [";
    for(int i=0;i<vt;i++){
	    cout << doutput[i];
	    if(i!=(vt-1)) cout << ",";
    }
    cout << "]"<<endl;
}
void graph::DFS(int N){
    c = new int[vt];         
    dvr = new int[vt];
    fh = new int[vt];
    prd = new int[vt];

    for (int i = 0; i < vt; i++) { 
        c[i] = 0;
        dvr[i] = 0;
        fh[i] = 0;
        prd[i] = -1;
    }
    int time=0;
    for (int i = 0; i < vt; i++) {
        if (c[N] == 0) {          
            DFSVisit(N, time);
        }
    }
    cout<<endl;
    cout << "DFS-Visit:"<<endl;
    cout << "visit order: [";
    int f=0, t=0;
    while(f<vt){
	for(int i=0;i<vt;i++){
		if(dvr[i] == t){
			cout << "'" << char(i+65) << "'";
			if(f!=(vt-1)) cout << ",";
			else cout << "]"<<endl;
			f++;
		}
	}
	t++;
    }
}

void graph::DFSVisit(int u, int &time){   
    c[u] = 1;                         
    dvr[u] = ++time;                 
    for (list<int>::iterator v = g[u].begin(); v != g[u].end(); v++) { 
        if (c[*v] == 0) {               
            prd[*v] = u;       
            DFSVisit(*v, time);             
	}
    }
    c[u] = 2;                      
    fh[u] = ++time;                
}

int main(){
    graph g(6);    
    g.add(0, 1);g.add(0, 3);g.add(0, 4);
    g.add(1, 0);g.add(1, 2);
    g.add(2, 1);g.add(2, 4);
    g.add(3, 0);g.add(3, 4);
    g.add(4, 0);g.add(4, 3);g.add(4, 5);g.add(4, 2);
    g.add(5, 4);

    g.BFS(0);   
    g.DFS(0);
    return 0;
}
