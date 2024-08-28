#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <iomanip> // For std::setw()
#include <limits> // For std::numeric_limits
#include <windows.h>

using namespace std;
#include "StdTypes.h"
#include "FinanceTracker_Interface.h"
#include "FinanceTracker_Private.h"

struct node *head=NULL;
struct node *current=NULL;
struct node *previous=NULL;


/*function description: display the main menu*/
void FinanceTracker_voidDisplayMenu (void){
    cout<<"\t\t\t\t*** This is personal Finance Tracker ***"<<endl;
    cout<<"\t\t\t\t*   1. Input Transaction               *"<<endl;
    cout<<"\t\t\t\t*   2. View Transaction                *"<<endl;
    cout<<"\t\t\t\t*   3. View Summary                    *"<<endl;
    cout<<"\t\t\t\t*   4. Get Insights                    *"<<endl;
    cout<<"\t\t\t\t*   5. Exit System                     *"<<endl;
    cout<<"\t\t\t\t****************************************"<<endl;
    cout<<"Choose an option: "<<endl;
}

/*function description: this function enables unlimited number of transactions
 * by using linked list
 * each time the user enters new transaction, a new node is created at the end of the list
 * to save index order of each transaction
 * return: it returns the status of operation
*/
operationStatus FinanceTracker_uint32NewTransaction (void)
{
    operationStatus local_FinanceTracker_status= NOK;

    struct node *link= (struct node*)malloc(sizeof(struct node));
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    cout<<"Enter transaction description:"<<endl;
    cin.getline(link->Description,100);

    cout<<"Enter transaction amount (positive for income, negative for expense):"<<endl;
    cin>>link->amount;

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout<<"Enter category (e.g., Food, Entertainment, Bills):"<<endl;
    cin.getline(link->category,100);

    link->next=NULL;

    if(head ==NULL)
    {
        head=link;
        local_FinanceTracker_status= OK;
            return local_FinanceTracker_status;
    }
    previous=head;
    while(previous->next != NULL){
        previous=previous->next;
    }

    previous->next=link;
    local_FinanceTracker_status= OK;
    return local_FinanceTracker_status;
}


/* function description: loop on the list
 * to calculate the total income
 * and calculate the total expense
 * and show the final balance
 * If the user selected "view summary" option before any transactions are made
 * an error message will appear
*/
void FininaceTracker_voidViewSummary(void){

    float32 local_TotalIncome=0;
    float32 local_TotalExpense=0;
    float32 local_balance=0;

    if(head==NULL){
        cout<<"No transactions are done, make a transaction first to know the summary"<<endl;
        return;
    }
    current=head;

    while(current != NULL){
        if(current->amount > 0)
            local_TotalIncome += current->amount;
        else
            local_TotalExpense += current->amount;
        current=current->next;
    }
    local_balance = local_TotalIncome + local_TotalExpense;

    cout<<"Total income= "<<local_TotalIncome<<endl;
    cout<<"Total expense= "<<local_TotalExpense<<endl;
    cout<<"Balance= "<<local_balance<<endl;
}

 /* Function Description: Record details of new financial transactions
  * The function have to sub function:
  1-print the transaction data in table
  2-sorting data from smallest to largest
  */
operationStatus FinanceTracker_uint32ViewTransaction(void)
{
    uint8 Local_uint8SortingOption;
    operationStatus Local_TransactionStatus=NOK;
    current=head;
    PrintTransaction();
    cout<<"Do you want transactions by amount?(Y/N)"<<endl;
    cin>>Local_uint8SortingOption;
    if(Local_uint8SortingOption=='Y')
    {
        cout<<"Transaction sorted by amount (low to high)"<<endl;
        SortingFromSmallest();
        PrintTransaction();
        Local_TransactionStatus=OK;
    }
    else
    {
        Local_TransactionStatus=NOK;
    }
    return Local_TransactionStatus;
}

