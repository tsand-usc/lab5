#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

struct Profit{
   
   double dollar; 
   int duration; 
};

//======================================KWP CLASS===============================================
class KWP{

    private:
      Profit *event; // pointer to the array
      
    public:
      KWP(int); // constructs
      ~KWP();   // destructs
      void print(int); // prints the values in the array
      double get_profit(int); // get the profit for a certain week
      void set_profit(int, double); // sets the profit for a certain week

};

KWP::KWP(int weeks){
   
   event = new Profit[weeks];  // creates array
   std::ofstream output ("output.txt"); // opens output file  
   output << "Created " << weeks << " element KWP Array" << std::endl; // print a message
   output.close();  // close the file 
   for(int i = 0; i < weeks; i++){ // fill the array with initial values
      event[i].duration = (i+1);
      event[i].dollar = 0; 
   }
}

KWP::~KWP(){
   
   delete [] event; // delete aynamic space
   std::ofstream output ("output.txt", std::ios_base::app); // opens output file  
   output << "Deleted KWP Array" << std::endl; // print message
   output.close();  // close the file    
}

void KWP::print(int weeks){ // prints out the values in the array
   
    for(int i = 0; i < weeks; i++){ 
      std::cout << "Week:" << event[i].duration << " Profit: " << event[i].dollar << std::endl; 
    } 
}

double KWP::get_profit(int week){ // gets the profit for a given week

   return event[week-1].dollar; 
   
}

void KWP::set_profit(int week, double value){ // sets the profit for a given week

   event[week-1].dollar = value; 

}

//==========================================KYP CLASS================================================
class KYP{

    private:
      Profit *event; // stores profits
      double interest;  // stores the interest he earns
      
    public:
      KYP(int);
      ~KYP();
      void print(int); 
      double get_profit(int);
      void set_profit(int, double);
      void set_interest(double);

};

KYP::KYP(int weeks){
 
   event = new Profit[weeks]; 
   std::ofstream output ("output.txt", std::ios_base::app); // opens output file  
   output << "Created " << weeks << " element KYP Array" << std::endl;
   output.close();  // close the file
   for(int i = 0; i < weeks; i++){
      event[i].duration = (i+1);
      event[i].dollar = 0; 
   }
}

KYP::~KYP(){
   
   delete [] event;
   std::ofstream output ("output.txt", std::ios_base::app); // opens output file  
   output << "Deleted KYP Array" << std::endl;
   output.close();  // close the file  
}

void KYP::print(int weeks){
   
    for(int i = 0; i < weeks; i++){
      std::cout << "Week:" << event[i].duration << " Profit: " << event[i].dollar << std::endl; 
    } 
}

double KYP::get_profit(int week){

   return event[week-1].dollar; 
   
}

void KYP::set_profit(int week, double value){

   event[week-1].dollar = value*interest; 

}

void KYP::set_interest(double value){ // sets the interest value for future use
   
   interest = value/100; 

}

//====================================PROFIT=====================================================

double P(int n, double storage[7]){ // recursive calculating function

   switch(n){ // out put based on n
              // zero is not included because 0 calculations do not work with the function and initial conditions
      case 1: // zero is handeled seperatly in the main
         return storage[1]; // week 1 has a known value
      break;
      
      case 2:
         return storage[3]; // week 2 has a known value
      break;
      
      case 3:
         return storage[5]; // week 3 has a known value
      break;
      
      default: // anything beyond 3 is calculated using the recursive function 
         double avg = ((P(1,storage) + P(n-1, storage)) + (P(2, storage) + P(n-2, storage)) + (P(3, storage) + P(n-3, storage)))/3;
         return avg;    
      break; 
   }
} 

//=======================================READ & PRINT==================================================
void read(double storage[7]){
   
   int count = 0;
   int i = 0;   
   std::string line;  // space to take in one line
   std::ifstream input("input.txt"); // input file
    
   while(getline(input, line)){                // runs through all lines
       
      if(line != ""){                          // remove blank lines
         if(line.at(0) != '/'){                // remove comments
            std::stringstream digits(line);    // makes an input from the string
            while(digits.good()){              // runs through all tokens
               digits >> storage[i];           // stores tokens in array for later use
               i++;  
            }
         }
      }
   }
   input.close();  // close the file
}

void printResult(int Z, double WWW, int U, double YYY){ // prints the results for a certain week
   
   std::cout << "KW's profit for " << Z << " number of weeks in average is estimated $" << WWW << ", out of which " << U << "%, i.e., $" << YYY << " is KY's." << std::endl;  
   
}

//=================================MAIN===========================================

using namespace std; 

int main(){
   
   int Z;           // weeks to calculate
   double file[7];  // space for file values
   double result; 
   
   cout << "Calculate how many weeks: "; // get number of weeks
   cin >> Z;
   
   if((Z < 0) || (Z > 52)){ // make sure the number of weeks is in the bounds
      cout << "Number of Weeks is not within one year" << endl; 
      exit(EXIT_FAILURE);  
   } 
 
   read(file); // get values from file
   
   KWP west(Z); // create KWP
   KYP yag(Z);  // create KYP
   
   yag.set_interest(file[6]); // get the interest value
   
   if(Z == 0){ // print zero case 
     printResult(Z, 0, (int)file[6], 0); 
   }
   
   for(int i = 0; i < Z; i++){ // Calculate All the values, and print them
      result = P((i+1), file);
      west.set_profit((i+1), result);
      yag.set_profit((i+1), result);
      printResult(Z, west.get_profit(i+1), (int)file[6], yag.get_profit(i+1)); 
   }
    
   return 0; 
}


