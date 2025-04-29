#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex> 
#include <sstream> 


using namespace std;

// Requirments:
// Develop a spam or ham (non-spam) email classifier using text analysis.
// 1. Read the email content from a file.
// 2. Remove special characters, HTML tags, and extra spaces.
// 3. Extract keywords or patterns often found in spam.
// 4. Classify the email as spam or ham 


// Todo today (4/29/25):
// add vector to store the label and message
// write function for training file (spam.csv)
// finish writing function for test file (email.txt)


// Function to read the email content from a file
string readEmailContent(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file: " << filePath << endl;
        return ""; // Return an empty string if the file cannot be opened
    }

    stringstream buffer;
    buffer << file.rdbuf(); // Read the entire file into the buffer
    file.close();

    return buffer.str(); // Return the full content as a string
}


// Function to preprocess the text (remove noise, tokenize, etc.)
string preprocessText(const string& text) {
    string cleanText = regex_replace(text, regex("<[^>]+>"), ""); // Remove HTML tags
    cleanText = regex_replace(cleanText, regex("[^a-zA-Z0-9\\s]"), ""); // Remove special characters
 
    
    return cleanText;
}




// Function to read test file
vector<pair<string, string>> emailData; // Vector to store label-message pairs
void loadTrainingData() {
    ifstream file("email.txt"); // Open the test file
    if (!file.is_open()) {
        cerr << "Error: Unable to open test file." << endl;
        return; // Exit if the file cannot be opened
    }

    string line;

    getline(file, line); // Skip header. So we can ignore the first line.

    while (getline(file, line)) { // Read each line
        // Find the position of the comma
        size_t commaPos = line.find(',');
        if (commaPos == string::npos) continue; // Skip if no comma is found

        // Extract label and message
        string label = line.substr(0, commaPos);
        string message = line.substr(commaPos + 1);

        // Add the label and message to the vector
        emailData.push_back(make_pair(label, message));
    }

    // Close the file
    file.close();
}

// Example: Print the stored data
void printEmailData() {
    for (const auto& entry : emailData) {
        cout << "Label: " << entry.first << ", Message: " << entry.second << endl;
    }
}



// Function to read training file
ifstream testFile("spam.csv"); // Open the spam csv file
int total = 0, correct = 0;

 


// Identify keywords or patterns often found in spam (e.g., "free", "click", "win").
vector<string> extractFeatures(const string& text) {
    // v1 use fixed list of spam keywords
    // v2 use regex to find spam patterns (e.g., "free", "click", "win"). case insensitive
    // v3 use mlpack to train a model on a dataset of spam and ham emails.
    vector<string> spamKeywords = {"free", "click", "win", "offer", "urgent", "limited time", "winner", "money", "No-Cost", "risk-free", "guaranteed", "act now", "Don't miss out", "customs", "package", "pay", "call", "free", "txt", "u", "ur", "mobile", "text", "claim", "stop", "reply"};

    vector<string> foundKeywords;
    for (const string& keyword : spamKeywords) {
        regex keywordRegex("\\b" + keyword + "\\b", regex_constants::icase); // Create a case-insensitive regex for the keyword
        if (regex_search(text, keywordRegex)) { // Check if the keyword is found using regex
            foundKeywords.push_back(keyword); // Add the keyword to the list
        }
    }
    cout << "Found keywords: " << foundKeywords.size() << endl; // Print the number of found keywords
    for (const string& keyword : foundKeywords) { 
        cout << keyword << " "; // Print the found keywords
    }
    cout << endl; // Print a new line
    return foundKeywords; // Return the list of found keywords

}



// Function to classify the email as spam or ham
bool classifyEmail(const vector<string>& features) {
    // v1 Simple classification logic.  if more than 2 keywords are found, classify as spam
    // v3 Use mlpack to train a model on a dataset of spam and ham emails.

    if (features.size() > 2) { 
        return true; // Classify as spam
    }
    // Otherwise, classify as ham
    return false;
}




int main() { 
    // v1: use list of spam keywords and find 3 or more in the text. Not case sensitive.
    // v2: use regex to find spam patterns (e.g., "free", "click", "win").
    // v3: use mlpack to train a model on a dataset of spam and ham emails.


    // 1. Load email Data (from file or user input)
    string emailContent;

    // 2. Preprocess Email (remove noise, tokenize, etc.)
    emailContent = readEmailContent("email.txt"); // Replace with your email file path

    // 3. Feature Extraction (keywords, patterns, etc.)
    string preprocessedText = preprocessText(emailContent); 
    // 4. Print email data (for debugging)
    printEmailData();

    // Extract features from the preprocessed text
    vector<string> features = extractFeatures(preprocessedText);

    // 5. Classification (Regex or ML model)
    bool isSpam = classifyEmail(features); // Classify the email based on the extracted features


    // 6. Output Result
    if (isSpam) { 
        cout << "This email is classified as spam." << endl;
    } else {
        cout << "This email is classified as ham." << endl;
    }

    return 0;
}