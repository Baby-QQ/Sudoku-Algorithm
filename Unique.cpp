#include "Sudoku.h"

int Flag_UniqueAppear;     //����Ψһ��ѡ�����أ�Ĭ��Ϊ�أ�

int Flag_Implicit;                 //������ʽ������
void Method_Unique()                 //Ψһ��ѡ���ⷨ
{
    int Flag_LoopUnique = 0;        //��������
    Flag_UniqueAppear = 0;     //�ر�Ψһ��ѡ������
    Flag_Implicit = 1;              //��ʽ�����ش�
    Finish_Check = 1;
	int i;
	for(i=0;i<81;i++)//Ѱ��Ψһ��
    {
        if(shudu[i].Value == 0 && shudu[i].CandidataNum != 1)
        {
            Flag_LoopUnique = 1;                   //���ֿյ�Ԫ�����ٴα������򿪿���
            Finish_Check = 0;
        }
        if(shudu[i].CandidataNum == 1)
        {
            shudu[i].Value = Read_UniqueCandidata(shudu[i].Candidata);//��ȡΨһ��ѡ�ֲ�����
            Delete_Candidata(&shudu[i] , shudu[i].Value);
            Update_Sudoku(shudu[i].RowNum,shudu[i].ColumnNum,shudu[i].PalaceNum,shudu[i].Value);	//�����������е�Ԫ�غ�ѡ��
            Flag_Implicit = 0;         //�ر���ʽ������
            MethodUsing_UniqueNumber = 1;
        }
        if(i == 80)
        {
            if(Flag_Implicit == 0)         //����ʽ��������Ϊ�ر�
            {
                if(Flag_LoopUnique == 1)
                {
                    Method_Unique();
                    Flag_LoopUnique =0;     //�������عر�
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
                    //Sudoku_print();//���
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
                                                    //��Ҫ��Ӷ�ȡʧ����ʾ!!!!!!
}
