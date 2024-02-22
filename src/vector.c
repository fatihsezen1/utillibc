#include "vector.h"

PVector CreateVectorWithCapacity(size_t cap)
{
	PVector pvec = (PVector)malloc(sizeof(Vector));
	if (!pvec)
		return NULL;

	pvec->msize = 0;
	pvec->mcap = cap;
	pvec->mp = (DATATYPE*)malloc(cap * sizeof(DATATYPE));
	if (!pvec->mp) {
		free(pvec);
		return NULL;
	}

	return pvec;
}

PVector CreateVector(void)
{
	return CreateVectorWithCapacity(DEFAULT_CAP);
}

/*
  This function creates a vector with a given array.Using the memmove function,
  it copies the data from the parr array to the mp member of the pvec object.
*/
PVector CreateVectorWithArray(const DATATYPE* parr, size_t cap)
{
	PVector pvec = CreateVectorWithCapacity(cap);
	if (!pvec)
		return NULL;

	pvec->msize = cap;
	memmove(pvec->mp, parr, cap * sizeof(DATATYPE));
	return pvec;
}

/*
  Implements a function that creates a PVector object with a specified capacity (cap)
  and fills all elements of this vector with a specified value (val).
*/
PVector CreateFilledVector(size_t cap, DATATYPE val)
{
	PVector pvec = CreateVectorWithCapacity(cap);
	if (!pvec)
		return NULL;

	pvec->msize = cap;
	for (size_t i = 0; i < pvec->msize; i++) {
		pvec->mp[i] = val;
	}
	
	return pvec;
}

void DestroyVec(PVector pvec)
{
	free(pvec->mp);
	free(pvec);
}

/*
  The function updates the capacity of the vector from which it receives its address with the value it receives
  in the second parameter. Returns false if the new value is less than the current value.
*/
bool SetCapacity(PVector pvec, size_t newCap)
{
	if (newCap < pvec->mcap)
		return false;
	
	if (newCap == pvec->mcap)
		return true;

	DATATYPE* pbuf = (DATATYPE*)realloc(pvec->mp, newCap * sizeof(DATATYPE));
	if (!pbuf)
		return false;

	pvec->mcap = newCap;
	pvec->mp = pbuf;
	return true;
}

/*
  Appends to a dynamic array from the end.
*/
bool PushBack(PVector pvec, DATATYPE val)
{
	/*
	If size is equal to the capacity when this function is called, then a run time
	error occurs. That's why we first question whether capacity is necessary.
	*/
	if (pvec->msize == pvec->mcap && !SetCapacity(pvec, pvec->mcap * 2))
		return false;

	pvec->mp[pvec->msize] = val;
	++pvec->msize;
	return true;
}

/*
  Let the dynamic array be in the following state before the function is called:
  2 4 6 8 10 12

  Let the parameters in the following state:
  idx = 3 and val = -1

  This is what happens after the InsertItemToVec() function call:
  2 4 6 -1 8 10 12
*/
bool InsertItemToVec(PVector pvec, size_t idx, DATATYPE val)
{
	// is idx valid?
	if (idx > pvec->msize)
		return false;

	//is increasing the capasity necessary?
	if (pvec->msize == pvec->mcap && !SetCapacity(pvec, pvec->mcap * 2))
		return false;

	memmove(pvec->mp + idx + 1, pvec->mp + idx, (pvec->msize - idx) * sizeof(DATATYPE));

	pvec->mp[idx] = val;
	++pvec->msize;
	return true;
}

/*
  Deletes last element in dynamic array.
*/
bool PopBack(PVector pvec)
{
	if (pvec->msize == 0)
		return false;
	
	--pvec->msize;
	return true;
}

/*
  Let the dynamic array be in the following state before the function is called:
  2 4 6 -1 8 10 12

  Let the parameters in the following state:
  idx = 3

  This is what happens after the InsertItemToVec() function call:
  2 4 6 8 10 12
*/
bool EraseItemFromVec(PVector pvec, size_t idx)
{
	if (idx >= pvec->msize)
		return false;

	memmove(pvec->mp + idx, pvec->mp + idx + 1, (pvec->msize) * sizeof(DATATYPE));
	
	--pvec->msize;
	return true;
}

bool IsVectorEmpty(PVector pvec)
{
	return pvec->msize == 0;
}


/*
  Shrinks unnecessary capacity.
 */
void ShrinkVec(PVector pvec)
{
	realloc(pvec->mp, pvec->msize * sizeof(DATATYPE));
}

bool ClearVec(PVector pvec)
{
	pvec->msize = 0;
}

/*
  Find index of spesific value.
 */
size_t FindIdxInVec(PVector pvec, DATATYPE val)
{
	for (size_t i = 0; i < pvec->msize; ++i) {
		if (pvec->mp[i] == val)
			return i;
	}

	return NOT_FOUND;
}

bool EraseValFromVec(PVector pvec, DATATYPE val)
{
	size_t idx = FindIdxInVec(pvec, val);
	if (idx == NOT_FOUND)
		return false;

	return EraseItemFromVec(pvec, idx);
}