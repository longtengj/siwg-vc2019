#pragma once
#include <iostream>
using namespace std;

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>
#include <chrono>   

//namespace matrix {
	//namespace ublas = boost::numeric::ublas;
	//using namespace boost::numeric::ublas;
	//using namespace std;
	//using namespace chrono;

	//std::unique_ptr<ShardFileThreadPool> g_pMatrixConvert = std::make_unique<ShardFileThreadPool>(4, false);

	template<typename T>
	class MatrixConvert
	{
	public:
		MatrixConvert(size_t lens) : M(8, lens / 8), nRows_(8192), nCols_(lens / nRows_), OtD(nRows_, nCols_)
		{
		}
		MatrixConvert(const MatrixConvert& other) = delete;

		~MatrixConvert()
		{

		}

		inline void matrixProcess(const T* rawData)
		{
			//reshape 8*(len/8) 8*102400
			for (size_t idxRow = 0; idxRow < M.size1(); idxRow++)
			{
				for (size_t idxCol = 0; idxCol < M.size2(); idxCol++)
				{
					M(idxRow, idxCol) = rawData[idxCol + idxRow * M.size2()];
					//M(idxRow, idxCol) = idxRow;
				}
			}
			//std::cout << ublas::row(M, 0) << std::endl;
			//std::cout << ublas::column(M, 0) << std::endl;
			//std::cout << ublas::column(M, 1024) << std::endl;

			const size_t bankLen = M.size2();
			const size_t oneChanLen = (bankLen / 1024);
			const size_t bankChRows = 1024;
			//ublas::matrix<T> bankCh(bankChRows, oneChanLen);

			for (uint8_t i = 0; i < 8; i++)
			{
				auto bankRd = boost::numeric::ublas::row(M, i);
				//reshape 1024*oneChanLen
				for (size_t idxRow = 0; idxRow < bankChRows; idxRow++)
				{
					for (size_t idxCol = 0; idxCol < oneChanLen; idxCol++)
					{
						OtD(idxRow + i * bankChRows, idxCol) = bankRd[idxCol + idxRow * oneChanLen];
					}
				}
				//std::cout << ublas::row(OtD, i * bankChRows) << std::endl;

				//ublas::project(ublas::row(M, i), ublas::range(0, oneChanLen * 1024 + 0));

				//ublas::matrix_range<ublas::matrix<T>> B(bankCh, ublas::range(beginCh, endCh), ublas::range(0, oneChanLen));
			}
		}

		void ToHostMatrix(T** mat, int* rows, int* cols) const
		{
			*mat = new T[Rows() * Columns()];
			*rows = Rows();
			*cols = Columns();
			for (size_t i = 0; i < Rows(); i++) {
				for (size_t j = 0; j < Columns(); j++) {
					(*mat)[i * Columns() + j] = (*this)(i, j);
				}
			}
		}
	public:
		inline size_t Rows() const { return nRows_; }

		inline size_t Columns() const { return nCols_; }
		inline T& operator()(size_t i, size_t j) const
		{
			return OtD[i, j];
		}
	private:
		boost::numeric::ublas::matrix<T> M;

		size_t nCols_;
		size_t nRows_{ 8192 };

		boost::numeric::ublas::matrix<T> OtD;
	};
//}

class example {
private:
    int num;
public:
	example();
    void say_hello(void);
    void change(int din);
    int get_num() {
		return num;
	}
};