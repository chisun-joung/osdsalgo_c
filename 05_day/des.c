#include<stdio.h>
#include<time.h>
#include<stdlib.h>        /* rand() 함수사용,  */
#include<string.h>        /* strcat(문자열 합치는 함수) & strlen() 사용 */
#include<ctype.h>         /* toascii()함수 사용 */

int pc1[] = { 57,49,41,33,25,17, 9,
	1,58,50,42,34,26,18,
	10, 2,59,51,43,35,27,
	19,11, 3,60,52,44,36,
	63,55,47,39,31,23,15,
	7,62,54,46,38,30,22,
	14, 6,61,53,45,37,29,
	21, 3, 5,28,20,12, 4 };

int pc2[] = { 14,17,11,24, 1, 5,
	3,28,15, 6,21,10,
	23,19, 2, 4,26, 8,
	16, 7,27,20,13, 2,
	41,52,31,37,47,55,
	30,40,51,45,33,38,
	44,49,39,56,34,53,
	46,42,50,36,29,32 };

int shiftschedule[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

int ip_replace[64]= { 58,50,42,34,26,18,10,2,
	60,52,44,36,28,20,12,4,
	62,54,46,38,30,22,14,6,
	64,56,48,40,32,24,16,8,
	57,49,41,33,25,17, 9,1,
	59,51,43,35,27,19,11,3,
	61,53,45,37,29,21,13,5,
	63,55,47,39,31,23,15,7 };

int   ep[] = { 32, 1, 2, 3, 4, 5,
	4, 5, 6, 7, 8, 9,
	8, 9,10,11,12,13,
	12,13,14,15,16,17,
	16,17,18,19,20,21,
	20,21,22,23,24,25,
	24,25,26,27,28,29,
	28,29,30,31,32, 1 };

int p[] = { 16, 7,20,21,
	29,12,28,17,
	1,15,23,26,
	5,18,31,10,
	2, 8,24,16,
	32,27, 3, 9,
	19,13,30, 6,
	22,11, 4,25 };

int s[8][4][16]= { { { 14, 4,13, 1, 2,15,11, 8, 3,10, 6,12, 5, 9, 0, 7 },
	{  0,15, 7, 4,14, 2,13, 1,10, 6,12,11, 9, 5, 3, 8 },
	{  4, 1,14, 8,13, 6, 2,11,15,12, 9, 7, 3,10, 5, 0 },
	{ 15,12, 8, 2, 4, 9, 1, 7, 5,11, 3,14,10, 0, 6,13 } },

	{ { 15, 1, 8,14, 6,11, 3, 4, 9, 7, 2,13,12, 0, 5,10 },
		{  3,13, 4, 7,15, 2, 8,14,12, 0, 1,10, 6, 9,11, 5 },
		{  0,14, 7,11,10, 4,13, 1, 5, 8,12, 6, 9, 3, 2,15 },
		{ 13, 8,10, 1, 3,15, 4, 2,11, 6, 7,12, 0, 5,14, 9 } },

	{ { 10, 0, 9,14, 6, 3,15, 5, 1,13,12, 7,11, 4, 2, 8 },
		{ 13, 7, 0, 9, 3, 4, 6,10, 2, 8, 5,14,12,11,15, 1 },
		{ 13, 6, 4, 9, 8,15, 3, 0,11, 1, 2,12, 5,10,14, 7 },
		{  1,10,13, 0, 6, 9, 8, 7, 4,15,14, 3,11, 5, 2,12 } },	

	{ {  7,13,14, 3, 0, 6, 9,10, 1, 2, 8, 5,11,12, 4,15 },
		{ 13, 8,11, 5, 6,15, 0, 3, 4, 7, 2,12, 1,10,14, 9 },
		{ 10, 6, 9, 0,12,11, 7,13,15, 1, 3,14, 5, 2, 8, 4 },
		{  3,15, 0, 6,10, 1,13, 8, 9, 4, 5,11,12, 7, 2,14 } },

	{ {  2,12, 4, 1, 7,10,11, 6, 8, 5, 3,15,13, 0,14, 9 },
		{ 14,11, 2,12, 4, 7,13, 1, 5, 0,15,10, 3, 9, 8, 6 },
		{  4, 2, 1,11,10,13, 7, 8,15, 9,12, 5, 6, 3, 0,14 },
		{ 11, 8,12, 7, 1,14, 2,13, 6,15, 0, 9,10, 4, 5, 3 } },

	{ { 12, 1,10,15, 9, 2, 6, 8, 0,13, 3, 4,14, 7, 5,11 },
		{ 10,15, 4, 2, 7,12, 9, 5, 6, 1,13,14, 0,11, 3, 8 },
		{  9,14,15, 5, 2, 8,12, 3, 7, 0, 4,10, 1,13,11, 6 },
		{  4, 3, 2,12, 9, 5,15,10,11,14, 1, 7, 6, 0, 8,13 } },

	{ {  4,11, 2,14,15, 0, 8,13, 3,12, 9, 7, 5,10, 6, 1 },
		{ 13, 0,11, 7, 4, 9, 1,10,14, 3, 5,12, 2,15, 8, 6 },
		{  1, 4,11,13,12, 3, 7,14,10,15, 6, 8, 0, 5, 9, 2 },
		{  6,11,13, 8, 1, 4,10, 7, 9, 5, 0,15,14, 2, 3,12 } },

	{ { 13, 2, 8, 4, 6,15,11, 1,10, 9, 3,14, 5, 0,12, 7 },
		{  1,15,13, 8,10, 3, 7, 4,12, 5, 6,11, 0,14, 9, 2 },
		{  7,11, 4, 1, 9,12,14, 2, 0, 6,10,13,15, 3, 5, 8 },
		{  2, 1,14, 7, 4,10, 8,13,15,12, 9, 0, 3, 5, 6,11 } } };

void makekey();           /* 키를 만드는 함수 */
void random64();          /* 난수를 발생시져 64비트의 키를 생성  */
void replace64to56();     /* 64비트 키를 PC1순열을 통하여 56비트 키로 치환 */
void devide28();          /* 56비트의 키를 28비트씩 나눔 */
void shift(int);          /* 28비트를 좌측 쉬프트시킴 */
void LRto56();            /* 28비트 두개를 합쳐서 56비트로 만듬*/
void replace56to48(int);  /* 56비트를 PC2순열을 통하여 48비트 키로 치환 */

void inputtext();         /* 8자리 문자를 입력받음 */
void texttoascii();       /* 8자리 문자를 아스키 10진값으로 변환 */
void binary(int,int);     /* 아스키10진값을 2진값으로 변환 */
void fill8();             /* 2진값의 앞부분을 0으로 채워넣어 8자리를 만듬 */
void plain8_8to64();      /* 8행 8열의 배열을 64자리 문자열로 입력 */
void ip();                /* 초기치환 ip */
void devide32();          /* 64비트 평문을 32비트씩 쪼갬 */
void f_function(int);     /* F함수 */
void ep32to48();          /* 확장순열 32비트를 48비트로 치환 */
void xorkey(int);         /* 48비트와 key 48비트 Xor연산 */
void devide6_8();         /* 48비트를 6비트씩 8개로 나눔 */
void sbox6to4(int);       /* 6비트를 sbox를 통해 4비트로 치환 */
void binarys(int,int);    /* 10진수를 2진값으로 변환 */
void fill4(int);          /* 2진값의 빈자리를 0으로 채워넣어 4자리로 만듬*/
void f8_4to32();          /* 4비트 8개를 합쳐서 32비트로 만듬*/
void p32to32();
void changeLR();          /* 오른쪽 32비트와 왼쪽 32비트를 바꿈*/
void xorLR();             /* 오른쪽과 왼쪽 32비트를 XOR연산 */
void RLto64();            /* 왼쪽과 오른쪽 각 32비트 합쳐서 64비트*/
void ip_1();              /* 역초기치환 */
void asciitotext();       /* 8비트씩 잘라서 아스키문자로 출력  */
//void strrev(char *);      /* 스트링 리버스 하기 */

char key64[65];
char key56[57];
char left28[29] , right28[29];
char key48[16][49];
char input8[9];
char plaintext8_8[8][9];
char plaintext64[65];
int cnt;
char ip64[65];
char left32[33] , right32[33];
char ep48[49];
char xorkey48[49];
char xorkey6[8][7];
char sbox8_4[8][5];

int main(){
	int i;
	char tmpR[33];
	makekey();

	/* #############먼저 문자열을 입력 받아서 2진코드로 변환 ################### */

	inputtext();  			printf("\n입력한문자에 대한 ASCII값 : \n");
	texttoascii();			printf("\n\n0을 채워 넣어서 8비트로 만든값 : \n");
	fill8();
	plain8_8to64();			printf("\n8비트 8개를 합친 64비트 평문 : \n%s\n",plaintext64);

	/* ################## 여기서부터 암호화 #################################### */
	ip();         			printf("\nIP(초기치환) : \n%s\n",ip64);
	devide32();    			printf("\n32비트씩 나눔 : \n%s  %s\n",left32,right32);
	printf("\n아무키나 누르면 F함수를 시작합니다.\n");getchar();
	for (i=0 ; i<16 ; i++){
		strcpy(tmpR,right32);
		f_function(i);
		xorLR();				printf("\n왼쪽32비트와 오른쪽 32비트를 XOR연산한 결과를 왼쪽에 저장 :\n%s , %s",left32,right32);
		strcpy(right32,tmpR);
		changeLR();			printf("\n왼쪽과 오른쪽을 바꿈 :\n%s , %s",left32,right32);
		printf("\n아무키나 누르면 계속합니다.");getchar();      
		if (i>=15){
			RLto64();  			printf("\n\n좌우 32비트를 합쳐서 64비트 :\n%s",ip64);         
			ip_1();    			printf("\n\nIP-1(역초기치환) --> 64비트 암호문 :\n%s",plaintext64);
		}             
	}
	/* ############# 암호화 끝 - 복호화 시작 ################################### */
	printf("\n\n암호화과정이 끝났습니다. 아무키나 누르면 복호화를 시작합니다.");getchar();
	ip();         			printf("\nIP(초기치환) : \n%s\n",ip64);
	devide32();    			printf("\n32비트씩 나눔 : \n%s  %s\n",left32,right32);
	printf("\n아무키나 누르면 F함수를 시작합니다.\n");getchar();
	for (i=15 ; i>=0 ; i--){
		strcpy(tmpR,right32);
		f_function(i);
		xorLR();				printf("\n왼쪽32비트와 오른쪽 32비트를 XOR연산한 결과를 왼쪽에 저장 :\n%s , %s",left32,right32);
		strcpy(right32,tmpR);
		changeLR();			printf("\n왼쪽과 오른쪽을 바꿈 :\n%s , %s",left32,right32);
		printf("\n아무키나 누르면 계속합니다.");getchar();
		if (i<=0){        	       
			RLto64();  			printf("\n\n좌우 32비트를 합쳐서 64비트 :\n%s",ip64);
			ip_1();    			printf("\n\nIP-1(역초기치환) --> 64비트 평문 :\n%s",plaintext64);
			printf("\n\n8비트씩 잘라서 아스키문자로 변환 : ");
			asciitotext();			printf("\n\n이용해 주셔서 감사합니다. 아무키나 누르면 끝납니다.");getchar();
		}             
	}
	return 0;
}
/*
void strrev(char *str)
{
	char *temp;
	int i;
	temp = (char *)malloc(sizeof(strlen(str)));
	strcpy(temp,str);
	for(i=0;i<strlen(temp);i++)
		str[i]=temp[strlen(temp)-1-i];
	str[strlen(temp)]=0;
	free(temp);
}
*/
void inputtext(){
	char c;
	cnt=0;
	printf("\n8자리 문자를 입력하시오. --> ");
	while ( (c=getchar()) != '\n')
		input8[cnt++] = c;
}


void texttoascii(){
	int i;
	int code;
	for(i=0 ; i<8 ; i++){
		code = toascii(input8[i]);
		cnt = 0;
		binary(code,i);
		printf("%s  " ,plaintext8_8[i]);
	}
}


void binary(int b,int i){
	if (b>0) {
		binary(b/2,i);

		if (b%2==0)
			plaintext8_8[i][cnt] = '0';
		else
			plaintext8_8[i][cnt] = '1';

		cnt++;
	}
}


void fill8(){
	int i,j;
	for(i=0 ; i<8 ; i++){
		strrev(plaintext8_8[i]);
		for(j=0 ; j<8 ; j++){
			if(j+1 > strlen(plaintext8_8[i]))
				plaintext8_8[i][j] = '0';
		}
		strrev(plaintext8_8[i]);
		printf("%s  ", plaintext8_8[i]);
	}
}


void plain8_8to64(){
	int i,j,cnt;
	cnt=0;
	for (i=0 ; i<8 ; i++){
		for (j=0 ; j<8 ; j++){
			plaintext64[cnt++] = plaintext8_8[i][j];
		}
	}
}


void ip(){
	int i,j;
	for (i=0 ; i<64 ; i++){
		j = ip_replace[i];
		ip64[i] = plaintext64[j-1];
	}
}


void devide32(){
	int i;
	for (i=0 ; i<64 ; i++){
		if (i<32)
			left32[i] = ip64[i];
		else
			right32[i-32] = ip64[i];
	}
}


void f_function(int round){
	int i;

	ep32to48();				printf("\n오른쪽 32비트에 확장순열을 적용해 48비트로 치환 : \n%s\n",ep48);
	xorkey(round);			printf("%d번째 KEY와 XOR연산한 결과 :\n%s\n",round+1,xorkey48);
	printf("48비트를 6비트씩 8개로 나눈 결과 :\n");
	devide6_8();  			printf("\n\n8개의 S-box치환하여 6비트-->4비트 :");
	for (i=0 ; i<8 ; i++)
		sbox6to4(i);

	f8_4to32();   			printf("\n\n4비트 8개를 합쳐서 32비트 :\n%s",right32);
	p32to32();				printf("\nP치환을 실행한  32비트 :\n%s",right32);
}


void ep32to48(){
	int i,j;
	for (i=0 ; i<48 ; i++){
		j = ep[i];
		ep48[i] = right32[j-1];
	}
}


void xorkey(int round){
	int i;
	for (i=0 ; i<48 ; i++){
		if (ep48[i]==key48[round][i])
			xorkey48[i] = '0';
		else
			xorkey48[i] = '1';         
	}
}


void devide6_8(){
	int i,j,cnt;
	cnt=0;
	for (i=0 ; i<8 ; i++){
		for (j=0 ; j<6 ; j++){
			xorkey6[i][j] = xorkey48[cnt++];
		}
		printf("%s  ",xorkey6[i]);
	}
}


void sbox6to4(int s_){
	int i=0;
	int j=0;
	int code;
	if (xorkey6[s_][0]=='1')
		i=2;
	if (xorkey6[s_][5]=='1')
		i=i+1;
	if (xorkey6[s_][1]=='1')
		j=8;
	if (xorkey6[s_][2]=='1')
		j=j+4;
	if (xorkey6[s_][3]=='1')
		j=j+2;
	if (xorkey6[s_][4]=='1')
		j=j+1;

	code = s[s_][i][j];
	printf("\n%s --> S%1d:%1d행,%2d열 : %2d",xorkey6[s_],s_+1,i,j,code);
	cnt=0;
	while(cnt < 4){sbox8_4[s_][cnt++] = '\0';}
	cnt=0;
	binarys(code,s_);
	printf(" = %5s",sbox8_4[s_]);
	fill4(s_);
	printf(" = %5s",sbox8_4[s_]);
}


void binarys(int b,int i){
	if (b>0){
		binarys(b/2,i);

		if (b%2==0)
			sbox8_4[i][cnt] = '0';
		else
			sbox8_4[i][cnt] = '1';

		cnt++;
	}
}


void fill4(int s_){
	int i;
	strrev(sbox8_4[s_]);
	for(i=0 ; i<4 ; i++){
		if(i+1 > strlen(sbox8_4[s_]))
			sbox8_4[s_][i] = '0';
	}
	strrev(sbox8_4[s_]);
}


void f8_4to32(){
	int i,j;
	int cnt=0;
	for (i=0 ; i<8 ; i++){
		for (j=0 ; j<4 ; j++){
			right32[cnt++] = sbox8_4[i][j];
		}
	}
}


void p32to32(){
	int i,j;
	char tmp32[33];
	strcpy(tmp32,right32);
	for (i=0 ; i<32 ; i++){
		j = p[i];
		right32[i] = tmp32[j-1];
	}
}


void xorLR(){
	int i;
	for (i=0 ; i<32 ; i++){
		if (left32[i]==right32[i])
			left32[i] = '0';
		else
			left32[i] = '1';
	}
}


void changeLR(){
	char tmp[33]="";
	strcpy(tmp,left32);
	strcpy(left32,right32);
	strcpy(right32,tmp);
}


void RLto64(){
	int i;
	for (i=0 ; i<64 ; i++){
		if(i<32)
			ip64[i] = right32[i];
		else
			ip64[i] = left32[i-32];
	}
}


void ip_1(){
	int i,j;
	for (i=0 ; i<64 ; i++){
		j = ip_replace[i];
		plaintext64[j-1] = ip64[i];
	}
}


void asciitotext(){
	int i,j;
	i=0;
	for (i=0 ; i<8 ; i++){
		j=0;
		if (plaintext64[i*8+1]=='1')
			j=64;
		if (plaintext64[i*8+2]=='1')
			j=j+32;
		if (plaintext64[i*8+3]=='1')
			j=j+16;
		if (plaintext64[i*8+4]=='1')
			j=j+8;
		if (plaintext64[i*8+5]=='1')
			j=j+4;          
		if (plaintext64[i*8+6]=='1')
			j=j+2;
		if (plaintext64[i*8+7]=='1')
			j=j+1;
		printf("%c",toascii(j));

	}
}



/*########################### 이 아래는 키16개 생성하기 위한 함수들 ####################################*/
void makekey(){
	int i;
	random64();
	printf ("난수로 생성된 64비트의 키 \n      --> %s\n" , key64);

	replace64to56();
	printf ("PC1치환한 56비트의 키 \n      --> %s\n",key56);
	devide28();
	printf ("28비트--> %s   %s\n",left28,right28);

	for (i=0 ; i<16 ; i++){
		shift(i);
		/*printf ("shift%2d   %s   %s\n",i+1,left28,right28);*/
		LRto56();
		replace56to48(i);
		printf("key%2d --> %s\n",i+1,key48[i]);
	}
}


void random64(){
	int i;
	srand(time(0));
	for (i=0 ; i<64 ; i++){
		if (rand()%2==0)
			key64[i] = '0';
		else
			key64[i] = '1';
	}
}


void replace64to56(){
	int i,j;
	for (i=0 ; i<56 ; i++){
		j = pc1[i];
		key56[i] = key64[j-1];
	}
}


void devide28(){
	int i;
	for (i=0 ; i<56 ; i++){
		if (i<28)
			left28[i] = key56[i];
		else
			right28[i-28] = key56[i];
	}
}


void shift(int round){
	int i,j;
	char left2[3],right2[3];
	j = shiftschedule[round];
	if (j==1){
		left2[0] = left28[0];
		right2[0] = right28[0];
		for (i=0 ; i<27 ; i++){
			left28[i] = left28[i+1];
			right28[i] = right28[i+1];
		}
		left28[27] = left2[0];
		right28[27] = right2[0];
	}
	else{
		left2[0] = left28[0]; left2[1] = left28[1];
		right2[0] = right28[0]; right2[1] = right28[2];
		for (i=0 ; i<26 ; i++){
			left28[i] = left28[i+2];
			right28[i] = right28[i+2];
		}
		left28[26] = left2[0]; left28[27] = left2[1];
		right28[26] = right2[0]; right28[27] = right2[1];
	}
}


void LRto56(){
	int i;
	for (i=0 ; i<56 ; i++){
		if(i<28)
			key56[i] = right28[i];
		else
			key56[i] = left28[i-28]; 
	}
}


void replace56to48(int round){
	int i,j;
	for (i=0 ; i<48 ; i++){
		j = pc2[i];
		key48[round][i] = key56[j-1];
	}
}


