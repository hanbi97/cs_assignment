#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <vector>
using namespace std;
#define ARRAYSIZE 1024

char * inputArr = new char[ARRAYSIZE];
int processNum;
int resourceNum;
int reqNum;
int reqresourceNum;
int cnt;

vector<int> available;
vector<vector<int> > maxx;
vector<vector<int> > alloc;
vector<vector<int> > req;
vector<vector<int> > need;
vector<bool> finish;
vector<int> work;

vector<int> setAvail(string s, vector<int> available) {
	inputArr = new char[ARRAYSIZE];
	ifstream txt(s);
	int position = 0;
	int size = sizeof(txt);
	char str[sizeof(txt)];
	if (txt.good()) {
		while (!txt.eof() && position < ARRAYSIZE) {

			txt.get(inputArr[position]); //\n있으면 붙여서 같이받음
			position++;

		}
		inputArr[position - 1] = '\0';

	}
	for (int i = 0; i < position - 1; i++) {
		if (inputArr[i] == ' ')
		{
			continue;
		}

		else if (inputArr[i] == '\n') {
			continue;
		}
		else {
			available.push_back(inputArr[i] - 48);
			//int로 만들어주기위해 string 0 아스키코드값 빼줌
		}
	}
	txt.close();
	return available;
}

vector<vector<int>> set2dVector(string s, vector<vector<int> > aa) {
	inputArr = new char[ARRAYSIZE];
	ifstream txt(s);
	int position = 0;
	int size = sizeof(txt);
	char str[sizeof(txt)];
	if (txt.good()) {
		while (!txt.eof() && position < ARRAYSIZE) {

			txt.get(inputArr[position]); //\n있으면 붙여서 같이받음
			position++;

		}
		inputArr[position - 1] = '\0';

	}
	aa.resize(position);
	int line = 0;

	for (int i = 0; i < position - 1; i++) {
		if (inputArr[i] == ' ')
		{
			continue;
		}

		else if (inputArr[i] == '\n') {
			line++;
			continue;
		}
		else {
			aa[line].push_back(inputArr[i] - 48);
			//int로 만들어주기위해 string 0 아스키코드값 빼줌
		}
	}
	txt.close();
	return aa;
}

int processNumber(string s, vector<vector<int> > aa) {
	inputArr = new char[ARRAYSIZE];
	ifstream txt(s);
	int position = 0;
	int size = sizeof(txt);
	char str[sizeof(txt)];
	if (txt.good()) {
		while (!txt.eof() && position < ARRAYSIZE) {

			txt.get(inputArr[position]); //\n있으면 붙여서 같이받음
			position++;

		}
		inputArr[position - 1] = '\0';

	}
	aa.resize(position);
	int line = 0;

	for (int i = 0; i < position - 1; i++) {
		if (inputArr[i] == ' ')
		{
			continue;
		}

		else if (inputArr[i] == '\n') {
			line++;
			continue;
		}
		else {
			aa[line].push_back(inputArr[i] - 48);
			//int로 만들어주기위해 string 0 아스키코드값 빼줌
		}
	}
	txt.close();
	return line;
}
void calcNeed() {
	need.resize(processNum);

	for (int i = 0; i < processNum; i++) {
		need[i].resize(resourceNum);
		for (int j = 0; j < resourceNum; j++) {
			need[i][j] = maxx[i][j] - alloc[i][j];
		}
	}

	for (int i = 0; i < processNum; i++) {
		for (int j = 0; j < need[i].size(); j++)
		{
			cout << need[i][j] << " ";
		}
		cout << endl;
	}

}

int main(int argc, char* argv[]) {

	if (argc != 5) {
		printf("인자를 다시 입력하세요.\n");
		return 1;
	}
	else {
		ofstream output("output.txt");
		available = setAvail(argv[1], available);
		cout << endl;
		cout << endl;
		maxx = set2dVector(argv[2], maxx);
		cout << endl;
		alloc = set2dVector(argv[3], alloc);
		cout << endl;
		req = set2dVector(argv[4], req);
		cout << endl;
		processNum = processNumber(argv[2], maxx);
		resourceNum = available.size();
		reqresourceNum = req[0].size();
		reqNum = processNumber(argv[4], req);
		calcNeed();
		/*banker algorithm 실행*/

		for (int i = 0; i < reqNum; i++) {
			cnt = 0;

			//resource-request algorithm
			int reqProcess = req[i][0]; //요구한프로세스

			for (int j = 0; j < resourceNum; j++) {
				if (req[i][j + 1] > need[i][j])
				{
					output << "reject\n";
					exit(0);
				}
				if (req[i][j + 1] > available[j])
				{
					output << "reject\n";
					exit(0);
				}
			}

			//request 적용
			/*available-request
			allocation+request
			need-request
			*/
			for (int j = 0; j < resourceNum; j++) {
				available[j] -= req[i][j + 1];
				alloc[reqProcess][j] += req[i][j + 1];
				need[reqProcess][j] -= req[i][j + 1];
			}

			//safety algorithm

			//initialize
			work.resize(resourceNum);
			finish.resize(processNum);
			for (int j = 0; j < resourceNum; j++) {
				work[j] = available[j];
			}

			while (cnt < processNum)
			{
				bool find = false;
				for (int j = 0; j < processNum; j++) {
					int k;
					for (k = 0; k < resourceNum; k++) {
						if (finish[j] == false && (need[j][k] > work[k]))//그줄전체가 다 커야함 
						{
							break;
							////검사
						}

					}
					if (k == resourceNum&&finish[j] != true) {
						finish[j] = true;
						for (int s = 0; s < resourceNum; s++)
						{
							work[s] += alloc[j][s];//여기에 루프생김
						}
						cnt++;
						find = true;
					}

					if (cnt == processNum) {
						output << "accept\n";
						find = true;
						break;
					}
				}

				if (find == false) {
					output << "reject\n";
					break;
				}
			}

		}
		output.close();
	}

	return 0;
}