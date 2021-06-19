#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bitset>
#include <algorithm>
using namespace std;
#define IRREDUCIBLE 0x01E7


class AES {
private:
	int irreduciblePoly[9] = { 1,1,1,1,0,0,1,1,1 }; // irreducible polynomial �������� �ٲ۰�(msb�� �� ��)
	int A[4][4] = {
		{2,3,1,1},
		{1,2,3,1},
		{1,1,2,3},
		{3,1,1,2}
	}; // mixColumn �� ���� ���Ǵ� ��� A
	int invA[4][4] = {
		{14,11,13,9},
		{9,14,11,13},
		{13,9,14,11},
		{11,13,9,14}
	};// mixColumn �� ���� ���Ǵ� A�� �����

	vector<int> rcs;//rc����
	vector<vector<int>> datas; //�� �Ǵ� ��ȣ�� �� �о����
	vector<vector<int>> keys; // key expansion�Ѱ� ����
	vector<vector<int>> plainMat; //�� �Ǵ� ��ȣ�� 1�� ����
	vector<vector<int>> keyMat; //key ��ķ� ������ ����
	vector<vector<int>> results; // ��� ����
	vector<int> initialKey;//key0 ����
	vector<int> initialPlain; //ù��° �� �Ǵ� ��ȣ��

	/*���Ͽ��� binary �� �о����*/
	void readData(string file) {
		ifstream fin(file, ios::in|ios::binary);
		vector<uint8_t> contents((istreambuf_iterator<char>(fin)), {});
		
		//ecb �����ϰ� 16���� �ɰ��� ����
		datas.resize(contents.size() / 16);
		for (int i = 0; i < contents.size() / 16; i++) {
			vector<int> res;
			for (int j = 0; j < 16; j++) {
				int val = contents[i*16+j];
				res.push_back(val);
			}
			datas[i] = res;
		}
	}

	//key ���Ͽ��� �о����
	vector<int> readKey(string file) {
		vector<int> res;
		ifstream fin(file, ios::in | ios::binary);
		vector<uint8_t> contents((istreambuf_iterator<char>(fin)), {});

		for (int i = 0; i < contents.size(); i++) {
				int val = contents[i];
				res.push_back(val);
		}
		return res;
	}

	/*��� �� binary ���Ϸ� �����*/
	void writeBin(string file) {
		ofstream output(file, ios::out | ios::binary);

		for (int y = 0; y < results.size(); y++) {
			for (int x = 0; x < results[y].size(); x++) {
				output.write((char*)&results[y][x], sizeof(uint8_t));
			}
		}
	}

	/*16byte ���� ������ ��ķ� �ٲ�*/
	vector<vector<int>> changeToMatrix(vector<int> binary) {
		vector<vector<int>> mat(4);
		int idx = 0;
		for (int x = 0; x < 4; x++) {
			for (int y = 0; y < 4; y++) {
				mat[y].push_back(binary[idx++]);
			}
		}
		return mat;
	}

	/*int�� binary�� �ٲٱ�*/
	vector<int> convertToBinary(int b) {
		vector<int> result;
		while (b != 0) {
			result.push_back(b % 2);
			b /= 2;
		}
		while (result.size() < 8) {
			result.push_back(0);
		}
		reverse(result.begin(), result.end());
		return result;
	}


	/*RC1~10 ���ϱ�*/
	void calcRC() {
		int start = 1;
		for (int i = 0; i < 10; i++) {
			rcs.push_back(start);
			start = start << 1;
			if (start >= 256) start = start ^ IRREDUCIBLE;
		}
	}

	/*keyExpansion�� g ����*/
	vector<int> keyExpansionG(vector<int> subKey, int round) {
		// permutation
		int tmp = subKey[0];
		for (int i = 0; i < 3; i++) {
			subKey[i] = subKey[(i + 1) % 4];
		}
		subKey[3] = tmp;

		//sbox ���
		for (int i = 0; i < 4; i++) {
			subKey[i] = enCalcSBoxValue(subKey[i]);
		}

		subKey[0] = subKey[0] ^ rcs[round];
		for (int i = 1; i < 4; i++) {
			subKey[i] = subKey[i] ^ 0;
		}
		return subKey;
	}

