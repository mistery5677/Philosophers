// #include "includes/philosophers.h"

// void *computation()
// {
//     printf("Computation\n");
//     return NULL;
// }

// int main()
// {
//     pthread_t thread1;  //Vou declarar um thread
//     pthread_t thread2;
//     pthread_t thread3;
//     pthread_t thread4;  //Vou declarar um thread
//     pthread_t thread5;
//     pthread_t thread6;
//     pthread_create(&thread1, NULL, computation, NULL); //Vou dizer que o thread1, vai ter uma funcao "associada"
//     pthread_create(&thread2, NULL, computation, NULL);
//     pthread_create(&thread3, NULL, computation, NULL);
//     pthread_create(&thread4, NULL, computation, NULL); //Vou dizer que o thread1, vai ter uma funcao "associada"
//     pthread_create(&thread5, NULL, computation, NULL);
//     pthread_create(&thread6, NULL, computation, NULL);
//     pthread_join(thread5, NULL); //Vou chamar o thread previamente criado 

//     return 0;
// }


// FORMA DE PASSAR VALOR ENTRE THREADS

// void *computation(void *add)
// {
//     long *add_num = (long *) (add);
//     printf("Add: %ld\n", *add_num);
//     return NULL;
// }

// int main()
// {
//     pthread_t thread1; 

//     long value1 = 1;

//     pthread_create(&thread1, NULL, computation, (void *) &value1);

//     pthread_join(thread1, NULL);

//     return 0;
// }


// Ver a diferenca entre um programa multithread e single thread
// void *computation(void *add)
// {
//     long sum = 0;
//     long *add_num = (long *) (add);

//     for (long i = 0; i < 1000000000; i++)
//         sum += *add_num;
//     printf("Add: %ld\n", *add_num);
//     return NULL;
// }

// int main()
// {
//     pthread_t thread1; 
//     pthread_t thread2;

//     long value1 = 1;
//     long value2 = 2;

//     //  SINGLE THREAD
//     // computation((void *) &value1);
//     // computation((void *) &value2);

//     // PARALLEL EXECUTION
//     // pthread_create(&thread1, NULL, computation, (void *) &value1);
//     // pthread_create(&thread2, NULL, computation, (void *) &value2);

//     // pthread_join(thread1, NULL);
//     // pthread_join(thread2, NULL);

//     // SINGLE THREAD 
//     pthread_create(&thread1, NULL, computation, (void *) &value1);
//     pthread_join(thread1, NULL);

//     pthread_create(&thread2, NULL, computation, (void *) &value2);
//     pthread_join(thread2, NULL);
//     return 0;
// }


// Neste exemplo estamos a testar um erro que pode acontecer chamado Data Races.
// Ou seja, quando dois threads tentam mexer no mesmo valor/endereco de memoria ao mesmo tempo.
// int balance = 0;


// // write the new balance (after as simulated 1/4 second delay)
// void write_balance(int new_balance)
// {
//   usleep(250000);
//   balance = new_balance;
// }

// // returns the balance (after a simulated 1/4 seond delay)
// int read_balance()
// {
//   usleep(250000);
//   return balance;
// }

// // carry out a deposit
// void* deposit(void *amount)
// {
//   // retrieve the bank balance
//   int account_balance = read_balance();

//   // make the update locally
//   account_balance += *((int *) amount);

//   // write the new bank balance
//   write_balance(account_balance);

//   return NULL;
// }

// int main()
// {
//   // output the balance before the deposits
//   int before = read_balance();
//   printf("Before: %d\n", before);

//   // we'll create two threads to conduct a deposit using the deposit function
//   pthread_t thread1;
//   pthread_t thread2;

//   // the deposit amounts... the correct total afterwards should be 500
//   int deposit1 = 300;
//   int deposit2 = 200;

//   // create threads to run the deposit function with these deposit amounts
//   pthread_create(&thread1, NULL, deposit, (void*) &deposit1);
//   pthread_create(&thread2, NULL, deposit, (void*) &deposit2);

//   // join the threads
//   pthread_join(thread1, NULL);
//   usleep (250000); // Esta e a solucao para nao termos data races, ou seja, so vai executar o segundo thread, apos o tempo acabar
//   pthread_join(thread2, NULL);

