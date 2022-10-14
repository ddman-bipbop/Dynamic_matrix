#include "Dmatrix.h"
Dmatrix::Dmatrix()
{
	/*	
	*	1. ������������� �������� �������
	*	2. ��������� ������ ������� � ������
	*	3. ������������ 0 ������� �������� ������� 1�1 (���� �������)
	*/
	Nrow_ = 1;
	Ncol_ = 1;
	row_ = new DmatrixSTR[Nrow_];
	row_->col_ = new double[Ncol_];
	row_->col_[0] = 0;
}



Dmatrix::Dmatrix(int n, int m)
{
	/*
	*	1. ������������� �������� �������
	*	2. ��������� ������ ������� � ������� ������� � ������
	*	3. ��������� 0 ������� �������� ������� 
	*/
	Nrow_ = n;
	Ncol_ = m;
	row_ = new DmatrixSTR[Nrow_];
	for (size_t i = 0; i < Nrow_; i++)
	{
		row_[i].col_ = new double[Ncol_];
	}
	

	for (size_t i = 0; i < Nrow_; i++)
	{
		for (size_t j = 0; j < Ncol_; j++)
		{
			row_[i].col_[j] = 0;
		}
	}
}



Dmatrix::Dmatrix(Dmatrix const& T)
{
	/*
	*	1. ��������� ������� ������� this � ������� ������� T
	*	2. �������� ������ ��� �������� � �����
	*	3. ��������� �������� ������� this � ��������� ������� T
	*/
	
	Nrow_ = T.Nrow_;
	Ncol_ = T.Ncol_;
	row_ = new DmatrixSTR[Nrow_];
	for (size_t i = 0; i < Nrow_; i++)
	{
		row_[i].col_ = new double[Ncol_];
	}

	for (size_t i = 0; i < Nrow_; i++)
	{
		for (size_t j = 0; j < Ncol_; j++)
		{
			row_[i].col_[j] = T.row_[i].col_[j];
		}
	}
}



Dmatrix::~Dmatrix()
{
	/*
	*	1. ������� ������ �������
	*	2. ������� ������
	*/
	for (size_t i = 0; i < Nrow_; i++)
	{
		delete[] row_[i].col_;
	}
	
	delete[] row_;
}



double Dmatrix::At(int i, int j)
{
	return row_[i-1].col_[j-1];
}



void Dmatrix::Print()
{
	for (size_t i = 0; i < Nrow_; i++)
	{
		for (size_t j = 0; j < Ncol_; j++) 
		{
			cout << At(i+1, j+1) << "\t";
		}
		cout << endl;
	}
}



void Dmatrix::Resize(int n, int m)
{
	/*
	*	1. ������� ����� �������
	*	2. ������� ������ �������
	*	3. ������� ������
	*	4. ���� n > Nrow_, �� ��������� ���-�� ����� �� n, ����� ������ �� ��������
	*	5. ���� m > Ncol_, �� ��������� ��� ������� �� m, ����� ������ �� ��������
	*	6. ����������� ������ � ������� ��������� ������
	*/
	Dmatrix tempMat(*this);

	for (size_t i = 0; i < Nrow_; i++)
	{
		delete[] row_[i].col_;
	}

	delete[] row_;

	int tempNrow_ = Nrow_, tempNcol_ = Ncol_;

	if (n > Nrow_) Nrow_ = n;
	if (m > Ncol_) Ncol_ = m;

	row_ = new DmatrixSTR[Nrow_];
	for (size_t i = 0; i < Nrow_; i++)
	{
		row_[i].col_ = new double[Ncol_];
	}

	for (size_t i = 0; i < Nrow_; i++)
	{
		for (size_t j = 0; j < Ncol_; j++)
		{
			row_[i].col_[j] = 0;
		}
	}

	for (size_t i = 0; i < tempNrow_; i++)
	{
		for (size_t j = 0; j < tempNcol_; j++)
		{
			row_[i].col_[j] = tempMat.row_[i].col_[j];
		}
	}
}



int Dmatrix::Insert(int i, int j, double value)
{
	/*	
	*	1. ������ ������� �� ������� �� ������� ������� (�� ������������� �������)
	*		�. ���� �� �������, �� �������� ������� ������� �� �����������
	*		�. ���� ������� �� �������� ������� ������� 
	*/

	// ������������� �������
	if (i < 0 || j < 0) return -1;

	// ���� ������� �� ������� �������, �� ��������� �
	if (i > Nrow_ || j > Ncol_)
		Resize(i,j);

	row_[i-1].col_[j-1] = value;
	return 1;
}



