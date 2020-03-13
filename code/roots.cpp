#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <complex>

using namespace std;

vector<double> get_coefficients(string fileName);
vector<complex<double>> bairstow_method(vector<double> coefficients);
vector<complex<double>> quadratic_equation(double r, double s);
void print_polynomial(vector<double> coefficients);
void print_roots(vector<complex<double>> roots);
void horner_method(vector<double> coefficients, complex<double> root);

int main(int argc, char *argv[])
{
    string fileName;

    if (argc == 1)
    {
        cout << "filename: ";
        cin >> fileName;
    }
    else
        fileName = argv[1];

    vector<double> coefficients = get_coefficients(fileName);
    cout << "Polynomial:" << endl;
    print_polynomial(coefficients);
    cout << endl;
    
    vector<complex<double>> roots = bairstow_method(coefficients);
    cout << "Roots:" << endl;
    print_roots(roots);
    cout << endl;

    cout << "Evaluating polynomial at identified roots:" << endl;
    for (auto root: roots)
        horner_method(coefficients, root);
    
    return 0;
}

vector<double> get_coefficients(string fileName)
{
    vector<double> terms;
    vector<double> coefficients;
    double term;
    
    stringstream termStream;
    ifstream file;
    char c;

    file.open(fileName);
    if (!file.is_open())
        cout << "File " << fileName << " is not found in this directory." << endl;
    while (file.get(c))
    {
        if (!isspace(c))
            termStream << c;
        else
        {
            if (termStream.rdbuf()->in_avail())
            {
                termStream >> term;
                terms.push_back(term);
                termStream.clear();
            }
            else
                termStream.clear();
        }  
    }
    file.close();

    for (int i = 1; i <= int(terms[0]) + 1; ++i)
        coefficients.push_back(terms[i]);

    return coefficients;
}

vector<complex<double>> bairstow_method(vector<double> coefficients)
{
    vector<complex<double>> roots;
    int n = coefficients.size() - 1;
    double r = 0.5;
    double s = 0.5;
    double e = 1e-6;
    double dr, ds, er, es;
    int iter = 1;
 
    vector<double> b(n+1, 0), c(n+1, 0);

    while (iter)
    {
        b[n] = coefficients[n];
        b[n-1] = coefficients[n-1] + b[n]*r;

        for (int i = n-2; i >= 0; --i)
            b[i] = coefficients[i] + b[i+1]*r + b[i+2]*s;

        c[n] = b[n];
        c[n-1] = b[n-1] + c[n]*r;
        
        for (int i = n-2; i >= 1; --i)
            c[i] = b[i] + c[i+1]*r + c[i+2]*s;

        dr = (b[0]*c[3] - b[1]*c[2]) / (c[2]*c[2] - c[1]*c[3]);
        ds = (b[1]*c[1] - b[0]*c[2]) / (c[2]*c[2] - c[1]*c[3]);

        r = r + dr;
        s = s + ds;

        er = abs(dr / r) * 100;
        es = abs(ds / s) * 100;

        for (auto x: b)
            cout << x << " ";
        cout << endl;
        
        if (iter)
            break;

        if (er < e && es < e)
        {
            for (auto root: quadratic_equation(r, s))
                roots.push_back(root);
            break;
        }
        ++iter;
    }
    
    if (n > 4)
    {
        b.erase(b.begin(), b.begin() + 2);
        for (auto root: bairstow_method(b))
            roots.push_back(root);
    }
    else if (n == 4)
    {
        for (auto root: quadratic_equation(-b[n-1], -b[n-2]))
            roots.push_back(root);
    }
    else if (n == 3)
    {
        roots.push_back(-b[n-1] / b[n]);
    }

    return roots;
}

vector<complex<double>> quadratic_equation(double r, double s)
{
    vector<complex<double>> quad_roots;
    complex<double> x1, x2;

    double discriminant = r*r + 4*s;

    if (discriminant > 0)
    {
        x1 = (r + sqrt(discriminant)) / 2;
        x2 = (r - sqrt(discriminant)) / 2;
        quad_roots.push_back(x1);
        quad_roots.push_back(x2);
    }
    else if (discriminant == 0)
    {
        x1 = (r + sqrt(discriminant)) / 2;
        quad_roots.push_back(x1);
    }
    else 
    {
        complex<double> cx1(r / 2, sqrt(-discriminant) / 2);
        complex<double> cx2(r / 2, -sqrt(-discriminant) / 2);
        quad_roots.push_back(cx1);
        quad_roots.push_back(cx2);      
    }

    return quad_roots;
}

void print_polynomial(vector<double> coefficients)
{
    for (int i = coefficients.size()-1; i >= 0; --i)
        cout << coefficients[i] << " x^" << i << endl;
}

void print_roots(vector<complex<double>> roots)
{
    for (auto root: roots)
        cout << root << endl;
}

void horner_method(vector<double> coefficients, complex<double> root)
{
    complex<double> eval(0,0);

    for (int i = coefficients.size()-1; i >= 0; --i)
        eval = eval * root + coefficients[i];
    
    if (!(real(eval) && imag(eval)))
        cout << "f(" << real(root) << ", " << imag(root) << ") = " << abs(eval) << endl;
    else
        cout << "f(" << real(root) << ", " << imag(root) << ") = " << eval << endl;
}