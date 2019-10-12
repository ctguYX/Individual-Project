// ConsoleApplication1.cpp : �������̨Ӧ�ó������ڵ㡣
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
#include <io.h>
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
		sum[i].pinlv = temp*1.0 / 100; //С����λ��ʱ������ʱ������һ��
	}

	sort(sum,sum + 52, cmp_solve_c);


	cout << "�����鿴debug�ļ��е��ļ������㲽����.txt" << endl;

	freopen("���㲽����.txt", "w", stdout);
	cout << "����	" << "Ƶ��" << endl;

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
map<string, ll>stopWord;
map<string, ll>::iterator iter_stopWord;
ll sum_word=0;
int max_size=0;
bool cmp_solve_f(solve_f_node x, solve_f_node y) {
	if (x.sum == y.sum)
		return x.word < y.word;
	else
		return x.sum > y.sum;
}

void function_first_step(string file,bool _x=false)
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
			if (str[i] >= 'A'&&str[i] <= 'Z') //��д��ĸתСд
				str[i] = str[i] + 'a' - 'A';

			if (str[i] >= 'a'&&str[i] <= 'z' || str[i] >= '0'&&str[i] <= '9') //��ǰλ����ĸ�����ּӵ������ַ�������
				test_word += str[i];

			else if (!test_word.empty() || (i == size - 1 && str[i] >= 'a'&&str[i] <= 'z' || str[i] >= '0'&&str[i] <= '9')) {
				if (_x) { //_x����ȥ��ͣ�ʱ��еĵ��� ���test_word������ģ�clearȻ��continue
					iter_stopWord = stopWord.find(test_word);
					if (iter_stopWord == stopWord.end()) { //����ͣ�ʱ�û���������

					}
					else {
						test_word.clear();
						continue;
					}
				}
				iterfind = index_word.find(test_word);
				if (iterfind == index_word.end()) { //��û���ֹ�������ʣ����뵽vector��
					temp_word.word = test_word;
					word.push_back(temp_word);

					index_word[test_word] = sum_word;//���ʲ��뵽map��
					sum_word++;

					max_size = max(max_size, int(test_word.size()));
				}
				else { //��������ʣ�����+1
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
	freopen("��һ������1.txt", "w", stdout);
	cout <<setw(max_size+10) << setiosflags(ios::left) << "����" << "����" << endl;
	for (int i = 0; i < sum_word; i++) {
		cout << setw(max_size+10-word[i].word.size()) << setiosflags(ios::left)<< word[i].word << word[i].sum << endl;
	}
	fclose(stdout);

}

void solve_f(string file)
{
	function_first_step(file);
	sort(word.begin(), word.end(), cmp_solve_f);
	cout << "�����鿴debug�ļ��е��ļ�����һ������1.txt" << endl;
	printf_solve_f();
}

// solve_f
/*****************************/




/*****************************/
// solve_d
void getAllFiles(string path, vector<string>& files)
{
	// �ļ����
	long hFile = 0;
	// �ļ���Ϣ
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
		do {
			// �����ļ���ȫ·��
			files.push_back(p.assign(path).append("\\").append(fileinfo.name));

		} while (_findnext(hFile, &fileinfo) == 0);  //Ѱ����һ�����ɹ�����0������-1
		_findclose(hFile);
	}
}

void getAllFiles_zi_folder(string path, vector<string>& files) {
	//�ļ����
	long hFile = 0;
	//�ļ���Ϣ
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
		do {
			if ((fileinfo.attrib & _A_SUBDIR)) {  //�Ƚ��ļ������Ƿ����ļ���
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
					files.push_back(p.assign(path).append("\\").append(fileinfo.name));
					//�ݹ�����
					getAllFiles(p.assign(path).append("\\").append(fileinfo.name), files);
				}
			}
			else {
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);  //Ѱ����һ�����ɹ�����0������-1
		_findclose(hFile);
	}
}

