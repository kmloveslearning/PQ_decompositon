#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include "gaussian_elimination.h"


int main() {

	int i = 0;
	int j = 0;
	int n = 0; // n表示增广矩阵的行数
	double x[100] = { 0 };  // 存放方程组的解
	double aug_array[100] = { 0 };  // 顺序存放增广矩阵
	n = test_sample_generation(aug_array, 4); // 测试样本生成函数
	//n = interaction(aug_array, n);  // 与用户交互，获取用户的增广矩阵和矩阵行数


	gaus_excuting(aug_array, x, n);

    return 0;
}
