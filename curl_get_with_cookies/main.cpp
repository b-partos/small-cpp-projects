#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <curl/curl.h>

// Callback function for data received by curl
size_t writeCallback(void *contents, size_t size, size_t nmemb, std::string *userp)
{
  userp->append((char *)contents, size * nmemb);
  return size * nmemb;
}

// Declare the enum SslCertPolicy with two members: Manual and Ignore
enum class SslCertPolicy
{
  Manual,
  Ignore
};

// Helper function to trim spaces from start and end of a string
std::string trim(const std::string &s)
{
  size_t start = s.find_first_not_of(" \n\r\t\f\v");
  size_t end = s.find_last_not_of(" \n\r\t\f\v");
  return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

// Function to load configuration from file
std::map<std::string, std::string> loadConfig(const std::string &filename)
{
  std::map<std::string, std::string> config;
  std::ifstream file(filename);
  std::string line;

  while (std::getline(file, line))
  {
    auto delimiterPos = line.find("=");
    auto key = trim(line.substr(0, delimiterPos));
    auto value = trim(line.substr(delimiterPos + 1));
    config[key] = value;
  }

  return config;
}

int main()
{

  SslCertPolicy certPolicy{SslCertPolicy::Ignore};

  // Load configuration
  auto config = loadConfig("config.txt");

  // Use the loaded configuration
  std::string host = config["host"];
  std::string cookie = config["cookie"];
  std::string url = config["url"];

  std::cout << "Loaded config:" << std::endl
            << "  Host: " << host << std::endl
            << "  URL: " << url << std::endl
            << "  Cookie: " << cookie << std::endl;

  CURL *curl;
  CURLcode res;
  std::string readBuffer;

  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();

  if (curl)
  {
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, ("Host: " + host).c_str());
    headers = curl_slist_append(headers, "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:123.0) Gecko/20100101 Firefox/123.0");
    headers = curl_slist_append(headers, "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8");
    headers = curl_slist_append(headers, "Accept-Language: en-GB,en;q=0.5");
    headers = curl_slist_append(headers, "Accept-Encoding: gzip, deflate, br");
    headers = curl_slist_append(headers, "Connection: keep-alive");
    headers = curl_slist_append(headers, ("Cookie: " + cookie).c_str());
    headers = curl_slist_append(headers, "Upgrade-Insecure-Requests: 1");
    headers = curl_slist_append(headers, "Sec-Fetch-Dest: document");
    headers = curl_slist_append(headers, "Sec-Fetch-Mode: navigate");
    headers = curl_slist_append(headers, "Sec-Fetch-Site: same-origin");
    headers = curl_slist_append(headers, "Sec-Fetch-User: ?1");

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    switch (certPolicy)
    {
    case SslCertPolicy::Manual:
    {
      curl_easy_setopt(curl, CURLOPT_CAINFO, "cacert.pem");
      break;
    }
    case SslCertPolicy::Ignore:
    {
      // Disable SSL Certificate Verificationg
      curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
      curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
      break;
    }
    }

    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    // Perform the request, and check for errors
    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
      std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;

    std::cout << "Response: " << std::endl
              << readBuffer << std::endl;

    // Clean-up
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();
  return 0;
}