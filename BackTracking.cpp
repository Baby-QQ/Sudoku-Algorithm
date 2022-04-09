#include "Sudoku.h"

/*void Method_Backtracking(int n)
{
    int i;
    if(n==81)
    {
        cout << "BT:" << countt << endl;
        Sudoku_renew();
        Array_print();
        printf("\n�������ʹ�÷�����\n");
        if(MethodUsing_UniqueNumber == 1)
            printf("Ψһ��ѡ�� ");
        if(MethodUsing_ImplicitUnique == 1)
            printf("��ʽ��ѡ�� ");
        if(MethodUsing_Backtracking == 1)
            printf("���ݷ� ");
        if(MethodUsing_TripleChain == 1)
            cout << "������ɾ���� ";
        if(MethodUsing_TripleChainImplicit == 1)
            cout << "��ʽ������ɾ���� ";
        if(MethodUsing_RecTangleVertex == 1)
            cout << "���ζ���ɾ���� ";

        printf("\n");
        exit(0);
    }
    else if(Array[n/9][n%9] != 0)
    {
        Method_Backtracking(n+1);//����λ�����������֣�����ת����һ��λ��
    }
    else if(Array[n/9][n%9] == 0)
    {countt++;
        for(i = 1 ; i <= 9 ; i++)
        {
            if(CanPlaceNumber(n,i))//�жϸ�λ�����ܷ��������i��������Ϊ�丳ֵ����ת����һλ��
            {
                Array[n/9][n%9] = i;
                Method_Backtracking(n+1);
            }
            Array[n/9][n%9] = 0;//�����Ҳ������������������������ڸ�λ�ã���ԭ��������ֵ������Ѱ����һ����ܵĽ⣬ÿ�ε�����֮����Ҫ����������ԭ����ֵ
        }
    }
}

int CanPlaceNumber(int n,int i)
{
    int j,k,flag=1;
    for(j = 0 ; j <= 8 ; j++)//�жϸ������Ƿ��и�����
    {
        if(Array[n/9][j] == i)
        {
            flag = 0;
            break;
        }
    }
    if(flag == 1)
    {
        for(j = 0 ; j <= 8 ; j++)//�жϸ����Ƿ��и�����
        {
            if(Array[j][n%9] == i)
            {
                flag=0;
                break;
            }
        }
    }
    if(flag == 1)//�ж������ڵ�С�Ź������Ƿ��и�����
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
                if(shudu[n].Candidata[i] != 0)      //�ڸ�λ��������������ѡ��
                {
                    vector<Sudoku> shudu_Backup = shudu;    //���������ݱ���
                    shudu[n].Value = i+1;
                    Update_Sudoku(shudu[n].RowNum,shudu[n].ColumnNum,shudu[n].PalaceNum,shudu[n].Value);	//�����������е�Ԫ�غ�ѡ��

                   // Sudoku_renew();
                    //cout << "Array Print(Before enter BT):" << endl;
                   // Array_print();

                    flag_UNusing = 1;
                    if(Method_Backtracking(0) == 81)
                        return 0;     //���û���������,���ݳɹ���ֱ�ӽ�����
                    if(Sudoku_Check() == 0)     //���������жϣ���ʧ����ָ�����
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
//        cout << endl << "�������ʹ�÷�����" << endl;;
//        if(MethodUsing_UniqueNumber == 1)
//            cout << "Ψһ��ѡ�� ";
//        if(MethodUsing_ImplicitUnique == 1)
//            cout << "��ʽ��ѡ�� ";
//        if(MethodUsing_Backtracking == 1)
//            cout << "���ݷ� ";
//        if(MethodUsing_TripleChain == 1)
//            cout << "������ɾ���� ";
//        if(MethodUsing_TripleChainImplicit == 1)
//            cout << "��ʽ������ɾ���� ";
//        if(MethodUsing_RecTangleVertex == 1)
//            cout << "���ζ���ɾ���� ";
//        cout << endl;

        return 81;
    }
    else if(shudu[n].Value != 0)
    {
        if(Method_Backtracking(n+1) == 81)//����λ�����������֣�����ת����һ��λ��
            return 81;
    }
    else if(shudu[n].Value == 0)
    {
        MethodUsing_Backtracking = 1;
        for(int i = 1 ; i <= 9 ; ++i)
        {
            if(CanPlaceNumber(n,i))//�ڸ�λ���Ϸ������ѡ��
            {
                shudu[n].Value = i;

                if(Method_Backtracking(n+1) == 81)
                    return 81;
            }
            shudu[n].Value = 0;//�����Ҳ������������������������ڸ�λ�ã���ԭ��������ֵ������Ѱ����һ����ܵĽ⣬ÿ�ε�����֮����Ҫ����������ԭ����ֵ
        }
    }
}

int CanPlaceNumber(int n,int i)
{
    int row = shudu[n].RowNum;
    int col = shudu[n].ColumnNum;
    int base = Palace[shudu[n].PalaceNum];
    int j,k,flag=1;
    for(j = col ; j <= col+72 ; j += 9)//�жϸ������Ƿ��и�����
    {
        if(shudu[j].Value == i)
        {
            flag = 0;
            break;
        }
    }
    if(flag == 1)
    {
        for(j = row*9 ; j < row*9+9 ; ++j)//�жϸ����Ƿ��и�����
        {
            if(shudu[j].Value == i)
            {
                flag=0;
                break;
            }
        }
    }
    if(flag == 1)//�ж������ڵ�С�Ź������Ƿ��и�����
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

