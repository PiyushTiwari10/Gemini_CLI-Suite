# Gemini CLI Suite

A powerful command-line interface tool that leverages Google's Gemini AI to provide multiple AI-powered features in one convenient application.

## 🚀 Features

### 1. **Chat Mode**
- Interactive conversation with Gemini AI
- Type 'exit' to quit the chat session
- Perfect for general questions, brainstorming, or casual conversation

### 2. **Text Summarizer**
- Summarize long texts, articles, or documents
- Input text by pasting and type 'END' to finish
- Automatically saves summary to `summary.txt`

### 3. **Email Generator**
- Generate professional emails based on subject and details
- Provides well-structured, professional email content
- Saves generated emails to `email.txt`

### 4. **Resume Reviewer**
- Get constructive feedback on your resume
- Receive improvement suggestions and optimization tips
- Saves feedback to `resume_review.txt`

### 5. **Code Assistant**
- Get help with code debugging and explanation
- Paste code snippets for analysis and improvement suggestions
- Saves responses to `code_assistant.txt`

## 📋 Prerequisites

Before running this application, you'll need:

- **C++ Compiler** (GCC, Clang, or MSVC)
- **libcurl** - HTTP client library
- **nlohmann/json** - JSON parsing library
- **Gemini API Key** - Get one from [Google AI Studio](https://makersuite.google.com/app/apikey)

## 🔧 Installation

### Step 1: Install Dependencies

#### Ubuntu/Debian:
```bash
sudo apt update
sudo apt install libcurl4-openssl-dev nlohmann-json3-dev build-essential
```

#### macOS (using Homebrew):
```bash
brew install curl nlohmann-json
```

#### Windows (using vcpkg):
```bash
vcpkg install curl nlohmann-json
```

### Step 2: Compile the Application

```bash
g++ -o gemini_cli gemini_cli.cpp -lcurl -std=c++17
```

### Step 3: Get Your API Key

1. Visit [Google AI Studio](https://makersuite.google.com/app/apikey)
2. Sign in with your Google account
3. Create a new API key
4. Copy the key for use in the application

## 🚀 Getting Started

### 1. Run the Application
```bash
./gemini_cli
```

### 2. Enter Your API Key
When prompted, paste your Gemini API key:
```
Enter your Gemini API key: YOUR_API_KEY_HERE
```

### 3. Choose Your Mode
Select from the available options:
```
Choose mode:
1. Chat
2. Summarize
3. Email Generator
4. Resume Reviewer
5. Code Assistant
>
```

## 📖 Usage Examples

### Chat Mode
```
You: What are the benefits of learning C++?
Gemini: [AI response about C++ benefits]
```

### Summarizer Mode
```
Paste the text to summarize (type 'END' on a new line to finish):
[Your text here]
END

Summary:
[Generated summary]

✅ Summary saved to summary.txt
```

### Email Generator
```
Enter email subject: Meeting Request
Enter details or purpose of the email: I need to schedule a meeting with the development team

Generated Email:
[Professional email content]

✅ Email saved to email.txt
```

### Resume Reviewer
```
Paste your resume content (type 'END' on a new line to finish):
[Your resume content]
END

Resume Feedback:
[Constructive feedback and suggestions]

✅ Feedback saved to resume_review.txt
```

### Code Assistant
```
Paste your code snippet or problem (type 'END' on a new line to finish):
[Your code here]
END

Code Assistant Response:
[Code explanation and debugging help]

✅ Response saved to code_assistant.txt
```

## 📁 Output Files

The application automatically saves responses to the following files:
- `summary.txt` - Generated summaries
- `email.txt` - Generated emails
- `resume_review.txt` - Resume feedback
- `code_assistant.txt` - Code assistance responses

## 🔒 Security Notes

- Your API key is only used for the current session
- No API keys are stored permanently
- All API calls are made securely via HTTPS
- Generated files are saved locally on your machine

## 🛠️ Troubleshooting

### Common Issues:

1. **Compilation Errors**
   - Ensure all dependencies are installed
   - Use C++17 or later: `-std=c++17`

2. **API Key Issues**
   - Verify your API key is correct
   - Ensure you have sufficient API quota
   - Check your internet connection

3. **File Permission Errors**
   - Ensure you have write permissions in the current directory
   - Check available disk space

## 🤝 Contributing

Feel free to submit issues, feature requests, or pull requests to improve this tool.

## 📄 License

This project is open source and available under the MIT License.

## 🙏 Acknowledgments

- Google Gemini AI for providing the underlying AI capabilities
- libcurl for HTTP communication
- nlohmann/json for JSON parsing

---

**Happy coding with Gemini CLI Suite! 🎉** 