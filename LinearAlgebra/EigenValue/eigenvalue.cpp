#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

double arr[2][2];
double arr1[3][3];
double arr2[2][3];

double P[2][2];

double Pinverse[2][2];
double D[2][2];
double checkD[2][2];

double D1[2][2];
double x ;
double y ;
double i;
double j;
double r;
double s;
void printP();
void printInverseP();
void printD();
void ce();
void eigenVectorOne(double arr[2][2]);
void eigenVectorTwo(double arr[2][2]);


void ce() {
	double a = arr[0][0];
	double b = arr[0][1];
	double c = arr[1][0];
	double d = arr[1][1];

	//�Ǻ���
	double s = (a - d)*(a - d) + (4 * b*c);
	if (s > 0) {
		//�� �ΰ�
		x = ((a + d) + sqrt(s)) / 2;
		y = ((a + d) - sqrt(s)) / 2;
		std::cout << "������ " << endl << "��1: " << x << endl
			<< "��2: " << y << endl;
		eigenVectorTwo(arr);
	}
	else if (s == 0) {
		//�� 1��
		x = ((a + d) / 2);
		std::cout << "������ : " << endl << "��1: " << x << endl;
		eigenVectorOne(arr);
	}
	else {
		cout << "�븦 ���Ҽ� ����(���)" << endl;
		exit(0);
	}
}

void eigenVectorTwo(double arr[2][2]) {
	//��������
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++)
		{
			arr1[i][j] = arr[i][j];
		}
	}
	//1��°��

	arr1[0][0] = arr1[0][0] - x;
	arr1[1][1] = arr1[1][1] - x;

	double e = arr1[0][0];
	double f = arr1[0][1];
	double g = arr1[1][0];
	double h = arr1[1][1];
	

	//������ �ϳ� ���ͼ� ������ ������
	if ((e == 0 && f == 0) && (g != 0 && h != 0) || (g == 0 && h == 0) && (e != 0 && f != 0)) {
		if (e == 0 && f == 0) {
			i = 1;
			j = (-arr1[1][0]) / arr1[1][1];
			cout << "v1 = " << endl
				<< i << endl << j << endl;

		}
		else if (g == 0 && h == 0) {
			i = 1;
			j = (-arr1[0][0]) / arr1[0][1];
			cout << "v1 = " << endl
				<< i << endl << j << endl;
		}
	}
	 if (e == 0 && f == 0 && g == 0 && h == 0) {
		i = 1;
		j = 0;
		cout << "v1 = " << endl
			<< i << endl << j << endl;
	}

	else if ((e == 0 && g == 0) && (f != 0 && h != 0) || (f == 0 && h == 0) && (e != 0 && g != 0)) {
		i = 1;
		j = 0;
		cout << "v1 = " << endl
			<< i << endl << j << endl;
	}
	//���������� �ΰ� ���ö�(���Ѱ��� �� �ϳ��� 1 �����ϰ� ������ ���)
	else {
		if (arr1[0][0] / arr1[1][0] == arr1[0][1] / arr1[1][1])
		{
			i = 1;
			j = (-arr1[0][0]) / arr1[0][1];
			cout << "v1 = " << endl
				<< i << endl << j << endl;
		}
		
	}

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++)
		{
			arr1[i][j] = arr[i][j];
		}
	}
	//	2��°��

	arr1[0][0] = arr1[0][0] - y;
	arr1[1][1] = arr1[1][1] - y;

	e = arr1[0][0];
	f = arr1[0][1];
	g = arr1[1][0];
	h = arr1[1][1];

	//���ٸ��� �� ��� ���ǹ� ������


	//������ �ϳ� ���ͼ� ������ ������
	if ((e == 0 && f == 0) && (g != 0 && h != 0) || (g == 0 && h == 0) && (e != 0 && f != 0)) {
		if (e == 0 && f == 0) {
			r = 1;
			s = (-arr1[1][0]) / arr1[1][1];
			cout << "v2 = " << endl
				<< r << endl << s << endl;

		}
		else if (g == 0 && h == 0) {
			r = 1;
			s = (-arr1[0][0]) / arr1[0][1];
			cout << "v2 = " << endl
				<< r << endl << s << endl;
		}	
	}

	if (e == 0 && f == 0 && g == 0 && h == 0) {
		r = 0;
		s = 1;
		cout << "v2 = " << endl
			<< r << endl << s << endl;

	}
	else if ((e == 0 && g == 0) && (f != 0 && h != 0) || (f == 0 && h == 0) && (e != 0 && g!= 0)) {
		r = 1;
		s = 0;
		cout << "v2 = " << endl
			<< r << endl << s << endl;
	}
	//���������� �ΰ� ���ö�(���Ѱ��� �� �ϳ��� 1 �����ϰ� ������ ���)
	else {
		//reducedRowEchelon(arr1);
		//infinite�϶�
		if (arr1[0][0] / arr1[1][0] == arr1[0][1] / arr1[1][1])
		{
			r = 1;
			s = (-arr1[0][0]) / arr1[0][1];
			cout << "v2 = " << endl
				<< r << endl << s << endl;
		}
	}

	printP();
	printInverseP();
	D[0][0] = x;
	D[1][1] = y;

}

