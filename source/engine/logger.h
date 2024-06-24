#pragma once
#include "engine/defines.h"

#include <stdio.h>

// build config
#ifdef BUILD_RELEASE
#define DISABLE_LOG_DEBUG
#define DISABLE_LOG_TRACE
#endif

#define FATAL(message, ...) printf("FATAL: "message"\n", ##__VA_ARGS__);
#define ERROR(message, ...) printf("ERROR: "message"\n", ##__VA_ARGS__);
#define WARN(message, ...) printf("WARN: "message"\n", ##__VA_ARGS__);
#define INFO(message, ...) printf("INFO: "message"\n", ##__VA_ARGS__);

#ifndef DISABLE_LOG_DEBUG
#define DEBUG(message, ...) printf("DEBUG: "message"\n", ##__VA_ARGS__);
#else
#define DEBUG(message, ...)
#endif

#ifndef DISABLE_LOG_TRACE
#define TRACE(message, ...) printf("TRACE: "message"\n", ##__VA_ARGS__);
#else
#define TRACE(message, ...)
#endif
