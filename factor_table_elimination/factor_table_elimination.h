#pragma once

#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;

constexpr auto ZERO = 1e-6;;
// 定义因子表结构体，其中包含因子表、交换位置表和交换次数表
struct Factor_table  
{
	double factor_table[100] = { 0 };  // 存放因子表
	int swap_table[100] = { 0 }; // 存放交换位置表
	int swap_num[100] = { 0 };  // 存放交换次数表
};

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
* 本函数可将两个整形元素进行互换
* 本函数包含两个参数，分别是两个需要互换的元素地址
*/
void swap_element(double* ele1, double* ele2)
{
	double temp;
	double i = 0;
	temp = *ele1;
	*ele1 = *ele2;
	*ele2 = temp;
}

/*
* 本函数可打印1、2维数组
* 本函数使用了多态特性，包括二或三个参数。打印一维数组的参数是数组名、列数，打印二维数组的参数是数组名、行数、列数，
* 二维数组作为参数传入本函数时，需要使用强制类型转换，将二维数组名转换为普通的地址。如print_array((double*)test1,2,3);
*/
void print_array(double* array, int a, int b)  // 打印double型二维数组
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

void print_array(double* array, int a)  // 打印double型一维数组
{

	for (int i = 0; i < a; i++)
	{
		printf("%lf ", *(array + i));
	}
	printf("\n");
}

void print_array(int* array, int a)  // 打印int型一维数组
{

	for (int i = 0; i < a; i++)
	{
		printf("%ld ", *(array + i));
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
* 本函数会生成因子表、交换位置表和交换次数表;本函数会生成同解增广矩阵
* 本函数包括3个参数，分别是因子表、二维数组（增广矩阵）的动态数组形式，二维数组的行数
* 在使用本函数时，需在主调函数中将二维数组名转化为一阶指针形式，也就是将二维数组首元素地址传入函数，这样是为了解决将任意行列数的二维数组传入本函数的函数泛用性问题
*/
void matrix2triangular(Factor_table &FactorTable, double* arr_aug, int n)
{
	int i = 0;  // i为迭代次数
	int j = 0;  // j为迭代过程中临时变量
	int k = 0;  // k为迭代过程中临时变量
	int m = 0;

	// 使用二维动态数组方式处理增广矩阵，将形参arr_aug内容全部赋值给aug_array，对aug_array的处理同时会改变arr_aug，而且将前者释放并不会影响arr_aug
	double** aug_array = new double* [n];
	for (int i = 0; i < n; i++) {
		aug_array[i] = arr_aug + (n+1) * i;
	}
	double** factor_table = new double* [n];
	for (int i = 0; i < n; i++) {
		factor_table[i] = FactorTable.factor_table + n * i;
	}

	// 将本次迭代需要处理的所有行向量中首元素为非零的置于第一行
	for (i = 0; i < n; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			if (fabs(aug_array[i][i]) <= ZERO)  // 如果对角元素为零则启动交换程序，第i行每交换一次，swap_num[i]数值加一，swap_table记录下第i行与第几行交换
			{
				swap_arrays(aug_array[i], aug_array[j], n + 1);
				FactorTable.swap_table[m++] = j;
				FactorTable.swap_num[i]++;
			}
			else { break; }
		}

		factor_table[i][i] = aug_array[i][i];  // 因子表的对角元素便是系数矩阵每次迭代时的对应位置元素
		if ((fabs(aug_array[i][i])) > ZERO)  // 形成同解增广矩阵的系数矩阵的对角矩阵
		{
			if (fabs(aug_array[i][i]-1) > ZERO)
			{
				for (j = i; j < n + 1; j++)
				{
					aug_array[i][j] /= factor_table[i][i];  // 使得对角元素为1
				}
			}
		}

		for (j = i + 1; j < n; j++)  // 填充同解增广矩阵的剩余部分并生成因子表的非对角元素部分
		{
			if (fabs(aug_array[j][i]) <= ZERO)
			{
				factor_table[j][i] = 0;
				continue;
			}
			else
			{
				factor_table[j][i] = aug_array[j][i];  // 因子表的下三角矩阵就是在迭代过程中消去列中的对应元素的值
				for (k = i; k < n + 1; k++)
				{
					aug_array[j][k] -= factor_table[j][i] * aug_array[i][k];
				}
			}
		}
	}
	// 将最终的系数矩阵的上三角元素赋值给因子表的对应位置，形成完全的因子表
	for (i = 0; i < n - 1; i++)
	{
		for (j = i+1; j < n; j++)
		{
			factor_table[i][j] = aug_array[i][j];
		}
	}
	//// 打印增广矩阵和因子表
	//for (int i = 0; i < n; i++) {
	//	for (int j = 0; j < n + 1; j++) {
	//		cout << aug_array[i][j] << " ";
	//	}
	//	cout << endl;
	//}

	cout << "your factor table is as follows" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n ; j++) {
			cout << factor_table[i][j] << " ";
		}
		cout << endl;
	}

	refine_arrays((double*)aug_array[0], n, n + 1);  // 将二维数组中过小的元素置0
	refine_arrays((double*)factor_table[0], n, n + 1);  // 将二维数组中过小的元素置0
	delete[] aug_array;
	delete[] factor_table;
}



