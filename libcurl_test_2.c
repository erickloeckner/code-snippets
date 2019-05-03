#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <curl/curl.h>

typedef struct {
  char *memory;
  size_t size;
} data_type;

size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    data_type *mem = (data_type *)userp;
        
    char *ptr = realloc(mem->memory, realsize + 1);
    if(ptr == NULL) {
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }
    
    mem->memory = ptr;
    memcpy(mem->memory, buffer, realsize);
    mem->size = realsize;
    mem->memory[mem->size] = 0;
    
    return realsize;
}

CURLcode curl_get(CURL *handle) {
    CURLcode res = curl_easy_perform(handle);
    return res;
}

int find_pos(char const* str, char const* substr) {
    char* pos = strstr(str, substr);
    return pos - str;
}

int find_end(char const* str, int pos) {
    int end = pos + 1;
    int end_char = 1;
    while(end_char){
        if(str[end] != '"') {
            end++;
        } else {
            end_char = 0;
        }
    }
    return end;
}

int main(void)
{
    CURL *curl;
    CURLcode res;
    int i, j;
    int req_count;
    
    char *match_str = "\"datetime\":";
    char *result = malloc(1);
    int match_s = 0;
    int match_e = 0;
    int match_len = 0;
    
    data_type chunk;
    chunk.memory = malloc(1);  /* will be grown as needed by the realloc above */ 
    chunk.size = 0;    /* no data at this point */
    
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://worldtimeapi.org/api/timezone/America/Detroit");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
                
        for (req_count = 0; req_count < 4; req_count++) {
            printf("--request #%d\n", (req_count + 1));
            res = curl_get(curl);
            
            /* Check for errors */
            if(res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
            } else {
                printf("%s\n", chunk.memory);
                
                match_s = find_pos(chunk.memory, match_str) + strlen(match_str);
                match_e = find_end(chunk.memory, match_s);
                match_len = match_e - match_s;
                
                result = realloc(result, match_len);
                
                for (i = match_s + 1, j = 0; i < match_e; i++, j++) {
                    result[j] = chunk.memory[i];
                }
                result[match_len] = 0;
                
                printf("\n%s\n\n", result);
            }
            
            sleep(10);
        }
    }
    
    curl_easy_cleanup(curl);
    free(chunk.memory);
    curl_global_cleanup();
    free(result);
    
    return 0;
}
