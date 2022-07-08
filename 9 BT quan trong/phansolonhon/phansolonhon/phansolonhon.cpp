#include <iostream>
using namespace std;

class CPhanSo {
private:
	int tu;
	int mau;
public:
	void Nhap();
	void SoSanh(CPhanSo);
};

int main() {
	CPhanSo a, b;
	a.Nhap();
	b.Nhap();
	b.SoSanh(a);
	return 0;
}

void CPhanSo::Nhap() {
	cout << "nhap tu ";
	cin >> tu;
	cout << "nhap mau";
	cin >> mau;
}

void CPhanSo::SoSanh(CPhanSo P) {
	float n = (float)tu / mau;
	float m = (float)P.tu / P.mau;
	if (n > m) {
		cout << tu << "/" << mau;
	}
	else if (m > n) {
		cout << P.tu << "/" << P.mau;
	}
	else cout << "2 phan so bang nhau";
}