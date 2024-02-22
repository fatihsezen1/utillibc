#ifndef VECTOR_H_
#define VECTOR_H_

#include <stddef.h>
#include <stdbool.h>

#define NOT_FOUND	((size_t)(-1))	//max number of size_t
#define DEFAULT_CAP	12
#define true		1
#define false		0

#define GET_SIZE(pvec)			((pvec)->msize)
#define GET_CAP(pvec)			((pvec)->mcap)
#define GET_ITEM(pvec, idx)		((pvec)->mp[idx])

typedef int DATATYPE;

typedef struct tagVector {
	DATATYPE* mp;
	size_t msize;	//current size value of the dynamic array
	size_t mcap;	//capacity of dynamic array
}Vector, *PVector;

PVector CreateVector(void);
PVector CreateVectorWithCapacity(size_t cap);
PVector CreateVectorWithArray(const DATATYPE* parr, size_t cap);
PVector CreateFilledVector(size_t cap, DATATYPE val);
bool SetCapacity(PVector pvec, size_t newCap);
bool PushBack(PVector pvec, DATATYPE val);
bool PopBack(PVector pvec);
bool InsertItemToVec(PVector pvec, size_t idx, DATATYPE val);
bool EraseItemFromVec(PVector pvec, size_t idx);
bool ClearVec(PVector pvec);
bool IsVectorEmpty(PVector pvec);
bool EraseValFromVec(PVector pvec, DATATYPE val);
size_t FindIdxInVec(PVector pvec, DATATYPE val);
void ShrinkVec(PVector pvec);
void DestroyVec(PVector pvec);

#endif // VECTOR_H_