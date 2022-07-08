#include <iostream>
using namespace std;

struct PhanSo {
	int tu;
	int mau;
};

void Nhap (PhanSo&);
int KiemTraAmHayDuong(PhanSo);

int main() {
	PhanSo ps;
	Nhap(ps);
	int kq = KiemTraAmHayDuong(ps);
	switch (kq) {
	case 1: cout << "phan so duong ";
			break;
	case -1: cout << "phan so am";
		break;
	case 0: cout << "phan so = 0";
	}
	return 0;
}
void Nhap(PhanSo &x) {
	cout << "nhap tu";
	cin >> x.tu;
	cout << "nhap mau";
	cin >> x.mau;
}
int KiemTraAmHayDuong(PhanSo x) {
	if (x.tu * x.mau > 0) return 1;
	else if (x.tu * x.mau < 0) {
		return -1;
	}
	else return 0;
}