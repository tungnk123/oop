#include<iostream>
using namespace std;
struct day
{
	int d, m, y;
};
void nhap(day& x);
void nextday(day x);
int main()
{
	day x;
	cout << "\nNHAP NGAY, THANG, NAM:\n";
	nhap(x);
	cout << "\nngay tiep theo la: ";
	nextday(x);
	system("pause");
}
void nextday(day x)
{
	int k = 0;
	x.d++;
	switch (x.m)
	{
	case 1:case 3: case 5: case 7: case 8: case 10:
		if (x.d > 31)
		{
			x.d = 1; x.m++;
		}
		break;
	case 4: case 6: case 9: case 11:
		if (x.d > 30)
		{
			x.d = 1; x.m++;
		}
		break;
	case 12:
		if (x.d > 31)
		{
			x.d = 1; x.m = 1; x.y++;
		}
		break;
	case 2:
		if (x.y % 400 == 0 || (x.y % 4 == 0 && x.y % 100 != 0)) k = 1;
		if (k == 1 && x.d > 29)
		{
			x.d = 1; x.m++;
		}
		if (k == 0 && x.d > 28)
		{
			x.d = 1; x.m++;
		}
	}
	cout << x.d << "/" << x.m << "/" << x.y;
}
void nhap(day& x)
{
	int kt, k = 0;
	do {
		kt = 0;
		cout << "\nngay:"; cin >> x.d;
		cout << "\nthang: "; cin >> x.m;
		cout << "\nnam: "; cin >> x.y;
		switch (x.m)
		{
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			if (x.d <= 0 || x.d > 31) kt = 1;
			break;
		case 4: case 6: case 9: case 11:
			if (x.d <= 0 || x.d > 30) kt = 1;
			break;
		case 2:
			if (x.y % 400 == 0 || (x.y % 4 == 0 && x.y % 100 != 0)) k = 1;
			if (k == 1 && (x.d <= 0 || x.d > 29)) kt = 1;
			if (k == 0 && (x.d <= 0 || x.d > 28)) kt = 1;
			break;
		default: kt = 1; break;
		}
		if (kt == 1) cout << "\nkhong hop le!";
	} while (kt);
}