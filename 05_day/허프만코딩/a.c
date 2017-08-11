/*                                                                  */
/*   HUFFMAN.C  :  Compression by Huffman's algorithm                  */
/*                                                                  */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

/* Huffman 압축에 의한 것임을 나타내는 식별 코드 */
#define IDENT1  0x55
#define IDENT2  0x66

long freq[256];

typedef struct _huf
{
    long count;
    int data;
    struct _huf *left, *right;
} huf;

huf *head[256];
int nhead;
huf *huf_head;
unsigned code[256];
int len[256];
int bitloc = -1;

/* 비트의 부분을 뽑아내는 함수 */
unsigned bits(unsigned x, int k, int j)
{
    return (x >> k) & ~(~0 << j);
}

/* 파일에 존재하는 문자들의 빈도를 구해서 freq[]에 저장 */
void get_freq(FILE *fp)
{
    int i;
	
    for (i = 0; i < 256; i++) 
        freq[i] = 0L;
    
    rewind(fp);
    
    while (!feof(fp)) 
        freq[getc(fp)]++;
}

/* 최소 빈도수를 찾는 함수 */
int find_minimum(void)
{
    int mindex;
    int i;
	
    mindex = 0;
	
    for (i = 1; i < nhead; i++)
        if (head[i]->count < head[mindex]->count)
            mindex = i;
		
		return mindex;
}

/* freq[]로 Huffman Tree를 구성하는 함수 */
void construct_trie(void)
{
    int i;
    int m;
    huf *h, *h1, *h2;
	
    /* 초기 단계 */
    for (i = nhead = 0; i < 256; i++)
    {
        if (freq[i] != 0)
        {
            if ((h = (huf*)malloc(sizeof(huf))) == NULL)
            {
                printf("\nError : Out of memory.");
                exit(1);
            }
            h->count = freq[i];
            h->data = i;
            h->left = h->right = NULL;
            head[nhead++] = h;
        }
    }
	
    /* 생성 단계 */
    while (nhead > 1)
    {
        m = find_minimum();
        h1 = head[m];
        head[m] = head[--nhead];
        m = find_minimum();
        h2 = head[m];
		
        if ((h = (huf*)malloc(sizeof(huf))) == NULL)
        {
            printf("\nError : Out of memory.");
            exit(1);
        }
        h->count = h1->count + h2->count;
        h->data = 0;
        h->left = h1;
        h->right = h2;
        head[m] = h;
    }
    
    huf_head = head[0];
}

/* Huffman Tree를 제거 */
void destruct_trie(huf *h)
{
    if (h != NULL)
    {
        destruct_trie(h->left);
        destruct_trie(h->right);
        free(h);
    }
}

/* Huffman Tree에서 코드를 얻어냄. code[]와 len[]의 설정 */
void _make_code(huf *h, unsigned c, int l)
{
    if (h->left != NULL || h->right != NULL)
    {
        c <<= 1;
        l++;
        _make_code(h->left, c, l);
        c |= 1u;
        _make_code(h->right, c, l);
        c >>= 1;
        l--;
    }
    else
    {
        code[h->data] = c;
        len[h->data] = l;
    }
}

/* _make_code()함수의 입구 함수 */
void make_code(void)
{
    int i;
	
    for (i = 0; i < 256; i++)
        code[i] = len[i] = 0;
	
    _make_code(huf_head, 0u, 0);
}


/* srcname[]에서 파일 이름만 뽑아내어서 그것의 확장자를 huf로 바꿈 */
void make_dstname(char dstname[], char srcname[])
{
    char temp[256];
	
	char *p;
    
    //fnsplit(srcname, temp, temp, dstname, temp);
	strcpy( temp, srcname );
	p = strtok( temp, ".");
	strcpy( dstname, p );
    strcat(dstname, ".huf");
}

/* 파일의 이름을 받아 그 파일의 길이를 되돌림 */
long file_length(char filename[])
{
    FILE *fp;
    long l;
	
    if ((fp = fopen(filename, "rb")) == NULL)
        return 0L;
    
    fseek(fp, 0, SEEK_END);
    l = ftell(fp);
    fclose(fp);
    
    return l;
}


#define NORMAL 0
#define FLUSH  1

/* 파일에 한 비트씩 출력하도록 캡슐화 한 함수 */
void put_bitseq(unsigned i, FILE *dst, int flag)
{
    static unsigned wbyte = 0;
    if (bitloc < 0 || flag == FLUSH)
    {
        putc(wbyte, dst);
        bitloc = 7;
        wbyte = 0;
    }
    wbyte |= i << (bitloc--);
}

/* Huffman 압축 함수 */
void huffman_comp(FILE *src, char *srcname)
{
    int cur;
    int i;
    union { long lenl; int leni[2]; } length;
    char dstname[13];
    FILE *dst;
    int b;
	
    fseek(src, 0L, SEEK_END);
    length.lenl = ftell(src);
    rewind(src);
	
    make_dstname(dstname, srcname);     /* 출력 파일 이름 만듬 */
    if ((dst = fopen(dstname, "wb")) == NULL)
    {
        printf("\n Error : Can't create file.");
        fclose(dst);
        exit(1);
    }
	
    /* 압축 파일의 헤더 작성 */
    putc(IDENT1, dst);    /* 출력 파일에 식별자 삽입 */
    putc(IDENT2, dst); 
    fputs(srcname, dst);    /* 출력 파일에 파일 이름 삽입 */
    putc(0, dst);        /* NULL 문자열 삽입 */
    putw(length.leni[0], dst);  /* 파일의 길이 출력 */
    putw(length.leni[1], dst);
	
    get_freq(src);
    construct_trie();
    make_code();
	
    /* code[]와 len[]을 출력 */
    for (i = 0; i < 128; i++)
    {
        putw(code[i*2], dst);
        cur = len[i*2] << 4;
        cur |= len[i*2+1];
        putc(cur, dst);
        putw(code[i*2+1], dst);
    }
	
    destruct_trie(huf_head);
	
    rewind(src);
    bitloc = 7;
    while (1)
    {
        cur = getc(src);
        
        if (feof(src)) 
            break;
        
        for (b = len[cur] - 1; b >= 0; b--)
            put_bitseq(bits(code[cur], b, 1), dst, NORMAL);
    }
    put_bitseq(0, dst, FLUSH);
    fclose(dst);
}

