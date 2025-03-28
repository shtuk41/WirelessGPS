#ifndef		__CIRCULAR_BUFFER_H
#define		__CIRCULAR_BUFFER_H


#define CIRC_BUFFER_SIZE	512

#define		OPERATION_OK		0
#define		ERROR_OVERRIDE		-1	//overriding unread data
#define		ERROR_OVERREAD		-2	//reading unwritten data
#define 	NULL_ARGUMENT 		-3


typedef struct 
{
	char	buff[CIRC_BUFFER_SIZE];
	unsigned int		iInsertPos;	
	unsigned int		iReadPos;
} circular_buffer;

int circ_buff_insert(volatile circular_buffer *p, char c);
int circ_buff_insert_mult(volatile circular_buffer *p, char *c, unsigned int size);
int circ_buff_read_next(volatile circular_buffer *p, char *next);
int circ_buff_read_between_inclusive(volatile circular_buffer *p, char c1, char c2, char **str,int *size);




#endif	
