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
* @brief ��������ͼ
* @param vertex				��������
* @param edge_weight[]      �ߵ�������������Ȩֵ��
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

		EdgeTableNode* et = new EdgeTableNode;		//��(vi,vj)����Ϣ����߱�
		et->begin = i;
		et->end = j;
		et->weight = weight;
		edge_table_.push_back(*et);


		EdgeNode* e = new EdgeNode;					//���(vi,vj)���ڽӱ�
		e->adjacency_vertex = j;
		e->weight = weight;

		e->next = graph_[i].first_edge;
		graph_[i].first_edge = e;

		e = new EdgeNode;							//���(vj,vi)���ڽӱ�
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
* @brief �����û����봴������ͼ
*
*/
void UndirectedGraph::CreateGraph() {
	//��ʼ����������
	for (int i = 0; i < vertex_nums_; i++) {
		VertexNode* vertex = new VertexNode;
		std::cout << "Input vertex " << i << " value:" << std::endl;
		std::cin >> vertex->data;
		vertex->first_edge = nullptr;
		graph_.push_back(*vertex);
	}

	//Ϊ���������صı���Ϣ
	for (int nums = 0; nums < edge_nums_; nums++) {
		int i, j;
		double weight;
		std::cout << "Input the i,j of (vi,vj): ";
		std::cin >> i >> j;
		std::cout << "Input the weight of (vi,vj): ";
		std::cin >> weight;

		EdgeNode* edge = new EdgeNode;					//���(vi,vj)���ڽӱ�
		edge->adjacency_vertex = j;
		edge->weight = weight;

		edge->next = graph_[i].first_edge;
		graph_[i].first_edge = edge;

		edge = new EdgeNode;							//���(vj,vi)���ڽӱ�
		edge->adjacency_vertex = i;
		edge->weight = weight;

		edge->next = graph_[j].first_edge;
		graph_[j].first_edge = edge;
	}

	//�����ӵ���Ϣ
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
*@param is_visted	 �����Ƿ񱻷��ʱ�ʶ
*@param vertex      ��������ֵ
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
*@brief Prim�㷨������С������
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
	edge_cost[v].lowest_cost = 0;				//lowestcost = 0 ��ʾ�˶����ѽ�����С����������
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
*@brief Kruskal�㷨������С������
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
		int v = edge_table_[i].begin;					//��ñ�(v,u)��β����v,ͷ����u��
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


/** Kruskal �㷨�������������鼯*/
void UndirectedGraph::MakeSet(int v,
	std::vector<ForestNode>& forest) {
	forest[v].parent = v;
	forest[v].rank = 0;
}


int UndirectedGraph::FindSet(int v,
	std::vector<ForestNode>& forest) {
	if (forest[v].parent != v) {
		forest[v].parent = FindSet(forest[v].parent, forest);	//·��ѹ��
	}
	return forest[v].parent;									//���ؼ��ϵĴ���ڵ�����ֵ
}


void UndirectedGraph::Union(int v, int u,
	std::vector<ForestNode>& forest) {
	int root1 = FindSet(v, forest);								//�ֱ���v,u���ڼ��ϵĸ��ڵ�
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