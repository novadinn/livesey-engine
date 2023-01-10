#ifndef LOG_H
#define LOG_H

#include <glad/glad.h>
#include <cstring>
#include <stdarg.h>

static void log_fmt_err(const char* err, ...) {
    char* errc;
    va_list va;
    va_start(va, err);
    errc = (char*)malloc(512);
    vsnprintf(errc, 512-1, err, va);
    errc = (char*)realloc(errc, strlen(errc)+1);
    va_end(va);

    printf("%s\n", errc);
    free(errc);
}

#define LOG_ERR_FATAL(fmt, ...)			\
    {						\
	log_fmt_err(fmt, ##__VA_ARGS__);	\
	abort();				\
    }
#define LOG_ERR(fmt, ...)			\
    {						\
    log_fmt_err(fmt, ##__VA_ARGS__);		\
    }

#endif // LOG_H
