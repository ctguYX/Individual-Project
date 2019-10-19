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

bool is_have_v = false; //�ж��Ƿ�Ҫ������̬��һ��


/*****************************/
//solve_v
bool judge_alphabet(char c) {
	if (c >= 'a'&&c <= 'z' || c >= 'A'&&c <= 'Z') {
		return true;
	}
	return false;
}
vector<string> verb;
map<string, ll>verb_map;//�涯�ʵı��ε�ԭ���±�
map<string, ll>::iterator iter_verb;
ll sum_verb = 0;
void solve_v(string file) {
	ifstream verbFile;
	verbFile.open(file);
	string str;

	while (!verbFile.eof()) {
		getline(verbFile, str);
		int size = str.size();
		int start = 0, end = 0;
		while (!judge_alphabet(str[start]) && start < size)
			start++;
		end = start;
		bool flag_yuan = true;
		for (; end <= size; end++) {
			if (str[end] == ' ' || end == size) {
				string word = str.substr(start, end - start);//end�ڵ���֮��Ŀո�λ��
				start = end + 1;
				if (flag_yuan) {
					//			cout << "����ԭ��:" << word << endl;
					flag_yuan = false;
					verb.push_back(word);
				}
				else {
					//		cout << "����������̬:" << word << endl;
					verb_map[word] = sum_verb;
				}
			}
		}
		sum_verb++;
	}
	verbFile.close();
}
void huan_yuan_v(string &str) { //��һ���ַ����������з�ԭ�ε��ʸ�Ϊԭ��
								//	cout << "huan_yuan_v str=" << str << endl;
	int size = str.size();
	int start = 0, end = 0;
	while (!judge_alphabet(str[start]) && start < size)
		start++;
	end = start;
	for (; end < size; end++) {
		//		cout<<"statrt="<<start << " end=" << end <<" size="<<size<< endl;
		//		cout << "str=" << str << endl << endl;
		if (!judge_alphabet(str[end]) || end == size - 1) {
			if (!judge_alphabet(str[end]))
				end--;
			string word = str.substr(start, end - start + 1);

			iter_verb = verb_map.find(word);
			if (iter_verb != verb_map.end()) { //������������ж��ʵı���
											   //			cout << "���ʱ���:" << word << endl;
				string yuan_verb = verb[iter_verb->second];
				int size_yuan = yuan_verb.size();
				int size_bianXing = word.size();
				if (size_bianXing >= size_yuan) { //���α�ԭ����ĸ�࣬���Ǻ�ɾ������
					for (int i = start, j = 0; j < size_yuan; i++, j++)
						str[i] = yuan_verb[j];
					if (size_bianXing > size_yuan) {
						str.erase(start + size_yuan, size_bianXing - size_yuan);
						size = size - (size_bianXing - size_yuan);
						end = end - (size_bianXing - size_yuan);
					}

				}
				else { //ԭ�αȱ��ζ࣬��Ҫ���ӿ�λ
					string front = str.substr(0, start);
					string back = str.substr(end + 1);
					string s = front + yuan_verb + back;
					swap(str, s);
					size = str.size();
					end = start + size_yuan;
				}
			}
			start = end + 1;
			while (!judge_alphabet(str[start]) && start < size)
				start++;
			end = start;
		}
	}

}
//solve_v
/*****************************/


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
	ifstream book;
	book.open(file);
	string str;


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

	while (!book.eof()) {
		getline(book, str);
		if(is_have_v==true)
			huan_yuan_v(str);

		for (int i = 0; str[i] != '\0'; i++) {
			if (str[i] >= 'a' && str[i] <= 'z') {
				sum_alphabet++;
				sum[str[i] - 'a' + 26].num++;
			}
			else if (str[i] >= 'A' && str[i] <= 'Z') {
				sum_alphabet++;
				sum[str[i] - 'A'].num++;
			}
		}
	}
	book.close();

	for (int i = 0; i < 52; i++) {
		sum[i].pinlv = sum[i].num*1.0 / sum_alphabet;
		int temp = sum[i].pinlv * 100;
		sum[i].pinlv = temp*1.0 / 100; //С����λ��ʱ������ʱ������һ��
	}

	sort(sum, sum + 52, cmp_solve_c);


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
ll sum_word = 0;
int max_size = 0;
bool cmp_solve_f(solve_f_node x, solve_f_node y) {
	if (x.sum == y.sum)
		return x.word < y.word;
	else
		return x.sum > y.sum;
}

