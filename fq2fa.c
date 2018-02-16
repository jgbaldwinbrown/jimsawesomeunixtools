#include <stdio.h>
#include <string.h>

/*void slice_str(const char * str, char * buffer, size_t start, size_t end)
{
    size_t j = 0;
    for ( size_t i = start; i <= end; ++i ) {
        buffer[j++] = str[i];
    }
    buffer[j] = 0;
}*/

int findex = 0;

int main()
{
    char *line = NULL;
    size_t size;
    while (getline(&line, &size, stdin) != -1) {
        findex++;
        if(findex%4==1)
        {
            printf(">%.*s", (unsigned)strlen(line)+1, line+1);
        }
        if(findex%4==2)
        {
            printf("%s",line);
        }
    } 
    return 0;
}


/*int main() {
    for (string line; getline(cin, line);) {
        findex++;
        if(findex%4==1)
        {
            printf(">%s",line.substr(1));
        }
        if(findex%4==2)
        {
            printf("%s",line);
        }
        //cout << line << endl;
    }
    return 0;
}*/



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
