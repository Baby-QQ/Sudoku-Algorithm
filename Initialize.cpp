#include "Sudoku.h"

int Attribute_initialize()      //初始化数独vector属性
{
    for(int i = 0 ; i < 9 ; i++)
    {
        for(int j = 0 ; j < 9 ; j++)
        {
            int x = i * 9 + j;
            shudu[x].Value = Array[i][j];
            shudu[x].RowNum = i;
            shudu[x].ColumnNum = j;
            if(i < 3)
                if(j < 3)
                    {
                        //Palace[0] = 0;
                        shudu[x].PalaceNum = 0;
                    }
                else if(j < 6)
                    {
                        //Palace[1] = 3;
                        shudu[x].PalaceNum = 1;
                    }
                else
                    {
                        //Palace[2] = 6;
                        shudu[x].PalaceNum = 2;
                    }
            else if(i < 6)
                if(j < 3)
                    {
                        //Palace[3] = 27;
                        shudu[x].PalaceNum = 3;
                    }
                else if(j < 6)
                    {
                        //Palace[4] = 30;
                        shudu[x].PalaceNum = 4;
                    }
                else
                    {
                        //Palace[5] = 33;
                        shudu[x].PalaceNum = 5;
                    }
            else
                if(j < 3)
                    {
                        //Palace[6] = 54;
                        shudu[x].PalaceNum = 6;
                    }
                    else if(j < 6)
                    {
                        //Palace[7] = 57;
                        shudu[x].PalaceNum = 7;
                    }
                    else
                    {
                        //Palace[8] = 60;
                        shudu[x].PalaceNum = 8;
                    }
        }
    }
    return 1;
}

int Candidata_initialize()       //初始化候选字
{
    int d;
    for(int i = 0 ; i < 81 ; i++)
    {
        for(int j = 0 ; j < 9 ; ++j)
        {
            shudu[i].Candidata[j] = j+1;
        }
        shudu[i].CandidataNum = 9;
        if(shudu[i].Value == 0)
        {
            for(int j = shudu[i].RowNum * 9 ; j < shudu[i].RowNum * 9 + 9 ; j++)
            {
                if(shudu[j].Value!=0)
                {
                    Delete_Candidata(&shudu[i],shudu[j].Value);
                }
            }
            for(int m = shudu[i].ColumnNum ; m < 81 ; m = m + 9)
            {
                if(shudu[m].Value!=0)
                {
                    Delete_Candidata(&shudu[i],shudu[m].Value);
                }
            }
            d = Palace[shudu[i].PalaceNum];
            for(int e = 0 ; e < 3 ; e++)
            {
                for(int j = 0 ; j < 3 ; j++)
                {
                    if(shudu[d].Value!=0)
                    {
                        Delete_Candidata(&shudu[i],shudu[d].Value);
                    }
                    d++;
                }
                d = d + 6;
            }
        }

    }
    return 1;
}


