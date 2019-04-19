/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#include "logging.h"
#include "service.h"

int main() {
  service_start(SERVICE_LOGGING);
  service_stop(SERVICE_LOGGING);
}
