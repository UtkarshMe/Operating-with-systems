/**
 * A example of threads with mutex locking and unlocking. Every thread calls a
 * function with different arguments to print natural number values from lower
 * to upper.
 *
 * @author Utkarsh Maheshwari
 * @date 15 Sept, 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void *thread_start(void *args);
void do_something(int upper, int lower);


/**
 * Structure for storing thread info
 * tid The thread id generated by creating
 * t_num The index used by the program
 * args Arguments to be passed
 */
typedef struct thread_info {
    pthread_t tid;
    int t_num;
} thread_info_t;

/**
 * The mutex to be used by threads. Since the program is simple and only one
 * mutex is needed, define it globally and initialize once */
pthread_mutex_t *mutex = NULL;

/**
 * The runner function for threads
 * @param args The argument pointer
 */
void *thread_start(void *args)
{
    thread_info_t *info = NULL;
    
    /* Load thread info */
    info = args;

    /* Lock the mutex while thread runs. If the mutex is locked, the thread
     * will be in blocked state */
    pthread_mutex_lock(mutex);

    /* Do what the thread has to do */
    do_something(info -> t_num * 10, info -> t_num * 10 - 10);

    /* Unlock the mutex after running */
    pthread_mutex_unlock(mutex);
}


/**
 * Count from upper to lower
 * @param upper Upper value
 * @param lower Lower value
 */
void do_something(int upper, int lower)
{
    /* Count from lower to upper */
    while (lower < upper) {
        printf("%d ", lower);
        lower++;
    }
    printf("\n");
}


int main(int argc, char *argv[])
{
    int t_count;
    pthread_attr_t tattr;
    thread_info_t *t_info = NULL;
    void *retval = NULL;

    /* Send number of threads to run as a command line argument */
    if (argc != 2) {
        fprintf(stderr, "Usage: number of threads needed\n");
        exit(1);
    }

    /* Argument sent must be an interger */
    t_count = atoi(argv[1]);
    if (t_count < 0) {
        fprintf(stderr, "Usage: %d must be positive integer\n", t_count);
        exit(1);
    }

    /* Initialize thread arguments */
    pthread_attr_init(&tattr);

    /* Initialize mutex */
    mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(mutex, NULL);

    /* Allocate space for thread info */
    t_info = (thread_info_t *) malloc(sizeof(thread_info_t) * t_count);
    if (t_info == NULL) {
        fprintf(stderr, "Could not allocate memory\n");
        exit(1);
    }

    /* Create and run threads */
    for (int i = 0; i < t_count; ++i) {

        /* Save thread info */
        t_info[i].t_num = i + 1;

        /* Create the thread with the info and run. Pass the thread info to each
         * thread */
        if (pthread_create(&t_info[i].tid , &tattr, thread_start, &t_info[i])) {
            fprintf(stderr, "Could not create new thread\n");
            exit(1);
        }
    }

    /* Join the thread after completion */
    for (int i = 0; i < t_count; ++i) {
        if (pthread_join(t_info[i].tid, &retval)) {
            fprintf(stderr, "Thread %d could not join\n", t_info[i].tid);
            exit(1);
        }
    }

    /* Deallocate all memory */
    pthread_attr_destroy(&tattr);
    pthread_mutex_destroy(mutex);
    free(mutex);
    free(t_info);

    return 0;
}