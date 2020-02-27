#include "VolImageMan.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class VolImageMan {


private: // private members
    int width, height, stacks; // width and height of image stack 
    std::vector<unsigned char**> slices; // data for each slice, in order
public: // public members
    VolImageMan(){}; // default constructor - define in .cpp
    ~VolImageMan(){}; // destructor - define in .cpp file
// populate the object with images in stack and //set member variables define in .cpp
bool readImages(std::string baseName){
  
   for(int i =0; i< stacks; i++){
        slices.push_back(new u_char *[height]); //allocate array of * chars with number of rows (height) as dimension
        for(int j =0; j< height; j++){
        slices[i][j] = new u_char[width];    
     }
   }


//    ifstream ifs;
//    ifs.open("../raws/"+baseName+"0.raw"); //try to open file and catch error
//     if(!ifs){
//         cerr<<"\nfile open failed.\nexiting...";
//         exit(0);
//     }else{
//         ifs.close();
//         for(int i = 0; i < stacks; i++){
//             string filename = "../raws/"+baseName+to_string(i)+".raw";
//             ifs.open(filename);
//             string line;
//             getline(ifs, line, '\n');
//             cout << line
            

            
//         }

//     }
//     ifs.close();
   

   


    
   

}
   // compute difference map and write out;  define in .cpp
void diffmap(int sliceI, int sliceJ, std::string output_prefix); // extract slice sliceId and write to output - define in .cpp
void extract(int sliceId, std::string output_prefix);
// number of bytes uses to store image data bytes //and pointers (ignore vector<> container, dims etc) 

void readHeader(string filename){
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

        cout << "\nNumber of images: " << stacks<<endl;
        cout << "Number of bytes required: " << volImageSize() << endl; //The dimension is how many bytes we need
    }
}
int volImageSize(void){
    return stacks*width*height;
}; // define in .cpp

};