void eigenVectorOne(double arr[2][2]) {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++)
		{
			arr1[i][j] = arr[i][j];
		}
	}
	//1��°��

	arr1[0][0] = arr1[0][0] - x;
	arr1[1][1] = arr1[1][1] - x;

	double e = arr1[0][0];
	double f = arr1[0][1];
	double g = arr1[1][0];
	double h = arr1[1][1];
	
	//���ٸ��� �� ��� ���ǹ� ������


	//������ �ϳ� ���ͼ� ������ ������
	if (e == 0 && f == 0 && g == 0 && h == 0) {
		i = 1;
		s = 1;
		cout << "v1 = " << endl
			<< i << endl << 0 << endl;
		cout << "v2 = " << endl
			<< 0 << endl << s << endl;
		j = 0;
		r = 0;

	}
	if ((e == 0 && f == 0) &&(g!=0 &&h!=0)|| (g == 0 && h == 0)&& (e != 0 && f != 0)) {
		if (e == 0 && f == 0) {
			i = 1;
			j= (-arr1[1][0]) / arr1[1][1];
			cout << "v1 = " << endl
				<< i << endl << j << endl;
			r = i;
			s = j;

		}
		else if (g == 0 && h == 0 && (e != 0 && f != 0)) {
			i = 1;
			j = (-arr1[0][0]) / arr1[0][1];
			cout << "v1 = " << endl
				<< i << endl << j << endl;
			r = i;
			s = j;
		}
	}
	
	else if ((e == 0 && g == 0)&&(f!= 0 && h != 0) || (f == 0 && h == 0) && (e != 0 && g != 0)) {
		i = 1;
		j = 0;
		cout << "v1 = " << endl
			<< i << endl << j << endl;
		r = i;
		s = j;
	}
	
	else {
		if (arr1[0][0] / arr1[1][0] == arr1[0][1] / arr1[1][1])
		{
			i = 1;
			j= (-arr1[0][0]) / arr1[0][1];
			cout << "v1 = " << endl
				<< i << endl << j<< endl;
			r = i;
			s = j;
		}
	}
	
	printP();
	printInverseP();
	D[0][0] = x;
	D[1][1] = x;

}


//P���ϰ� ������̶� D ����ϱ�
void printP() {
	P[0][0] = i;
	P[1][0] = j;
	P[0][1] = r;
	P[1][1] = s;

	cout << "P��" << endl;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++)
		{
			cout << P[i][j] << ' ';
		}
		cout << endl;
	}

}
//PAP����� =D���� Ȯ��
bool det() {
	double det = 0;
	det = P[0][0] * P[1][1] - P[0][1] * P[1][0];
	if (det == 0)
		return 0; //�밢ȭ ����
	else
		return 1;
}

void isDia() {
	if (det() != 0)
		cout << "�밢ȭ ����" << endl;
	else
	{
		cout << "�밢ȭ �Ұ���(���)";
		exit(0);
	}

}
void printInverseP() {
	//�ٽ� ���
	double a = P[0][0];
	double b=P[0][1];
	double c=P[1][0];
	double d=P[1][1];
	double u = a*d - b*c;

	if (u == 0) {
		cout << "����� ����" << endl;
		exit(0);
	}
	double w = -b;
	double t = -c;
	Pinverse[0][0] = d / u;
	Pinverse[0][1] = w /u; //������ �νĸ���
	Pinverse[1][0] = t / u;
	Pinverse[1][1] = a / u;

	cout << "P �������" << endl;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++)
		{
			cout << Pinverse[i][j] << ' ';
		}
		cout << endl;
	}
}

void printD() {
	cout << "D��(�Ҽ���5°�ڸ� �ݿø�)" << endl;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++)
		{
			cout << floor(D[i][j] * 100000 + 0.5) / 100000 << ' ';
		}
		cout << endl;
	}
}


void cD() {
	
	D1[0][0] = Pinverse[0][0] * arr[0][0] + Pinverse[0][1] * arr[1][0];
	D1[0][1] = Pinverse[0][0] * arr[0][1] + Pinverse[0][1] * arr[1][1];
	D1[1][0] = Pinverse[1][0] * arr[0][0] + Pinverse[1][1] * arr[1][0];
	D1[1][1] = Pinverse[1][0] * arr[0][1] + Pinverse[1][1] * arr[1][1];
	

	checkD[0][0] = D1[0][0] * P[0][0] + D1[0][1] * P[1][0];
	checkD[0][1] = D1[0][0] * P[0][1] + D1[0][1] * P[1][1];
	checkD[1][0] = D1[1][0] * P[0][0] + D1[1][1] * P[1][0];
	checkD[1][1] = D1[1][0] * P[0][1] + D1[1][1] * P[1][1];

	

	cout << "(P�����)X A X P = D �� �Ǵ��� Ȯ��, ����� D��(�Ҽ���5°�ڸ� �ݿø�) " << endl;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++)
		{
			//floor(i * 1000) / 1000
			cout << floor(checkD[i][j]*100000+0.5)/100000 << ' ';
		}
		cout << endl;
	}

}


void inputMatrix() {
	cout << "����� �����͸� �Է��ϼ���(2by2): ";
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++)
		{
			cin >> arr[i][j];
		}
	}
}
void printMatrix() {

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++)
		{
			cout << arr[i][j] << ' ';
		}
		cout << endl;
	}
}
int main() {
	inputMatrix();
	cout << "�Է��� ���" << endl;
	printMatrix();
	
	//�밢ȭ �ȵǴ°�
	/*if (det() == 0) {
		cout << "���";
		exit(0);
	}
	else {*/
		//�������� �������� ���
		ce();
		printD();
		cD();
	/*}*/
	isDia();


}