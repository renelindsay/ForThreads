// Rene Lindsay 2017
//---------------------------Parallel For-loops--------------------------
// Run for-loops faster, by using multi-threading.
// At startup, queries CPU for optimal thread count.
// Loop iterations are divided evenly between available threads.
// - Double the cores, boosts speed by 1.6x.
// - Hypertheading boosts speed by 1.3x.
// WARNING: Iterations run concurrently, so avoid causing race conditions.
//
// USAGE EXAMPLE:
// Single-threaded loop for reference:
//     for(int i = 0; i< 100; ++i) {  // Loop from 0 to 99
//         printf("i=%d\n", i);       // Print i value
//     }                              // No Semi-colon needed.
//
// Equivalent Multi-threaded loop :
//    for_threads(100) {              // Loop from 0 to 99, using i as loop counter.
//        printf("i=%d\n", i);        // Warning: May run out of order: Dont write to shared vars!
//    };                              // Semi-colon is required :(
//
//-----------------------------------------------------------------------

#ifndef FOR_THREADS_H
#define FOR_THREADS_H

//#include <stdio.h>
#include <thread>
#include <functional>

#define for_i(COUNT) for(int i=0; i<COUNT; ++i)            // Single-threaded loop
#define for_threads(COUNT) ForThread(COUNT)=[&](int i)     // Multi-threaded loop

typedef std::function<void(int)> thread_fn_t;

class ForThreads {
    int cnt = 0;                       // iteration count
    std::vector<std::thread> threads;  // thread pool

    static void run_batch(thread_fn_t fn, int start, int end) {
        //printf("start=%d end=%d count=%d\n", start, end, end-start);
        for(int i=start; i<end; ++i) fn(i);
    }

public:
    ForThreads() {max_threads(std::thread::hardware_concurrency());} // Default to optimal thread-count
    void max_threads(int count) { threads.resize(count);}            // Set desired thread-count
    int max_threads() {return threads.size();}                       // Get current thread-count

    ForThreads& operator()(int count) {
        cnt = count;
        return *this;
    }

    void operator=(thread_fn_t fn) {
        if(cnt==1) fn(0);
        if(cnt<2) return;

        uint num_threads = std::min(cnt, max_threads());
        uint batch_size = cnt / num_threads;
        uint batch_left = cnt % num_threads;
        //printf("Threads: %d  (Batch size=%d) (left=%d)\n", num_threads, batch_size, batch_left);

        int start = 0;
        for_i(num_threads) {  // divide into thread-batches
            int end = start + batch_size + (i < batch_left ? 1 : 0);
            threads[i] = std::thread(run_batch, fn, start, end);
            start = end;  // start next batch where this one ends
        }
        for_i(num_threads) threads[i].join(); // wait for threads to finish
    }

}ForThread;

#endif
