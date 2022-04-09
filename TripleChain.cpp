#include "Sudoku.h"

bool comp(const Sudoku &a , const Sudoku &b)    //������vectorԪ�ذ�candidataNum����
{
    return a.CandidataNum > b.CandidataNum;
}

bool IsCandidataSame(vector<Sudoku>::iterator it1 , vector<Sudoku>::iterator it2)   //�ж���������ĺ�ѡ���Ƿ���ͬ
{
    for(int i = 0 ; i < 9 ; ++i)
    {
        if(it1->Candidata[i] != it2-> Candidata[i])
            return false;
    }
    return true;
}

bool IsCandidataPart(vector<Sudoku>::iterator it1 , vector<Sudoku>::iterator it2)   //�ж���������ĺ�ѡ���Ƿ񲿷���ͬ
{
    for(int i = 0 ; i < 9 ; ++i)
    {
        if(it1-> Candidata[i] == 0 && it2->Candidata[i] != 0)
            return false;
    }
    return true;
}

bool IsPartSame_FirstTwo(vector<Sudoku>::iterator it1 , vector<Sudoku>::iterator it2 , vector<int> &vec)    //�ж�������������ѡ���Ķ����е�ǰ�����Ƿ񲿷���ͬ
{
    for(int i = 0 ; i < 9 ; ++i)
    {
        if(it2->Candidata[i] != 0)
        {
            if(find(vec.begin() , vec.end() , it2->Candidata[i]) == vec.end())
            {
                 vec.push_back(it2->Candidata[i]);
            }

        }
        if(it1->Candidata[i] != 0)
        {
            if(find(vec.begin() , vec.end() , it1->Candidata[i]) == vec.end())
                vec.push_back(it1->Candidata[i]);
        }
        if(vec.size() > 3)
            return false;
    }
    return true;
}

bool IsPartSame_Last(vector<Sudoku>::iterator it , vector<int> &vec)    //�ж�������������ѡ���Ķ��������һ���Ƿ���ǰ��������ĺ�ѡ���������Ӽ�
{
    if(vec.size() == 3)//��ǰ�����ĺ�ѡ��������Ϊ3��
    {

        for(int i = 0 ; i < 9 ; ++i)
        {
            if(it->Candidata[i] != 0)
            {
                if(find(vec.begin() , vec.end() , it->Candidata[i]) == vec.end())//����������ĳ����ѡ���ڲ������Ҳ���
                    return false;
            }
        }
        return true;
    }
    else
    {
        int NotExitsNum = 0;
        for(int i = 0 ; i < 9 ; ++i)
        {
            if(it->Candidata[i] != 0)
            {
                if(find(vec.begin() , vec.end() , it->Candidata[i]) == vec.end())
                {
                    ++NotExitsNum;
                    vec.push_back(it->Candidata[i]);
                }

            }
            if(NotExitsNum > 1)
                return false;
        }
        if(vec.size() == 3)
            return true;
        else
            return false;
    }

}

inline int Update_Sudoku_Row(int RowNum , int Value1 , int Value2 , int Value3 , int ColumnNum1 , int ColumnNum2 , int ColumnNum3)  //���и��º�ѡ��
{
    MethodUsing_TripleChain = 1;
	int i;
	for(i = RowNum*9 ; i < RowNum*9+9 ; ++i)
	{
		if(shudu[i].Value == 0 && shudu[i].ColumnNum != ColumnNum1 && shudu[i].ColumnNum != ColumnNum2 && shudu[i].ColumnNum != ColumnNum3)
		{

			Delete_Candidata(&shudu[i],Value1);
			Delete_Candidata(&shudu[i],Value2);
			Delete_Candidata(&shudu[i],Value3);
			if(shudu[i].CandidataNum == 1)
			{
                Flag_UniqueAppear = 1;         //��Ψһ��ѡ������
			}
		}
	}

	return 1;
}

