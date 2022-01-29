/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#include "log.h"
#include "logging.h"
#include "service.h"

int main() {
  service_start(SERVICE_LOGGING);

  LOGI("Hello, {}!", LOG_ARG_STR("logging"));

  sleep(5);

  service_stop(SERVICE_LOGGING);
}
