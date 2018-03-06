/*==============================================================================
Zachary Hadjah                    February 9th 2018
Junior Year                       Data Structures/ Algorithm Analysis

This program tracks the user's monthly budget and their expenses in order to 
calculate the over/under and tells the user whether they are within their
budget.

 * MonthlyBudget struct consists of the budgets for certain categories
 * MonthlyExpenses struct consists of the amount of money that was spent in that
   particular category
 * getMonths() will prompt the user for the number of months for which they want
   to keep track of
 * getMonthlyBudget() will prompt the user for the budget amounts in seven different 
   finance categories
 * getMonthlyExpenses() will prompt the user for how much money they spent in the
   seven different finance categories
 * getMonthlyReport()  will display the information in a tabular format and tell
   the user how much money they spent in comparison to their budget, giving them
   an over/under amount.
==============================================================================*/
#include <cstdlib>
#include <limits>
#include <iostream>
#include <iomanip> 
#include <string>
#include <fstream>
#include <cmath>
#include <cctype>
using namespace std;

struct MonthlyBudget
{
    double housing;
    double utilites;
    double houseHold;
    double transportation;
    double food;
    double medical;
    double insurance;
    double entertainment;
    double clothinng;
    double misc;
};

struct MonthlyExpenses
{
    double housingEx;
    double utilitesEx;
    double householdEx;
    double transportationEx;
    double foodEx;
    double medicalEx;
    double insuranceEx;
    double entertainmentEx;
    double clothinngEx;
    double miscEx;
};

//prototypes declared outside of main so main function logic isn't distorted
void describeProgram();
void getMonths(int& months);
void getMonthlyBudget(fstream& budgetFile, int months);
void getMonthlyExpenses(fstream& expenseFile, int months);
void getMonthlyReport(fstream& budgetFile, fstream& expenseFile, int months);   


int main() 
{
    int months = 1;
    fstream budgetFile, expenseFile;   
    
    describeProgram();
    getMonths(months);
    getMonthlyBudget(budgetFile, months);
    getMonthlyExpenses(expenseFile, months);
    getMonthlyReport(budgetFile, expenseFile, months);
        
    return 0;
}

void describeProgram()
{
    cout<<
          "This program will ask you for your desired budget for housing, "
          "utilites, entertainment,  \n etc (8 budget options), and will also ask you for the amount"
          " of money you spent on such expenses. \n First, the program will ask you for how "
          "many months you would like analyzed. These numbers entered will be put into "
          "a \n MonthlyBudget struct and sent to two external files (budget.bin ad expenses.bin). "
          "It will then calculate the difference and display the budget,  \n the expenses, "
          "and over/under in a tabular format.\n";
}

/**
 * 
 * @param months will take integer input from 1 - 12 (both inclusive) 
 */
void getMonths(int& months)
{
    cout<<"How many months would you like to have analyzed? \n";
    cin>>months;  
    
    while(months <=0 || months >=13)
    {
        cout<<"Please enter input between 1 - 12 \n";
        cin>>months;
    }
    
    while(cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Enter valid input ";
        cin >> months;
    }

}

/**
 * @param budgetFile will open the bugdet.bin file and write in the data members
 *        of the MonthlyExpenses struct
 */
void getMonthlyBudget(fstream& budgetFile, int months)
{
    MonthlyBudget mb;
    int count = 1;
    
    budgetFile.open("budget.bin", ios::out|ios::binary);
    if(budgetFile.fail())
    {
      cout<<"Could not find file: budget.bin \n";
      system("PAUSE"); 
    }
    
    try
    {
        do
        {
            cin.exceptions(std::ios::failbit);  //when the failbit is set on cin, std::ios_base::failure is thrown
            
            cout<<"Enter your housing budget for month "<<count<<":\n";
            cin>>mb.housing;
            cout<<"Enter your utilities budget for month "<<count<<":\n";
            cin>>mb.utilites;
            cout<<"Enter your household expense budget for month "<<count<<":\n";
            cin>>mb.houseHold;
            cout<<"Enter your transportation budget for month "<<count<<":\n";
            cin>>mb.transportation;
            cout<<"Enter your food budget for month "<<count<<":\n";
            cin>>mb.food;
            cout<<"Enter your medical budget for month "<<count<<":\n";
            cin>>mb.medical;
            cout<<"Enter your insurance budget for month "<<count<<":\n";
            cin>>mb.insurance;
            cout<<"Enter your entertainment budget for month "<<count<<":\n";
            cin>>mb.entertainment;
            cout<<"Enter your clothing budget for month "<<count<<":\n";
            cin>>mb.clothinng;
            cout<<"Enter your Miscellaneous budget for month "<<count<<":\n";
            cin>>mb.misc;

            budgetFile.write(reinterpret_cast<char*>(&mb),sizeof(mb));
            count++;
            months --;
        }while(months != 0);
    }
    
    catch(...)
    {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
        cout<<"Error, invalid input entered. \n";
    }
            
    budgetFile.close();
}

/**
 * @param expenseFile will open the expenses.bin file and write in the data members
 *        of the MonthlyExpenses struct
 */
