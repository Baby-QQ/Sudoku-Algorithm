#include "Sudoku.h"

int Flag_UniqueAppear;     //出现唯一候选数开关（默认为关）

int Flag_Implicit;                 //调用隐式法开关
void Method_Unique()                 //唯一候选数解法
{
    int Flag_LoopUnique = 0;        //遍历开关
    Flag_UniqueAppear = 0;     //关闭唯一候选数开关
    Flag_Implicit = 1;              //隐式法开关打开
    Finish_Check = 1;
	int i;
	for(i=0;i<81;i++)//寻找唯一解
    {
        if(shudu[i].Value == 0 && shudu[i].CandidataNum != 1)
        {
            Flag_LoopUnique = 1;                   //发现空单元，需再次遍历，打开开关
            Finish_Check = 0;
        }
        if(shudu[i].CandidataNum == 1)
        {
            shudu[i].Value = Read_UniqueCandidata(shudu[i].Candidata);//读取唯一候选字并填入
            Delete_Candidata(&shudu[i] , shudu[i].Value);
            Update_Sudoku(shudu[i].RowNum,shudu[i].ColumnNum,shudu[i].PalaceNum,shudu[i].Value);	//更新所在行列的元素候选字
            Flag_Implicit = 0;         //关闭隐式法开关
            MethodUsing_UniqueNumber = 1;
        }
        if(i == 80)
        {
            if(Flag_Implicit == 0)         //若隐式法法开关为关闭
            {
                if(Flag_LoopUnique == 1)
                {
                    Method_Unique();
                    Flag_LoopUnique =0;     //遍历开关关闭
                }
                else
                {
                    //Sudoku_print();
                }
            }
            else
            {
                if(Finish_Check == 0)
                {
                    Method_ImplicitUnique();
                }
                else
                {
                    //Sudoku_print();//输出
                }
            }
        }
    }
}



int Read_UniqueCandidata(int Candidata[])
{
	int i;
	for(i=0;i<9;i++)
	{
		if(Candidata[i] != 0)
			return(Candidata[i]);
	}
	return 0;
                                                    //需要添加读取失败提示!!!!!!
}
