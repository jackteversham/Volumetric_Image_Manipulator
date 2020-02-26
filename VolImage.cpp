
#include "VolImage.h"
#include "VolImageMan.cpp"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>





int main(int argc, char ** argv){
    //DEAL WITH COMMAND LINE ARGUMENTS
     string prefix;
     string output_filename;
     bool diffMap;
     bool extract;
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
     int width, height, stacks;
     string filename = prefix +".data";
     readHeader(width, height, stacks, filename);





    return 0;
}

void readHeader(int width, int height, int stacks, string filename){
    string line;
    ifstream ifs;
   
    ifs.open("../raws/"+filename); //try to open file and catch error
    if(!ifs){
        cerr<<"\nfile open failed.\nexiting...";
        exit(0);
    }else{
        getline(ifs, line, '\n');
        //cout << line << endl;

        vector<int> dim;
        string token;
        istringstream ss(line); //crete a string stream with the line of dimensions
        while (getline(ss, token, ' '))
        {
            dim.push_back(stoi(token));
        }
        //assign dimensions
        width = dim[0];
        height = dim[1];
        stacks = dim[2];

        cout << width << height << stacks << endl;
        
    }
}


