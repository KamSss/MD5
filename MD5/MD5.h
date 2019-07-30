#pragma once
#define N 64
class MD5
{
private:
	//这里的chunk数据块是经过64次的操作每次以4个字节为单位处理的
	void calculateMD5(size_t* chunk);
	//最后一个数据两种情况 等于448就要补一块512位数据块 或者不足于448
	void calculateMD5Final();

	/* 
		F(x,y,z) = (x & y) | ((~x) & z)
		G(x,y,z) = (x & z) | ( y & (~z))
		H(x,y,z) = x ^ y ^ z
		I(x,y,z) = y ^ (x | (~z))
	*/
	//把四个哈希函数定义在这里变成内联函数 不用开辟额外的函数栈帧 节省开销
	size_t F(size_t x, size_t y, size_t z){
		return (x & y) | ((~x) & z);
	}

	size_t G(size_t x, size_t y, size_t z){
		return (x & z) | (y & (~z));
	}

	size_t h(size_t x, size_t y, size_t z){
		return x ^ y ^ z;
	}

	size_t i(size_t x, size_t y, size_t z){
		return y ^ (x | (~z));
	}

	size_t shiftLeftRotate(size_t num, size_t n){
		return (num << n) | (num >> (32 - n));
	}


	size_t _a;
	size_t _b;
	size_t _c;
	size_t _d;

	size_t _k[N];
	//循环移位的次数
	size_t _sft[N];

	//每次处理用的块的大小 一般512bit(64字节)
	const size_t _chunkByte;
	unsigned char _chunk[N];

	//最后一块数据的大小
	size_t _lastByte;
	//总共处理了多少字节 乘以8就是整个文档的位的大小 （用longlong正好是64位）
	unsigned long long _totalByte;
};