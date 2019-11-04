/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : calcfunction.cpp --- CalcFunction
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/1
*******************************************************************/
#include "calcfunction.h"

#include <cmath>
#include <qmath.h>
#include <QRegExp>
#include <QSettings>

CCalculator::CCalculator():m_curIndex(0){}

int CCalculator::TransExp(QString &express)
{
    m_curIndex = 0;                       //当前字符所指位置
    if(!IsValid(express))                 //检查字符串中是否存在异常字符
    {return RET_WRONG;}
    unsigned int size,len=0,i;
    short countBack=0;                    //记录小括号是否匹配
    size=express.length();
    QChar charray[2000];
    QString str;
    //对不同进制的数进行预处理
    if(isChangeSystem)
    {
        for(i=0;i<size&&countBack>=0;i++)
        {
            if(isHexNumber(express[i]))
            {
                int position = i,res=0;
                str="";
                do{
                    if(express[i]==' ')
                    {i++;continue;}
                    if(oldSystem!=16&&express[i].isUpper())
                    {
                        ERRORBEGIN=i;
                        return RET_UPPERLETTER;
                    }
                    str+=express[i++];
                }while(i<size&&isHexNumber(express[i]));
                if(oldSystem==10)
                {
                    res=str.length();
                    for(int k=0;k<res;k++)
                        charray[len++]=str[k];
                }
                str=changeSystem(str,newSystem,oldSystem);
                express.replace(position,i-position,str);
                size=express.length();
                i=position+str.length()-1;
                if(oldSystem!=10)
                {
                    if(newSystem!=10)
                        str=changeSystem(str,10,newSystem);
                    res=str.length();
                    for(int k=0;k<res;k++)
                        charray[len++]=str[k];
                }

            }
            else
            {
                if(express[i].isUpper())
                {
                    ERRORBEGIN=i;
                    return RET_UPPERLETTER;
                }
                charray[len++]=express[i];
                if(express[i]=='(')
                    countBack++;
                else if(express[i]==')')
                    countBack--;
            }
        }
    }
    else if(newSystem!=10)
    {
        for(i=0;i<size&&countBack>=0;i++)
        {
            if(isHexNumber(express[i]))
            {
                str="";
                do{
                    if(express[i]==' ')
                    {i++;continue;}
                    if(oldSystem!=16&&express[i].isUpper())
                    {
                        ERRORBEGIN=i;
                        return RET_UPPERLETTER;
                    }
                    str+=express[i++];
                }while(i<size&&isHexNumber(express[i]));
                int res;
                if(isErrorNumber(str,newSystem))
                    return RET_NUMBER;
                str=changeSystem(str,10,newSystem);
                res=str.length();
                for(int k=0;k<res;k++)
                    charray[len++]=str[k];
                i--;
            }
            else
            {
                if(express[i].isUpper())
                {
                    ERRORBEGIN=i;
                    return RET_UPPERLETTER;
                }
                charray[len++]=express[i];
                if(express[i]=='(')
                    countBack++;
                else if(express[i]==')')
                    countBack--;
            }
        }
    }
    else
    {
        for(i=0;i<size&&countBack>=0;i++)
        {
            if(express[i].isUpper())
            {ERRORBEGIN=i;return RET_UPPERLETTER;}
            else
            {
                charray[len++]=express[i];
                if(express[i]=='(')
                    countBack++;
                else if(express[i]==')')
                    countBack--;
            }
        }
    }

    m_strExp=QString(charray);

    if(countBack!=0)
    {
        if(countBack<0)
        {ERRORBEGIN=i-1;}
        else
        {
            for(i=0;i<size;i++)
                if(express[i]=='(')
                {ERRORBEGIN=i;break;}
        }
        return RET_BACK;
    }                    //括号不匹配
    if(Check_Start()==RET_START)          //表达式开头有错
        return RET_START;
    if(Check_Last()==RET_LAST)           //表达式结尾有错
        return RET_LAST;
    Symbol sym;
    QQueue<Symbol> que;
    int ret;
    while((ret=GetNextSymbol(que,sym))!=RET_END)
    {
        if(ret!=RET_CORRECT)
        {return ret;}
    }
    //中缀式转换成后缀式
    Symbol symTop;
    QStack<Symbol> stk;        //存放操作符和函数的栈
    //将‘#’压入栈底
    symTop.type=Symbol::OPERATOR;
    symTop.content.opType=Symbol::STACKEND;
    stk.push(symTop);
    while(!que.empty())
    {
        symTop=que.head();
        que.dequeue();
        if(symTop.type==Symbol::NUMBER)
        {//操作数直接入队列
            QueSymbol.enqueue(symTop);
            continue;
        }
        else if(symTop.type==Symbol::FUNCTION)
        {//函数入操作符栈
            stk.push(symTop);
            continue;
        }
        //以下均为Symbol::OPERATOR的情况
        else if(symTop.content.opType==Symbol::LEFTBRACE)
        {//'('入操作符栈
            stk.push(symTop);
            continue;
        }
        else if(symTop.content.opType==Symbol::FACTORIAL||symTop.content.opType==Symbol::PERCENT)
        {//单目运算符直接入队列
            if(!stk.empty()&&stk.top().type==Symbol::FUNCTION)
            {QueSymbol.enqueue(stk.top()); stk.pop();}
            QueSymbol.enqueue(symTop);
            continue;
        }
        else if(symTop.content.opType==Symbol::RIGHTBRACE)
        {//遇到')'，弹出操作符，直到'('
            while(stk.top().type==Symbol::FUNCTION||
                  stk.top().content.opType!=Symbol::LEFTBRACE)
            {
                QueSymbol.enqueue(stk.top());
                stk.pop();
            }
            stk.pop();     //将'('弹出栈
            continue;
        }
        else if(symTop.content.opType==Symbol::COMMA)
        {//遇到‘,’，弹出操作符，直到‘(’
            while(stk.top().type==Symbol::FUNCTION||
                  stk.top().content.opType!=Symbol::LEFTBRACE)
            {
                QueSymbol.enqueue(stk.top());
                stk.pop();
            }
            stk.push(symTop);
            continue;
        }
        else if(!CompPri(stk.top(),symTop))
        {
            stk.push(symTop);
            continue;
        }
        else
        {
            do
            {
                QueSymbol.enqueue(stk.top());
                stk.pop();
            }while(CompPri(stk.top(),symTop));
            stk.push(symTop);
        }
    }
    while(!stk.empty())
    {
        QueSymbol.enqueue(stk.top());
        stk.pop();
    }
    return RET_CORRECT;
}
int CCalculator::GetNextSymbol(QQueue<Symbol>&que,Symbol &sym)
{
    int size=m_strExp.length();
    if( m_curIndex >=size)
        return RET_END;
    QChar ch=m_strExp[m_curIndex];
    while(ch==' ')
    {ch=m_strExp[++m_curIndex];}
    if(ch=='$')//常量
    {
        QString str;
        ERRORLENGTH=0;
        do
        {
            if(ch!=' ')str+=ch;
            m_curIndex++,ERRORLENGTH++;
            if(m_curIndex>=size)
                break;
            else
                ch=m_strExp[m_curIndex];
        }while(ch.isLetterOrNumber()||ch==' ');
        double temp;
        int lower =0,upper = 12,mid;
        while( lower <=upper )
        {//二分法查找常量
            mid = (lower+upper)/2;
            if(str == STR_CONST[mid])
            {
                temp=CONST[mid];
                sym.type = Symbol::NUMBER;
                if(isComplex)
                    sym.content.CompNumber = Complex(temp);
                else
                    sym.content.number =temp;             //将字符串转化为数字
                que.enqueue(sym);
                if(ch=='$'||ch=='(')
                {
                    sym.type = Symbol::OPERATOR;
                    sym.content.opType=Symbol::MULTIPLY;
                    que.enqueue(sym);
                }
                return RET_CORRECT;
            }
            else if(str <STR_CONST[mid])
                upper = mid -1;
            else
                lower = mid+1;
        }
        //未找到常量
        ERRORBEGIN=m_curIndex-ERRORLENGTH;
        return RET_WRONGSTR;
    }
    if(ch=='.'||ch.isDigit())
    {
        QString str;
        bool bHasPeriod = false;
        do
        {
            if( !bHasPeriod && ch == '.' )
            {ERRORBEGIN=m_curIndex;bHasPeriod = true;}
            else if( bHasPeriod && ch == '.' )
            { ERRORBEGIN=m_curIndex;return RET_POINT;}
            if(ch!=' ')
                str+=ch;
            m_curIndex++;
            if(m_curIndex>=size)
                break;
            else
                ch=m_strExp[m_curIndex];
        }while( ch == '.' || ch.isDigit()||ch==' ');
        if(str[str.length()-1]=='.')
        {return RET_POINT;}
        sym.type = Symbol::NUMBER;
        if(isComplex)
        {
            sym.content.CompNumber = Complex(str.toDouble());
        }
        else
        {
            sym.content.number = str.toDouble();             //将字符串转化为数字
        }
        que.enqueue(sym);
        if(m_curIndex<size&&!IsOpt())                        //数字后面是‘（’或函数则添加一个‘*’
        {
            sym.type = Symbol::OPERATOR;
            sym.content.opType=Symbol::MULTIPLY;
            que.enqueue(sym);
        }
        return (RET_CORRECT);
    }
    else
    {
        if(ch<'a'||ch>'z')
        {
            int ret=Check_Next();
            if(ret!=RET_CORRECT)        //运算符使用不正确
            {return ret;}

            if(ch=='+')
            {
                int i;
                for(i=m_curIndex-1;i>=0;i--)
                {if(m_strExp[i]!=' ')break;}
                if(i==-1||m_strExp[i]=='('||m_strExp[i]==',')
                {
                    // 如果‘+’在表达式开头或‘(’或‘,’后面，则表示正号
                    m_curIndex++;
                    return RET_CORRECT;
                }
                else
                {
                    sym.type = Symbol::OPERATOR;
                    sym.content.opType = Symbol::ADD;
                    m_curIndex++;
                    que.enqueue(sym);
                    return RET_CORRECT;
                }
            }
            else if(ch=='-')
            {
                int i;
                for(i=m_curIndex-1;i>=0;i--)
                {if(m_strExp[i]!=' ')break;}
                if(i==-1||m_strExp[i]=='('||m_strExp[i]==',')
                {
                    // 如果‘-’在表达式开头或‘(’后面，则表示负号
                    m_curIndex++;
                    sym.type = Symbol::NUMBER;
                    if(isComplex)
                    {
                        sym.content.CompNumber = Complex(-1);
                    }
                    else
                    {
                        sym.content.number = -1;
                    }
                    que.enqueue(sym);
                    sym.type = Symbol::OPERATOR;
                    sym.content.opType=Symbol::MULTIPLY;
                    que.enqueue(sym);
                    return RET_CORRECT;
                }
                else
                {
                    sym.type = Symbol::OPERATOR;
                    sym.content.opType = Symbol::SUBSTRACT;
                    m_curIndex++;
                    que.enqueue(sym);
                    return RET_CORRECT;
                }
            }
            else if(ch=='*')
            {
                sym.type = Symbol::OPERATOR;
                m_curIndex++;
                sym.content.opType = Symbol::MULTIPLY;
                que.enqueue(sym);
                return RET_CORRECT;
            }
            else if(ch=='/')
            {
                sym.type = Symbol::OPERATOR;
                sym.content.opType = Symbol::DIVIDE;
                m_curIndex++;
                que.enqueue(sym);
                return RET_CORRECT;
            }
            else if(ch=='(')
            {
                sym.type = Symbol::OPERATOR;
                sym.content.opType = Symbol::LEFTBRACE;
                m_curIndex++;
                que.enqueue(sym);
                return RET_CORRECT;
            }
            else if(ch==')')
            {
                sym.type = Symbol::OPERATOR;
                sym.content.opType = Symbol::RIGHTBRACE;
                m_curIndex++;
                que.enqueue(sym);
                if(m_curIndex<size&&!IsOpt())         //')'后面是'('或函数则添加一个'*'
                {
                    sym.type = Symbol::OPERATOR;
                    sym.content.opType=Symbol::MULTIPLY;
                    que.enqueue(sym);
                }
                return RET_CORRECT;
            }
            else if(ch=='^')
            {
                sym.type = Symbol::OPERATOR;
                sym.content.opType = Symbol::POWER;
                m_curIndex++;
                que.enqueue(sym);
                return RET_CORRECT;
            }
            else if(ch=='%')
            {
                if(isComplex)
                    return RET_COMPLEX;               //复数域下不能处理这些运算
                sym.type=Symbol::OPERATOR;
                sym.content.opType = Symbol::PERCENT;
                m_curIndex++;
                que.enqueue(sym);
                if(m_curIndex<size&&!IsOpt())          //%后面是‘（’或函数则添加一个‘*’
                {
                    sym.type = Symbol::OPERATOR;
                    sym.content.opType=Symbol::MULTIPLY;
                    que.enqueue(sym);
                }
                return RET_CORRECT;
            }
            else if(ch=='!')
            {
                if(isComplex)
                    return RET_COMPLEX;                 //复数域下不能处理这些运算
                sym.type=Symbol::OPERATOR;
                sym.content.opType = Symbol::FACTORIAL;
                m_curIndex++;
                que.enqueue(sym);
                if(m_curIndex<size&&!IsOpt())           //!后面是‘（’或函数则添加一个‘*’
                {
                    sym.type = Symbol::OPERATOR;
                    sym.content.opType=Symbol::MULTIPLY;
                    que.enqueue(sym);
                }
                return RET_CORRECT;
            }
            else if(ch==',')
            {
                if(isComplex)
                    return RET_COMPLEX;                 //复数域下不能处理这些运算
                int countLeftback=0;
                bool work=false;
                for(int i=m_curIndex-1;i>=0;i--)          //检查','左边左括号数目是否大于右括号数目
                {
                    if(countLeftback>0)
                    {work=true; break;}
                    if(m_strExp[i]=='(')
                        countLeftback++;
                    else if(m_strExp[i]==')')
                        countLeftback--;
                    else if(m_strExp[i]==',')
                    {
                        if(countLeftback==0)
                            break;
                    }
                }
                if(!work||isComma<=0)                    //逗号使用不合法
                {ERRORBEGIN=m_curIndex; return RET_COMMA;}
                isComma--;
                sym.type=Symbol::OPERATOR;
                sym.content.opType = Symbol::COMMA;
                m_curIndex++;
                que.enqueue(sym);
                return RET_CORRECT;
            }
        }
        else   //含有字母
        {
            if(ch=='e')     //科学计数法
            {
                int i;
                if(m_curIndex>0&&m_curIndex<size-1)
                {
                    QChar pre=m_strExp[m_curIndex-1],aft=m_strExp[m_curIndex+1];
                    for(i=m_curIndex-2;pre==' '&&i>=0;--i)
                    {pre=m_strExp[i];}
                    if(pre.isDigit())
                    {
                        for(i=m_curIndex+2;aft==' ';i++)
                        {aft=m_strExp[i];}
                        if(aft.isDigit()||aft=='.')
                        {
                            sym.type=Symbol::NUMBER;
                            if(isComplex)
                                sym.content.CompNumber=Complex(10);
                            else
                                sym.content.number=10;
                            que.enqueue(sym);
                            sym.type = Symbol::OPERATOR;
                            sym.content.opType=Symbol::POWER;
                            que.enqueue(sym);
                            m_curIndex++;
                            return RET_CORRECT;
                        }
                        else if(aft=='+'||aft=='-')
                        {
                            bool sign=(aft=='+')?1:0;
                            do{
                                aft=m_strExp[i++];
                            }while(aft==' ');
                            if(aft.isDigit()){
                                sym.type=Symbol::NUMBER;
                                if(sign){
                                    if(isComplex)
                                        sym.content.CompNumber=Complex(10);
                                    else
                                        sym.content.number=10;
                                }
                                else{
                                    if(isComplex)
                                        sym.content.CompNumber=Complex(0.1);
                                    else
                                        sym.content.number=0.1;
                                }
                                que.enqueue(sym);
                                sym.type = Symbol::OPERATOR;
                                sym.content.opType=Symbol::POWER;
                                que.enqueue(sym);
                                m_curIndex=i-1;
                                return RET_CORRECT;
                            }
                        }
                        else
                        {
                            ERRORBEGIN=m_curIndex;
                            return RET_SCIENTIFIC;
                        }
                    }
                    else{
                        ERRORBEGIN=m_curIndex;
                        return RET_SCIENTIFIC;
                    }
                }
            }
            QString str;
            ERRORLENGTH=0;
            do
            {
                if(ch!=' ')
                    str+=ch;
                m_curIndex++,ERRORLENGTH++;
                if(m_curIndex>=size)break;
                else  ch=m_strExp[m_curIndex];
            }while(ch.isLetter()||ch==' ');
            if(str=="mod"||str=="div"||str=="nad")
            {
                sym.type=Symbol::OPERATOR;
                if(ch=='*'||ch=='/'||ch==')'||ch=='^'||ch=='!'||ch=='%'||ch==',')
                    return RET_OPER;
                if(str=="mod")
                    sym.content.opType=Symbol::MOD;
                else if(str=="div")
                    sym.content.opType=Symbol::DIV;
                else
                    sym.content.opType=Symbol::NAD;
                if(isComplex)
                    return RET_COMPLEX;    //复数域下不能处理这些运算
                que.enqueue(sym);
                for(int i=m_curIndex-ERRORLENGTH-1;i>=0;i--)
                {
                    if(m_strExp[i]==' ')
                        continue;
                    else if(m_strExp[i]==','||m_strExp[i]=='(')
                    {errorStr=str;return RET_OPERNUMBER;}
                    else
                        return RET_CORRECT;
                }
                return RET_CORRECT;
            }
            else if(str=="i")       //i为虚数单位
            {
                if(isComplex){
                    if(m_curIndex>1&&m_strExp[m_curIndex-2].isDigit())
                    {
                        que.pop_back();   //将乘号弹出队列尾
                        double r=que.back().content.CompNumber.getReal();
                        que.back().content.CompNumber=Complex(0,r);
                    }
                    else{
                        sym.type=Symbol::NUMBER;
                        sym.content.CompNumber = Complex(0,1);
                        que.enqueue(sym);
                    }
                    if(ch.isDigit()||ch=='$')
                    {
                        sym.type = Symbol::OPERATOR;
                        sym.content.opType=Symbol::MULTIPLY;
                        que.enqueue(sym);
                    }
                    return RET_CORRECT;
                }
                else{
                    ERRORBEGIN=m_curIndex-ERRORLENGTH;
                    return RET_WRONGSTR;
                }
            }
            else
            {
                sym.type = Symbol::FUNCTION;
                int lower =0,upper = (int)Symbol::TANH,mid;
                while(lower <=upper)
                {//二分法查找函数
                    mid = (lower+upper)/2;
                    if(str == STR_FUNCTIONS[mid])
                    {
                        if(isComplex)
                        {
                            if(str!="abs"&&str!="conj")
                                return RET_COMPLEX;    //复数域下不能处理这些运算
                        }
                        sym.content.funType=(Symbol::FUNTYPE)mid;
                        que.enqueue(sym);
                        if(mid==(int)Symbol::LOG||mid==(int)Symbol::POW||
                                mid==(int)Symbol::GCD||mid==(int)Symbol::LCM)
                        {isComma++;}
                        return RET_CORRECT;
                    }
                    else if(str<STR_FUNCTIONS[mid])
                        upper = mid -1;
                    else
                        lower = mid+1;
                }
                if(str=="x"||str=="y"||str=="z"){
                    QSettings settings;
                    if(str=="x"&&settings.value("Variable_X_Bool").toBool())
                    {
                        sym.type = Symbol::NUMBER;
                        if(isComplex){
                            QString number = settings.value("Variable_X_Value").toString();
                            sym.content.CompNumber = getComplex(number);
                        }
                        else
                            sym.content.number =settings.value("Variable_X_Value").toDouble();
                        que.enqueue(sym);
                        return RET_CORRECT;
                    }
                    else if(str=="y"&&settings.value("Variable_Y_Bool").toBool())
                    {
                        sym.type = Symbol::NUMBER;
                        if(isComplex){
                            QString number = settings.value("Variable_Y_Value").toString();
                            sym.content.CompNumber = getComplex(number);
                        }
                        else
                            sym.content.number =settings.value("Variable_Y_Value").toDouble();
                        que.enqueue(sym);
                        return RET_CORRECT;
                    }
                    else if(str=="z"&&settings.value("Variable_Z_Bool").toBool())
                    {
                        sym.type = Symbol::NUMBER;
                        if(isComplex){
                            QString number = settings.value("Variable_Z_Value").toString();
                            sym.content.CompNumber = getComplex(number);
                        }
                        else
                            sym.content.number =settings.value("Variable_Z_Value").toDouble();
                        que.enqueue(sym);
                        return RET_CORRECT;
                    }
                    else
                        return RET_VARIABLE;
                }
                else{
                    ERRORBEGIN=m_curIndex-ERRORLENGTH;
                    return RET_WRONGSTR;
                }
            }
        }
        return RET_WRONG;
    }
}
int CCalculator::Calc(QString &result, QString &express, int precision, bool isDeg,
                      bool isFraction, bool isComplex, bool isChangeSystem, int oldSystem, int newSystem)
{
    this->isComplex = isComplex;
    this->isDeg = isDeg;
    this->isChangeSystem = isChangeSystem;
    this->oldSystem=oldSystem;
    this->newSystem=newSystem;
    if(isFraction==true)
    {
        QRegExp regExp("^(-?\\d+)(/\\d+$)");
        if(regExp.indexIn(express)!=-1)
        {
            qlonglong q1,q2,q;
            int index=express.indexOf('/');
            bool isNegative=false;
            q1=express.left(index).toLongLong();
            q2=express.right(express.length()-index-1).toLongLong();
            if(q1<0){isNegative=true;q1=-q1;}
            q=gcd(q1,q2);
            q1/=q;q2/=q;
            if(isNegative)
                result=QString("-%1/%2").arg(q1).arg(q2);
            else
                result=QString("%1/%2").arg(q1).arg(q2);
            index=result.indexOf('/');
            for(int i=index+1;i<result.length();i+=4)
            {result.insert(i,' ');}
            for(int i=index;i>=0;i-=3)
            {result.insert(i,' ');}
            return RET_CORRECT;
        }
    }
    int ret;
    while(!QueSymbol.empty())            //清空堆栈
        QueSymbol.dequeue();
    isComma=0;                           //将记录逗号使用个数清零
    ret=this->TransExp(express);
    if(ret!=RET_CORRECT)
    {result=errorStr; return ret;}
    QStack<Symbol> stk;
    Symbol sym;
    while(!QueSymbol.empty())
    {
        sym=QueSymbol.head();
        QueSymbol.dequeue();
        if(sym.type==Symbol::NUMBER)
        {stk.push(sym);continue;}
        else if(sym.type==Symbol::OPERATOR)//运算符计算
        {
            if(sym.content.opType==Symbol::COMMA)
            {stk.push(sym);continue;}
            ret=DoCalcOpt(stk,sym);
            if(ret!=RET_CORRECT)
            {
                result=STR_OPERATORS[(int)sym.content.opType];
                return ret;
            }
        }
        else    //函数计算
        {
            ret=DoCalcFun(stk,sym);
            if(ret!=RET_CORRECT)
            {
                result=STR_FUNCTIONS[(int)sym.content.funType];
                return ret;
            }
        }
        if(ret!=RET_CORRECT)
            return ret;
    }
    if(isComplex==true)
    {
        double real=stk.top().content.CompNumber.getReal();
        double imag=stk.top().content.CompNumber.getImag();
        result = Complex(real,imag).toString(precision,1e-8);
        return RET_CORRECT;
    }
    double dl=stk.top().content.number;
    if(newSystem==10)
        result.setNum(dl,'g',precision);
    else
        result.setNum(dl,'g',20);
    result=changeSystem(result,newSystem);
    if(isFraction==true)//将小数转换为分数
    {
        Fraction(dl,result);
        int index;
        index=result.indexOf('/');
        for(int i=index+1;i<result.length();i+=4)
        {result.insert(i,' ');}
        for(int i=index;i>=0;i-=3)
        {result.insert(i,' ');}
        return RET_CORRECT;
    }
    if(!result.contains('e'))   //加入空格符分隔
    {
        int ret=result.indexOf('.',0);
        if(ret==-1){
            for(int i=result.size();i>=0;i-=3)
            {result.insert(i,' ');}
        }
        else{
            for(int i=ret+4;i<result.size();i+=4)
            {result.insert(i,' ');}
            for(int i=ret-3;i>=0;i-=3)
            {result.insert(i,' ');}
        }
    }
    return RET_CORRECT;
}
int CCalculator::Check_Start()
{
    QChar ch=m_strExp[0];
    int i=0;
    while(ch==' ')
    {ch=m_strExp[++i];}
    if(ch.isLetterOrNumber()||ch=='-'||ch=='+'||ch=='('||ch=='.'||ch=='$')
    {return RET_CORRECT;}
    else
    {ERRORBEGIN=i;return RET_START;}

}
int CCalculator::Check_Last()
{
    int i=m_strExp.length()-1;
    QChar ch=m_strExp[i];
    while(ch==' '&&i>0)
    {ch=m_strExp[--i];}
    if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='^'||ch==',')
    {ERRORBEGIN=i;return RET_LAST;}
    return RET_CORRECT;
}
int CCalculator::Check_Next()
{
    //本函数前提是m_strExp[m_curIndex]是一个运算符
    if(m_curIndex>=m_strExp.length()-1)
        return RET_CORRECT;
    int i=m_curIndex+1;
    QChar ch1=m_strExp[m_curIndex],ch2=m_strExp[i];
    while(ch2==' '){ch2=m_strExp[++i];}
    if(ch2=='('||ch2.isLetterOrNumber()||ch2=='.'||ch2=='$')
        return RET_CORRECT;
    if(ch1==')'||((ch1=='('||ch1==',')&&(ch2=='-'||ch2=='+')))
        return RET_CORRECT;
    else if(ch1=='%')
    {
        if(ch2=='%')
        { ERRORBEGIN=m_curIndex,ERRORLENGTH=i-m_curIndex+1;
            return RET_OPER;}
        else return RET_CORRECT;
    }
    else if(ch1=='!')
    {
        if(ch2=='%'||ch2=='!')
        { ERRORBEGIN=m_curIndex,ERRORLENGTH=i-m_curIndex+1;
            return RET_OPER;}
        else return RET_CORRECT;
    }
    else if(ch2==',')
    { ERRORBEGIN=i;
        return RET_COMMA;}
    else if(ch1=='('&&ch2==')')
    {ERRORBEGIN=m_curIndex,ERRORLENGTH=i-m_curIndex+1;
        return RET_BACKEMPTY;      //括号中没有表达式
    }

    else
    { ERRORBEGIN=m_curIndex,ERRORLENGTH=i-m_curIndex+1;
        return RET_OPER;}
}
bool CCalculator::IsValid(QString str)
{
    int  size=str.length(),i=0;
    QChar ch;
    for(i=0;i<size;i++)
    {
        ch=str[i];
        if(ch.toLatin1() > 122 || ch.toLatin1() < 32)
        {ERRORBEGIN=i;return 0;}
        if(ch.isLetterOrNumber())
            continue;
        else if(ch=='.'||ch=='%'||ch=='!'||ch=='^'||ch=='*'||ch=='/'||ch=='+'||
                ch=='-'||ch=='('||ch==')'||ch==','||ch==' '||ch=='$')
            continue;
        else
        {ERRORBEGIN=i;return 0;}
    }
    return 1;
}
bool CCalculator::IsOpt()
{
    QChar ch=m_strExp[m_curIndex];
    int length=m_strExp.length()-1;
    while(ch==' ')
    {
        if(m_curIndex>=length)
        {++m_curIndex; return true;}
        ch=m_strExp[++m_curIndex];
    }
    if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch==')'||ch=='^'||ch=='!'||ch=='%'||ch=='n'||ch=='m'||ch=='d'||ch==',')
        return true;
    else return false;
}
bool CCalculator::CompPri(Symbol &symIN,Symbol &symOUT)
{
    if(symIN.type==Symbol::FUNCTION)
        return 1;
    else if(PRI_IN[(int)symIN.content.opType]>PRI_OUT[(int)symOUT.content.opType])
        return 1;
    else
        return 0;
}
int CCalculator::DoCalcOpt(QStack<Symbol>&stk,Symbol &sym )
{
    int size=stk.size();
    if(size<1)return RET_OPERNUMBER;
    switch (sym.content.opType)
    {
    case Symbol::PERCENT:
    {
        stk.top().content.number/=100;
        return RET_CORRECT;
    }
    case Symbol::FACTORIAL:
    {
        int temp=stk.top().content.number;
        if(temp>170||temp<-170)
            return RET_INF;          //溢出
        if(isZero(temp-stk.top().content.number))
        {
            stk.top().content.number=factorial(temp);
            return RET_CORRECT;
        }
        return RET_INT;
    }
    case Symbol::POWER:
    {
        if(size<2)return RET_OPERNUMBER;
        if(isComplex)
        {
            Complex index = stk.top().content.CompNumber,base;
            stk.pop();
            base=stk.top().content.CompNumber;
            if(base.isZero())
            {return RET_INF;}
            stk.top().content.CompNumber.cPow(index,isDeg);
            return RET_CORRECT;
        }
        double index=stk.top().content.number,base;
        stk.pop();
        base=stk.top().content.number;
        if(base>=0||fabs(index-int(index))<=1e-10)
            stk.top().content.number=pow(base,index);//调用系统的函数
        else
        {
            int INTEGER=1/index+1e-15;
            if(fabs(INTEGER-1/index)<1e-10&&INTEGER%2==1)
                stk.top().content.number=-pow(-base,index);
            else
                return RET_NEGSQRT;               //负数不能开方
        }
        if(stk.top().content.number>INF)
            return RET_INF;                      //数据溢出
        return RET_CORRECT;
    }
    case Symbol::DIV:
    {
        if(size<2)return RET_OPERNUMBER;
        long long  temp1=stk.top().content.number,temp2;
        if(!isZero(temp1-stk.top().content.number))return RET_INT;
        stk.pop();
        temp2=stk.top().content.number;
        if(!isZero(temp2-stk.top().content.number))return RET_INT;
        if(temp1==0)return RET_ZERO;
        stk.top().content.number=temp2/temp1;
        return RET_CORRECT;
    }
    case Symbol::MOD:
    {
        if(size<2)return RET_OPERNUMBER;
        long long temp1=stk.top().content.number,temp2;
        if(!isZero(temp1-stk.top().content.number))return RET_INT;
        stk.pop();
        temp2=stk.top().content.number;
        if(!isZero(temp2-stk.top().content.number))
            return RET_INT;
        if(temp1==0)return RET_ZERO;
        stk.top().content.number=temp2%temp1;
        return RET_CORRECT;
    }
    case Symbol::NAD:
    {
        if(size<2)return RET_OPERNUMBER;
        long long temp1=stk.top().content.number,temp2;
        if(!isZero(temp1-stk.top().content.number))return RET_INT;
        stk.pop();
        temp2=stk.top().content.number;
        if(!isZero(temp2-stk.top().content.number))return RET_INT;
        if(temp1<0||temp2<0)return RET_NONGINT;
        if(temp1>temp2)return RET_ARGUMENT;
        stk.top().content.number=combinate(temp1,temp2);
        if(stk.top().content.number>INF)
            return RET_INF;                  //数据溢出
        return RET_CORRECT;
    }
    case Symbol::MULTIPLY:
    {
        if(size<2)return RET_OPERNUMBER;
        if(isComplex)
        {
            Complex temp=stk.top().content.CompNumber;
            stk.pop();
            stk.top().content.CompNumber*=temp;
            return RET_CORRECT;
        }
        else
        {
            double temp=stk.top().content.number;
            stk.pop();
            stk.top().content.number*=temp;
            return RET_CORRECT;
        }
    }
    case Symbol::DIVIDE:
    {
        if(size<2)
            return RET_OPERNUMBER;
        if(isComplex)
        {
            Complex temp=stk.top().content.CompNumber;
            if(temp.isZero())
                return RET_ZERO;
            stk.pop();
            stk.top().content.CompNumber/=temp;
            return RET_CORRECT;
        }
        else
        {
            double temp=stk.top().content.number;
            if(isZero(temp))
                return RET_ZERO;
            stk.pop();
            stk.top().content.number/=temp;
            return RET_CORRECT;
        }
    }
    case Symbol::ADD:
    {
        if(size<2)return RET_OPERNUMBER;
        if(isComplex)
        {
            Complex temp=stk.top().content.CompNumber;
            stk.pop();
            stk.top().content.CompNumber+=temp;
            return RET_CORRECT;
        }
        else
        {
            double temp=stk.top().content.number;
            stk.pop();
            stk.top().content.number+=temp;
            return RET_CORRECT;
        }
    }
    case Symbol::SUBSTRACT:
    {
        if(size<2)return RET_OPERNUMBER;
        if(isComplex)
        {
            Complex temp=stk.top().content.CompNumber;
            stk.pop();
            stk.top().content.CompNumber-=temp;
            return RET_CORRECT;
        }
        else
        {
            double temp=stk.top().content.number;
            stk.pop();
            stk.top().content.number-=temp;
            return RET_CORRECT;
        }
    }
    default :            //Symbol::STACKEND
        return RET_CORRECT;
    }
}
int CCalculator::DoCalcFun(QStack<Symbol>&stk,Symbol &sym )
{
    int size=stk.size();
    if(size<1)return RET_FUNNUMBER;
    switch (sym.content.funType)
    {
    case Symbol::ABS:
    {
        if(isComplex)
        {
            stk.top().content.CompNumber.cAbs();
        }
        else
        {
            stk.top().content.number=fabs(stk.top().content.number);
        }
        return RET_CORRECT;
    }
    case Symbol::ACOS:
    {
        double x=stk.top().content.number;
        if(fabs(x)>1)
            return RET_ARGUMENT;
        stk.top().content.number=acos(x);
        if(isDeg)
            stk.top().content.number*=(180/$pi);
        return RET_CORRECT;
    }
    case Symbol::ACOSH:
    {
        double x=stk.top().content.number;
        if(x<1)
            return RET_ARGUMENT;
        stk.top().content.number=log(x+sqrt(x*x-1));
        return RET_CORRECT;
    }
    case Symbol::ACOT:
    {
        double x=stk.top().content.number;
        if(x>=0)
            stk.top().content.number=$pi/2-atan(x);
        else
        {
            x=-x;
            stk.top().content.number=-$pi/2+atan(x);
        }
        if(isDeg)
            stk.top().content.number*=(180/$pi);
        return RET_CORRECT;
    }
    case Symbol::ACOTH:
    {
        double x=stk.top().content.number;
        if(fabs(x)<=1)
            return RET_ARGUMENT;
        stk.top().content.number=0.5*log((1+x)/(x-1));
        return RET_CORRECT;
    }
    case Symbol::ASIN:
    {
        double x=stk.top().content.number;
        if(fabs(x)>1)
            return RET_ARGUMENT;
        stk.top().content.number=asin(x);
        if(isDeg)
            stk.top().content.number*=(180/$pi);
        return RET_CORRECT;
    }
    case Symbol::ASINH:
    {
        double x=stk.top().content.number;
        stk.top().content.number=log(x+sqrt(x*x+1));
        return RET_CORRECT;
    }
    case Symbol::ATAN:
    {
        double x=stk.top().content.number;
        stk.top().content.number=atan(x);
        if(isDeg)
            stk.top().content.number*=(180/$pi);
        return RET_CORRECT;
    }
    case Symbol::ATANH:
    {
        double x=stk.top().content.number;
        if(fabs(x)>=1)
            return RET_ARGUMENT;
        stk.top().content.number=0.5*log((1+x)/(1-x));
        return RET_CORRECT;
    }
    case Symbol::CONJ:
    {
        if(isComplex)
        {
            stk.top().content.CompNumber.conj();
            return RET_CORRECT;
        }
        else
        {
            return RET_USEINCOMP;
        }
    }
    case Symbol::COS:
    {
        double x=stk.top().content.number;
        if(isDeg)
            x*=($pi/180);
        stk.top().content.number=cos(x);
        return RET_CORRECT;
    }
    case Symbol::COSH:
    {
        double x=stk.top().content.number;
        stk.top().content.number=cosh(x);
        return RET_CORRECT;
    }
    case Symbol::COT:
    {
        double x=stk.top().content.number;
        if(isDeg)
            x*=($pi/180);
        if(isZero(tan(x)))
            return RET_ARGUMENT;
        stk.top().content.number=1/tan(x);
        return RET_CORRECT;
    }
    case Symbol::COTH:
    {
        double x=stk.top().content.number;
        if(isZero(x))
            return RET_ARGUMENT;
        stk.top().content.number=cosh(x)/sinh(x);
        return RET_CORRECT;
    }
    case Symbol::CSC:
    {
        double x=stk.top().content.number;
        if(isDeg)
            x*=($pi/180);
        if(isZero(sin(x)))
            return RET_ARGUMENT;
        stk.top().content.number=1/sin(x);
        return RET_CORRECT;
    }
    case Symbol::CUR:
    {
        double x=stk.top().content.number;
        if(x<0)
        {x=-x;stk.top().content.number=-pow(x,1/3.0);}
        else
        {stk.top().content.number=pow(x,1/3.0);}
        return RET_CORRECT;
    }
    case Symbol::EXP:
    {
        stk.top().content.number=exp(stk.top().content.number);
        if(stk.top().content.number>INF)
            return RET_INF;
        return RET_CORRECT;
    }
    case Symbol::GCD:
    {
        if(stk.top().content.opType!=Symbol::COMMA)
        {return RET_FUNNUMBER;}
        stk.pop();
        long long  temp1=stk.top().content.number,temp2;
        if(!isZero(temp1-stk.top().content.number))
            return RET_GCDLCM;
        stk.pop();
        temp2=stk.top().content.number;
        if(!isZero(temp2-stk.top().content.number))
            return RET_GCDLCM;
        if(temp1==0||temp2==0)
            return RET_ARGUMENT;
        stk.top().content.number=gcd(temp2,temp1);
        return RET_CORRECT;
    }
    case Symbol::LCM:
    {
        if(stk.top().content.opType!=Symbol::COMMA)
        {return RET_FUNNUMBER;}
        stk.pop();
        long long  temp1=stk.top().content.number,temp2;
        if(!isZero(temp1-stk.top().content.number))
            return RET_GCDLCM;
        stk.pop();
        temp2=stk.top().content.number;
        if(!isZero(temp2-stk.top().content.number))
            return RET_GCDLCM;
        if(temp1==0||temp2==0)
            return RET_ARGUMENT;
        if(1.0*temp1*temp2>9.2e18)
            return RET_INF;
        stk.top().content.number=lcm(temp2,temp1);
        return RET_CORRECT;
    }
    case Symbol::LG:
    {
        if(stk.top().content.number<=DBL_EPS)
            return RET_ARGUMENT;
        stk.top().content.number=log10(stk.top().content.number);
        return RET_CORRECT;
    }
    case Symbol::LN:
    {
        if(stk.top().content.number<=DBL_EPS)
            return RET_ARGUMENT;
        stk.top().content.number=log(stk.top().content.number);
        return RET_CORRECT;
    }
    case Symbol::LOG:
    {
        if(stk.top().content.opType!=Symbol::COMMA)
        {return RET_FUNNUMBER;}
        stk.pop();
        double y=stk.top().content.number,x;
        if(y<=0)
            return RET_ARGUMENT;
        stk.pop();
        x=stk.top().content.number;
        if(x<=0||x==1)
            return RET_ARGUMENT;
        stk.top().content.number=log(y)/log(x);
        return RET_CORRECT;
    }
    case Symbol::POW:
    {
        if(stk.top().content.opType!=Symbol::COMMA)
        {return RET_FUNNUMBER;}
        else
        {
            stk.pop();
            double y=stk.top().content.number,x;
            stk.pop();
            x=stk.top().content.number;
            if(x>=0||fabs(y-int(y))<=1e-10)
                stk.top().content.number=pow(x,y);//调用系统的函数
            else
            {
                int INTEGER=1/y+1e-10;
                if(fabs(INTEGER-1/y)<1e-10&&INTEGER%2==1)
                    stk.top().content.number=-pow(-x,y);
                else
                    return RET_NEGSQRT;               //负数不能开方
            }
            if(stk.top().content.number>INF)
                return RET_INF;
            return RET_CORRECT;
        }
    }
    case Symbol::SEC:
    {
        double x=stk.top().content.number;
        if(isDeg)
            x*=($pi/180);
        if(isZero(cos(x)))
            return RET_ARGUMENT;
        stk.top().content.number=1/cos(x);
        return RET_CORRECT;
    }
    case Symbol::SIN:
    {
        double x=stk.top().content.number;
        if(isDeg)
            x*=($pi/180);
        stk.top().content.number=sin(x);
        return RET_CORRECT;
    }
    case Symbol::SINH:
    {
        stk.top().content.number=sinh(stk.top().content.number);
        return RET_CORRECT;
    }
    case Symbol::SQR:
    {
        stk.top().content.number*=stk.top().content.number;
        if(stk.top().content.number>INF)
            return RET_INF;
        return RET_CORRECT;
    }
    case Symbol::SQRT:
    {
        if(stk.top().content.number<0)
            return RET_ARGUMENT;
        stk.top().content.number=sqrt(stk.top().content.number);
        return RET_CORRECT;
    }
    case Symbol::TAN:
    {
        double x=stk.top().content.number;
        if(isDeg)
            x*=($pi/180);
        stk.top().content.number=tan(x);
        return RET_CORRECT;
    }
    case Symbol::TANH:
    {
        stk.top().content.number=tanh(stk.top().content.number);
        return RET_CORRECT;
    }
    default:
        return RET_CORRECT;
    }
}
void CCalculator::Fraction(double dl, QString &result)
{
    if(qAbs(dl)<=1e-19)
    {result="0";return ;}
    else if(qAbs(dl)<1e14)
    {
        double eps=1e-10;
        double dl2=1/dl;
        if(qAbs(dl-qlonglong(dl))<eps)
        {result=QString("%1").arg(qlonglong(dl));return;}
        if(qAbs(dl2-qlonglong(dl2))<eps&&qAbs(dl)<1)
        {
            if(dl2<0)
                result=QString("-1/%1").arg(qlonglong(-dl2));
            else
                result=QString("1/%1").arg(qlonglong(dl2));
            return ;
        }
        qlonglong numerator=1,denominator=1;
        qlonglong dInteger=qlonglong(dl);
        double dFraction,dDecimal=dl-dInteger;
        int count=0;
        bool work=false,isNegative=false;
        if(dDecimal<0||dInteger<0)
        {
            isNegative=true;
            dDecimal=qAbs(dDecimal);
            dInteger=qAbs(dInteger);
        }
        QString str;
        count=str.setNum(dInteger).length();
        str.setNum(dDecimal,'f',15-count);
        dDecimal=str.toDouble();
        count=0;
        while(count<1e5)
        {
            dFraction=1.0*numerator/denominator;
            if(qAbs(dFraction-dDecimal)<=eps)
            {work=true;break;}
            if(dFraction<dDecimal)
            {numerator+=1;}
            else
            {denominator+=1;}
            count++;
        }
        if(work==false)
        {
            count=0;
            while(qAbs(dDecimal-qlonglong(dDecimal))>eps&&count<14)
            {
                dDecimal*=10;
                count++;
            }
            numerator=qlonglong(dDecimal);
            denominator=qPow(10,count);
            qlonglong qll=gcd(numerator,denominator);
            numerator/=qll;
            denominator/=qll;
        }
        numerator+=dInteger*denominator;
        if(isNegative==true)
            numerator=-numerator;
        if(denominator==1)
            result=QString("%1").arg(numerator);
        else
            result=QString("%1/%2").arg(numerator).arg(denominator);
        return;
    }
    else if(qAbs(dl)<9e18)
    {
        result=QString("%1").arg(qlonglong(dl));
        return ;
    }
    return ;
}

