#include <cstddef>
#include <cassert>
#include <vector>

#ifndef DEFAULT_CHUNK_SIZE
#define DEFAULT_CHUNK_SIZE 128
#endif

class FixedAllocator
{
private:
	// Nothing is private — Chunk is a Plain Old Data (POD) structure
	// structure defined inside FixedAllocator and manipulated only by it
	struct Chunk
	{
		void Init(std::size_t blockSize, unsigned char blocks);
		void* Allocate(std::size_t blockSize);
		void Deallocate(void* p, std::size_t blockSize);
		void Release(void);
		unsigned char* pData_;
		unsigned char firstAvailableBlock_;
		unsigned char blocksAvailable_;
	};
	std::size_t blockSize_;
	unsigned char numBlocks_;
	typedef std::vector<Chunk> Chunks;
	Chunks chunks_;
	Chunk* allocChunk_; //current chunk
	Chunk* deallocChunk_; //last place in which was a deallocation
	Chunk* VicinityFind(void* p);
	void DoDeAllocate(void *p);
	// For ensuring proper copy semantics
    mutable const FixedAllocator* prev_;
    mutable const FixedAllocator* next_;
public:
	explicit FixedAllocator(std::size_t blockSize);
	FixedAllocator(const FixedAllocator&);
    FixedAllocator& operator=(const FixedAllocator&);
	~FixedAllocator();
	void* Allocate();
	void DeAllocate(void *p);
	std::size_t BlockSize() const
    { return blockSize_; }
	void Swap(FixedAllocator& rhs);
};

class SmallObjAllocator
{
public:
	SmallObjAllocator(std::size_t chunkSize, std::size_t maxObjectSize);
	void * Allocate(std::size_t numBytes);
	void DeAllocate(void *pData,std::size_t size);
private:
	typedef std::vector<FixedAllocator> Pool;
	Pool pool_;
    FixedAllocator* pLastAlloc_;
    FixedAllocator* pLastDealloc_;
    std::size_t chunkSize_;
    std::size_t maxObjectSize_;
};