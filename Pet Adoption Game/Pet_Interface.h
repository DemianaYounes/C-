
#ifndef PET_PRIVATE_H
#define PET_PRIVATE_H

#define PET_ADOPT     1
#define PET_FEED      2
#define PET_PLAY      3
#define PET_STATUS    4
#define PET_GAME_END  5

typedef struct
{
    string Local_StringPetName;
    uint32 Local_uint32PetHungrLevel=50;
    uint32 Local_uint32PetHappinessLevel=50;
}Pet_identity;
typedef enum
{
    Pet_OK,
    pet_NOK
} Adapt_Status;

void PetGame_voidDisplay(void);
Adapt_Status PetGame_Adapt_StatusPetAdapt(uint8 Copy_uint8GameOption,Pet_identity*pet);
Adapt_Status PetGame_FeedThePet(Pet_identity*pet);
Adapt_Status PetGame_PlayWithPet(Pet_identity*pet);
void PetGame_voidPetStatus(Pet_identity*pet);
Adapt_Status PetGame_voidStartingGame(Pet_identity*pet);

#endif
