This submisssion contains a SKencrypt.cpp program to encrypt any given text file.
This submission contaitns a SKdecrypt.cpp program to decrypt any given text file (it will ask to decrypt the encrypted file by default).

As per my design, my program will convert all letters to their uppercase form and will discard all special characters
with an ascii value of > 99, all integers are preserved.
By doing this, my program allows a user to choose a 3 digit code that can generate powerfully but lenghty encryption, or smaller and weaker
encryption. The smaller each digit of the 3 digit key is, the weaker and the encryption will be.

For example; a code of 000 will be weaker but more compact than a code of 345 in terms of the generated encryption file contents.
