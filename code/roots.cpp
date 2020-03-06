#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <complex>
#include <tuple>

using namespace std;

vector<double> get_coefficients(string fileName);
vector<complex<double>> bairnstow_method(vector<double> coefficients);
void print_polynomial(vector<double> coefficients);

int main(int argc, char *argv[])
{
    string fileName;

    if (argc == 1)
    {
        cout << "filename: ";
        cin >> fileName;
    }
    else
    {
        fileName = argv[1];
    }

    vector<double> coefficients = get_coefficients(fileName);

    print_polynomial(coefficients);

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
    {
        cout << "File " << fileName << " is not found in this directory." << endl;
    }
    while (file.get(c))
    {
        if (!isspace(c))
        {
            termStream << c;
        }
        else
        {
            if (termStream.rdbuf()->in_avail())
            {
                termStream >> term;
                terms.push_back(term);
                termStream.clear();
            }
            else
            {
                termStream.clear();
            }
        }  
    }
    file.close();

    for (int i = 1; i <= int(terms[0]) + 1; ++i)
    {
        coefficients.push_back(terms[i]);
    }

    return coefficients;
}

vector<complex<double>> bairnstow_method(vector<double> coefficients)
{
    double r = 0.5;
    double s = -0.5;
    double e = 0.01;

    
}

void print_polynomial(vector<double> coefficients)
{
    cout << "Polynomial:" << endl;
    for (int i = coefficients.size()-1; i >= 0; --i)
    {
        cout << coefficients[i] << " x^" << i << endl;
    }
}