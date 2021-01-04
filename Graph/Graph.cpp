#include "Graph.h"


void UndirectedGraph::CreateGraph(std::vector<std::string> vertex,
	std::pair<std::vector<int>, double> edgeWeight[]) {

	for (int i = 0; i < vNums; i++) {
		VertexNode* v = new VertexNode;
		v->vertex = vertex[i];
		v->firstEdge = nullptr;
		graph.push_back(*v);
	}
	for (int nums = 0; nums < eNums; nums++) {

		int i, j;
		double weight;
		i = edgeWeight[nums].first[0];
		j = edgeWeight[nums].first[1];
		weight = edgeWeight[nums].second;

		EdgeTableNode* et = new EdgeTableNode;		//将(vi,vj)的信息加入边表
		et->begin = i;
		et->end = j;
		et->weight = weight;
		edgeTable.push_back(*et);


		EdgeNode* e = new EdgeNode;					//添加(vi,vj)到邻接表
		e->adjVertex = j;
		e->weight = weight;

		e->next = graph[i].firstEdge;
		graph[i].firstEdge = e;

		e = new EdgeNode;							//添加(vj,vi)到邻接表
		e->adjVertex = i;
		e->weight = weight;

		e->next = graph[j].firstEdge;
		graph[j].firstEdge = e;
	}


	for (auto v : graph) {
		std::cout << "Vertex: " << v.vertex << std::endl;
		std::cout << "Edges: ";
		for (auto p = v.firstEdge; p != nullptr; p = p->next) {
			int adjVxIndex = p->adjVertex;
			std::cout << "(" << v.vertex << ","
				<< graph[adjVxIndex].vertex << "),weight = " << p->weight << " ";
		}

		std::cout << std::endl;
		std::cout << std::endl;
	}
}



void UndirectedGraph::CreateGraph() {
	//初始化顶点数组
	for (int i = 0; i < vNums; i++) {
		VertexNode* v = new VertexNode;
		std::cout << "Input vertex " << i << " value:" << std::endl;
		std::cin >> v->vertex;
		v->firstEdge = nullptr;
		graph.push_back(*v);
	}

	//为顶点添加相关的边信息
	for (int nums = 0; nums < eNums; nums++) {
		int i, j;
		double weight;
		std::cout << "Input the i,j of (vi,vj): ";
		std::cin >> i >> j;
		std::cout << "Input the weight of (vi,vj): ";
		std::cin >> weight;

		EdgeNode* e = new EdgeNode;					//添加(vi,vj)
		e->adjVertex = j;
		e->weight = weight;
		e->next = graph[i].firstEdge;				//插入边节点
		graph[i].firstEdge = e;

		e = new EdgeNode;							//无向图还需要添加(vj,vi)
		e->adjVertex = i;
		e->weight = weight;
		e->next = graph[j].firstEdge;
		graph[j].firstEdge = e;
	}

	//输出添加的信息
	for (auto v : graph) {
		std::cout << "Vertex: " << v.vertex << std::endl;
		std::cout << "Edges: ";
		for (auto p = v.firstEdge; p != nullptr; p = p->next) {
			std::cout << p->adjVertex << " ";
		}

		std::cout << std::endl;
		std::cout << std::endl;
	}
}


void UndirectedGraph::DFS(std::vector<bool>& isVisted, int i) {

	isVisted[i] = true;
	std::cout << graph[i].vertex << " ";
	for (auto p = graph[i].firstEdge; p != nullptr; p = p->next) {
		if (!isVisted[p->adjVertex]) {
			DFS(isVisted, p->adjVertex);
		}
	}

}


void UndirectedGraph::DFSTraverse() {
	std::vector<bool> isVisted(vNums, false);

	for (int i = 0; i < vNums; i++) {
		if (!isVisted[i]) {
			DFS(isVisted, i);
		}
	}
	std::cout << std::endl;
}


