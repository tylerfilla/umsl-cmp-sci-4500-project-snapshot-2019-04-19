/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#define LOG_ARG_SHORT_NAMES
#include "log.h"
#include "service.h"

int service_start(struct service* svc) {
  LOGD("(service) request to start {}", _str(svc->name));

  if (svc->on_started) {
    svc->on_started(svc);
  } else {
    LOGW("(service) no start callback on {}", _str(svc->name));
  }

  return 0;
}

int service_stop(struct service* svc) {
  LOGD("(service) request to stop {}", _str(svc->name));

  if (svc->on_stopping) {
    svc->on_stopping(svc);
  } else {
    LOGW("(service) no stop callback on {}", _str(svc->name));
  }

  return 0;
}
