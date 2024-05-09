#include<bits/stdc++.h>
using namespace std;

class Graph{
    public:
    int n;
    int v[10][10];

    void input(){
        cout<<"Enter number of Vertices:";
        cin>>n;
        cout<<"Enter the adjacency matrix (0 for no edge and 1 for an edge)"<<endl;

        for(int i=0;i<n;i++){
            for(int j=i;j<n;j++){
                if(i==j) v[i][j]=0;
                else{
                    int a;
                    cout<< "Is there an edge between " << i << " and " << j << " (1 for yes, 0 for no): ";
                    cin>>a;
                    v[i][j] = v[j][i] = a;
                }
            }
        }
    }

    bool isSafe(int vertex  ,vector<int> &color  ,int c){
        for(int i=0;i<n;i++){
            if(v[vertex][i] && color[i]==c) return false;
        }
        return true;
    }

    bool graphColoringUtil(int m, vector<int> &color , int vertex = 0){
        if(vertex == n)  return true;
        for(int c=1;c<=m;c++){
            if(isSafe(vertex,color,c)){
                color[vertex] = c;
                if(graphColoringUtil(m,color,vertex+1)) return true;
                color[vertex] = 0;
            }
        }

        return false;
    }

    bool graphColoring(int m){
        vector<int> color(n, 0);
        if (!graphColoringUtil(m, color, 0)) {
            cout << "Solution does not exist" << endl;
            return false;
        } else {
            cout << "Vertex colors: ";
            for (int c : color) {
                cout << c << " ";
            }
            cout << endl;
            return true;
        }
    }

};

int main(){

    Graph g;
    g.input();

    int m;
    cout<<"Enter number of colors:";
    cin>>m;

    cout<<"Coloring the graph"<<endl;
    g.graphColoring(m);

    return 0;
}