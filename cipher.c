//
// Created by Daniel on 9/26/2017.
//

/*
 *  EE312 Assignment 4.
 *  On my honor, Daniel Canterino, this programming assignment is my own work.
 *
 *  This program demonstrates a transposition cipher.
 *  A cipher is an algorithm to encrypt or decrypt a message.
 *
 *  Name: Daniel Canterino
 *  email address: dnc1231@verizon.net
 *  UTEID: djc3323
 *  Section 5 digit ID: 16115
 *  Number of slip days used on this assignment: 0
 *. Total number of slip days used this semester: 0
 */

#include <stdio.h>
const int MAX_ROWS=6;

void introCipher();
void userInput(char arr[]);
void encryptNoPad(char message[], int size);
int length(char arr[]);
void addPad(char message[], int size);
void padEncrypt(char cipher[], int size, int row);
void introDecrypt();
void decrypt(char message[], int size);
void decryptPad(char message[], int size, int row);

int main(){
    char msg[158];
    char decryption[158];
    introCipher();
    userInput(msg);
    encryptNoPad(msg, length(msg));
    addPad(msg, length(msg));
    introDecrypt();
    userInput(decryption);
    decrypt(decryption, length(decryption));
}

/*intro Cipher prints text detailing what this program will do and how it will encrypt and decrypt a
 * string entered by the user*/
void introCipher(){
    printf("This program demonstrates a transposition cipher.\n"
                   "A cipher is an algorithm to encrypt or decrypt a message.\n"
                   "\n"
                   "This program will demonstrate encrypting a message with\n"
                   "a columnar transposition cipher both with and without\n"
                   "padding characters. The program will then decrypt a message\n"
                   "assuming it was encrypted with a columnar transposition cipher\n"
                   "with padding.\n\n"
                   "\n"
                   "A demonstration of encrypting with a columnar transposition cipher:\n\n"
                   "\n"
                   "Enter the message to encrypt:");
}

/*user input takes the input from the line and inputs it into an array passed to it*/
void userInput(char arr[]){
    fgets(arr, 158, stdin);
}

/*length counts the length of the array passed to assuming it is a
 * string with a new line entered at the end of it*/
int length(char arr[]){
    int count=0;
    int i=0;
    while (arr[i] != 0){
        count++;
        i++;
    }
    return (count-1);//-1 gets rid of new line
}

/*encryptNoPad encrypts a given array passed to it based off columnar transposition
 * cipher and then prints this new encrypted string to the console*/
void encryptNoPad(char message[], int size){
    int i = 0;
    int k = 0;
    int row = 2;
    char cipher[size + 1];
    cipher[size] = '\0';//null terminates the array at the length of the message
    printf( "\nMessage encrypted with columnar transposition cipher and no padding.\n" );
    while (row <= MAX_ROWS){
        while (i < size) {
            for (int j = k; j < size; j += row) {
                cipher[i] = message[j];
                i++;
            }
            k++;
        }
        printf("Encrypted with %d rows: %s\n" ,row, cipher);
        row++;
        i = 0;
        k = 0;
    }
}

/*addPad will pad an array passed to it with the character 'X' based off how many rows the string needs to
 * padded for encryption for and then prints the padded non encrypted string to the console. Additionally it
 * passes this padded encrypted message to the function padEncrypt for the padded string to be encrypted and printed*/
void addPad(char message[], int size){
    int row = 2;
    char cipher[158];
    int i;
    int temp;
    cipher[size] = '\0';
    printf( "\nMessage encrypted with columnar transposition cipher and padding.\n\n" );
    while (row <= MAX_ROWS){
        i = 0;
        temp = size;
        while (i < size){
            cipher[i] = message[i];
            i++;
        }
        while (temp % row != 0){
            cipher[temp] = 'X';
            temp++;
        }
        cipher[temp] = '\0';
        printf("Clear text padded for %d rows: %s\n", row, cipher);
        padEncrypt(cipher, temp, row);
        row++;
    }
}

/*padEncrypt will take a padded string and encrypt it based off the current row passed to it and the
 * size of the padded string. This padded encrypted string is then printed to the console*/
void padEncrypt(char cipher[], int size, int row){
    int i = 0;
    int k = 0;
    char encrypt[158];
    encrypt[size] = '\0';
    while (i < size) {
        for (int j = k; j < size; j += row) {
            encrypt[i] = cipher[j];
            i++;
        }
        k++;
    }
    printf("Encrypted with %d rows: %s\n\n" ,row, encrypt);
}

/*introDecrypt prints an introduction to how this program will now decrypt a message input by the
 * user and then prompts the user
 * for a string input*/
void introDecrypt(){
    printf("\nA demonstration of decrypting with a columnar transposition cipher.\n"
                   "If the length of the message is not a multiple of the number of rows\n"
                   "it will be padded which may throw off the decryption.\n"
                   "\n"
                   "Enter the message to decrypt: ");
}

/*decrypt will take an array of characters and decrypt it based off columnar decryption. It first ensures that
 * the string entered is padded for the current row to be decrypted by and then passes that newly padded string to
 * decryptPad for decyrption and printing of the string*/
void decrypt(char message[], int size) {
    int i = 0;
    int temp;
    int row = 2;
    char padCopy[158];
    printf("\nMessage decrypted with a columnar transposition cipher:\n\n");
    while (row <= MAX_ROWS) {
        i = 0;
        temp = size;
        while (i < size){
            padCopy[i] = message[i];
            i++;
        }
        while (temp % row != 0){
            padCopy[temp] = 'X';
            temp++;
        }
        padCopy[temp] = '\0';
        printf("Encrypted text padded for %d rows: %s\n", row, padCopy);
        decryptPad(padCopy, temp, row);
        row++;
    }
}

/*decryptPad takes a padded string, its size, and the row for it to be decrypted by and decrypted in and decrypts it.
 * Then this newly decrypted string is printed to the console.*/
void decryptPad(char message[], int size, int row){
    int i = 0;
    int k = 0;
    char decrypt[158];
    while (i < size){
        for (int j = k; j < size; j += (size / row)){
            decrypt[i] = message[j];
            i++;
        }
        k++;
    }
    decrypt[i] = '\0';
    printf("Decrypted with %d rows: %s\n\n", row, decrypt);
}
