#include "str_match.h"
#include <cmath>
#include <iostream>
using namespace std;

/*
* @brief �����ַ���ƥ��
* @return ����pattern��textƥ��ɹ�������ֵ����δƥ��ɹ������ؿ�����
*/
vector<int> NaiveStringMatch(string text,string pattern) {
	vector<int> matched_index;
	int t_len = text.size();
	int p_len = pattern.size();

	if (t_len < p_len) {
		return matched_index;
	}
	for (int i = 0; i < t_len - p_len + 1; i++) {
		for (int j = 0; j < p_len; j++) {
			if (text[i + j] != pattern[j]) {
				break;
			}
			if (j == p_len - 1) {
				matched_index.push_back(i);
			}
		}
	}
	return matched_index;
}

/*
* @brief Rabin-Karp ƥ���㷨
* @return ����pattern��textƥ��ɹ�������ֵ����δƥ��ɹ������ؿ�����
*/
vector<int> RabinKarpMatch(string text, string pattern) {
	
	vector<int> matched_index;
	int t_len = text.size();
	int p_len = pattern.size();
	
	/* ��128Ϊ�ף�ƥ������ASCII���ַ� ����ѡ�� 113 */
	int d = 128;
	int q = 113;
	int h = pow(d, p_len - 1);
	h = fmod(h,113);

	int t_hash = 0;
	int p_hash = 0;
	for (int i = 0; i < p_len; i++) {
		p_hash = fmod((d * p_hash + pattern[i]) , q);
		t_hash = fmod((d * t_hash + pattern[i]), q);
	}
	cout << "p_hash: "<< p_hash << endl;
	for (int i = 0; i < t_len - p_len + 1; i++) {
		cout <<i<<".t_hash:" << t_hash << endl;
		if (t_hash == p_hash) {
			for (int j = 0; j < p_len; j++) {
				if (text[i + j] != pattern[j]) {
					break;
				}
				if (j == p_len - 1) {
					matched_index.push_back(i);
				}
			}
		}

		if (i < t_len - p_len) {
			t_hash = fmod((d * (t_hash - text[i] * h) + text[i + p_len]) , q);
			while (t_hash < 0) {
				t_hash += q;
			}
		}
	}
	return matched_index;
}



static vector<int> KmpPrefixComputing(string pattern) {
	vector<int> prefix(pattern.size() + 1, 0);

	/* pattern����ƥ���ַ��� */
	int k = 0; 
	prefix[0] = k;

	/* ��������pattern[0:] ȡƥ�� pattern[1:] ��pattern[0:i]��׺�Ĺ���pattern���ǰ׺ */
	for (int i = 1; i < pattern.size(); i++) {
		while (k > 0 && pattern[k] != pattern[i]) {
			k = prefix[k];
		}
		if (pattern[k] == pattern[i]) {
			k++;
		}
		prefix[i] = k;
	}
	return prefix;
}

/*
* @brief KMP ƥ���㷨
* @return ����pattern��textƥ��ɹ�������ֵ����δƥ��ɹ������ؿ�����
*/
vector<int> KmpMatch(string text, string pattern) {
	vector<int> matched_index;
	vector<int> prefix = KmpPrefixComputing(pattern);

	int k = 0;
	for (int i = 0; i < text.size(); i++) {
		while (k > 0 && pattern[k] != text[i]) {
			k = prefix[k];
		}
		if (pattern[k] == text[i]) {
			k++;
		}
		if (k == pattern.size()) {
			matched_index.push_back(i - pattern.size() + 1);
			k = prefix[k];
		}
	}
	return matched_index;
}