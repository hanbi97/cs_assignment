#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <cmath>
#include <malloc.h>
#include <fstream>
#include <string>
#include <assert.h>
#include <bitset>
#include <vector>
#include <stdio.h>
#include <sstream>
using namespace std;

#define FILE_SIZE_OFFSET 0x0002
#define DATAOFFSET_OFFSET 0x000A
#define HEIGHT_OFFSET 0x00012
#define WIDTH_OFFSET 0x0016
#define SIZE_OFFSET 0x0022
#define BITS_PER_PIXEL_OFFSET 0x001C
#define HEADER_SIZE 14
#define INFO_HEADER_SIZE 40

typedef unsigned int uint;
typedef unsigned char uchar;

//hide original character to B pixels'LSB
int change(int number, int bit) {
	if (number % 2 == 0) {
		if (bit == 1) number += 1;
	}
	else {
		if (bit == 0) number -= 1;
	}
	return number;
}

//find original character
int recover(int val) {
	return val & 1;
}

//int to binary
vector<int> iTob(int num) {
	vector<int> res(8);
	int idx = 7;
	while (num > 0) {
		res[idx--] = num % 2;
		num /= 2;
	}
	return res;
}

//d option
string decrypt(string dst) {
	/* read pixel data */
	ifstream fin(dst, ios::binary);
	assert(fin.is_open());

	//reading header
	vector<char> header(HEADER_SIZE + INFO_HEADER_SIZE);
	fin.read(header.data(), header.size());

	//start reading width and height
	uint width = *reinterpret_cast<uint32_t*>(&header[18]);
	uint height = *reinterpret_cast<uint32_t*>(&header[22]);
	uint dataOffset = *reinterpret_cast<uint32_t*>(&header[10]);


	//read data
	vector<char> data(dataOffset - (HEADER_SIZE + INFO_HEADER_SIZE));
	fin.read(data.data(), data.size());

	auto dataSize = ((width * 3 + 3) & (~3)) * height;
	data.resize(dataSize);
	fin.read(data.data(), data.size());

	long long txtSize = (data[dataSize - 4] - '\0') + (data[dataSize - 5] - '\0') * 256;
	vector<int> binary; 
	string res = "";

	for (auto i = dataSize - 7; i >= 0; i-=3)
	{
		if (res.size() == txtSize) break;
		if ((data[i] - '\0') % 2 == 0) {
			binary.push_back(0);
		}
		else {
			binary.push_back(1);
		}
		if (binary.size() == 8) {
			int sum = 0; int idx = 7;
			for (int j = 0; j < binary.size(); j++) {
				if (binary[j] == 1)
					sum += pow(2, idx);
				idx--;
			}
			res.push_back(char(sum));
			binary.clear();
		}
	}
	return res;
}

//write stego.bmp
void write(const char* output, vector<char> header, vector<char> data) {
	ofstream fout(output, ios::binary);
	assert(fout.is_open());
	fout.write(header.data(), header.size());

	uint dataOffset = *reinterpret_cast<uint32_t*>(&header[10]);
	FILE* outputFile = fopen(output, "wb");
	fseek(outputFile, dataOffset, SEEK_SET);
	fread(&dataOffset, 4, 1, outputFile);
	fclose(outputFile);

	for (auto d : data) {
		fout << d;
	}
	fout.close();
}

/*e option*/
void encrypt(const char* src, string txt) {
	/* read pixel data */
	ifstream fin(src, ios::binary);
	assert(fin.is_open());

	//reading header
	vector<char> header(HEADER_SIZE + INFO_HEADER_SIZE);
	fin.read(header.data(), header.size());

	//start reading width and height
	uint width = *reinterpret_cast<uint32_t*>(&header[18]);
	uint height = *reinterpret_cast<uint32_t*>(&header[22]);
	uint dataOffset = *reinterpret_cast<uint32_t*>(&header[10]);


	//read data
	vector<char> data(dataOffset - (HEADER_SIZE + INFO_HEADER_SIZE));
	fin.read(data.data(), data.size());

	auto dataSize = ((width * 3 + 3) & (~3)) * height;
	data.resize(dataSize);
	fin.read(data.data(), data.size());

	long long size = txt.size();
	int idx = dataSize - 7;
	int txtSize = 0;
	
	data[dataSize - 4] = size % 256;
	data[dataSize - 5] = size / 256;
	
	//RGB 각 픽셀 맨 마지막 비트에 문자 변환한거 하나씩 뒤에 넣음
	for (int i = 0; i < txt.size(); i++) {
		vector<int> binary = iTob(txt[i]);
		for (auto bit : binary) {
			data[idx] = change(int(data[idx] & 0xff), bit);
			idx -= 3;
		}
	}
	write("./stego.bmp", header, data);
}

int main(int argc, char* argv[]) {
	if (strcmp(argv[1], "e")==0) { //encrypt
		string txt;
		getline(cin, txt);
		encrypt("./origin.bmp", txt);
	}
	else if (strcmp(argv[1], "d") == 0) {//decrypt
		cout << decrypt("./stego.bmp");
	}
	return 0;
}