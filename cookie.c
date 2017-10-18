#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int get_cookie(char *cookiename) {
    char    *cookie, *tp;
    int    count = 0;

    if((cookie = getenv("HTTP_COOKIE")) != NULL) {
        tp = strtok(cookie, "= ");
        while(tp != NULL) {
            if(strcmp(tp, cookiename) == 0) {
                tp = strtok(NULL, "; ");
                break;
            }
            else {
                tp = strtok(NULL, "; ");
            }
            if(tp != NULL) {
                tp = strtok(NULL, "= ");
            }            
        }
        count = atoi(tp);
    }
    return count;
}

void set_cookie(char *cookiename, int cookielife, int count) {
    time_t    timer;
    struct tm    *date;
    char    expires[256];

    timer = time(NULL);
    timer += cookielife;
    date = gmtime(&timer);

    strftime(expires, 255, "%a, %d-%b-%Y %H:%M:%S GMT", date);

    printf("Set-Cookie: %s=%d; expires=%s;\n", cookiename, count, expires);
}

int main(void) {
    char    cookiename[] = "count";
    int    cookielife = 60 * 60 * 24 * 30;
    int    count;
    printf("Content-type: text/html\n");
    count = get_cookie(cookiename);
    count++;
    set_cookie(cookiename, cookielife, count);
    printf("\n");
    printf("<html>\n");
    printf("<head>\n");
    printf("<title>クッキー</title>\n");
    printf("</head>\n");
    printf("<body>\n");
    printf("訪問回数：%d回目<br>\n", count);
    printf("</body>\n");
    printf("</html>\n");
    return 0;
}