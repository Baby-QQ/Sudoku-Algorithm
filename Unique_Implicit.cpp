#include "Sudoku.h"

/*void SubCandidata_CacheSudoku(int CacheArray[],int Candidata[])         //删除缓存数组中的候选字
{
    int k,j;//for(k=0;k<9;k++)printf("backup为%d",CacheArray[k]);
    for(k = 0 ; k < 9 ; ++k)
    {
        if(CacheArray[k] != 0)
        {
            for(j = 0 ; j < 9 ; ++j)
            {
                if(Candidata[j] != 0)
                {
                    if(CacheArray[k] == Candidata[j])
                    {
                        CacheArray[k] = 0;
                        --CacheArrayNum;
                    }
                }
            }
        }
    }
}*/
void SubCandidata_CacheSudoku(int CacheArray[],int Candidata[])         //删除缓存数组中的候选字
{
    for(int k = 0 ; k < 9 ; ++k)
    {
        if(CacheArray[k] != 0)
        {
            if(Candidata[k] != 0)
            {
                if(CacheArray[k] == Candidata[k])
                {
                    CacheArray[k] = 0;
                    --CacheArrayNum;
                }
            }
        }
    }
}


int CacheArrayNum = 0;              //backup元素个数计数器
int Flag_LoopImplcit;             //隐式遍历开关（若有更新则打开）
void Method_ImplicitUnique()             //隐式唯一候选数解法
{
    int i,j,m,n,f,g;
    //Flag_UniqueAppear = 0;     //关闭唯一候选数开关
    Flag_LoopImplcit = 0;     //关闭隐式遍历开关
    int Flag_ImplicitRenew;     //数独单元完成开关
    for(i = 0 ; i < 81 ; ++i)
    {
        int CacheArray[9];              //候选字备用数组
        if(shudu[i].Value == 0)
        {
            Flag_ImplicitRenew = 0;      //数独单元未完成
            for(g = 0 ; g < 9 ; ++g)
            {
                CacheArray[g] = shudu[i].Candidata[g];
            }
            CacheArrayNum = shudu[i].CandidataNum;
            for(j = shudu[i].RowNum*9 ; j < shudu[i].RowNum*9+9 ; ++j)        //按行搜索隐式候选字
            {
                if(shudu[j].Value == 0 && j != i)
                {
                    SubCandidata_CacheSudoku(CacheArray,shudu[j].Candidata);
                    if(CacheArrayNum == 0)
                        break;
                }
            }
            if(CacheArrayNum == 1)
            {

                shudu[i].Value = Read_UniqueCandidata(CacheArray);//读取隐式唯一候选字并填入
                shudu[i].CandidataNum = 0;
                Update_Sudoku(shudu[i].RowNum , shudu[i].ColumnNum , shudu[i].PalaceNum , shudu[i].Value);	//更新所在行列的元素候选字
                Flag_LoopImplcit = 1;
                Flag_ImplicitRenew = 1;
                MethodUsing_ImplicitUnique = 1;
                if(Flag_UniqueAppear == 1)
                {
                    break;
                }
            }
            for(g = 0 ; g < 9 ; ++g)
            {
                CacheArray[g] = shudu[i].Candidata[g];
            }
            CacheArrayNum = shudu[i].CandidataNum;
            for(m=shudu[i].ColumnNum;m<81;m=m+9)             //按列搜索隐式候选字
            {
                if(shudu[m].Value == 0 && m != i)
                {
                    SubCandidata_CacheSudoku(CacheArray,shudu[m].Candidata);
                    if(CacheArrayNum == 0)
                        break;
                }
            }
            if(CacheArrayNum == 1)
            {
                shudu[i].Value = Read_UniqueCandidata(CacheArray);//读取隐式唯一候选字并填入
                shudu[i].CandidataNum = 0;
                Update_Sudoku(shudu[i].RowNum,shudu[i].ColumnNum,shudu[i].PalaceNum,shudu[i].Value);	//更新所在行列的元素候选字
                Flag_LoopImplcit = 1;
                Flag_ImplicitRenew = 1;
                MethodUsing_ImplicitUnique = 1;
                if(Flag_UniqueAppear == 1)
                {
                    break;

                }
            }
            for(g = 0 ; g < 9 ; ++g)
            {
                CacheArray[g] = shudu[i].Candidata[g];
            }
            CacheArrayNum = shudu[i].CandidataNum;
            n = Palace[shudu[i].PalaceNum];
            for(f = 0 ; f < 3 ; ++f)                //按宫搜索隐式候选字
            {
                for(j = 0 ; j < 3 ; ++j)
                {
                    if(shudu[n].Value == 0 && n != i)
                    {
                        SubCandidata_CacheSudoku(CacheArray,shudu[n].Candidata);
                        if(CacheArrayNum == 0)
                        {
                            break;
                        }
                    }
                    ++n;
                }
                n = n + 6;
                if(CacheArrayNum == 0)
                {
                    break;
                }
            }
            if(CacheArrayNum == 1)
            {
                shudu[i].Value = Read_UniqueCandidata(CacheArray);//读取隐式唯一候选字并填入
                shudu[i].CandidataNum = 0;
                Update_Sudoku(shudu[i].RowNum , shudu[i].ColumnNum , shudu[i].PalaceNum , shudu[i].Value);	//更新所在行列的元素候选字
                Flag_LoopImplcit = 1;
                Flag_ImplicitRenew = 1;
                MethodUsing_ImplicitUnique = 1;
                if(Flag_UniqueAppear == 1)
                {
                    break;
                }
            }
            if(Flag_ImplicitRenew == 0)
            {
                Finish_Check = 0;
            }
        }
    }
    if(Flag_LoopImplcit == 1)         //若数独有更新，则再次搜索隐式候选字
    {
        if(Finish_Check == 0)      //若数独未完成
        {
            Method_ImplicitUnique();
        }
        else
        {
            //Sudoku_print();//输出
        }
    }
    else
    {
        if(Finish_Check == 0)      //若数独未完成
        {
            if(Flag_UniqueAppear == 1)     //若出现唯一候选字，则调回唯一法
            {
                Method_Unique();
            }
            else
            {
                Sudoku_renew();
                Method_TripleChainNumber_Implicit();
                Method_TripleChainNumber();


                /*cout << "Array Print(Before enter RV):" << endl;
                Array_print();*/
                Method_RectangleVertex();
                //Sudoku_print();

                /*cout << "Array Print(Before enter BT):" << endl;
                Array_print();
                Method_Backtracking(0);// 调用回溯！！！！！！！！！！！！！！！！！*/
            }
        }
        else
        {
            //Sudoku_print();
        }
    }
}

