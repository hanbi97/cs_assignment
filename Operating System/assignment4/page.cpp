#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <stdio.h>
#include <vector>
#include <queue>
#include <utility>
#include <math.h>
using namespace std;
#define ARRAYSIZE 1024

/*��ü��뺯��*/
char * inputArr = new char[ARRAYSIZE];
char type;
int frame, num;
int d[100];
bool findbit;
ofstream output("output.txt");

/*fifo ����*/
queue<int> q;
int res[100];


/*opt����*/
pair<int, int> optd[100];
pair<int, int>ores[100];
int maxval;
int realmax;
int sizecount;

/*LRU����*/
int cnt;
pair<int, int>ld[100];
pair<int, int>lres[100];

void Fifo() {

	for (int i = 0; i < frame; i++) {
		res[i] = d[i];
		q.push(d[i]);
		output << d[i] << "|";
		for (int k = 0; k < frame; k++)
		{
			if (res[k] != -1)
			{
				output << res[k] << " ";
			}
		}

		output << endl;
	}

	for (int i = frame; i < num; i++) {
		//��ü����ã�ƾ���
		findbit = false;
		for (int j = 0; j < frame; j++)
		{
			if (res[j] == d[i]) {
				findbit = true;
			}

		}
		if (findbit == false)
		{
			for (int j = 0; j < frame; j++) {
				if (q.front() == res[j]) {
					res[j] = d[i];
				}
			}
			q.pop();
			q.push(d[i]);
		}


		output << d[i] << "|";
		for (int k = 0; k < frame; k++)
		{
			if (res[k] != -1)
			{
				output << res[k] << " ";
			}
		}

		output << endl;
	}

}

void LRU() {
	for (int i = 0; i < num; i++) {
		maxval = 0;
		if (sizecount < frame) {
			ld[i].first = d[i];
			for (int j = 0; j < frame; j++) {
				if (ld[j].first != -1) {
					ld[j].second++;
				}
			}
			sizecount++;
		}
		else {
			//�� á����
			//�� ī��Ʈ ����
			for (int j = 0; j < frame; j++) {
				ld[j].second++;
			}

			findbit = false;
			for (int j = 0; j < frame; j++) {
				if (ld[j].first == d[i]) {
					findbit = true;
					ld[j].second = 0;
					break;
				}
			}
			if (findbit == false) {
				for (int j = 0; j < frame; j++) {
					if (maxval < ld[j].second) {
						maxval = ld[j].second;
					}
				}
				for (int j = 0; j < frame; j++) {
					if (maxval == ld[j].second) {
						//lruã��
						ld[j].first = d[i];
						ld[j].second = 0;
						break;
					}
				}
			}


		}

		output << d[i] << "|";
		for (int k = 0; k < frame; k++) {

			if (ld[k].first != -1)
			{
				output << ld[k].first << " ";
			}
		}
		output << endl;

	}
}

void Opt() {
	//�� ����Ƚ�� �̸� ����
	for (int i = 0; i < num; i++) {
		optd[i].first = d[i];
	}
	for (int i = 0; i < num; i++) {
		for (int j = i + 1; j <= num; j++) {
			if (optd[i].first != d[j])
			{
				optd[i].second++;
			}
			else {
				break;
			}
		}
	}

	for (int i = 0; i < num; i++) {
		if (sizecount < frame) {
			ores[i] = make_pair(optd[i].first, optd[i].second);
			sizecount++;
		}//ó���� ����ֱ�
		//->�̹� i�� frame��ŭ ����
		else {
			findbit = false;
			for (int k = 0; k < frame; k++) {
				ores[k].second--;
			}
			for (int k = 0; k < frame; k++) {
				if (ores[k].first == d[i]) {
					findbit = true;
					ores[k] = make_pair(optd[i].first, optd[i].second);
				}
			}
			if (findbit == false)
			{
				maxval = 0;
				realmax = 0;
				for (int j = 0; j < frame; j++) {
					if (maxval < ores[j].second) {
						maxval = ores[j].second;
						realmax = ores[j].first;
					}
				}
				for (int j = 0; j < frame; j++) {
					if (ores[j].first == realmax) {
						ores[j] = make_pair(optd[i].first, optd[i].second);
						break;
					}
				}
			}
		}
		output << d[i] << "|";
		for (int k = 0; k < frame; k++) {
			if (ores[k].first != -1)
			{
				output << ores[k].first << " ";
			}
		}
		output << endl;
	}
}

int main() {
	//txt file input
	//F,L,O ���� (�Լ� 3��), physical frame����, �Է¹��� ������ ����, ������ �Է�

	ifstream txt("input.txt");
	int position = 0;
	int size = sizeof(txt);
	char str[sizeof(txt)];
	if (txt.good()) {
		while (!txt.eof() && position < ARRAYSIZE) {

			txt.get(inputArr[position]); //\n������ �ٿ��� ���̹���
			position++;

		}
		inputArr[position - 1] = '\0';

	}
	//���ͷ� ���ڱ����ؼ� �ޱ�(4���Է�)
	int temp = 0;
	int j = 0;
	vector<int> framenum;
	vector<int> numnum;

	for (int i = 0; i < 4; i++) {
		if (i == 0)
		{
			while (inputArr[temp] != '\n') {
				type = inputArr[temp];
				temp++;
			}
			temp++;
		}

		else if (i == 1) {
			while (inputArr[temp] != '\n') {
				framenum.push_back(inputArr[temp] - 48);
				temp++;
			}
			temp++;
		}

		else if (i == 2) {
			while (inputArr[temp] != '\n') {
				numnum.push_back(inputArr[temp] - 48);
				temp++;
			}
			temp++;
		}
		else {
			while (inputArr[temp] != '\n') {
				if (inputArr[temp] != ' ')
				{
					d[j] = inputArr[temp] - 48;
					j++;
				}
				temp++;
			}
		}
	}
	txt.close();

	//frame,num ��¥ �� ���ϱ�
	if (framenum.size() > 1) {
		int idx = framenum.size();
		int c = idx - 1;
		while (c > 0)
		{
			frame += framenum[idx - c] * pow(10, c - 1);
			c--;
		}

	}
	else if (framenum.size() == 1) {
		frame = framenum[0];
	}
	if (numnum.size() > 1) {
		int idx = numnum.size();
		int c = idx;
		while (c > 0)
		{
			num += numnum[idx - c] * pow(10, c - 1);
			c--;
		}

	}
	else if (numnum.size() == 0) {
		num = numnum[0];
	}

	memset(res, -1, sizeof(res));
	memset(optd, -1, sizeof(optd));
	memset(ores, -1, sizeof(ores));
	memset(ld, -1, sizeof(ld));

	switch (type)
	{
	case 'F':
		Fifo();
		break;
	case 'L':
		LRU();
		break;
	case 'O':
		Opt();
		break;
	}
}