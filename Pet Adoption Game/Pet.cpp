#include <iostream>
#include <string>
#include <windows.h>
using namespace std;
#include "StdTypes.h"
#include "Pet_Interface.h"
#include "Pet.h"
#include "Pet_Private.h"

void PetGame_voidDisplay(void)
{
    cout<<"\t\t\t\t*** Welcome to the Pet Adoption Game ***"<<endl;
    cout<<"\t\t\t\t* 1-Adopt a Pet                        *"<<endl;
    cout<<"\t\t\t\t* 2-Feed the Pet                       *"<<endl;
    cout<<"\t\t\t\t* 3-Play with the Pet                  *"<<endl;
    cout<<"\t\t\t\t* 4-Check Status                       *"<<endl;
    cout<<"\t\t\t\t* 5-End Game                           *"<<endl;
    cout<<"\t\t\t\t****************************************"<<endl;
    cout<<"Enter Your option: ";
}

Adapt_Status PetGame_Adapt_StatusPetAdapt(uint8 Copy_uint8GameOption,Pet_identity*pet)
{
    Adapt_Status Local_PetStatus=pet_NOK;
    if(Copy_uint8GameOption==PET_ADOPT)
    {
        Local_PetStatus=Pet_OK;
        cout<<"Enter your pet's name: ";
        cin>>pet->Local_StringPetName;
    }
    else
    {
        cout<<"You should adopt a pet first"<<endl;
    }
    return Local_PetStatus;
}
Adapt_Status PetGame_FeedThePet(Pet_identity*pet)
{
    Adapt_Status Local_PetStatus=Pet_OK;

    if(pet->Local_uint32PetHungrLevel<90)
    {
        cout<<"Pet has been fed"<<endl;
        pet->Local_uint32PetHungrLevel+=10;
        pet->Local_uint32PetHappinessLevel-=10;
    }
    else if(pet->Local_uint32PetHungrLevel==90)
    {
        cout<<"Feed Full"<<endl;
        pet->Local_uint32PetHappinessLevel-=10;
    }
    if(pet->Local_uint32PetHappinessLevel==0 || pet->Local_uint32PetHungrLevel==0)
    {
        PetGame_voidPetStatus(pet);
        cout<<"Game Over"<<endl;
        Local_PetStatus=pet_NOK;
        BEEP;
    }
    return Local_PetStatus;
}

Adapt_Status PetGame_PlayWithPet(Pet_identity*pet)
{
    Adapt_Status Local_PetStatus=Pet_OK;

    if(pet->Local_uint32PetHappinessLevel<90)
    {
        cout<<"Pet is happy now"<<endl;
        pet->Local_uint32PetHungrLevel-=10;
        pet->Local_uint32PetHappinessLevel+=10;
    }
    else if(pet->Local_uint32PetHappinessLevel==90)
    {
        cout<<"happiness Full"<<endl;
        pet->Local_uint32PetHungrLevel-=10;
    }
    if(pet->Local_uint32PetHappinessLevel==0 || pet->Local_uint32PetHungrLevel==0)
    {
        PetGame_voidPetStatus(pet);
        cout<<"Game Over"<<endl;
        Local_PetStatus=pet_NOK;
        BEEP;
    }
    return Local_PetStatus;
}

void PetGame_voidPetStatus(Pet_identity*pet)
{
    cout<<"Hungry Level: "<<pet->Local_uint32PetHungrLevel<<endl;
    cout<<"Happy Level: "<<pet->Local_uint32PetHappinessLevel<<endl;
}

Adapt_Status PetGame_voidStartingGame(Pet_identity*pet)
{
    Adapt_Status Local_PetStatus=Pet_OK;
    uint32 Local_uint32GameOption;
    PetGame_voidDisplay();
    cin>>Local_uint32GameOption;
    switch(Local_uint32GameOption)
    {
    case PET_FEED:
        Local_PetStatus=PetGame_FeedThePet(pet);
        break;
    case PET_PLAY:
        Local_PetStatus=PetGame_PlayWithPet(pet);
        break;
    case PET_STATUS:
        PetGame_voidPetStatus(pet);
        break;
    case PET_GAME_END:
        Local_PetStatus=pet_NOK;
        cout<<"Game Over"<<endl;
        BEEP;
        break;
    default:
        cout<<"Wrong Choice"<<endl;
    }
    return Local_PetStatus;
}

