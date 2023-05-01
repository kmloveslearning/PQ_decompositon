#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include "factor_table_elimination.h"

int main() {

	int n = 0; // n表示增广矩阵的行数
	double aug_array[100] = { 0 };  // 顺序存放增广矩阵
	double b[100] = { 0 };  // 存放增广矩阵最后一列，也就是常数列
	double x[100] = { 0 };  // 存放方程组的解
	struct Factor_table FactorTable;  // 存放因子表

	n = test_sample_generation(aug_array, 4, b); // 测试样本生成函数
	//n = interaction(aug_array, n);  // 与用户交互，获取用户的增广矩阵和矩阵行数
	gaus_excuting(aug_array, n, x, FactorTable);  // 执行一次完整的高斯消元法，然后生成解向量和因子表、交换位置表、交换次数表
	factor2x(FactorTable, b, n, x);  // 执行一次因子表解方程组

    return 0;
}
