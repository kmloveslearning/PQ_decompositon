#pragma once

#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;

constexpr auto ZERO = 1e-6;;
// �������ӱ�ṹ�壬���а������ӱ�����λ�ñ�ͽ���������
struct Factor_table  
{
	double factor_table[100] = { 0 };  // ������ӱ�
	int swap_table[100] = { 0 }; // ��Ž���λ�ñ�
	int swap_num[100] = { 0 };  // ��Ž���������
};

/*
* �������ɽ�����һά������л���
* ���������������������ֱ���������Ҫ������������
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
* �������ɽ���������Ԫ�ؽ��л���
* ���������������������ֱ���������Ҫ������Ԫ�ص�ַ
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
* �������ɴ�ӡ1��2ά����
* ������ʹ���˶�̬���ԣ���������������������ӡһά����Ĳ���������������������ӡ��ά����Ĳ�������������������������
* ��ά������Ϊ�������뱾����ʱ����Ҫʹ��ǿ������ת��������ά������ת��Ϊ��ͨ�ĵ�ַ����print_array((double*)test1,2,3);
*/
void print_array(double* array, int a, int b)  // ��ӡdouble�Ͷ�ά����
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

void print_array(double* array, int a)  // ��ӡdouble��һά����
{

	for (int i = 0; i < a; i++)
	{
		printf("%lf ", *(array + i));
	}
	printf("\n");
}

void print_array(int* array, int a)  // ��ӡint��һά����
{

	for (int i = 0; i < a; i++)
	{
		printf("%ld ", *(array + i));
	}
	printf("\n");
}

/*
* �������ɽ���ά����С��ZERO��ֵ����
* ����������������������ά������׵�ַ����������
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
* �������ɽ���������е�ϵ������ת��Ϊ�����Ǿ���ͬʱ�����б任Ҳ�������ڳ����У����ջ�õĶ�ά������ԭ�������ͬ�ⷽ������������
* ���������������ӱ�����λ�ñ�ͽ���������;������������ͬ���������
* ����������3���������ֱ������ӱ���ά���飨������󣩵Ķ�̬������ʽ����ά���������
* ��ʹ�ñ�����ʱ���������������н���ά������ת��Ϊһ��ָ����ʽ��Ҳ���ǽ���ά������Ԫ�ص�ַ���뺯����������Ϊ�˽���������������Ķ�ά���鴫�뱾�����ĺ�������������
*/
void matrix2triangular(Factor_table &FactorTable, double* arr_aug, int n)
{
	int i = 0;  // iΪ��������
	int j = 0;  // jΪ������������ʱ����
	int k = 0;  // kΪ������������ʱ����
	int m = 0;

	// ʹ�ö�ά��̬���鷽ʽ����������󣬽��β�arr_aug����ȫ����ֵ��aug_array����aug_array�Ĵ���ͬʱ��ı�arr_aug�����ҽ�ǰ���ͷŲ�����Ӱ��arr_aug
	double** aug_array = new double* [n];
	for (int i = 0; i < n; i++) {
		aug_array[i] = arr_aug + (n+1) * i;
	}
	double** factor_table = new double* [n];
	for (int i = 0; i < n; i++) {
		factor_table[i] = FactorTable.factor_table + n * i;
	}

	// �����ε�����Ҫ�������������������Ԫ��Ϊ��������ڵ�һ��
	for (i = 0; i < n; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			if (fabs(aug_array[i][i]) <= ZERO)  // ����Խ�Ԫ��Ϊ���������������򣬵�i��ÿ����һ�Σ�swap_num[i]��ֵ��һ��swap_table��¼�µ�i����ڼ��н���
			{
				swap_arrays(aug_array[i], aug_array[j], n + 1);
				FactorTable.swap_table[m++] = j;
				FactorTable.swap_num[i]++;
			}
			else { break; }
		}

		factor_table[i][i] = aug_array[i][i];  // ���ӱ�ĶԽ�Ԫ�ر���ϵ������ÿ�ε���ʱ�Ķ�Ӧλ��Ԫ��
		if ((fabs(aug_array[i][i])) > ZERO)  // �γ�ͬ����������ϵ������ĶԽǾ���
		{
			if (fabs(aug_array[i][i]-1) > ZERO)
			{
				for (j = i; j < n + 1; j++)
				{
					aug_array[i][j] /= factor_table[i][i];  // ʹ�öԽ�Ԫ��Ϊ1
				}
			}
		}

		for (j = i + 1; j < n; j++)  // ���ͬ����������ʣ�ಿ�ֲ��������ӱ�ķǶԽ�Ԫ�ز���
		{
			if (fabs(aug_array[j][i]) <= ZERO)
			{
				factor_table[j][i] = 0;
				continue;
			}
			else
			{
				factor_table[j][i] = aug_array[j][i];  // ���ӱ�������Ǿ�������ڵ�����������ȥ���еĶ�ӦԪ�ص�ֵ
				for (k = i; k < n + 1; k++)
				{
					aug_array[j][k] -= factor_table[j][i] * aug_array[i][k];
				}
			}
		}
	}
	// �����յ�ϵ�������������Ԫ�ظ�ֵ�����ӱ�Ķ�Ӧλ�ã��γ���ȫ�����ӱ�
	for (i = 0; i < n - 1; i++)
	{
		for (j = i+1; j < n; j++)
		{
			factor_table[i][j] = aug_array[i][j];
		}
	}
	//// ��ӡ�����������ӱ�
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

	refine_arrays((double*)aug_array[0], n, n + 1);  // ����ά�����й�С��Ԫ����0
	refine_arrays((double*)factor_table[0], n, n + 1);  // ����ά�����й�С��Ԫ����0
	delete[] aug_array;
	delete[] factor_table;
}



