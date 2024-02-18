#include <iostream>
#include <vector>
#include <cstdlib> 
#include <iostream>
using namespace std;

vector<vector<double>> Table;

//type - double

double mod(double a, double b)
{
    return (((a / b) - floor(a / b)) * b);
}

double HashFunc(double element, double a, double b, double p, double m)
{
    return mod(mod((a * element + b), p), m);
}

void createNewTable(std::vector<double> vectorElements)
{
    
}

void test()
{
    srand((unsigned)time(NULL));

    vector<vector<double>> Table;
    vector<double> Hashes;
    vector<double> Elements;
    int numberOfElements;
    double temp;
    double a = rand() % 100;
    double b = rand() % 100;
    double p = rand() % 100;
    double m = rand() % 100;
    /*
    cout << "Enter the number of elements:\n";
    cin >> number;
    */

    numberOfElements = rand() % 100;

    for (int i = 0; i < numberOfElements; i++)
    {
        /*
        cout << "Enter "<<i<<" element:\n";
        cin >> temp;
        Elements.push_back(temp);
        */

        Elements.push_back(rand() % 100);
        cout << Elements[i] << " ";
    }
    for (int i = 0; i < numberOfElements; i++)
    {
        Hashes.push_back(HashFunc(Elements[i], a, b, p, m));
    }
    cout << "\n\n\n";
    for (int i = 0; i < numberOfElements; i++)
    {
        cout << Hashes[i] << " ";
    }
}

int main()
{
    test();
}