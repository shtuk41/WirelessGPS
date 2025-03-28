
#include "stdafx.h"
#include "circular_buffer.h"




int circ_buff_insert_mult(circular_buffer *p, char *c)
{
	int iError = OPERATION_OK;

	int i = 0;

	for (i; i < sizeof(c);i++)
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

int circ_buff_read_next(circular_buffer *p, char *next)
{
	int iError = OPERATION_OK;

	if (p->iReadPos == p->iInsertPos)
		iError = ERROR_OVERREAD;

	*next = p->buff[p->iReadPos];

	p->iReadPos++;

	if (p->iReadPos == CIRC_BUFFER_SIZE)
		p->iReadPos = 0;

	return iError;
}