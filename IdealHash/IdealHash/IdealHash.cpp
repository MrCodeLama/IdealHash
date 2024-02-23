#include <iostream>
#include <vector>
#include <cstdlib> 
#include <iostream>
#include <stdlib.h>
#include <chrono>

using namespace std;

vector<vector<double>> Table;
double a, b, p, m;

//type - double

double mod(double a, double b)
{
    return (((a / b) - floor(a / b)) * b);
}

int HashFunc(double element, double a, double b, double p, double m)
{
    if (a == 0 && b == 0 && p == 0 && m == 1)
        return 0;

    return (int)mod(mod((a * element + b), p), m);
}

void printTable()
{
    for (int i = 0; i < Table.size(); i++)
    {
        cout << i << ") \n";
        for (int j = 0; j < Table[i].size(); j++)
        {
            if (Table[i][j] != -1)
            {
                cout << "\t" << j << ") " << Table[i][j] << "\n";
            }
        }
        cout << "\n";
    }
}

//m^2 a b p 
vector<double> createParameters(vector<double> elements)
{
    bool checker = true;
    int numberofelements = elements.size();
    vector<int> hashes;
    vector<int> uniqueHashes;
    vector<double> res = { (double)numberofelements * numberofelements, 0, 1, 1 };
    int temp = 0;

    if (elements.size() != 1)
    {
        for (res[1] = 0; res[1] < 999999999999999; res[1]++)
        {
            for (res[2] = 1; res[2] < 999999999999999; res[2]++)
            {
                for (res[3] = 1; res[3] < 999999999999999; res[3]++)
                {
                    temp = rand() % 3 + 1;
                    res[temp]++;
                    hashes.clear();
                    uniqueHashes.clear();

                    for (int i = 0; i < elements.size(); i++)
                        hashes.push_back(HashFunc(elements[i], res[1], res[2], res[3], res[0]));

                    for (int i = 0; i < elements.size(); ++i)
                        if (count(uniqueHashes.begin(), uniqueHashes.end(), hashes.at(i)) == 0)
                            uniqueHashes.push_back(hashes.at(i));

                    if (uniqueHashes.size() == numberofelements)
                        return res;
                }
                if (uniqueHashes.size() == numberofelements)
                    return res;
            }
            if (uniqueHashes.size() == numberofelements)
                return res;
        }
    }
    else
        res = { 1, 0, 0, 0 };

    return res;
}

vector<double> createFirstParameters(vector<double> elements)
{
    srand((unsigned)time(NULL));

    bool checker = true;
    int numberofelements = elements.size();
    vector<int> hashes;
    vector<int> uniqueHashes;
    vector<double> res = { (double)numberofelements / 3, 0, 1, 1 };
    int temp;
    if (numberofelements != 1)
    {
        for (res[1] = 0; res[1] < 999999999999999; res[1]++)
        {
            for (res[2] = 1; res[2] < 999999999999999; res[2]++)
            {
                for (res[3] = 1; res[3] < 999999999999999; res[3]++)
                {

                    temp = rand() % 4;
                    res[temp]++;
                    hashes.clear();
                    uniqueHashes.clear();
                    for (int i = 0; i < elements.size(); i++)
                        hashes.push_back(HashFunc(elements[i], res[0], res[1], res[2], res[3]));

                    for (int i = 0; i < elements.size(); ++i)
                        if (count(uniqueHashes.begin(), uniqueHashes.end(), hashes.at(i)) == 0)
                            uniqueHashes.push_back(hashes.at(i));

                    if (uniqueHashes.size() != 1 && uniqueHashes.size() >= sqrt(numberofelements))
                        return res;
                }
                if (uniqueHashes.size() != 1 && uniqueHashes.size() >= sqrt(numberofelements))
                    return res;
            }
            if (uniqueHashes.size() != 1 && uniqueHashes.size() >= sqrt(numberofelements))
                return res;
        }
        if (uniqueHashes.size() != 1 && uniqueHashes.size() >= sqrt(numberofelements))
            return res;
    }
    return res;
}

