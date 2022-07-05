#include "connect5.h"

//ReallyLong

ReallyLong::ReallyLong(std::vector<short> rli, bool n) //(digit order opposite from standard) one's place is 0th element of vector
    : reallyLongInt{rli}, neg{n}
{
}
ReallyLong::ReallyLong(long long num)
{
    //int length = LongLength(num);
    long long temp;
    neg = false;
    if (num < 0)
    {
        neg = true;
        num *= -1;
    }
    while (num >= 10)
    {
        temp = num;
        num /= 10;
        reallyLongInt.push_back(temp - num * 10);
    }
    reallyLongInt.push_back(num);
}


int ReallyLong::Length() const //const here means *this is const
{
    return reallyLongInt.size();
}
short ReallyLong::operator[](int ind) const//one's place is last
{
    return reallyLongInt[this->Length()-ind-1];
}
void ReallyLong::Display() const //(standard digit order) display ones place last
{
    if (neg == true)
        std::cout << '-';
    for (int i = 0; i < reallyLongInt.size(); i++)
        std::cout << (*this)[i];// << ' ';
    //std::cout << std::endl;
}
ReallyLong &ReallyLong::Negation()
{
    neg = !neg;
    return *this;
}
ReallyLong ReallyLong::Abs() const
{
    ReallyLong absRL;
    const std::vector<short>* rliP = &this->reallyLongInt;//pointer instead of copy?
    absRL.reallyLongInt = *rliP;
    absRL.neg = false;
    return absRL;
}
bool operator==(const ReallyLong rl1, const ReallyLong rl2)
{
    return (rl1.reallyLongInt == rl2.reallyLongInt) && (rl1.neg == rl2.neg);
}
bool operator!=(const ReallyLong rl1, const ReallyLong rl2)
{
    return !(rl1 == rl2);
}
bool operator<(const ReallyLong rl1, const ReallyLong rl2)
{
    if(rl1.neg != rl2.neg)
        return rl1.neg;
    else if (rl1.reallyLongInt.size() != rl2.reallyLongInt.size())
        return (rl1.reallyLongInt.size() > rl2.reallyLongInt.size()) == rl1.neg;//== works as xnor
    else
        for(int d = rl1.reallyLongInt.size(); d > 0; d--)
        {
            if(rl1.reallyLongInt[d-1] != rl2.reallyLongInt[d-1])
                return (rl1.reallyLongInt[d-1] > rl2.reallyLongInt[d-1]) == rl1.neg;
        }
        return false;//rl1=rl2   
}
bool operator>(const ReallyLong rl1, const ReallyLong rl2)
{
    return rl2<rl1;
}
ReallyLong &ReallyLong::operator+=(const ReallyLong &add)//a + b
{
    if(!this->neg && add.neg)//a is + and b is -
    {
        *this = *this - add;
        return *this;
    }
    else if(this->neg && !add.neg)//a is - and b is +
    {
        *this = add - *this;
        return *this;
    }
    else if(this->neg && add.neg)//a is - and b is -
    {
        *this = (this->Negation() - add).Negation();
        return *this;
    }
    else
    {
        for (int i = 0; i < add.Length(); i++)
        {
            if (i < this->Length())
                reallyLongInt[i] += add.reallyLongInt[i];
            else
                reallyLongInt.push_back(add.reallyLongInt[i]);
        }
        for (int i = 0; i < this->Length(); i++)
        {
            if (reallyLongInt[i] > 9)
            {
                reallyLongInt[i] -= 10;
                if (i + 1 == this->Length())
                    reallyLongInt.push_back(1);
                else
                    reallyLongInt[i + 1] += 1;
            }
        }
    /*if (add.Length() > this->Length())
        reallyLongInt.insert(reallyLongInt.end(), add.Length() - this->Length(), 0);
    for(int i = 0; i < this->Length(); i++)
    {
        if ((i + 1) > add.Length())
            break;
        reallyLongInt[i] += add.reallyLongInt[i];
        if(reallyLongInt[i] > 9)
        {
            reallyLongInt[i] -= 10;
            if((i + 1) == this->Length())
                reallyLongInt.push_back(1);
            else
                reallyLongInt[i + 1]++;
        }        
    }
    */
    return *this;
    }
}
ReallyLong operator+(ReallyLong aug, const ReallyLong &add)
{
    aug += add;
    return aug;
}
ReallyLong &ReallyLong::operator-=(const ReallyLong &subtrah)//a-=b
{ //using nines' complement
    ReallyLong temp{};
    if(*this != subtrah)
    {
        if(!this->neg && subtrah.neg)//a is + and b is -
        {
            temp = subtrah;
            *this = *this + temp.Negation();
            return *this;
        }
        else if(this->neg && !subtrah.neg)//a is - and b is +
        {
            *this = (this->Negation() + subtrah).Negation();
            return *this;
        }
        else if (this->neg && subtrah.neg)//a is - and b is -
        {
            temp = subtrah;
            *this = temp.Negation() - this->Negation();
            return *this;
        }
        else
        {
            temp = ninesComp(subtrah);
            for(int i = temp.Length(); i < this->Length(); i++)
                temp.reallyLongInt.push_back(9);
            temp += *this;
            if(temp.Length() > subtrah.Length() && temp.reallyLongInt.back() == 1)
            {
                temp.reallyLongInt.pop_back();
                temp += ReallyLong(1);
            }
            else
            {
                temp = ninesComp(temp);
                temp.neg = true;
            }
        }
    }
    while (temp.reallyLongInt.back() == 0 && temp.reallyLongInt.size() > 1)
        temp.reallyLongInt.pop_back();
    *this = temp;
    return *this;
}
ReallyLong operator-(ReallyLong minu, const ReallyLong &subtrah)
{
    minu -= subtrah;
    return minu;
}
ReallyLong &ReallyLong::operator*=(const ReallyLong &cand)
{
    ReallyLong total{}, sub{}; //not parentheses b/c ambiguous to compiler
    int temp;
    bool negs = this->neg != cand.neg;
    for (int i = 0; i < this->Length(); i++)
    {
        for (int j = 0; j < cand.Length(); j++)
        {
            sub.reallyLongInt.clear();
            for (int zeros = i + j; zeros > 0; zeros--)
                sub.reallyLongInt.push_back(0);
            temp = reallyLongInt[i] * cand.reallyLongInt[j];
            sub.reallyLongInt.push_back(temp % 10);
            if (temp > 9)
                sub.reallyLongInt.push_back(temp / 10);
            total += sub;
        }
    }
    /*for(int i = 0; i < this->Length(); i++)//alternative that with += calls of a instead of a*b
    {
        sub.reallyLongInt.clear();
        for(int zeros = i+1; zeros > 0; zeros--)
                sub.reallyLongInt.push_back(0);
        for(int j = 0; j < cand.Length(); j++)
        {
            temp = reallyLongInt[i] * cand.reallyLongInt[j];
            sub.reallyLongInt[i+j]+=(temp % 10);
            if(temp > 9)
                sub.reallyLongInt.push_back(temp / 10);
            else if(j+1!=cand.Length())
                sub.reallyLongInt.push_back(0);
        }
        for(int j = 0; j < cand.Length(); j++)
        {
            if(sub.reallyLongInt[i+j]>9)
            {
                sub.reallyLongInt[i+j]-=10;
                if(i+j+1<sub.Length())
                    sub.reallyLongInt[i+j+1]++;
                else
                    sub.reallyLongInt.push_back(1);
            }
        }
        total += sub;
    }*/
    *this = total;
    this->neg = negs;
    return *this;
}
ReallyLong operator*(ReallyLong er, const ReallyLong &cand)
{
    er *= cand;
    return er;
}
ReallyLong &ReallyLong::operator/=(const ReallyLong &sor)//16 / 1 = 61??
{
    bool negs = !(this->neg == sor.neg);
    ReallyLong sorabs = sor.Abs();
    if(sor == ReallyLong(0))
    {
        std::cerr << "Undefined division by zero";
        *this = ReallyLong(std::vector<short>(1,0), true);//return reallylong of value -0
        return *this;
    }
    else if(this->Abs() < sorabs)//then, this / sor = 0 remainder this
    {    
        *this = ReallyLong(0);
        return *this;
    }
    else
    {
        ReallyLong quotient{}, rem{}, mult{}, nextmult{};//sets all to 0! //quotient is reverse order
        quotient.reallyLongInt.pop_back();
        rem.reallyLongInt.pop_back();
        mult.reallyLongInt.pop_back();
        nextmult.reallyLongInt.pop_back();//work around...
        int place = this->Length();
        do//do first, so rem is not empty on check
            rem.reallyLongInt.insert(rem.reallyLongInt.begin(),reallyLongInt[place---1]); //index of place - 1, then place-=1 
        //vector inserts at front inefficient, future improvement opportunity
        while(rem < sorabs);
        while(place >= 0)
        {
            quotient.reallyLongInt.push_back(0);//start digit at zero
            nextmult = sorabs;//first multiple of sor is sor
            while(nextmult < rem || nextmult == rem)
            {
                mult = nextmult;
                nextmult += sorabs;
                quotient.reallyLongInt.back()++;
            }
            rem -= mult;
            if(place > 0)
            {
                if(rem == ReallyLong(0))
                    rem.reallyLongInt.pop_back();
                rem.reallyLongInt.push_back(reallyLongInt[place---1]);
                mult = ReallyLong(0);
            }
            else
                place--;
        }
        this->reallyLongInt.resize(quotient.Length());
        for(int i = 0; i < quotient.Length(); i++)
            this->reallyLongInt[i] = quotient[i];//reverses quotient into this
        while (this->reallyLongInt.back() == 0 && this->reallyLongInt.size() > 1)
            this->reallyLongInt.pop_back();
        this->neg = negs;
        return *this;
        
    }

    
}
ReallyLong operator/(ReallyLong dend, const ReallyLong &sor)
{
    dend /= sor;
    return dend;
}
/*
ReallyLong &ReallyLong::operator%=(const ReallyLong &sor)
{
    if(*this < sor)
        return *this;
    else
    {
        
    }

}
ReallyLong operator%(ReallyLong dend, const ReallyLong &sor)
{
    dend %= sor;
    return dend;
}
//*/

