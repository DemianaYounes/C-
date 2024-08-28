#include <iostream>
#include <string>
#include <cstring>
#include "StdTypes.h"
#include "FinanceTracker_Interface.h"


using namespace std;

int main()
{
    uint16 Local_uint16SystemFlag=0;
    while(1)
    {
        Local_uint16SystemFlag=FinanceTracker_voidSystemStart();
        if(Local_uint16SystemFlag==1)
        {
            break;
        }
    }
    return 0;
}
