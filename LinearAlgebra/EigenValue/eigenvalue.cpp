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

	//판별식
	double s = (a - d)*(a - d) + (4 * b*c);
	if (s > 0) {
		//근 두개
		x = ((a + d) + sqrt(s)) / 2;
		y = ((a + d) - sqrt(s)) / 2;
		std::cout << "고유값 " << endl << "λ1: " << x << endl
			<< "λ2: " << y << endl;
		eigenVectorTwo(arr);
	}
	else if (s == 0) {
		//근 1개
		x = ((a + d) / 2);
		std::cout << "고유값 : " << endl << "λ1: " << x << endl;
		eigenVectorOne(arr);
	}
	else {
		cout << "λ를 구할수 없음(허근)" << endl;
		exit(0);
	}
}

void eigenVectorTwo(double arr[2][2]) {
	//고유벡터
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++)
		{
			arr1[i][j] = arr[i][j];
		}
	}
	//1번째값

	arr1[0][0] = arr1[0][0] - x;
	arr1[1][1] = arr1[1][1] - x;

	double e = arr1[0][0];
	double f = arr1[0][1];
	double g = arr1[1][0];
	double h = arr1[1][1];
	

	//방정식 하나 나와서 미지수 잡을때
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
	//연립방정식 두개 나올때(식한개면 걍 하나에 1 대입하고 나머지 계산)
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
	//	2번째값

	arr1[0][0] = arr1[0][0] - y;
	arr1[1][1] = arr1[1][1] - y;

	e = arr1[0][0];
	f = arr1[0][1];
	g = arr1[1][0];
	h = arr1[1][1];

	//행사다리꼴 한 행렬 조건문 나누기


	//방정식 하나 나와서 미지수 잡을때
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
	//연립방정식 두개 나올때(식한개면 걍 하나에 1 대입하고 나머지 계산)
	else {
		//reducedRowEchelon(arr1);
		//infinite일때
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
	//1번째값

	arr1[0][0] = arr1[0][0] - x;
	arr1[1][1] = arr1[1][1] - x;

	double e = arr1[0][0];
	double f = arr1[0][1];
	double g = arr1[1][0];
	double h = arr1[1][1];
	
	//행사다리꼴 한 행렬 조건문 나누기


	//방정식 하나 나와서 미지수 잡을때
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


//P구하고 역행렬이랑 D 출력하기
void printP() {
	P[0][0] = i;
	P[1][0] = j;
	P[0][1] = r;
	P[1][1] = s;

	cout << "P는" << endl;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++)
		{
			cout << P[i][j] << ' ';
		}
		cout << endl;
	}

}
//PAP역행렬 =D인지 확인
bool det() {
	double det = 0;
	det = P[0][0] * P[1][1] - P[0][1] * P[1][0];
	if (det == 0)
		return 0; //대각화 ㄴㄴ
	else
		return 1;
}

void isDia() {
	if (det() != 0)
		cout << "대각화 가능" << endl;
	else
	{
		cout << "대각화 불가능(허근)";
		exit(0);
	}

}
void printInverseP() {
	//다시 계산
	double a = P[0][0];
	double b=P[0][1];
	double c=P[1][0];
	double d=P[1][1];
	double u = a*d - b*c;

	if (u == 0) {
		cout << "역행렬 없음" << endl;
		exit(0);
	}
	double w = -b;
	double t = -c;
	Pinverse[0][0] = d / u;
	Pinverse[0][1] = w /u; //음수를 인식못함
	Pinverse[1][0] = t / u;
	Pinverse[1][1] = a / u;

	cout << "P 역행렬은" << endl;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++)
		{
			cout << Pinverse[i][j] << ' ';
		}
		cout << endl;
	}
}

void printD() {
	cout << "D는(소수점5째자리 반올림)" << endl;
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

	

	cout << "(P역행렬)X A X P = D 가 되는지 확인, 계산한 D는(소수점5째자리 반올림) " << endl;
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
	cout << "행렬의 데이터를 입력하세요(2by2): ";
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
	cout << "입력한 행렬" << endl;
	printMatrix();
	
	//대각화 안되는거
	/*if (det() == 0) {
		cout << "허근";
		exit(0);
	}
	else {*/
		//고유값과 고유벡터 출력
		ce();
		printD();
		cD();
	/*}*/
	isDia();


}