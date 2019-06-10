#include <iostream>
#include <curl/curl.h>
#include <fstream>

static size_t Writer(char *data, size_t size, size_t nmemb, std::ofstream* pBuf){
    size_t result = 0;
    if(pBuf != nullptr){
        pBuf->write(data, size*nmemb);
        result = size * nmemb;
    }
    return result;
}

int main (int argc, char* argv[]){
    if( argc < 3 || argc > 4) 
    { 
        std::cerr<<"Wrong amount of arguments!"<<std::endl;
        return 0;
    }
    curl_global_init(CURL_GLOBAL_DEFAULT);
    CURL *curl = curl_easy_init();
    if(!curl){std::cerr<<"curl_easy_init failed\n"; return 1;}
    
    std::ofstream ofs(argv[2], std::ofstream::binary);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ofs);
    curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Writer);
    curl_easy_perform(curl);
    
    curl_easy_cleanup(curl);
    curl_global_cleanup();
}
