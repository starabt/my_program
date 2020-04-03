#include <stdlib.h>
#include <stdio.h>
float score[10] = {60,61,62,63,64,65,66,67,68,69};
//从键盘获取分数
float get_score_from_stdin(float *m_score,int num)
{
	int i = 0;
	for(i = 0;i<num;i++)
	{
		printf("请输入第 %d 个学生成绩：", i);
		scanf("%f",&m_score[i]);
	}
	return 0;
}
// 求平均数
float get_average_score(float *m_score,int num)
{
	float sum = 0;
	int i = 0;
	for(i = 0;i<num;i++)
	{
		sum += m_score[i];
	}
	float f_num  = (float)(num*1.0);
	return sum/f_num;
}
// 求最大数
float get_max_score(float *m_score,int num)
{
	float max_score = 0.0;
	max_score = m_score[0];
	int i = 0;
	for(i = 1;i<num;i++)
	{
		if(max_score<m_score[i])
		{
			max_score = m_score[i];
		}
	}
	return max_score;
}
// 求最小数
float get_min_score(float *m_score,int num)
{
	float min_score = 0.0;
	min_score = m_score[0];
	int i = 0;
	for(i = 1;i<num;i++)
	{
		if(m_score[i] < min_score)
		{
			min_score = m_score[i];
		}
	}
	return min_score;
}
int main()
{
	char flag = 'N';
	printf("请问你想从键盘获取10个成绩吗？(Y/N):");
	scanf("%c",&flag);
	int score_num  = sizeof(score)/sizeof(score[0]);
	if(flag == 'Y' || flag == 'y')
	{
		get_score_from_stdin(score,score_num);
	}
	printf("平均数:%f,最高分:%f\n，最低分:%f \n",\
		get_average_score(score,score_num),
		get_max_score(score,score_num) ,\
		get_min_score(score,score_num));
	return 0;
}
