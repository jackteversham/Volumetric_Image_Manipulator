
#include "VolImage.h"
#include "VolImageMan.h"
#include "VolImageMan.cpp"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>





int main(int argc, char ** argv){
    //DEAL WITH COMMAND LINE ARGUMENTS
     string prefix;
     string output_filename;
     bool diffMap=false;
     bool extract=false;
     int i, j;
    
    if(!(argc >= 2)){ //the file prefix is compulsory
        cout << "\nINVALID ARGUMENTS.\nexiting...\n\n";
             return 0; //exit the program
    }

     if (argc > 2){           //NOTE: CAN ONLY DO ONE INVOCATION OF EITHER -d OR -x EACH RUN
         prefix = argv[1];

         string option = string(argv[2]);
        
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
         } else { //if option is -d or -x then invalid arguments and exit
             cout << "\nINVALID ARGUMENTS.\nexiting...\n\n";
             return 0; //exit the program
             }  
         
     }else{
         prefix = argv[1];
         diffMap = false;
         extract = false;
     }  
     //END COMMAND LINE INTEFRACE

     //READ HEADER FILE
     string filename = prefix +".data";
     //readHeader(width, height, stacks, filename);

     
     VolImageMan imageManipulator;
     imageManipulator.readHeader(filename);
     imageManipulator.readImages(prefix);

    if(extract){
        imageManipulator.extract(i,output_filename);
        cout << "\nExtracting slice "<<i<<" and writing it to "<<output_filename<<".raw with header file "<< output_filename<<".data located in the 'out' folder.\n";

    }
    if(diffMap){
        imageManipulator.diffmap(i,j,output_filename);
        cout << "\nComputing difference map between slice " <<i<< " and slice "<<j<< ". Output written to "<<output_filename<<".raw with header file "<<output_filename <<".data located in 'out' folder.\n";

    }
     
     //imageManipulator.~VolImageMan();
     

    return 0;
}




