// Wordlist.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <queue>
#include <stdlib.h>
#include "wordchain.cpp"
using namespace std;

ifstream infile;
ofstream outfile;
char word[100];
char cpath[100];
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
	strcpy_s(cpath, path);
	//cout << cpath << endl;
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
			if (head[out[outnum - 1]] == hop) {
				break;
			}
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
	if (hflag != 1 && tflag != 1) {
		getcchain(2, 'a', 'a', cpath);
	}
	if (hflag == 1 && tflag != 1) {
		getcchain(5, hop, 'a', cpath);
	}
	if (hflag != 1 && tflag == 1) {
		getcchain(6, 'a', top, cpath);
	}
	if (hflag == 1 && tflag == 1) {
		getcchain(8, hop, top, cpath);
	}
}

void rchain() {
	int head[10000];
	int tail[10000];
	int temp = 0;

	for (int i = 0; i < num; i++) {
		while (isletter(swords[i][temp]))
			temp++;
		head[i] = swords[i][0];
		tail[i] = swords[i][temp - 1];
		temp = 0;

		//cout << head[i] << " " << tail[i] << endl;
	}

	//no -h-t
	if (hflag != 1 && tflag != 1) {
		int t = 0;
		int length1 = 0;
		int nowlen = 0;
		int nowloca = 0;
		int loca[30] = { 0 };
		int nowca[30] = { 0 };
		while (t < num) {
			char tt = tail[t];
			loca[length1] = t;

			for (int j = 0; j < num; j++) {
				if (head[j] == tt && j != t) {
					int jxflag = 0;
					for (int ttt = 0; ttt <= length1; ttt++) {
						if (j == loca[ttt])
							jxflag = 1;
					}
					if (jxflag == 1)
						continue;

					tt = tail[j];

					length1++;
					loca[length1] = j;
					j = -1;
				}
			}

			if (nowlen < length1) {
				nowlen = length1;
				nowloca = t;
				for (int k = 0; k <= nowlen; k++)
					nowca[k] = loca[k];
			}
			length1 = 0;
			memset(loca, 0, 30 * sizeof(int));
			t++;
		}

		for (int m = 0; m <= nowlen; m++) {
			outfile << swords[nowca[m]] << endl;
		}

	}
	//only -h
	else if (hflag == 1 && tflag != 1) {
		int t = 0;
		int tloca[10000];
		int tnum = 0;
		int length1 = 0;
		int nowlen = 0;
		int nowloca = 0;
		int loca[30] = { 0 };
		int nowca[30] = { 0 };


		for (int i = 0; i < num; i++) {
			if (head[i] == hop) {
				tloca[tnum++] = i;
			}
		}

		while (t < tnum) {
			int tempt;
			tempt = tloca[t];
			char tt = tail[tempt];
			loca[length1] = tempt;

			for (int j = 0; j < num; j++) {
				if (head[j] == tt && j != tempt) {
					int jxflag = 0;
					for (int ttt = 0; ttt <= length1; ttt++) {
						if (j == loca[ttt])
							jxflag = 1;
					}
					if (jxflag == 1)
						continue;

					tt = tail[j];

					length1++;
					loca[length1] = j;
					j = -1;
				}
			}

			if (nowlen < length1) {
				nowlen = length1;
				nowloca = tempt;
				for (int k = 0; k <= nowlen; k++)
					nowca[k] = loca[k];
			}
			length1 = 0;
			memset(loca, 0, 30 * sizeof(int));
			t++;


		}
		if (nowlen == 0) {
			outfile << swords[tloca[0]] << endl;
		}
		else {
			for (int m = 0; m <= nowlen; m++) {
				if (tnum != 0)
					outfile << swords[nowca[m]] << endl;
			}
		}
	}

	//only -t
	else if (hflag != 1 && tflag == 1) {
		int t = 0;
		int tloca[10000];
		int tnum = 0;
		int length1 = 0;
		int nowlen = 0;
		int nowloca = 0;
		int loca[30] = { 0 };
		int nowca[30] = { 0 };


		for (int i = 0; i < num; i++) {
			if (tail[i] == top) {
				tloca[tnum++] = i;
			}
		}

		while (t < tnum) {
			int tempt;
			tempt = tloca[t];
			char tt = head[tempt];
			loca[length1] = tempt;

			for (int j = 0; j < num; j++) {
				if (tail[j] == tt && j != tempt) {
					int jxflag = 0;
					for (int ttt = 0; ttt <= length1; ttt++) {
						if (j == loca[ttt])
							jxflag = 1;
					}
					if (jxflag == 1)
						continue;

					tt = head[j];

					length1++;
					loca[length1] = j;
					j = -1;
				}
			}

			if (nowlen < length1) {
				nowlen = length1;
				nowloca = tempt;
				for (int k = 0; k <= nowlen; k++)
					nowca[k] = loca[k];
			}
			length1 = 0;
			memset(loca, 0, 30 * sizeof(int));
			t++;


		}
		if (nowlen == 0) {
			outfile << swords[tloca[0]] << endl;
		}
		else {
			for (int m = nowlen; m >= 0; m--) {
				if (tnum != 0)
					outfile << swords[nowca[m]] << endl;
			}
		}
	}
}

void judge() {
	if (wflag == 1 && cflag != 1 && rflag != 1) {
		wchain();
	}
	else if (wflag != 1 && cflag == 1 && rflag != 1) {
		cchain();
	}
	else if (wflag == 1 && cflag == 1 && rflag != 1) {
		cout << "ERROR, -w and -c can not be both requested!" << endl;
	}
	else if (rflag == 1) {
		rchain();
	}
}




int main(int argv, char *argc[])
{
	for (int ar = 1; ar < argv; ar++) {
		if (argc[ar][0] == '-') {
			if (argc[ar][1] == 'w') {
				wflag = 1;
				if (argc[ar + 1][0] != '-') {
					strcpy_s(cpath, argc[ar + 1]);
				}
			}
			else if (argc[ar][1] == 'c') {
				cflag = 1;
				if (argc[ar + 1][0] != '-') {
					strcpy_s(cpath, argc[ar + 1]);
				}
			}
			else if (argc[ar][1] == 'r') {
				rflag = 1;
			}
			else if (argc[ar][1] == 't') {
				tflag = 1;
				top = argc[ar + 1][0];
			}
			else if (argc[ar][1] == 'h') {
				hflag = 1;
				hop = argc[ar + 1][0];
			}
		}


	}
    
	infile.open(cpath);
	outfile.open("solution.txt");
	//get_request();


	
	while (!infile.eof()) {
		getword();
		if (strcmp(word, "") == 0)
			continue;
		strcpy_s(swords[num++], word);
		memset(word, 0, sizeof(word));
	}
	cout << "end" << endl;
	judge();



}

