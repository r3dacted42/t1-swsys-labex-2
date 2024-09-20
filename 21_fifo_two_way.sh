# ========================================================================================
# Name:       Priyansh Agrahari
# Reg. No.:   MT2024120
# Date:       20 September 2024

# 21. Write two programs so that both can communicate by FIFO -Use two way communications.
# ========================================================================================

if $(ls 21.fifo 2>/dev/null)
then
    rm 21.fifo
fi
gcc -o 21a.o 21a_fifo_p1.c
./21a.o &
gcc -o 21b.o 21b_fifo_p2.c
./21b.o

rm 21a.o 21b.o 21.fifo

<<sample
Sample Execution:

$ sh 21_fifo_two_way.sh 
created and opened FIFO pipe ./21.fifo, will write a message...
wrote 17 bytes to pipe
read 17 bytes from pipe: message from 21a
read 17 bytes from pipe: message from 21b
wrote 17 bytes to pipe

sample