void getMonthlyExpenses(fstream& expenseFile, int months)
{
    MonthlyExpenses me;
    int count = 1;

    
    expenseFile.open("expenses.bin", ios::out|ios::binary);
    if(expenseFile.fail())
    {
      cout<<"Could not open expenses.bin \n";
      system("read");
    }
    try
    {
        do
        {
            cin.exceptions(std::ios::failbit); 

            cout<<"Enter your housing expenses for month "<<count<<":\n";
            cin>>me.housingEx;
            cout<<"Enter your utilities expenses for month "<<count<<":\n";
            cin>>me.utilitesEx;
            cout<<"Enter the cost of your house hold expenses for month "<<count<<":\n";
            cin>>me.householdEx;
            cout<<"Enter your transportation expenses for month "<<count<<":\n";
            cin>>me.transportationEx;
            cout<<"Enter your food expenses for month "<<count<<":\n";
            cin>>me.foodEx;
            cout<<"Enter your medical expenses for month "<<count<<":\n";
            cin>>me.medicalEx;
            cout<<"Enter your insurance expenses for month "<<count<<":\n";
            cin>>me.insuranceEx;
            cout<<"Enter your entertainment expenses for month "<<count<<":\n";
            cin>>me.entertainmentEx;
            cout<<"Enter your clothing expenses for month "<<count<<":\n";
            cin>>me.clothinngEx;
            cout<<"Enter your Miscellaneous expenses for month "<<count<<":\n";
            cin>>me.miscEx;    

            expenseFile.write(reinterpret_cast<char*>(&me),sizeof(me));
            count++;	
            months--;	
        }while(months!=0);  
    }
    
    catch(...)
    {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
        cout<<"Error, invalid input entered. \n";
    } 
    expenseFile.close();
}

/**
 * @param budgetFile will read from the budget.bin file 
 * @param expenseFile will read from the expenses.bin file
 */
