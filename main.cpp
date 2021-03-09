#include <iostream>
#include <cmath>
#include <stdlib.h>

using namespace std;


bool error = false;
double eps, R, a, b;

void main_menu();
void menu1();
void domenu1(double a, double b, double eps);
double f(double x);
double g(double x);
double hord(double a, double b, double eps);
double polovina(double a, double b, double eps);
double itera(double a, double b, double eps);

void main_menu()
{
    int N;
    cout << "MENU" <<endl;
    cout << "(1) Find the root f(x)=sin(x)*(x^2) \n" <<
    "(2) Close \n" << "Your choice: ";
    cin >> N;
    switch (N)
    {
        case 1:
            menu1();
            break;
        case 2:
            exit(0);
    }
    if (N != 1 && N != 2)
    {
        cout << "!Input ERROR. Try again. \n" << endl;
        main_menu();
    }
    main_menu();
}
void menu1()
{
    cout << '\n' << "Find the root f(x)=sin(x)*(x^2):" << endl;
    cout << "Input EPS: ";
    cin >> eps;
    cout << "Input segment [a; b]:"<<endl;
    cout << "a = ";
    cin >> a;
    cout << "b = ";
    cin >> b;
    cout << "Choose a calculation method: \n" <<
    "(1) Chord method \n" << "(2) Half-division method\n" <<
    "(3) Iteration method\n" << "(4) Cancel \n";
    domenu1(a, b, eps);
}
void domenu1(double a, double b, double eps)
{
    int N;
    cout << "Your choice: ";
    cin >> N;
    switch (N)
    {
        case 1:
            R = hord(a, b, eps);
            if (! error)
            {
                cout << "Root f(x) on the segment [" << a <<
                "; " << b << "]: " << R << '\n' << endl;
            }
            else
            {
                error = false;
                domenu1(a, b, eps);
            }
            break;
        case 2:
            R = polovina(a, b, eps);
            if (! error)
            {
                cout << "Root f(x) on the segment [" << a <<
                "; " << b << "]: " << R << '\n' << endl;
            }
            error = false;
            break;
        case 3:
            R = itera(a, b, eps);
            if (! error)
            {
                cout << "Root f(x) on the segment [" << a <<
                "; " << b << "]: " << R << '\n' << endl;
            }
            else
            {
                error = false;
                domenu1(a, b, eps);
            }
            break;
        case 4:
            cout << '\n';
            main_menu();
    }
    if (N != 1 && N != 2 && N != 3 && N != 4)
    {
        cout << "!Input ERROR. Try again. \n";
        domenu1(a, b, eps);
    }
    main_menu();
}

double f(double x)
{
    return sin(x) * x * x;
}
double g(double x)
{
    return x + sin(x) * x * x;
}
double hord(double a, double b, double eps)
{
    double x, xnow, xnext;
    if(f(a) * f(b) > 0)
    {
        cout << "!ERROR: Wrong interval. Try another method. \n";
        error = true;
        return 0;
    }
    else if(f(a) * f(b) == 0)
    {
        return ((f(a) == 0) ? a : b);
    }
    if (a < 0 and b < 0)
    {
        x = a;
        a = b;
        b = x;
    }
    xnow = a;
    do
    {
        x = xnow;
        xnext = xnow - ((f(xnow) * (xnow - b)) / (f(xnow) - f(b)));
        xnow = xnext;
        if((f(xnow)*f(b)) > 0)
        {
            b = xnow;
            xnow = a;
        }
    }
    while (abs(x - xnext) > eps);
    return xnow;
}

double polovina(double a, double b, double eps)
{
    double xcentr, aish, bish, R;
    if(f(a) * f(b) == 0)
    {
        return ((f(a) == 0) ? a : b);
    }
    aish = a;
    bish = b;
    while (abs(b - a) > eps)
    {
		xcentr = (a + b) / 2;
        if (f(a) * f(xcentr) <= 0)
        {
            b = xcentr;
        }
        else
        {
            a = xcentr;
        }
    }
    R = (a + b) / 2;
    if ((a == aish) || (b == bish))
    {
        cout << "No roots!\n" << endl;
        error = true;
        return 0;
    }
    else
    {
        return R;
    }

}

double itera(double a, double b, double eps)
{
    double xnow, xnext, x;
    xnow = (a + b) / 2;
    do
    {
        x = xnow;
        xnext = g(xnow);
        xnow = xnext;
        if (xnow < a || xnow > b)
        {
            cout << "!Calculation ERROR. Try another method. \n";
            error = true;
            return 0;
        }
    }
    while (abs(x - xnext) > eps);
    return xnow;
}

int main()
{
    main_menu();
}




