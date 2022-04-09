#include "Sudoku.h"

int test();
int MyMethod();
int Method();
int BackTracking();
int Method_BT();
int Analyse();

int Palace[9] {0,3,6,27,30,33,54,57,60};
vector<Sudoku> shudu(81);
int Finish_Check = 0;      //����־����������ɣ���check = 1
int MethodUsing_UniqueNumber = 0,MethodUsing_ImplicitUnique = 0,MethodUsing_Backtracking = 0 , MethodUsing_TripleChain = 0 ,
        MethodUsing_TripleChainImplicit = 0 , MethodUsing_RecTangleVertex = 0;     //�ж�ʹ����Щ����

clock_t StartTime , EndTime;
LARGE_INTEGER Freq,Start,End;

int Array[9][9];
/*int Array[9][9]={{0,0,2,0,0,0,0,5,0},
                 {7,0,0,0,0,5,0,0,1},
                 {0,0,0,7,2,9,0,0,0},
                 {0,0,0,0,0,0,0,3,0},
                 {0,0,0,0,3,0,8,0,0},
                 {0,5,0,9,0,0,0,6,2},
                 {6,9,0,1,8,4,3,0,0},
                 {0,8,0,0,6,0,0,0,0},
                 {2,0,0,0,0,0,6,0,0}};*/
/*int Array[9][9]={{0,0,0,0,0,0,8,0,0},   //59
                 {0,0,6,0,7,0,0,0,0},
                 {0,0,0,0,2,0,0,5,6},
                 {6,0,0,0,0,0,3,0,4},
                 {0,9,0,7,0,1,0,0,0},
                 {0,3,0,9,0,0,0,0,7},
                 {3,0,7,0,0,8,0,0,2},
                 {5,0,0,0,0,4,0,8,0},
                 {8,4,0,0,0,0,0,0,0}};*/
/*int Array[9][9]={{},
                 {},
                 {},
                 {},
                 {},
                 {},
                 {},
                 {},
                 {}};*/
/*int Array[9][9]={{0,0,2,0,4,0,0,9,3},
                 {0,5,0,0,0,9,0,0,0},
                 {3,4,0,0,7,0,0,0,0},
                 {0,3,0,0,6,0,0,4,0},
                 {4,0,0,0,1,7,0,0,9},
                 {0,0,0,4,0,0,8,3,1},
                 {0,0,0,0,0,0,0,0,0},
                 {0,6,0,0,0,0,0,7,0},
                 {0,0,8,9,0,0,0,0,5}};*/




int main()
{
    //test();
    MyMethod();
    //BackTracking();

    //Analyse();



}

