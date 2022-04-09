#include "Sudoku.h"

/*void Method_Backtracking(int n)
{
    int i;
    if(n==81)
    {
        cout << "BT:" << countt << endl;
        Sudoku_renew();
        Array_print();
        printf("\n解此数独使用方法：\n");
        if(MethodUsing_UniqueNumber == 1)
            printf("唯一候选法 ");
        if(MethodUsing_ImplicitUnique == 1)
            printf("隐式候选法 ");
        if(MethodUsing_Backtracking == 1)
            printf("回溯法 ");
        if(MethodUsing_TripleChain == 1)
            cout << "三链数删减法 ";
        if(MethodUsing_TripleChainImplicit == 1)
            cout << "隐式三链数删减法 ";
        if(MethodUsing_RecTangleVertex == 1)
            cout << "矩形顶点删减法 ";

        printf("\n");
        exit(0);
    }
    else if(Array[n/9][n%9] != 0)
    {
        Method_Backtracking(n+1);//若该位置上已有数字，则跳转至下一个位置
    }
    else if(Array[n/9][n%9] == 0)
    {countt++;
        for(i = 1 ; i <= 9 ; i++)
        {
            if(CanPlaceNumber(n,i))//判断该位置上能否放置数字i，若可以为其赋值，跳转至下一位置
            {
                Array[n/9][n%9] = i;
                Method_Backtracking(n+1);
            }
            Array[n/9][n%9] = 0;//若若找不到可以满足条件的数放置在该位置，还原它本来的值，回溯寻找下一组可能的解，每次调用完之后都需要让它返回与原来的值
        }
    }
}

int CanPlaceNumber(int n,int i)
{
    int j,k,flag=1;
    for(j = 0 ; j <= 8 ; j++)//判断该列上是否有该数字
    {
        if(Array[n/9][j] == i)
        {
            flag = 0;
            break;
        }
    }
    if(flag == 1)
    {
        for(j = 0 ; j <= 8 ; j++)//判断该行是否有该数字
        {
            if(Array[j][n%9] == i)
            {
                flag=0;
                break;
            }
        }
    }
    if(flag == 1)//判断其所在的小九宫格里是否有该数字
    {
        for(j = (n/9/3)*3 ; j < (n/9/3)*3+3 ; j++)
        {
            for(k = (n%9/3)*3 ; k < (n%9/3)*3+3 ; k++)
            {
                if(Array[j][k] == i)
                {
                    flag=0;
                    break;
                }
            if(flag == 0)
                break;
            }
        }
    }
    return flag;
}
*/
int flag_UNusing = 0;
int CandidataGuess()
{
    for(int n = 0 ; n < 81 ; ++n)
    {
        if(shudu[n].Value != 0)
        {
            continue;
        }
        else if(shudu[n].Value == 0)
        {
            for(int i = 0 ; i < 9 ; ++i)
            {
                if(shudu[n].Candidata[i] != 0)      //在该位置上逐个放置其候选字
                {
                    vector<Sudoku> shudu_Backup = shudu;    //将数独数据备份
                    shudu[n].Value = i+1;
                    Update_Sudoku(shudu[n].RowNum,shudu[n].ColumnNum,shudu[n].PalaceNum,shudu[n].Value);	//更新所在行列的元素候选字

                   // Sudoku_renew();
                    //cout << "Array Print(Before enter BT):" << endl;
                   // Array_print();

                    flag_UNusing = 1;
                    if(Method_Backtracking(0) == 81)
                        return 0;     //调用回溯试着填,回溯成功则直接结束了
                    if(Sudoku_Check() == 0)     //回溯完了判断，若失败则恢复数独
                    {
                        shudu = shudu_Backup;
                    }
                }
            }
            return 0;
        }
    }

    return 1;

}


int countt = 0;
int Method_Backtracking(int n)
{
    if(flag_UNusing == 1)
    {
        flag_UNusing = 0;
        Method_Unique();
    }
    ++countt;
    if(n==81)
    {
        //EndTime = clock();
        //cout << "The run time is: " <<EndTime - StartTime << "ms" << endl;

        QueryPerformanceCounter(&End);
//        cout << "The run time is: " << (End.QuadPart-Start.QuadPart)*1.0/Freq.QuadPart << "s" << endl;
//
//
//        cout << "BT:" << countt << endl;
//
        Sudoku_renew();
        //Array_print();
//        cout << endl << "解此数独使用方法：" << endl;;
//        if(MethodUsing_UniqueNumber == 1)
//            cout << "唯一候选法 ";
//        if(MethodUsing_ImplicitUnique == 1)
//            cout << "隐式候选法 ";
//        if(MethodUsing_Backtracking == 1)
//            cout << "回溯法 ";
//        if(MethodUsing_TripleChain == 1)
//            cout << "三链数删减法 ";
//        if(MethodUsing_TripleChainImplicit == 1)
//            cout << "隐式三链数删减法 ";
//        if(MethodUsing_RecTangleVertex == 1)
//            cout << "矩形顶点删减法 ";
//        cout << endl;

        return 81;
    }
    else if(shudu[n].Value != 0)
    {
        if(Method_Backtracking(n+1) == 81)//若该位置上已有数字，则跳转至下一个位置
            return 81;
    }
    else if(shudu[n].Value == 0)
    {
        MethodUsing_Backtracking = 1;
        for(int i = 1 ; i <= 9 ; ++i)
        {
            if(CanPlaceNumber(n,i))//在该位置上放置其候选字
            {
                shudu[n].Value = i;

                if(Method_Backtracking(n+1) == 81)
                    return 81;
            }
            shudu[n].Value = 0;//若若找不到可以满足条件的数放置在该位置，还原它本来的值，回溯寻找下一组可能的解，每次调用完之后都需要让它返回与原来的值
        }
    }
}

int CanPlaceNumber(int n,int i)
{
    int row = shudu[n].RowNum;
    int col = shudu[n].ColumnNum;
    int base = Palace[shudu[n].PalaceNum];
    int j,k,flag=1;
    for(j = col ; j <= col+72 ; j += 9)//判断该列上是否有该数字
    {
        if(shudu[j].Value == i)
        {
            flag = 0;
            break;
        }
    }
    if(flag == 1)
    {
        for(j = row*9 ; j < row*9+9 ; ++j)//判断该行是否有该数字
        {
            if(shudu[j].Value == i)
            {
                flag=0;
                break;
            }
        }
    }
    if(flag == 1)//判断其所在的小九宫格里是否有该数字
    {
        for(j = 0 ; j < 3 ; ++j)
        {
            for(k = 0 ; k < 3 ; ++k)
            {
                if(shudu[base].Value == i)
                {
                    flag=0;
                    break;
                }
                if(flag == 0)
                    break;
                ++base;
            }
            base += 6;
        }
    }
    return flag;
}

