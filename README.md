## **PHILOSOPHERS**

<p align="center" width="100%">
    <img width="33%" src="https://github.com/Arcane-Jill/images/blob/main/philosophersm.png">
</p>

Philosophers is a rank 3 project at **Hive** Helsinki, which is a school in the 42 network. This project introduced me to threads, multi-threading and 
mutexes. This was a really fun project, that I enjoyed immensely. the debugging was actually the most fun part. I enjoyed spending time working out where
I needed to include a mutex to protect a variable to avoid data race. I really learned to think about what my code was doing and in what order.

### **Description**

From the subject: *Here are the key things you need to know to succeed in this assignment:

• One or more philosophers sit at a round table. There is a large bowl of spaghetti in the middle of the table.\
• The philosophers take turns eating, thinking, and sleeping. While they are eating, they are not thinking nor sleeping; \
while thinking, they are not eating nor sleeping; and, of course, while sleeping, they are not eating nor thinking.\
• There are also forks on the table. There are as many forks as philosophers.\
• Since eating spaghetti with just one fork is impractical, a philosopher must pick up both the fork to their right and the fork to their left before eating.\
• When a philosopher has finished eating, they put their forks back on the table and start sleeping. Once awake, they start thinking again. The simulation stops when
a philosopher dies of starvation.\
• Every philosopher needs to eat and should never starve.\
• Philosophers do not communicate with each other.\
• Philosophers do not know if another philosopher is about to die. \
• Needless to say, philosophers should avoid dying!* \

There was also a bonus project, where we could repeat the whole thing, but this time with semaphores. I did not do the bonus, but I might return to it in 
the future.

### **How to use**

1. Clone the repository:
   ```
   git clone git@github.com:natalie-mein/philosophers.git philo && cd philo
   ```
2. Make
   ```
   make
   ```
   This will generate a 'philo' executable
3. Usage examples
   ```
   ./philo 4 500 200 200 5
   ```
   The first number represents the number of philosophers. \
   The second number is the time, in milliseconds, it will take the philosopher to die, after completing his last meal. \
   The third number is how long they should spend eating, in milliseconds. \
   The fourth number is how long they should spend sleeping, in milliseconds.\
   The fifth number is optional, and represents the minimum number of times each philosopher should eat. \
   
