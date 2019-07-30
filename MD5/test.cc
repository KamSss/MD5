#include<string>
#include "MD5.h"

void MD5::calculateMD5Final(){
	//lastByteС��64�ֽ� ��ʾ���һ�����ݴ�С
	unsigned char* p =  _chunk + _lastByte;
	//���λ��ǰ�˸�bitλ 1000 0000 0x80
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
	//����64bit���ԭʼ�ĵ���bit���� (��Ϊchar���256 ����ǿ��תһ������)
	((unsigned long long*)_chunk)[7] = _totalByte * 8;
	calculateMD5((size_t*)_chunk);


}
void MD5::calculateMD5(size_t* chunk){
	size_t a = _a;
	size_t b = _b;
	size_t c = _c;
	size_t d = _d;
	// chunk[g]g��ʾ��ǰҪ����һ�����ݵ�λ�� f�ǹ�ϣ��������ֵ 
	size_t f,g; 
	//if (0 <= i < 16) g = i;
	//if (16 <= i < 32) g = (5 * i + 1) % 16;
	//if (32 <= i < 48) g = (3 * i + 5) % 16;
	//if (48 <= i < 63) g = (7 * i) % 16;

	//64�α任 4�ֲ��� ÿһ�ֲ��� 16�β���
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
		//b ���� b����ѭ�����Ƽ��Ϲ�ϣ����ֵ����k[i]
		b = b + shiftLeftRotate(a + f + _k[i] + chunk[g], _sft[i]);
		a = dtemp;
	}

	//64�α任����֮��������MD buffer��ֵ
	_a += a;
	_b += b;
	_c += c;
	_d += d;

}