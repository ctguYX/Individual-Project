// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<cstring>
#include<iostream>
#include<string>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;


/*****************************/
// solve -c
struct solve_c_node {
	ll num;
	char c;
	double pinlv;
};
bool cmp_solve_c(solve_c_node x, solve_c_node y) {
	if (x.pinlv == y.pinlv)
		return x.c < y.c;
	else
		return x.pinlv > y.pinlv;
}
void solve_c(string file)
{
	FILE *book = fopen(file.c_str(), "r");
	char str[1000];
	ll sum_alphabet = 0;

	solve_c_node sum[52];
	for (int i = 0; i < 26; i++) {
		sum[i].num = 0;
		sum[i].c = i + 'A';
		sum[i].pinlv = 0.0;
	}
	for (int i = 26; i < 52; i++) {
		sum[i].num = 0;
		sum[i].c = i + 'a' - 26;
		sum[i].pinlv = 0.0;
	}

	while (fscanf(book, "%s", str) != EOF) {
		for (int i = 0; str[i] != '\0'; i++) {
			if (str[i] >= 'a' && str[i] <= 'z' ) {
				sum_alphabet++;
				sum[str[i] - 'a' + 26].num++;
			}
			else if (str[i] >= 'A' && str[i] <= 'Z') {
				sum_alphabet++;
				sum[str[i] - 'A'].num++;
			}
		}
	}

	for (int i = 0; i < 52; i++) {
		sum[i].pinlv = sum[i].num*1.0 / sum_alphabet;
		int temp = sum[i].pinlv * 100;
		sum[i].pinlv = temp*1.0 / 100; //小数多位的时候排序时和需求不一样
	}

	sort(sum,sum + 52, cmp_solve_c);
	cout << file << "文本文件中 26 字母出现的频率如下" << endl;
	for (int i = 0; i < 52; i++) {
		cout << sum[i].c << "的频率为";
		printf("%.2lf\n", sum[i].pinlv);
	}

}
// solve -c
/*****************************/


int main(int argc, char* argv[])
{
	//for (int i = 0; i<argc; i++)
	//	cout << argv[i] << endl;

	if (strcmp(argv[1], "-c") == 0) {
		string file = argv[2];
		solve_c(file);
	}


    return 0;
}