inline int Update_Sudoku_Column(int ColNum , int Value1 , int Value2 , int Value3 , int RowNum1 , int RowNum2 , int RowNum3)  //���и��º�ѡ��
{
    MethodUsing_TripleChain = 1;
	int i;
	for(i = ColNum ; i <= ColNum*1+72 ; i += 9)
	{
		if(shudu[i].Value == 0 && shudu[i].RowNum != RowNum1 && shudu[i].RowNum != RowNum2 && shudu[i].RowNum != RowNum3)
		{
			Delete_Candidata(&shudu[i],Value1);
			Delete_Candidata(&shudu[i],Value2);
			Delete_Candidata(&shudu[i],Value3);
			if(shudu[i].CandidataNum == 1)
			{
                Flag_UniqueAppear = 1;         //��Ψһ��ѡ������
			}
		}
	}
	return 1;
}

inline int Update_Sudoku_Palace(int PalaceNum , int Value1 , int Value2 , int Value3 , int Seq1 , int Seq2 , int Seq3)  //�������º�ѡ��
{
    MethodUsing_TripleChain = 1;
	int base = Palace[PalaceNum];
	for(int i = 0 ; i < 3 ; ++i)
	{
	    for(int j = 0 ; j < 3 ; ++j)
        {
            if(shudu[base].Value == 0 && base != Seq1 && base != Seq2 && base != Seq3)
            {
                Delete_Candidata(&shudu[base],Value1);
                Delete_Candidata(&shudu[base],Value2);
                Delete_Candidata(&shudu[base],Value3);
                if(shudu[i].CandidataNum == 1)
                {
                    Flag_UniqueAppear = 1;         //��Ψһ��ѡ������
                }
            }
            ++base;
        }
        base += 6;
	}
	return 1;
}


void Method_TripleChainNumber()
{
    //cout << "enter TC!!" << endl;

    vector<Sudoku> TripleChain;
    //int next_loop = 0;
    //cout << "begin!" << endl;
    for(int i = 0 ; i < 9 ; ++i)    //��������������
    {
     //   cout << "loop level:" << i << endl;
        for(int j = 0 ; j < 9 ; ++j)
        {
            if(shudu[i*9+j].Value == 0 && shudu[i*9+j].CandidataNum <= 3 && shudu[i*9+j].CandidataNum > 1)
                TripleChain.push_back(shudu[i*9+j]);

        }
        if(TripleChain.size() >= 3)   //������3�����ϣ�����Ƿ����������
        {
            find_TripleChain(TripleChain , "Row");

            //��������������
        }
        TripleChain.clear();  //�������

    }
                                       //�˴�Ӧ���Ψһ��ѡ���ж�

    for(int i = 0 ; i < 9 ; ++i)    //��������������
    {
       // cout << "loop level:" << i << endl;
        for(int j = 0 ; j <= 72 ; j += 9)
        {
            if(shudu[i*9+j].Value == 0 && shudu[i*1+j].CandidataNum <= 3 && shudu[i*1+j].CandidataNum > 1)
                TripleChain.push_back(shudu[i*1+j]);

        }
        if(TripleChain.size() >= 3)   //������3�����ϣ�����Ƿ����������
        {
            find_TripleChain(TripleChain , "Column");
            //��������������
        }
        TripleChain.clear();  //�������
    }
                               //�˴�Ӧ���Ψһ��ѡ���ж�

    for(int i = 0 ; i < 9 ; ++i)    //��������������
    {
        int base = Palace[i];
      //  cout << "loop level:" << i << endl;
        for(int x = 0 ; x < 3 ; ++x)
        {
            for(int j = 0 ; j < 3 ; ++j)
            {
                if(shudu[base].Value == 0 && shudu[base].CandidataNum <= 3 && shudu[base].CandidataNum > 1)
                    TripleChain.push_back(shudu[base]);
                ++base;
            }
            base += 6;
        }
        if(TripleChain.size() >= 3)   //������3�����ϣ�����Ƿ����������
        {
            find_TripleChain(TripleChain , "Palace");
            //��������������
        }
        TripleChain.clear();  //�������
    }
                    //�˴�Ӧ���Ψһ��ѡ���ж�
    if(Flag_UniqueAppear == 1)  //������Ψһ��ѡ����־
    {
        //cout << "TC Again!!!" << endl;
       // cout << "Array Print:" << endl;
 //   Array_print();
        Method_Unique();
    }

   // cout << "finish!" << endl;

}

