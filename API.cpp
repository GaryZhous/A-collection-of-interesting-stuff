#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <glog/logging.h>

// Struct to hold API response
struct User {
    int id;
    std::string name;
    std::string username;
    std::string email;
};

// libcurl callback to store response in a string
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main(int argc, char* argv[]) {
    // Initialize Google logging
    google::InitGoogleLogging(argv[0]);
    FLAGS_logtostderr = 1; // log to stderr instead of file
    LOG(INFO) << "Starting API call...";

    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        const char* url = "https://jsonplaceholder.typicode.com/users/1";
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            LOG(ERROR) << "curl_easy_perform() failed: " << curl_easy_strerror(res);
            return 1;
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    LOG(INFO) << "Raw JSON: " << readBuffer;

    // Parse JSON
    try {
        auto j = nlohmann::json::parse(readBuffer);
        User user {
            j.at("id").get<int>(),
            j.at("name").get<std::string>(),
            j.at("username").get<std::string>(),
            j.at("email").get<std::string>()
        };

        LOG(INFO) << "User parsed successfully!";
        std::cout << "ID: " << user.id << "\n"
                  << "Name: " << user.name << "\n"
                  << "Username: " << user.username << "\n"
                  << "Email: " << user.email << "\n";
    } catch (std::exception& e) {
        LOG(ERROR) << "Failed to parse JSON: " << e.what();
    }

    google::ShutdownGoogleLogging();
    return 0;
}
