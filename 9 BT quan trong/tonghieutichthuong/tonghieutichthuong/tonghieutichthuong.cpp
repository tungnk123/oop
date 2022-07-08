#include <iostream>
using namespace std;

class PhanSo {
public:
    int tu;
    int mau;
public:
    void Nhap();
    void RutGon();
    void Xuat();
    PhanSo Tong(PhanSo);
    PhanSo Hieu(PhanSo);
    PhanSo Tich(PhanSo);
    PhanSo Thuong(PhanSo&);
    void DauTru();
};

int main() {
    PhanSo ps1, ps2, kq;
    ps1.Nhap();
    ps2.Nhap();
    ps1.RutGon();
    ps2.RutGon();
    kq = ps1.Tong(ps2);
    kq.Xuat();
    kq = ps1.Hieu(ps2);
    kq.Xuat();
    kq = ps1.Tich(ps2);
    kq.Xuat();
    kq = ps1.Thuong(ps2);
    kq.Xuat();
    return 0;

}

void PhanSo::Nhap() {
    cin >> tu;
    if (tu == 0) mau = 0;
    else cin >> mau;
    while (mau == 0) {
        cin >> mau;
    }

}

void PhanSo::RutGon() {
    int a = tu;
    int b = mau;

    if (a < 0) {
        a = -a;
    }
    if (b < 0) {
        b = -b;
    }
    if (a != 0 && b != 0) {
        while (a != b) {
            if (a > b) a -= b;
            else b -= a;
        }
        tu /= a;
        mau /= a;
    }
    else {
        if (a > b) {
            tu /= a;
            mau /= a;
        }
        else {
            tu /= b;
            mau /= b;
        }
    }


}

void PhanSo::Xuat() {
    cout << tu << "/" << mau << endl;
}

PhanSo PhanSo::Tong(PhanSo x) {
    PhanSo temp;
    temp.tu = tu * x.mau + mau * x.tu;
    temp.mau = mau * x.mau;
    temp.RutGon();
    temp.DauTru();
    return temp;
}

PhanSo PhanSo::Hieu(PhanSo x) {
    PhanSo temp;
    temp.tu = tu * x.mau - mau * x.tu;
    temp.mau = mau * x.mau;
    temp.RutGon();
    temp.DauTru();
    return temp;
}

PhanSo PhanSo::Tich(PhanSo x) {
    PhanSo temp;
    temp.tu = tu * x.tu;
    temp.mau = mau * x.mau;
    temp.RutGon();
    temp.DauTru();
    return temp;
}
PhanSo PhanSo::Thuong(PhanSo& x) {

    PhanSo temp;
    temp.tu = tu * x.mau;
    temp.mau = mau * x.tu;

    temp.RutGon();
    temp.DauTru();
    return temp;
}
void PhanSo::DauTru() {
    if (tu > 0 && mau < 0) {
        mau = -mau;
        tu = -tu;
    }
    else if (tu < 0 && mau < 0) {
        tu = -tu;
        mau = -mau;
    }
}
