#include <stdio.h>
#include <stdlib.h>

void main()
{
	int i,j,k;
	int s,n;//s��nά������
	int groupNum=0;//���������޹������
	double **array,**deterArray;
	double **groupArray,**result;
	int *groupPosition;
	
	void printfDouble2Dimension(int s, int n, double **array);
	void printfInt1Dimension(int n, int *array);	
	void primaryRowChange(int s, int n, double **array);
	int getGreatLinerlyIndependentGroup(int s, int n, double **array, int *result);
	void calcOrthogonalization(int s, int n, double **array, double **result);
	
	printf("��������������S:");
	scanf("%d",&s);
	printf("����������ά��N:");
	scanf("%d",&n);
	array=(double**)malloc(s*sizeof(double*));
	deterArray=(double**)malloc(n*sizeof(double*));
	groupPosition =(int*)malloc(s*sizeof(int));

	for(i=0;i<n;i++)
	{		
		deterArray[i]=(double*)malloc(n*sizeof(double));
	}
	for(i=0;i<s;i++)
		*(groupPosition+i)=-1;
	//
	for(i=0;i<s;i++)
	{
		array[i]=(double*)malloc(n*sizeof(double));
		for(j=0;j<n;j++)
		{
			scanf("%lf",*(array+i)+j);
			*(*(deterArray+j)+i) = *(*(array+i)+j);
		}
	}

	printf("1:\n");
	printfDouble2Dimension(s,n,array);
	printf("2:\n");
	printfDouble2Dimension(n,s,deterArray);

	primaryRowChange(n,s,deterArray);
	
	printf("2:\n");
	printfDouble2Dimension(n,s,deterArray);

	groupNum = getGreatLinerlyIndependentGroup(n,s,deterArray,groupPosition);

	printf("���������޹���:\n");
	printfInt1Dimension(s,groupPosition);

	groupArray= (double**)malloc(groupNum*sizeof(double*));
	result = (double**)malloc(groupNum*sizeof(double*));
	for(i=0;i<groupNum;i++)
	{
		if(*(groupPosition+i)!=-1)
		{
			groupArray[i] = (double*)malloc(n*sizeof(double));
			result[i] = (double*)malloc(n*sizeof(double));
			groupArray[i] = *(array+ *(groupPosition+i));
			result[i] = *(array+ *(groupPosition+i));
		}
	}

	printfDouble2Dimension(groupNum,n,groupArray);

	calcOrthogonalization(groupNum,n,groupArray,result);
	
	printf("����������:\n");
	printfDouble2Dimension(groupNum,n,result);

	system("pause");
}
//�����б任
void primaryRowChange(int s, int n, double **array)
{
	int i,j,k,ii,kk,flag;
	double temp;
	for(i=0,j=0;i<s-1;i++,j++)//s�У�����Χֻ��Ҫ�任s-1
	{		
		ii=i;
		//����е���ԪΪ0�����²���һ����Ϊ0�ģ�Ȼ����
		if(*(*(array+i)+j) == 0)
		{
			flag=0;
			for(k=i+1;k<s;k++)
			{
				if(*(*(array+k)+j)!=0)//��k�����i�н���
				{
					for(kk=j;kk<n;kk++)
					{	
						temp=*(*(array+k)+kk);
						*(*(array+k)+kk) = *(*(array+i)+kk);
						*(*(array+i)+kk) = temp;
					}			
					flag =1;
					break;
				}
			}		
			//�ж��ǽ����ɹ������û�гɹ�����i--
			if(!flag)
			{				
				i--;
				continue;
			}
			i--;
			j--;
			continue;
		}
		for(;ii<s-1;ii++)
		{
			if(*(*(array+ii+1)+j)==0)
				continue;
			temp =-*(*(array+ii+1)+j) / *(*(array+i)+j);
			for(k=j;k<n;k++)
				*(*(array+ii+1)+k) += *(*(array+i)+k) * temp;
				
		}
	}
}

//��ȡ���������޹���λ�ü�����
int getGreatLinerlyIndependentGroup(int s, int n, double **array, int *result)
{
	int i,j,num=0;
	for(i=0;i<s;i++)
	{
		for(j=0;j<n;j++)
		{
			if(*(*(array+i)+j)!=0)
			{
				*(result + num++)=j;
				break;
			}
		}
	}
	return num;
}

//��������������
void calcOrthogonalization(int s, int n, double **array, double **result)
{
	int i,j,k;
	double **tempArray ,temp;
	double getInnerProduct(int n,double *array1, double *array2);
	for(i=0;i<s;i++)
	{
		tempArray = (double**)malloc(i*sizeof(double*));
		for(j=0;j<i;j++)
		{
			tempArray[j] = (double*)malloc(n*sizeof(double));
			temp = getInnerProduct(n,*(array+i),*(result+j)) / getInnerProduct(n,*(result+j),*(result+j));
			for(k=0;k<n;k++)
			{
				*(*(tempArray+j)+k) = temp * *(*(result+j)+k);
			}
		}
		for(j=0;j<i;j++)
		{
			for(k=0;k<n;k++)
				*(*(array+i)+k) -= *(*(tempArray+j)+k);
		}
	}
}

//���������������ڻ�
double getInnerProduct(int n, double *array1, double *array2)
{
	int i;
	double result=0;
	for(i=0;i<n;i++)
		result += *(array1+i) * *(array2+i);
	return result;
}
//print array
void printfDouble2Dimension(int s, int n, double **array)
{
	int i,j;
	for(i=0;i<s;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%6.2lf",*(*(array+i)+j));
		}
		printf("\n");
	}
}


void printfInt1Dimension(int n, int *array)
{
	int i;
	for(i=0;i<n;i++)
	{
		printf("%4d",*(array+i));
	}
	printf("\n");
}