#ifndef __BITMAP_H__
#define __BITMAP_H__
#include <vector>
#include "Common.h"

class BitMap
{
public:
	BitMap(size_t size = 0)
		:_size(0)
	{
		_a.resize((size>>5)+1);
	}

	void Set(size_t x)
	{
		size_t index = x >> 5;
		size_t num = x % 32;
		if (!(_a[index] & (1 << num)))
		{
			++_size;
			_a[index] |= (1 << num);
		}
	}

	void Reset(size_t x)
	{
		size_t index = x >> 5;
		size_t num = x % 32;

		if (_a[index] & (1 << num))
		{
			--_size;
			_a[index] &= ~(1 << num);
		}
	}

	bool Test(size_t x)
	{
		size_t index = x >> 5;
		size_t num = x % 32;

		if (_a[index] & (1 << num))
		{
			return true;
		}

		return false;
	}

	void Resize(size_t size)
	{
		_a.resize((size >> 5) + 1);
	}

	size_t Size()
	{
		return _size;
	}

private:
	vector<size_t> _a;
	size_t _size;
};


void Test()
{
	BitMap bm(35);
	bm.Set(4);
	bm.Set(5);
	bm.Set(6);
	cout << "is4Exist?->" << bm.Test(4) << endl;
	cout <<"is5Exist?->"<< bm.Test(5) << endl;

	bm.Reset(5);
	cout << "is4Exist?->" << bm.Test(4) << endl;
	cout << "is5Exist?->" << bm.Test(5) << endl;
}

#endif //__BITMAP_H__