#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include "gaussian_elimination.h"


int main() {

	int i = 0;
	int j = 0;
	int n = 0; // n��ʾ������������
	double x[100] = { 0 };  // ��ŷ�����Ľ�
	double aug_array[100] = { 0 };  // ˳�����������
	n = test_sample_generation(aug_array, 4); // �����������ɺ���
	//n = interaction(aug_array, n);  // ���û���������ȡ�û����������;�������


	gaus_excuting(aug_array, x, n);

    return 0;
}