double factorial(int n)
{
    double res=1;
    if(n<0){res=-1;n=-n;}
    if(n==0)
        return 1;
    for(int i=1;i<=n;++i)
    {res*=i;}
    return res;
}
double combinate(int k,int n)
{
    double sum=0;
    double eps=1e-15;
    if(2*k>n)
        return combinate(n-k,n);
    else
    {
        for(int i=n;i>n-k;i--)
        {sum+=log(double(i));}
        for(int i=k;i>0;i--)
        {sum-=log(double(i));}
        sum=exp(sum+eps);
        modf(sum,&sum);
        return sum;
    }
}
qlonglong gcd(qlonglong a,qlonglong b)
{
    if(a%b==0)return b;
    else return gcd(b,a%b);
}
qlonglong lcm(qlonglong a, qlonglong b)
{
    return (a*b)/gcd(a,b);
}
QString changeSystem(QString num, int new_System, int old_System)
{
    QString result;
    int digital;
    double dl;
    if(old_System==10)
    {
        if(new_System==10)
            return num;
        dl=num.toDouble();
        bool isNegative=false;
        if(num[0]=='-')
        {
            num.remove(0,1);
            dl=-dl;
            isNegative=true;
        }
        switch(new_System)
        {
        case 2:
        {
            dl=dl*pow(2,20)+0.5;
            result.setNum(qlonglong(dl),2);
            digital=result.length()-20;
            if(digital>0)
                result.insert(digital,'.');
            else
            {
                digital=-digital;
                QString temp="0.";
                while(digital--)
                {temp+='0';}
                result.prepend(temp);
            }
            QRegExp regExp("(\\.)?([0]+$)");
            result.remove(regExp);
            if(isNegative)
                result.prepend('-');
            return result;
        }
        case 8:
        {
            dl=dl*pow(8,6)+0.5;
            result.setNum(qlonglong(dl),8);
            digital=result.length()-6;
            if(digital>0)
                result.insert(digital,'.');
            else
            {
                digital=-digital;
                QString temp="0.";
                while(digital--)
                {temp+='0';}
                result.prepend(temp);
            }
            QRegExp regExp("(\\.)?([0]+$)");
            result.remove(regExp);
            if(isNegative)
                result.prepend('-');
            return result;
        }
        case 16:
        {
            dl=dl*pow(16,5)+0.5;
            result.setNum(qlonglong(dl),16);
            digital=result.length()-5;
            if(digital>0)
                result.insert(digital,'.');
            else
            {
                digital=-digital;
                QString temp="0.";
                while(digital--)
                {temp+='0';}
                result.prepend(temp);
            }
            result=result.toUpper();
            QRegExp regExp("(\\.)?([0]+$)");;
            result.remove(regExp);
            if(isNegative)
                result.prepend('-');
            return result;
        }
        default:
            return num;
        }
    }
    else if(new_System==10)
    {
        double dl=0;
        int length=num.length();
        if(old_System==2||old_System==8||old_System==16)
        {
            int pointPosition=num.indexOf('.');
            bool isNegative=false;
            if(num[0]=='-')
            {
                num.remove(0,1);
                isNegative=true;
            }
            if(pointPosition==-1)
            {
                for(int i=0;i<length;i++)
                {
                    if(num[length-i-1]!='0')
                        dl=dl+toNumber(num[length-i-1])*pow(old_System,i*1.0);
                }
            }
            else
            {
                for(int i=0;i<pointPosition;i++)
                {
                    if(num[pointPosition-i-1]!='0')
                        dl=dl+toNumber(num[pointPosition-i-1])*pow(old_System,i);
                }
                for(int i=pointPosition+1;i<length;i++)
                {
                    if(num[i]!='0')
                    {dl=dl+toNumber(num[i])/pow(old_System,i-pointPosition);}
                }
            }
            result.setNum(dl,'g',16);
            if(isNegative)
                result.prepend('-');
            return result;
        }
        else
            return num;
    }
    else
    {
        result=changeSystem(num,10,old_System);
        result=changeSystem(result,new_System,10);
        return result;
    }
}
bool isErrorNumber(QString str, int system)
{
    if(system==16)
        return false;
    int len=str.length();
    switch(system)
    {
    case 2:
    {
        for(int i=0;i<len;i++)
        {
            if(str[i]=='0'||str[i]=='1'||str[i]=='.')
                continue;
            else
                return true;
        }
        return false;
    }
    case 8:
    {
        for(int i=0;i<len;i++)
        {
            if(str[i]!='8'&&str[i]!='9')
                continue;
            else
                return true;
        }
        return false;
    }
    default:
        return false;
    }
}

Complex getComplex(QString str)
{
    if(str.contains('i')){
        int index01 = str.lastIndexOf('+');
        int index02 = str.lastIndexOf('-');
        if(index01>0){
            str.insert(index01,' ');
            str.insert(index01+2,' ');
        }
        if(index01<=0&&index02>0)
        {
            str.insert(index02,' ');
            str.insert(index02+2,' ');
        }
    }
    Complex temp;
    temp.setComplex(str);
    return temp;
}
