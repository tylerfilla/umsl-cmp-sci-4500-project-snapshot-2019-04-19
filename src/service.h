/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#ifndef SERVICE_H
#define SERVICE_H

/**
 * A service definition.
 *
 * Services are singleton units that manage specific domains of the application.
 * They may be completely static, or they may run background daemons to do work.
 * One thing is absolute: only one instance of each service can run at once. The
 * service is then free to define "run" however it wants to solve a problem.
 */
struct service {
  /** The service name. */
  const char* name;

  /**
   * Called after the service starts.
   *
   * @param svc The service
   */
  void (* on_started)(struct service* svc);

  /**
   * Called before the service stops.
   *
   * @param svc The service
   */
  void (* on_stopping)(struct service* svc);
};

/**
 * Start a service.
 *
 * @param svc The service definition
 * @return Zero on success, otherwise nonzero
 */
int service_start(struct service* svc);

/**
 * Stop a service.
 *
 * @param svc The service definition
 * @return Zero on success, otherwise nonzero
 */
int service_stop(struct service* svc);

#endif // #ifndef SERVICE_H
