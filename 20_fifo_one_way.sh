# ========================================================================================
# Name:       Priyansh Agrahari
# Reg. No.:   MT2024120
# Date:       20 September 2024

# 20. Write two programs so that both can communicate by FIFO -Use one way communication.
# ========================================================================================

if $(ls 20.fifo 2>/dev/null)
then
    rm 20.fifo
fi
gcc -o 20a.o 20a_fifo_send.c
./20a.o &
gcc -o 20b.o 20b_fifo_recv.c
./20b.o

rm 20a.o 20b.o 20.fifo

<<sample
Sample Execution:

$ sh 20_fifo_one_way.sh 
created and opened FIFO pipe ./20.fifo, will write a message...
wrote 17 bytes to pipe
read from pipe: message from 20a

sample