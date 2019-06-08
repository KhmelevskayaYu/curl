#include <iostream>
#include <curl/curl.h>
#include <fstream>
#include <string>
static size_t Writer(char *data, size_t size, size_t nmemb, std::ofstream* pBuf){
    size_t result = 0;
    if(pBuf != NULL){
        pBuf->write(data, size*nmemb);
        result = size * nmemb;
    }
    return result;
}
 
int main (int argc, char* argv[]){
    CURL* curl;
    curl=curl_easy_init();
    if(!curl){std::cerr<<"curl_easy_init failed\n"; return 1;}
    std::string URL = argv[1];
    int pos;
    for(int i = 0; i< URL.size(); i++)
    if(URL[i] == '/') pos = i;
    int fname_size = 0;
    std::string fname = "";
    for(int i = pos+1; i <  URL.size(); i++){ fname_size++; fname+=URL[i];}
    std::string file_name = URL.substr(pos, fname_size);
    
    std::ofstream ofs(fname,std::ofstream::binary);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ofs);
    curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Writer);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    ofs.close();
    return 0;
}
