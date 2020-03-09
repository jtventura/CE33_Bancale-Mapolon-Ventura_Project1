#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <complex>

using namespace std;

vector<double> get_coefficients(string fileName);
vector<complex<double>> bairstow_method(vector<double> coefficients);
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
    
    // test for p2.txt
    vector<complex<double>> roots;
    complex<double> r1(2,0);
    complex<double> r2(-1,0);
    complex<double> r3(1,0.5);
    complex<double> r4(1,-0.5);
    complex<double> r5(0.5,0);
    roots.push_back(r1);
    roots.push_back(r2);
    roots.push_back(r3);
    roots.push_back(r4);
    roots.push_back(r5);

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
    double r = coefficients[1]/coefficients[0];
    double s = coefficients[2]/coefficients[0];
    

}

void print_polynomial(vector<double> coefficients)
{
    for (int i = coefficients.size()-1; i >= 0; --i)
        cout << coefficients[i] << " x^" << i << endl;
}

void print_roots(vector<complex<double>> roots)
{
    //
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

vector<complex<double>> quadratic_equation(vector<double> coefficients_2)
{
    vector<complex<double>> root;
    complex<double> r1 = (coefficients_2[0] + sqrt(coefficients_2[0]+(4*coefficients_2[1])))/2;
    complex<double> r2 = (coefficients_2[0] - sqrt(coefficients_2[0]+(4*coefficients_2[1])))/2;
    
    root.push_back(r1);
    root.push_back(r2);
    
    return root;
}