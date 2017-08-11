/*                                                                  */
/*   LZWIN.C  :  Lempel-Ziv compression using Sliding Window        */
/*                                                                  */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>


#define SIZE 255

int queue[SIZE];
int front, rear;

/* 해시 테이블의 구조 */
typedef struct _jump
{
    int index;
    struct _jump *next;
} jump;

jump jump_table[256];

/* 탈출 문자 */
#define ESCAPE  0xB4

/* Lempel-Ziv 압축법에 의한 것임을 나타내는 식별 코드 */
#define IDENT1  0x33
#define IDENT2  0x44

#define FAIL    0xff

/* 큐를 초기화 */
void init_queue(void)
{
    front = rear = 0;
}

/* 큐가 꽉 찼으면 1을 되돌림 */
int queue_full(void)
{
    return (rear + 1) % SIZE == front;
}

/* 큐가 비었으면 1을 되돌림 */
int queue_empty(void)
{
    return front == rear;
}

/* 큐에 문자를 집어 넣음 */
int put(int k)
{
    queue[rear] = k;
    rear = ++rear % SIZE;

    return k;
}

/* 큐에서 문자를 꺼냄 */
int get(void)
{
    int i;

    i = queue[front];
    queue[front] = 0;
    front = ++front % SIZE;

    return i;
}

/* k를 큐의 첨자로 변환, 범위에서 벗어나는 것을 범위 내로 조정 */
int qx(int k)
{
    return (k + SIZE) % SIZE;
}


