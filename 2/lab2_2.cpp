#include <iostream>
using namespace std;

#define MAX_POWER 30

class Polynomial
{
public:
    double k[MAX_POWER];
    int power;
    Polynomial()
    {
        power = 0;
        for (int i = 0; i < MAX_POWER; i++)
            k[i] = 0;
    }
    Polynomial(double _k)
    {
        power = 1;
        for (int i = 0; i < MAX_POWER; i++)
            k[i] = 0;
        k[0] = _k;
        k[1] = 1;
    }
    Polynomial(int p, double* _k)
    {
        power = p;
        for (int i = 0; i < MAX_POWER; i++)
            k[i] = 0;
        for (int i = 0; i <= p; i++)
            k[i] = _k[i];
    }
    void set1()
    {
        power = 0;
        k[0] = 1;
    }
    void set1ci(double _x)
    {
        power = 1;
        k[1] = 1;
        k[0] = _x;
    }
    void print()
    {
        int i;
        for (i = power; i > 0; i--)
        {
            cout << k[i] << "x^" << i << " + ";
        }
        cout << k[0] << '\n';
    }
    void add(Polynomial* p)
    {
        if (p->power > this->power)
            this->power = p->power;
        for (int i = 0; i <= this->power; i++)
            this->k[i] += p->k[i];
    }
    void multiply(Polynomial* p)
    {
        int _p = this->power + p->power;
        double _k[_p+1];
        for (int i = 0; i <= _p; i++)
            _k[i] = 0;
        for (int i = 0; i <= p->power; i++)
            for (int j = 0; j <= this->power; j++)
                _k[i+j] += p->k[i]*this->k[j];
        this->power = _p;
        for (int i = 0; i <= _p; i++)
            this->k[i] = _k[i];
    }
    void multiply_number(double a)
    {
        for (int i = 0; i <= power; i++)
            k[i] *= a;
    }
    double Power(double x, int i)
    {
        double res = 1;
        for (int j = 1; j <= i; j++)
            res *= x;
        return res;
    }
    double value(double x)
    {
        double res = k[0];
        for (int i = 1; i <= power; i++)
        {
            res += k[i] * Power(x, i);
        }
        return res;
    }
    double d1(double x)//yi jie dao shu
    {
        if (power == 0)
            return 0;
        double res = k[1];
        for (int i = 2; i <= power; i++)
            res += k[i] * i * Power(x, i-1);
        return res;
    }
    double d2(double x)//er jie dao shu
    {
        if (power <= 1)
            return 0;
        double res = k[2] * 2;
        for (int i = 3; i <= power; i++)
            res += k[i]*i*(i-1)*Power(x, i-2);
        return res;
    }
};

class Matrix
{
public:
    int n;
    double m[100][100];
    double b[100];
    Matrix(int _n)
    {
        n = _n;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                m[i][j] = 0;
    }
    void setM(double* u, double* lamda)
    {
        int i, j;
        for (i = 1; i <= n; i++)
            m[i][i] = 2;
        for (i = 2; i <= n; i++)
            m[i][i-1] = u[i-1];
        for (i = 1; i < n; i++)
            m[i][i+1] = lamda[i];
    }
    void setB(double* _b)
    {
        for (int i = 1; i <= n; i++)
            b[i] = _b[i];
    }
    double* getSolution()
    {
        double* res = new double[n+1];
        int i, j;
        for (j = 1; j <= n-1; j++)
        {
            for (i = j+1; i <= n; i++)
            {
                double k = m[i][j]/m[j][j];
                b[i] -= b[j]*k;
                m[i][j] = 0;
                for (int z = j+1; z <= n; z++)
                    m[i][z] -= k*m[j][z];
            }
        }
        for (i = n; i >= 1; i--)
        {
            for (j = n; j >= i+1; j--)
                b[i] -= m[i][j]*res[j];
            res[i] = b[i]/m[i][i];
        }
        return res;
    }
};



int main()
{
    double df0 = 1.86548, dfn = -0.046115;
    int n = 18;
    double x[19] = {0.52, 3.1, 8, 17.95, 28.65, 39.62, 50.65, 78, 104.6, 156.6, 208.6, 260.7, 312.5, 364.4, 416.3, 468, 494, 507, 520};
    double y[19] = {5.288, 9.4, 13.84, 20.2, 24.9, 28.44, 31.1, 35, 36.9, 36.6, 34.6, 31, 26.34, 20.9, 14.8, 7.8, 3.7, 1.5, 0.2};
    double h[19], u[19], lamda[19], d[20];

    for (int i = 0; i < n; i++)
        h[i] = x[i+1] - x[i];
    for (int i = 1; i < n; i++)
        u[i] = h[i-1]/(h[i-1]+h[i]);
    u[n] = 1;
    lamda[1] = 1;
    for (int i = 2; i <= n; i++)
        lamda[i] = h[i-1]/(h[i-2]+h[i-1]);
    d[1] = 6.0/h[0]*((y[1]-y[0])/h[0] - df0);
    d[n+1] = 6.0/h[n-1]*(dfn - (y[n] - y[n-1])/h[n-1]);
    for (int i = 2; i <= n; i++)
        d[i] = 6.0*((y[i] - y[i-1])/h[i-1] - (y[i-1]-y[i-2])/h[i-2])/(h[i-2]+h[i-1]);
    Matrix mat(n+1);
    mat.setM(u, lamda);
    mat.setB(d);
    double *M = mat.getSolution();
    for (int i = 0; i <= n; i++)
        M[i] = M[i+1];
    int _j[6] = {0,4,8,13,15,17};
    double _x[6] = {2,30,133,390,470,515};
    Polynomial *tmp1 = new Polynomial(), *tmp2 = new Polynomial();
    for (int i = 0; i < 6; i++)
    {
        int j = _j[i];
        Polynomial S;

        tmp1->set1();
        tmp2->set1ci(-x[j+1]);
        for (int _i = 0; _i < 3; _i++)
            tmp1->multiply(tmp2);
        tmp1->multiply_number(-M[j]/6/h[j]);
        S.add(tmp1);

        tmp2->multiply_number((M[j]*h[j]*h[j]/6-y[j])/h[j]);
        S.add(tmp2);

        tmp1->set1();
        tmp2->set1ci(-x[j]);
        for (int _i = 0; _i < 3; _i++)
            tmp1->multiply(tmp2);
        tmp1->multiply_number(M[j+1]/6/h[j]);
        S.add(tmp1);

        tmp2->multiply_number((-M[j+1]*h[j]*h[j]/6+y[j+1])/h[j]);
        S.add(tmp2);

        cout << "f(" << _x[i] <<") = " << S.value(_x[i]) << '\n';
        cout << "f'(" << _x[i] <<") = " << S.d1(_x[i]) << '\n';
        cout << "f''(" << _x[i] <<") = " << S.d2(_x[i]) << '\n';
    }
    delete tmp1;
    delete tmp2;
    delete[] M;
    return 0;
}
