/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#include <stdlib.h>
#include <pthread.h>
#include <liblfds711.h>

#include "log.h"
#include "logging.h"
#include "service.h"

/** The log daemon. */
static pthread_t daemon;

/** The log daemon mutex. */
static pthread_mutex_t daemon_mutex;

/** The log daemon kill switch. */
static int daemon_kill;

/** A linked list of registered contexts. */
static struct context* contexts;

/** A log context. */
struct context {
  /** The next context. */
  struct context* next;

  /** The log record queue. */
  struct lfds711_queue_bss_state queue;
};

static void poll_context(struct context* ctx) {
}

static void* register_context() {
  // Allocate new context
  struct context* ctx = malloc(sizeof(struct context));
  ctx->next = NULL;

  // Allocate elements for log record queue
  struct lfds711_queue_bss_element* rec = malloc(1024 * sizeof(struct lfds711_queue_bss_element));

  // Initialize log submission queue
  lfds711_queue_bss_init_valid_on_current_logical_core(&ctx->queue, rec, 1024, NULL);

  // Lock the daemon mutex
  pthread_mutex_lock(&daemon_mutex);

  // Seek to the last context
  struct context* last_ctx = contexts;
  if (last_ctx) {
    while (last_ctx->next != NULL) {
      last_ctx = last_ctx->next;
    }
  }

  // Insert the new context
  if (last_ctx) {
    last_ctx->next = ctx;
  } else {
    contexts = ctx;
  }

  // Unlock the daemon mutex
  pthread_mutex_unlock(&daemon_mutex);

  return ctx;
}

// TODO: Add a method to unregister and clean up after contexts

static void context_submit(struct context* ctx, struct log_record* rec) {
  // Add record to queue
  lfds711_queue_bss_enqueue(&ctx->queue, NULL, rec);
}

static void* logging__daemon_main(void* ptr) {
  LOGD("The logging daemon is online");

  do {
    // Lock the daemon mutex
    pthread_mutex_lock(&daemon_mutex);

    // If kill switch is set, then die
    if (daemon_kill) {
      pthread_mutex_unlock(&daemon_mutex);
      break;
    }

    // Tend all contexts
    struct context* ctx = contexts;
    do {
      poll_context(ctx);
    } while ((ctx = ctx->next) != NULL);

    // Unlock the daemon mutex
    pthread_mutex_unlock(&daemon_mutex);
  } while (1);

  return NULL;
}

static void logging_call(struct service* svc, int func, void* arg, void** ret) {
  switch (func) {
    case logging_call_register:
      *ret = register_context();
      break;
    case logging_call_record:
      context_submit((struct context*) *ret, (struct log_record*) arg);
      break;
  }
}

static void logging_on_started(struct service* svc) {
  // Reset the kill switch
  daemon_kill = 0;

  // Spawn the daemon thread
  pthread_create(&daemon, NULL, &logging__daemon_main, NULL);
}

static void logging_on_stopping(struct service* svc) {
  // Ask the daemon to die
  pthread_mutex_lock(&daemon_mutex);
  daemon_kill = 1;
  pthread_mutex_unlock(&daemon_mutex);

  // Wait for daemon to die
  pthread_join(daemon, NULL);
}

static struct service service = {
  .name = "logging",
  .call = &logging_call,
  .on_started = &logging_on_started,
  .on_stopping = &logging_on_stopping,
};

struct service* const SERVICE_LOGGING = &service;