void UndirectedGraph::BFSTraverse() {
	std::vector<bool> isVisted(vNums, false);
	std::queue<VertexNode> Q;
	VertexNode v;

	for (int i = 0; i < vNums; i++) {
		if (!isVisted[i]) {
			Q.push(graph[i]);
			isVisted[i] = true;
		}
		while (!Q.empty()) {
			v = Q.front();

			std::cout << v.vertex << " ";
			for (auto p = v.firstEdge; p != nullptr; p = p->next) {
				if (!isVisted[p->adjVertex]) {
					Q.push(graph[p->adjVertex]);
					isVisted[p->adjVertex] = true;
				}
			}
			Q.pop();

		}
	}
	std::cout << std::endl;
}



void UndirectedGraph::MiniSpanTreePrim() {
	std::vector<EdgeCost> eCost(vNums);
	for (int i = 0; i < eCost.size(); i++) {
		eCost[i].lowestcost = INFIN;
		eCost[i].parent = 0;
	}

	LowestCostUpdate(0, eCost);
	for (int i = 1; i < vNums; i++) {
		double min = INFIN;
		int nextIndex = 0;
		for (int j = 0; j < eCost.size(); j++) {
			if (eCost[j].lowestcost < min && eCost[j].lowestcost != 0) {
				min = eCost[j].lowestcost;
				nextIndex = j;
			}
		}
		int parentIndex = eCost[nextIndex].parent;
		std::cout << "(" << graph[parentIndex].vertex << "," << graph[nextIndex].vertex << ") "
			<< "weight = " << min << std::endl;
		LowestCostUpdate(nextIndex, eCost);
	}

}


void UndirectedGraph::LowestCostUpdate(int v,
	std::vector<EdgeCost>& eCost) {
	eCost[v].lowestcost = 0;				//lowestcost = 0 表示此顶点已进入最小生成树集合
	for (auto p = graph[v].firstEdge; p != nullptr; p = p->next) {
		int adjIndex = p->adjVertex;
		double cost = eCost[adjIndex].lowestcost;
		if (cost != 0 && p->weight < cost) {
			eCost[adjIndex].lowestcost = p->weight;
			eCost[adjIndex].parent = v;
		}
	}
}


void UndirectedGraph::MiniSpanTreeKruskal() {
	std::vector<ForestNode> forest(eNums);

	std::sort(edgeTable.begin(), edgeTable.end(), [](EdgeTableNode e1, EdgeTableNode e2) {
		return e1.weight < e2.weight;
		});
	for (int i = 0; i < eNums; i++) {
		MakeSet(i, forest);
	}

	for (int i = 0; i < eNums; i++) {
		int v = edgeTable[i].begin;
		int u = edgeTable[i].end;
		if (FindSet(v, forest) != FindSet(u, forest)) {
			std::cout << "(" << graph[v].vertex << ","
				<< graph[u].vertex << ") "
				<< "weight = " << edgeTable[i].weight << std::endl;
			Union(u, v, forest);
		}
	}
	std::cout << std::endl;
}



void UndirectedGraph::MakeSet(int v,
	std::vector<ForestNode>& forest) {
	forest[v].parent = v;
	forest[v].rank = 0;
}


int UndirectedGraph::FindSet(int v,
	std::vector<ForestNode>& forest) {
	if (forest[v].parent != v) {
		forest[v].parent = FindSet(forest[v].parent, forest);			//路径压缩
	}
	return forest[v].parent;									//返回集合的代表节点索引值
}


void UndirectedGraph::Union(int v, int u,
	std::vector<ForestNode>& forest) {
	int p1 = FindSet(v, forest);
	int p2 = FindSet(u, forest);
	if (forest[p1].rank > forest[p2].rank) {
		forest[p2].parent = p1;
	}
	else {
		forest[p1].parent = p2;
		if (forest[p1].rank = forest[p2].rank) {
			forest[p2].rank++;
		}
	}
}