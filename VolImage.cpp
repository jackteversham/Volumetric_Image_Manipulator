
#include "VolImageMan.cpp"
#include <string>
#include <iostream>
#include <sstream>


int main(int argc, char ** argv){

    //DEAL WITH COMMAND LINE ARGUMENTS
     string prefix;
     string output_filename;
     bool diffMap;
     bool extract;
     int i, j;
     std::istringstream iss;
    if(!(argc >= 2)){
        cout << "\nINVALID ARGUMENTS.\nexiting...\n\n";
             return 0; //exit the program
    }

     if (argc > 2){
         prefix = argv[1];
         string option;
         iss.str(argv[2]); //convert char sequence to string for comparision
         iss >> option;
        
         if(option=="-d"){
             diffMap = true;
             i = stoi(argv[3]); //convert string input to int
             j = stoi(argv[4]);
             output_filename = argv[5];
         }
         else if(option=="-x"){
             extract = true;
             i = stoi(argv[3]); //convert string input to int
             j = 0;
             output_filename = argv[4];
         } else {

             cout << "\nINVALID ARGUMENTS.\nexiting...\n\n";
             return 0; //exit the program
         }
         
     }else{
         prefix = argv[1];
     }



    return 0;
}