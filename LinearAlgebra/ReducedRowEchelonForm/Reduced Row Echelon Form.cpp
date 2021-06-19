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
	cout << "행렬의 데이터를 입력하세요: ";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
		{
			cin >> matrix[i][j];
		}
	}
}

void printMatrix() {
	cout << "행렬: " << endl;
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
	//맨 앞 수가 0이 아닌수가 가장 위로 오게 만듬
	 // [i][i]가 0인지 아닌지 검사 도와주는 임시변수
	 // 값이 0이면 다음꺼랑 교환해야 되니까 계속 세기 위해 필요한 변수
	for (int i = 0; i < n; i++) {
		double tmp = matrix[i][i];
		int c = 1;
		
			while (tmp == 0 && c != 0) {
				//change
				for (int j = 0; j < m; j++) {
					swap(matrix[i][j], matrix[i + c][j]);
				}
				//바꾸고 다시 ii가 0이 아닌지 확인
				tmp = matrix[i][i];
				if (tmp != 0)
					c = 0; //더이상 안바꾸니까 0으로 만들어버림
				else if (tmp == 0)
					c++;
			
		}
		//빼고 더하고 계산	
		//맨 앞수를 1로 만들기
			a = matrix[i][i];
			if (a != 0&&a!=1) {
				for (int k = 0; k < m; k++) {
					matrix[i][k] = matrix[i][k] / a;
				}
			}
	
		//계산하기
		//0아닌 가장 가까운수랑 비교해서 나누고 계산함 
			for (int j = i + 1; j < n; j++) //+1: 다음줄비교해야되니까
			{
				b = matrix[j][i] / matrix[i][i];
				for (int k = 0; k < m; k++) {
					matrix[j][k] = matrix[j][k] - b*matrix[i][k];
				}
			}

			
	}
	//1아닌 나머지를 0으로 만들어야함 (거꾸로..)
	//젤 마지막줄 끝은 1이기 때문에 하나 전줄부터 없애야함
	double d = 0;
	for (int i = n-1; i >=0; i--) {
		for (int j = i-1;j >= 0; j--)
		{
			for (int k = m-1; k >= 0; k--) {//곱해줄 수 찾기

				d = matrix[j][i];
				matrix[j][k] = matrix[j][k] - (d*matrix[i][k]);
			}
		}
		
	}
}







int main() {

	cout << "행 n 열 m 입력하시오: ";
	cin >> n >> m;

	inputMatrix();
	printMatrix();
	reducedRowEchelon();
	cout << "reducedRowEchelon: " << endl;
	printMatrix();
}
