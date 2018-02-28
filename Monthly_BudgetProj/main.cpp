/*==============================================================================
Zachary Hadjah                    February 9th 2018
Junior Year                       Data Structures/ Algorithm Analysis

This program tracks the users monthly budget and their expenses in order to 
calculate the over/under and tell the user whether they are within their
budget.

 * MonthlyBudget struct consists of the budgets for certain categories
 * MonthlyExpenses struct consists of the amount of money that was spent in that
   particular category
 * getMonths() will ask the user for the number of months which they want to 
   track their over/under
 * getMonthlyBudget() will ask the user for the amount in which they want their 
 * getMonthlyExpenses() will ask the user for the dollar amounts in which they 
   spent money
 * getMonthlyReport()  
==============================================================================*/
#include <cstdlib>
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

/*
 * 
 */
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

/**
 * 
 */
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
 * @param months
 */
void getMonths(int& months)
{
    cout<<"How many months would you like to have analyzed? ";
    cin>>months;  
}

/**
 * 
 * @param budgetFile
 * @param months
 */
void getMonthlyBudget(fstream& budgetFile, int months)
{
    MonthlyBudget mb;

    budgetFile.open("budget.bin", ios::out|ios::binary);
    if(budgetFile.fail())
    {
      cout<<"Could not find file: budget.bin \n";
      system("PAUSE");
    }
    do{
        cout<<"Enter your housing budget: \n";
        cin>>mb.housing;
        cout<<"Enter your utilities budget: \n";
        cin>>mb.utilites;
        cout<<"Enter your household expense budget: \n";
        cin>>mb.houseHold;
        cout<<"Enter your transportation budget: \n";
        cin>>mb.transportation;
        cout<<"Enter your food budget: \n";
        cin>>mb.food;
        cout<<"Enter your medical budget: \n";
        cin>>mb.medical;
        cout<<"Enter your insurance budget: \n";
        cin>>mb.insurance;
        cout<<"Enter your entertainment budget \n";
        cin>>mb.entertainment;
        cout<<"Enter your clothing budget: \n";
        cin>>mb.clothinng;
        cout<<"Enter your Miscellaneous budget: \n";
        cin>>mb.misc;

        budgetFile.write(reinterpret_cast<char*>(&mb),sizeof(mb));		
        months --;
    }while(months != 0);
    budgetFile.close();
}

/**
 * 
 * @param expenseFile
 * @param months
 */
void getMonthlyExpenses(fstream& expenseFile, int months)
{
    MonthlyExpenses me;
    expenseFile.open("expenses.bin", ios::out|ios::binary);
    if(expenseFile.fail())
    {
      cout<<"Could not open expense.bin \n";
      system("PAUSE");
    }
    
    do{
        cout<<"Enter your housing expenses: \n";
        cin>>me.housingEx;
        cout<<"Enter your utilities expenses: \n";
        cin>>me.utilitesEx;
        cout<<"Enter the cost of your house hold expenses: \n";
        cin>>me.householdEx;
        cout<<"Enter your transportation expenses: \n";
        cin>>me.transportationEx;
        cout<<"Enter your food expenses: \n";
        cin>>me.foodEx;
        cout<<"Enter your medical expenses: \n";
        cin>>me.medicalEx;
        cout<<"Enter your insurance expenses: \n";
        cin>>me.insuranceEx;
        cout<<"Enter your entertainment expenses: \n";
        cin>>me.entertainmentEx;
        cout<<"Enter your clothing expenses: \n";
        cin>>me.clothinngEx;
        cout<<"Enter your Miscellaneous expenses: \n";
        cin>>me.miscEx;        
        expenseFile.write(reinterpret_cast<char*>(&me),sizeof(me));	
        months--;	
    }while(months!=0);
    expenseFile.close();
}

/**
 * 
 * @param budgetFile
 * @param expenseFile
 * @param months
 */
