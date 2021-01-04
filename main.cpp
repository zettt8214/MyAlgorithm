#include "Graph.h"
using namespace std;


void GraphTest();
int main() {
	GraphTest();
}

void GraphTest() {
	UndirectedGraph g(9, 15);
	vector<string> vertex = { "v0","v1","v2","v3","v4","v5","v6","v7","v8" };
	pair <vector<int>, double> edgeWeight[15] = {
		{{0,1},10},{{0,5},11},{{1,2},18},
		{{1,6},16},{{1,8},12},{{2,8},8},
		{{2,3},22},{{3,6},24},{{3,8},21},
		{{3,7},16},{{3,4},20},{{4,5},26},
		{{4,7},7},{{5,6},17},{{6,7},19},
	};

	g.CreateGraph(vertex, edgeWeight);
	cout << "DFS:" << endl;
	g.DFSTraverse();
	cout << "BFS:" << endl;
	g.BFSTraverse();
	cout << "Prim:" << endl;
	g.MiniSpanTreePrim();
	cout << "Kruskal:" << endl;
	g.MiniSpanTreeKruskal();

	vector<string> vertex1 = { "a","b","c","d","e","f","g","h","i" };
	pair <vector<int>, double> edgeWeight1[14] = {
		{{0,1},4},{{0,7},8},{{1,7},11},
		{{1,2},8},{{2,3},7},{{2,8},2},
		{{2,5},4},{{3,4},9},{{3,5},14},
		{{4,5},10},{{5,6},2},{{6,7},1},
		{{6,8},6},{{7,8},7},
	};
	UndirectedGraph g1(9, 14);
	g1.CreateGraph(vertex1, edgeWeight1);
	cout << "DFS:" << endl;
	g1.DFSTraverse();
	cout << "BFS:" << endl;
	g1.BFSTraverse();
	cout << "Prim:" << endl;
	g1.MiniSpanTreePrim();
	cout << "Kruskal:" << endl;
	g1.MiniSpanTreeKruskal();

}