# ForThreads  
---  
A tiny single-header-file library for running parallel for loops, using multi-threading.  
At startup, ForThreads queries the current CPU for its optimal thread count.  
Loop iterations are divided evenly between available threads.  

  * Double the cores, boosts speed by 1.6x.
  * Hypertheading boosts speed by 1.3x.

**WARNING**: Iterations run concurrently, so avoid causing race conditions.  
  
---  
**USAGE:**  

    #include "for_threads.h"

<u>*Single-threaded loop (for reference):*</u>  

    for(int i=0; i<100; ++i) {  // Loop from 0 to 99
        printf("i=%d\n", i);    // Print i value
    }                           // No Semi-colon needed


<u>*Equivalent Multi-threaded loop :*</u>  

    for_threads(100) {          // Loop from 0 to 99, using i as loop counter.
        printf("i=%d\n", i);    // Warning: May run out of order: Don't write to shared vars!
    };                          // Semi-colon is required :(
