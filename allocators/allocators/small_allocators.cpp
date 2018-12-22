#include "small_allocators.h"
#include <functional>
#include <algorithm>

//this will initialize a blocks of chunks with the size blockSize
///it also initalize the indexes which will be in the first part of each block
void FixedAllocator::Chunk::Init(std::size_t blockSize, unsigned char blocks)
{
	pData_ = new unsigned char[blockSize * blocks];
	firstAvailableBlock_ = 0;
	blocksAvailable_ = blocks;
	unsigned char i = 0;
	unsigned char* p = pData_;
	for (; i != blocks; p += blockSize)
	{
		*p = ++i;
	}
}

//allocate a chunk inside and return the pointer to it
void* FixedAllocator::Chunk::Allocate(std::size_t blockSize)
{
	if (!blocksAvailable_) return 0;
	unsigned char* pResult = pData_ + (firstAvailableBlock_ * blockSize);
	// Update firstAvailableBlock_ to point to the next block
	firstAvailableBlock_ = *pResult;
	--blocksAvailable_;
	return pResult;
}

//deallocate a block that was allocated with allocate function
void FixedAllocator::Chunk::Deallocate(void* p, std::size_t blockSize)
{
	assert(p >= pData_);
	unsigned char* toRelease = static_cast<unsigned char*>(p);
	// Alignment check
	assert((toRelease - pData_) % blockSize == 0);
	*toRelease = firstAvailableBlock_;
	firstAvailableBlock_ = static_cast<unsigned char>((toRelease - pData_) / blockSize);
	// Truncation check
	assert(firstAvailableBlock_ ==(toRelease - pData_) / blockSize);
	++blocksAvailable_;
}

//Release/free the chunk
void FixedAllocator::Chunk::Release(void)
{
	delete[] pData_;
}

//constructor with block size
FixedAllocator::FixedAllocator(std::size_t blockSize)
	 : blockSize_(blockSize)
    , allocChunk_(0)
    , deallocChunk_(0)
{
    assert(blockSize_ > 0);
    
    prev_ = next_ = this;

    std::size_t numBlocks = DEFAULT_CHUNK_SIZE / blockSize;
    if (numBlocks > UCHAR_MAX) numBlocks = UCHAR_MAX;
    else if (numBlocks == 0) numBlocks = 8 * blockSize;
    
    numBlocks_ = static_cast<unsigned char>(numBlocks);

    assert(numBlocks_ == numBlocks);
}

FixedAllocator::FixedAllocator(const FixedAllocator& rhs)
    : blockSize_(rhs.blockSize_)
    , numBlocks_(rhs.numBlocks_)
    , chunks_(rhs.chunks_)
{
    prev_ = &rhs;
    next_ = rhs.next_;
    rhs.next_->prev_ = this;
    rhs.next_ = this;
    
    allocChunk_ = rhs.allocChunk_
        ? &chunks_.front() + (rhs.allocChunk_ - &rhs.chunks_.front())
        : 0;

    deallocChunk_ = rhs.deallocChunk_
        ? &chunks_.front() + (rhs.deallocChunk_ - &rhs.chunks_.front())
        : 0;
}

FixedAllocator& FixedAllocator::operator=(const FixedAllocator& rhs)
{
    FixedAllocator copy(rhs);
    copy.Swap(*this);
    return *this;
}

void FixedAllocator::Swap(FixedAllocator& rhs)
{
    using namespace std;
    
    swap(blockSize_, rhs.blockSize_);
    swap(numBlocks_, rhs.numBlocks_);
    chunks_.swap(rhs.chunks_);
    swap(allocChunk_, rhs.allocChunk_);
    swap(deallocChunk_, rhs.deallocChunk_);
}

//destructor
FixedAllocator::~FixedAllocator()
{
	if (prev_ != this)
    {
        prev_->next_ = next_;
        next_->prev_ = prev_;
        return;
    }

    Chunks::iterator i = chunks_.begin();
    for (; i != chunks_.end(); ++i)
    {
		//why this option because this will be not available is the data still exists so yes memory leak but no stop of processing
       assert(i->blocksAvailable_ == numBlocks_);
       i->Release();
    }
}
//Allocated a fixed size object
void* FixedAllocator::Allocate()
{
	if (allocChunk_ == 0 ||allocChunk_->blocksAvailable_ == 0)
	{
		// No available memory in this chunk; Try to find one
		Chunks::iterator i = chunks_.begin();
		for (;; ++i)
		{
			if (i == chunks_.end())
			{
				// All filled up-add a new chunk
				chunks_.reserve(chunks_.size()+1);
				Chunk newChunk;
				newChunk.Init(blockSize_, numBlocks_);
				chunks_.push_back(newChunk);
				allocChunk_ = &chunks_.back();
				deallocChunk_ = &chunks_.back();
				break;
			}
			if (i->blocksAvailable_ > 0)
			{
				// Found a chunk
				allocChunk_ = &*i;
				break;
			}
		}
	}
	assert(allocChunk_ != 0);
	assert(allocChunk_->blocksAvailable_ > 0);
	return allocChunk_->Allocate(blockSize_);
}

