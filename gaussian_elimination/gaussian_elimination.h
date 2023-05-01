#pragma once

#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;
constexpr auto ZERO = 1e-6;;

/*
* 本函数可将两个一维数组进行互换
* 本函数包含两个参数，分别是两个需要互换的数组名
*/
void swap_arrays(double* array1, double* array2, int n)
{

	double temp;
	int i = 0;
	if (n <= 0)
	{
		printf("the input array is wrong!");
	}
	else
	{
		for (i = 0; i < n; i++)
		{
			temp = array1[i];
			array1[i] = array2[i];
			array2[i] = temp;
		}
	}

}

/*
* 本函数可打印1、2维数组
* 本函数使用了多态特性，包括二或三个参数。打印一维数组的参数是数组名、列数，打印二维数组的参数是数组名、行数、列数，
* 二维数组作为参数传入本函数时，需要使用强制类型转换，将二维数组名转换为普通的地址。如print_array((double*)test1,2,3);
*/
void print_array(double* array, int a, int b)
{
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < b; j++)
		{
			printf("%lf ", *(array + b * i + j));
		}
		printf("\n");
	}
}

void print_array(double* array, int a)
{

	for (int i = 0; i < a; i++)
	{
		printf("%lf ", *(array + i));
	}
	printf("\n");
}

/*
* 本函数可将二维数组小于ZERO的值置零
* 本函数包含三个参数，二维数组的首地址和行数列数
*/
void refine_arrays(double* array, int a, int b)
{
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < b; j++)
		{
			if (fabs(*(array + i * b + j)) < ZERO)
			{
				*(array + i * b + j) = 0.0;
			}
		}
	}
}

