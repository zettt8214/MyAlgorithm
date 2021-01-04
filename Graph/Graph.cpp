/**
* @file			graph.cpp
* @author		tanghf
* @date			2021-01-03
* @version		V1.0
* @copyright    Copyright (c) 2021
*
*/

#include "Graph.h"


/**
* @brief 生成无向图
* @param vertex				顶点数组
* @param edge_weight[]      边的两顶点索引和权值对
* 
*/

void UndirectedGraph::CreateGraph(std::vector<std::string> vertex,
	std::pair<std::vector<int>, double> edge_weight[]) {

	for (int i = 0; i < vertex_nums_; i++) {
		VertexNode* v = new VertexNode;
		v->data = vertex[i];
		v->first_edge = nullptr;
		graph_.push_back(*v);
	}
	for (int nums = 0; nums < edge_nums_; nums++) {

		int i, j;
		double weight;
		i = edge_weight[nums].first[0];
		j = edge_weight[nums].first[1];
		weight = edge_weight[nums].second;

		EdgeTableNode* et = new EdgeTableNode;		//将(vi,vj)的信息加入边表
		et->begin = i;
		et->end = j;
		et->weight = weight;
		edge_table_.push_back(*et);


		EdgeNode* e = new EdgeNode;					//添加(vi,vj)到邻接表
		e->adjacency_vertex = j;
		e->weight = weight;

		e->next = graph_[i].first_edge;
		graph_[i].first_edge = e;

		e = new EdgeNode;							//添加(vj,vi)到邻接表
		e->adjacency_vertex = i;
		e->weight = weight;

		e->next = graph_[j].first_edge;
		graph_[j].first_edge = e;
	}


	for (auto vertex : graph_) {
		std::cout << "Vertex: " << vertex.data << std::endl;
		std::cout << "Edges: ";
		for (auto vptr = vertex.first_edge; vptr != nullptr; vptr = vptr->next) {
			std::cout << vptr->adjacency_vertex << " ";
		}

		std::cout << std::endl;
		std::cout << std::endl;
	}
}



/**
* @brief 根据用户输入创建无向图
*
*/
void UndirectedGraph::CreateGraph() {
	//初始化顶点数组
	for (int i = 0; i < vertex_nums_; i++) {
		VertexNode* vertex = new VertexNode;
		std::cout << "Input vertex " << i << " value:" << std::endl;
		std::cin >> vertex->data;
		vertex->first_edge = nullptr;
		graph_.push_back(*vertex);
	}

	//为顶点添加相关的边信息
	for (int nums = 0; nums < edge_nums_; nums++) {
		int i, j;
		double weight;
		std::cout << "Input the i,j of (vi,vj): ";
		std::cin >> i >> j;
		std::cout << "Input the weight of (vi,vj): ";
		std::cin >> weight;

		EdgeNode* edge = new EdgeNode;					//添加(vi,vj)到邻接表
		edge->adjacency_vertex = j;
		edge->weight = weight;

		edge->next = graph_[i].first_edge;
		graph_[i].first_edge = edge;

		edge = new EdgeNode;							//添加(vj,vi)到邻接表
		edge->adjacency_vertex = i;
		edge->weight = weight;

		edge->next = graph_[j].first_edge;
		graph_[j].first_edge = edge;
	}

	//输出添加的信息
	for (auto vertex : graph_) {
		std::cout << "Vertex: " << vertex.data << std::endl;
		std::cout << "Edges: ";
		for (auto vptr = vertex.first_edge; vptr != nullptr; vptr = vptr->next) {
			std::cout << vptr->adjacency_vertex << " ";
		}

		std::cout << std::endl;
		std::cout << std::endl;
	}
}

/**
*@brief DFS
*@param is_visted	 顶点是否被访问标识
*@param vertex      顶点索引值
*@birth: 2021/1/3
*/
void UndirectedGraph::DFS(std::vector<bool>& is_visted, int vertex) {

	is_visted[vertex] = true;
	std::cout << graph_[vertex].data << " ";
	for (auto p = graph_[vertex].first_edge; p != nullptr; p = p->next) {
		if (!is_visted[p->adjacency_vertex]) {
			DFS(is_visted, p->adjacency_vertex);
		}
	}

}

void UndirectedGraph::DFSTraverse() {
	std::vector<bool> isVisted(vertex_nums_, false);

	for (int i = 0; i < vertex_nums_; i++) {
		if (!isVisted[i]) {
			DFS(isVisted, i);
		}
	}
	std::cout << std::endl;
}