//DeAllocate a fixed size object
void FixedAllocator::DeAllocate(void *p)
{
	assert(!chunks_.empty());
    assert(&chunks_.front() <= deallocChunk_);
    assert(&chunks_.back() >= deallocChunk_);
    
    deallocChunk_  = VicinityFind(p);
    assert(deallocChunk_);

    DoDeAllocate(p);
}

//find the chunk where the allocated pointer lies
FixedAllocator::Chunk* FixedAllocator::VicinityFind(void* p)
{
    assert(!chunks_.empty());
    assert(deallocChunk_);

    const std::size_t chunkLength = numBlocks_ * blockSize_;

    Chunk* lo = deallocChunk_;
    Chunk* hi = deallocChunk_ + 1;
    Chunk* loBound = &chunks_.front();
    Chunk* hiBound = &chunks_.back() + 1;
	
	// Special case: deallocChunk_ is the last in the array
	if (hi == hiBound) hi = 0;

    for (;;)
    {
        if (lo)
        {
			//it is into the current dealloc chunk
            if (p >= lo->pData_ && p < lo->pData_ + chunkLength)
            {
                return lo;
            }
			//if the last dealocated chunk is not the first one
			//the previous chunk become the dealocated chunk from where to search
            if (lo == loBound) lo = 0;
            else --lo;
        }
        
        if (hi)
        {
			//if is into the next chunk
            if (p >= hi->pData_ && p < hi->pData_ + chunkLength)
            {
                return hi;
            }
			//go to the next chunk
            if (++hi == hiBound) hi = 0;
        }
    }
    assert(false);
    return 0;
}


//do the actual job of deallocating the data from the chunk
void FixedAllocator::DoDeAllocate(void* p)
{
    assert(deallocChunk_->pData_ <= p);
    assert(deallocChunk_->pData_ + numBlocks_ * blockSize_ > p);

    // call into the chunk, will adjust the inner list but won't release memory
    deallocChunk_->Deallocate(p, blockSize_);

    if (deallocChunk_->blocksAvailable_ == numBlocks_)
    {
        // deallocChunk_ is completely free, should we release it? 
        
        Chunk& lastChunk = chunks_.back();
        
        if (&lastChunk == deallocChunk_)
        {
            // check if we have two last chunks empty
            
            if (chunks_.size() > 1 && 
                deallocChunk_[-1].blocksAvailable_ == numBlocks_)
            {
                // Two free chunks, discard the last one
                lastChunk.Release();
                chunks_.pop_back();
                allocChunk_ = deallocChunk_ = &chunks_.front();
            }
            return;
        }
        
        if (lastChunk.blocksAvailable_ == numBlocks_)
        {
            // Two free blocks, discard one
            lastChunk.Release();
            chunks_.pop_back();
            allocChunk_ = deallocChunk_;
        }
        else
        {
            // move the empty chunk to the end
            std::swap(*deallocChunk_, lastChunk);
            allocChunk_ = &chunks_.back();
        }
    }
}
//constructor for small Obj allocator

SmallObjAllocator::SmallObjAllocator(std::size_t chunkSize,std::size_t maxObjectSize)
    : pLastAlloc_(0), pLastDealloc_(0)
    , chunkSize_(chunkSize), maxObjectSize_(maxObjectSize) 
{   
}
namespace { // anoymous 

// See LWG DR #270
struct CompareFixedAllocatorSize
    : std::binary_function<const FixedAllocator &, std::size_t, bool>
{
    bool operator()(const FixedAllocator &x, std::size_t numBytes) const
    {
        return x.BlockSize() < numBytes;
    }
};

} // anoymous namespace

void* SmallObjAllocator::Allocate(std::size_t numBytes)
{
    if (numBytes > maxObjectSize_) return operator new(numBytes);
    
    if (pLastAlloc_ && pLastAlloc_->BlockSize() == numBytes)
    {
        return pLastAlloc_->Allocate();
    }
    Pool::iterator i = std::lower_bound(pool_.begin(), pool_.end(), numBytes, 
                                        CompareFixedAllocatorSize());
    if (i == pool_.end() || i->BlockSize() != numBytes)
    {
        i = pool_.insert(i, FixedAllocator(numBytes));
        pLastDealloc_ = &*pool_.begin();
    }
    pLastAlloc_ = &*i;
    return pLastAlloc_->Allocate();
}


void SmallObjAllocator::DeAllocate(void* p, std::size_t numBytes)
{
    if (numBytes > maxObjectSize_) return operator delete(p);

    if (pLastDealloc_ && pLastDealloc_->BlockSize() == numBytes)
    {
        pLastDealloc_->DeAllocate(p);
        return;
    }
    Pool::iterator i = std::lower_bound(pool_.begin(), pool_.end(), numBytes, 
                                        CompareFixedAllocatorSize());
    assert(i != pool_.end());
    assert(i->BlockSize() == numBytes);
    pLastDealloc_ = &*i;
    pLastDealloc_->DeAllocate(p);
}
