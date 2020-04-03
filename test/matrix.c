#if 0
#include <stdlib.h>
#include <stdio.h>
#define MATRIC_NUM  3
float matri_ary[MATRIC_NUM][MATRIC_NUM] = {{1,2,3},{4,5,6},{7,8,9}};
int get_matri_from_stdin(float *matri[MATRIC_NUM],int matric_num)
{
	int i=0,j=0;
	for(i=0;i<matric_num;i++)
	{
		for(j=0;j<=i;i++)
		{
			printf("请输入矩阵的第 %d 行 第 %d 列:",i+1,j+1);
			scanf("%f",&matri[i][j]);
		}
	}
	return 0;
}
int analyze_matri(float matri[][MATRIC_NUM],int matric_num)
{
	float maxNum[MATRIC_NUM]={0};
	float maxNumSum = 0;
	int i=0,j=0;
	for(i=0;i<matric_num;i++)
	{
		maxNum[i] = matri[i][0];
		for(j=1;j<i;j++)
		{
			if(maxNum[i] < matri[i][j])
			{
				maxNum[i] = matri[i][j];
			}
			
		}
		printf("矩阵的第 %d 行 最大值为 %f\n",i+1,maxNum[i]);
		maxNumSum += maxNum[i];
	}

	printf("每一行最大值加和为:%lf\n",maxNumSum);
	return 0;
}
int main()
{
	// char flag = 'N';
	// printf("请问是否自己创建矩阵？(Y/N):");
	// scanf("%c",&flag);
	// if(flag == 'Y' || flag == 'y')
	// {
	// 	printf("请输入矩阵行列数：");
	// 	int matric_num_temp = 0;
	// 	scanf("%d",&matric_num_temp);
	// 	const int MATRIC_NUM_IN = matric_num_temp;
	// 	float matri_ary_in[MATRIC_NUM_IN][MATRIC_NUM_IN];
	// 	get_matri_from_stdin(matri_ary_in,MATRIC_NUM_IN);
	// 	analyze_matri(matri_ary_in,MATRIC_NUM_IN);
	// }
	// else
	// {
		analyze_matri(matri_ary,MATRIC_NUM);
	// }
	return 0;
}
#endif
#if 1
#include <stdlib.h>
#include <stdio.h>
#define MATRIC_NUM  3
float matri_ary[MATRIC_NUM][MATRIC_NUM] = {{1,2,3},{4,5,6},{7,8,9}};
int main()
{
	float maxNum[MATRIC_NUM]={0};//存储每一行的最大数
	float maxNumSum = 0;//每一行最大数的加和
	int i=0,j=0;
	for(i=0;i<MATRIC_NUM;i++)
	{
		maxNum[i] = matri_ary[i][0];//最大值先附初值，每一行的的第一个数
		for(j=1;j<=i;j++)
		{
			/*每一行获取最大值*/
			if(maxNum[i] < matri_ary[i][j])
			{
				maxNum[i] = matri_ary[i][j];
			}
			
		}
		printf("矩阵的第 %d 行 最大值为 %f \n",i+1,maxNum[i]);
		maxNumSum += maxNum[i];
	}

	printf("每一行最大值加和为:%lf\n",maxNumSum);
	return 0;
}
#endif