void SortingFromSmallest(void)
{
    uint32 Local_uint32Counter=0;
    current=head;
    struct node *temp;
    uint32 Local_uint32DescriptionSize,Local_uint32categorySize;
    while(current->next!=NULL)
    {
        if(current->amount > current->next->amount)
        {
            temp->amount=current->amount;
            current->amount=current->next->amount;
            current->next->amount=temp->amount;
            Local_uint32DescriptionSize=strlen(current->Description) > strlen(current->next->Description)? strlen(current->Description):strlen(current->next->Description);
            for(Local_uint32Counter=0; Local_uint32Counter<Local_uint32DescriptionSize; Local_uint32Counter++)
            {
                temp->Description[Local_uint32Counter]=current->Description[Local_uint32Counter];
                current->Description[Local_uint32Counter]=current->next->Description[Local_uint32Counter];
                current->next->Description[Local_uint32Counter]=temp->Description[Local_uint32Counter];
            }
            current->Description[Local_uint32Counter]=0;
            current->next->Description[Local_uint32Counter]=0;

            Local_uint32categorySize=strlen(current->category) > strlen(current->next->category)? strlen(current->category):strlen(current->next->category);
            for(Local_uint32Counter=0; Local_uint32Counter<Local_uint32categorySize; Local_uint32Counter++)
            {
                temp->category[Local_uint32Counter]=current->category[Local_uint32Counter];
                current->category[Local_uint32Counter]=current->next->category[Local_uint32Counter];
                current->next->category[Local_uint32Counter]=temp->category[Local_uint32Counter];
            }
            current->category[Local_uint32Counter]=0;
            current->next->category[Local_uint32Counter]=0;
        }
        current=current->next;
    }
}

void PrintTransaction(void)
{
    current=head;
    cout<<"\t\t\t*************************************************************************"<<endl;
    cout<<"\t\t\t*********Description \t\t Amount \t\t Category********"<<endl;
    cout<<"\t\t\t*************************************************************************"<<endl;
    while(current != NULL)
    {
        cout<<setw(32)<<current->Description<<setw(24)<<current->amount<<setw(24)<<current->category<<endl;
        current=current->next;
    }
    cout<<"\t\t\t*************************************************************************"<<endl;
}

/*Description:Offer insights into spending habits by category
 *Calculate the total expenses
 *Calculates the percentage of total expenses attributed to each category
 */
void FinanceTracker_voidGetInsight(void)
{
    sint32 Local_uint32ExpensesSum=0;
    uint32 Local_uint32Categorypercentage=0;
    float32 Local_float32CategorypercentageFraction=0;
    current=head;
    cout<<"<-------------------Spending Insights------------------->"<<endl;
    while(current!=NULL)
    {
        if((current->amount) <0)
        {
            Local_uint32ExpensesSum+= (current->amount);
        }
        current=current->next;
    }
    Local_uint32ExpensesSum*=-1;
    cout<<"Total Expenses= "<<Local_uint32ExpensesSum<<endl;
    current=head;
    while(current!=NULL)
    {
        if((current->amount) <0)
        {
            Local_float32CategorypercentageFraction=(((current->amount)*-1)/(float32)Local_uint32ExpensesSum)*100;
            Local_uint32Categorypercentage=Local_float32CategorypercentageFraction;
            cout<<"Category: "<<current->category<<" -spent: "<<Local_uint32Categorypercentage<<" ("<<Local_float32CategorypercentageFraction<<"% OF Total)"<<endl;
        }
        current=current->next;
    }

}

uint16 FinanceTracker_voidSystemStart (void)
{
    uint32 Local_uint32InputOption;
    operationStatus Local_TransactionStatus=NOK;
    uint16 Local_uint16SystemFlag=0;
    FinanceTracker_voidDisplayMenu();

    cin>>Local_uint32InputOption;

    if (cin.fail())
    {
        // Clear error state
        cin.clear();
        // Ignore the invalid input
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // Provide feedback and prompt again
        cout << "Invalid input. Please enter a number between 1 and 5." << endl;
    }

    switch(Local_uint32InputOption)
    {
    case NEW_TRANSACTION:
        Local_TransactionStatus=FinanceTracker_uint32NewTransaction();
        if(Local_TransactionStatus==OK)
        {
            cout<<"<---Done-->"<<endl;
        }
        else
        {
            cout<<"<---Fail-->"<<endl;
        }
        BEEP_DONE;
        break;
    case VIEW_TRANSACTION:
        Local_TransactionStatus=FinanceTracker_uint32ViewTransaction();
        if(Local_TransactionStatus==OK)
        {
            cout<<"<---Done-->"<<endl;
        }
        else
        {
            cout<<"<---Fail-->"<<endl;
        }
        BEEP_DONE;
        break;
    case VIEW_SUMMARY:
        FininaceTracker_voidViewSummary();
        cout<<"<---Done-->"<<endl;
        BEEP_DONE;
        break;
    case GET_INSIGHTS:
        FinanceTracker_voidGetInsight();
        cout<<"<---Done-->"<<endl;
        BEEP_DONE;
        break;
    case EXIT_SYSTEM:
        cout<<"<--- Good Luck -->"<<endl;
        Local_uint16SystemFlag=1;
        BEEP;
        break;
    default:
        BEEP;
        cout<<"Invalid Input"<<endl;
    }
    return Local_uint16SystemFlag;
}