	/*keyExpansion*/
	void keyExpansion() {
		keys[0] = initialKey;

		vector<vector<int>> subKeys(4);
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				subKeys[i].push_back(initialKey[i * 4 + j]);
			}
		}

		for (int round = 1; round <= 10; round++) {
			//g����
			vector<int> g = keyExpansionG(subKeys[3], round - 1);

			//XOR
			for (int i = 0; i < 4; i++) {
				subKeys[0][i] = subKeys[0][i] ^ g[i];
			}
			for (int j = 1; j < 4; j++) {
				for (int i = 0; i < 4; i++) {
					subKeys[j][i] = subKeys[j][i] ^ subKeys[j - 1][i];
				}
			}
			//���� �� ���� ���꿡 ����
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					keys[round].push_back(subKeys[i][j]);
				}
			}
		}
		cout << "key expansion" << '\n';
		for (int i = 0; i <= 10; i++) {
			for (int j = 0; j < keys[i].size(); j++) {
				cout << hex << keys[i][j] << " ";
			}
			cout << '\n';
		}
	}

public:
	AES() {
		initialKey = readKey("key.bin"); 
		keys.resize(11);
		calcRC();
		keyExpansion();
	}
	
	/*��ȣȭ*/
	void encrpyt(string file) {
		readData(file);
		results.resize(datas.size());
		for (int t = 0; t < datas.size(); t++) {//ecb
			initialPlain.clear();
			for (int i = 0; i < datas[t].size(); i++) {
				int val = datas[t][i];
				initialPlain.push_back(val);
			}
			for (int i = 0; i < initialPlain.size(); i++) {
				cout << initialPlain[i] << " ";
			}
			cout << '\n';
			plainMat = changeToMatrix(initialPlain);
			keyMat = changeToMatrix(keys[0]);
			cout << "init: " << '\n';
			for (int y = 0; y < 4; y++) {
				for (int x = 0; x < 4; x++) {
					plainMat[y][x] = (plainMat[y][x] ^ keyMat[y][x]);
				}
			}
			for (int y = 0; y < 4; y++) {
				for (int x = 0; x < 4; x++) {
					cout << hex << plainMat[y][x] << " ";
				}
				cout << '\n';
			}

			for (int round = 1; round <= 10; round++) {
				keyMat = changeToMatrix(keys[round]);
				enSubstituteBytes();
				enShiftRows();
				if (round != 10) enMixColumns();
				AddRoundKey();
				cout << "---------------------------------------------" << '\n';
			}
			for (int y = 0; y < 4; y++) {
				for (int x = 0; x < 4; x++) {
					results[t].push_back(plainMat[x][y]);
				}
			}
		}		
		writeBin("cipher.bin");
	}

	/*��ȣȭ*/
	void decrypt(string file) {
		readData(file);
		results.resize(datas.size());
		for (int t = 0; t < datas.size(); t++) {//ecb
			initialPlain.clear();
			for (int i = 0; i < datas[t].size(); i++) {
				int val = datas[t][i];
				initialPlain.push_back(val);
			}
			plainMat = changeToMatrix(initialPlain);
			initialKey = keys[10];
			keyMat = changeToMatrix(initialKey);

			cout << "init: " << '\n';
			for (int y = 0; y < 4; y++) {
				for (int x = 0; x < 4; x++) {
					plainMat[y][x] ^= keyMat[y][x];
				}
			}

			for (int y = 0; y < 4; y++) {
				for (int x = 0; x < 4; x++) {
					cout << hex << plainMat[y][x] << " ";
				}
				cout << '\n';
			}

			for (int round = 9; round >= 0; round--) {
				keyMat = changeToMatrix(keys[round]);
				deShiftRows();
				deSubstituteBytes();
				AddRoundKey();
				if (round != 0) deMixColumns();
				cout << "---------------------------------------------" << '\n';
			}
			for (int y = 0; y < 4; y++) {
				for (int x = 0; x < 4; x++) {
					results[t].push_back(plainMat[x][y]);
				}
			}
		}
		writeBin("plain2.bin");
	}

	/*��ȣȭ�� ���Ǵ� SB*/
	void enSubstituteBytes() {
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				plainMat[y][x] = enCalcSBoxValue(plainMat[y][x]);
			}
		}
		cout << "sb" << '\n';
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				cout << hex << plainMat[y][x] << " ";
			}
			cout << '\n';
		}
	}

	/*��ȣȭ�� ���Ǵ� shift row*/
	void enShiftRows() {
		for (int i = 1; i < 4; i++) {
			vector<int> change(4);
			for (int j = 0; j < 4; j++) {
				change[j] = plainMat[i][(j + i) % 4];
			}
			plainMat[i] = change;
		}
		cout << "sr" << '\n';
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				cout << hex << plainMat[y][x] << " ";
			}
			cout << '\n';
		}
	}

	/*��ȣȭ�� ���Ǵ� mix colum*/
	void enMixColumns() {
		vector<vector<int>> tmpMat(4);
		for (int i = 0; i < 4; i++) {
			for(int j=0; j<4; j++) tmpMat[i].push_back(0);
		}
		for (int x = 0; x < 4; x++) {
			vector<int> calc(4);
			for (int y = 0; y < 4; y++) {
				calc[y] = plainMat[y][x];
			}
			for (int k = 0; k < 4; k++) {
				vector<int> values(4);
				for (int y = 0; y < 4; y++) {
					int tmp = 0;
					if (A[k][y] == 1) {
						tmp =calc[y];
					}
					else if (A[k][y] == 2) {
						tmp = calc[y] << 1;
					}
					else {
						tmp = (calc[y] << 1) ^ calc[y];
					}
					if (tmp >= 256) tmp ^= IRREDUCIBLE;
					values[y] = tmp;
				}
				int ini = values[0];
				for (int i = 1; i < 4; i++) {
					ini ^= values[i];
					if (ini >= 256) ini ^= IRREDUCIBLE;
				}
				tmpMat[k][x] = ini;
			}
		}

		cout << "mc" << '\n';
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				plainMat[y][x] = tmpMat[y][x];
				cout << hex << plainMat[y][x] << " ";
			}
			cout << '\n';
		}
	}

	/*��ȣȭ, ��ȣȭ �Ѵ� ���Ǵ� addroundkey*/
	void AddRoundKey() {
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				plainMat[y][x] ^= keyMat[y][x];
			}
		}

		cout << "ar" << '\n';
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				cout << hex << plainMat[y][x] << " ";
			}
			cout << '\n';
		}
	}

	/*��ȣȭ�� ���Ǵ� shift row*/
	void deShiftRows() {
		for (int i = 1; i < 4; i++) {
			vector<int> change(4);
			for (int j = 0; j < 4; j++) {
				change[j] = plainMat[i][((j-i)+4) % 4];
			}
			plainMat[i] = change;
		}
		cout << "sr" << '\n';
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				cout << hex << plainMat[y][x] << " ";
			}
			cout << '\n';
		}
	}

	/*��ȣȭ�� ���Ǵ� mix colum*/
	void deMixColumns() {
		vector<vector<int>> tmpMat(4);
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) tmpMat[i].push_back(0);
		}
		for (int x = 0; x < 4; x++) {
			vector<int> calc(4);
			for (int y = 0; y < 4; y++) {
				calc[y] = plainMat[y][x];
			}
			for (int k = 0; k < 4; k++) {
				vector<int> values(4);
				for (int y = 0; y < 4; y++) {
					int tmp = calc[y];

					if (invA[k][y] == 9) {
						int origin = tmp;
						for (int i = 0; i < 3; i++) {
							tmp = tmp << 1;
							if (tmp >= 256) tmp ^= IRREDUCIBLE;
						}
						tmp ^= origin;
					}
					else if (invA[k][y] == 11) {
						int origin = tmp;
						for (int i = 0; i < 2; i++) {
							tmp = tmp << 1;
							if (tmp >= 256) tmp ^= IRREDUCIBLE;
						}
						tmp ^= origin;
						tmp = tmp << 1;
						if (tmp >= 256) tmp ^= IRREDUCIBLE;
						tmp ^= origin;
					}
					else if (invA[k][y] == 13) {
						int origin = tmp;
						tmp = tmp << 1;
						if (tmp >= 256) tmp ^= IRREDUCIBLE;
						tmp ^= origin;

						for (int i = 0; i < 2; i++) {
							tmp = tmp << 1;
							if (tmp >= 256) tmp ^= IRREDUCIBLE;
						}
						tmp ^= origin;
					}
					else {
						int origin=tmp;
						tmp = tmp << 1;
						if (tmp >= 256) tmp ^= IRREDUCIBLE;
						tmp ^= origin;
						tmp = tmp << 1;
						if (tmp >= 256) tmp ^= IRREDUCIBLE;
						tmp ^= origin;
						tmp = tmp << 1;
						if (tmp >= 256) tmp ^= IRREDUCIBLE;
					}

					if (tmp >= 256)tmp ^= IRREDUCIBLE;
					values[y] = tmp;
				}
				int ini = values[0];
				for (int i = 1; i < 4; i++) {
					ini ^= values[i];
					if (ini >= 256) ini ^= IRREDUCIBLE;
				}
				tmpMat[k][x] = ini;
			}
		}

		cout << "mc" << '\n';
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				plainMat[y][x] = tmpMat[y][x];
				cout << hex << plainMat[y][x] << " ";
			}
			cout << '\n';
		}
	}

	/*��ȣȭ�� ���Ǵ� SB*/
	void deSubstituteBytes() {
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				plainMat[y][x] = deCalcSBoxValue(plainMat[y][x]);
			}
		}
		cout << "sb" << '\n';
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				cout << hex << plainMat[y][x] << " ";
			}
			cout << '\n';
		}
	}

	/*extended euclid ��꿡 ���Ǵ� binary �ְ����� ���*/
	int deg(int n) {
		vector<int> bin = convertToBinary(n);
		for (int i = bin.size() - 1; i >= 0; i--) {
			if ((n & (1 << i)) != 0) {
				return i;
			}
		}
		return 0;
	}

	/*binary extended euclid�� ���� ���� ���ϱ�*/
	int binaryInverse(int input) {
		int u = input; int v = IRREDUCIBLE; //binary?
		int g1 = 1, g2 = 0, h1 = 0, h2 = 1;
		int d = 0, g = 0, h = 0;
		int degU = deg(input); int degV = 8;
		while (u != 0) {
			int diff = degU - degV;
			if (diff < 0) {
				swap(u, v);
				swap(g1, g2);
				swap(h1, h2);
				diff *= -1;
			}
			u = u ^ (v << diff);
			g1 = g1 ^ (g2 << diff);
			h1 = h1 ^ (h2 << diff);
			degU = deg(u); degV = deg(v);
		}
		return g2;
	}

	/*��ȣȭ sbox ��꿡 ���*/
	int enCalcSBoxValue(int y) { //online
		int inv = binaryInverse(y);
		int add[8] = { 1, 1, 0, 0, 0, 1, 1, 0 };
		bitset<8> b(inv);
		bitset<8> res(0);
		for (int k = 0; k <= 7; k++)
		{
			res[k] = b[k] ^ b[(k + 4) % 8] ^ b[(k + 5) % 8] ^ b[(k + 6) % 8] ^ b[(k + 7) % 8] ^ add[k];
		}
		return res.to_ulong();
	}

	/*��ȣȭ sbox ��꿡 ���*/
	int deCalcSBoxValue(int y) { //online
		int add[8] = { 1, 0, 1, 0, 0, 0, 0, 0 };
		bitset<8> b(y);
		bitset<8> res(0);
		for (int k = 0; k <= 7; k++)
		{
			res[k] = b[(k + 2) % 8] ^ b[(k + 5) % 8] ^ b[(k + 7) % 8] ^ add[k];
		}
		return binaryInverse(res.to_ulong());
	}
	
};

int main(int argc, char* argv[]) {
	AES aes;
	if (argc == 2) {
		cout << argv[1];
		if (strcmp(argv[1], "e") == 0) { //encrypt
			aes.encrpyt("plain.bin");
		}
		else if (strcmp(argv[1], "d") == 0) {//decrypt
			aes.decrypt("cipher.bin");
		}
	}
	return 0;
}