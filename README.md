# MIPT programming, 2 курс

Программы, написанные на 2 курсе МФТИ (ГУ) в рамках курса информатики.

***


*   [безопасное копирование файлов](https://github.com/canorbal/2_year_MIPT/tree/master/copying_files)

        user@ubuntu:~$ gcc cp.c -o cp.out
        user@ubuntu:~$ cat example.txt
        Hello, world!
        user@ubuntu:~$ ./cp.out example.txt example_1.txt
        user@ubuntu:~$ cat example_1.txt
        Hello, world!
        user@ubuntu:~$

*   [запуск процессов в соответствии с расписанием](https://github.com/canorbal/2_year_MIPT/blob/master/fork/executor.c)

        формат записи расписания:

        time_0 process_0 args
        time_1 process_1 args
        time_2 process_2 args
        ...
        time_n process_n argc


        user@ubuntu:~$ gcc executor.c -o executor.out
        user@ubuntu:~$ cat example.txt
        10 sleep 5
        6 echo Hello world
        2 ls -all
        1 sleep 10
        user@ubuntu:~$ ./executor.out example.txt
        total 96
        drwxr-xr-x   9 Roman  staff    306 Aug 11 13:15 .
        drwxr-xr-x@ 18 Roman  staff    612 May 17 14:24 ..
        -rw-r--r--@  1 Roman  staff   6148 Nov 12  2016 .DS_Store
        -rwxr-xr-x@  1 Roman  staff     51 Aug 11 13:15 example.txt
        -rw-r--r--@  1 Roman  staff   7867 Feb 20 21:41 executor.c
        -rwxr-xr-x   1 Roman  staff  13840 Aug 11 13:15 executor.o
        -rwxr-xr-x@  1 Roman  staff    785 Jan 12  2017 fork.c
        -rwxr-xr-x   1 Roman  staff    697 Feb 14 16:46 process.c
        -rw-r--r--   1 Roman  staff     51 Aug 11 13:15 tmp_sorted_programs.txt
        Hello world
        process echo ended with code 0
        process ls ended with code 0
        process sleep ended with code 0
        process sleep ended with code 0
        user@ubuntu:~$

*   [shell](https://github.com/canorbal/2_year_MIPT/blob/master/shell_implementation/shell.c)

Реализация shell с пайплайнами и подсчетом количества байт на выходе

        user@ubuntu:~$ gcc shell.c -o shell.out
        user@ubuntu:~$ ./shell.out
        ***********SHELL*************
        **write down shell commands**

        ls
        age_profile_train.csv
        pipe.c
        shell.c
        shell.o
        readed 45 bytes
        ***********SHELL*************
        **write down shell commands**

        head shell.c
        #include <errno.h>
        #include <string.h>
        #include <stdio.h>
        #include <stdlib.h>
        #include <sys/wait.h>
        #include <fcntl.h>
        #include <unistd.h>

        #define MAX_STRING_SIZE 256
        #define MAX_PROG_NAME_SIZE 16
        readed 198 bytes
        ***********SHELL*************
        **write down shell commands**

        who | wc -l
              3
        readed 9 bytes
        ***********SHELL*************
        **write down shell commands**




*   [копирование файлов через сигналы](https://github.com/canorbal/2_year_MIPT/blob/master/signal_copying/signalcp.c)

Занимает гораздо больше времени, чем cp

        user@ubuntu:~$ gcc signalcp.c -o signalcp.out
        user@ubuntu:~$ cat example.txt
        Hello, world!
        user@ubuntu:~$ ./signalcp.out example.txt example_1.txt
        user@ubuntu:~$ cat example_1.txt
        Hello, world!
        user@ubuntu:~$

*   [эмулятор работы офиса (задача на потоки)](https://github.com/canorbal/2_year_MIPT/blob/master/threads/office.c)

        user@ubuntu:~$ gcc office.c -o office.out -lpthread
        user@ubuntu:~$ ./office.out

        ##############################################################
	                     OFFICE.
        OFFICE is a model of clerks and scanners work in office.

        ##############################################################
	                     Description.
        ./office.out NC ND TD NS TS L
        NC is number of clerks
        ND is number of documents
        TD is time for one document
        NS is number of scanners
        TS is time for one document to scan
        L is the length of queue
        All time should be in seconds. All numbers should be positive
        #############################################################
        user@ubuntu:~$ ./office.out 1 2 3 4 5 6
        Document 0x0101 ready
        Document 0x0102 ready
        user@ubuntu:~$



*   [класс трёхмерного вектора и основных методов](https://github.com/canorbal/2_year_in_MIPT/blob/master/7sem/)

*   [класс матриц 3×3 и рациональных дробей](https://github.com/canorbal/2_year_in_MIPT/blob/master/8sem/)

*   [материалы по наследованию](https://github.com/canorbal/2_year_in_MIPT/tree/master/9sem/inheritance)

*   [math_lib](https://github.com/canorbal/2_year_in_MIPT/tree/master/9sem/math_lib) – вектора и матрицы над полем рациональных чисел

*   [материалы](https://github.com/canorbal/2_year_in_MIPT/tree/master/10sem/people) по абстрактным классам и виртуальным функциям

*   [шаблоны](https://github.com/canorbal/2_year_in_MIPT/tree/master/10sem/templates) – реализован шаблон классов векторов и матриц над int, double и fraction (<- последний класс определен в frac.h)

*   [шаблоны, обработка исключений](https://github.com/canorbal/2_year_in_MIPT/tree/master/11sem/) – реализован шаблон классов на n-мерными векторами и матрицами произвольных размеров
