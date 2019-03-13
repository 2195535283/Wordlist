// Wordlist.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

ifstream infile;
ofstream outfile;
char word[50];
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
	cin.getline(request, 100);
	for (int i = 0; i < sizeof(request); i++) {
		if (request[i] == '-') {
			if (request[i + 1] == 'w') {
				wflag = 1;
			}
			if (request[i + 1] == 'c') {
				cflag = 1;
			}
			if (request[i + 1] == 'r') {
				rflag = 1;
			}
        


		}

	}


	cout << request << endl;

}


int main()
{
	char swords[500][50];
	int num = 0;

	outfile.open("E://vs//solution.txt");
	get_request();

	cout << wflag << " " << cflag << endl;

	infile.open("E://vs//test.txt");
	



	while (!infile.eof()) {
		getword();
		if (strcmp(word, "") == 0)
			continue;
		strcpy_s(swords[num++], word);
		memset(word, 0, sizeof(word));
	}
	


}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
