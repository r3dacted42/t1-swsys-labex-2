# ========================================================================================
# Name:       Priyansh Agrahari
# Reg. No.:   MT2024120
# Date:       22 September 2024

# 32. Write a program to implement semaphore to protect any critical section.
#     a. rewrite the ticket number creation program using semaphore
#     b. protect shared memory from concurrent write access
#     c. protect multiple pseudo resources ( may be two) using counting semaphore
#     d. remove the created semaphore
# ========================================================================================

#### helper script to initialize the semaphores required in parts a, b, c of task 32 #####
echo "initializing semaphores needed for parts a,b,c...";
gcc -o bsem.o 31a_sem_bin.c
./bsem.o t 1>/dev/null
./bsem.o s 1>/dev/null
rm bsem.o
gcc -o csem.o 31b_sem_cnt.c
./csem.o r 5 1>/dev/null
rm csem.o
echo "successfully initialized 2 binary and 1 counting sems";