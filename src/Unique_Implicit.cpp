#include "Sudoku.h"

/*void SubCandidata_CacheSudoku(int CacheArray[],int Candidata[])         //ɾ�����������еĺ�ѡ��
{
    int k,j;//for(k=0;k<9;k++)printf("backupΪ%d",CacheArray[k]);
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
void SubCandidata_CacheSudoku(int CacheArray[],int Candidata[])         //ɾ�����������еĺ�ѡ��
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


int CacheArrayNum = 0;              //backupԪ�ظ���������
int Flag_LoopImplcit;             //��ʽ�������أ����и�����򿪣�
void Method_ImplicitUnique()             //��ʽΨһ��ѡ���ⷨ
{
    int i,j,m,n,f,g;
    //Flag_UniqueAppear = 0;     //�ر�Ψһ��ѡ������
    Flag_LoopImplcit = 0;     //�ر���ʽ��������
    int Flag_ImplicitRenew;     //������Ԫ��ɿ���
    for(i = 0 ; i < 81 ; ++i)
    {
        int CacheArray[9];              //��ѡ�ֱ�������
        if(shudu[i].Value == 0)
        {
            Flag_ImplicitRenew = 0;      //������Ԫδ���
            for(g = 0 ; g < 9 ; ++g)
            {
                CacheArray[g] = shudu[i].Candidata[g];
            }
            CacheArrayNum = shudu[i].CandidataNum;
            for(j = shudu[i].RowNum*9 ; j < shudu[i].RowNum*9+9 ; ++j)        //����������ʽ��ѡ��
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

                shudu[i].Value = Read_UniqueCandidata(CacheArray);//��ȡ��ʽΨһ��ѡ�ֲ�����
                shudu[i].CandidataNum = 0;
                Update_Sudoku(shudu[i].RowNum , shudu[i].ColumnNum , shudu[i].PalaceNum , shudu[i].Value);	//�����������е�Ԫ�غ�ѡ��
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
            for(m=shudu[i].ColumnNum;m<81;m=m+9)             //����������ʽ��ѡ��
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
                shudu[i].Value = Read_UniqueCandidata(CacheArray);//��ȡ��ʽΨһ��ѡ�ֲ�����
                shudu[i].CandidataNum = 0;
                Update_Sudoku(shudu[i].RowNum,shudu[i].ColumnNum,shudu[i].PalaceNum,shudu[i].Value);	//�����������е�Ԫ�غ�ѡ��
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
            for(f = 0 ; f < 3 ; ++f)                //����������ʽ��ѡ��
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
                shudu[i].Value = Read_UniqueCandidata(CacheArray);//��ȡ��ʽΨһ��ѡ�ֲ�����
                shudu[i].CandidataNum = 0;
                Update_Sudoku(shudu[i].RowNum , shudu[i].ColumnNum , shudu[i].PalaceNum , shudu[i].Value);	//�����������е�Ԫ�غ�ѡ��
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
    if(Flag_LoopImplcit == 1)         //�������и��£����ٴ�������ʽ��ѡ��
    {
        if(Finish_Check == 0)      //������δ���
        {
            Method_ImplicitUnique();
        }
        else
        {
            //Sudoku_print();//���
        }
    }
    else
    {
        if(Finish_Check == 0)      //������δ���
        {
            if(Flag_UniqueAppear == 1)     //������Ψһ��ѡ�֣������Ψһ��
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
                Method_Backtracking(0);// ���û��ݣ���������������������������������*/
            }
        }
        else
        {
            //Sudoku_print();
        }
    }
}

