#include<bits/stdc++.h>
using namespace std;

map<string, vector<pair<string, int>>> romaniaMap = {
    {"Arad", {{"Zerind", 75}, {"Timisoara", 118}, {"Sibiu", 140}}},
    {"Zerind", {{"Arad", 75}, {"Oradea", 71}}},
    {"Oradea", {{"Zerind", 71}, {"Sibiu", 151}}},
    {"Timisoara", {{"Arad", 118}, {"Lugoj", 111}}},
    {"Lugoj", {{"Timisoara", 111}, {"Mehadia", 70}}},
    {"Mehadia", {{"Lugoj", 70}, {"Drobeta", 75}}},
    {"Drobeta", {{"Mehadia", 75}, {"Craiova", 120}}},
    {"Craiova", {{"Drobeta", 120}, {"Rimnicu Vilcea", 146}, {"Pitesti", 138}}},
    {"Rimnicu Vilcea", {{"Craiova", 146}, {"Pitesti", 97}, {"Sibiu", 80}}},
    {"Sibiu", {{"Arad", 140}, {"Oradea", 151}, {"Rimnicu Vilcea", 80}, {"Fagaras", 99}}},
    {"Fagaras", {{"Sibiu", 99}, {"Bucharest", 211}}},
    {"Pitesti", {{"Rimnicu Vilcea", 97}, {"Craiova", 138}, {"Bucharest", 101}}},
    {"Bucharest", {{"Fagaras", 211}, {"Pitesti", 101}}},
};

double heuristic(string city , string dest){
    map<string , int> coord  = {
    {"Arad", 366}, {"Zerind", 374}, {"Oradea", 380}, {"Timisoara", 329}, {"Lugoj", 244}, {"Mehadia", 241}, {"Drobeta", 242}, {"Craiova", 160}, {"Rimnicu Vilcea", 193}, {"Sibiu", 253}, {"Fagaras", 178}, {"Pitesti", 98}, {"Bucharest", 0}};

    return coord[city];
}

vector<string> aStar(string start , string goal){
    priority_queue<pair<int,string> , vector<pair<int,string>> , greater<pair<int,string>>> pq;
    map<string , int> cost;
    map<string , string> parent;

    pq.push({0,start});
    cost[start] = 0;

    while(!pq.empty()){
        string current = pq.top().second;
        pq.pop();

        if(current == goal){
            vector<string> path;
            while(current!=start){
                path.push_back(current);
                current = parent[current];
            }
            path.push_back(start);
            reverse(path.begin(),path.end());
            return path;
        }

        for(auto neighbour : romaniaMap[current]){
            string next = neighbour.first;
            int new_cost = cost[current] + neighbour.second;

            if(cost.find(next)==cost.end() || cost[next]> new_cost){
                cost[next] = new_cost;
                int priority = new_cost + heuristic(next,goal);
                pq.push({priority,next});
                parent[next] = current;
            }
        }
    }

    return {};

    
}

int main(){
    
    string start = "Arad";
    string goal = "Bucharest";

    vector<string> path = aStar(start,goal);

    if(path.empty()) cout<<"No path Exists b/w "<<start<<" & "<<goal<<endl;

    else{
        for(auto i : path){
            cout<<i<<" ";
        }
        cout<<endl;
    }

    
    return 0;
}

