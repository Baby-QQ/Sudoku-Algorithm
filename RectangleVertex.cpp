#include "Sudoku.h"


class AppearNum
{
public:
    //AppearNum() : ColumnNum(10) {};
    vector<int> AppearPos[9];
};

class Triplet
{
public:
    Triplet(int row,int rcol1,int rcol2,int col,int crow1,int crow2) : Row(row),Row_Column1(rcol1),Row_Column2(rcol2),Col(col),Col_Row1(crow1),Col_Row2(crow2) {};
    int Row;
    int Row_Column1;
    int Row_Column2;
    int Col;
    int Col_Row1;
    int Col_Row2;
} ;





bool ExistRV(vector<Triplet> &PotentialRV , vector<Triplet>::iterator &it1 , vector<Triplet>::iterator &it2 , string SeachStyle)
{
    if(SeachStyle == "Row")
    {
        for(it1 = PotentialRV.begin() ; it1 != PotentialRV.end() ; ++it1)
        {
            for(it2 = it1+1 ; it2 != PotentialRV.end() ; ++it2)
            {
                if(it1->Row != it2->Row && it1->Row_Column1 == it2->Row_Column1 && it1->Row_Column2 == it2->Row_Column2)
                {
                    return true;
                }
            }
        }
        return false;
    }
    else if(SeachStyle == "Col")
    {
        for(it1 = PotentialRV.begin() ; it1 != PotentialRV.end() ; ++it1)
        {
            for(it2 = it1+1 ; it2 != PotentialRV.end() ; ++it2)
            {
                if(it1->Col != it2->Col && it1->Col_Row1 == it2->Col_Row1 && it1->Col_Row2 == it2->Col_Row2)
                {
                    return true;
                }
            }
        }
        return false;
    }
    return false;

}

int Delete_Candidata_RV(int NotChange1 , int NotChange2 , int Para1 , int Para2 , int Value , string UpdateStyle)
{
    int Sub;
    if(UpdateStyle == "Row")
    {
        Sub = Para2 - Para1;

        for(int i = Para1 ; i <= Para1+72 ; i += 9)
        {
            if(shudu[i].RowNum != NotChange1 && shudu[i].RowNum != NotChange2)
            {
                if(shudu[i].Value == 0)
                {
                    Delete_Candidata(&shudu[i],Value);
                    //Delete_Candidata_iterator(shudu[i].RowNum , shudu[i].ColumnNum , Value);
                    if(shudu[i].CandidataNum == 1)
                    {
                        Flag_UniqueAppear = 1;         //打开唯一候选数开关
                    }
                }
            }
            if(shudu[i + Sub].RowNum != NotChange1 && shudu[i + Sub].RowNum != NotChange2)
            {
                if(shudu[i + Sub].Value == 0)
                {
                    Delete_Candidata(&shudu[i + Sub],Value);
                    //Delete_Candidata_iterator(shudu[i].RowNum , shudu[i].ColumnNum , Value);
                    if(shudu[i + Sub].CandidataNum == 1)
                    {
                        Flag_UniqueAppear = 1;         //打开唯一候选数开关
                    }
                }
            }

        }
    }
    else if(UpdateStyle == "Col")
    {
        Sub = (Para2 - Para1) * 9;
        for(int i = Para1*9 ; i < Para1*9+9 ; ++i)
        {
            if(shudu[i].ColumnNum != NotChange1 && shudu[i].ColumnNum != NotChange2)
            {
                if(shudu[i].Value == 0)
                {
                    Delete_Candidata(&shudu[i],Value);
                    //Delete_Candidata_iterator(shudu[i].RowNum , shudu[i].ColumnNum , Value);
                    if(shudu[i].CandidataNum == 1)
                    {
                        Flag_UniqueAppear = 1;         //打开唯一候选数开关
                    }
                }
            }
            if(shudu[i + Sub].ColumnNum != NotChange1 && shudu[i + Sub].ColumnNum != NotChange2)
            {
               if(shudu[i + Sub].Value == 0)
                {
                    Delete_Candidata(&shudu[i + Sub],Value);
                    //Delete_Candidata_iterator(shudu[i].RowNum , shudu[i].ColumnNum , Value);
                    if(shudu[i + Sub].CandidataNum == 1)
                    {
                        Flag_UniqueAppear = 1;         //打开唯一候选数开关
                    }
                }
            }
        }
    }
    return 1;
}



