/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : calcfunction.h --- CalcFunction
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/1
*******************************************************************/
#ifndef CALCFUNCTION_H
#define CALCFUNCTION_H

#include "complex.h"

#include <QQueue>
#include <QString>
#include <QStack>

const char STR_OPERATORS[][4]=
         {"#","%","!","^","nad","div", "mod", "*", "/","+", "-","(",")" ","}; // '#'是栈底标志
const char STR_FUNCTIONS[][8]=
         {"abs","arccos","arccosh","arccot","arccoth","arcsin","arcsinh","arctan","arctanh",
          "conj","cos","cosh","cot","coth","csc","cur","exp","gcd","lcm","lg","ln",
          "log","pow","sec","sin","sinh","sqr","sqrt","tan","tanh"};
const char STR_CONST[][6]=
        {"$c","$e","$en","$eps0","$g","$h","$k","$me","$mi0","$mn","$mp","$mu","$pi"};
/*
$pi#圆周率#3.141592653589793238#
$e#欧拉指数#2.71828182845905#
$g#重力加速度#9.80665#m / s^2
$c#真空中光速#299792458#m / s
$eps0#真空介电常数#8.854187817E-12#F / m
$mi0#真空磁导率#1.2566370614E-6#H / m
$en#基本电荷#1.60217733E-19#C
$mu#原子质量#1.6605402E-27#kg
$me#电子质量#9.1093897E-31#kg
$mp#质子质量#1.6726231E-27#kg
$mn#中字质量#1.6749286E-27#kg
$k#玻耳兹曼常数#1.380658E-23#J / K
$h#普朗克常数#6.6260693E-34#J.s
*/
//优先级在栈内和栈外的顺序
const int PRI_IN[] = {0, 15, 13, 10, 9, 7, 7, 5, 5, 3, 3, 1, -1, 1};   //这里的-1是没用的
const int PRI_OUT[] ={0, 14, 12, 11, 8, 6, 6, 4, 4, 2, 2};
enum RETURN
{
    RET_CORRECT = 1,       //表达式语法正确
    RET_WRONG  = 0,        //表达式中存在异常字符
    RET_WRONGSTR =-1,      //未申明的字符串
    RET_END = -2,          //表达式结束
    RET_BACK = -3,         //括号不匹配
    RET_POINT =-4,         //多余小数点
    RET_OPER =-5,          //连续使用两个运算符
    RET_START=-6,          //表达式开头不合法
    RET_LAST =-7,          //表达式结尾不合法
    RET_BACKEMPTY=-8,      //括号中啥都没有
    RET_OPERNUMBER=-9,     //运算符缺少操作数
    RET_FUNNUMBER=-10,     //函数缺少操作数
    RET_ZERO=-11,          //除数为零
    RET_INT=-12,           //运算符只能用于整数
    RET_NONGINT=-13,       //NAD只能用于非负整数
    RET_NEGSQRT=-14,       //负数不能开方
    RET_ARGUMENT=-15,      //函数参数非法
    RET_INF=-16,           //数据溢出
    RET_COMMA=-17,         //逗号使用不合法
    RET_COMPLEX=-18,       //复数域下不能计算的函数
    RET_UPPERLETTER=-19,   //非法使用大写字母
    RET_GCDLCM=-20,        //gcd和lcmd的参数不合法
    RET_NUMBER=-21,        //使用数字不合法
    RET_VARIABLE=-22,      //变量名
    RET_USEINCOMP=-23,     //该函数只能在复数域下使用
    RET_SCIENTIFIC=-24     //科学计数法使用有误
};

const double INF=1.7e308;
const double CONST[]={299792458,2.71828182845905,1.60217733e-19,8.854187817e-12,9.80665,
                      6.6260693e-34,1.380658e-23,9.1093897e-31,1.2566370614e-6,
                      1.6749286e-27,1.6726231e-27,1.6605402e-27,3.141592653589793238};
inline bool isZero( double db )
{
    if(db<DBL_EPS&&db>-DBL_EPS)
        return 1;
    else
        return 0;
}

inline bool isHexNumber(QChar ch)
{
    if((ch>='0'&&ch<='9')||ch=='.'||ch==' '||(ch>='A'&&ch<='F'))
       return true;
    else
       return false;
}

inline int toNumber(QChar ch)
{
    if(ch>='0'&&ch<='9')
       return ch.toLatin1()-48;
    else
        return ch.toLatin1()-55;
}

class CCalculator
{
public:
    unsigned short ERRORBEGIN,ERRORLENGTH;                  //记录错误的位置
public:
     struct Symbol
     {
        enum SYMTYPE                                        //枚举类型：操作数、操作符、函数
        {NUMBER,OPERATOR,FUNCTION}type;
        enum OPTYPE
        {
            //其中%和!是单目运算符
            //这里各个符号有顺序，不能交换位置
            STACKEND,                                        // #结束符
            PERCENT,FACTORIAL,POWER,NAD,DIV,MOD,             // % ! ^ nad div,mod
            MULTIPLY,DIVIDE,ADD,SUBSTRACT,                   // * / + -
            LEFTBRACE,RIGHTBRACE,                            // ( )
            COMMA                                            // ,逗号
        };
        enum FUNTYPE
        {
            ABS,ACOS,ACOSH,ACOT,ACOTH,ASIN,ASINH,ATAN,ATANH,
            CONJ,COS,COSH,COT,COTH,CSC,CUR,                  //CONJ为共轭复数函数,CUR为立方根
            EXP,GCD,LCM,LG,LN,LOG,POW,                       //含两个参数gcd(a,b),lcm(a,b),log(a,b),pow(a,b)
            SEC,SIN,SINH,SQR,SQRT,TAN,TANH                   //SQR为平方
        };
        struct
        {
            OPTYPE opType;
            FUNTYPE funType;
            double number;
            Complex CompNumber;
        } content;
     };
public:
      CCalculator();
      int Calc(QString &result,
               QString &express,
               int precision = 6,
               bool isDeg = true,
               bool isFraction = false,
               bool isComplex = false,
               bool isChangeSystem = false,
               int oldSystem = 10,
               int newSystem = 10);
private:
     QString m_strExp,errorStr;
     int m_curIndex;
     int isComma;                                               //记录最多可以使用‘,’的个数
     QQueue<Symbol> QueSymbol;									//数据和操作符队列
     int TransExp(QString &express );						    //表达式中缀式转换为后缀式及语法检查
     int GetNextSymbol(QQueue<Symbol> &que,Symbol &sym);	    //获得下一个操作数或操作符
     int Check_Start();											//检查表达式开头是否合法
     int Check_Last();											//检查表达式结尾是否合法
     int Check_Next();											//检查是否有连续的运算符
     bool IsValid(QString str);                                 //检查字符是否合法
     bool IsOpt();                                              //判断是否是运算符
     bool CompPri(Symbol &symIN,Symbol &symOUT);				//优先级比较，前者大返回1，后者大返回0

     int DoCalcOpt(QStack<Symbol> &stk,Symbol &sym );				//运算符计算
     int DoCalcFun(QStack<Symbol>&stk,Symbol &sym);     //函数计算
     void Fraction(double dl,QString &result);
private:
     bool isComplex;
     bool isDeg;
     bool isChangeSystem;
     int newSystem;
     int oldSystem;

};

double factorial(int n);
double combinate(int k,int n);
qlonglong gcd(qlonglong a,qlonglong b);
qlonglong lcm(qlonglong a,qlonglong b);
QString changeSystem(QString num,int new_System, int old_System=10);
bool isErrorNumber(QString str,int system);
Complex getComplex(QString str);

#endif // CALCFUNCTION_H
