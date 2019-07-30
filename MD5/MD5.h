#pragma once
#define N 64
class MD5
{
private:
	//�����chunk���ݿ��Ǿ���64�εĲ���ÿ����4���ֽ�Ϊ��λ�����
	void calculateMD5(size_t* chunk);
	//���һ������������� ����448��Ҫ��һ��512λ���ݿ� ���߲�����448
	void calculateMD5Final();

	/* 
		F(x,y,z) = (x & y) | ((~x) & z)
		G(x,y,z) = (x & z) | ( y & (~z))
		H(x,y,z) = x ^ y ^ z
		I(x,y,z) = y ^ (x | (~z))
	*/
	//���ĸ���ϣ������������������������ ���ÿ��ٶ���ĺ���ջ֡ ��ʡ����
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
	//ѭ����λ�Ĵ���
	size_t _sft[N];

	//ÿ�δ����õĿ�Ĵ�С һ��512bit(64�ֽ�)
	const size_t _chunkByte;
	unsigned char _chunk[N];

	//���һ�����ݵĴ�С
	size_t _lastByte;
	//�ܹ������˶����ֽ� ����8���������ĵ���λ�Ĵ�С ����longlong������64λ��
	unsigned long long _totalByte;
};