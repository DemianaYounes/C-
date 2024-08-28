#ifndef FINANCETRACKER_INTERFACE_H
#define FINANCETRACKER_INTERFACE_H

struct node{
    float32 amount;
    char Description[100];
    char category[100];
    struct node *next;
};

typedef enum{
    OK,
    NOK
}operationStatus;

void FinanceTracker_voidDisplayMenu (void);
uint16 FinanceTracker_voidSystemStart (void);
operationStatus FinanceTracker_uint32NewTransaction (void);
operationStatus FinanceTracker_uint32ViewTransaction(void);
void FininaceTracker_voidViewSummary(void);
void FinanceTracker_voidGetInsight(void);
void SortingFromSmallest(void);
void PrintTransaction(void);

#endif // FINANCETRACKER_INTERFACE_H_INCLUDED
