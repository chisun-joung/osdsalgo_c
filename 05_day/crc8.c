#include <stdio.h>

typedef unsigned char u8;
#define  CRC8_TABLE_SIZE   256
void crc8_populate_msb(u8 table[CRC8_TABLE_SIZE], u8 polynomial)
{
	int i, j;
	const u8 msbit = 0x80;
	u8 t = msbit;

	table[0] = 0;

	for (i = 1; i < CRC8_TABLE_SIZE; i *= 2) {
		t = (t << 1) ^ (t & msbit ? polynomial : 0);
		for (j = 0; j < i; j++)
			table[i+j] = table[j] ^ t;
	}

	for( i=0 ; i<256; i++ )
	{
		printf("%02x ", table[i] );
		if( (i+1)%16 == 0 )
			printf("\n");
	}
	printf("\n");
}

u8 crc8(const u8 table[CRC8_TABLE_SIZE], u8 *pdata, size_t nbytes, u8 crc)
{
	/* loop over the buffer data */
	while (nbytes-- > 0)
		crc = table[(crc ^ *pdata++) & 0xff];

	return crc;
}
//----------------------------------------------------------------
u8 table[CRC8_TABLE_SIZE];
int main()
{
	u8 data[3] = {0x12, 0x34, 0 };
	u8 crc = 0x0;
	crc8_populate_msb(table, 0xd5);
    crc = crc8(table, data, 2, 0);
	printf("%x\n", crc );
	data[2] = crc;
//--------------------------------------------------------
    data[0]++;
    data[1]--;
    if( crc8( table, data , 3, 0 ) == 0 )
		printf("올바른 데이터 입니다.\n");
	else
		printf("변조된 데이터 입니다.\n");

	return 0;
}



