#include "..\..\..\templeware\hooks\hooks.h"
#include "..\..\..\templeware\interfaces\interfaces.h"

#include "cutlbuffer.h"

CUtlBuffer::CUtlBuffer(int a1, int size, int a3)
{
	I::ConstructUtlBuffer(this, a1, size, a3);
}

void CUtlBuffer::ensure(int size)
{
	I::EnsureCapacityBuffer(this, size);
}

void CUtlBuffer::PutString(const char* szString)
{

	I::PutUtlString(this, szString);
}
