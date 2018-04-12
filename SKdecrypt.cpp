/* Justin Penny 11126992
 * CSCE 4550 - term project
 * 
 * This program pairs with SKencrypt.cpp
 * This program is a Secret Key decryption program that reads input from a previously encrypted file and converts it back to legible text
 * Due to the encryption/obfuscation method I chose, all text will be capitalized and most symbols are converted to spaces.
 * 
 * To use this program, simply compile it with 'g++ SKdecrypt.cpp' and follow the instructions in the terminal
 * */

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <time.h> 
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;
int main()
{
	int pattern = 0; 
	int pattern1 = 0; 
	int pattern2 = 0;
	int pattern3 = 0;
	int patCount = 1;// used to loop the pattern entered above from 1 to 3 repeatedly
	int num = 0; // used for loops
	int i = 0; // used for loops
	char phrase[100000]; // input string to be decrypted
	int b = 0; // stores the value to be passed into the vector 
    //char filename[100]; // input string to be decrypted
    string filename;
    char choice;
	
    vector<char> vct; // the vector that holds the output of the decryption
    
    // standard file i/o
    cout << "The file decrypted by default is ENCRYPTED_DATA.TXT\nIs this correct?\n[y] to continue, [n] to enter new file name\n";
    cin >> choice;
    
    if(choice == 'y' || choice == 'Y')
    {
        filename = "ENCRYPTED_DATA.TXT";
    }
    else if(choice == 'n' || choice == 'N'){
        cout << "Enter name of file to decrypt\n";
        cin >> filename;
    }
    else{
        cout << "ERROR: invalid input detected\n";
        return -1;
    }
    
	fstream myfile (filename);
        if(!myfile.is_open()){
            cout << "Error opening file\n";
            return -1;
        }
    
    // the secret key is entered here, if the incorrect key is entered then the data will all be scrambled
	cout << "Enter 3 digit pattern code\n";
	cin >> pattern;
	
	pattern1 = pattern / 100;
	pattern2 = (pattern % 100)/10;
	pattern3 = pattern % 10;
	
    // Decrypting the data here based on the pattern key
    myfile.getline(phrase,sizeof(phrase));
	while(phrase[i] != '\0')
		{
            
			if(patCount > 3) // this cycles through the 3 pattern elements in sequence
			{
				patCount = patCount - 3;
			}
			
			switch (patCount){ // assigns num the corresponding pattern value
				case 1: num = pattern1; break;
				case 2: num = pattern2; break;
				case 3: num = pattern3; break;
			}
			b = (phrase[i]*10 + phrase[i+1] + 16 - 32); // converting to the proper ascii values
			
			vct.push_back (b);
	
			i = i+2 + num;
			patCount++;
		}
		
	// printing the decrypted data containted in the vector to the output file
    ofstream outfile;
    outfile.open("DECRYPTED_DATA.TXT");
    
	vector<char>::iterator start = vct.begin();
	while(start != vct.end())
	{
        outfile << *start;
		start++;
	}
	cout << "Decrypted message was written to DECRYPTED_DATA.TXT\n";
    myfile.close();
    outfile.close();
	return 0;
}

