/**
* @file			graph.h
* @author		tanghf
* @date			2021-01-03
* @version		V1.0
* @copyright    Copyright (c) 2021
*/
#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>
#include <string>

/**
 *  @brief 无向图，包含创建无向图、DFS、BFS、最小生成树（Prim 和 Kruskal算法）
 */ 
class UndirectedGraph								
{
private:
	
	typedef struct EdgeNode {						///  @brief 边节点
		int adjacency_vertex;						///< 与顶点邻接的另一个顶点的索引值
		double weight;								///< 权
		EdgeNode* next;
	}EdgeNode;

	typedef struct VertexNode {						///  @brief 顶点节点
		std::string data;							///< 顶点值
		EdgeNode* first_edge;						///< 指向的边
	}VertexNode;

	typedef struct EdgeTableNode {					///  @brief 边表节点，用于Kruskal算法，生成最小生成树
		int begin;									///< 起始顶点
		int end;									///< 结束顶点
		double weight;
	}EdgeTableNode;

	typedef struct EdgeCost {						/// @brief 辅助Prim算法
		double lowest_cost;
		int parent;
	}EdgeCost;

	typedef struct ForestNode {						/// @brief 辅助Kruskal算法结构，用来并查集操作
		int parent;
		int rank;
	}ForestNode;

	std::vector<VertexNode> graph_;					///< 邻接表
	std::vector<EdgeTableNode> edge_table_;			///< 边表

	int vertex_nums_;								///< 顶点数量
	int edge_nums_;									///< 边数量

	
	void DFS(std::vector<bool>& isVisted, int i);	///< 深度优先遍历递归调用函数

	
	void LowestCostUpdate(int v, std::vector<EdgeCost>& edgecost);	///< Prim算法辅助函数，更新最小权值

	/** Kruskal算法，辅助函数 */
	void MakeSet(int v, std::vector<ForestNode>& forest);			///< 将顶点设置为集合元素
	void Union(int v, int u,std::vector<ForestNode>& forest);		///< 合并两个顶点所在的集合
	int FindSet(int v, std::vector<ForestNode>& forest);			///< 查找顶点所在集合				

public:
	static const int kInfinity = 65535;
	UndirectedGraph(int vn ,int en):vertex_nums_(vn), edge_nums_(en){} ///< 指定定点数、边数
	void CreateGraph(std::vector<std::string> vertex,		
		std::pair<std::vector<int>, double> edge_weight[]); ///< 静态创建无向图

	void CreateGraph();										///< 动态输入创建无向图

	void DFSTraverse();										///< 深度优先遍历
	void BFSTraverse();										///< 广度优先遍历
	void MiniSpanTreePrim();								///< Prim算法生成最小生成树
	void MiniSpanTreeKruskal();								///< Kruskal算法生成最小生成树
};
	
#endif // !GRAPH_H_


