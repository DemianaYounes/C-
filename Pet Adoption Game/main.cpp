#include <iostream>
#include <string>
#include <windows.h>

using namespace std;
#include "StdTypes.h"
#include "Pet_Interface.h"
#include "Pet.h"
#include "Pet_Private.h"

int main()
{
    /*Variables Decleration*/
    Pet_identity pet1;
    uint32 Local_uint32GameOption;
    Adapt_Status Local_PetStatus=Pet_OK,Local_AdoptPetStatus=pet_NOK;
    /*Welcome Screen:
     * The user has 5 options:
     * 1-Adopt a Pet
     * 2-Feed the Pet
     * 3-Play with the Pet
     * 4-Check Status
     * 5-End Game
     */
    while(Local_uint32GameOption!=PET_ADOPT)
    {
        PetGame_voidDisplay();
        cin>>Local_uint32GameOption;
        Local_AdoptPetStatus=PetGame_Adapt_StatusPetAdapt(Local_uint32GameOption,&pet1);
        if(Local_AdoptPetStatus==Pet_OK)
        {
            while(Local_PetStatus==Pet_OK)
            {
                Local_PetStatus=PetGame_voidStartingGame(&pet1);
            }

        }
        else
        {
            BEEP_NOT_ADOPT;
        }
    }
    return 0;
}


