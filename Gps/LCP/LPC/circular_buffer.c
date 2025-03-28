#include <stdlib.h>
#include <string.h>
#include "circular_buffer.h"


int circ_buff_insert(volatile circular_buffer *p, char c)
{
	int iError = OPERATION_OK;

	p->buff[p->iInsertPos] = c;

	p->iInsertPos++;

	if (p->iInsertPos == CIRC_BUFFER_SIZE)
		p->iInsertPos = 0;

	if (p->iInsertPos == p->iReadPos)
		iError =  ERROR_OVERRIDE;

	return iError;
}

int circ_buff_insert_mult(volatile circular_buffer *p, char *c, unsigned int size)
{
	int iError = OPERATION_OK;

	int i;

	for (i = 0; i < size;i++)
	{
		p->buff[p->iInsertPos] = c[i];

		p->iInsertPos++;

		if (p->iInsertPos == CIRC_BUFFER_SIZE)
			p->iInsertPos = 0;

		if (p->iInsertPos == p->iReadPos)
			iError =  ERROR_OVERRIDE;
	}


	return iError;
}

int circ_buff_read_next(volatile circular_buffer *p, char *next)
{
	int iError = OPERATION_OK;

	if (p->iReadPos == p->iInsertPos)
	{
		return (iError = ERROR_OVERREAD);
	}

	*next = p->buff[p->iReadPos];

	p->iReadPos++;

	if (p->iReadPos == CIRC_BUFFER_SIZE)
		p->iReadPos = 0;

	return iError;	
}

int circ_buff_read_between_inclusive(volatile circular_buffer *p, char c1, char c2, char **str,int *size)
{
  
   if (!size || !p)
     return NULL_ARGUMENT;
  
   int 			iError 			= OPERATION_OK;
   *size 					= 0;
   unsigned int 	iStart 			= p->iReadPos;
   char 		name[CIRC_BUFFER_SIZE] ={'\0'};
   char 		next;
    
    do
    {
	int error = circ_buff_read_next(p,&next);
	
	if (error == ERROR_OVERREAD)
	{
	    *size = 0;
	    return ERROR_OVERREAD;
	}
	
	if (*size  > 0)
	{
	  if (next == c1)
	  {
	    *size = 0;
	  }
	  
	   name[*size] = next;
	   (*size)++;
	   
	   if (next == c2)
	     break;
	}	
	else if (*size  == 0 && next == c1)
	{
	  name[*size ] = next;
	   (*size)++;
	}
    }while (iStart != p->iReadPos);
    
    if (*size == CIRC_BUFFER_SIZE)
      *size = 0;
    else
    {
	*str = (char*)malloc(*size);
	memcpy(*str,name,*size);
    }
    
    
    return iError;
}