void UndirectedGraph::BFSTraverse() {
	std::vector<bool> is_visted(vertex_nums_, false);
	std::queue<VertexNode> Q;
	VertexNode vertex;

	for (int i = 0; i < vertex_nums_; i++) {
		if (!is_visted[i]) {
			Q.push(graph_[i]);
			is_visted[i] = true;
		}
		while (!Q.empty()) {
			vertex = Q.front();

			std::cout << vertex.data << " ";
			for (auto vptr = vertex.first_edge; vptr != nullptr; vptr = vptr->next) {
				if (!is_visted[vptr->adjacency_vertex]) {
					Q.push(graph_[vptr->adjacency_vertex]);
					is_visted[vptr->adjacency_vertex] = true;
				}
			}
			Q.pop();

		}
	}
	std::cout << std::endl;
}


/**
*@brief Prim算法生成最小生成树
*@birth: 2021/1/3
*/
void UndirectedGraph::MiniSpanTreePrim() {
	std::vector<EdgeCost> edge_cost(vertex_nums_);
	for (int i = 0; i < edge_cost.size(); i++) {
		edge_cost[i].lowest_cost = kInfinity;
		edge_cost[i].parent = 0;
	}

	LowestCostUpdate(0, edge_cost);
	for (int i = 1; i < vertex_nums_; i++) {
		double min_cost = kInfinity;
		int next_vertex = 0;
		for (int j = 0; j < edge_cost.size(); j++) {
			if (edge_cost[j].lowest_cost < min_cost && edge_cost[j].lowest_cost != 0) {
				min_cost = edge_cost[j].lowest_cost;
				next_vertex = j;
			}
		}
		int parent_vertex = edge_cost[next_vertex].parent;
		std::cout << "(" << graph_[parent_vertex].data << "," << graph_[next_vertex].data << ") "
			<< "weight = " << min_cost << std::endl;
		LowestCostUpdate(next_vertex, edge_cost);
	}

}


void UndirectedGraph::LowestCostUpdate(int v,
	std::vector<EdgeCost>& edge_cost) {
	edge_cost[v].lowest_cost = 0;				//lowestcost = 0 表示此顶点已进入最小生成树集合
	for (auto p = graph_[v].first_edge; p != nullptr; p = p->next) {
		int adjacency_vertex = p->adjacency_vertex;
		double cost = edge_cost[adjacency_vertex].lowest_cost;
		if (cost != 0 && p->weight < cost) {
			edge_cost[adjacency_vertex].lowest_cost = p->weight;
			edge_cost[adjacency_vertex].parent = v;
		}
	}
}


/**
*@brief Kruskal算法生成最小生成树
*@birth: 2021/1/3
*/
void UndirectedGraph::MiniSpanTreeKruskal() {
	std::vector<ForestNode> forest(edge_nums_);

	std::sort(edge_table_.begin(), edge_table_.end(), [](EdgeTableNode e1, EdgeTableNode e2) {
		return e1.weight < e2.weight;
		});
	for (int i = 0; i < edge_nums_; i++) {
		MakeSet(i, forest);
	}

	for (int i = 0; i < edge_nums_; i++) {
		int v = edge_table_[i].begin;					//获得边(v,u)的尾顶点v,头顶点u，
		int u = edge_table_[i].end;
		if (FindSet(v, forest) != FindSet(u, forest)) {
			std::cout << "(" << graph_[v].data << ","
				<< graph_[u].data << ") "
				<< "weight = " << edge_table_[i].weight << std::endl;
			Union(u, v, forest);
		}
	}
	std::cout << std::endl;
}


/** Kruskal 算法辅助函数：并查集*/
void UndirectedGraph::MakeSet(int v,
	std::vector<ForestNode>& forest) {
	forest[v].parent = v;
	forest[v].rank = 0;
}


int UndirectedGraph::FindSet(int v,
	std::vector<ForestNode>& forest) {
	if (forest[v].parent != v) {
		forest[v].parent = FindSet(forest[v].parent, forest);	//路径压缩
	}
	return forest[v].parent;									//返回集合的代表节点索引值
}


void UndirectedGraph::Union(int v, int u,
	std::vector<ForestNode>& forest) {
	int root1 = FindSet(v, forest);								//分别获得v,u所在集合的根节点
	int root2 = FindSet(u, forest);
	if (forest[root1].rank > forest[root2].rank) {
		forest[root2].parent = root1;
	}
	else {
		forest[root1].parent = root2;
		if (forest[root1].rank = forest[root2].rank) {
			forest[root2].rank++;
		}
	}
}