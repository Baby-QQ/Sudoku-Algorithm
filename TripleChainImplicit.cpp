#include "Sudoku.h"


void Method_TripleChainNumber_Implicit()
{
    vector<Sudoku> Potential_TripleChain;
    //cout << "enter TCIMPL!!" << endl;
    //int next_loop = 0;
    //cout << "begin!" << endl;
    for(int i = 0 ; i < 9 ; ++i)    //��������������
    {
        //cout << "loop level:" << i << endl;
        for(int j = 0 ; j < 9 ; ++j)
        {
            if(shudu[i*9+j].Value == 0)
                Potential_TripleChain.push_back(shudu[i*9+j]);

        }
        if(Potential_TripleChain.size() >= 3)   //������3�����ϣ�����Ƿ����������
        {
            find_ImplicitTripleChain(Potential_TripleChain , "Row");
            //��������������
        }


        Potential_TripleChain.clear();  //�������

    }                                                           //�˴�Ӧ���Ψһ��ѡ���ж�

    for(int i = 0 ; i < 9 ; ++i)    //��������������
    {
        //cout << "loop level:" << i << endl;
        for(int j = 0 ; j <= 72 ; j += 9)
        {
            if(shudu[i+j].Value == 0)
                Potential_TripleChain.push_back(shudu[i+j]);

        }
        if(Potential_TripleChain.size() >= 3)   //������3�����ϣ�����Ƿ����������
        {
            find_ImplicitTripleChain(Potential_TripleChain , "Column");
            //��������������
        }
        Potential_TripleChain.clear();  //�������
    }                                                              //�˴�Ӧ���Ψһ��ѡ���ж�

    for(int i = 0 ; i < 9 ; ++i)    //��������������
    {
        int base = Palace[i];
        //cout << "loop level:" << i << endl;
        for(int x = 0 ; x < 3 ; ++x)
        {
            for(int j = 0 ; j < 3 ; ++j)
            {
                if(shudu[base].Value == 0)
                    Potential_TripleChain.push_back(shudu[base]);
                ++base;
            }
            base += 6;
        }
        if(Potential_TripleChain.size() >= 3)   //������3�����ϣ�����Ƿ����������
        {
            find_ImplicitTripleChain(Potential_TripleChain , "Palace");
            //��������������
        }
        Potential_TripleChain.clear();  //�������
    }                                           //�˴�Ӧ���Ψһ��ѡ���ж�

    //cout << "finish!" << endl;
    if(Flag_UniqueAppear == 1)  //������Ψһ��ѡ����־
    {
        //cout << "TCIMPL Again!!!" << endl;

        Method_Unique();
    }

}

int find_ImplicitTripleChain(vector<Sudoku> &ImplicitTripleChain , string UpdateStyle)
{
   // cout << "find:" << ImplicitTripleChain.size() << endl;
    sort(ImplicitTripleChain.begin() , ImplicitTripleChain.end() , comp);

    for(auto it1 = ImplicitTripleChain.begin() ; it1 != ImplicitTripleChain.end() ; ++it1)
    {
        for(auto it2 = it1 + 1 ; it2 != ImplicitTripleChain.end() ; ++it2)
        {
            for(auto it3 = it2 + 1 ; it3 != ImplicitTripleChain.end() ; ++it3)
            {
                int ComfortNum = 0; //��¼������shudu�з���Ҫ��ĺ�ѡ��
                int Value[4];
                for(int i = 0 ; i < 9 ; ++i)
                {
                    int FindOne = 1;
                    if(it1->Candidata[i] == 0 && it2->Candidata[i] == 0 && it3->Candidata[i] == 0)
                    {
                        continue;
                    }
                    else if((it3+1) == ImplicitTripleChain.end())
                    {
                        continue;
                    }
                    else
                    {
                        for(auto it4 = ImplicitTripleChain.begin() ; it4 != ImplicitTripleChain.end() ; ++it4)
                        {
                            if(it4 != it3 && it4 != it2 && it4 != it1)
                            {
                                if(it4->Candidata[i] != 0)
                                {
                                    FindOne = 0;
                                    break;
                                }
                            }
                            else
                                continue;
                        }
                        if(FindOne == 1)
                        {
                            Value[ComfortNum++] = i + 1;
                        }

                    }
                    if(ComfortNum > 3)
                        break;
                }
                if(ComfortNum == 3)         //�ɹ��ҵ�
                {
                    MethodUsing_TripleChainImplicit = 1;
                    //cout << "TCImpli::Success!!!!!!!!" << endl;
                    Delete_Candidata_iterator(it1->RowNum , it1->ColumnNum , Value[0] , Value[1] , Value[2]);
                    Delete_Candidata_iterator(it2->RowNum , it2->ColumnNum , Value[0] , Value[1] , Value[2]);
                    Delete_Candidata_iterator(it3->RowNum , it3->ColumnNum , Value[0] , Value[1] , Value[2]);

                    return 1;
                }


            }
        }
    }
    return 0;
}

void Delete_Candidata_iterator(int RowNum , int ColumnNum ,int Value1 , int Value2 , int Value3)
{
    vector<Sudoku>::iterator it = shudu.begin() + (RowNum*9 + ColumnNum);
    for(int i = 0 ; i < 9 ; ++i)
    {
        if(it->Candidata[i] != 0 && it->Candidata[i] != Value1 && it->Candidata[i] != Value2 && it->Candidata[i] != Value3)
        {
            it->Candidata[i] = 0;
            if(it->CandidataNum > 0)
                --it->CandidataNum;
        }
    }
    if(it->CandidataNum == 1)           //��Ψһ��ѡ������
    {
        Flag_UniqueAppear = 1;
    }

}


