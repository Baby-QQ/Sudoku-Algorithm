#ifndef SUDOKU_H_INCLUDED
#define SUDOKU_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <Windows.h>
#include <fstream>
#include <sstream>

using namespace std;



class Sudoku
{
public:
	int Value;
	int Candidata[9] = {1,2,3,4,5,6,7,8,9};
	int RowNum;
	int ColumnNum;
	int PalaceNum;
	int CandidataNum = 9;

};


extern vector<Sudoku> shudu;
extern int Palace[9];
extern int Array[9][9];

extern int CacheArrayNum;              //backup元素个数计数器
extern int Flag_LoopImplcit;                //隐式遍历开关（若有更新则打开）
extern int Flag_UniqueAppear;     //出现唯一候选数开关（默认为关）
extern int Flag_Implicit;                 //调用隐式法开关
extern int Finish_Check;      //检查标志，若数独完成，则check = 1
extern int MethodUsing_UniqueNumber , MethodUsing_ImplicitUnique , MethodUsing_Backtracking , MethodUsing_TripleChain ,
            MethodUsing_TripleChainImplicit , MethodUsing_RecTangleVertex ;     //判断使用哪些方法

extern clock_t StartTime , EndTime;
extern LARGE_INTEGER Freq,Start,End;

int Attribute_initialize();
int Candidata_initialize();
void Method_RectangleVertex();
void Method_TripleChainNumber();
int find_TripleChain(vector<Sudoku> &TripleChain , string UpdateStyle);
bool comp(const Sudoku &a , const Sudoku &b);
void Method_TripleChainNumber_Implicit();
int find_ImplicitTripleChain(vector<Sudoku> &ImplicitTripleChain , string UpdateStyle);
void Delete_Candidata_iterator(int RowNum , int ColumnNum ,int Value1 , int Value2 , int Value3);
int Method_Backtracking(int n);
void Method_Unique();
void Method_ImplicitUnique();
int Sudoku_Check();
int Array_Check();
int CandidataGuess();


extern int countt;
int Read_UniqueCandidata(int Candidata[]);

int Update_Sudoku(int RowNum,int ColumeNum,int PalaceNum,int Value);    //更新该行列宫的候选数
void Sudoku_renew();         //将vector的value赋回数组
int Delete_Candidata(Sudoku *shudu,int Value);   //删除该shudu对象的某个候选数
void Sudoku_print();
void Array_print();

int CanPlaceNumber(int n,int i);
void Delete_Candidata_iterator(int RowNum , int ColumnNum , int Value);



#endif // SUDOKU_H_INCLUDED
