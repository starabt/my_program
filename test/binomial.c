#include <stdio.h>
#include <stdlib.h>
int binomial_ary[10][10]={0};
int main()
{
	int rowNum = 10;//显示总行数
	char flag = 'N';
	printf("请问你想从键盘输入显示多少行？默认10行(Y/N):");
	scanf("%c",&flag);
	if(flag == 'Y' || flag == 'y')
	{
		printf("请输入要显示多少行:");
		scanf("%d",&rowNum);
	}
	
	int rowNo = 0;//行号
	int columnNo = rowNo ; //列号
	for(rowNo = 0; rowNo < rowNum ; rowNo ++)
	{
		for(columnNo = 0; columnNo < rowNo + 1 ; columnNo ++)//每一行从0开始，一直计算到列数等于行数
		{
			if(columnNo == 0 || columnNo == rowNo)//列数为0或者列数等于行数（最后一列），为1
			{
				binomial_ary[rowNo][columnNo] =  1;
			}
			else
			{
				/*每一行除了头尾两个数，每个列号的数值都等于前一行的前一列号的数值加当前列号的数值*/
				binomial_ary[rowNo][columnNo] = binomial_ary[rowNo-1][columnNo-1] + binomial_ary[rowNo-1][columnNo];
			}
			printf("%d ",binomial_ary[rowNo][columnNo] );
		}
		printf("\n");//换行的时候打印一个换行符
	}
	return 0;
}