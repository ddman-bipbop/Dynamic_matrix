#include "Dmatrix.h"
Dmatrix::Dmatrix()
{
	/*	
	*	1. Инициализация размеров матрицы
	*	2. Выделение памяти столбцу и строке
	*	3. Присваивание 0 первому элументу матрицы 1х1 (ноль матрица)
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
	*	1. Инициализация размеров матрицы
	*	2. Выделение памяти строкам и каждому столбцу в строке
	*	3. Присвоить 0 каждому элементу массива 
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
	*	1. Присвоить размеры матрицы this к размера матрицы T
	*	2. Выделить память для столбцов и строк
	*	3. Присвоить элементы матрицы this к элементам матрицы T
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
	*	1. Удалить каждый столбец
	*	2. Удалить строки
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
	*	1. Сделать копию матрицы
	*	2. Удалить каждый столбец
	*	3. Удалить строки
	*	4. Если n > Nrow_, то увеличить кол-во строк до n, иначе ничего не изменять
	*	5. Если m > Ncol_, то увеличить все столбцы до m, иначе ничего не изменять
	*	6. Добавленные строки и столбцы заполнить нулями
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
	*	1. Узнать выходит ли элемент за границы матрицы (не отрицательные границы)
	*		а. Если не выходит, то ЗАМЕНИТЬ элемент матрицы по координатам
	*		б. Если выходит то Изменить размеры матрицы 
	*/

	// отрицательные границы
	if (i < 0 || j < 0) return -1;

	// Если выходит за границы матрицы, то расширить её
	if (i > Nrow_ || j > Ncol_)
		Resize(i,j);

	row_[i-1].col_[j-1] = value;
	return 1;
}



Dmatrix& Dmatrix::Add(Dmatrix const& T)
{
	/*
	*	1. Если матрица ,которую складываем с текущей, больше или меньше чем текущая, то вернуть не изменённую матрицу
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
	*	1. Надо чтобы кол-во столбцов текущей матрицы равнялось кол-ву строк умножаемой матрицы
	*	2. Конечная матрица будет иметь размер Nrow_ на T.Ncol_
	*	3. Создать матрицу Nrow_ на T.Ncol_
	*	4. Выполнить умножение матриц, результ умножения записать в ранее созданную матрицу
	*	5. Переписать значения из перемноженной матрицы в текущую и вернуть её
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
					auto temp1 = At(i+1, k+1);		// для проверки значений
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