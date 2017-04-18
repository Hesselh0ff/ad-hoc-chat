/*
 * Security.cpp
 *
 */

#include "Security.h"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <functional>



Security::Security() {
}

Security::~Security() {
}

/*
 * This appears to be a simple encryption and decryption algorithm
 * http://stackoverflow.com/questions/10005124/public-private-key-encryption-tutorials
 */

//On beforehand there are some includes needed for this algorithm to work
const int encryption_key = 25; //can be any random number
const int decrytpion_key = /*key should be known to all users*/ 80;
const int n = 423; //a random number to make it more random.

struct crypt : std::binary_function<int, int, int> { //creates a function object with 2 arguments
        int operator()(int input, int key) const {	//This is what should happen with the 2 arguments
                int result = 1;
                for(int i=0; i<key; i++) {
                        result = result * input; //Since the result is 1, the new result will just be the input
                        result = result % n;
                }
                return result;
        }
}; //end struct

//Since the message has to be known by both the encrypt/decrypt function
//It should be placed outside those two functions.

std::string /*Message that has to be send*/ message = "Fetch from Packet.cpp(?), the sended message should be called here.";
std::vector<int>encrypted; //The vector in which the encrypted message is stored.

void Security::encrypt(){
        //Encryption
        std::transform(	message.begin(),
                                        message.end(),
                                        std::back_inserter(encrypted),	//Store the encrypted message in the vector 'encrypted' .
                                        std::bind2nd(crypt(), encryption_key) //binds the encryption key to second argument(int key) after running crypt() on it.
                                        ); //Now the message should be encrypted with the
                                           //and should be encrypted with encryption key
}

void Security::decrypt(){
    //Decryption
        std::transform( encrypted.begin(),		//reads from the vector with the encrypted message
                                        encrypted.end(),
                                        std::ostream_iterator<char>(std::cout, ""),	//Not sure about what is happening here _:)
                                        std::bind2nd(crypt(), decrytpion_key)
                                        ); //Now the message is decrypted and transformed back
                                           //into characters.
        std::cout << "\n";
}

std::string Security::getMD5sum(std::string str){
    /* Get the MD5 sum of a string */
    MD5 md5;
    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());

    std::string ret_str = md5.digestString(cstr);
    delete cstr;
    return ret_str;
}

std::string Security::getFileMD5(std::string path){
    /* Get the MD5 sum of a file */
    MD5 md5;
    char *cstr = new char[path.length() + 1];
    strcpy(cstr, path.c_str());

    std::string ret_str = md5.digestFile(cstr);
    delete cstr;
    return ret_str;
}
