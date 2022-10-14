#pragma once
#include <iostream>
#include <locale>
#include <vector>
#include <string>

using namespace std;


class Dmatrix
{
public:
	class DmatrixSTR
	{
	public:
		double* col_; // динамический массив столбцов
	};
	DmatrixSTR* row_; // динамический массив строк
	int Nrow_; // кол-во строк
	int Ncol_; // кол-во столбцов

	Dmatrix(); // по умолчанию
	Dmatrix(int n,int m);
	Dmatrix(Dmatrix const& T);// конструктор копирования
	~Dmatrix(); // деструктор

	// вывод массива
	void Print(); 
	// получить элемент по индексу
	double At(int i,int j); 
	// вставить/изменить элемент
	int Insert(int i, int j, double value); 

	// арифметические операции

	
	Dmatrix Add(Dmatrix const& T) const;
	Dmatrix Add(Dmatrix T) const;
	Dmatrix& Add(Dmatrix const& T);
	
	Dmatrix& Mul(Dmatrix const& T);
	Dmatrix Mul(Dmatrix const& T) const;
	Dmatrix Mul(Dmatrix T) const;
	Dmatrix Mul(double a) const;

	// операторы

	// арифметическеи операторы

	Dmatrix& operator=(Dmatrix const& R);
	Dmatrix operator+(Dmatrix T)const;
	Dmatrix operator*(Dmatrix T)const;
	Dmatrix operator-(Dmatrix T)const;

	// логические операторы

	bool operator==(Dmatrix const& T);
	bool operator!=(Dmatrix const& T);

	// операторы потока
	 
	friend ostream& operator<<(ostream& out, Dmatrix const& T);
	friend istream& operator>>(istream& in, Dmatrix const& T);

private:
	// расширить матрицу до размеров n X m
	void Resize(int n, int m); 
};