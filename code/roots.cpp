#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

//Hello

using namespace std;

vector<double> getCoefficients(string fileName);

int main(int argc, char *argv[])
{
    string fileName;
    //cout.precision(18);

    if (argc == 1)
    {
        cout << "filename: ";
        cin >> fileName;
    }
    else
    {
        fileName = argv[1];
    }

    vector<double> coefficients = getCoefficients(fileName);

    //display coefficients
    for (auto x: coefficients)
    {
        cout << x << endl;
    }

    return 0;
}

vector<double> getCoefficients(string fileName)
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