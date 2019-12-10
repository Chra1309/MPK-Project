#include <stdio.h>  /* for perror() */
#include <stdlib.h> /* for exit() */
#include <string>
#include <cstring> 
using namespace std;

void DieWithError(string errorMessage)
{
    perror( errorMessage.c_str());
    exit(1);
}
