#include "connect5.h"

int LongLength(long long num)
{
    int len;
    for(len = 1; num >= 10; len++)
        num/=10;
    return len;
}
ReallyLong intExp(int base, int exp)
{
    ReallyLong vBase(base);
    ReallyLong power(1);
    if (exp == 0)
        return power;
    for(int i = 1; i <= exp; i++)
        power *= vBase;
    return power;
}
ReallyLong ninesComp(const ReallyLong &rl)
{
    std::vector<short> rli;
    for (short x : rl.reallyLongInt)
        rli.push_back(9 - x);
    ReallyLong rl9sc(rli);
    return rl9sc;
}
/*
ReallyLong Euclidean(std::vector<short> a, std::vector<short> b)
{
    if(b == std::vector<short>(1,0))
        return a;
    else return Euclidean(b, a % b);
}
//*/

/*
long long intExp(int base, int exp)//integer exponent
{
    long long power = 1;
    for(int i = 1; i <= exp; i++)
        power *= base;
    return power;
}

long long Euclidean(long long a, long long b)//return gcd(a,b)
{
    if(b == 0)//code from wikipedia.org/wiki/Euclidean_algorithm
       return a;
    else
        return Euclidean(b, a % b);
}*/
void RREF(std::vector<std::vector<Rational>> &augMatrix)
{
    for(int pivotRow = 0; pivotRow < augMatrix.size(); pivotRow++)
    {
        Rational pivot = augMatrix[pivotRow][pivotRow];
        if(pivot == Rational(0,1))
            std::cerr << "pivot of zero";
        for(int col = pivotRow; col < augMatrix[pivotRow].size(); col++)
            augMatrix[pivotRow][col] /= pivot;
        for(int row = 0; row < augMatrix.size(); row++)
        {
            if(row == pivotRow)//skip pivotRow
                continue;
            Rational factor = augMatrix[row][pivotRow];
            for(int col = pivotRow; col < augMatrix[row].size(); col++)
                augMatrix[row][col] -= (augMatrix[pivotRow][col] * factor); 
        }
    }
}
std::vector<Rational> LinSysSolve(std::vector<std::vector<ReallyLong>> eqMatrix)
{
    std::vector<Rational> solVector;
    std::vector<std::vector<Rational>> QMatrix(eqMatrix.size(),std::vector<Rational>(eqMatrix.size() + 1, Rational()));
    for(int m = 0; m < eqMatrix.size(); m++)
        for(int n = 0; n < eqMatrix.size() + 1; n++)//might need more parentheses
            QMatrix[m][n].numer = eqMatrix[m][n];//make rational version of eqMatrix
    for (int m = 0; m < QMatrix.size(); m++)
    {
        Rational diag(QMatrix[m][m].numer, QMatrix[m][m].denom);//remember value throughout next step
        for (int n = 0; n < QMatrix.size() + 1; n++)//divide row by its diagonal element's value
        {
            QMatrix[m][n].denom *= diag.numer;
            QMatrix[m][n].numer *= diag.denom;
            QMatrix[m][n].Reduce();//fixed?
        }
        for (int eq = 0; eq < QMatrix.size(); eq++)
        {
            if(eq != m)
            {
                Rational xco(QMatrix[eq][m].numer, QMatrix[eq][m].denom); //remember value throughout next step
                for (int co = 0; co < QMatrix.size() + 1; co++)//row operations
                {
                    QMatrix[eq][co].numer *= (xco.denom * QMatrix[m][co].denom);
                    QMatrix[eq][co].numer -= (xco.numer * QMatrix[m][co].numer * QMatrix[eq][co].denom);
                    QMatrix[eq][co].denom *= (xco.denom * QMatrix[m][co].denom);
                    QMatrix[eq][co].Reduce();
                }
            }
        }
    }
    for (int i = 0; i < QMatrix.size(); i++)
    {
        Rational final = QMatrix[i][QMatrix.size()];
        final.Reduce();
        solVector.push_back(final);
    }
    return solVector;
}