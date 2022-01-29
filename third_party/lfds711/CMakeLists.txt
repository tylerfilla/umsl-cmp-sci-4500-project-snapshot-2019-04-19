#
# Cozmonaut
# Copyright 2019 The Cozmonaut Contributors
#

cmake_minimum_required(VERSION 3.4)

set(lfds711_SRC_FILES
        liblfds711/src/lfds711_misc/lfds711_misc_query.c
        liblfds711/src/lfds711_misc/lfds711_misc_globals.c
        liblfds711/src/lfds711_misc/lfds711_misc_internal_backoff_init.c
        liblfds711/src/lfds711_prng/lfds711_prng_init.c
        liblfds711/src/lfds711_stack/lfds711_stack_pop.c
        liblfds711/src/lfds711_stack/lfds711_stack_init.c
        liblfds711/src/lfds711_stack/lfds711_stack_push.c
        liblfds711/src/lfds711_stack/lfds711_stack_query.c
        liblfds711/src/lfds711_stack/lfds711_stack_cleanup.c
        liblfds711/src/lfds711_freelist/lfds711_freelist_pop.c
        liblfds711/src/lfds711_freelist/lfds711_freelist_init.c
        liblfds711/src/lfds711_freelist/lfds711_freelist_push.c
        liblfds711/src/lfds711_freelist/lfds711_freelist_query.c
        liblfds711/src/lfds711_freelist/lfds711_freelist_cleanup.c
        liblfds711/src/lfds711_ringbuffer/lfds711_ringbuffer_init.c
        liblfds711/src/lfds711_ringbuffer/lfds711_ringbuffer_read.c
        liblfds711/src/lfds711_ringbuffer/lfds711_ringbuffer_query.c
        liblfds711/src/lfds711_ringbuffer/lfds711_ringbuffer_write.c
        liblfds711/src/lfds711_ringbuffer/lfds711_ringbuffer_cleanup.c
        liblfds711/src/lfds711_hash_addonly/lfds711_hash_addonly_get.c
        liblfds711/src/lfds711_hash_addonly/lfds711_hash_addonly_init.c
        liblfds711/src/lfds711_hash_addonly/lfds711_hash_addonly_query.c
        liblfds711/src/lfds711_hash_addonly/lfds711_hash_addonly_insert.c
        liblfds711/src/lfds711_hash_addonly/lfds711_hash_addonly_cleanup.c
        liblfds711/src/lfds711_hash_addonly/lfds711_hash_addonly_iterate.c
        liblfds711/src/lfds711_btree_addonly_unbalanced/lfds711_btree_addonly_unbalanced_get.c
        liblfds711/src/lfds711_btree_addonly_unbalanced/lfds711_btree_addonly_unbalanced_init.c
        liblfds711/src/lfds711_btree_addonly_unbalanced/lfds711_btree_addonly_unbalanced_query.c
        liblfds711/src/lfds711_btree_addonly_unbalanced/lfds711_btree_addonly_unbalanced_insert.c
        liblfds711/src/lfds711_btree_addonly_unbalanced/lfds711_btree_addonly_unbalanced_cleanup.c
        liblfds711/src/lfds711_list_addonly_singlylinked_ordered/lfds711_list_addonly_singlylinked_ordered_get.c
        liblfds711/src/lfds711_list_addonly_singlylinked_ordered/lfds711_list_addonly_singlylinked_ordered_init.c
        liblfds711/src/lfds711_list_addonly_singlylinked_ordered/lfds711_list_addonly_singlylinked_ordered_query.c
        liblfds711/src/lfds711_list_addonly_singlylinked_ordered/lfds711_list_addonly_singlylinked_ordered_insert.c
        liblfds711/src/lfds711_list_addonly_singlylinked_ordered/lfds711_list_addonly_singlylinked_ordered_cleanup.c
        liblfds711/src/lfds711_list_addonly_singlylinked_unordered/lfds711_list_addonly_singlylinked_unordered_get.c
        liblfds711/src/lfds711_list_addonly_singlylinked_unordered/lfds711_list_addonly_singlylinked_unordered_init.c
        liblfds711/src/lfds711_list_addonly_singlylinked_unordered/lfds711_list_addonly_singlylinked_unordered_query.c
        liblfds711/src/lfds711_list_addonly_singlylinked_unordered/lfds711_list_addonly_singlylinked_unordered_insert.c
        liblfds711/src/lfds711_list_addonly_singlylinked_unordered/lfds711_list_addonly_singlylinked_unordered_cleanup.c
        liblfds711/src/lfds711_queue_bounded_manyproducer_manyconsumer/lfds711_queue_bounded_manyproducer_manyconsumer_init.c
        liblfds711/src/lfds711_queue_bounded_manyproducer_manyconsumer/lfds711_queue_bounded_manyproducer_manyconsumer_query.c
        liblfds711/src/lfds711_queue_bounded_manyproducer_manyconsumer/lfds711_queue_bounded_manyproducer_manyconsumer_cleanup.c
        liblfds711/src/lfds711_queue_bounded_manyproducer_manyconsumer/lfds711_queue_bounded_manyproducer_manyconsumer_dequeue.c
        liblfds711/src/lfds711_queue_bounded_manyproducer_manyconsumer/lfds711_queue_bounded_manyproducer_manyconsumer_enqueue.c
        liblfds711/src/lfds711_queue_unbounded_manyproducer_manyconsumer/lfds711_queue_unbounded_manyproducer_manyconsumer_init.c
        liblfds711/src/lfds711_queue_unbounded_manyproducer_manyconsumer/lfds711_queue_unbounded_manyproducer_manyconsumer_query.c
        liblfds711/src/lfds711_queue_unbounded_manyproducer_manyconsumer/lfds711_queue_unbounded_manyproducer_manyconsumer_cleanup.c
        liblfds711/src/lfds711_queue_unbounded_manyproducer_manyconsumer/lfds711_queue_unbounded_manyproducer_manyconsumer_dequeue.c
        liblfds711/src/lfds711_queue_unbounded_manyproducer_manyconsumer/lfds711_queue_unbounded_manyproducer_manyconsumer_enqueue.c
        liblfds711/src/lfds711_queue_bounded_singleproducer_singleconsumer/lfds711_queue_bounded_singleproducer_singleconsumer_init.c
        liblfds711/src/lfds711_queue_bounded_singleproducer_singleconsumer/lfds711_queue_bounded_singleproducer_singleconsumer_query.c
        liblfds711/src/lfds711_queue_bounded_singleproducer_singleconsumer/lfds711_queue_bounded_singleproducer_singleconsumer_cleanup.c
        liblfds711/src/lfds711_queue_bounded_singleproducer_singleconsumer/lfds711_queue_bounded_singleproducer_singleconsumer_dequeue.c
        liblfds711/src/lfds711_queue_bounded_singleproducer_singleconsumer/lfds711_queue_bounded_singleproducer_singleconsumer_enqueue.c
        )

add_library(lfds711 STATIC ${lfds711_SRC_FILES})
target_include_directories(lfds711 PUBLIC liblfds711/inc)
