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
 *  @brief ����ͼ��������������ͼ��DFS��BFS����С��������Prim �� Kruskal�㷨��
 */ 
class UndirectedGraph								
{
private:
	
	typedef struct EdgeNode {						///  @brief �߽ڵ�
		int adjacency_vertex;						///< �붥���ڽӵ���һ�����������ֵ
		double weight;								///< Ȩ
		EdgeNode* next;
	}EdgeNode;

	typedef struct VertexNode {						///  @brief ����ڵ�
		std::string data;							///< ����ֵ
		EdgeNode* first_edge;						///< ָ��ı�
	}VertexNode;

	typedef struct EdgeTableNode {					///  @brief �߱�ڵ㣬����Kruskal�㷨��������С������
		int begin;									///< ��ʼ����
		int end;									///< ��������
		double weight;
	}EdgeTableNode;

	typedef struct EdgeCost {						/// @brief ����Prim�㷨
		double lowest_cost;
		int parent;
	}EdgeCost;

	typedef struct ForestNode {						/// @brief ����Kruskal�㷨�ṹ���������鼯����
		int parent;
		int rank;
	}ForestNode;

	std::vector<VertexNode> graph_;					///< �ڽӱ�
	std::vector<EdgeTableNode> edge_table_;			///< �߱�

	int vertex_nums_;								///< ��������
	int edge_nums_;									///< ������

	
	void DFS(std::vector<bool>& isVisted, int i);	///< ������ȱ����ݹ���ú���

	
	void LowestCostUpdate(int v, std::vector<EdgeCost>& edgecost);	///< Prim�㷨����������������СȨֵ

	/** Kruskal�㷨���������� */
	void MakeSet(int v, std::vector<ForestNode>& forest);			///< ����������Ϊ����Ԫ��
	void Union(int v, int u,std::vector<ForestNode>& forest);		///< �ϲ������������ڵļ���
	int FindSet(int v, std::vector<ForestNode>& forest);			///< ���Ҷ������ڼ���				

public:
	static const int kInfinity = 65535;
	UndirectedGraph(int vn ,int en):vertex_nums_(vn), edge_nums_(en){} ///< ָ��������������
	void CreateGraph(std::vector<std::string> vertex,		
		std::pair<std::vector<int>, double> edge_weight[]); ///< ��̬��������ͼ

	void CreateGraph();										///< ��̬���봴������ͼ

	void DFSTraverse();										///< ������ȱ���
	void BFSTraverse();										///< ������ȱ���
	void MiniSpanTreePrim();								///< Prim�㷨������С������
	void MiniSpanTreeKruskal();								///< Kruskal�㷨������С������
};
	
#endif // !GRAPH_H_


