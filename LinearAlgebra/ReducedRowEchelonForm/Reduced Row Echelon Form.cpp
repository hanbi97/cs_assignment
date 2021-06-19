#include <iostream>
#include <algorithm>
using namespace std;

int n = 0;
int m = 0;
double matrix[7][7] = {
	{},
	{},
	{},
	{},
	{},
	{},
	{}
};


void inputMatrix() {
	cout << "����� �����͸� �Է��ϼ���: ";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
		{
			cin >> matrix[i][j];
		}
	}
}

void printMatrix() {
	cout << "���: " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
		{
			cout << matrix[i][j] << ' ';
		}
		cout << endl;
	}
}

void reducedRowEchelon() {
	double a = 0;
	double b = 0;
	//�� �� ���� 0�� �ƴѼ��� ���� ���� ���� ����
	 // [i][i]�� 0���� �ƴ��� �˻� �����ִ� �ӽú���
	 // ���� 0�̸� �������� ��ȯ�ؾ� �Ǵϱ� ��� ���� ���� �ʿ��� ����
	for (int i = 0; i < n; i++) {
		double tmp = matrix[i][i];
		int c = 1;
		
			while (tmp == 0 && c != 0) {
				//change
				for (int j = 0; j < m; j++) {
					swap(matrix[i][j], matrix[i + c][j]);
				}
				//�ٲٰ� �ٽ� ii�� 0�� �ƴ��� Ȯ��
				tmp = matrix[i][i];
				if (tmp != 0)
					c = 0; //���̻� �ȹٲٴϱ� 0���� ��������
				else if (tmp == 0)
					c++;
			
		}
		//���� ���ϰ� ���	
		//�� �ռ��� 1�� �����
			a = matrix[i][i];
			if (a != 0&&a!=1) {
				for (int k = 0; k < m; k++) {
					matrix[i][k] = matrix[i][k] / a;
				}
			}
	
		//����ϱ�
		//0�ƴ� ���� �������� ���ؼ� ������ ����� 
			for (int j = i + 1; j < n; j++) //+1: �����ٺ��ؾߵǴϱ�
			{
				b = matrix[j][i] / matrix[i][i];
				for (int k = 0; k < m; k++) {
					matrix[j][k] = matrix[j][k] - b*matrix[i][k];
				}
			}

			
	}
	//1�ƴ� �������� 0���� �������� (�Ųٷ�..)
	//�� �������� ���� 1�̱� ������ �ϳ� ���ٺ��� ���־���
	double d = 0;
	for (int i = n-1; i >=0; i--) {
		for (int j = i-1;j >= 0; j--)
		{
			for (int k = m-1; k >= 0; k--) {//������ �� ã��

				d = matrix[j][i];
				matrix[j][k] = matrix[j][k] - (d*matrix[i][k]);
			}
		}
		
	}
}







int main() {

	cout << "�� n �� m �Է��Ͻÿ�: ";
	cin >> n >> m;

	inputMatrix();
	printMatrix();
	reducedRowEchelon();
	cout << "reducedRowEchelon: " << endl;
	printMatrix();
}
