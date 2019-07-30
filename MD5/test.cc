#include<string>
#include "MD5.h"

void MD5::calculateMD5Final(){
	//lastByte小于64字节 表示最后一块数据大小
	unsigned char* p =  _chunk + _lastByte;
	//填充位的前八个bit位 1000 0000 0x80
	*p++ = 0x80;
	size_t remainFillByte = _chunkByte - _lastByte - 1;
	if (remainFillByte < 8){
		memset(p, 0, remainFillByte);
		calculateMD5((size_t*)_chunk);
		memset(_chunk, 0, _chunkByte);
	}
	else{		
		memset(p, 0, remainFillByte);
	}
	//最后的64bit存放原始文档的bit长度 (因为char最大256 所以强制转一下类型)
	((unsigned long long*)_chunk)[7] = _totalByte * 8;
	calculateMD5((size_t*)_chunk);


}
void MD5::calculateMD5(size_t* chunk){
	size_t a = _a;
	size_t b = _b;
	size_t c = _c;
	size_t d = _d;
	// chunk[g]g表示当前要用哪一块数据的位置 f是哈希函数返回值 
	size_t f,g; 
	//if (0 <= i < 16) g = i;
	//if (16 <= i < 32) g = (5 * i + 1) % 16;
	//if (32 <= i < 48) g = (3 * i + 5) % 16;
	//if (48 <= i < 63) g = (7 * i) % 16;

	//64次变换 4轮操作 每一轮操作 16次操作
	for (size_t i = 0; i < 64; ++i){
		if (0 <= i && i < 16){
			f = H(b, c, d);
			g = i;
		}
		else if (16 <= i && i  < 32){
			f = G(b, c, d);
			g = (5 * i + 1) % 16;
		}
		else if (32 <= i && i < 48){
			f = H(b, c, d);
			g = (3 * i + 5) % 16;
		}
		else {
			f = I(b, c, d);
			g = (7 * i) % 16;
		}

		size_t dtemp = d;
		d = c;
		c = b;
		//b 等于 b加上循环左移加上哈希返回值加上k[i]
		b = b + shiftLeftRotate(a + f + _k[i] + chunk[g], _sft[i]);
		a = dtemp;
	}

	//64次变换操作之后更新这个MD buffer的值
	_a += a;
	_b += b;
	_c += c;
	_d += d;

}