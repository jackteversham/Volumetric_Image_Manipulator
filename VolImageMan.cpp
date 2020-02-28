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
    VolImageMan(){
        width = 0;
        height = 0;
    } // default constructor - define in .cpp
    ~VolImageMan(){
       for(int i=0; i < slices.size(); i++){
             for(int j=1; j < height; j++){
                delete [] slices[i][j]; //delete pointers to rows
             } 
          delete [] slices[i]; //delete pointers to images
       }
       cout << endl << "Cleaning up...\nMemory Freed!"<<endl;  
    }
    // destructor - define in .cpp file
// populate the object with images in stack and //set member variables define in .cpp
bool readImages(std::string baseName){

   ifstream ifs;
   ifs.open("../raws/"+baseName+"0.raw", ios::binary); //try to open binary file and catch error
    if(!ifs){
        cerr<<"\nfile open failed.\nexiting...";
        exit(0);
    }else{
        ifs.close();
        for(int i = 0; i < stacks; i++){  // FOR EACH STACK
            string filename = "../raws/"+baseName+to_string(i)+".raw"; //open the .raw file 0-122
            ifs.open(filename, ios::binary);//open the file

            unsigned char ** slice = new unsigned char * [height];
            
            int rowCounter = 0;
            while (rowCounter<height) //READ UNTIL END OF RAW FILE REACHED
            {  
                unsigned char *buf = new unsigned char[width]; 
                ifs.read((char *)buf, width);
                slice[rowCounter] = buf; 
                rowCounter++;
            }   
            slices.push_back(slice);  
            ifs.close(); //close each time because we reopen the next raw file each time

             std::bitset<8> x(slices[i][0][128]); //convert to binary value
             cout <<i<<":"<< x << endl;
        }
     }
     ifs.close(); //ensure file stream is closed
}

   // compute difference map and write out;  define in .cpp
void diffmap(int sliceI, int sliceJ, std::string output_prefix){

     //  (unsigned char)(abs((float)volume[i][r][c] - (float)volume[j][r][c])/2)
    std::vector<unsigned char> differenceMap;

    unsigned char ** islice = slices[sliceI];
    unsigned char ** j = slices[sliceJ];

    for(int i = 0; i < height; i++){

        for(int j= 0; j< width; j++){
           unsigned char  out = islice[i][j];
           std::bitset<8> x(out); //convert to binary value
           cout << x << endl;
           
        }
   }





} // extract slice sliceId and write to output - define in .cpp
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
        cout << height << endl << width << endl;
    }
}
int volImageSize(void){
    return stacks*32 + stacks*height*32 + stacks*width * height; //32 bytes for a pointer and 1 byte per value
}; // define in .cpp

};