int test()
{
    int answer = 1;     //���������
    cout << "����������ʼ��" << endl << "ԭ����Ϊ��" << endl;
    Array_print();
    cout << endl << "������Ϊ��" << endl;
	if(Attribute_initialize() == 0)  //��ʼ������vector����
    {
        cout << "������ʼ��ʧ�ܣ�" << endl;
        return 0;
    }
    if(Candidata_initialize() == 0)  //��ʼ������vector��ѡ��
    {
         cout << "��ѡ�ֳ�ʼ��ʧ�ܣ�" << endl;
         return 0;
    }

    //StartTime =  clock();
    QueryPerformanceFrequency(&Freq);
    QueryPerformanceCounter(&Start);


    Method_Unique();            //����Ψһ��ѡ���ⷨ
    //Method_Backtracking(0);

    /*cout << "Array Print(Before enter BT):" << endl;
    Array_print();*/
    //Method_Backtracking(0);// ���û��ݣ���������������������������������
    //CandidataGuess();

    if(CandidataGuess() != 0)
    {
        Sudoku_renew();
        Array_print();

    }

    //EndTime = clock();
    //cout << "The run time is(NBT): " <<EndTime - StartTime<< "ms" << endl;

    QueryPerformanceCounter(&End);
    cout << "The run time is(NBT):" << (End.QuadPart-Start.QuadPart)*1.0/Freq.QuadPart << "s" << endl;

    cout << "BT?:" << countt << endl;
     Array_print();
    Sudoku_renew();             //��vector��value��������
    answer = Sudoku_Check();
    if(answer == 1)
    {
        cout << "�������ʹ�÷�����" << endl;
        if(MethodUsing_UniqueNumber == 1)
            cout << "Ψһ��ѡ�� ";
        if(MethodUsing_ImplicitUnique == 1)
            cout << "��ʽ��ѡ�� ";
        if(MethodUsing_Backtracking == 1)
            cout << "���ݷ� ";
        if(MethodUsing_TripleChain == 1)
            cout << "������ɾ���� ";
        if(MethodUsing_TripleChainImplicit == 1)
            cout << "��ʽ������ɾ���� ";
        if(MethodUsing_RecTangleVertex == 1)
            cout << "���ζ���ɾ���� ";
        cout << endl;
    }
    else
    {
        if(MethodUsing_UniqueNumber == 1)
            cout << "Ψһ��ѡ�� ";
        if(MethodUsing_ImplicitUnique == 1)
            cout << "��ʽ��ѡ�� ";
        if(MethodUsing_Backtracking == 1)
            cout << "���ݷ� ";
        if(MethodUsing_TripleChain == 1)
            cout << "������ɾ���� ";
        if(MethodUsing_TripleChainImplicit == 1)
            cout << "��ʽ������ɾ���� ";
        if(MethodUsing_RecTangleVertex == 1)
            cout << "���ζ���ɾ���� ";
        cout << endl;
        cout << "�������޽⣡" << endl;
    }
    //Method_RectangleVertex();
    //Method_TripleChainNumber();
    //Method_TripleChainNumber_Implicit();
    //Method_Backtracking(0);
    return 0;
}

int MyMethod()
{
    int seq = 0 , cot;
    string line;
    vector<int> vec;
    ifstream fp;
    fp.open("./���/ʮ���������.txt" , ios::in);
    //fp.open("./���/expert.txt" , ios::in);
    if(!fp.is_open())
    {
        cout<<"���ļ�ʧ�ܣ���\n";
        return 1;
    }
    while(getline(fp,line))
    {
        string temp;
        istringstream is(line);
        is >> seq;
        is >> cot;
        is >> temp;
        for(size_t i = 0 ; i < temp.size() ; ++i)
        {
            vec.push_back(temp[i]-'0');
        }

        auto it = vec.begin();
        for(int i = 0 ; i < 9 ; ++i)
        {
            for(int j = 0 ; j < 9 ; ++j)
            {
                Array[i][j] = *it++;
            }
        }

        Finish_Check = 0;      //����־����������ɣ���check = 1
        MethodUsing_UniqueNumber = 0,MethodUsing_ImplicitUnique = 0,MethodUsing_Backtracking = 0 , MethodUsing_TripleChain = 0 ,
        MethodUsing_TripleChainImplicit = 0 , MethodUsing_RecTangleVertex = 0;
        Method();


        //cout << "The run time is(NBT):" << (End.QuadPart-Start.QuadPart)*1.0/Freq.QuadPart << "s" << endl;

        fstream out;
        out.open("./���/Test.txt" , ios::app);
        if(!out.is_open())
        {
            cout << "��ȡ�ļ�ʧ��" << endl;
        }
        out << seq++ << " " << (End.QuadPart-Start.QuadPart)*1.0/Freq.QuadPart;
        /*for(auto v : shudu)
        {
            out << v.Value;
        }*/
        out << endl;

        vec.clear();
    }
    return 1;

}

