#include <iostream>
#include <string>
using namespace std;

class CHocSinh {
private: 
	int toan;
	int van;
	string name;
	int ma;
	float anh;
	int ngaythangnamsinh;
public:
	void Nhap();
	void Xuat();
	void CaoHon15();
};

int main() {
	int n;

	cin >> n;
	CHocSinh a[100];
	for (int i = 0; i < n; i++) {
		a[i].Nhap();
		a[i].CaoHon15();
	}
	
	
}

void CHocSinh::Nhap() {
	cout << "nhap ten cua hoc sinh : ";
		getline(cin, name);
	cout << "nhap diem toan : ";
	cin >> toan;
	cout << "nhap diem van :";
	cin >> van;
	cout << "nhap diem anh :";
	cin >> anh;
	cout << "nhap ma :";
	cin >> ma;
	cout << "nhap ngay thang nam sinh :";
	cin >> ngaythangnamsinh;
}

void CHocSinh::Xuat() {
	cout << ma << endl;
	cout << name << endl;
	cout << ngaythangnamsinh << endl;
	cout << toan << endl;
	cout << van << endl;
	cout << anh;
}
void CHocSinh::CaoHon15() {
	if (toan + van + anh > 15) {
		Xuat();
	}
}



