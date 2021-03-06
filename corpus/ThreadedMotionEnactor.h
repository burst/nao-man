/**
 * This class is an abstraction of the connection between the Switchboard and
 * the lower level access to robot hardware. Since this connection may change
 * often, and is different for the simulator and the robot, this class provides
 * a contract to fulfill to provide that connection.
 *
 * Each MotionEnactor is in charge of passing joint commands to the low-level.
 * Typically, this will be done by starting a high-priority thread which recurs
 * close to the timestep (20 ms) as possible.
 * Each enactor must call getNextJoints on the switchboard, and relay that
 * information correctly.
 */

#ifndef _ThreadedMotionEnactor_h_DEFINED
#define _ThreadedMotionEnactor_h_DEFINED

#include <iostream>
#include <pthread.h>

#include "MotionEnactor.h"

class ThreadedMotionEnactor : public MotionEnactor {
public:
    ThreadedMotionEnactor()
        : MotionEnactor(), running(false){};
    virtual ~ThreadedMotionEnactor() { }

    void start() {
#ifdef DEBUG_INITIALIZATION
        cout << "ThreadedEnactor::initializing" << endl;
        cout << "  creating threads" << endl;
#endif
        fflush(stdout);

        running = true;

        // set thread attributes
        pthread_attr_t attr;
        pthread_attr_init (&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
        // create & start thread.
        pthread_create(&enactor_thread, &attr, runThread, (void *)this);
        // destroy the used attributes
        pthread_attr_destroy(&attr);
    }

    void stop() {
        running = false;
    }

    static void* runThread(void *enactor) {
        // This is a common routine for all possible enactors.
        ((ThreadedMotionEnactor*)enactor)->run();
        pthread_exit(NULL);
    }

    virtual void run() = 0;

protected:
    bool running;
    pthread_t enactor_thread;
};

#endif
