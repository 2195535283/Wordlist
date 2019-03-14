// zuichangdancilian.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include "stdlib.h"
#include <string>
using  std::string;
using namespace std;
#include "stdio.h"

void getcchain(int comm, char spc1, char spc2, char *cpath)
{
	FILE *fp;
	char * fname = {};
	char c = ' ';
	int count = 0;
	int vcount = 0;
	char head = ' ';
	char tail = ' ';
	int wordlen = 0;
	int huanchong = 0;
	string word[11000];
	int tmp = 0;
	int chu[27];
	int ru[27];
	int exist[27];
	int lian[28][28];
	int vis[28];  //拓扑序列
	string dis[28][28];
	int Dis[28][28];
	int father[28][2];
	int max = 0;
	string path[10000];
	int pathlen = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	int ruflag[27][27];

	//1-h,2-c,3-h+w,4-t+w,5-h+c,6-t+c,7-h+t+w,8-h+t+c


	for (i = 0; i < 11000; i++) {
		word[i] = "";
	}
	for (i = 0; i < 28; i++) {
		vis[i] = 0;
	}

	for (i = 0; i < 27; i++) {
		chu[i] = 0;
		ru[i] = 0;
		exist[i] = 0;
		for (int j = 0; j < 27; j++) {
			lian[i][j] = 0;
		}
	}

	for (i = 1; i < 27; i++) {
		for (j = 1; j < 27; j++) {
			ruflag[i][j] = 0;
		}
	}

	for (i = 0; i < 28; i++) {
		lian[0][i] = 1;
		lian[i][27] = 1;
	}
	for (i = 0; i < 28; i++) {
		father[i][0] = 0;
		father[i][1] = 0;
		for (int j = 0; j < 28; j++) {
			dis[i][j] = "";
			Dis[i][j] = 0;
		}
	}

	for (i = 0; i < 10000; i++) {
		path[i] = "";
	}

	if ((fopen_s(&fp, cpath, "r")) != 0) {
		printf("file not exist\n");
	}


	for (i = 0; i < 11000; i++) {
		while ((c = fgetc(fp)) != EOF && isalpha(c)) {

			if ('A' <= c && c <= 'Z') {
				c = c - 'A' + 'a';

			}
			word[i] = word[i] + c;
		}

		if (c == '\n' && (c = fgetc(fp)) == EOF) {

			count = i;
		}
		else ungetc(c, fp);
		if (c == EOF) {
			count = i + 1;

			break;
		}
	}


	for (i = 0; i < count; i++) {
		head = word[i][0];
		wordlen = word[i].length();
		tail = word[i][wordlen - 1];
		exist[tail - 'a' + 1] = 1;
		exist[head - 'a' + 1] = 1;

		if (head == tail) {
			if (wordlen - 1 > Dis[head - 'a' + 1][head - 'a' + 1]) {
				if (comm == 2 || comm == 5 || comm == 6 || comm == 8) {
					Dis[head - 'a' + 1][head - 'a' + 1] = wordlen;
					dis[head - 'a' + 1][head - 'a' + 1] = word[i];
				}
				else if (comm == 1 || comm == 3 || comm == 4 || comm == 7) {
					Dis[head - 'a' + 1][head - 'a' + 1] = 1;
					dis[head - 'a' + 1][head - 'a' + 1] = word[i];
				}
			}
			continue;
		}

		lian[head - 'a' + 1][tail - 'a' + 1] = 1;
		if (wordlen - 1 > Dis[head - 'a' + 1][tail - 'a' + 1]) {
			if (comm == 2 || comm == 5 || comm == 6 || comm == 8) {
				Dis[head - 'a' + 1][tail - 'a' + 1] = wordlen;
				dis[head - 'a' + 1][tail - 'a' + 1] = word[i];
			}
			else if (comm == 1 || comm == 3 || comm == 4 || comm == 7) {
				Dis[head - 'a' + 1][tail - 'a' + 1] = 1;
				dis[head - 'a' + 1][tail - 'a' + 1] = word[i];

			}
		}


		if (ruflag[head - 'a' + 1][tail - 'a' + 1] == 0) {
			ru[tail - 'a' + 1]++;
			ruflag[head - 'a' + 1][tail - 'a' + 1] = 1;
		}



	}




	vcount = 1;
	for (i = 1; i < 27; i++) {
		for (j = 1; j < 27; j++) {
			if (ru[j] == 0 && exist[j] == 1) {
				tmp = j;
				vis[vcount++] = j;
				ru[j]--;
				break;
			}
		}

		for (int k = 1; k < 27; k++) {
			if (lian[tmp][k])
				ru[k]--;
		}
	}





	int vnum = 0;
	int vnum_ = 0;
	vis[0] = 0;
	vis[vcount] = 27;
	for (i = 0; i < 28; i++) {
		lian[i][i] = 1;
	}

	if (comm == 1 || comm == 2) {////-w,-c
		vnum = vcount;

		for (i = 0; i <= vnum; i++) {
			for (j = 0; j <= i; j++) {
				if (lian[vis[j]][vis[i]] != 0 && (Dis[0][vis[j]] + Dis[vis[j]][vis[i]] > Dis[0][vis[i]])) {
					Dis[0][vis[i]] = Dis[0][vis[j]] + Dis[vis[j]][vis[i]];
					//cout << "当前节点： " << vis[i] << "父节点是： " << vis[j] << "长度达到了： " << Dis[0][vis[i]] << "\n";
					if (i != j) {
						father[vis[i]][0] = vis[j];
					}
					else {
						//cout << "自环节点： " << vis[i] << "\n";
						father[vis[i]][1] = vis[j];
					}

				}
				if (Dis[0][vis[i]] > max) {
					max = Dis[0][vis[i]];
				}
			}
		}

	}

	if (comm == 3 || comm == 5) {////-w+h,-c+h
		for (i = 1; i < vcount; i++) {
			if (vis[i] - 1 + 'a' == spc1) {
				vnum = i;
			}
		}

		for (i = 0; i <= vcount; i++) {
			for (j = 0; j <= i; j++) {
				if (lian[vis[j]][vis[i]] != 0 && (Dis[0][vis[j]] + Dis[vis[j]][vis[i]] > Dis[0][vis[i]])) {
					Dis[0][vis[i]] = Dis[0][vis[j]] + Dis[vis[j]][vis[i]];
					//cout << "当前节点： " << vis[i] << "父节点是： " << vis[j] << "长度达到了： " << Dis[0][vis[i]] << "\n";
					if (i != j) {
						father[vis[i]][0] = vis[j];
					}
					else {
						//cout << "自环节点： " << vis[i] << "\n";
						father[vis[i]][1] = vis[j];
					}

				}
				if (Dis[0][vis[i]] > max) {
					max = Dis[0][vis[i]];
				}
			}
		}

	}


	if (comm == 4 || comm == 6) {////-w+t,-c+t
		for (i = 1; i < vcount; i++) {
			if (vis[i] - 1 + 'a' == spc2) {
				vnum = i;
			}
		}

		for (i = 0; i <= vnum; i++) {
			for (j = 0; j <= i; j++) {
				if (lian[vis[j]][vis[i]] != 0 && (Dis[0][vis[j]] + Dis[vis[j]][vis[i]] > Dis[0][vis[i]])) {
					Dis[0][vis[i]] = Dis[0][vis[j]] + Dis[vis[j]][vis[i]];
					//cout << "当前节点： " << vis[i] << "父节点是： " << vis[j] << "长度达到了： " << Dis[0][vis[i]] << "\n";
					if (i != j) {
						father[vis[i]][0] = vis[j];
					}
					else
						father[vis[i]][1] = vis[j];
				}
				if (Dis[0][vis[i]] > max) {
					max = Dis[0][vis[i]];
				}
			}
		}

	}

	if (comm == 7 || comm == 8) {////-w+h+t,-c+h+t
		for (i = 1; i < vcount; i++) {
			if (vis[i] - 1 + 'a' == spc1) {
				vnum = i;
			}

			if (vis[i] - 1 + 'a' == spc2) {
				vnum_ = i;
			}
		}

		for (i = 0; i <= vcount; i++) {
			for (j = 0; j <= i; j++) {
				if (lian[vis[j]][vis[i]] != 0 && (Dis[0][vis[j]] + Dis[vis[j]][vis[i]] > Dis[0][vis[i]])) {
					Dis[0][vis[i]] = Dis[0][vis[j]] + Dis[vis[j]][vis[i]];
					if (i != j) {
						father[vis[i]][0] = vis[j];
					}
					else
						father[vis[i]][1] = vis[j];
				}
				if (Dis[0][vis[i]] > max) {
					max = Dis[0][vis[i]];
				}
			}
		}

	}

	//printf("max is: %d\n", max);
	int i1 = 0;
	int i0 = 0;


	if (comm == 1 || comm == 2) {////-w,-c
		for (i0 = father[vis[vcount]][0], i1 = father[i0][1]; i0 > 0; ) {
			if (i1 != 0) {
				printf("有自环\n");
				path[pathlen] = dis[i1][i1];
				pathlen = pathlen + 1;
			}
			if (father[i0][0] > 0) {
				path[pathlen] = dis[father[i0][0]][i0];
				pathlen = pathlen + 1;
			}
			i0 = father[i0][0];
			i1 = father[i0][1];

		}
	}

	if (comm == 3 || comm == 5) {////-w+h,-c+h
		for (i = 1; i < vcount; i++) {
			if (vis[i] - 1 + 'a' == spc1) {
				vnum = i;
			}
		}

		for (i0 = father[vis[vcount]][0], i1 = father[i0][1]; ; ) {
			if (i1 != 0) {
				printf("有自环\n");
				path[pathlen] = dis[i1][i1];
				pathlen = pathlen + 1;
			}
			if (father[i0][0] != vis[vnum]) {
				path[pathlen] = dis[father[i0][0]][i0];
				pathlen = pathlen + 1;
			}
			else {
				path[pathlen++] = dis[father[i0][0]][i0];
				i1 = father[vis[vnum]][1];
				if (i1 != 0) {
					printf("有自环\n");
					path[pathlen] = dis[i1][i1];
					pathlen = pathlen + 1;
				}
				break;
			}
			i0 = father[i0][0];
			i1 = father[i0][1];

		}

	}

	if (comm == 4 || comm == 6) {////-w+t,-c+t
		for (i = 1; i < vcount; i++) {
			if (vis[i] - 1 + 'a' == spc2) {
				vnum = i;
			}
		}

		for (i0 = vis[vnum], i1 = father[i0][1]; i0 > 0; ) {
			if (i1 != 0) {
				printf("有自环\n");
				path[pathlen] = dis[i1][i1];
				pathlen = pathlen + 1;
			}
			if (father[i0][0] > 0) {
				path[pathlen] = dis[father[i0][0]][i0];
				pathlen = pathlen + 1;
			}
			i0 = father[i0][0];
			i1 = father[i0][1];

		}

	}

	if (comm == 7 || comm == 8) {////-w+h+t,-c+h+t
		for (i = 1; i < vcount; i++) {
			if (vis[i] - 1 + 'a' == spc1) {
				vnum = i;
			}

			if (vis[i] - 1 + 'a' == spc2) {
				vnum_ = i;
			}
		}

		for (i0 = vis[vnum_], i1 = father[i0][1];; ) {
			if (i1 != 0) {
				printf("有自环\n");
				path[pathlen] = dis[i1][i1];
				pathlen = pathlen + 1;
			}
			if (father[i0][0] != vis[vnum]) {
				path[pathlen] = dis[father[i0][0]][i0];
				pathlen = pathlen + 1;
			}
			else {
				path[pathlen++] = dis[father[i0][0]][i0];
				i1 = father[vis[vnum]][1];
				if (i1 != 0) {
					printf("有自环\n");
					path[pathlen] = dis[i1][i1];
					pathlen = pathlen + 1;
				}
				break;
			}

			i0 = father[i0][0];
			i1 = father[i0][1];

		}

	}

	ofstream ofile;
	ofile.open("solution.txt");
	for (i = pathlen - 1; i >= 0; i--) {
		ofile << path[i] << "\n";
	}

}

