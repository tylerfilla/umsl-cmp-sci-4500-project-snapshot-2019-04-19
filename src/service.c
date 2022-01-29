/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#define LOG_ARG_SHORT_NAMES
#include "log.h"
#include "service.h"

int service_call(struct service* svc, int func, void* arg, void** ret) {
  switch (svc->_state) {
    case service_state_ready:
    case service_state_stopped: {
      LOGE("Cannot call into {}", _str(svc->name));
      return 1;
    }
    case service_state_started: {
      if (svc->call) {
        svc->call(svc, func, arg, ret);
      } else {
        LOGW("No call interface on {}", _str(svc->name));
      }
      return 0;
    }
  }
}

int service_start(struct service* svc) {
  LOGD("Request to start service {}", _str(svc->name));

  switch (svc->_state) {
    case service_state_ready:
    case service_state_stopped: {
      svc->_state = service_state_started;
      if (svc->on_started) {
        svc->on_started(svc);
      } else {
        LOGW("No start callback on {}", _str(svc->name));
      }
      return 0;
    }
    case service_state_started: {
      LOGE("Cannot start {}", _str(svc->name));
      return 1;
    }
  }
}

int service_stop(struct service* svc) {
  LOGD("Request to stop service {}", _str(svc->name));

  switch (svc->_state) {
    case service_state_ready:
    case service_state_stopped: {
      LOGE("Cannot stop {}", _str(svc->name));
      return 1;
    }
    case service_state_started: {
      svc->_state = service_state_stopped;
      if (svc->on_stopping) {
        svc->on_stopping(svc);
      } else {
        LOGW("No stop callback on {}", _str(svc->name));
      }
      return 0;
    }
  }
}