int find_TripleChain(vector<Sudoku> &TripleChain , string UpdateStyle)
{
    //cout << "find:" << TripleChain.size() << endl;
    sort(TripleChain.begin() , TripleChain.end() , comp);   //������vectorԪ�ذ�candidataNum��������
    vector<int> Candidata;
    for(auto it1 = TripleChain.begin() ; it1 != TripleChain.end() ; ++it1)
    {
        //cout << "beginning1" << endl;
        for(auto it2 = it1 + 1 ; it2 != TripleChain.end() ; ++it2)
        {
            //cout << "beginning2" << endl;
            if(it1-> CandidataNum == 3)
            {
                if(it2-> CandidataNum == 3)//�Ƚ�������������ѡ���ĳ�Ա
                {
                    if(IsCandidataSame(it1 , it2))    //��������ͬ,�򿴵�����
                    {
                        for(auto it3 = it2 + 1 ; it3 != TripleChain.end() ; ++it3)
                        {
                            //cout << "beginning3" << endl;
                            if(it3-> CandidataNum == 3) //����������������ѡ��
                            {
                                if(IsCandidataSame(it2 , it3))  //���ڶ����������Ҳ��ͬ
                                {
                                    int Value[3];
                                    int n = 0;
                                    for(int m = 0 ; m < 9 ; ++m)    //��ȡ����������value
                                    {
                                        if(it1->Candidata[m] != 0)
                                            Value[n++] = it1->Candidata[m];
                                    }
                                    if(UpdateStyle == "Row")
                                    {
                                        Update_Sudoku_Row(it1->RowNum , Value[0] , Value[1] , Value[2] , it1->ColumnNum , it2->ColumnNum , it3->ColumnNum);
                                        //cout << "TC::Success1Row!!!!!!!!" << endl;
                                    }
                                    else if(UpdateStyle == "Column")
                                    {
                                        Update_Sudoku_Column(it1->ColumnNum , Value[0] , Value[1] , Value[2] , it1->RowNum , it2->RowNum , it3->RowNum);
                                        //cout << "TC::Success1!Col!!!!!!!!" << endl;
                                    }
                                    else if(UpdateStyle == "Palace")
                                    {
                                        int seq1 = it1->RowNum*9+it1->ColumnNum;
                                        int seq2 = it2->RowNum*9+it2->ColumnNum;
                                        int seq3 = it3->RowNum*9+it3->ColumnNum;
                                        Update_Sudoku_Palace(it1->PalaceNum , Value[0] , Value[1] , Value[2] , seq1 , seq2 , seq3);
                                        //cout << "TC::Success1!Pal!!!!!!!!" << endl;
                                    }
                                    return 1;
                                    //���¸��к�ѡ��������Ƿ���Ψһ��ѡ��
                                }
                            }
                            else
                            {
                                if(IsCandidataPart(it2 , it3))    //���������ǵڶ������Ӽ�
                                {
                                    int Value[3];
                                    int n = 0;
                                    for(int m = 0 ; m < 9 ; ++m)    //��ȡ����������value
                                    {
                                        if(it1->Candidata[m] != 0)
                                            Value[n++] = it1->Candidata[m];
                                    }
                                    if(UpdateStyle == "Row")
                                    {
                                        Update_Sudoku_Row(it1->RowNum , Value[0] , Value[1] , Value[2],it1->ColumnNum,it2->ColumnNum,it3->ColumnNum);
                                        //cout << "TC::Success2Row!!!!!!!!!" << endl;
                                    }
                                    else if(UpdateStyle == "Column")
                                    {
                                        Update_Sudoku_Column(it1->ColumnNum , Value[0] , Value[1] , Value[2] , it1->RowNum , it2->RowNum , it3->RowNum);
                                        //cout << "TC::Success2!Col!!!!!!!!" << endl;
                                    }
                                    else if(UpdateStyle == "Palace")
                                    {
                                        int seq1 = it1->RowNum*9+it1->ColumnNum;
                                        int seq2 = it2->RowNum*9+it2->ColumnNum;
                                        int seq3 = it3->RowNum*9+it3->ColumnNum;
                                        Update_Sudoku_Palace(it1->PalaceNum , Value[0] , Value[1] , Value[2] , seq1 , seq2 , seq3);
                                        //cout << "TC::Success2!Pal!!!!!!!!" << endl;
                                    }//���¸��к�ѡ��������Ƿ���Ψһ��ѡ��
                                    return 1;
                                }
                            }
                        }
                    }
                }
                else        //�Ƚ�������������ѡ���ĳ�Ա
                {
                    if(IsCandidataPart(it1 , it2))  //���ڶ����ǵ�һ���Ӽ�
                    {
                        for(auto it3 = it2 + 1 ; it3 != TripleChain.end() ; ++it3)
                        {
                            if(IsCandidataPart(it1 , it3))  //���������ǵ�һ���Ӽ�
                            {
                                int Value[3];
                                int n = 0;
                                for(int m = 0 ; m < 9 ; ++m)    //��ȡ����������value
                                {
                                    if(it1->Candidata[m] != 0)
                                        Value[n++] = it1->Candidata[m];
                                }
                                if(UpdateStyle == "Row")
                                {
                                    Update_Sudoku_Row(it1->RowNum , Value[0] , Value[1] , Value[2],it1->ColumnNum,it2->ColumnNum,it3->ColumnNum);
                                    //cout << "TC::Success3Row!!!!!!!!!" << endl;
                                }
                                else if(UpdateStyle == "Column")
                                {
                                    Update_Sudoku_Column(it1->ColumnNum , Value[0] , Value[1] , Value[2] , it1->RowNum , it2->RowNum , it3->RowNum);
                                    //cout << "TC::Success3!Col!!!!!!!!" << endl;
                                }
                                else if(UpdateStyle == "Palace")
                                {
                                    int seq1 = it1->RowNum*9+it1->ColumnNum;
                                    int seq2 = it2->RowNum*9+it2->ColumnNum;
                                    int seq3 = it3->RowNum*9+it3->ColumnNum;
                                    Update_Sudoku_Palace(it1->PalaceNum , Value[0] , Value[1] , Value[2] , seq1 , seq2 , seq3);
                                    //cout << "TC::Success3!Pal!!!!!!!!" << endl;
                                }//���¸��к�ѡ��������Ƿ���Ψһ��ѡ��
                                return 1;
                            }
                        }
                    }
                }
            }
            else //�Ƚ�������������ѡ����
            {
                vector<int> Candidata_Cache;
                if(IsPartSame_FirstTwo(it1 , it2 , Candidata_Cache))
                {
                    vector<int> Candidata_Cache_Backup = Candidata_Cache;
                    for(auto it3 = it2 + 1 ; it3 != TripleChain.end() ; ++it3)
                    {
                        //cout << "beginning3" << endl;
                        if(IsPartSame_Last(it3 , Candidata_Cache))  //�����������
                        {

                            if(UpdateStyle == "Row")
                            {//cout <<  Candidata_Cache[0] <<endl<<Candidata_Cache[1] <<endl<< Candidata_Cache[2]<<endl<<Candidata_Cache.size()<<endl;
                                Update_Sudoku_Row(it1->RowNum , Candidata_Cache[0] , Candidata_Cache[1] , Candidata_Cache[2] , it1->ColumnNum , it2->ColumnNum , it3->ColumnNum);
                                //cout << "TC::Success4Row!!!!!!!!!" << endl;
                            }
                            else if(UpdateStyle == "Column")
                            {
                                Update_Sudoku_Column(it1->ColumnNum , Candidata_Cache[0] , Candidata_Cache[1] , Candidata_Cache[2] , it1->RowNum , it2->RowNum , it3->RowNum);
                                //cout << "TC::Success4!Col!!!!!!!!" << endl;
                            }
                            else if(UpdateStyle == "Palace")
                            {
                                int seq1 = it1->RowNum*9+it1->ColumnNum;
                                int seq2 = it2->RowNum*9+it2->ColumnNum;
                                int seq3 = it3->RowNum*9+it3->ColumnNum;
                                Update_Sudoku_Palace(it1->PalaceNum , Candidata_Cache[0] , Candidata_Cache[1] , Candidata_Cache[2] , seq1 , seq2 , seq3);
                                //cout << "TC::Success4!Pal!!!!!!!!" << endl;
                            }
                            return 1;
                        }
                        Candidata_Cache = Candidata_Cache_Backup;
                    }

                }
                else
                {
                    Candidata_Cache.clear();
                }
            }
        }
    }
    return 0;
}

