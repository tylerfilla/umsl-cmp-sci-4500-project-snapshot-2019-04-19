/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#ifndef LOG_H
#define LOG_H

#include <stddef.h>

/**
 * A log submission.
 *
 * This is a precursor to a log record. The message has not yet been formatted,
 * and string memory is owned by someone else. But, making one of these is fast.
 */
struct log_sub {
  /** The message format string. */
  const char* msg_fmt;

  /** The message format arguments. */
  struct log_sub_msg_fmt_arg {
    /** The argument value. */
    union {
      char as_char;
      signed char as_signed_char;
      unsigned char as_unsigned_char;
      signed short int as_signed_short_int;
      unsigned short int as_unsigned_short_int;
      signed int as_signed_int;
      unsigned int as_unsigned_int;
      signed long int as_signed_long_int;
      unsigned long int as_unsigned_long_int;
      signed long long int as_signed_long_long_int;
      unsigned long long int as_unsigned_long_long_int;
      float as_float;
      double as_double;
      long double as_long_double;
      const char* as_string;
    } value;

    /** The argument type. */
    enum log_sub_msg_fmt_arg_type {
      log_sub_msg_fmt_arg_type_char,
      log_sub_msg_fmt_arg_type_signed_char,
      log_sub_msg_fmt_arg_type_unsigned_char,
      log_sub_msg_fmt_arg_type_signed_short_int,
      log_sub_msg_fmt_arg_type_unsigned_short_int,
      log_sub_msg_fmt_arg_type_signed_int,
      log_sub_msg_fmt_arg_type_unsigned_int,
      log_sub_msg_fmt_arg_type_signed_long_int,
      log_sub_msg_fmt_arg_type_unsigned_long_int,
      log_sub_msg_fmt_arg_type_signed_long_long_int,
      log_sub_msg_fmt_arg_type_unsigned_long_long_int,
      log_sub_msg_fmt_arg_type_float,
      log_sub_msg_fmt_arg_type_double,
      log_sub_msg_fmt_arg_type_long_double,
      log_sub_msg_fmt_arg_type_string,
    } type;
  } * msg_fmt_args;

  /** The number of message format arguments. */
  size_t num_msg_fmt_args;

  /** The severity level. */
  enum log_sub_level {
    log_sub_level_trace,
    log_sub_level_debug,
    log_sub_level_info,
    log_sub_level_warn,
    log_sub_level_error,
    log_sub_level_fatal,
  } level;

  /** The source file name. */
  const char* file;

  /** The source line number. */
  unsigned int line;
};

/**
 * Write a log submission.
 *
 * @param sub The submission
 */
void log_submit(struct log_sub* sub);

/** @private */
#define LOG__MSG_FMT_ARGS(...) \
    ((struct log_sub_msg_fmt_arg[]) { __VA_ARGS__ })

/** @private */
#define LOG__NUM_MSG_FMT_ARGS(...) \
    (sizeof((struct log_sub_msg_fmt_arg[]) { __VA_ARGS__ }) / sizeof(struct log_sub_msg_fmt_arg))

/**
 * Prepare a log submission.
 *
 * @param lvl The severity level
 * @param fmt The format string
 * @param ... The format arguments
 */
#define LOG(lvl, fmt, ...)                                    \
    ((void) log_submit(&(struct log_sub) {                    \
      .msg_fmt = (fmt),                                       \
      .msg_fmt_args = LOG__MSG_FMT_ARGS(__VA_ARGS__),         \
      .num_msg_fmt_args = LOG__NUM_MSG_FMT_ARGS(__VA_ARGS__), \
      .level = (lvl),                                         \
      .file = __FILE__,                                       \
      .line = __LINE__,                                       \
    }))

/**
 * Write to the log with TRACE severity.
 *
 * @param fmt The format string
 * @param ... The format arguments
 */
#define LOGT(fmt, ...) LOG(log_sub_level_trace, (fmt), ##__VA_ARGS__)

