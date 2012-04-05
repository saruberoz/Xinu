/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void consume(pipid32 pip);
void produce(pipid32 pip);

/************************************************************************/
/*									*/
/* main - main program for testing Xinu					*/
/*									*/
/************************************************************************/

int main(int argc, char **argv)
{
  //umsg32 retval;
  
  /* Creating a shell process */
  /*
   *	resume(create(shell, 4096, 1, "shell", 1, CONSOLE));
   * 
   *	retval = recvclr();
   *	while (TRUE) {
   *		retval = receive();
   *		kprintf("\n\n\rMain process recreating shell\n\n\r");
   *		resume(create(shell, 4096, 1, "shell", 1, CONSOLE));
   }
   */
  
  // PRODUCER AND CONSUMER CASES
  kprintf("--------------Start ProdCom--------------\n\r");
  pipid32	pip;
  pid32		reader;
  pid32		writer;
  
  kprintf("--------------Creating Pipe--------------\n\r");
  if(SYSERR == (pip = pipcreate())) {
    kprintf("-----------Error Creating Pipe-----------\n\r");
    return 0;
  }
  
  kprintf("Pipe ID Created: %d\n\r", pip);
  
  kprintf("---------Creating Consumer Proc---------\n\r");
  if(SYSERR == (reader = create(consume, 4098, 25, "read", 1, pip))) {
    kprintf("---------Error Consumer Process---------\n\r");
    return 0;
  }
  
  kprintf("---------Creating Producer Proc---------\n\r");
  if(SYSERR == (writer = create(produce, 4098, 25, "write", 1, pip))) {
    kprintf("---------Error Producer Process---------\n\r");
    return 0;
  }
  
  
  kprintf("connect pipe\n\r");
  if((pipconnect(pip, reader, writer) == SYSERR)) {
    kprintf("----------Error Connecting Pipe----------\n\r");
    return 0;
  }
  
  kprintf("------------Resuming Producer------------\n\r");	
  resume(writer);
  kprintf("------------Resuming Reader------------\n\r");
  resume(reader);
  
  kprintf("-------------Killing Process-------------\n\r");
  
  suspend((pid32)getpid);	
  
  kill(reader);
  kill(writer);
  
  kprintf("-----------Disconnecting Pipe------------\n\r");
  pipdisconnect(pip);
  kprintf("--------------Deleting Pipe--------------\n\r");
  pipdelete(pip);
  kprintf("---------------End ProcCom---------------\n\r");	
  
  return OK;
}

void consume(pipid32 pip) {
  char msg[600];
  int	lineNum = 0;
  int 	read = 0;
  int	i = 0;
//char	key;
  int	len = 600;
  
  // THIS WHILE TO KEEP THE PRODUCER KEEP RUNNING UNTIL IT IS BEING KILLED
  while(1) {
    
    kprintf("--------------Start Reading--------------\n\r");
    
    read = pipread(pip, msg, len);
    
    if(read == 0) {
      continue;
      
    }
    
    kprintf("String of message: %s\r\n", msg);
    kprintf("Length of message that has been read: %d\r\n", read);
    
    while(i < read) {
      kprintf("Message that has been read %c\r\n", msg[i]);
      if(msg[i] == '\n') {
	lineNum++;
      }
      
      i++;
      
      // THIS DOESNT WORK, IF IT DOES, IT ALWAYS SKIP THE FGETC
      /*
      if(lineNum % 3 == 0 && lineNum != 0) {	
	kprintf("-------Press \"ENTER\" to continue-------");
	key = fgetc(stdin);
	kprintf("Key entered is: %c\n\r", key);
	
	if( key == '\r' ) {
	    continue;  
	} else if(key == '\n') {
	  kprintf("------------Continue Reading------------\n\r");
	  continue;
	}
	else if (key == 'q') {
	  kprintf("-------Stopping Reading and Exiting------\n\r");
	  break;
	}
      }*/
    }
  
    kprintf("---------------End Reading---------------\n\r");
    break;
  }
}

void produce(pipid32 pip) {
  
char input[600] = "12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890\0";  int	write = 0;

  kprintf("--------------Start Writing--------------\n\r");
    
  write = pipwrite(pip, msg, 600);
    
  kprintf("Successful writing this length : %d\n\r", write);
  kprintf("---------------End Writing---------------\n\r");
}
/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void consume(pipid32 pip);
void produce(pipid32 pip);

