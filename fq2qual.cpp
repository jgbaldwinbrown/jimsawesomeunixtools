#include <cstdlib>
#include <iostream>
#include <math.h>
#include <string>
using namespace std;

double phred2qual(int phredscore)
{
    //probgood = 1 - (float(10) ** (-float(phredscore)/float(10)))
    double dphredscore = static_cast<double>(phredscore-33);
    double tempexp = pow(static_cast<double>(10.0), 0 - (static_cast<double>(dphredscore) / static_cast<double>(10.0)));
    double probgood = 1 - tempexp;
    return probgood;
}

void printem(string phredscores)
{
    for (int i=0;i<phredscores.length()-1;i++)
    {
        int myphredscore = static_cast<int>(phredscores[i]);
        if (i==0)
        {
            cout << myphredscore;
        }
        cout << " " << myphredscore;
    }
    cout << endl;
}

int findex = 0;

int main() {
    for (string line; getline(cin, line);) {
        findex++;
        if(findex%4==1)
        {
            cout << ">" << line.substr(1) << endl;
        }
        if(findex%4==0)
        {
            printem(line);
        }
    }
    return 0;
}
