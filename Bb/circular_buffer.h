#ifndef		__CIRCULAR_BUFFER_H
#define		__CIRCULAR_BUFFER_H

#define CIRC_BUFFER_SIZE	2048

#define		OPERATION_OK		0
#define		ERROR_OVERRIDE		-1	//overriding unread data
#define		ERROR_OVERREAD		-2	//reading unwritten data


typedef struct 
{
	char	buff[CIRC_BUFFER_SIZE];	
	int		iInsertPos;	
	int		iReadPos;
} circular_buffer;

int circ_buff_insert(circular_buffer *p, char c);
int circ_buff_insert_mult(circular_buffer *p, char *c);
int circ_buff_read_next(circular_buffer *p, char *next);

#endif