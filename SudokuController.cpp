#include "Sudoku.h"

int Update_Sudoku(int RowNum,int ColumeNum,int PalaceNum,int Value)
{
	int i,j;
	int x = Palace[PalaceNum];
	for(i=RowNum*9;i<RowNum*9+9;i++)
	{
		if(shudu[i].Value==0)
		{
			Delete_Candidata(&shudu[i],Value);
			if(shudu[i].CandidataNum == 1)
			{
                Flag_UniqueAppear = 1;         //打开唯一候选数开关
			}
		}

	}
	for(i=ColumeNum;i<81;i=i+9)
	{
		if(shudu[i].Value==0)
		{
			Delete_Candidata(&shudu[i],Value);
			if(shudu[i].CandidataNum == 1)
			{
                Flag_UniqueAppear = 1;         //打开唯一候选数开关
			}
		}
	}
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
		    if(shudu[x].Value == 0)
            {
                Delete_Candidata(&shudu[x],Value);
                if(shudu[i].CandidataNum == 1)
                {
                    Flag_UniqueAppear = 1;         //打开唯一候选数开关
                }
            }
            x++;
		}
		x=x+6;
	}
    return 1;
}


void Sudoku_renew()         //将vector的value赋回数组
{
    int i,j;
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            Array[i][j] = shudu[i*9+j].Value;
        }
    }
}

int Delete_Candidata(Sudoku *shudu , int Value)   //删除该shudu对象的某个候选数,成功返回1
{

    if(shudu->Candidata[Value-1] != 0)
    {
        shudu->Candidata[Value-1] = 0;
        if(shudu->CandidataNum > 0)
            --shudu->CandidataNum;

    }
    return 1;
}
void Delete_Candidata_iterator(int RowNum , int ColumnNum , int Value)
{
    vector<Sudoku>::iterator it = shudu.begin() + (RowNum*9 + ColumnNum);

        if(it->Candidata[Value-1] != 0 )
        {
            it->Candidata[Value-1] = 0;
            if(it->CandidataNum > 0)
                --it->CandidataNum;
        }


}

void Sudoku_print()
{
    int i;
    for(i=0;i<81;i++)
		{
            if(i%9 == 0)
            {
                printf("\n");
            }
            printf("%d  ",shudu[i].Value);
		}
    printf("\n");
}

void Array_print()//输出数组
{
    int i,j;
    for(i = 0 ; i < 9 ; i++)
    {

        for(j = 0 ; j < 9 ; j++)
        {
            printf("%d  ",Array[i][j]);
        }
        printf("\n");
    }
}

int Sudoku_Check()
{
    int answer = 1;
    for(int i = 0 ; i < 81 ; ++i)            //检查数独是否完成
    {
        if(shudu[i].Value == 0)
        {
            answer = 0;
            break;
        }
    }
    return answer;

}

int Array_Check()//输出数组
{
    int answer = 1;
    for(int i = 0 ; i < 9 ; i++)
    {

        for(int j = 0 ; j < 9 ; j++)
        {
             if(Array[i][j] == 0)
            {
                answer = 0;
                break;
            }
        }
    }
    return answer;
}
