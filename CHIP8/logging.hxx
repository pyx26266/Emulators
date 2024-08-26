#ifndef LOGGING_H_
#define LOGGING_H_

#include <stdio.h>

#define LOG_INFO(format, ...) { \
    printf("INFO %s:%d   ", __FILE__, __LINE__); \
    printf(format, ##__VA_ARGS__); \
    printf("\n"); \
}


#endif // LOGGING_H_
