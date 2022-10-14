#include "Dmatrix.h"
#include "List.h"

int main() 
{
	setlocale(LC_ALL, "rus");

	Dmatrix a(2, 3);
	a.Insert(1, 1, 1);
	a.Insert(1, 2, 2);
	a.Insert(1, 3, 3);
	a.Insert(2, 1, 4);
	a.Insert(2, 2, 5);
	a.Insert(2, 3, 6);
	a.Print();
	cout << "--------------------------------" << endl;
	cout << a.At(1, 1) << endl;
	cout << "--------------------------------" << endl;
	Dmatrix b(3, 2);
	b.Insert(1, 1, 1);
	b.Insert(1, 2, 2);
	b.Insert(2, 1, 3);
	b.Insert(2, 2, 4);
	b.Insert(3, 1, 5);
	b.Insert(3, 2, 6);
	b.Print();
	cout << "--------------------------------" << endl;
	Dmatrix c = a * b;
	c.Print();
	cout << "--------------------------------" << endl;
	cout << "--------------------------------" << endl;

	List < Dmatrix> ls;
	a.Insert(10, 10, 35);
	a.Insert(9, 9, 50.555);
	ls.add_back(a);
	
	ls.print();

	//...
	cout << "--------------------------------" << endl;
	cout << "--------------------------------" << endl;
	
	Dmatrix z,v;
	z.Insert(1, 1, 1);
	z.Insert(1, 2, 1);
	z.Insert(2, 1, 1);
	z.Insert(2, 2, 1);
	z.Print();
	cout << "--------------------------------" << endl;
	v.Insert(1, 1, 1);
	v.Insert(1, 2, 1);
	v.Insert(2, 1, 1);
	v.Insert(2, 2, 1);
	v.Print();
	cout << "--------------------------------" << endl;
	cout << z - v << endl;
	return 0;
}