//Rational: container for rational with ReallyLong numer & denom

Rational::Rational(ReallyLong n, ReallyLong d)
    : numer{n}, denom{d} {}

void Rational::Reduce()
{
    ReallyLong a = numer;
    ReallyLong b = denom;
    a.neg = false;
    b.neg = false;
    if(numer != ReallyLong{})
    {
        while (a != b)//euclidean algorithm
        {
            if(a > b)
                a -= b;
            else
                b -= a;     
        }//a (& b) is now gcd(numer, denom)
        numer /= a;
        denom /= a;
        if(denom.neg == true) //double neg is pos, move single bottom neg to top
        {
            denom.neg = false;
            if(numer.neg == true)
                numer.neg = false;
            else
                numer.neg = true;
        }
    }
    else
        denom = ReallyLong(1);
}
void Rational::Display()
{
    numer.Display();
    std::cout << " / ";
    denom.Display();
    std::cout << std::endl;
    /*
    numer.Display();
    for(int i=0;i<std::max(numer.Length(),denom.Length());i++)
        std::cout<<'-';
    std::cout<<std::endl;
    denom.Display();
    //*/
}
Rational &Rational::Negation()//useful function??
{
    numer.neg = !numer.neg;
    return *this;
}
bool operator==(const Rational r1, const Rational r2)
{
    return (r1.numer == r2.numer) && (r1.denom == r2.denom);
}
Rational &Rational::operator+=(const Rational &addend)
{
    numer *= addend.denom;
    numer += (addend.numer * denom);
    denom *= addend.denom;
    this->Reduce();
    return *this;
}
Rational operator+(Rational augend, const Rational &addend)
{
    augend += addend;
    return augend;
}
Rational &Rational::operator-=(const Rational &subtrah)
{
    numer *= subtrah.denom;
    numer -= (subtrah.numer * denom);
    denom *= subtrah.denom;
    this->Reduce();
    return *this;
}
Rational operator-(Rational minu, const Rational &subtrah)
{
    minu -= subtrah;
    return minu;
}
Rational &Rational::operator*=(const Rational &cand)
{
    numer *= cand.numer;
    denom *= cand.denom;
    this->Reduce();//divide by gcd of num,den
    return *this;
}
Rational operator*(Rational er, const Rational &cand)
{
    er *= cand;
    return er;
}
Rational &Rational::operator/=(const Rational &sor)
{
    numer *= sor.denom;
    denom *= sor.numer;
    this->Reduce();
    return *this;
}
Rational operator/(Rational dend, const Rational &sor)
{
    dend /= sor;
    return dend;
}
/*
Rational &Rational::operator%=(const Rational &sor)
{
}
Rational operator%(Rational dend, const Rational &sor)
{
}
//*/

/*
Rational::Rational(long long n, long long d)//default values only in declaration
        :numer{ n }, denom{ d } {}
    
void Rational::Reduce()
{
    long long gcf = Euclidean(numer, denom);
    numer /= gcf;
    denom /= gcf;
    if (denom < 0)
    {
        numer *= -1;
        denom *= -1;
    }
}
void Rational::Display()
{
    std::cout << numer << " / " << denom << std::endl;
}

Rational& Rational::operator+=(const Rational& addend)
{
    numer *= addend.denom;
    numer += addend.numer * denom;
    denom *= addend.denom;
    this->Reduce();
    return *this;
}

Rational operator+(Rational augend, const Rational& addend)
{
    augend+=addend;
    return augend;
}

Rational &Rational::operator*=(const Rational &cand)
{
    numer *= cand.numer;
    denom *= cand.denom;
    this->Reduce();
    return *this;
}

Rational operator*(Rational er, const Rational &cand)
{
    er *= cand;
    return er;
}
*/
