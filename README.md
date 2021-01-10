# Volumetric Image Manipulator using Raw Pointers

This project is a volumetric image tool using raw pointers, which can load a “stack” of 2D images and manipulate them as a group. Volumetric images are produced by many instruments, including radio astronomy telescopes and MRI machines used in medical imaging.

SOURCE CODE:
All source code is located in the 'src' folder.
 - VolImageMan.cpp contains the implementation of the program.
 - VolImage.cpp contains the main methods and makes calls to VolImageMan.

TO COMPILE and RUN:
- cd into the src folder and run the command make to compile the program.
- invoke the program using 1 of the following 3 invocations:

./volimage prefix -x i output_file_prefix             #Extraction
./volimage prefix -d i j output_file_prefix           #Difference Map
./volimage prefix -g 1 output_file_prefix             #Row Extraction

INPUT:
The program looks for input files, with the prefix specifed in the command line arguments, in the raws folder.

OUTPUT:
The output of the program will be output to the 'out' folder
