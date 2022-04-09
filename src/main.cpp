#include "Sudoku.h"

int test();
int MyMethod();
int Method();
int BackTracking();
int Method_BT();
int Analyse();

int Palace[9] {0,3,6,27,30,33,54,57,60};
vector<Sudoku> shudu(81);
int Finish_Check = 0;      //检查标志，若数独完成，则check = 1
int MethodUsing_UniqueNumber = 0,MethodUsing_ImplicitUnique = 0,MethodUsing_Backtracking = 0 , MethodUsing_TripleChain = 0 ,
        MethodUsing_TripleChainImplicit = 0 , MethodUsing_RecTangleVertex = 0;     //判断使用哪些方法

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
    int answer = 1;     //数独解情况
    cout << "解数独程序开始！" << endl << "原数独为：" << endl;
    Array_print();
    cout << endl << "数独解为：" << endl;
	if(Attribute_initialize() == 0)  //初始化数独vector属性
    {
        cout << "数独初始化失败！" << endl;
        return 0;
    }
    if(Candidata_initialize() == 0)  //初始化数独vector候选字
    {
         cout << "候选字初始化失败！" << endl;
         return 0;
    }

    //StartTime =  clock();
    QueryPerformanceFrequency(&Freq);
    QueryPerformanceCounter(&Start);


    Method_Unique();            //调用唯一候选数解法
    //Method_Backtracking(0);

    /*cout << "Array Print(Before enter BT):" << endl;
    Array_print();*/
    //Method_Backtracking(0);// 调用回溯！！！！！！！！！！！！！！！！！
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
    Sudoku_renew();             //将vector的value赋回数组
    answer = Sudoku_Check();
    if(answer == 1)
    {
        cout << "解此数独使用方法：" << endl;
        if(MethodUsing_UniqueNumber == 1)
            cout << "唯一候选法 ";
        if(MethodUsing_ImplicitUnique == 1)
            cout << "隐式候选法 ";
        if(MethodUsing_Backtracking == 1)
            cout << "回溯法 ";
        if(MethodUsing_TripleChain == 1)
            cout << "三链数删减法 ";
        if(MethodUsing_TripleChainImplicit == 1)
            cout << "隐式三链数删减法 ";
        if(MethodUsing_RecTangleVertex == 1)
            cout << "矩形顶点删减法 ";
        cout << endl;
    }
    else
    {
        if(MethodUsing_UniqueNumber == 1)
            cout << "唯一候选法 ";
        if(MethodUsing_ImplicitUnique == 1)
            cout << "隐式候选法 ";
        if(MethodUsing_Backtracking == 1)
            cout << "回溯法 ";
        if(MethodUsing_TripleChain == 1)
            cout << "三链数删减法 ";
        if(MethodUsing_TripleChainImplicit == 1)
            cout << "隐式三链数删减法 ";
        if(MethodUsing_RecTangleVertex == 1)
            cout << "矩形顶点删减法 ";
        cout << endl;
        cout << "此数独无解！" << endl;
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
    fp.open("./题库/十万道数独题.txt" , ios::in);
    //fp.open("./题库/expert.txt" , ios::in);
    if(!fp.is_open())
    {
        cout<<"打开文件失败！！\n";
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

        Finish_Check = 0;      //检查标志，若数独完成，则check = 1
        MethodUsing_UniqueNumber = 0,MethodUsing_ImplicitUnique = 0,MethodUsing_Backtracking = 0 , MethodUsing_TripleChain = 0 ,
        MethodUsing_TripleChainImplicit = 0 , MethodUsing_RecTangleVertex = 0;
        Method();


        //cout << "The run time is(NBT):" << (End.QuadPart-Start.QuadPart)*1.0/Freq.QuadPart << "s" << endl;

        fstream out;
        out.open("./结果/Test.txt" , ios::app);
        if(!out.is_open())
        {
            cout << "读取文件失败" << endl;
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
    int answer = 1;     //数独解情况
	if(Attribute_initialize() == 0)  //初始化数独vector属性
    {
        cout << "数独初始化失败！" << endl;
        return 0;
    }
    if(Candidata_initialize() == 0)  //初始化数独vector候选字
    {
         cout << "候选字初始化失败！" << endl;
         return 0;
    }

    QueryPerformanceFrequency(&Freq);
    QueryPerformanceCounter(&Start);


    Method_Unique();            //调用唯一候选数解法

    QueryPerformanceCounter(&End);

    if(CandidataGuess() != 0)
    {
        Sudoku_renew();
        answer = 1;
        /*cout << "解此数独使用方法：" << endl;
        if(MethodUsing_UniqueNumber == 1)
            cout << "唯一候选法 ";
        if(MethodUsing_ImplicitUnique == 1)
            cout << "隐式候选法 ";
        if(MethodUsing_Backtracking == 1)
            cout << "回溯法 ";
        if(MethodUsing_TripleChain == 1)
            cout << "三链数删减法 ";
        if(MethodUsing_TripleChainImplicit == 1)
            cout << "隐式三链数删减法 ";
        if(MethodUsing_RecTangleVertex == 1)
            cout << "矩形顶点删减法 ";
        cout << endl;*/
        return 0;
        //Array_print();
    }

    //QueryPerformanceCounter(&End);
    //cout << "The run time is(NBT):" << (End.QuadPart-Start.QuadPart)*1.0/Freq.QuadPart << "s" << endl;
    //cout << "BT?:" << countt << endl;
    cout << SudokuNum++ << endl;
    Sudoku_renew();             //将vector的value赋回数组
    answer = Array_Check();
    //Array_print();
    if(answer == 1)
    {
        /*cout << "解此数独使用方法：" << endl;
        if(MethodUsing_UniqueNumber == 1)
            cout << "唯一候选法 ";
        if(MethodUsing_ImplicitUnique == 1)
            cout << "隐式候选法 ";
        if(MethodUsing_Backtracking == 1)
            cout << "回溯法 ";
        if(MethodUsing_TripleChain == 1)
            cout << "三链数删减法 ";
        if(MethodUsing_TripleChainImplicit == 1)
            cout << "隐式三链数删减法 ";
        if(MethodUsing_RecTangleVertex == 1)
            cout << "矩形顶点删减法 ";
        cout << endl;*/
    }
    else
    {
        /*if(MethodUsing_UniqueNumber == 1)
            cout << "唯一候选法 ";
        if(MethodUsing_ImplicitUnique == 1)
            cout << "隐式候选法 ";
        if(MethodUsing_Backtracking == 1)
            cout << "回溯法 ";
        if(MethodUsing_TripleChain == 1)
            cout << "三链数删减法 ";
        if(MethodUsing_TripleChainImplicit == 1)
            cout << "隐式三链数删减法 ";
        if(MethodUsing_RecTangleVertex == 1)
            cout << "矩形顶点删减法 ";
        cout << endl;
        cout << "此数独无解！" << endl;*/
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
    fp.open("./题库/expert.txt" , ios::in);
    if(!fp.is_open())
    {
        cout<<"打开文件失败！！\n";
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

        Finish_Check = 0;      //检查标志，若数独完成，则check = 1

        Method_BT();


        //cout << "The run time is(NBT):" << (End.QuadPart-Start.QuadPart)*1.0/Freq.QuadPart << "s" << endl;

        fstream out;
        out.open("./结果/expert_BT.txt" , ios::app);
        if(!out.is_open())
        {
            cout << "读取文件失败" << endl;
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
    int answer = 1;     //数独解情况
    if(Attribute_initialize() == 0)  //初始化数独vector属性
    {
        cout << "数独初始化失败！" << endl;
        return 0;
    }
    if(Candidata_initialize() == 0)  //初始化数独vector候选字
    {
         cout << "候选字初始化失败！" << endl;
         return 0;
    }

    QueryPerformanceFrequency(&Freq);
    QueryPerformanceCounter(&Start);


    //Method_Unique();            //调用唯一候选数解法
    Method_Backtracking(0);      //调用回溯法

    //QueryPerformanceCounter(&End);



    //QueryPerformanceCounter(&End);
    //cout << "The run time is(NBT):" << (End.QuadPart-Start.QuadPart)*1.0/Freq.QuadPart << "s" << endl;
    //cout << "BT?:" << countt << endl;
    cout << se++ << endl;
    Sudoku_renew();             //将vector的value赋回数组
    answer = Array_Check();
    //Array_print();
    if(answer == 1)
    {
        /*cout << "解此数独使用方法：" << endl;
        if(MethodUsing_UniqueNumber == 1)
            cout << "唯一候选法 ";
        if(MethodUsing_ImplicitUnique == 1)
            cout << "隐式候选法 ";
        if(MethodUsing_Backtracking == 1)
            cout << "回溯法 ";
        if(MethodUsing_TripleChain == 1)
            cout << "三链数删减法 ";
        if(MethodUsing_TripleChainImplicit == 1)
            cout << "隐式三链数删减法 ";
        if(MethodUsing_RecTangleVertex == 1)
            cout << "矩形顶点删减法 ";
        cout << endl;*/
    }
    else
    {
        /*if(MethodUsing_UniqueNumber == 1)
            cout << "唯一候选法 ";
        if(MethodUsing_ImplicitUnique == 1)
            cout << "隐式候选法 ";
        if(MethodUsing_Backtracking == 1)
            cout << "回溯法 ";
        if(MethodUsing_TripleChain == 1)
            cout << "三链数删减法 ";
        if(MethodUsing_TripleChainImplicit == 1)
            cout << "隐式三链数删减法 ";
        if(MethodUsing_RecTangleVertex == 1)
            cout << "矩形顶点删减法 ";
        cout << endl;
        cout << "此数独无解！" << endl;*/
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
    fp.open("./结果/simple.txt" , ios::in);
    if(!fp.is_open())
    {
        cout<<"打开文件失败！！\n";
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
    out.open("./分析/simple.txt" , ios::app);
    if(!out.is_open())
    {
        cout << "读取文件失败" << endl;
    }
    out << " Avg:" << avg/200;

    return 1;
}