void function_first_step(string file, bool _x = false)
{


	temp_word.sum = 1;
	ifstream book;
	book.open(file);
	string str;
	while (!book.eof()) {
		getline(book, str);

		if (is_have_v == true)
			huan_yuan_v(str);

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
	cout << setw(max_size + 10) << setiosflags(ios::left) << "����" << "����" << endl;
	for (int i = 0; i < sum_word; i++) {
		cout << setw(max_size + 10 - word[i].word.size()) << setiosflags(ios::left) << word[i].word << word[i].sum << endl;
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

	int size_n = sum_word;
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
		if (is_have_v == true)
			huan_yuan_v(str);

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
void solve_x(string stopWord, string file) {
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

void solve_p(string file, int number) {
	ifstream phraseFile;
	phraseFile.open(file);
	string str;

	while (!phraseFile.eof()) {
		getline(phraseFile, str);
	//	cout << "��ԭǰ�ַ���:" << str << endl;
		//		cout << "��ԭǰ�ַ���:" << str << endl;
		if (is_have_v == true)
			huan_yuan_v(str);
	//	cout << "��ԭ���ַ���:" << str << endl << endl;


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

string getFile(int &start, char *argv[],int size) { //��start��ʼ���һ���ļ���,startָ���ļ��������һ������
	string file;
	string kong_ge = " ";
//	cout <<"file="<< file << endl;
	string end = ".txt";
	for (; start < size; start++) {
		string te = argv[start];
		file += te;
		int t_size = te.size();
		int sum_deng = 0;
		if (t_size >= 4) {
			for (int i = t_size - 4, j = 0; j < 4; i++, j++) {
			//	cout << "te[i]=" << te[i] << " end[j]=" << end[j] << endl;
				if (te[i] != end[j]) {
					break;
				}
				else
					sum_deng++;
			}
		}
		if (sum_deng==4)
			break;

		file += kong_ge;
	}
	start++;
	return file;
}



int main(int argc, char* argv[])
{
	bool _c = false; //����0 ��ĸƵ��    wf.exe -c <file name> 
	string file_c;
	bool _f = false;// ����1 ����ļ������в��ظ��ĵ���    wf.exe -f <file>  
	bool _d = false;//����2 ��һ��Ŀ¼�����ļ�ִ�й���1 wf.exe -d <directory> 
	bool _s = false;  //����2��չ������Ŀ¼��������Ŀ¼  wf.exe -d -s  <directory> 
	int _n = -1;   //����2��չ��������ִ�������ǰ n ������  wf.exe -d -s  <directory> -n <number> (_n������ǰ��)
	bool _x = false; //����2��չ ֧�����ʱ�  wf.exe -x <stopwordfile>  -f <file> 
	bool _p = false; //����5  ���<number>���ʵĶ���    wf.exe -p <number>  <file> 
	bool _v = false; //���Ϲ�����չ ֧�ֶ�����̬�Ĺ�һ�� wf.exe -v <verb file> .... 
	string file_v;
	
	









	//�����ж����
	if (_v == true) { //����-v���� ֧�ֶ�����̬�Ĺ�һ��
		is_have_v = true;
		solve_v(file_v);
	}


	//�ж�����5�͹���6
	//int flag_v_p = 0;
	//for (int i = 0; i < argc; i++) {
	//	if (strcmp(argv[i], "-p") == 0) {
	//		flag_v_p = 5;
	//	}
	//	else if (strcmp(argv[i], "-v") == 0) {
	//		flag_v_p = 6;
	//	}
	//}

	//if (strcmp(argv[1], "-c") == 0) {
	//	string file = argv[2];
	//	solve_c(file);
	//}
	//else if (strcmp(argv[1], "-f") == 0) {
	//	string file = argv[2];
	//	solve_f(file);
	//}
	//else if (strcmp(argv[1], "-d") == 0) {
	//	int n = -1;
	//	bool _s = false;
	//	for (int i = 0; i < argc; i++) {
	//		if (strcmp(argv[i], "-n") == 0) {
	//			string number = argv[i + 1];
	//			int size = number.size();
	//			n = 0;
	//			for (int j = 0; j < size; j++)
	//				n = n * 10 + number[j] - '0';
	//		}
	//		if (strcmp(argv[i], "-s") == 0) {
	//			_s = true;
	//		}
	//	}
	//	string directory = argv[argc - 1];
	//	solve_d(directory, _s, n);
	//}
	//else if (strcmp(argv[1], "-x") == 0) {
	//	string stopword = argv[2];
	//	string file = argv[4];
	//	solve_x(stopword, file);
	//}
	//else if (flag_v_p == 5) {
	//	string file;
	//	int number = 0;
	//	for (int i = 1; i < argc; i++) {
	//		if (strcmp(argv[i], "-p") != 0) {
	//			//	cout << "argv[" << i << "]=" << argv[i] << endl;
	//			int size = strlen(argv[i]);
	//			if (argv[i][size - 3] == 't'&&argv[i][size - 2] == 'x'&&argv[i][size - 1] == 't') {
	//				file = argv[i];
	//			}
	//			else {
	//				for (int j = 0; j < size; j++) {
	//					number = number * 10 + argv[i][j] - '0';
	//				}
	//			}

	//		}
	//	}
	//	solve_p(file, number);
	//	//cout << "number=" << number << " file=" << file << endl;
	//}
	////	else if (flag_v_p == 6) {

	////}

	return 0;
}
