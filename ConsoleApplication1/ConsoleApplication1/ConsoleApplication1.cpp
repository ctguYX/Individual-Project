// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<cstring>
#include<iostream>
#include<string>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<map>
#include<vector>
#include<fstream>
#include <iomanip>
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
	fclose(book);

	for (int i = 0; i < 52; i++) {
		sum[i].pinlv = sum[i].num*1.0 / sum_alphabet;
		int temp = sum[i].pinlv * 100;
		sum[i].pinlv = temp*1.0 / 100; //小数多位的时候排序时和需求不一样
	}

	sort(sum,sum + 52, cmp_solve_c);


	cout << "结果请查看debug文件夹的文件：第零步功能.txt" << endl;

	freopen("第零步功能.txt", "w", stdout);
	cout << "单词	" << "频率" << endl;

	for (int i = 0; i < 52; i++) {
		cout << sum[i].c << "	";
		printf("%.2lf\n", sum[i].pinlv);
	}
	fclose(stdout);


}
// solve -c
/*****************************/


/*****************************/
// function_first_step
struct solve_f_node {
	string word;
	ll sum;
}temp_word;
vector<solve_f_node> word;
map<string, ll>index_word;
map<string, ll>::iterator iterfind;
ll sum_word=0;
int max_size=0;
bool cmp_solve_f(solve_f_node x, solve_f_node y) {
	if (x.sum == y.sum)
		return x.word < y.word;
	else
		return x.sum > y.sum;
}

void function_first_step(string file)
{
	temp_word.sum = 1;
	ifstream book;
	book.open(file);
	string str;
	while (!book.eof()) {
		getline(book, str);
		int size = str.size();
		string test_word;
		for (int i = 0; i < size; i++) {
			if (str[i] >= 'A'&&str[i] <= 'Z') //大写字母转小写
				str[i] = str[i] + 'a' - 'A';

			if (str[i] >= 'a'&&str[i] <= 'z' || str[i] >= '0'&&str[i] <= '9') //当前位是字母或数字加到单词字符串后面
				test_word += str[i];

			else if (!test_word.empty() || (i == size - 1 && str[i] >= 'a'&&str[i] <= 'z' || str[i] >= '0'&&str[i] <= '9')) {

				iterfind = index_word.find(test_word);
				if (iterfind == index_word.end()) { //还没出现过这个单词，插入到vector中
					temp_word.word = test_word;
					word.push_back(temp_word);

					index_word[test_word] = sum_word;//单词插入到map中
					sum_word++;

					max_size = max(max_size, int(test_word.size()));
				}
				else { //有这个单词，数量+1
					word[iterfind->second].sum++;
				}
				test_word.clear();
			}
		}
	}
	book.close();
	
}
// function_first_step
/*****************************/

/*****************************/
// solve_f
void printf_solve_f()
{
	freopen("第一步功能1.txt", "w", stdout);
	cout <<setw(max_size+10) << setiosflags(ios::left) << "单词" << "数量" << endl;
	for (int i = 0; i < sum_word; i++) {
		cout << setw(max_size+10-word[i].word.size()) << setiosflags(ios::left)<< word[i].word << word[i].sum << endl;
	}
	fclose(stdout);

}

void solve_f(string file)
{
	function_first_step(file);
	sort(word.begin(), word.end(), cmp_solve_f);
	cout << "结果请查看debug文件夹的文件：第一步功能1.txt" << endl;
	printf_solve_f();
}

// solve_f
/*****************************/


int main(int argc, char* argv[])
{


	if (strcmp(argv[1], "-c") == 0) {
		string file = argv[2];
		solve_c(file);
	}
	else if (strcmp(argv[1], "-f") == 0) {
		string file = argv[2];
		solve_f(file);
	}

    return 0;
}