void printf_solve_d(int n)
{
	freopen("��һ������2��3.txt", "w", stdout);
	cout << setw(max_size + 10) << setiosflags(ios::left) << "����" << "����" << endl;

	int size_n= sum_word;
	if (n != -1)
		size_n = min((ll)n, sum_word);

	for (int i = 0; i < size_n; i++) {
		cout << setw(max_size + 10 - word[i].word.size()) << setiosflags(ios::left) << word[i].word << word[i].sum << endl;
	}
	fclose(stdout);
}
void solve_d(string directory, bool _s, int _n) {


	vector<string>file;
	if (_s) { //����������Ŀ¼
		getAllFiles_zi_folder(directory, file);
		int size = file.size();

		for (int i = 0; i < size; i++) {
			if (file[i].substr(file[i].size() - 4) == ".txt") {
				function_first_step(file[i]);
			}

		}
	}
	else {
		getAllFiles(directory, file);
		int size = file.size();

		for (int i = 0; i < size; i++) {
			if (file[i].substr(file[i].size() - 4) == ".txt") {
				function_first_step(file[i]);
			}

		}
	}
	cout << "�����鿴debug�ļ��е��ļ�����һ������2��3.txt" << endl;
	sort(word.begin(), word.end(), cmp_solve_f);
	printf_solve_d(_n);
}
// solve_d
/*****************************/



/*****************************/
// solve_x
void init_map_stopWordFile(string stopWord_file) {
	ifstream stopWordFile;
	stopWordFile.open(stopWord_file);
	string str;

	while (!stopWordFile.eof()) {
		getline(stopWordFile, str);
		int size = str.size();
		string test_word;
		for (int i = 0; i < size; i++) {
			if (str[i] >= 'A'&&str[i] <= 'Z') //��д��ĸתСд
				str[i] = str[i] + 'a' - 'A';

			if (str[i] >= 'a'&&str[i] <= 'z' || str[i] >= '0'&&str[i] <= '9') //��ǰλ����ĸ�����ּӵ������ַ�������
				test_word += str[i];

			else if (!test_word.empty() || (i == size - 1 && str[i] >= 'a'&&str[i] <= 'z' || str[i] >= '0'&&str[i] <= '9')) {
				stopWord[test_word] = 1;//���ʲ��뵽map��
				test_word.clear();
			}
		}
	}
	stopWordFile.close();
}
void printf_solve_x() {
	freopen("�ڶ�������4.txt", "w", stdout);
	cout << setw(max_size + 10) << setiosflags(ios::left) << "����" << "����" << endl;
	for (int i = 0; i < sum_word; i++) {
		cout << setw(max_size + 10 - word[i].word.size()) << setiosflags(ios::left) << word[i].word << word[i].sum << endl;
	}
	fclose(stdout);
}
void solve_x(string stopWord, string file){
	init_map_stopWordFile(stopWord);
	function_first_step(file, true);
	sort(word.begin(), word.end(), cmp_solve_f);
	cout << "�����鿴debug�ļ��е��ļ����ڶ�������4.txt" << endl;
	printf_solve_x();
}

// solve_x
/*****************************/