/************************************************************************/
/*									*/
/* main - main program for testing Xinu					*/
/*									*/
/************************************************************************/

int main(int argc, char **argv)
{
  //umsg32 retval;
  
  /* Creating a shell process */
  /*
   *	resume(create(shell, 4096, 1, "shell", 1, CONSOLE));
   * 
   *	retval = recvclr();
   *	while (TRUE) {
   *		retval = receive();
   *		kprintf("\n\n\rMain process recreating shell\n\n\r");
   *		resume(create(shell, 4096, 1, "shell", 1, CONSOLE));
   }
   */
  
  // PRODUCER AND CONSUMER CASES
  kprintf("--------------Start ProdCom--------------\n\r");
  pipid32	pip;
  pid32		reader;
  pid32		writer;
  
  kprintf("--------------Creating Pipe--------------\n\r");
  if(SYSERR == (pip = pipcreate())) {
    kprintf("-----------Error Creating Pipe-----------\n\r");
    return 0;
  }
  
  kprintf("Pipe ID Created: %d\n\r", pip);
  
  kprintf("---------Creating Consumer Proc---------\n\r");
  if(SYSERR == (reader = create(consume, 4098, 25, "read", 1, pip))) {
    kprintf("---------Error Consumer Process---------\n\r");
    return 0;
  }
  
  kprintf("---------Creating Producer Proc---------\n\r");
  if(SYSERR == (writer = create(produce, 4098, 25, "write", 1, pip))) {
    kprintf("---------Error Producer Process---------\n\r");
    return 0;
  }
  
  
  kprintf("connect pipe\n\r");
  if((pipconnect(pip, reader, writer) == SYSERR)) {
    kprintf("----------Error Connecting Pipe----------\n\r");
    return 0;
  }
  
  kprintf("------------Resuming Producer------------\n\r");	
  resume(writer);
  kprintf("------------Resuming Reader------------\n\r");
  resume(reader);
  
  kprintf("-------------Killing Process-------------\n\r");
  
  suspend((pid32)getpid);	
  
  kill(reader);
  kill(writer);
  
  kprintf("-----------Disconnecting Pipe------------\n\r");
  pipdisconnect(pip);
  kprintf("--------------Deleting Pipe--------------\n\r");
  pipdelete(pip);
  kprintf("---------------End ProcCom---------------\n\r");	
  
  return OK;
}

void consume(pipid32 pip) {
  char msg[600];
  int	lineNum = 0;
  int 	read = 0;
  int	i = 0;
//char	key;
  int	len = 600;
  
  // THIS WHILE TO KEEP THE PRODUCER KEEP RUNNING UNTIL IT IS BEING KILLED
  while(1) {
    
    kprintf("--------------Start Reading--------------\n\r");
    
    read = pipread(pip, msg, len);
    
    if(read == 0) {
      continue;
      
    }
    
    kprintf("String of message: %s\r\n", msg);
    kprintf("Length of message that has been read: %d\r\n", read);
    
    while(i < read) {
      kprintf("Message that has been read %c\r\n", msg[i]);
      if(msg[i] == '\n') {
	lineNum++;
      }
      
      i++;
      
      // THIS DOESNT WORK, IF IT DOES, IT ALWAYS SKIP THE FGETC
      /*
      if(lineNum % 3 == 0 && lineNum != 0) {	
	kprintf("-------Press \"ENTER\" to continue-------");
	key = fgetc(stdin);
	kprintf("Key entered is: %c\n\r", key);
	
	if( key == '\r' ) {
	    continue;  
	} else if(key == '\n') {
	  kprintf("------------Continue Reading------------\n\r");
	  continue;
	}
	else if (key == 'q') {
	  kprintf("-------Stopping Reading and Exiting------\n\r");
	  break;
	}
      }*/
    }
  
    kprintf("---------------End Reading---------------\n\r");
    break;
  }
}

void produce(pipid32 pip) {
  
char input[600] = "12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890\0";  int	write = 0;

  kprintf("--------------Start Writing--------------\n\r");
    
  write = pipwrite(pip, msg, 600);
    
  kprintf("Successful writing this length : %d\n\r", write);
  kprintf("---------------End Writing---------------\n\r");
}