int SudokuNum = 0;
int Method()
{
    int answer = 1;     //���������
	if(Attribute_initialize() == 0)  //��ʼ������vector����
    {
        cout << "������ʼ��ʧ�ܣ�" << endl;
        return 0;
    }
    if(Candidata_initialize() == 0)  //��ʼ������vector��ѡ��
    {
         cout << "��ѡ�ֳ�ʼ��ʧ�ܣ�" << endl;
         return 0;
    }

    QueryPerformanceFrequency(&Freq);
    QueryPerformanceCounter(&Start);


    Method_Unique();            //����Ψһ��ѡ���ⷨ

    QueryPerformanceCounter(&End);

    if(CandidataGuess() != 0)
    {
        Sudoku_renew();
        answer = 1;
        /*cout << "�������ʹ�÷�����" << endl;
        if(MethodUsing_UniqueNumber == 1)
            cout << "Ψһ��ѡ�� ";
        if(MethodUsing_ImplicitUnique == 1)
            cout << "��ʽ��ѡ�� ";
        if(MethodUsing_Backtracking == 1)
            cout << "���ݷ� ";
        if(MethodUsing_TripleChain == 1)
            cout << "������ɾ���� ";
        if(MethodUsing_TripleChainImplicit == 1)
            cout << "��ʽ������ɾ���� ";
        if(MethodUsing_RecTangleVertex == 1)
            cout << "���ζ���ɾ���� ";
        cout << endl;*/
        return 0;
        //Array_print();
    }

    //QueryPerformanceCounter(&End);
    //cout << "The run time is(NBT):" << (End.QuadPart-Start.QuadPart)*1.0/Freq.QuadPart << "s" << endl;
    //cout << "BT?:" << countt << endl;
    cout << SudokuNum++ << endl;
    Sudoku_renew();             //��vector��value��������
    answer = Array_Check();
    //Array_print();
    if(answer == 1)
    {
        /*cout << "�������ʹ�÷�����" << endl;
        if(MethodUsing_UniqueNumber == 1)
            cout << "Ψһ��ѡ�� ";
        if(MethodUsing_ImplicitUnique == 1)
            cout << "��ʽ��ѡ�� ";
        if(MethodUsing_Backtracking == 1)
            cout << "���ݷ� ";
        if(MethodUsing_TripleChain == 1)
            cout << "������ɾ���� ";
        if(MethodUsing_TripleChainImplicit == 1)
            cout << "��ʽ������ɾ���� ";
        if(MethodUsing_RecTangleVertex == 1)
            cout << "���ζ���ɾ���� ";
        cout << endl;*/
    }
    else
    {
        /*if(MethodUsing_UniqueNumber == 1)
            cout << "Ψһ��ѡ�� ";
        if(MethodUsing_ImplicitUnique == 1)
            cout << "��ʽ��ѡ�� ";
        if(MethodUsing_Backtracking == 1)
            cout << "���ݷ� ";
        if(MethodUsing_TripleChain == 1)
            cout << "������ɾ���� ";
        if(MethodUsing_TripleChainImplicit == 1)
            cout << "��ʽ������ɾ���� ";
        if(MethodUsing_RecTangleVertex == 1)
            cout << "���ζ���ɾ���� ";
        cout << endl;
        cout << "�������޽⣡" << endl;*/
    }
    //Method_RectangleVertex();
    //Method_TripleChainNumber();
    //Method_TripleChainNumber_Implicit();
    //Method_Backtracking(0);
    return 0;
}

int BackTracking()
{
     int seq = 1 , cot;
    string line;
    vector<int> vec;
    ifstream fp;
    fp.open("./���/expert.txt" , ios::in);
    if(!fp.is_open())
    {
        cout<<"���ļ�ʧ�ܣ���\n";
        return 1;
    }
    while(getline(fp,line))
    {
        string temp;
        istringstream is(line);
        //is >> seq;
        //is >> cot;
        is >> temp;
        for(size_t i = 0 ; i < temp.size() ; ++i)
        {
            vec.push_back(temp[i]-'0');
        }

        auto it = vec.begin();
        for(int i = 0 ; i < 9 ; ++i)
        {
            for(int j = 0 ; j < 9 ; ++j)
            {
                Array[i][j] = *it++;
            }
        }

        Finish_Check = 0;      //����־����������ɣ���check = 1

        Method_BT();


        //cout << "The run time is(NBT):" << (End.QuadPart-Start.QuadPart)*1.0/Freq.QuadPart << "s" << endl;

        fstream out;
        out.open("./���/expert_BT.txt" , ios::app);
        if(!out.is_open())
        {
            cout << "��ȡ�ļ�ʧ��" << endl;
        }
        out << seq++ << " " << (End.QuadPart-Start.QuadPart)*1.0/Freq.QuadPart;
        /*for(auto v : shudu)
        {
            out << v.Value;
        }*/
        out << endl;

        vec.clear();
    }
    return 1;
}


