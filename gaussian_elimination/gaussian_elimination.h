#pragma once

#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;
constexpr auto ZERO = 1e-6;;

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
* �������ɴ�ӡ1��2ά����
* ������ʹ���˶�̬���ԣ���������������������ӡһά����Ĳ���������������������ӡ��ά����Ĳ�������������������������
* ��ά������Ϊ�������뱾����ʱ����Ҫʹ��ǿ������ת��������ά������ת��Ϊ��ͨ�ĵ�ַ����print_array((double*)test1,2,3);
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
* ����������3���������ֱ��Ƕ�ά���飨������󣩵Ķ�̬������ʽ����ָ��ָ���ָ�룬ָ����ÿһ��Ԫ�ض���Ӧ��ά�����һ�е��׵�ַ����2��3�����Ƕ�ά������к�����
* ��ʹ�ñ�����ʱ���������������н���ά������ת��Ϊָ����ʽ��Ҳ���ǽ���ά�����׵�ַ���뺯����������Ϊ�˽���������������Ķ�ά���鴫�뱾�����ĺ�������������
*/
void matrix2triangular(double* arr, int n, int b)
{
	int i = 0;  // iΪ��������
	int j = 0;  // jΪ������������ʱ����
	int k = 0;  // kΪ������������ʱ����
	double factor = 0;  // factorΪ�����б任ʱ���˵�����

	// ʹ�ö�ά��̬���鷽ʽ����������󣬽��β�arr����ȫ����ֵ��aug_matrix����aug_matrix�Ĵ���ͬʱ��ı�arr�����ҽ�ǰ���ͷŲ�����Ӱ��arr
	double** aug_matrix = new double* [n];
	for (int i = 0; i < n; i++) {
		aug_matrix[i] = arr + b * i;
	}

	// �����ε�����Ҫ�������������������Ԫ��Ϊ��������ڵ�һ��
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
				factor = aug_matrix[j][i] / aug_matrix[i][i];  //factor�б�����aug_matrix[j][i]��������aug_matrix[i + 1][i]
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
	refine_arrays((double*)aug_matrix[0], n, n + 1);  // ����ά�����й�С��Ԫ����0
	delete[] aug_matrix;
}

/*
* �������ɶ�ϵ������Ϊ�����Ǿ����������������⣬�õ������У�Ҳ����ÿ��������ÿ��x�Ľ�
* ����������3���������ֱ��Ƕ�ά���飨������󣩵Ķ�̬������ʽ����ָ��ָ���ָ�룬ָ����ÿһ��Ԫ�ض���Ӧ��ά�����һ�е��׵�ַ����2��3�����Ƕ�ά������к�����
* ��ʹ�ñ�����ʱ���������������н���ά������ת��Ϊָ����ʽ��Ҳ���ǽ���ά�����׵�ַ���뺯����������Ϊ�˽���������������Ķ�ά���鴫�뱾�����ĺ�������������
*/
void triangular_soving(double* arr, int n, int b)
{
	int i = 0;
	int j = 0;
	// ʹ�ö�ά��̬���鷽ʽ����������󣬽��β�arr����ȫ����ֵ��aug_matrix����aug_matrix�Ĵ���ͬʱ��ı�arr�����ҽ�ǰ���ͷŲ�����Ӱ��arr
	double** aug_matrix = new double* [n];
	for (i = 0; i < n; i++) {
		aug_matrix[i] = arr + b * i;
	}
	//ͨ����ѭ������ѭ���Գ������������
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
	refine_arrays((double*)aug_matrix[0], n, n + 1);  // ����ά�����й�С��Ԫ����0
	delete[] aug_matrix;
}

/*
* ������������������Ľ�
* ����������2���������ֱ��Ƕ�ά���飨������󣩵Ķ�̬������ʽ����ָ��ָ���ָ�룬ָ����ÿһ��Ԫ�ض���Ӧ��ά�����һ�е��׵�ַ����2��ϵ������Ľ���
*/
void gaus_excuting(double*temp, double*x, int n)
{
	int i = 0;
	// �������Ĺؼ������еĵ�һ�������Ƕ�ά����ĵ�һ��Ԫ�صĵ�ַ����������ö�ά���������Σ��ã�double*)ǿת���С������һλ����������ֱ�Ӵ��ݼ���
	matrix2triangular(temp, n, n + 1);
	triangular_soving(temp, n, n + 1);
	cout << "your solution of augmented matrix is as follows" << endl;
	// ��ӡ��������Ľ�
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
*�ṩ���������ĺ��������������������ֱ�Ϊ���������Ԫ��λ�����������������
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