/**
 * Write to the log with DEBUG severity.
 *
 * @param fmt The format string
 * @param ... The format arguments
 */
#define LOGD(fmt, ...) LOG(log_sub_level_debug, (fmt), ##__VA_ARGS__)

/**
 * Write to the log with INFO severity.
 *
 * @param fmt The format string
 * @param ... The format arguments
 */
#define LOGI(fmt, ...) LOG(log_sub_level_info, (fmt), ##__VA_ARGS__)

/**
 * Write to the log with WARN severity.
 *
 * @param fmt The format string
 * @param ... The format arguments
 */
#define LOGW(fmt, ...) LOG(log_sub_level_warn, (fmt), ##__VA_ARGS__)

/**
 * Write to the log with ERROR severity.
 *
 * @param fmt The format string
 * @param ... The format arguments
 */
#define LOGE(fmt, ...) LOG(log_sub_level_error, (fmt), ##__VA_ARGS__)

/**
 * Write to the log with FATAL severity.
 *
 * @param fmt The format string
 * @param ... The format arguments
 */
#define LOGF(fmt, ...) LOG(log_sub_level_fatal, (fmt), ##__VA_ARGS__)

/**
 * Annotation for char log format arguments.
 * 
 * @param x The argument
 */
#define LOG_ARG_C(x)                          \
    (struct log_sub_msg_fmt_arg) {            \
      .value.as_char = (x),                   \
      .type = log_sub_msg_fmt_arg_type_char,  \
    }

#ifdef LOG_ARG_SHORT_NAMES
#define _c LOG_ARG_C
#endif

/**
 * Annotation for signed char log format arguments.
 * 
 * @param x The argument
 */
#define LOG_ARG_SC(x)                               \
    (struct log_sub_msg_fmt_arg) {                  \
      .value.as_signed_char = (x),                  \
      .type = log_sub_msg_fmt_arg_type_signed_char, \
    }

#ifdef LOG_ARG_SHORT_NAMES
#define _sc LOG_ARG_SC
#endif

/**
 * Annotation for unsigned char log format arguments.
 * 
 * @param x The argument
 */
#define LOG_ARG_UC(x)                                 \
    (struct log_sub_msg_fmt_arg) {                    \
      .value.as_unsigned_char = (x),                  \
      .type = log_sub_msg_fmt_arg_type_unsigned_char, \
    }

#ifdef LOG_ARG_SHORT_NAMES
#define _uc LOG_ARG_UC
#endif

/**
 * Annotation for signed short log format arguments.
 * 
 * @param x The argument
 */
#define LOG_ARG_S(x)                                      \
    (struct log_sub_msg_fmt_arg) {                        \
      .value.as_signed_short_int = (x),                   \
      .type = log_sub_msg_fmt_arg_type_signed_short_int,  \
    }

#ifdef LOG_ARG_SHORT_NAMES
#define _s LOG_ARG_S
#endif

/**
 * Annotation for unsigned short log format arguments.
 * 
 * @param x The argument
 */
#define LOG_ARG_US(x)                                       \
    (struct log_sub_msg_fmt_arg) {                          \
      .value.as_unsigned_short_int = (x),                   \
      .type = log_sub_msg_fmt_arg_type_unsigned_short_int,  \
    }

#ifdef LOG_ARG_SHORT_NAMES
#define _us LOG_ARG_US
#endif

/**
 * Annotation for signed int log format arguments.
 * 
 * @param x The argument
 */
#define LOG_ARG_I(x)                                \
    (struct log_sub_msg_fmt_arg) {                  \
      .value.as_signed_int = (x),                   \
      .type = log_sub_msg_fmt_arg_type_signed_int,  \
    }

#ifdef LOG_ARG_SHORT_NAMES
#define _i LOG_ARG_I
#endif

/**
 * Annotation for unsigned int log format arguments.
 * 
 * @param x The argument
 */
