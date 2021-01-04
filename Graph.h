#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>
#include <string>


/********************************************
* 时间：2021/1/2
* 作者：tanghf
* 类简介：使用邻接表实现无向图
********************************************/

class UndirectedGraph								//邻接表实现无向图
{
private:
	
	typedef struct EdgeNode {						//边节点
		int adjVertex;
		double weight;								//权重
		EdgeNode* next;
	}EdgeNode;

	typedef struct VertexNode {						//顶点节点
		std::string vertex;							//顶点值
		EdgeNode* firstEdge;						//指向的边
	}VertexNode;

	typedef struct EdgeTableNode {					//边表节点，用于Kruskal算法，生成最小生成树
		int begin;
		int end;
		double weight;
	}EdgeTableNode;

	typedef struct EdgeCost {
		double lowestcost;
		int parent;
	}EdgeCost;

	typedef struct ForestNode {						//辅助Kruskal算法结构，用来并查集操作
		int parent;
		int rank;
	}ForestNode;

	std::vector<VertexNode> graph;					//邻接表
	std::vector<EdgeTableNode> edgeTable;			//边表

	int vNums;										//顶点数量
	int eNums;										//边数量

	//DFS辅助函数
	void DFS(std::vector<bool>& isVisted, int i);	//深度优先遍历递归调用函数

	//Prim算法辅助函数
	void LowestCostUpdate(int v, std::vector<EdgeCost>& edgecost);	//更新最小权值

	//Kruskal算法，辅助函数
	void MakeSet(int v, std::vector<ForestNode>& forest);			//将顶点设置为集合元素
	void Union(int v, int u,std::vector<ForestNode>& forest);		//合并两个顶点所在的集合
	int FindSet(int v, std::vector<ForestNode>& forest);			//查找顶点所在集合				

public:
	static const int INFIN = 65535;
	UndirectedGraph(int vn = 0,int en = 0):vNums(vn),eNums(en){}
	void CreateGraph(std::vector<std::string> vertex,		
		std::pair<std::vector<int>, double> edgeWeight[]); //静态创建无向图
	void CreateGraph();										//动态输入创建无向图
	void DFSTraverse();
	void BFSTraverse();
	void MiniSpanTreePrim();
	void MiniSpanTreeKruskal();
};
	