/*****************************/
// solve_p
struct node_phrase {
	string s;
	int sum;
}tem_phrase;
vector<node_phrase> phrase;
map<string, ll>phrase_map;
map<string, ll>::iterator iter_phrase;
ll sum_phrase = 0;
bool cmp_phrase(node_phrase x, node_phrase y) {
	if (x.sum == y.sum) {
		return x.s < y.s;
	}
	else
		return x.sum > y.sum;
}
bool judge_alphabet(char c) {
	if (c >= 'a'&&c <= 'z' || c >= 'A'&&c <= 'Z') {
		return true;
	}
	return false;
}
void solve_p(string file, int number) {
	ifstream phraseFile;
	phraseFile.open(file);
	string str;

	while (!phraseFile.eof()) {
		getline(phraseFile, str);
		int size = str.size();
		int start = 0, end = 0;
		while (!judge_alphabet(str[start]) && start < size)
			start++;
		int num_word = 0;
		end = start;
		tem_phrase.sum = 1;
		for (; end < size; end++) {
			//����start��end��number������
			if (num_word == number) {
				string phr = str.substr(start, end - start + 1 - 2);//��ʱend�ڿո����һλ
				iter_phrase = phrase_map.find(phr);
	//			cout << "����:" << phr << endl;
				if (iter_phrase == phrase_map.end()) { //��û���ֹ����������뵽vector��
					tem_phrase.s = phr;
					phrase.push_back(tem_phrase);
					phrase_map[phr] = sum_phrase;
					sum_phrase++;
				}
				else { //������������+1
					phrase[iter_phrase->second].sum++;
				}
				//Ȼ����������ƶ�һ�����ʣ�������-1
				num_word--;
				while (judge_alphabet(str[start])) { //����ĸ�ʹ����ڵ�һ��������
					start++;
				}
				start++;
			}

			if (!judge_alphabet(str[end]) && str[end] != ' ') {//������ĸҲ���ǿո��������
				num_word++;
				if (num_word == number) { //�п����Ǿ��ӽ�β������պù�����������Ҳ���ԣ�������֮���������
					string phr = str.substr(start, end - start + 1 - 2);
					iter_phrase = phrase_map.find(phr);
		//			cout << "����:" << phr << endl;
					if (iter_phrase == phrase_map.end()) { //��û���ֹ����������뵽vector��
						tem_phrase.s = phr;
						phrase.push_back(tem_phrase);
						phrase_map[phr] = sum_phrase;
						sum_phrase++;
					}
					else { //������������+1
						phrase[iter_phrase->second].sum++;
					}
				}

				start = end + 1; //�����Ϊ��ǰλ����һλ
				while (!judge_alphabet(str[start]) && start < size) //��һ����ĸ�����
					start++;
				num_word = 0;
				end = start - 1;
			}
			else { //����ĸ���߿ո�
				if (str[end] == ' ')
					num_word++;
			}
		}
	}
	sort(phrase.begin(), phrase.end(), cmp_phrase);
	cout << "�����鿴debug�ļ��е��ļ�������������5.txt" << endl;
	freopen("����������5.txt", "w", stdout);
	int size_phr = phrase.size();
	for (int i = 0; i < size_phr; i++) {
		cout << phrase[i].s << endl;
	}
	fclose(stdout);
}

// solve_p
/*****************************/

int main(int argc, char* argv[])
{
	//�ж�����5�͹���6
	int flag_v_p = 0;
	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-p") == 0) {
			flag_v_p = 5;
		}
		else if (strcmp(argv[i], "-v" )== 0){
			flag_v_p = 6;
		}
	}

	if (strcmp(argv[1], "-c") == 0) {
		string file = argv[2];
		solve_c(file);
	}
	else if (strcmp(argv[1], "-f") == 0) {
		string file = argv[2];
		solve_f(file);
	}
	else if (strcmp(argv[1], "-d") == 0) {
		int n = -1;
		bool _s = false;
		for (int i = 0; i < argc; i++) {
			if (strcmp(argv[i], "-n") == 0) {
				string number = argv[i+1];
				int size = number.size();
				n = 0;
				for (int j = 0; j < size; j++)
					n = n * 10 + number[j] - '0';
			}
			if (strcmp(argv[i], "-s") == 0) {
				_s = true;
			}
		}
		string directory = argv[argc - 1];
		solve_d(directory, _s, n);
	}
	else if (strcmp(argv[1], "-x") == 0) {
		string stopword = argv[2];
		string file = argv[4];
		solve_x(stopword, file);
	}
	else if (flag_v_p == 5) {
		string file;
		int number=0;
		for (int i = 1; i < argc; i++) {
			if (strcmp(argv[i], "-p") != 0) {
			//	cout << "argv[" << i << "]=" << argv[i] << endl;
				int size = strlen(argv[i]);
				if (argv[i][size - 3] == 't'&&argv[i][size - 2] == 'x'&&argv[i][size - 1] == 't') {
					file = argv[i];
				}
				else {
					for (int j = 0; j < size; j++) {
						number = number * 10 + argv[i][j] - '0';
					}
				}

			}
		}
		solve_p(file, number);
		//cout << "number=" << number << " file=" << file << endl;
	}
	else if (flag_v_p == 6) {

	}

    return 0;
}