#define LOG_ARG_U(x)                                  \
    (struct log_sub_msg_fmt_arg) {                    \
      .value.as_unsigned_int = (x),                   \
      .type = log_sub_msg_fmt_arg_type_unsigned_int,  \
    }

#ifdef LOG_ARG_SHORT_NAMES
#define _u LOG_ARG_U
#endif

/**
 * Annotation for signed long int log format arguments.
 * 
 * @param x The argument
 */
#define LOG_ARG_L(x)                                    \
    (struct log_sub_msg_fmt_arg) {                      \
      .value.as_signed_long_int = (x),                  \
      .type = log_sub_msg_fmt_arg_type_signed_long_int, \
    }

#ifdef LOG_ARG_SHORT_NAMES
#define _l LOG_ARG_L
#endif

/**
 * Annotation for unsigned long int log format arguments.
 * 
 * @param x The argument
 */
#define LOG_ARG_UL(x)                                     \
    (struct log_sub_msg_fmt_arg) {                        \
      .value.as_unsigned_long_int = (x),                  \
      .type = log_sub_msg_fmt_arg_type_unsigned_long_int, \
    }

#ifdef LOG_ARG_SHORT_NAMES
#define _ul LOG_ARG_UL
#endif

/**
 * Annotation for signed long long int log format arguments.
 * 
 * @param x The argument
 */
#define LOG_ARG_LL(x)                                         \
    (struct log_sub_msg_fmt_arg) {                            \
      .value.as_signed_long_long_int = (x),                   \
      .type = log_sub_msg_fmt_arg_type_signed_long_long_int,  \
    }

#ifdef LOG_ARG_SHORT_NAMES
#define _ll LOG_ARG_LL
#endif

/**
 * Annotation for unsigned long long int log format arguments.
 * 
 * @param x The argument
 */
#define LOG_ARG_ULL(x)                                          \
    (struct log_sub_msg_fmt_arg) {                              \
      .value.as_unsigned_long_long_int = (x),                   \
      .type = log_sub_msg_fmt_arg_type_unsigned_long_long_int,  \
    }

#ifdef LOG_ARG_SHORT_NAMES
#define _ull LOG_ARG_ULL
#endif

/**
 * Annotation for float log format arguments.
 * 
 * @param x The argument
 */
#define LOG_ARG_F(x)                          \
    (struct log_sub_msg_fmt_arg) {            \
      .value.as_float = (x),                  \
      .type = log_sub_msg_fmt_arg_type_float, \
    }

#ifdef LOG_ARG_SHORT_NAMES
#define _f LOG_ARG_F
#endif

/**
 * Annotation for double log format arguments.
 * 
 * @param x The argument
 */
#define LOG_ARG_D(x)                            \
    (struct log_sub_msg_fmt_arg) {              \
      .value.as_double = (x),                   \
      .type = log_sub_msg_fmt_arg_type_double,  \
    }

#ifdef LOG_ARG_SHORT_NAMES
#define _d LOG_ARG_D
#endif

/**
 * Annotation for long double log format arguments.
 * 
 * @param x The argument
 */
#define LOG_ARG_LD(x)                               \
    (struct log_sub_msg_fmt_arg) {                  \
      .value.as_long_double = (x),                  \
      .type = log_sub_msg_fmt_arg_type_long_double, \
    }

#ifdef LOG_ARG_SHORT_NAMES
#define _ld LOG_ARG_LD
#endif

/**
 * Annotation for string log format arguments.
 * 
 * @param x The argument
 */
#define LOG_ARG_STR(x)                          \
    (struct log_sub_msg_fmt_arg) {              \
      .value.as_string = (x),                   \
      .type = log_sub_msg_fmt_arg_type_string,  \
    }

#ifdef LOG_ARG_SHORT_NAMES
#define _str LOG_ARG_STR
#endif

#endif // #ifndef LOG_H
