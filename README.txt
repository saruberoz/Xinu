/*CS 354 Spring 2012*/
/*Lab 3: Interprocess Communication Using Bounded Buffers In Xinu */
/*Created by : Wilson Sumanang
  Date       : 26 February 2012*/
Submitted on March 4, 2012: 11.33PM
*****************README***************************

I was building the pipe structure by having a circular buffer of a maximum fixed size (bounded buffer)
In which I used implementation of head and tail to keep track of reading and writing.
I used 2 semaphore so that multiple threads can communicate using this bounded buffer.
1st semaphore is used so that read will use to wait until there are items that has been write.(emptysem)
2nd semaphore is used so that write will use to wait until there is space that has been read.(fullsem)

*****FILE THAT HAS BEEN CREATED AND EDITED ACCORDINGLY:*****
1.---pipe.h---
Created the struct for the interprocess communication

2.---xinu.h---
Include the pipe.h

3.---kernel.h---
Include the pipe data type

4.---initialize.c---
Initialize all the struct pipe entry to certain value and semaphore

5.---pipcreate.c---
Creating a new pipe whenever the pipe queue is empty and return the pipe id that has been created.
create the new pipe id using a newpipid function

6.---pipdelete.c---
Delete a pipe by freeing and resetting whenever this function is called.
return system error if pipe id is wrong and non owner call this function

7.---pipconnect.c---
Connecting pipe, check the process id of the owner, writer, and reader, return sys err if anything wrong.
return system error if process is empty. return system error if pipe id is wrong.

8.---pipdisconnect.c---
Disconnecting pipe, check the process id trying to call the disconnect function return sys err if it is wrong.
Return system error if pipe id that is going to be disconnect is wrong,

9.---pipwrite.c---
Write to buffer if buffer is full then start writing from the beginning by using modulus 256
Return system error if wrong pipe

10.---pipread.c---
Read from buffer if buffer is full then reset reading from the beginning by using modulus 256
Return system error if wrong pipe

11.---kill.c---
Extra credit to exit gracefully for a process and kill and reset the pipe value.

12.---main.c---
Implementation on the producer and consumer case

13.---prototype.h---
Add all syscall function for the pipe

14.---Makerules---
Adding all the *.c file that has been created to be compiled accordingly


***********************PLEASE READ THIS!!!!!!!NOTIFY!!!!!!!!!!!!!!!!!!!********************************
fgetc doesnt work in my program, so it printing everything instead of printing by n lines.
I assume this is because for creating a pipe like "grep" in linux we have to introduce a mutex lock.
in which it is for reading and writing one at a time


******************DONT READ THIS!!!! INFORMATION ON TEST CASES!!!*****************
/* hint and test cases for me only */
LOOP USING NPIPE!! and PIPESIZE
similar to proctab, there should be smth. like opieptab which is seen system wide
most of th data manipulation will be using this pipetab only
pipid32 is a typedef of int
a sample test case
consider during an ongoing pipe if the pipe owner try pipdisconnect/pipdelete
then 	-free pipe internal buffer, if you are getting memory from heap
	-delete associated sempahore
	-reader/writer who was waiting on that will receive syserr, so catch that and exit properly
1. State machine related. Example: Writing to an closed pipe.
2. Does the reader/writer block when it has to?
3. Does the reader/writer read/write when it has to?
4. Is any data lost/corrupted?
5. Pipe disconnect when reader/writer blocked. 
6. Pipe delete when reader/writer blocked.