Dmatrix& Dmatrix::Add(Dmatrix const& T)
{
	/*
	*	1. ���� ������� ,������� ���������� � �������, ������ ��� ������ ��� �������, �� ������� �� ��������� �������
	*/
	if (T.Nrow_ != Nrow_ || T.Ncol_ != Ncol_) return *this;

	for (size_t i = 0; i < Nrow_; i++)
	{
		for (size_t j = 0; j < Ncol_; j++)
		{
			row_[i].col_[j] += T.row_[i].col_[j];
		}
	}
	return *this;
}



Dmatrix Dmatrix::Add(Dmatrix const& T) const
{

	Dmatrix R(*this);
	R.Add(T);
	return R;
}



Dmatrix Dmatrix::Add(Dmatrix T) const
{
	T.Add(*this);
	return T;
}



Dmatrix& Dmatrix::Mul(Dmatrix const& T)
{
	/*
	*	1. ���� ����� ���-�� �������� ������� ������� ��������� ���-�� ����� ���������� �������
	*	2. �������� ������� ����� ����� ������ Nrow_ �� T.Ncol_
	*	3. ������� ������� Nrow_ �� T.Ncol_
	*	4. ��������� ��������� ������, ������� ��������� �������� � ����� ��������� �������
	*	5. ���������� �������� �� ������������� ������� � ������� � ������� �
	*/

	Dmatrix tempMat(Nrow_, T.Ncol_);
	double tempValue = 0;


	if (Ncol_ == T.Nrow_) 
	{
		for (size_t i = 0; i < Nrow_; i++) {
			for (size_t j = 0; j < T.Ncol_; j++) {
				auto temp = 0;
				for (size_t k = 0; k < Ncol_; k++) 
				{
					auto temp1 = At(i+1, k+1);		// ��� �������� ��������
					auto temp2 = T.row_[k].col_[j];	//

					temp += temp1 * temp2;
				}
				tempMat.Insert(i+1, j+1, temp);
			}
		}

		this->Resize(tempMat.Nrow_, tempMat.Ncol_);

		

		for (size_t i = 0; i < Nrow_; i++)
		{
			for (size_t j = 0; j < Ncol_; j++)
			{
				this->Insert(i + 1, j + 1, tempMat.At(i+1, j+1));
			}
		}
		
		return *this;
	}
	return *this;

}



Dmatrix Dmatrix::Mul(Dmatrix const& T) const
{
	Dmatrix R(*this);
	R.Mul(T);
	return R;
}



Dmatrix Dmatrix::Mul(Dmatrix T) const
{
	T.Mul(*this);
	return T;
}



Dmatrix Dmatrix::Mul(double a) const
{
	for (size_t i = 0; i < Nrow_; i++)
	{
		for (size_t j = 0; j < Ncol_; j++)
		{
			row_[i].col_[j] *= a;
		}
	}
	return *this;
}



Dmatrix& Dmatrix::operator=(Dmatrix const& R)
{
	if (&R == this) return *this;

	for (size_t i = 0; i < Nrow_; i++)
	{
		delete[] row_[i].col_;
	}
	delete[] row_;

	Ncol_ = R.Ncol_;
	Nrow_ = R.Nrow_;


	row_ = new DmatrixSTR[Nrow_];
	for (size_t i = 0; i < Nrow_; i++)
	{
		row_[i].col_ = new double[Ncol_];
	}

	for (size_t i = 0; i < Nrow_; i++)
	{
		for (size_t j = 0; j < Ncol_; j++)
		{
			row_[i].col_[j] = R.row_[i].col_[j];
		}
	}

	return *this;
}



Dmatrix Dmatrix::operator+(Dmatrix T) const
{
	T.Add(*this);
	return T;
}



Dmatrix Dmatrix::operator*(Dmatrix T) const
{
	T.Mul(*this);
	return T;
}



Dmatrix Dmatrix::operator-(Dmatrix T) const
{
	T.Mul(-1);
	T.Add(*this);
	return T;
}



bool Dmatrix::operator==(Dmatrix const& T)
{
	for (size_t i = 0; i < Nrow_; i++)
	{
		for (size_t j = 0; j < Ncol_; j++)
		{
			if (row_[i].col_[j] != T.row_[i].col_[j])
				return false;
		}
	}
	return true;
}



bool Dmatrix::operator!=(Dmatrix const& T)
{
	for (size_t i = 0; i < Nrow_; i++)
	{
		for (size_t j = 0; j < Ncol_; j++)
		{
			if (row_[i].col_[j] != T.row_[i].col_[j])
				return true;
		}
	}
	return false;
}



ostream& operator<<(ostream& out, Dmatrix const& T)
{
	for (size_t i = 0; i < T.Nrow_; i++)
	{
		for (size_t j = 0; j < T.Ncol_; j++)
		{
			cout << T.row_[i].col_[j] << "\t";
		}
		cout << endl;
	}
	return out;
}



istream& operator>>(istream& in, Dmatrix const& T)
{
	return in;
}