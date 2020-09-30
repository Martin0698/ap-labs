#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>
#include <syslog.h>


int mysyslog = 0;
int status = 0;


#define RST 0
#define BRIGHT 1


#define BLACK 0
#define RED 1
#define YELLOW 3
#define BLUE 4
#define WHITE 7

void Coloring(int attr, int fg, int bg)
{
    char command[13];

    sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
    printf("%s", command);
}

int initLogger(char *logType)
{
    if (strcmp(logType, "syslog") == 0)
    {
        mysyslog = 1;
        printf("Logger on: %s\n", logType);
    }


    else if (strcmp(logType, "") == 0 || strcmp(logType, "stdout") == 0)
    {
        printf("Logger on: stdout\n");
    }


    else
    {
        printf("Incorrect value");
        return 1;
    }



    return 0;
}



int infof(const char *format, ...)
{
    Coloring(BRIGHT, BLUE, BLACK);
    va_list arg;
    va_start(arg, format);

    if (mysyslog == 1)
    {
        openlog("logger", LOG_PID | LOG_CONS, LOG_SYSLOG);
        vsyslog(LOG_INFO, format, arg);
        closelog();
    }


    else
    {
        vprintf(format, arg);
        printf("\n");
    }


    va_end(arg);
    Coloring(RST, WHITE, BLACK);

    
    return 0;
}

int warnf(const char *format, ...)
{
    Coloring(BRIGHT, YELLOW, BLACK);
    va_list arg;
    va_start(arg, format);

    if (mysyslog == 1)
    {
        openlog("logger", LOG_PID | LOG_CONS, LOG_SYSLOG);
        vsyslog(LOG_WARNING, format, arg);
        closelog();
    }


    else
    {
        vprintf(format, arg);
        printf("\n");
    }

    va_end(arg);
    Coloring(RST, WHITE, BLACK);



    return 0;
}

int errorf(const char *format, ...)
{
    Coloring(BRIGHT, RED, BLACK);
    va_list arg;
    va_start(arg, format);

    if (mysyslog == 1)
    {
        openlog("logger", LOG_PID | LOG_CONS, LOG_SYSLOG);
        vsyslog(LOG_ERR, format, arg);
        closelog();
    }


    else
    {
        vprintf(format, arg);
        printf("\n");
    }


    va_end(arg);
    Coloring(RST, WHITE, BLACK);


    return 0;
}

int panicf(const char *format, ...)
{
    Coloring(BRIGHT, WHITE, RED);
    va_list arg;
    va_start(arg, format);

    if (mysyslog == 1)
    {
        openlog("logger", LOG_PID | LOG_CONS, LOG_SYSLOG);
        vsyslog(LOG_EMERG, format, arg);
        closelog();
    }


    else
    {
        vprintf(format, arg);
        printf("\n");
    }



    va_end(arg);
    Coloring(RST, WHITE, BLACK);
    raise(SIGABRT);

    
    return 0;
}