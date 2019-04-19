/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#include <stdio.h>
#include "log.h"

void log_submit(struct log_sub* sub) {
  printf("Got a submission...\n");
  printf("  fmt: %s\n", sub->msg_fmt);

  for (int i = 0; i < sub->num_msg_fmt_args; ++i) {
    struct log_sub_msg_fmt_arg* arg = &sub->msg_fmt_args[i];

    printf("  args[%d] = ", i);

    switch (arg->type) {
      case log_sub_msg_fmt_arg_type_char:
        printf("%c\n", arg->value.as_char);
        break;
      case log_sub_msg_fmt_arg_type_signed_char:
        printf("%c\n", arg->value.as_signed_char);
        break;
      case log_sub_msg_fmt_arg_type_unsigned_char:
        printf("%c\n", arg->value.as_unsigned_char);
        break;
      case log_sub_msg_fmt_arg_type_signed_short_int:
        printf("%d\n", arg->value.as_signed_short_int);
        break;
      case log_sub_msg_fmt_arg_type_unsigned_short_int:
        printf("%d\n", arg->value.as_unsigned_short_int);
        break;
      case log_sub_msg_fmt_arg_type_signed_int:
        printf("%d\n", arg->value.as_signed_int);
        break;
      case log_sub_msg_fmt_arg_type_unsigned_int:
        printf("%d\n", arg->value.as_unsigned_int);
        break;
      case log_sub_msg_fmt_arg_type_signed_long_int:
        printf("%ld\n", arg->value.as_signed_long_int);
        break;
      case log_sub_msg_fmt_arg_type_unsigned_long_int:
        printf("%ld\n", arg->value.as_unsigned_long_int);
        break;
      case log_sub_msg_fmt_arg_type_signed_long_long_int:
        printf("%lld\n", arg->value.as_signed_long_long_int);
        break;
      case log_sub_msg_fmt_arg_type_unsigned_long_long_int:
        printf("%lld\n", arg->value.as_unsigned_long_long_int);
        break;
      case log_sub_msg_fmt_arg_type_float:
        printf("%f\n", arg->value.as_float);
        break;
      case log_sub_msg_fmt_arg_type_double:
        printf("%f\n", arg->value.as_double);
        break;
      case log_sub_msg_fmt_arg_type_long_double:
        printf("%Lf\n", arg->value.as_long_double);
        break;
      case log_sub_msg_fmt_arg_type_string:
        printf("\"%s\"\n", arg->value.as_string);
        break;
    }

    printf("\n");
  }
}
