#ifndef __COMMON_H__
#define __COMMON_H__

size_t GetPrimeSize(size_t size)
{
	static const int _PrimeSize = 28;
	static const unsigned long _PrimeList[_PrimeSize] =
	{
		53ul, 97ul, 193ul, 389ul, 769ul,
		1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
		49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
		1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
		50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
		1610612741ul, 3221225473ul, 4294967291ul
	};

	for (size_t i = 0; i < _PrimeSize; i++)
	{
		if (_PrimeList[i] > size)
		{
			return _PrimeList[i];
		}
		if (_PrimeList[_PrimeSize] == size)
			return _PrimeList[_PrimeSize - 1];
	}
	return _PrimeList[_PrimeSize - 1];
}


template<class T>
struct __HashFunc1
{
	size_t BKDRHash(const char* str)
	{
		register size_t hash = 0;
		while (size_t ch = (size_t)*str++)
		{
			hash = hash * 131 + ch;   // 也可以乘以31、131、1313、13131、131313..  
		}
		return hash;
	}

	size_t operator()(const T& str)
	{
		return BKDRHash(str.c_str());
	}

};


template<class T>
struct __HashFunc2
{
	size_t SDBMHash(const char* str)
	{
		register size_t hash = 0;
		while (size_t ch = (size_t)*str++)
		{
			hash = 65599 * hash + ch;
			//hash = (size_t)ch + (hash << 6) + (hash << 16) - hash;  
		}
		return hash;
	}

	size_t operator()(const T& str)
	{
		return SDBMHash(str.c_str());
	}

};


template<class T>
struct __HashFunc3
{
	size_t RSHash(const char *str)
	{
		register size_t hash = 0;
		size_t magic = 63689;
		while (size_t ch = (size_t)*str++)
		{
			hash = hash * magic + ch;
			magic *= 378551;
		}
		return hash;
	}

	size_t operator()(const T& str)
	{
		return RSHash(str.c_str());
	}

};


template<class T>
struct __HashFunc4
{
	size_t APHash(const char *str)
	{
		register size_t hash = 0;
		size_t ch;
		for (long i = 0; ch = (size_t)*str++; i++)
		{
			if ((i & 1) == 0)
			{
				hash ^= ((hash << 7) ^ ch ^ (hash >> 3));
			}
			else
			{
				hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
			}
		}
		return hash;
	}

	size_t operator()(const T& str)
	{
		return APHash(str.c_str());
	}

};


template<class T>
struct __HashFunc5
{
	size_t JSHash(const char *str)
	{
		if (!*str)        // 这是由本人添加，以保证空字符串返回哈希值0  
			return 0;
		register size_t hash = 1315423911;
		while (size_t ch = (size_t)*str++)
		{
			hash ^= ((hash << 5) + ch + (hash >> 2));
		}
		return hash;
	}

	size_t operator()(const T& str)
	{
		return JSHash(str.c_str());
	}

};






#endif //__COMMON_H__