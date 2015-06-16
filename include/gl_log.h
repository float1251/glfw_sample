#include <stdbool.h>

#ifndef _GL_LOG_H_
#define _GL_LOG_H_

bool restart_gl_log();
bool gl_log (const char* message, ...);
bool gl_log_error (const char* message, ...);

#endif