/* len[]와 code[]를 이용하여 Huffman Tree를 구성 */
void trie_insert(int data)
{
    int b = len[data] - 1;
    huf *p, *t;
	
    if (huf_head == NULL)
    {
        if ((huf_head = (huf*)malloc(sizeof(huf))) == NULL)
        {
            printf("\nError : Out of memory.");
            exit(1);
        }
        huf_head->left = huf_head->right = NULL;
    }
	
    p = t = huf_head;
    while (b >= 0)
    {
        if (bits(code[data], b, 1) == 0)
        {
            t = t->left;
            if (t == NULL)
            {
                if ((t = (huf*)malloc(sizeof(huf))) == NULL)
                {
                    printf("\nError : Out of memory.");
                    exit(1);
                }
                t->left = t->right = NULL;
                p->left = t;
            }
        }
        else
        {
            t = t->right;
            if (t == NULL)
            {
                if ((t = (huf*)malloc(sizeof(huf))) == NULL)
                {
                    printf("\nError : Out of memory.");
                    exit(1);
                }
                t->left = t->right = NULL;
                p->right = t;
            }
        }
        p = t;
        b--;
    }
    t->data = data;
}

/* trie_insert()의 입구 함수 */
void restruct_trie(void)
{
    int i;
    
    huf_head = NULL;
    for (i = 0; i < 256; i++)
        if (len[i] > 0) trie_insert(i);
}

/* 파일에서 한 비트씩 읽는 것처럼 캡슐화 한 함수 */
int get_bitseq(FILE *fp)
{
    static int cur = 0;
	
    if (bitloc < 0)
    {
        cur = getc(fp);
        bitloc = 7;
    }
	
    return bits(cur, bitloc--, 1);
}

/* Huffman 압축 복원 알고리즘 */
void huffman_decomp(FILE *src)
{
    int cur;
    char srcname[13];
    FILE *dst;
    union { long lenl; int leni[2]; } length;
    long n;
    huf *h;
    int i = 0;
	
    rewind(src);
    cur = getc(src);
    if (cur != IDENT1 || getc(src) != IDENT2)
    {
        printf("\n Error : That file is not Run-Length Encoding file");
        fclose(src);
        exit(1);
    }
    while ((cur = getc(src)) != 0) 
        srcname[i++] = cur;
    
    srcname[i] = 0;
    if ((dst = fopen(srcname, "wb")) == NULL)
    {
        printf("\n Error : Disk full? ");
        fclose(dst);
        exit(1);
    }
    length.leni[0] = getw(src);
    length.leni[1] = getw(src);
	
    for (i = 0; i < 128; i++)       /* code[]와 len[]을 읽어들임 */
    {
        code[i*2] = getw(src);
        cur = getc(src);
        code[i*2+1] = getw(src);
        len[i*2] = bits(cur, 4, 4);
        len[i*2+1] = bits(cur, 0, 4);
    }
    restruct_trie();        /* 헤더를 읽어서 Huffman Tree 재구성 */
	
    n = 0;
    bitloc = -1;
    while (n < length.lenl)
    {
        h = huf_head;
        while (h->left && h->right)
        {
            if (get_bitseq(src) == 1)
                h = h->right;
            else
                h = h->left;
        }
        putc(h->data, dst);
        n++;
    }
    destruct_trie(huf_head);
    fclose(dst);
}


void main(int argc, char *argv[])
{
    FILE *src;
    long s, d;
    char dstname[13];
    clock_t tstart, tend;
	
    /* 사용법 출력 */
    if (argc < 3)
	{
        printf("\n Usage : HUFFMAN <a or x> <filename>");
        exit(1);
    }
	
    tstart = clock();   /* 시작 시각 기록 */
    s = file_length(argv[2]);   /* 원래 파일의 크기 구함 */
	
    if ((src = fopen(argv[2], "rb")) == NULL)
    {
        printf("\n Error : That file does not exist.");
        exit(1);
    }
	
    if (strcmp(argv[1], "a") == 0)      /* 압축 */
    {
        huffman_comp(src, argv[2]);
        make_dstname(dstname, argv[2]);
        d = file_length(dstname);       /* 압축 파일의 크기를 구함 */
        printf("\nFile compressed to %d%%.", (int)((double)d/s*100.));
    }
    else if (strcmp(argv[1], "x") == 0)     /* 압축의 해제 */
    {
        huffman_decomp(src);
        printf("\nFile decompressed & created.");
    }
	
    fclose(src);
	
    tend = clock();     /* 종료 시각 저장 */
    printf("\nTime elapsed %d ticks", tend - tstart);   /* 수행 시간 출력 : 단위 tick */
}