/*
* �������ɶ�ϵ������Ϊ�����Ǿ����������������⣬�õ������У�Ҳ����ÿ��������ÿ��x�Ľ�
* ����������3���������ֱ��Ƕ�ά���飨������󣩵Ķ�̬������ʽ����ά���������,������Ľ�������������ֻ�ǽ������������ܸı���������ֵ
* ��ʹ�ñ�����ʱ���������������н���ά������ת��Ϊָ����ʽ��Ҳ���ǽ���ά�����׵�ַ���뺯����������Ϊ�˽���������������Ķ�ά���鴫�뱾�����ĺ�������������
*/
void triangular_soving(double* arr_temp, int n, double*x)
{
	int i = 0;
	int j = 0;
	int flag = 0;  // ��¼�����Ƿ��н�

	// ʹ��copy������ʹ�ò��ı�ԭʼ����
	double* arr = new double[n * (n+1)];
	std::copy(arr_temp, arr_temp + n * (n+1), arr);
	// ʹ�ö�ά��̬���鷽ʽ����������󣬽��β�arr����ȫ����ֵ��aug_array����aug_array�Ĵ���ͬʱ��ı�arr�����ҽ�ǰ���ͷŲ�����Ӱ��arr
	double** aug_array = new double* [n];
	for (i = 0; i < n; i++) {
		aug_array[i] = arr + (n+1)*i;
	}
	//ͨ����ѭ������ѭ���Գ������������
	for (i = n - 1; i >= 0; i--)
	{
		if (fabs(aug_array[i][i]) < ZERO) { cout << "your matrix can't be sovled, please review your input" << endl; flag = 1; break; }  // �����޽⣬��flag=1������ѭ��
		for (j = n - 1; j >= i + 1; j--)
		{
			aug_array[i][n] -= aug_array[i][j] / aug_array[j][j] * aug_array[j][n];
		}
	}
	refine_arrays((double*)aug_array[0], n, n + 1);  // ����ά�����й�С��Ԫ����0
	if (flag == 0)
	{
		cout << "your solution of augmented matrix is as follows" << endl;
		// ��ӡ��������Ľ�
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


/*��������ʹ�����ӱ�������Է�����
* ��������4���������ֱ������ӱ����󷽳��鳣���С���������Ŀ����������������������������н�ʹ�ò��ܸı��ֵʹ��copy���������˴���
* �������е�ǰ�������Ϊ�������ӱ��������ر��ĺ���������������Ϊ���ؼ�����������Ĳ���
*/
void factor2x(Factor_table FactorTable, double* b_temp, int n, double* x)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int m = 0;

	// ������̬һά���飬��������洢�޸Ĺ����������
	double* aug_array = new double[n*(n+1)];

	double* b = new double[n * n];
	std::copy(b_temp, b_temp + n * n, b);
	// ������̬��ά���飬�洢���ӱ���������˫�±���ʣ�
	double** factor_table = new double* [n];
	for (int i = 0; i < n; i++) {
		factor_table[i] = FactorTable.factor_table + n * i;
	}

	//print_array(b, n);  // ��ӡ��ʼb
	// �������ӱ�����λ�ñ�ͽ���������������
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

	//for (i = 0; i < n; i++)  // ��ӡ�������ӱ�����b
	//{
	//	printf("%lf ", b[i]);
	//}
	// 
	// ������ӱ�ʹ����ĳ����У���ȡ������ͬ���������
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
	// ��ⷽ����
	triangular_soving(aug_array, n, x);

	delete[] factor_table;
	delete[] b;
	delete[] aug_array;
}

/*
* ������������������Ľ�,����ø������������ɵ����ӱ�����λ�ñ�ͽ���������
* ����������4���������ֱ��Ƕ�ά���飨������󣩵Ķ�̬������ʽ��ϵ������Ľ����������������ӱ�
* ��������ǰ��������Ϊ���м���������Ĳ��������ĸ�����Ϊ���ؼ�����������Ĳ���
*/
void gaus_excuting(double* aug_array, int n, double* x, Factor_table &FactorTable)
{
	// ����������ϵ������ת��Ϊ�����Ǿ��󣬲���ȡ���ӱ�
	matrix2triangular(FactorTable, aug_array, n);
	// ֱ��ʹ�ûش�����ⷽ����
	triangular_soving(aug_array, n, x);
}

/*
* ������Ϊ�������������û���������ȡ�û����������;�������
* �������Ϊ���������Ԫ��λ���������������
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
* ��������������2��3��4ά��Ԫһ�����Է����飬�����ɶ�Ӧ�ĳ�����*2
*����������3���������ֱ�Ϊ���������Ԫ�ص�ַ������������������ɵĳ����С�
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