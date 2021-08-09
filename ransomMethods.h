#include <string>
#include "HTTPRequest.hpp"
//Function to read locations and push them into a vector.
bool getFileContents(std::string fileName, std::vector<std::string> & fileContents){  

    std::ifstream in(fileName);  
    if(!in){
        std::cerr << "Cannot open the File : " << fileName << std::endl;
        return false;
    }
    std::string str;    
    while (getline(in, str)){        
        if(str.size() > 0)
            fileContents.push_back(str);
    }    
    in.close();
    return true;
}

//Basic function to read all chars and increment them by one. 
void basicEncryptContent(std::string& content){
	for(char& chr : content){
		chr = chr + 1;
	}
}

//Basic function to read all chars and decrement them by one.
void basicDecryptContent(std::string& content){
	for(char& chr : content){
		chr = chr - 1;
	}
}


std::string get_request(std::string uri){
      try{
        
        http::Request request{uri};

        // send a get request
        const auto response = request.send("GET");      
        return std::string{response.body.begin(), response.body.end()};
        
    
    }
    catch (const std::exception& e){
        std::cerr << "Request failed, error: " << e.what() << '\n';
        return std::string{"Did not work"};
        
    } 
}


// *** TODO *** - PART 3
std::vector<std::string> checkExistingLocations(std::vector<std::string> & fileContents){
    return fileContents;
}