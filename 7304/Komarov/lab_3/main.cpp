#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
using namespace std;

class Graph {
public:
    Graph() {};
    void createGraph() {
        while (true) {
            char v1;
            char v2;
            double weight;
            if ((cin >> v1) && (cin >> v2) && (cin >> weight)) {
                graph[v1].push_back(pair<char, double>(v2, weight));
                graph[v2];
                continue;
            }
            break;
        }
    }

    string search(char fromVertex, char toVertex) {
        map<char,bool> visitedVertex;
        vector<char> stack;
        map<char,char> way;
        for(it_for_graph=graph.begin();it_for_graph!=graph.end();it_for_graph++)
            visitedVertex[it_for_graph->first]=false;
        stack.push_back(fromVertex);
        for(int i=0;i<2*graph.size();i++) {
            if(stack[stack.size()-1]==toVertex)
                break;
            visitedVertex[stack[stack.size()-1]]=true;
            vector<pair<char, double>> neighbors;
            //cout<<stack[stack.size()-1]<<endl;
            for(pair<char,double> neighbor:graph.find(stack[stack.size()-1])->second)
                if(!visitedVertex[neighbor.first])
                    neighbors.push_back(neighbor);
            if(neighbors.size()==0){
                stack.pop_back();
                continue;
            }
            pair<char,double> min=*min_element(neighbors.begin(),neighbors.end(),[](pair<char,double>& n1,pair<char, double>& n2){
                return n1.second<n2.second;
            });
            way[min.first]=stack[stack.size()-1];
            stack.push_back(min.first);
        }
        string path="";
        for(char vertex=toVertex;path[0]!=fromVertex;vertex=way.find(vertex)->second)
            path=vertex+path;
        return path;
    }

private:
    map<char, vector<pair<char, double>>> graph;
    map<char,vector<pair<char,double>>>::iterator it_for_graph;
};

int main() {
    char A;//из точки А
    char B;// в точку B
    cin>>A>>B;
    Graph graph;
    graph.createGraph();
    cout<<graph.search(A,B);
    return 0;
}

