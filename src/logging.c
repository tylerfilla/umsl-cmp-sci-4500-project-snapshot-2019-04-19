/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#include "log.h"
#include "logging.h"
#include "service.h"

static void logging_on_started(struct service* svc) {
  LOGI("The logging service is now online");
}

static void logging_on_stopping(struct service* svc) {
  LOGI("The logging service is stopping");
}

/** The actual service definition. */
static struct service service = {
  .name = "logging",
  .on_started = &logging_on_started,
  .on_stopping = &logging_on_stopping,
};

struct service* const SERVICE_LOGGING = &service;
