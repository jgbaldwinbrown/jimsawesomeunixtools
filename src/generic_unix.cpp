#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

int findex = 0;

int main() {
    for (string line; getline(cin, line);) {
        findex++;
        if(findex%4==1)
        {
            cout << ">" << line.substr(1) << endl;
        }
        if(findex%4==2)
        {
            cout << line << endl;
        }
        //cout << line << endl;
    }
    return 0;
}



/*int fib(int n)
{
  if(1 == n || 2 == n)
  {
      return 1;
  }
  else
  {
      return fib(n-1) + fib(n-2);
  }

}

int main()
{
    cout << "This program prints the first ten fibonacci numbers." << endl;
    for(int i=1; i<=10; i++)
    {
        cout << fib(i) << endl;
    }
    return 0;
}*/
