#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include "factor_table_elimination.h"

int main() {

	int n = 0; // n��ʾ������������
	double aug_array[100] = { 0 };  // ˳�����������
	double b[100] = { 0 };  // �������������һ�У�Ҳ���ǳ�����
	double x[100] = { 0 };  // ��ŷ�����Ľ�
	struct Factor_table FactorTable;  // ������ӱ�

	n = test_sample_generation(aug_array, 4, b); // �����������ɺ���
	//n = interaction(aug_array, n);  // ���û���������ȡ�û����������;�������
	gaus_excuting(aug_array, n, x, FactorTable);  // ִ��һ�������ĸ�˹��Ԫ����Ȼ�����ɽ����������ӱ�����λ�ñ�����������
	factor2x(FactorTable, b, n, x);  // ִ��һ�����ӱ�ⷽ����

    return 0;
}
