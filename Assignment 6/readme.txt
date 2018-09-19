I did not run into many issues as I have done a project on optimizing
multithreaded performance in CS33 in the past. Thus, I am still somewhat 
familiar on what needs to be done in the multithreading process. 

Some issues I did face, however, was that I was unfamiliar with the code on
ray tracing, so it was difficult to interpret the program at first. Once I 
was able to extrapolate which parts of the program were important for the 
multithreading process, it became easier to implement pthreads.

As for performance, by looking at the output of make-log.txt, we can see 
that using more and more threads, up to 8, made the program run faster than 
the last. However, using more than 8 threads could perhaps make the program 
run slower than the 8-threaded version because of the overhead of using 
that many threads.