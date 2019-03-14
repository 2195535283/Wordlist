// Wordlist.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <queue>
#include <stdlib.h>
using namespace std;

ifstream infile;
ofstream outfile;
char word[100];
char swords[10000][100];
int map[10000][10000] = { 0 };
int num = 0;
int wflag = 0;
int cflag = 0;
int hflag = 0;
int tflag = 0;
int rflag = 0;
char hop;
char top;

int isletter(char c) {
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
		return 1;
	}
	return 0;
}

//大写字母转换为小写
char transform_le(char c) {
	if (c >= 'A' && c <= 'Z')
		c = c + 32;
	return c;
}

// 读取单词
void getword() {
	int n = 0;
	char ctemp;
	ctemp = infile.get();
	while (isletter(ctemp)) {
		ctemp = transform_le(ctemp);
		word[n++] = ctemp;
		ctemp = infile.get();
	}
}

//控制台输入的判断
void get_request() {
	char request[100];
	char path[50];
	int plen = 0;
	cin.getline(request, 100);
	for (int i = 0; i < sizeof(request); i++) {
		if (request[i] == '-') {
			if (request[i + 1] == 'w') {
				wflag = 1;
				if (isletter(request[i + 3])) {
					i = i + 3;
					while (i < sizeof(request))
						path[plen++] = request[i++];

				}
			}
			if (request[i + 1] == 'c') {
				cflag = 1;
				if (isletter(request[i + 3])) {
					i = i + 3;
					while (i < sizeof(request))
						path[plen++] = request[i++];

				}
			}
			if (request[i + 1] == 'r') {
				rflag = 1;
				if (isletter(request[i + 3])) {
					i = i + 3;
					while (i < sizeof(request))
						path[plen++] = request[i++];

				}
			}
			if (request[i + 1] == 'h') {
				hflag = 1;
				if (isletter(request[i + 3])) {
					hop = request[i + 3];
				}
			}
			if (request[i + 1] == 't') {
				tflag = 1;
				if (isletter(request[i + 3])) {
					top = request[i + 3];
				}
			}

		}

	}
	infile.open(path);

}


void wchain() {
	char head[10000];
	char tail[10000];
	int prev[10000] = { -1 };
	int indegree[10000] = { 0 };
	int temp = 0;
	int topo[10000] = { 0 };
	int toponum = 0;
 
	queue <int> tpline;



	for (int i = 0; i < num; i++) {
		while (isletter(swords[i][temp]))
			temp++;
		head[i] = swords[i][0];
		tail[i] = swords[i][temp-1];
		temp = 0;

		//cout << head[i] << " " << tail[i] << endl;
	}
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			if (tail[j] == head[i] && j != i) {
				indegree[i]++;
				map[j][i] = 1;
			}

		}
	}
	for (int k = 0; k < num; k++) {
		if (indegree[k] == 0) {
			tpline.push(k);
			prev[k] = -1;
		}
	}
	int tmp;
	while (!tpline.empty()) {
		tmp = tpline.front();
		topo[toponum++] = tmp;
		tpline.pop();
		for (int k = 0; k < num; k++) {
			if (map[tmp][k] != 0) {
				indegree[k]--;
				if (indegree[k] == 0) {
					prev[k] = tmp;
					tpline.push(k);
				}

			}
		}



	}
	//cout << map[0][2] << endl;
	//for (int m = 0; m < toponum; m++) {
		//cout << topo[m] << " " << prev[m] << endl;
	//}

	//no -h-t
	if (hflag != 1 && tflag != 1) {
		int out[10000];
		int outnum = 0;
		out[outnum++] = topo[toponum - 1];
		while (prev[out[outnum - 1]] != -1) {
			out[outnum++] = prev[out[outnum - 1]];
		}

		for (int m = outnum-1; m >= 0; m--) {
			outfile << swords[out[m]] << endl;
		}
		


	}
	//only -t
	if (tflag == 1 && hflag != 1) {
		int out[10000];
		int outnum = 0;
		int l = 0;
		for (l = toponum - 1; l >= 0; l--) {
			if (tail[topo[l]] == top)
				break;
		}
		//cout << l << endl;

		out[outnum++] = topo[l];
		while (prev[out[outnum - 1]] != -1) {
			out[outnum++] = prev[out[outnum - 1]];
		}

		for (int m = outnum - 1; m >= 0; m--) {
			outfile << swords[out[m]] << endl;
		}

	}
	
	//only -h
	if (tflag != 1 && hflag == 1) {
		int out[10000];
		int outnum = 0;
		int count = 1;
		while (count < toponum) {
			out[outnum++] = topo[toponum - count];
			while (prev[out[outnum - 1]] != -1) {
				out[outnum++] = prev[out[outnum - 1]];
				if (head[out[outnum - 1]] == hop) {
					break;
				}
			}
			if (head[out[outnum - 1]] == hop)
				break;
			outnum = 0;
			count++;
		}
		for (int m = outnum - 1; m >= 0; m--) {
			outfile << swords[out[m]] << endl;
		}

	}

}
void cchain() {
	;

}


void judge() {
	if (wflag == 1 && cflag != 1) {
		wchain();
	}
	else if (wflag != 1 && cflag == 1) {
		cchain();
	}
	else if (wflag == 1 && cflag == 1) {
		cout << "ERROR, -w and -c can not be both requested!" << endl;
	}
}




int main(int argv, char *argc[])
{


	outfile.open("E://solution.txt");
	get_request();


	
	while (!infile.eof()) {
		getword();
		if (strcmp(word, "") == 0)
			continue;
		strcpy_s(swords[num++], word);
		memset(word, 0, sizeof(word));
	}

	judge();



}