void getMonthlyReport(fstream& budgetFile, fstream& expenseFile, int months)
{
    MonthlyBudget mb;
    MonthlyExpenses me;
    ofstream toFile;
    const int width1 = 14;
    const int width2 = 11;
       
    
    budgetFile.open("budget.bin", ios::in|ios::binary);
    if(budgetFile.fail()){
        cout<<"Could not open budget.bin";
        system("read"); 
    }
    budgetFile.read(reinterpret_cast<char*>(&mb),sizeof(mb));
        
    expenseFile.open("expenses.bin", ios::in|ios::binary);  
    if(expenseFile.fail()){
        cout<<"Could not open expenses.bin (getMonthlyReport function)";
        system("read");
    }    
    expenseFile.read(reinterpret_cast<char*>(&me),sizeof(me));
        
    while(  !expenseFile.eof() && !budgetFile.eof()  )
    {
       //displaying info to screen 
       cout<<fixed<<showpoint<<setprecision(2);
       cout<<"--------------------------------------------------------------------\n";
       cout<<left<<setw(width1)<<"Category";
       cout<<right<<setw(width2)<<"Budgeted";
       cout<<right<<setw(width1)<<"Spent";
       cout<<right<<setw(width1)<<"   Over(-)/Under \n";
       cout<<"--------------------------------------------------------------------\n";
      
       cout<<left<<setw(width1)<<"Housing";
       cout<<right<<setw(width2)<<mb.housing;
       cout<<right<<setw(width1)<<me.housingEx;
       cout<<right<<setw(width1)<<(mb.housing - me.housingEx)<<"\n";
       
       cout<<left<<setw(width1)<<"Utilities";
       cout<<right<<setw(width2)<<mb.utilites;
       cout<<right<<setw(width1)<<me.utilitesEx;
       cout<<right<<setw(width1)<<(mb.utilites - me.utilitesEx)<<"\n";
       
       cout<<left<<setw(width1)<<"House Hold";
       cout<<right<<setw(width2)<<mb.houseHold;
       cout<<right<<setw(width1)<<me.householdEx;
       cout<<right<<setw(width1)<<(mb.houseHold - me.householdEx)<<"\n";
       
       cout<<left<<setw(width1)<<"Transportation";
       cout<<right<<setw(width2)<<mb.transportation;
       cout<<right<<setw(width1)<<me.transportationEx;
       cout<<right<<setw(width1)<<(mb.transportation - me.transportationEx)<<"\n";
               
       cout<<left<<setw(width1)<<"Food";
       cout<<right<<setw(width2)<<mb.food;
       cout<<right<<setw(width1)<<me.foodEx;
       cout<<right<<setw(width1)<<(mb.food - me.foodEx)<<"\n";
       
       cout<<left<<setw(width1)<<"Medical";
       cout<<right<<setw(width2)<<mb.medical;
       cout<<right<<setw(width1)<<me.medicalEx;
       cout<<right<<setw(width1)<<(mb.medical - me.medicalEx)<<"\n";
       
       cout<<left<<setw(width1)<<"Insurance";
       cout<<right<<setw(width2)<<mb.insurance;
       cout<<right<<setw(width1)<<me.insuranceEx;
       cout<<right<<setw(width1)<<(mb.insurance - me.insuranceEx)<<"\n";
       
       cout<<left<<setw(width1)<<"Entertainment";
       cout<<right<<setw(width2)<<mb.entertainment;
       cout<<right<<setw(width1)<<me.entertainmentEx;
       cout<<right<<setw(width1)<<(mb.entertainment - me.entertainmentEx)<<"\n";
       
       cout<<left<<setw(width1)<<"Clothing";
       cout<<right<<setw(width2)<<mb.clothinng;
       cout<<right<<setw(width1)<<me.clothinngEx;
       cout<<right<<setw(width1)<<(mb.clothinng - me.clothinngEx)<<"\n";
       
       cout<<left<<setw(width1)<<"Miscellaneous";
       cout<<right<<setw(width2)<<mb.misc;
       cout<<right<<setw(width1)<<me.miscEx;
       cout<<right<<setw(width1)<<(mb.misc - me.miscEx)<<"\n";
                 
       cout<<"For the month you are over budget by $"<<          
            (me.housingEx + me.utilitesEx + me.householdEx + me.transportationEx
             + me.foodEx + me.medicalEx + me.insuranceEx + me.entertainmentEx + 
             me.clothinngEx + me.miscEx )
            -   
            (mb.housing + mb.utilites + mb.houseHold + mb.transportation + mb.food +
             mb.medical + mb.insurance + mb.entertainment + mb.clothinng + mb.misc)<<"\n";
      
       //writing to text file
       toFile.open("results.txt",ios::app);
       toFile<<fixed<<showpoint<<setprecision(2);
       toFile<<"--------------------------------------------------------------------\n";
       toFile<<left<<setw(width1)<<"Category";
       toFile<<right<<setw(width2)<<"Budgeted";
       toFile<<right<<setw(width1)<<"Spent";
       toFile<<right<<setw(19)<<"   Over(-)/Under \n";
       toFile<<"--------------------------------------------------------------------\n";
      
       toFile<<left<<setw(width1)<<"Housing";
       toFile<<right<<setw(width2)<<mb.housing;
       toFile<<right<<setw(width1)<<me.housingEx;
       toFile<<right<<setw(width1)<<(mb.housing - me.housingEx)<<"\n";
       
       toFile<<left<<setw(width1)<<"Utilities";
       toFile<<right<<setw(width2)<<mb.utilites;
       toFile<<right<<setw(width1)<<me.utilitesEx;
       toFile<<right<<setw(width1)<<(mb.utilites - me.utilitesEx)<<"\n";
       
       toFile<<left<<setw(width1)<<"House Hold";
       toFile<<right<<setw(width2)<<mb.houseHold;
       toFile<<right<<setw(width1)<<me.householdEx;
       toFile<<right<<setw(width1)<<(mb.houseHold - me.householdEx)<<"\n";
       
       toFile<<left<<setw(width1)<<"Transportation";
       toFile<<right<<setw(width2)<<mb.transportation;
       toFile<<right<<setw(width1)<<me.transportationEx;
       toFile<<right<<setw(width1)<<(mb.transportation - me.transportationEx)<<"\n";
               
       toFile<<left<<setw(width1)<<"Food";
       toFile<<right<<setw(width2)<<mb.food;
       toFile<<right<<setw(width1)<<me.foodEx;
       toFile<<right<<setw(width1)<<(mb.food - me.foodEx)<<"\n";
       
       toFile<<left<<setw(width1)<<"Medical";
       toFile<<right<<setw(width2)<<mb.medical;
       toFile<<right<<setw(width1)<<me.medicalEx;
       toFile<<right<<setw(width1)<<(mb.medical - me.medicalEx)<<"\n";
       
       toFile<<left<<setw(width1)<<"Insurance";
       toFile<<right<<setw(width2)<<mb.insurance;
       toFile<<right<<setw(width1)<<me.insuranceEx;
       toFile<<right<<setw(width1)<<(mb.insurance - me.insuranceEx)<<"\n";
       
       toFile<<left<<setw(width1)<<"Entertainment";
       toFile<<right<<setw(width2)<<mb.entertainment;
       toFile<<right<<setw(width1)<<me.entertainmentEx;
       toFile<<right<<setw(width1)<<(mb.entertainment - me.entertainmentEx)<<"\n";
       
       toFile<<left<<setw(width1)<<"Clothing";
       toFile<<right<<setw(width2)<<mb.clothinng;
       toFile<<right<<setw(width1)<<me.clothinngEx;
       toFile<<right<<setw(width1)<<(mb.clothinng - me.clothinngEx)<<"\n";
       
       toFile<<left<<setw(width1)<<"Miscellaneous";
       toFile<<right<<setw(width2)<<mb.misc;
       toFile<<right<<setw(width1)<<me.miscEx;
       toFile<<right<<setw(width1)<<(mb.misc - me.miscEx)<<"\n";
       toFile.close();
       
       expenseFile.read(reinterpret_cast<char*>(&me),sizeof(me));
       budgetFile.read(reinterpret_cast<char*>(&mb),sizeof(mb));       
    }
    
    budgetFile.close();
    expenseFile.close();
}