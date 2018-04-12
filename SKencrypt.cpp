/* Justin Penny 11126992
 * CSCE 4550 - term project
 * 
 * This program pairs with SKdecrypt.cpp
 * This program is a Secret Key encryption program that converts a text document into a number string using a 3 digit key specified by the user
 * If this key is correctlly entered while running SKdecrypt.cpp then the decrypted message will be written to a file.
 * The 3 digit key serves to lock to file and also to determine the level of obfuscation desired by the user, the larger each digit of the 
 * 3 digit code is, the more secure the data will be. This security comes at a cost of increasing the file size of the encrypted data. 
 * For academic purposes, this program and its decryption counterpart only accept entries of 100,000 characters.
 * 
 * To run this program, compile it with 'g++ Skencrypt' and follow the instructions in the terminal once executed.
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
#include <sstream>
#include <string>

using namespace std;
int main()
{
    /* srand and randunm are used to generate filler numbers in my encrypted data, the pattern ints are used to keep track of the random numbers
     * and feed them into the encrypted data, effectivly obfuscating it.
     * */
	srand (time(NULL)); 
	long randnum = 0; 
	
	int pattern = 0; 
	int pattern1 = 0; 
	int pattern2 = 0;
	int pattern3 = 0;
	int temp = 0;
	int patCount = 1;// used to loop the pattern entered above from 1 to 3 repeatedly
	
	int num = 0;
	int i = 0;
	
	char filename[100]; // input string to be encrypted
    char phrase[100000]; // max length of file that can be encrypted
	
    vector<int> vct; // the vector that will hold the results of my encryption
    
	// standard file i/o
	cout << "Enter the name of a file to decrypt\n";
    cin >> filename;
    fstream myfile (filename);
    if(!myfile.is_open()){
        cout << "Error opening file\n";
        return -1;
    }
    
    cout << "Enter a 3 digit key to encrypt the contents of the file\n";
    cin >> pattern;
	
	pattern1 = pattern / 100;
	pattern2 = (pattern % 100)/10;
	pattern3 = pattern % 10;
	
    /* This is where the encryption happens. I convert all 2 digit characters to their coresponding ascii values
     * everything above or below 2 digits is converted into a space.
     * In order to make the file hard to decypher, the 3 digit key provided by the user will generate filler integers
     * that go inbetween the ascii values that represent text. 
     * */
    while(myfile)
		{
            phrase[temp++] = myfile.get();
			randnum = rand()%899999999 + 100000000;
			
			if(patCount > 3) // this cycles through the 3 pattern elements in sequence
			{
				patCount = patCount - 3;
			}
			
			switch (patCount){ // assigns num the corresponding pattern value
				case 1: num = pattern1; break;
				case 2: num = pattern2; break;
				case 3: num = pattern3; break;
			}
			
			int b = phrase[i];
				
				if(b < 65)
				{
                    if(b > 46 && b < 58)
                    {
                        // do nothing for numbers
                    }
                    else if (b == 10)
                    {
                        // do nothing for newline
                    }
                    else{
                        b = 32;
                    }
				}
				if(b > 96 && b < 123)
				{
					b = b-32;
				}
				if(b > 122)
				{
					b = 32;
				}
			vct.push_back (b);
				if(num > 0) // skips generating a random number if the pattern num is 0
				{
				vct.push_back (randnum / pow(10, (9-num))); // creates 3 random #s if the pattern num is 3 and so on.
				}
			i++;
			patCount++;
		};

	// printing the encrypted data contained in the vector to the output file
    ofstream outfile;
    outfile.open("ENCRYPTED_DATA.TXT");
	
	vector<int>::iterator start = vct.begin();
	while(start != vct.end())
	{
		outfile << *start;
        start++;
	}
    cout << "Encrypted message was written to ENCRYPTED_DATA.TXT\n";
    myfile.close();
    outfile.close();
	return 0;
}
