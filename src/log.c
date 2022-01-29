/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#include <stdio.h>

#include "log.h"
#include "logging.h"
#include "service.h"

/** Whether or not logging is blocked. */
static __thread int blocked;

/** A handle to the logging context. */
static __thread void* context;

void log_submit(struct log_sub* sub) {
  // If blocked, ignore the submission
  if (blocked) {
    return;
  }

  // If we don't yet have a context on this thread
  if (!context) {
    // Block all logging on this thread
    // This prevents infinite loops of logs about logs
    blocked = 1;

    // Register for a logging context on this thread
    // This is a relatively expensive operation (mutexes and mallocs), but it only happens once per thread
    service_call(SERVICE_LOGGING, logging_call_register, NULL, &context);

    // If context is still unavailable
    if (!context) {
      // Resort to stderr for error reporting
      fprintf(stderr, "unable to register logging context\n");
      return;
    }

    // Unblock logging
    blocked = 0;
  }

  // The log record
  struct log_record rec = {
    .fmt = "asdf?",
  };

  // Submit the log record
  service_call(SERVICE_LOGGING, logging_call_record, &rec, &context);

  /*
  printf("Got a submission...\n");
  printf("  fmt: %s\n", sub->msg_fmt);

  for (int i = 0; i < sub->num_msg_fmt_args; ++i) {
    struct log_sub_msg_fmt_arg* arg = &sub->msg_fmt_args[i];

    printf("  args[%d] = ", i);

    switch (arg->type) {
      case log_sub_msg_fmt_arg_type_char:
        printf("%c", arg->value.as_char);
        break;
      case log_sub_msg_fmt_arg_type_signed_char:
        printf("%c", arg->value.as_signed_char);
        break;
      case log_sub_msg_fmt_arg_type_unsigned_char:
        printf("%c", arg->value.as_unsigned_char);
        break;
      case log_sub_msg_fmt_arg_type_signed_short_int:
        printf("%d", arg->value.as_signed_short_int);
        break;
      case log_sub_msg_fmt_arg_type_unsigned_short_int:
        printf("%d", arg->value.as_unsigned_short_int);
        break;
      case log_sub_msg_fmt_arg_type_signed_int:
        printf("%d", arg->value.as_signed_int);
        break;
      case log_sub_msg_fmt_arg_type_unsigned_int:
        printf("%d", arg->value.as_unsigned_int);
        break;
      case log_sub_msg_fmt_arg_type_signed_long_int:
        printf("%ld", arg->value.as_signed_long_int);
        break;
      case log_sub_msg_fmt_arg_type_unsigned_long_int:
        printf("%ld", arg->value.as_unsigned_long_int);
        break;
      case log_sub_msg_fmt_arg_type_signed_long_long_int:
        printf("%lld", arg->value.as_signed_long_long_int);
        break;
      case log_sub_msg_fmt_arg_type_unsigned_long_long_int:
        printf("%lld", arg->value.as_unsigned_long_long_int);
        break;
      case log_sub_msg_fmt_arg_type_float:
        printf("%f", arg->value.as_float);
        break;
      case log_sub_msg_fmt_arg_type_double:
        printf("%f", arg->value.as_double);
        break;
      case log_sub_msg_fmt_arg_type_long_double:
        printf("%Lf", arg->value.as_long_double);
        break;
      case log_sub_msg_fmt_arg_type_string:
        printf("\"%s\"", arg->value.as_string);
        break;
    }

    printf("\n");
  }

  printf("\n");
  */
}