void getMonthlyReport(fstream& budgetFile, fstream& expenseFile, int months)
{
    MonthlyBudget mb;
    MonthlyExpenses me;
    ofstream toFile;
        
    budgetFile.open("budget.bin", ios::in|ios::binary);
    if(budgetFile.fail()){
        cout<<"Could not open budget.bin";
        system("PAUSE");
    }
    budgetFile.read(reinterpret_cast<char*>(&mb),sizeof(mb));
        
    expenseFile.open("expense.bin", ios::in|ios::binary);  
    if(expenseFile.fail()){
        cout<<"Could not open expense.bin (getMonthlyReport function)";
        system("read");
    }    
    expenseFile.read(reinterpret_cast<char*>(&me),sizeof(me));
        
    while(  !expenseFile.eof() && !budgetFile.eof()  )
    {
       //displaying info to screen 
       cout<<fixed<<showpoint<<setprecision(1);
       cout<<"--------------------------------------------------------------------\n";
       cout<<left<<setw(14)<<"Category";
       cout<<right<<setw(7)<<"Budget";
       cout<<right<<setw(10)<<"Spent";
       cout<<right<<setw(15)<<"   Over(-)/Under \n";
       cout<<"--------------------------------------------------------------------\n";
      
       cout<<left<<setw(14)<<"Housing";
       cout<<right<<setw(7)<<mb.housing;
       cout<<right<<setw(10)<<me.housingEx;
       cout<<right<<setw(10)<<(mb.housing - me.housingEx)<<"\n";
       
       cout<<left<<setw(14)<<"Utilities";
       cout<<right<<setw(7)<<mb.utilites;
       cout<<right<<setw(10)<<me.utilitesEx;
       cout<<right<<setw(10)<<(mb.utilites - me.utilitesEx)<<"\n";
       
       cout<<left<<setw(14)<<"House Hold";
       cout<<right<<setw(7)<<mb.houseHold;
       cout<<right<<setw(10)<<me.householdEx;
       cout<<right<<setw(10)<<(mb.houseHold - me.householdEx)<<"\n";
       
       cout<<left<<setw(14)<<"Transportation";
       cout<<right<<setw(7)<<mb.transportation;
       cout<<right<<setw(10)<<me.transportationEx;
       cout<<right<<setw(10)<<(mb.transportation - me.transportationEx)<<"\n";
               
       cout<<left<<setw(14)<<"Food";
       cout<<right<<setw(7)<<mb.food;
       cout<<right<<setw(10)<<me.foodEx;
       cout<<right<<setw(10)<<(mb.food - me.foodEx)<<"\n";
       
       cout<<left<<setw(14)<<"Medical";
       cout<<right<<setw(7)<<mb.medical;
       cout<<right<<setw(10)<<me.medicalEx;
       cout<<right<<setw(10)<<(mb.medical - me.medicalEx)<<"\n";
       
       cout<<left<<setw(14)<<"Insurance";
       cout<<right<<setw(7)<<mb.insurance;
       cout<<right<<setw(10)<<me.insuranceEx;
       cout<<right<<setw(10)<<(mb.insurance - me.insuranceEx)<<"\n";
       
       cout<<left<<setw(14)<<"Entertainment";
       cout<<right<<setw(7)<<mb.entertainment;
       cout<<right<<setw(10)<<me.entertainmentEx;
       cout<<right<<setw(10)<<(mb.entertainment - me.entertainmentEx)<<"\n";
       
       cout<<left<<setw(14)<<"Clothing";
       cout<<right<<setw(7)<<mb.clothinng;
       cout<<right<<setw(10)<<me.clothinngEx;
       cout<<right<<setw(10)<<(mb.clothinng - me.clothinngEx)<<"\n";
       
       cout<<left<<setw(14)<<"Miscellaneous";
       cout<<right<<setw(7)<<mb.misc;
       cout<<right<<setw(10)<<me.miscEx;
       cout<<right<<setw(10)<<(mb.misc - me.miscEx)<<"\n";
                     
       //writing to text file
       toFile.open("results.txt",ios::app);
       toFile<<fixed<<showpoint<<setprecision(1);
       toFile<<"--------------------------------------------------------------------\n";
       toFile<<left<<setw(14)<<"Category";
       toFile<<right<<setw(7)<<"Budget";
       toFile<<right<<setw(10)<<"Spent";
       toFile<<right<<setw(15)<<"   Over(-)/Under \n";
       toFile<<"--------------------------------------------------------------------\n";
      
       toFile<<left<<setw(14)<<"Housing";
       toFile<<right<<setw(7)<<mb.housing;
       toFile<<right<<setw(10)<<me.housingEx;
       toFile<<right<<setw(10)<<(mb.housing - me.housingEx)<<"\n";
       
       toFile<<left<<setw(14)<<"Utilities";
       toFile<<right<<setw(7)<<mb.utilites;
       toFile<<right<<setw(10)<<me.utilitesEx;
       toFile<<right<<setw(10)<<(mb.utilites - me.utilitesEx)<<"\n";
       
       toFile<<left<<setw(14)<<"House Hold";
       toFile<<right<<setw(7)<<mb.houseHold;
       toFile<<right<<setw(10)<<me.householdEx;
       toFile<<right<<setw(10)<<(mb.houseHold - me.householdEx)<<"\n";
       
       toFile<<left<<setw(14)<<"Transportation";
       toFile<<right<<setw(7)<<mb.transportation;
       toFile<<right<<setw(10)<<me.transportationEx;
       toFile<<right<<setw(10)<<(mb.transportation - me.transportationEx)<<"\n";
               
       toFile<<left<<setw(14)<<"Food";
       toFile<<right<<setw(7)<<mb.food;
       toFile<<right<<setw(10)<<me.foodEx;
       toFile<<right<<setw(10)<<(mb.food - me.foodEx)<<"\n";
       
       toFile<<left<<setw(14)<<"Medical";
       toFile<<right<<setw(7)<<mb.medical;
       toFile<<right<<setw(10)<<me.medicalEx;
       toFile<<right<<setw(10)<<(mb.medical - me.medicalEx)<<"\n";
       
       toFile<<left<<setw(14)<<"Insurance";
       toFile<<right<<setw(7)<<mb.insurance;
       toFile<<right<<setw(10)<<me.insuranceEx;
       toFile<<right<<setw(10)<<(mb.insurance - me.insuranceEx)<<"\n";
       
       toFile<<left<<setw(14)<<"Entertainment";
       toFile<<right<<setw(7)<<mb.entertainment;
       toFile<<right<<setw(10)<<me.entertainmentEx;
       toFile<<right<<setw(10)<<(mb.entertainment - me.entertainmentEx)<<"\n";
       
       toFile<<left<<setw(14)<<"Clothing";
       toFile<<right<<setw(7)<<mb.clothinng;
       toFile<<right<<setw(10)<<me.clothinngEx;
       toFile<<right<<setw(10)<<(mb.clothinng - me.clothinngEx)<<"\n";
       
       toFile<<left<<setw(14)<<"Miscellaneous";
       toFile<<right<<setw(7)<<mb.misc;
       toFile<<right<<setw(10)<<me.miscEx;
       toFile<<right<<setw(10)<<(mb.misc - me.miscEx)<<"\n";
       toFile.close();
       
       expenseFile.read(reinterpret_cast<char*>(&me),sizeof(me));
       budgetFile.read(reinterpret_cast<char*>(&mb),sizeof(mb));       
    }
    budgetFile.close();
    expenseFile.close();
}





