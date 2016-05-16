#ifndef __BLOOMFILTER_H__
#define __BLOOMFILTER_H__
#include <iostream>
using namespace std;
#include<string>
#include"BitMap.h"
#include "Common.h"


template<class K = string,
class HashFunc1 = __HashFunc1<K>,
class HashFunc2 = __HashFunc2<K>,
class HashFunc3 = __HashFunc3<K>,
class HashFunc4 = __HashFunc4<K>,
class HashFunc5 = __HashFunc5<K>>
class BloomFilter
{
public:
	BloomFilter(size_t size = 0)
	{
		_capacity = GetPrimeSize(size);
		_bitMap.Resize(_capacity);
	}

	void Set(const K& key)
	{
		size_t index1 = HashFunc1()(key);
		size_t index2 = HashFunc2()(key);
		size_t index3 = HashFunc3()(key);
		size_t index4 = HashFunc4()(key);
		size_t index5 = HashFunc5()(key);

		_bitMap.Set(index1%_capacity);//����Ϊ�ڶ���λ������Ȼ�����λͼ��Set���óɵڼ����ֽڵĵڼ�λ
		_bitMap.Set(index2%_capacity);
		_bitMap.Set(index3%_capacity);
		_bitMap.Set(index4%_capacity);
		_bitMap.Set(index5%_capacity);
	}

	bool Test(const K& key)
	{
		size_t index1 = HashFunc1()(key);
		if (!(_bitMap.Test(index1%_capacity)))//Ϊ1��һ�����ڣ�Ϊ0�϶�������
			return false;

		size_t index2 = HashFunc2()(key);
		if (!(_bitMap.Test(index2%_capacity)))
			return false;

		size_t index3 = HashFunc3()(key);
		if (!(_bitMap.Test(index3%_capacity)))
			return false;

		size_t index4 = HashFunc4()(key);
		if (!(_bitMap.Test(index4%_capacity)))
			return false;

		size_t index5 = HashFunc4()(key);
		if (!(_bitMap.Test(index5%_capacity)))
			return false;

		return true;
	}

protected:
	BitMap _bitMap;
	size_t _capacity;
};


void TestBloomFilter()
{
	BloomFilter<> bf(50);
	bf.Set("�Զ��");
	bf.Set("����");
	bf.Set("����");
	bf.Set("peter");
	bf.Set("��");
	bf.Set("http://www.cnblogs.com/-clq/archive/2012/05/31/2528153.html");
	bf.Set("http://www.cnblogs.com/-clq/archive/2012/05/31/2528155.html");

	cout << "Exist?->:" << bf.Test("�Զ��") << endl;
	cout << "Exist?->:" << bf.Test("����") << endl;
	cout << "Exist?->:" << bf.Test("peter") << endl;
	cout << "Exist?->:" << bf.Test("�캽") << endl;
	cout << "Exist?->:" << bf.Test("http://www.cnblogs.com/-clq/archive/2012/05/31/2528153.html") << endl;
	cout << "Exist?->:" << bf.Test("http://www.cnblogs.com/-clq/archive/2012/05/31/25288153.html") << endl;






}

#endif //__BLOOMFILTER_H__