/*
* 本函数可对系数矩阵为上三角矩阵的增广矩阵进行求解，得到常数列，也就是每个方程组每个x的解
* 本函数包括3个参数，分别是二维数组（增广矩阵）的动态数组形式，二维数组的行数,方程组的解向量。本函数只是解增广矩阵而不能改变增广矩阵的值
* 在使用本函数时，需在主调函数中将二维数组名转化为指针形式，也就是将二维数组首地址传入函数，这样是为了解决将任意行列数的二维数组传入本函数的函数泛用性问题
*/
void triangular_soving(double* arr_temp, int n, double*x)
{
	int i = 0;
	int j = 0;
	int flag = 0;  // 记录方程是否有解

	// 使用copy函数，使得不改变原始数组
	double* arr = new double[n * (n+1)];
	std::copy(arr_temp, arr_temp + n * (n+1), arr);
	// 使用二维动态数组方式处理增广矩阵，将形参arr内容全部赋值给aug_array，对aug_array的处理同时会改变arr，而且将前者释放并不会影响arr
	double** aug_array = new double* [n];
	for (i = 0; i < n; i++) {
		aug_array[i] = arr + (n+1)*i;
	}
	//通过行循环和列循环对常数列逐个运算
	for (i = n - 1; i >= 0; i--)
	{
		if (fabs(aug_array[i][i]) < ZERO) { cout << "your matrix can't be sovled, please review your input" << endl; flag = 1; break; }  // 方程无解，给flag=1，跳出循环
		for (j = n - 1; j >= i + 1; j--)
		{
			aug_array[i][n] -= aug_array[i][j] / aug_array[j][j] * aug_array[j][n];
		}
	}
	refine_arrays((double*)aug_array[0], n, n + 1);  // 将二维数组中过小的元素置0
	if (flag == 0)
	{
		cout << "your solution of augmented matrix is as follows" << endl;
		// 打印出方程组的解
		for (i = 0; i < n; i++)
		{
			cout << "x" << i << "=" << aug_array[i][n] << endl;
		}
		for (i = 0; i < n; i++)
		{
			x[i] = aug_array[i][n];
		}
	}

	delete[] arr;
	delete[] aug_array;

}


