// GeminiCLI Suite - Chat + Summarizer + Email Generator + Resume Reviewer + Code Assistant
// Features: Chat, summarize text, generate emails, review resumes, and get code help

#include <iostream>
#include <string>
#include <fstream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Callback for handling response
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

std::string sendToGemini(const std::string& prompt, const std::string& apiKey) {
    CURL* curl = curl_easy_init();
    std::string response;

    if (curl) {
        std::string url = "https://generativelanguage.googleapis.com/v1beta/models/gemini-2.0-flash:generateContent?key=" + apiKey;

        json body = {
            {"contents", {
                {"parts", {{"text", prompt}}}
            }}
        };

        std::string jsonData = body.dump();

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
    std::string apiKey;
    std::cout << "Enter your Gemini API key: ";
    std::getline(std::cin, apiKey);

    std::cout << "\nWelcome to Gemini CLI Suite!\n";
    std::cout << "Choose mode:\n1. Chat\n2. Summarize\n3. Email Generator\n4. Resume Reviewer\n5. Code Assistant\n> ";
    int mode;
    std::cin >> mode;
    std::cin.ignore(); // clear newline

    if (mode == 1) {
        std::cout << "\nChat mode started. Type 'exit' to quit.\n";
        while (true) {
            std::string prompt;
            std::cout << "\nYou: ";
            std::getline(std::cin, prompt);
            if (prompt == "exit") break;
            std::string reply = sendToGemini(prompt, apiKey);
            std::cout << "Gemini: " << reply << std::endl;
        }

    } else if (mode == 2) {
        std::cout << "\nPaste the text to summarize (type 'END' on a new line to finish):\n";
        std::string line, longText;
        while (std::getline(std::cin, line)) {
            if (line == "END") break;
            longText += line + "\n";
        }

        std::string prompt = "Summarize the following text:\n" + longText;
        std::string reply = sendToGemini(prompt, apiKey);

        std::cout << "\nSummary:\n" << reply << std::endl;

        std::ofstream outFile("summary.txt");
        if (outFile.is_open()) {
            outFile << reply;
            outFile.close();
            std::cout << "\n✅ Summary saved to summary.txt\n";
        } else {
            std::cout << "\n⚠️ Could not save summary to file.\n";
        }

    } else if (mode == 3) {
        std::string subject, details;
        std::cout << "\nEnter email subject: ";
        std::getline(std::cin, subject);
        std::cout << "Enter details or purpose of the email:\n";
        std::getline(std::cin, details);

        std::string prompt = "Write a professional email with subject: '" + subject + "'. The details are: " + details;
        std::string reply = sendToGemini(prompt, apiKey);

        std::cout << "\nGenerated Email:\n" << reply << std::endl;

        std::ofstream outFile("email.txt");
        if (outFile.is_open()) {
            outFile << reply;
            outFile.close();
            std::cout << "\n✅ Email saved to email.txt\n";
        } else {
            std::cout << "\n⚠️ Could not save email to file.\n";
        }

    } else if (mode == 4) {
        std::cout << "\nPaste your resume content (type 'END' on a new line to finish):\n";
        std::string line, resumeText;
        while (std::getline(std::cin, line)) {
            if (line == "END") break;
            resumeText += line + "\n";
        }

        std::string prompt = "Review the following resume and provide constructive feedback and improvement suggestions:\n" + resumeText;
        std::string reply = sendToGemini(prompt, apiKey);

        std::cout << "\nResume Feedback:\n" << reply << std::endl;

        std::ofstream outFile("resume_review.txt");
        if (outFile.is_open()) {
            outFile << reply;
            outFile.close();
            std::cout << "\n✅ Feedback saved to resume_review.txt\n";
        } else {
            std::cout << "\n⚠️ Could not save feedback to file.\n";
        }

    } else if (mode == 5) {
        std::cout << "\nPaste your code snippet or problem (type 'END' on a new line to finish):\n";
        std::string line, codeText;
        while (std::getline(std::cin, line)) {
            if (line == "END") break;
            codeText += line + "\n";
        }

        std::string prompt = "Explain or help debug the following code:\n" + codeText;
        std::string reply = sendToGemini(prompt, apiKey);

        std::cout << "\nCode Assistant Response:\n" << reply << std::endl;

        std::ofstream outFile("code_assistant.txt");
        if (outFile.is_open()) {
            outFile << reply;
            outFile.close();
            std::cout << "\n✅ Response saved to code_assistant.txt\n";
        } else {
            std::cout << "\n⚠️ Could not save response to file.\n";
        }

    } else {
        std::cout << "\nInvalid option. Exiting.\n";
    }

    std::cout << "\nSession ended.\n";
    return 0;
}
