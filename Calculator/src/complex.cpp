//有关复数运算
#include "complex.h"
#include <qmath.h>

//有关复数运算
Complex& Complex:: operator = (Complex c)
{
    this->Real=c.Real;
    this->Imag=c.Imag;
    return *this;
}
Complex operator + ( const Complex &  c1, const  Complex & c2 )
{
    double r = c1.Real + c2.Real ;
    double i = c1.Imag+c2.Imag ;
    return Complex ( r,  i ) ;
}
Complex operator - ( const Complex & c1, const Complex & c2 )
{
    double r = c1.Real - c2.Real ;
    double i = c1.Imag - c2.Imag ;
    return Complex ( r,  i ) ;
}
Complex operator* ( const Complex & c1, const Complex & c2 )
{
    double r=c1.Real*c2.Real-c1.Imag*c2.Imag;
    double i=c1.Real*c2.Imag+c1.Imag*c2.Real;
    return Complex(r,i);
}
Complex operator/ ( const Complex & c1, const Complex & c2 )
{
    double r=(c1.Real*c2.Real+c1.Imag*c2.Imag)/(c2.Real*c2.Real+c2.Imag*c2.Imag);
    double i= (c1.Imag*c2.Real-c1.Real*c2.Imag)/(c2.Real*c2.Real+c2.Imag*c2.Imag);
    return Complex(r,i);
}
void Complex::operator +=(const Complex &c)
{
    this->Real+=c.Real;
    this->Imag+=c.Imag;
    return ;
}
void Complex::operator -=(const Complex &c)
{
    this->Real-=c.Real;
    this->Imag-=c.Imag;
    return ;
}
void Complex::operator *=(const Complex &c)
{
    *this=(*this)*c;
    return;
}
void Complex::operator /=(const Complex &c)
{
    *this=(*this)/c;
    return;
}
bool Complex::isZero()
{
    return (qAbs(Real)<=DBL_EPS&&qAbs(Imag)<=DBL_EPS);
}
void Complex::cAbs()
{
    this->Real=qSqrt(Real*Real+Imag*Imag);
    this->Imag=0;
    return;
}
double Complex::cfabs()
{
    return qSqrt(Real*Real+Imag*Imag);
}
void Complex::conj()
{
    Imag=-Imag;
    return ;
}
void Complex::cPow(Complex Index, bool isDeg)
{
    double eps=1e-25;
    double angle;
    if(isDeg&&qAbs(this->getReal()-$e)<=DBL_EPS)
        Index=Index*($pi/180);
    if(fabs(Real)>eps)
        angle=atan(Imag/Real);
    else
        angle=(Imag>0)?$pi/2:-$pi/2;
    if(Real<0&&Imag>=0)
        angle+=$pi;
    if(Real<0&&Imag<0)
        angle-=$pi;
    double mo=log(sqrt(Real*Real+Imag*Imag)/exp(Index.Imag*angle));
    double mod=exp(mo*Index.Real-angle*Index.Imag);
    angle=angle*Index.Real+Index.Imag*mo;
    if(angle<0)
        while(angle<=-$pi)
            angle+=2*$pi;
    else
        while(angle>$pi)
            angle-=2*$pi;

    Real=mod*cos(angle);
    Imag=mod*sin(angle);
    return ;
}
double Complex::getReal()
{
    return Real;
}
double Complex::getImag()
{
    return Imag;
}
QString Complex::toExponential(bool isDeg,int precision)
{
    QString result;
    double r=qSqrt(Real*Real+Imag*Imag);
    if(qAbs(r)<=DBL_EPS)
    {
        bool isNegative=false;
        if(Imag<0)
            Imag=-Imag,isNegative=true;
        result.setNum(Imag,'g',precision);
        result+="$e^(";
        if(isNegative)
            result+='-';
        if(isDeg)
            result+="90i)";
        else
            result+="i*$pi/2)";
        return result;
    }
    if(qAbs(Imag)<=DBL_EPS)
    {
        bool isNegative=false;
        if(Real<0)
            Real=-Real,isNegative=true;
        result.setNum(Real,'g',precision);
        if(isNegative)
        {

            if(isDeg)
                result+="$e^(180i)";
            else
                result+="$e^(i*$pi)";
        }
        else
        {
            result+="$e^0";
        }
        return result;
    }
    double angle=atan(Imag/Real);
    result.setNum(r,'g',precision);
    if(qAbs(angle)<=DBL_EPS)
        result+=QString("$e^0");
    else if(isDeg)
    {
        angle=angle*180/$pi;
        if(Imag>0&&Real<0)
            angle+=180;
        if(Imag<0&&Real<0)
            angle-=180;
        result+=QString("$e^(%1*i)").arg(angle);
    }
    else
    {
        angle/=$pi;
        if(Imag>0&&Real<0)
            angle+=$pi;
        if(Imag<0&&Real<0)
            angle-=$pi;
        result+=QString("$e^(%1i*$pi)").arg(angle);
    }
    return result;
}
QString Complex::toString(int precision,double eps)
{
    QString result;
    if(qAbs(Real)<=eps)
    {
        if(qAbs(Imag)<=eps)
            result = "0";
        else if(Imag<0)
        {
            result="- ";
            if(qAbs(Imag+1)>=eps)
                result+=QString().setNum(-Imag,'g',precision);
            result+='i';
        }
        else
        {
            if(qAbs(Imag-1)>=eps)
                result.setNum(Imag,'g',precision);
            result+='i';
        }
    }
    else if(qAbs(Imag)<=eps)
    {
        result.setNum(Real,'g',precision);
    }
    else
    {
        if(Imag<0)
        {
            result.setNum(Real,'g',precision);
            result+=" - ";
            if(qAbs(Imag+1)>=eps)
                result+=QString().setNum(-Imag,'g',precision);
            result+='i';
        }
        else
        {
            result.setNum(Real,'g',precision);
            result+=" + ";
            if(qAbs(Imag-1)>=eps)
                result+=QString().setNum(Imag,'g',precision);
            result+='i';
        }
    }
    return result;
}
void Complex::setComplex(QString str)
{
    double real,imag;
    if(str=="0"){
       *this = 0;
        return ;
    }
    if(!str.contains('i'))
    {
        real=str.toDouble();
        imag=0;
    }
    else if(!str.contains(' '))
    {
        QString lef=str.left(str.length()-1);
        if(lef=="-")
            imag=-1;
        else if(lef=="")
            imag=1;
        else
            imag=lef.toDouble();
        real=0;
    }
    else
    {
        int index=str.indexOf(' ');
        real=str.left(index).toDouble();
        str.remove(0,index);
        str.remove(' ');
        if(str[0]=='+')
            str.remove('+');
        QString lef=str.left(str.length()-1);
        if(lef=="-")
            imag=-1;
        else if(lef=="")
            imag=1;
        else
            imag=lef.toDouble();

    }
    *this = Complex(real,imag);
}