/*本函数可使用因子表法求解线性方程组
* 本函数有4个参数，分别是因子表、所求方程组常数列、方程组数目（增广矩阵行数）、解向量，其中仅使用不能改变的值使用copy函数进行了处理
* 本函数中的前五个参数为进行因子表法计算所必备的函数，第六个参数为承载计算结果所必须的参数
*/
void factor2x(Factor_table FactorTable, double* b_temp, int n, double* x)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int m = 0;

	// 创建动态一维数组，最后用来存储修改过的增广矩阵
	double* aug_array = new double[n*(n+1)];

	double* b = new double[n * n];
	std::copy(b_temp, b_temp + n * n, b);
	// 创建动态二维数组，存储因子表，并可以用双下标访问，
	double** factor_table = new double* [n];
	for (int i = 0; i < n; i++) {
		factor_table[i] = FactorTable.factor_table + n * i;
	}

	//print_array(b, n);  // 打印初始b
	// 依据因子表、交换位置表和交换次数表处理常数列
	for (i = 0; i < n; i++)
	{
		if (FactorTable.swap_num[i] == 0)
		{
			for (j = i; j < n; j++)
			{
				if (j == i)
				{
					b[j] /= factor_table[i][i];
				}
				else
				{
					b[j] -= factor_table[j][i] * b[i];
				}
			}
		}
		else
		{
			for (k = FactorTable.swap_num[i]; k > 0; k--)
			{
				swap_element(&b[i], &b[FactorTable.swap_table[m++]]);
			}
			FactorTable.swap_num[i] = 0;
			i--;
		}
	}

	//for (i = 0; i < n; i++)  // 打印经过因子表处理后的b
	//{
	//	printf("%lf ", b[i]);
	//}
	// 
	// 结合因子表和处理后的常数列，获取完整的同解增广矩阵
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n + 1; j++)
		{
			*(aug_array + i * (n + 1) + j) = 0;
		}
	}

	for (i = 0; i < n; i++)
	{
		for (j = i; j < n + 1; j++)
		{
			if (i == j)
			{
				*(aug_array + i * (n + 1) + j) = 1;
			}
			else if (j == n)
			{
				*(aug_array + i * (n + 1) + j) = b[i];
			}
			else
			{
				*(aug_array + i * (n + 1) + j) = factor_table[i][j];
			}
		}
	}
	// 求解方程组
	triangular_soving(aug_array, n, x);

	delete[] factor_table;
	delete[] b;
	delete[] aug_array;
}

/*
* 本函数可求出增广矩阵的解,并获得根据求解过程生成的因子表、交换位置表和交换次数表
* 本函数包括4个参数，分别是二维数组（增广矩阵）的动态数组形式，系数矩阵的阶数，解向量，因子表
* 本函数的前两个参数为进行计算所必须的参数，后四个参数为承载计算结果所必须的参数
*/
void gaus_excuting(double* aug_array, int n, double* x, Factor_table &FactorTable)
{
	// 将增广矩阵的系数矩阵转换为上三角矩阵，并获取因子表
	matrix2triangular(FactorTable, aug_array, n);
	// 直接使用回代法求解方程组
	triangular_soving(aug_array, n, x);
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
* 本函数可以生成2、3、4维多元一次线性方程组，并生成对应的常数列*2
*本函数包括3个参数，分别为增广矩阵首元素地址、增广矩阵行数和生成的常数列。
*/
int test_sample_generation(double* aug_array, int n, double* b)
{
	int i = 0;
	double aug_array2[6] = { 2,1,3,1,2,0 };
	//double aug_array3[12] = { 1,1,1,12,1,2,5,22,1,1,0,10 };
	double aug_array3[12] = { 1,1,1,12,1,1,0,10,1,2,5,22 };
	//double aug_array4[20] = { 1,2,1,1,5,2,1,0,0,3,1,0,1,0,2,1,0,0,1,2 };
	double aug_array4[20] = { 1,1,1,1,4,2,1,1,2,6,1,1,1,0,3,1,2,0,0,3 };

	switch (n)
	{
	case 2:
		for (i = 0; i < n * (n + 1); i++)
		{
			aug_array[i] = aug_array2[i];
		}
		for (i = 0; i < n; i++)
		{
			b[i] = *(aug_array2 + n + i * (n + 1));
			b[i] *= 2;
		}
		break;
	case 3:
		for (i = 0; i < n * (n + 1); i++)
		{
			aug_array[i] = aug_array3[i];
		}
		for (i = 0; i < n; i++)
		{
			b[i] = *(aug_array3 + n + i * (n + 1));
			b[i] *= 2;
		}
		break;
	case 4:
		for (i = 0; i < n * (n + 1); i++)
		{
			aug_array[i] = aug_array4[i];
		}
		for (i = 0; i < n; i++)
		{
			b[i] = *(aug_array4 + n + i * (n + 1));
			b[i] *= 2;
		}
		break;
	}
	return n;
}