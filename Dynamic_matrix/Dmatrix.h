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
		double* col_; // ������������ ������ ��������
	};
	DmatrixSTR* row_; // ������������ ������ �����
	int Nrow_; // ���-�� �����
	int Ncol_; // ���-�� ��������

	Dmatrix(); // �� ���������
	Dmatrix(int n,int m);
	Dmatrix(Dmatrix const& T);// ����������� �����������
	~Dmatrix(); // ����������

	// ����� �������
	void Print(); 
	// �������� ������� �� �������
	double At(int i,int j); 
	// ��������/�������� �������
	int Insert(int i, int j, double value); 

	// �������������� ��������

	
	Dmatrix Add(Dmatrix const& T) const;
	Dmatrix Add(Dmatrix T) const;
	Dmatrix& Add(Dmatrix const& T);
	
	Dmatrix& Mul(Dmatrix const& T);
	Dmatrix Mul(Dmatrix const& T) const;
	Dmatrix Mul(Dmatrix T) const;
	Dmatrix Mul(double a) const;

	// ���������

	// �������������� ���������

	Dmatrix& operator=(Dmatrix const& R);
	Dmatrix operator+(Dmatrix T)const;
	Dmatrix operator*(Dmatrix T)const;
	Dmatrix operator-(Dmatrix T)const;

	// ���������� ���������

	bool operator==(Dmatrix const& T);
	bool operator!=(Dmatrix const& T);

	// ��������� ������
	 
	friend ostream& operator<<(ostream& out, Dmatrix const& T);
	friend istream& operator>>(istream& in, Dmatrix const& T);

private:
	// ��������� ������� �� �������� n X m
	void Resize(int n, int m); 
};