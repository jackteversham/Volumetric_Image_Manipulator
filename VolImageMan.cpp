#include "VolImageMan.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cmath>


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
            //  std::bitset<8> x(slices[i][0][128]); //convert to binary value
            //  cout <<i<<":"<< x << endl;
        }
     }
     ifs.close(); //ensure file stream is closed
}

   // compute difference map and write out;  define in .cpp
void diffmap(int sliceI, int sliceJ, std::string output_prefix){

   ofstream headerOutputStream;
   string filename = "../out/"+output_prefix+".data";
   headerOutputStream.open(filename);
   
   
    string header = to_string(width)+" "+to_string(height)+" 1";
    headerOutputStream.write(header.c_str(), header.length());
   
   headerOutputStream.close();

     //  (unsigned char)(abs((float)volume[i][r][c] - (float)volume[j][r][c])/2)
   ofstream fileOutputStream;
   filename = "../out/"+output_prefix+".raw";
   fileOutputStream.open(filename, ios::binary);

    unsigned char ** islice = slices[sliceI]; //find the sliceI
    unsigned char ** jslice = slices[sliceJ];//find sliceJ

    unsigned char out[width*height];
    int index = 0;

    for(int i = 0; i < height; i++){
        for(int j= 0; j< width; j++){
            
           out[index] = (unsigned char )(abs((float)islice[i][j]-(float)jslice[i][j])/2.0);
        //    std::bitset<8> x(out[index]); //convert to binary value
        //    cout << x << endl;
           index++;
        }
   }
   fileOutputStream.write((char*)out, sizeof(out)); //write to output file
   fileOutputStream.close();
} 

// extract slice sliceId and write to output - define in .cpp
void extract(int sliceId, std::string output_prefix){

   ofstream headerOutputStream;
   string filename = "../out/"+output_prefix+".data";
   headerOutputStream.open(filename);
   
   
    string header = to_string(width)+" "+to_string(height)+" 1";
    headerOutputStream.write(header.c_str(), header.length());
   
   headerOutputStream.close();

   ofstream fileOutputStream;
   filename = "../out/"+output_prefix+".raw";
   fileOutputStream.open(filename, ios::binary);
   
    unsigned char ** slice = slices[sliceId]; //find the sliceI
    //int counter = 0;
    unsigned char out[width*height];
    int index = 0;

    for(int i = 0; i < height; i++){

        for(int j= 0; j< width; j++){
           out[index] = slice[i][j]; 
        //    std::bitset<8> x(out[index]); //convert to binary value
        //    cout << x << endl;
           index++;
        }
   }
   fileOutputStream.write((char*)out, sizeof(out)); //write to output file
   fileOutputStream.close();
   //cout << sizeof(out)<<endl;
    
}


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
        istringstream ss(line); //create a string stream with the line of dimensions
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
// number of bytes uses to store image data bytes //and pointers (ignore vector<> container, dims etc) 
int volImageSize(void){
    int bytes=0;
    for(int i = 0; i< stacks; i++){
        bytes += sizeof(slices[i]);
        for(int j = 0; j<height; j++){
            bytes += sizeof(slices[i][j]);
            bytes += width; //add width since each element is 1 byte
        }
    }
    return bytes;
};

};