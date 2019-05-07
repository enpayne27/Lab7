#include "string.h"
#include "circularBuffer.h"

// Initialize the struct commBuffer_t to zero
void initBuffer(commBuffer_t* comm, uint8_t type){
    comm -> head = 0;
    comm -> tail = 0;
    comm -> type = type;
    comm -> MessageCount = 0;
    comm -> bufferSize = 0;
}

// Test if a complete message is in buffer delimiter is '\n'
// Read only, checking MessageCount - doesn't matter how many, just if one is there
uint8_t haveMessage(commBuffer_t* comm){
  // If MessageCount == 0 (false) || == 1 (true) then return
  if(comm -> MessageCount) return 1;
  else return 0;
}

// Put character in buffer and update head - focused on Tx
// Using haveMessage - could check for delimiter here and change MessageCount
void putChar(commBuffer_t* comm, char ch){
  // Handles maximum buff fill
  if(comm -> bufferSize >= MAXCOMMBUFFER - 1){
	if(ch == '\n'){
		comm -> bufferSize += 1;
		comm -> MessageCount += 1;
	}
    comm -> buffer[comm -> head] = '\0';
    return;
  }
  // Handle delimiter (translate into null character)
  if(ch == '\n'){
    ch = '\0';
    comm -> MessageCount += 1;
  }
  // Check if head does not exceed maximum buffer size
  if(comm -> head < MAXCOMMBUFFER - 1){
    comm -> buffer[comm -> head] = ch;
    comm -> head += 1;
    comm -> bufferSize += 1;
  }
  // If so, return to start and then put character in buffer
  else{
    comm -> buffer[comm -> head] = ch;
    comm -> head = 0;
    comm -> bufferSize += 1;
  }
}

// Get character from buffer and update tail - focused Rx
char getChar(commBuffer_t* comm){
  // Handle delimiter (translate into newline)
  char ch = comm->buffer[comm -> tail];

  if(ch == '\0'){
    ch = '\n';
    comm -> MessageCount -= 1;
  }
  if(comm -> head == comm -> tail && ch == '\n'){
	comm -> bufferSize -= 1;
  }
  // Check if head does not exceed maximum buffer size
  else if(comm -> tail < MAXCOMMBUFFER - 1){
    comm -> tail += 1;
    comm -> bufferSize -= 1;
  }
  // If so, return to start and then put character in buffer
  else{
    comm -> tail = 0;
    comm -> bufferSize -= 1;
  }
  return ch;
}

// Put C string into buffer - utilize putChar
void putMessage(commBuffer_t* comm, char* str, uint8_t length){
  for(int i = 0; i < length; i++){
	  putChar(comm, str[i]);
  }
}

// Get C string from buffer - utilize getChar
void getMessage(commBuffer_t* comm, char* str){
	int i = 0;
    while(1){
      str[i] = getChar(comm);
      if (str[i] == '\n') break;
      i++;
    }
}

// Get Size of Buffer
int getBufferSize(commBuffer_t* comm){
  //(head-tail+maxSize) % maxSize
  return comm -> bufferSize;
}
