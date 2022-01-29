/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#ifndef LOGGING_H
#define LOGGING_H

enum {
  logging_call_register,
  logging_call_record,
};

/** A log record formatting argument. */
union log_record_fmt_arg {
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

  struct {
    /** The auxiliary begin index. */
    int begin;

    /** The auxiliary end index. */
    int end;
  } as_string;
};

/** The size of a log record format string. */
#define LOG_RECORD_FMT_SIZE 512

/** The maximum number of log record format arguments. */
#define LOG_RECORD_FMT_ARG_MAX 8

/** The size of a log record auxiliary buffer. */
#define LOG_RECORD_AUX_SIZE 512

/** A log record. */
struct log_record {
  /** The format string. */
  const char fmt[LOG_RECORD_FMT_SIZE];

  /** The number of format arguments. */
  int fmt_args_num;

  /** The format arguments. */
  union log_record_fmt_arg fmt_args[LOG_RECORD_FMT_ARG_MAX];

  /** The auxiliary buffer. */
  const char aux[LOG_RECORD_AUX_SIZE];
};

/**
 * The logging service definition.
 */
extern struct service* const SERVICE_LOGGING;

#endif // #ifndef LOGGING_H