/*
* 本函数可将增广矩阵中的系数矩阵转化为上三角矩阵，同时初等行变换也会作用于常数列，最终获得的二维数组是原增广矩阵同解方程组的增广矩阵
* 本函数包括3个参数，分别是二维数组（增广矩阵）的动态数组形式，即指向指针的指针，指针中每一个元素都对应二维数组的一行的首地址。第2和3参数是二维数组的行和列数
* 在使用本函数时，需在主调函数中将二维数组名转化为指针形式，也就是将二维数组首地址传入函数，这样是为了解决将任意行列数的二维数组传入本函数的函数泛用性问题
*/
void matrix2triangular(double* arr, int n, int b)
{
	int i = 0;  // i为迭代次数
	int j = 0;  // j为迭代过程中临时变量
	int k = 0;  // k为迭代过程中临时变量
	double factor = 0;  // factor为初等行变换时所乘的因数

	// 使用二维动态数组方式处理增广矩阵，将形参arr内容全部赋值给aug_matrix，对aug_matrix的处理同时会改变arr，而且将前者释放并不会影响arr
	double** aug_matrix = new double* [n];
	for (int i = 0; i < n; i++) {
		aug_matrix[i] = arr + b * i;
	}

	// 将本次迭代需要处理的所有行向量中首元素为非零的置于第一行
	for (i = 0; i < n; i++)
	{
		for (j = i + 1; j < n; j++)
		{

			if (fabs(aug_matrix[i][i]) < ZERO)
			{
				swap_arrays(aug_matrix[i], aug_matrix[j], n + 1);
			}
			else { break; }
		}

		for (j = i + 1; j < n; j++)
		{
			if (fabs(aug_matrix[j][i]) < ZERO)
				continue;

			else
			{
				factor = aug_matrix[j][i] / aug_matrix[i][i];  //factor中必须是aug_matrix[j][i]，不能是aug_matrix[i + 1][i]
				for (k = i; k < n + 1; k++)
				{
					aug_matrix[j][k] -= factor * aug_matrix[i][k];
				}
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n + 1; j++) {
			cout << aug_matrix[i][j] << " ";
		}
		cout << endl;
	}
	refine_arrays((double*)aug_matrix[0], n, n + 1);  // 将二维数组中过小的元素置0
	delete[] aug_matrix;
}

/*
* 本函数可对系数矩阵为上三角矩阵的增广矩阵进行求解，得到常数列，也就是每个方程组每个x的解
* 本函数包括3个参数，分别是二维数组（增广矩阵）的动态数组形式，即指向指针的指针，指针中每一个元素都对应二维数组的一行的首地址。第2和3参数是二维数组的行和列数
* 在使用本函数时，需在主调函数中将二维数组名转化为指针形式，也就是将二维数组首地址传入函数，这样是为了解决将任意行列数的二维数组传入本函数的函数泛用性问题
*/
void triangular_soving(double* arr, int n, int b)
{
	int i = 0;
	int j = 0;
	// 使用二维动态数组方式处理增广矩阵，将形参arr内容全部赋值给aug_matrix，对aug_matrix的处理同时会改变arr，而且将前者释放并不会影响arr
	double** aug_matrix = new double* [n];
	for (i = 0; i < n; i++) {
		aug_matrix[i] = arr + b * i;
	}
	//通过行循环和列循环对常数列逐个运算
	for (i = n - 1; i >= 0; i--)
	{
		for (j = n - 1; j >= i + 1; j--)
		{
			if (fabs(aug_matrix[j][j]) < ZERO) { continue; }
			else {
				aug_matrix[i][n] -= aug_matrix[i][j] / aug_matrix[j][j] * aug_matrix[j][n];
			}
		}
		aug_matrix[i][n] /= aug_matrix[i][i];
		aug_matrix[i][i] /= aug_matrix[i][i];
	}
	refine_arrays((double*)aug_matrix[0], n, n + 1);  // 将二维数组中过小的元素置0
	delete[] aug_matrix;
}

/*
* 本函数可求出增广矩阵的解
* 本函数包括2个参数，分别是二维数组（增广矩阵）的动态数组形式，即指向指针的指针，指针中每一个元素都对应二维数组的一行的首地址。第2是系数矩阵的阶数
*/
void gaus_excuting(double*temp, double*x, int n)
{
	int i = 0;
	// 接下来的关键函数中的第一个参数是二维数组的第一个元素的地址，所以如果用二维数组名传参，用（double*)强转就行。如果用一位数组名，则直接传递即可
	matrix2triangular(temp, n, n + 1);
	triangular_soving(temp, n, n + 1);
	cout << "your solution of augmented matrix is as follows" << endl;
	// 打印出方程组的解
	for (i = 1; i < n + 1; i++)
	{
		cout << "x" << i << "=" << temp[(n + 1) * i - 1] << endl;
	}
	for (i = 1; i < n+1; i++)
	{
		x[i-1] = temp[(n + 1) * i - 1];
	}
}

/*
* 本函数为交互函数，与用户交互，获取用户的增广矩阵和矩阵行数
* 输入参数为增广矩阵首元素位置与增广矩阵行数
*/
int interaction(double* temp, int n)
{
	int i = 0;
	cout << "please input the row of your augmented matrix" << endl;
	cin >> n;
	cout << "please input your augmented matrix" << endl;
	for (i = 0; i < n * (n + 1); i++)
	{
		cin >> temp[i];
	}
	cout << "your augmented matrix is as follows" << endl;
	print_array(temp, n, n + 1);
	cout << "your upper triangular augmented matrix is as follows" << endl;
	return n;
}

/*
*提供测试样例的函数，包含两个参数，分别为增广矩阵首元素位置与增广矩阵行数。
*/
int test_sample_generation(double* temp, int n)
{
	int i = 0;
	double aug_array2[6] = { 2,1,3,1,2,0 };
	double aug_array3[12] = { 1,1,1,12,1,-4,0,0,1,2,5,22 };
	double aug_array4[20] = { 1,2,3,4,7,1,1,1,1,2,1,0,0,1,3,0,0,1,0,0 };

	switch (n)
	{
	case 2:
		for (i = 0; i < n * (n + 1); i++)
		{
			temp[i] = aug_array2[i];
		}
		break;
	case 3:
		for (i = 0; i < n * (n + 1); i++)
		{
			temp[i] = aug_array3[i];
		}
		break;
	case 4:
		for (i = 0; i < n * (n + 1); i++)
		{
			temp[i] = aug_array4[i];
		}
		break;
	}
	return n;
}