int se = 0;
int Method_BT()
{
    int answer = 1;     //���������
    if(Attribute_initialize() == 0)  //��ʼ������vector����
    {
        cout << "������ʼ��ʧ�ܣ�" << endl;
        return 0;
    }
    if(Candidata_initialize() == 0)  //��ʼ������vector��ѡ��
    {
         cout << "��ѡ�ֳ�ʼ��ʧ�ܣ�" << endl;
         return 0;
    }

    QueryPerformanceFrequency(&Freq);
    QueryPerformanceCounter(&Start);


    //Method_Unique();            //����Ψһ��ѡ���ⷨ
    Method_Backtracking(0);      //���û��ݷ�

    //QueryPerformanceCounter(&End);



    //QueryPerformanceCounter(&End);
    //cout << "The run time is(NBT):" << (End.QuadPart-Start.QuadPart)*1.0/Freq.QuadPart << "s" << endl;
    //cout << "BT?:" << countt << endl;
    cout << se++ << endl;
    Sudoku_renew();             //��vector��value��������
    answer = Array_Check();
    //Array_print();
    if(answer == 1)
    {
        /*cout << "�������ʹ�÷�����" << endl;
        if(MethodUsing_UniqueNumber == 1)
            cout << "Ψһ��ѡ�� ";
        if(MethodUsing_ImplicitUnique == 1)
            cout << "��ʽ��ѡ�� ";
        if(MethodUsing_Backtracking == 1)
            cout << "���ݷ� ";
        if(MethodUsing_TripleChain == 1)
            cout << "������ɾ���� ";
        if(MethodUsing_TripleChainImplicit == 1)
            cout << "��ʽ������ɾ���� ";
        if(MethodUsing_RecTangleVertex == 1)
            cout << "���ζ���ɾ���� ";
        cout << endl;*/
    }
    else
    {
        /*if(MethodUsing_UniqueNumber == 1)
            cout << "Ψһ��ѡ�� ";
        if(MethodUsing_ImplicitUnique == 1)
            cout << "��ʽ��ѡ�� ";
        if(MethodUsing_Backtracking == 1)
            cout << "���ݷ� ";
        if(MethodUsing_TripleChain == 1)
            cout << "������ɾ���� ";
        if(MethodUsing_TripleChainImplicit == 1)
            cout << "��ʽ������ɾ���� ";
        if(MethodUsing_RecTangleVertex == 1)
            cout << "���ζ���ɾ���� ";
        cout << endl;
        cout << "�������޽⣡" << endl;*/
    }
    //Method_RectangleVertex();
    //Method_TripleChainNumber();
    //Method_TripleChainNumber_Implicit();
    //Method_Backtracking(0);
    return 0;
}

int Analyse()
{
    int seq ;
    double avg = 0;
    string line;
    ifstream fp;
    //fp.open("./Result.txt" , ios::in);
    fp.open("./���/simple.txt" , ios::in);
    if(!fp.is_open())
    {
        cout<<"���ļ�ʧ�ܣ���\n";
        return 1;
    }
    while(getline(fp,line))
    {
        double temp;
        istringstream is(line);
        is >> seq;
        is >> temp;

        avg += temp;


    }
    fstream out;
    //out.open("./Analyse.txt" , ios::app);
    out.open("./����/simple.txt" , ios::app);
    if(!out.is_open())
    {
        cout << "��ȡ�ļ�ʧ��" << endl;
    }
    out << " Avg:" << avg/200;

    return 1;
}
