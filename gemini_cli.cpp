// GeminiCLI Suite - Chat + Summarizer + Email Generator + Resume Reviewer + Code Assistant
// Features: Chat, summarize text, generate emails, review resumes, and get code help

#include <iostream>
#include <string>
#include <fstream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

// Callback for handling response
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

string sendToGemini(const string& prompt, const string& apiKey) {
    CURL* curl = curl_easy_init();
    string response;

    if (curl) {
        string url = "https://generativelanguage.googleapis.com/v1beta/models/gemini-2.0-flash:generateContent?key=" + apiKey;

        json body = {
            {"contents", {
                {"parts", {{"text", prompt}}}
            }}
        };

        string jsonData = body.dump();

        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    try {
        auto jsonResp = json::parse(response);
        return jsonResp["candidates"][0]["content"]["parts"][0]["text"];
    } catch (...) {
        return "Error: Could not parse Gemini response.";
    }
}

int main() {
    string apiKey;
    cout << "Enter your Gemini API key: ";
    getline(cin, apiKey);

    cout << "\nWelcome to Gemini CLI Suite!\n";
    cout << "Choose mode:\n1. Chat\n2. Summarize\n3. Email Generator\n4. Resume Reviewer\n5. Code Assistant\n> ";
    int mode;
    cin >> mode;
    cin.ignore(); // clear newline

    if (mode == 1) {
        cout << "\nChat mode started. Type 'exit' to quit.\n";
        while (true) {
            string prompt;
            cout << "\nYou: ";
            getline(cin, prompt);
            if (prompt == "exit") break;
            string reply = sendToGemini(prompt, apiKey);
            cout << "Gemini: " << reply << endl;
        }

    } else if (mode == 2) {
        cout << "\nPaste the text to summarize (type 'END' on a new line to finish):\n";
        string line, longText;
        while (getline(cin, line)) {
            if (line == "END") break;
            longText += line + "\n";
        }

        string prompt = "Summarize the following text:\n" + longText;
        string reply = sendToGemini(prompt, apiKey);

        cout << "\nSummary:\n" << reply << endl;

        ofstream outFile("summary.txt");
        if (outFile.is_open()) {
            outFile << reply;
            outFile.close();
            cout << "\n✅ Summary saved to summary.txt\n";
        } else {
            cout << "\n⚠️ Could not save summary to file.\n";
        }

    } else if (mode == 3) {
        string subject, details;
        cout << "\nEnter email subject: ";
        getline(cin, subject);
        cout << "Enter details or purpose of the email:\n";
        getline(cin, details);

        string prompt = "Write a professional email with subject: '" + subject + "'. The details are: " + details;
        string reply = sendToGemini(prompt, apiKey);

        cout << "\nGenerated Email:\n" << reply << endl;

        ofstream outFile("email.txt");
        if (outFile.is_open()) {
            outFile << reply;
            outFile.close();
            cout << "\n✅ Email saved to email.txt\n";
        } else {
            cout << "\n⚠️ Could not save email to file.\n";
        }

    } else if (mode == 4) {
        cout << "\nPaste your resume content (type 'END' on a new line to finish):\n";
        string line, resumeText;
        while (getline(cin, line)) {
            if (line == "END") break;
            resumeText += line + "\n";
        }

        string prompt = "Review the following resume and provide constructive feedback and improvement suggestions:\n" + resumeText;
        string reply = sendToGemini(prompt, apiKey);

        cout << "\nResume Feedback:\n" << reply << endl;

        ofstream outFile("resume_review.txt");
        if (outFile.is_open()) {
            outFile << reply;
            outFile.close();
            cout << "\n✅ Feedback saved to resume_review.txt\n";
        } else {
            cout << "\n⚠️ Could not save feedback to file.\n";
        }

    } else if (mode == 5) {
        cout << "\nPaste your code snippet or problem (type 'END' on a new line to finish):\n";
        string line, codeText;
        while (getline(cin, line)) {
            if (line == "END") break;
            codeText += line + "\n";
        }

        string prompt = "Explain or help debug the following code:\n" + codeText;
        string reply = sendToGemini(prompt, apiKey);

        cout << "\nCode Assistant Response:\n" << reply << endl;

        ofstream outFile("code_assistant.txt");
        if (outFile.is_open()) {
            outFile << reply;
            outFile.close();
            cout << "\n✅ Response saved to code_assistant.txt\n";
        } else {
            cout << "\n⚠️ Could not save response to file.\n";
        }

    } else {
        cout << "\nInvalid option. Exiting.\n";
    }

    cout << "\nSession ended.\n";
    return 0;
}