void Method_RectangleVertex()
{
    //cout << "enter RV!!" << endl;
    vector<AppearNum> Appear(9);    //每行一个对象
    //int next_loop = 0;
    vector<Triplet> PotentialRV;
    //cout << "begin!" << endl;
    for(int m = 0 ; m < 9 ; ++m)
    {
        for(int i = 0 ; i < 9 ; ++i)    //按行搜索矩形顶点
        {
            //cout << "loop level:" << i << endl;
            for(int j = 0 ; j < 9 ; ++j)
            {//cout << Appear[i].AppearPos[m].size() << endl;
                if(shudu[i*9+j].Value == 0 && shudu[i*9+j].Candidata[m] != 0)
                {
                    Appear[i].AppearPos[m].push_back(j);//将i行出现的候选数m+1中送入其出现的位置的列值j
                }
            }
            if(Appear[i].AppearPos[m].size() == 2)//若该候选数m+1在该行i出现两次,列值分别为AppearPos[m][0]AppearPos[m][1]
            {
                Triplet transition(i , Appear[i].AppearPos[m][0] , Appear[i].AppearPos[m][1] , 0 , 0 , 0);
                PotentialRV.push_back(transition);

            }


        }
        vector<Triplet>::iterator it1 , it2;
        if(ExistRV(PotentialRV , it1 , it2 , "Row"))//若存在不同行但同列的矩形顶点
        {
            //cout << "RV:" << m+1 << " Row:" << it1->Row << it2->Row << " Col:" << it1->Row_Column1 << it1->Row_Column2 << " " << it2->Row_Column1 << it2->Row_Column2 << endl;
            MethodUsing_RecTangleVertex = 1;
            Delete_Candidata_RV(it1->Row , it2->Row , it1->Row_Column1 , it1->Row_Column2 , m+1 , "Row");//更新这两列的候选数
        }
       // cout << PotentialRV.size() << endl;
        Appear.clear();
        PotentialRV.clear();
    }
    Appear.clear();
    PotentialRV.clear();

    vector<AppearNum> Appears(9);

    for(int m = 0 ; m < 9 ; ++m)
    {
        for(int i = 0 ; i < 9 ; ++i)    //按列搜索矩形顶点
        {
            //cout << "loop level:" << i << endl;
            for(int j = 0 ; j <= 72 ; j += 9)
            {//cout << Appears[i].AppearPos[m].size() << endl;
                if(shudu[i+j].Value == 0 && shudu[i+j].Candidata[m] != 0)
                {
                    Appears[i].AppearPos[m].push_back(shudu[i+j].RowNum);//将i列出现的候选数m+1中送入其出现的位置的行值
                }

            }
            if(Appears[i].AppearPos[m].size() == 2)//若该候选数m+1在该列i出现两次,行值分别为AppearPos[m][0]AppearPos[m][1]
            {

                Triplet transition( 0 , 0 , 0 , i , Appears[i].AppearPos[m][0] , Appears[i].AppearPos[m][1]);
                PotentialRV.push_back(transition);

            }
        }
        vector<Triplet>::iterator it1 , it2;
        if(ExistRV(PotentialRV , it1 , it2 , "Col"))//若存在不同列但同行的矩形顶点
        {
            //cout << "RV:" << m+1 << " Col:" << it1->Col << it2->Col << " Row:" << it1->Col_Row1 << it1->Col_Row2 << " " << it2->Col_Row1 << it2->Col_Row2 << endl;
            MethodUsing_RecTangleVertex = 1;
            Delete_Candidata_RV(it1->Col , it2->Col , it1->Col_Row1 , it1->Col_Row2 , m+1 , "Col");//更新这两行的候选数
        }
       // cout << PotentialRV.size() << endl;
        Appears.clear();
        PotentialRV.clear();                                                              //此处应添加唯一候选数判断
    }
                                             //此处应添加唯一候选数判断
    if(Flag_UniqueAppear == 1)  //若出现唯一候选数标志
    {
        //cout << "RV  Again!!!" << endl;
        Method_Unique();
    }

    //cout << "finish!" << endl;


}