//   // output the balance after the deposits
//   int after = read_balance();
//   printf("After: %d\n", after);

//   return 0;
// }


// Outro exemplo de data races, caso a gente coloque um valor alto
//  de incrementacoes, ambos os threads vao tentas subescrever no mesmo sitio
// int mails = 0;

// void *routine()
// {
//     for (int i = 0; i < 100000; i++)
//         mails++;
//     return NULL;
// }

// int main()
// {
//     pthread_t p1, p2;
//     if (pthread_create(&p1, NULL, &routine, NULL) != 0)
//         return 1;
//     if (pthread_create(&p2, NULL, &routine, NULL) != 0)
//         return 2;
//     if (pthread_join(p1, NULL) != 0)
//         return 3;
//     if (pthread_join(p2, NULL) != 0)
//         return 4;
//     printf("Number of mails: %d\n", mails);
//     return 0;
// }

// Mutex --> Prevente que caso algum outro thread tente executar ao mesmo tempo, com o valor ja encrementado
// ele nao vai conseguir por causa do lock.

// int mails = 0;
// pthread_mutex_t mutex; // Era como se fosse um thread, para o sistema perceber quando este thread acabar a execucao, os outros podem continuar

// void *routine()
// {
//     for (int i = 0; i < 100000; i++)
//     {
//         pthread_mutex_lock(&mutex); // Caso haja um data race, vai prevenir que o segundo thread, tente correr o programa
//         mails++;
//         pthread_mutex_unlock(&mutex);
//     }
//     return NULL;
// }

// int main()
// {
//     pthread_t p1, p2;
//     pthread_mutex_init(&mutex, NULL);
//     if (pthread_create(&p1, NULL, &routine, NULL) != 0)
//         return 1;
//     if (pthread_create(&p2, NULL, &routine, NULL) != 0)
//         return 2;
//     if (pthread_join(p1, NULL) != 0)
//         return 3;
//     if (pthread_join(p2, NULL) != 0)
//         return 4;
//     pthread_mutex_destroy(&mutex);
//     printf("Number of mails: %d\n", mails);
//     return 0;
// }

// int balance = 0;

// int read_balance()
// {
//     usleep(250000);
//     return balance;
// }

// void write_balance(int new_balance)
// {
//     usleep(250000);
//     balance = new_balance;
// }

// void *deposit(void *amount)
// {
//     int account_balance = read_balance();

//     account_balance += amount;

//     write_balance(account_balance);

//     return NULL;
// }

// int main()
// {
//     int before = read_balance();
//     printf("Before: %d\n", before);
    
//     deposit(300);
//     deposit(200);

//     int after = read_balance();
//     printf("After: %d\n", after);

//     return 0;
// }

// NOTE: Deadlock e quando tentamos dar lock ao mutex, duas vezesx

// TESTANDO COM MUITOS THREADS //

// #include <stdio.h>       
// #include <pthread.h>
// #include <sys/time.h>
// #include <stdlib.h>
// #include <unistd.h>

// #ifndef NUM_THREADS
// #define NUM_THREADS 10
// #endif


// pthread_mutex_t print_mutex;  // Declaração do mutex
// int mails = 0;
// void *funcao(void *argumentos)
// {
//    pthread_mutex_lock(&print_mutex);  // Bloqueia o mutex
//    for(int x = 0; x <= 100000; x++)
//     mails++;
//    pthread_mutex_unlock(&print_mutex);  // Desbloqueia o mutex
//    return NULL;
// }

// int main()
// {
//   pthread_t threads[NUM_THREADS - 2];
//   int i;

//   // Inicializa o mutex antes de criar as threads
//   pthread_mutex_init(&print_mutex, NULL);

//   for(i = 0; i < NUM_THREADS - 2; i++)
//   {
//     printf("vou criar o thread %d\n", i);
//        pthread_create(&threads[i], NULL, funcao, &i);
//   }


//   printf("Thread principal a esperar a terminação das threads criadas NUM_THREADS\n");
//         for(i = 0; i < NUM_THREADS - 2; i++)
//             pthread_join(threads[i], NULL);  // Espera pela conclusão de cada thread
//     printf("mails %d\n", mails);
//   // Destroi o mutex após o uso
//   pthread_mutex_destroy(&print_mutex);

//   return 0;
// }
// // }