/* srcname[]에서 파일 이름만 뽑아내어서 그것의 확장자를 lzw로 바꿈 */
void make_dstname(char dstname[], char srcname[])
{
    char temp[256];

 	char *p;
    
    //fnsplit(srcname, temp, temp, dstname, temp);
	strcpy( temp, srcname );
	p = strtok( temp, ".");
	strcpy( dstname, p );
    strcat(dstname, ".lzw");
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

/* jump_table[]의 모든 노드를 제거 */
void delete_all_jump(void)
{
    int i;
    jump *j, *d;

    for (i = 0; i < 256; i++)
    {
        j = jump_table[i].next;
        while (j != NULL)
        {
            d = j;
            j = j->next;
            free(d);
        }
        jump_table[i].next = NULL;
    }
}


/* jump_table[]에 새로운 문자의 위치를 삽입 */
void put_jump(int c, int ptr)
{
    jump *j;

    if ((j = (jump*)malloc(sizeof(jump))) == NULL)
    {
        printf("\nError : Out of memory.");
        exit(1);
    }

    j->next = jump_table[c].next;       /* 선두에 삽입 */
    jump_table[c].next = j;
    j->index = ptr;
}


/* ptr 위치를 가지는 노드를 삭제 */
void del_jump(int c, int ptr)
{
    jump *j, *p;

    p = jump_table + c;
    j = p->next;

    while (j && j->index != ptr)    /* 노드 검색 */
    {
        p = j;
        j = j->next;
    }

    p->next = j->next;
    free(j);
}


/* cp와 length로 주어진 패턴을 해시법으로 찾아서 되돌림 */
int qmatch(int length)
{
    int i;
    jump *t, *p;
    int cp, sp;
    
    cp = qx(rear - length);     /* cp의 위치를 얻음 */
    p = jump_table + queue[cp];
    t = p->next;
    while (t != NULL)
    {
        sp = t->index;
    
        /*  첫 문자는 비교할 필요 없음. -> i =1; */
        for (i = 1; i < length && queue[qx(sp+i)] == queue[qx(cp+i)]; i++);
            if (i == length) return sp;     /* 패턴을 찾았음 */
    
        t = t->next;
    }

    return FAIL;
}

/* 문자 c를 출력 파일에 씀 */
int putc1(int c, FILE *dst)
{
    if (c == ESCAPE)        /* 탈출 문자이면 <탈출문자 0x00>쌍으로 치환 */
	{
    	putc(ESCAPE, dst);
    	putc(0x00, dst);
	}
    else
	    putc(c, dst);

    return c;
}

/* 패턴을 압축해서 출력 파일에 씀 */
void encode(int sp, int cp, int length, FILE *dst)
{
    int i;
    
    for (i = 0; i < length; i++)        /* jump_table[]에 패턴의 문자들을 기록 */
        put_jump(queue[qx(cp+i)], qx(cp+i));
    
    putc(ESCAPE, dst);      /* 탈출 문자 */
    putc(qx(cp-sp), dst);   /* 상대 위치 */
    putc(length, dst);      /* 패턴 길이 */
}


/* Sliding Window를 이용한 LZ 압축 함수 */
void lzwin_comp(FILE *src, char *srcname)
{
    int length;
    char dstname[13];
    FILE *dst;
    int sp, cp;
    int i, j;

    make_dstname(dstname, srcname);     /* 출력 파일 이름을 만듬 */
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
    putc(0, dst);        /* NULL 문자 삽입 */

    for (i = 0; i < 256; i++)       /* jump_table[] 초기화 */
        jump_table[i].next = NULL;
    
    rewind(src);
    init_queue();

    put(getc(src));

    length = 0;
    while (!feof(src))
	{
        if (queue_full())       /* 큐가 꽉 찼으면 */
	    {
	        if (sp == front)    /* sp의 패턴이 넘어가려고 하면 현재의 정보로 출력 파일에 씀*/
            {
                if (length > 3)
		            encode(sp, cp, length, dst);
                else
                    for (i = 0; i < length; i++)
                    {
                        put_jump(queue[qx(cp+i)], qx(cp+i));
                        putc1(queue[qx(cp+i)], dst);
                    }
                
                length = 0;
            }
            
            /* 큐에서 빠져나가는 문자의 위치를 jump_table[]에서 삭제 */
            del_jump(queue[front], front);
            
            get();  /* 큐에서 한 문자 삭제 */
	    }
	    
        if (length == 0)
        {
            cp = qx(rear-1);
            sp = qmatch(length+1);
            
            if (sp == FAIL)
            {
                putc1(queue[cp], dst);
                put_jump(queue[cp], cp);
            }
            else
                length++;
            
            put(getc(src));
        }
        else if (length > 0)
	    {
            if (queue[qx(cp+length)] != queue[qx(sp+length)])
                j = qmatch(length+1);
            else j = sp;
            if (j == FAIL || length > SIZE - 3)
            {
                if (length > 3)
                {
                    encode(sp, cp, length, dst);
                    length = 0;
                }
                else
                {
                    for (i = 0; i < length; i++)
                    {
                        put_jump(queue[qx(cp+i)], qx(cp+i));
                        putc1(queue[qx(cp+i)], dst);
                    }
                    length = 0;
                }
            }
	        else
            {
                sp = j;
                length++;
                put(getc(src));
            }
	    }
    }
    
    /* 큐에 남은 문자 출력 */
    if (length > 3) 
        encode(sp, cp, length, dst);
    else
        for (i = 0; i < length; i++)
            putc1(queue[qx(cp+i)], dst);
    
    delete_all_jump();
    fclose(dst);
}

/* 큐에 문자를 넣고, 만일 꽉 찼다면 큐에서 빠져나온 문자를 출력 */
void put_byte(int c, FILE *dst)
{
    if (queue_full()) putc(get(), dst);
    put(c);
}

/* Sliding Window를 이용한 LZ 압축법의 복원 함수 */
void lzwin_decomp(FILE *src)
{
    int c;
    char srcname[13];
    FILE *dst;
    int length;
    int i = 0;
    int sp;

    rewind(src);
    c = getc(src);
    if (c != IDENT1 || getc(src) != IDENT2) /* 헤더 확인 */
	{
    	printf("\n Error : That file is not Lempel-Ziv Encoding file");
    	fclose(src);
    	exit(1);
	}

    while ((c = getc(src)) != 0)     /* 파일 이름을 얻음 */
    	srcname[i++] = c;
    
    srcname[i] = 0;
    if ((dst = fopen(srcname, "wb")) == NULL)
	{
    	printf("\n Error : Disk full? ");
    	fclose(dst);
    	exit(1);
	}

    init_queue();
    c = getc(src);

    while (!feof(src))
	{
        if (c == ESCAPE)        /* 탈출 문자이면 */
        {
            if ((c = getc(src)) == 0)   /* <탈출 문자 0x00> 이면 */
                put_byte(ESCAPE, dst);
            else        /* <탈출문자 상대위치 패턴길이> 이면 */
            {
                length = getc(src);
                sp = qx(rear - c);
                for (i = 0; i < length; i++) 
                    put_byte(queue[qx(sp+i)], dst);
            }
        }
        else    /* 일반적인 문자의 경우 */
            put_byte(c, dst);
        
        c = getc(src);
	}
	
    
    while (!queue_empty())  /* 큐에 남아 있는 모든 문자를 출력 */
        putc(get(), dst);
    
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
    	printf("\n Usage : LZWIN <a or x> <filename>");
    	exit(1);
	}

    tstart = clock();       /* 시작 시간 기록 */
    s = file_length(argv[2]);   /* 원래 파일의 크기를 구함 */

    if ((src = fopen(argv[2], "rb")) == NULL)
    {
        printf("\n Error : That file does not exist.");
        exit(1);
    
    }
    if (strcmp(argv[1], "a") == 0)  /* 압축 */
	{
	    lzwin_comp(src, argv[2]);
        make_dstname(dstname, argv[2]); 
    	d = file_length(dstname);       /* 압축 파일의 크기를 구함 */
    	printf("\nFile compressed to %d%%.", (int)((double)d/s*100.));
	}
    else if (strcmp(argv[1], "x") == 0)     /* 압축의 해제 */
    {
    	lzwin_decomp(src);
        printf("\nFile decompressed & created.");
    }
    
    fclose(src);
    
    tend = clock(); /* 종료 시간 기록 */
    printf("\nTime elapsed %d ticks", tend - tstart);   /* 수행 시간 출력 : 단위 tick */
}
