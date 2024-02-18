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

int HashFunc(double element, double a, double b, double p, double m)
{
    return (int)mod(mod((a * element + b), p), m);
}

void PrintAll()
{
    for (int i = 0; i < Table.size(); i++)
    {
        cout << i << ")\n";
        for (int j = 0; j < Table[i].size(); j++)
        {
            cout << "\t" << Table[i][j] << "\n";
        }
        cout << "\n";
    }
}

void createNewTable(vector<double> vectorElements)
{
    srand((unsigned)time(NULL));
    double a = rand() % 100;
    double b = rand() % 100;
    double p = rand() % 100;
    double m = rand() % 20;

    vector<double> Hashes;
    vector<double> UniqueHashes;
    vector<int> NumberOfElementsInHashes;
    Table.clear();

    //create hashes and put em into Hashes
    for (int i = 0; i < vectorElements.size(); i++)
        Hashes.push_back((double)HashFunc(vectorElements[i], a, b, p, m));

    //find unique hashes and put em to UniqueHashes
    for (int i = 0; i < vectorElements.size(); ++i)
        if (count(UniqueHashes.begin(), UniqueHashes.end(), Hashes.at(i)) == 0)
            UniqueHashes.push_back(Hashes.at(i));

    /*
    for (int i = 0; i < UniqueHashes.size(); i++)
        cout << UniqueHashes[i] << " ";
    */

    //create NumberOfElementsInHashes vector
    for (int i = 0; i < UniqueHashes.size(); i++)
        NumberOfElementsInHashes.push_back(0);
    
    //find the numbers of elements with each hash
    for (int i = 0; i < vectorElements.size(); i++)
        for (int j = 0; j < UniqueHashes.size(); j++)
            if (Hashes[i] == UniqueHashes[j])
                NumberOfElementsInHashes[j]++;
    
     /*
     for (int i = 0; i < vectorElements.size(); i++)
        cout << vectorElements[i] << " - " << Hashes[i] << "\n";
    for (int i = 0; i < UniqueHashes.size(); i++)
        cout <<"=>" << UniqueHashes[i] << " - " << NumberOfElementsInHashes[i] << "\n";

    cout << "\n";
     */

    vector<double> temp = { 0, 0, 0, 0 };

    //create Table vector of vectors
    for (int i = 0; i < m; i++)
        Table.push_back(temp);
    
    //m a b p -> elements
    for (int i = 0; i < m; i++)
        Table[i][0] = -1;
    
    for (int i = 0; i < UniqueHashes.size(); i++)
    {
        Table[UniqueHashes[i]][0] = NumberOfElementsInHashes[i] * NumberOfElementsInHashes[i];
        Table[UniqueHashes[i]][1] = rand() % 100;
        Table[UniqueHashes[i]][2] = rand() % 100;
        Table[UniqueHashes[i]][3] = rand() % 100;
    }

    for (int i = 0; i < UniqueHashes.size(); i++)
        for (int j = 0; j < Table[UniqueHashes[i]][0]; j++)
            Table[UniqueHashes[i]].push_back(-1);

    for (int i = 0; i < Hashes.size(); i++)
    {
        Table[Hashes[i]][HashFunc(vectorElements[i], Table[Hashes[i]][1], Table[Hashes[i]][2], Table[Hashes[i]][3], Table[Hashes[i]][0])] = vectorElements[i];
    }
    PrintAll();
}



void test()
{
    /*
    cout << "Enter the number of elements:\n";
    cin >> number;
    */

    vector<double> vectorElements;
    int numberOfElements = rand() % 100;

    for (int i = 0; i < numberOfElements; i++)
    {
        /*
        cout << "Enter "<<i<<" element:\n";
        cin >> temp;
        Elements.push_back(temp);
        */

        vectorElements.push_back(rand() % 100);
    }
    createNewTable(vectorElements);

}

int main()
{
        test();
}