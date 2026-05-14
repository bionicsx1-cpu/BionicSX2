#pragma once
// iOS build stub — HTTP via CFNetwork/NSURLSession (HTTPDownloaderCurl excluded)
#include <stddef.h>
typedef void CURL;
typedef int  CURLcode;
typedef int  CURLoption;
typedef int  CURLINFO;
typedef struct curl_slist { char *data; struct curl_slist *next; } curl_slist;
#define CURLE_OK             0
#define CURLOPT_URL          10002
#define CURLOPT_WRITEFUNCTION 20011
#define CURLOPT_WRITEDATA    10001
#define CURLOPT_USERAGENT    10018
#define CURLOPT_FOLLOWLOCATION 52
#define CURLOPT_SSL_VERIFYPEER 64
#define CURLINFO_RESPONSE_CODE 0x200002
static inline CURL*     curl_easy_init(void){return (CURL*)0;}
static inline void      curl_easy_cleanup(CURL*c){}
static inline CURLcode  curl_easy_setopt(CURL*c,CURLoption o,...){return CURLE_OK;}
static inline CURLcode  curl_easy_perform(CURL*c){return CURLE_OK;}
static inline CURLcode  curl_easy_getinfo(CURL*c,CURLINFO i,...){return CURLE_OK;}
static inline CURLcode  curl_global_init(long f){return CURLE_OK;}
static inline void      curl_global_cleanup(void){}
static inline curl_slist* curl_slist_append(curl_slist*l,const char*s){return (curl_slist*)0;}
static inline void      curl_slist_free_all(curl_slist*l){}
static inline const char* curl_easy_strerror(CURLcode e){return "stub";}