void createNewTable(vector<double> vectorElements)
{
    srand((unsigned)time(NULL));

    Table.clear();

    //create first parameters

    vector<double> parameters = createFirstParameters(vectorElements);
    a = parameters[1];
    b = parameters[2];
    p = parameters[3];
    m = parameters[0];

    vector<int> Hashes;
    vector<int> UniqueHashes;
    vector<int> NumberOfElementsInHashes;

    //create hashes and put em into Hashes
    for (int i = 0; i < vectorElements.size(); i++)
        Hashes.push_back(HashFunc(vectorElements[i], a, b, p, m));

    //find unique hashes and put em to UniqueHashes
    for (int i = 0; i < vectorElements.size(); ++i)
        if (count(UniqueHashes.begin(), UniqueHashes.end(), Hashes.at(i)) == 0)
            UniqueHashes.push_back(Hashes.at(i));

    //create NumberOfElementsInHashes vector
    for (int i = 0; i < UniqueHashes.size(); i++)
        NumberOfElementsInHashes.push_back(0);

    //find the numbers of elements in each hash
    for (int j = 0; j < UniqueHashes.size(); j++)
        for (int i = 0; i < vectorElements.size(); i++)
            if (Hashes[i] == UniqueHashes[j])
                NumberOfElementsInHashes[j]++;

    //create Table vector of vectors
    for (int i = 0; i < m; i++)
        Table.push_back({ -1 });

    //find parameters for each subvector
    for (int i = 0; i < UniqueHashes.size(); i++)
    {
        vector<double> temp;
        for (int j = 0; j < vectorElements.size(); j++)
            if (Hashes[j] == UniqueHashes[i])
                temp.push_back(vectorElements[j]);

        vector<double> parameters = createParameters(temp);
        Table[UniqueHashes[i]] = parameters;

        for (int k = 0; k < NumberOfElementsInHashes[i] * NumberOfElementsInHashes[i]; k++)

            Table[UniqueHashes[i]].push_back(-1);
    }

    //put elements to subvectors using secondary hashes
    for (int i = 0; i < vectorElements.size(); i++)
    {

        if (Table[Hashes[i]][0] == 1 &&
            Table[Hashes[i]][1] == 0 &&
            Table[Hashes[i]][2] == 0 &&
            Table[Hashes[i]][3] == 0)
            Table[Hashes[i]][4] = vectorElements[i];
        else
        {
            int temp = HashFunc(
                vectorElements[i],
                Table[Hashes[i]][1],
                Table[Hashes[i]][2],
                Table[Hashes[i]][3],
                Table[Hashes[i]][0]
            );
            Table[Hashes[i]][temp + 4] = vectorElements[i];
        }
    }
}

bool checkIfElementAppears(double element)
{
    int hash = HashFunc(element, a, b, p, m);

    if (Table[hash][0] == -1)
        return false;
    else
    {
        int subHash = HashFunc(
            element,
            Table[hash][1],
            Table[hash][2],
            Table[hash][3],
            Table[hash][0]
        );
        if (Table[hash][subHash + 4] != element)
            return false;

    }
    return true;
}

void menu()
{
    while (true)
    {
        int task;
        int numberOfElements;
        vector<double> vectorElements;
        double temp;

        cout << "\n0 - new table | 1 - check if element appears in current table | 2 - printTable | 3 - exit\n";
        cin >> task;

        switch (task)
        {
        case 0:
            
            cout << "\nEnter number of elements: ";
            cin >> numberOfElements;
            for (int i = 0; i < numberOfElements; i++)
            {
                cout << i+1 << "/" << numberOfElements << " : ";
                cin >> temp;
                vectorElements.push_back(temp);
            }
            createNewTable(vectorElements);
            break;

        case 1:
            cout << "\nEnter element:\n";
            cin >> temp;
            cout << checkIfElementAppears(temp)<<"\n";
            break;
        case 2:
            printTable();
            break;
        case 3:
            exit(1);
            break;
        default:
            cout << "\nError, not in range 0-2\n";
            break;
        }
    }
}

int main()
{
    menu();
}