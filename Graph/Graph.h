#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>
#include <string>


/********************************************
* ʱ�䣺2021/1/2
* ���ߣ�tanghf
* ���飺ʹ���ڽӱ�ʵ������ͼ
********************************************/

class UndirectedGraph								//�ڽӱ�ʵ������ͼ
{
private:
	
	typedef struct EdgeNode {						//�߽ڵ�
		int adjVertex;
		double weight;								//Ȩ��
		EdgeNode* next;
	}EdgeNode;

	typedef struct VertexNode {						//����ڵ�
		std::string vertex;							//����ֵ
		EdgeNode* firstEdge;						//ָ��ı�
	}VertexNode;

	typedef struct EdgeTableNode {					//�߱�ڵ㣬����Kruskal�㷨��������С������
		int begin;
		int end;
		double weight;
	}EdgeTableNode;

	typedef struct EdgeCost {
		double lowestcost;
		int parent;
	}EdgeCost;

	typedef struct ForestNode {						//����Kruskal�㷨�ṹ���������鼯����
		int parent;
		int rank;
	}ForestNode;

	std::vector<VertexNode> graph;					//�ڽӱ�
	std::vector<EdgeTableNode> edgeTable;			//�߱�

	int vNums;										//��������
	int eNums;										//������

	//DFS��������
	void DFS(std::vector<bool>& isVisted, int i);	//������ȱ����ݹ���ú���

	//Prim�㷨��������
	void LowestCostUpdate(int v, std::vector<EdgeCost>& edgecost);	//������СȨֵ

	//Kruskal�㷨����������
	void MakeSet(int v, std::vector<ForestNode>& forest);			//����������Ϊ����Ԫ��
	void Union(int v, int u,std::vector<ForestNode>& forest);		//�ϲ������������ڵļ���
	int FindSet(int v, std::vector<ForestNode>& forest);			//���Ҷ������ڼ���				

public:
	static const int INFIN = 65535;
	UndirectedGraph(int vn = 0,int en = 0):vNums(vn),eNums(en){}
	void CreateGraph(std::vector<std::string> vertex,		
		std::pair<std::vector<int>, double> edgeWeight[]); //��̬��������ͼ
	void CreateGraph();										//��̬���봴������ͼ
	void DFSTraverse();
	void BFSTraverse();
	void MiniSpanTreePrim();
	void MiniSpanTreeKruskal();
};
	



