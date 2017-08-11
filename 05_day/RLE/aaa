/*                                                                  */
/*   RUNLEN.C  :  Compression by Run-Length Encoding                */
/*                                                                  */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>


/* 탈출 문자 */
#define ESCAPE  0xB4

/* Run-Length 압축법에 의한 것임을 나타내는 식별 코드 */
#define IDENT1  0x11
#define IDENT2  0x22



/* srcname[]에서 파일 이름만 뽑아내어서 그것의 확장자를 rle로 바꿈 */
void make_dstname(char dstname[], char srcname[])
{
    char temp[256];
	char *p;
    
    //fnsplit(srcname, temp, temp, dstname, temp);
	strcpy( temp, srcname );
	p = strtok( temp, ".");
	strcpy( dstname, p );
    strcat( dstname, ".rle");
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


/* code[] 배열의 내용을 출력함 */
void flush(char code[], int len, FILE *fp)
{
    int i;
    for (i = 0; i < len; i++)
    putc(code[i], fp); 
}

/* Run-Length 압축 함수 */
void run_length_comp(FILE *src, char *srcname)
{
    int cur;
    int code_len;
    int length;
    unsigned char code[10];
    char dstname[13];
    FILE *dst;

    make_dstname(dstname, srcname);

    if ((dst = fopen(dstname, "wb")) == NULL)   /* 출력 파일 오픈 */
    {
        printf("\n Error : Can't create file.");
        fclose(dst);
        exit(1);
    }

    /*  압축 파일의 헤더 작성 */
    putc(IDENT1, dst);      /* 출력 파일에 식별자 삽입 */
    putc(IDENT2, dst); 
    fputs(srcname, dst);    /* 출력 파일에 파일 이름 삽입 */
    putc(0, dst);        /* NULL 문자 삽입 */

    cur = getc(src);
    code_len = length = 0;

    while (!feof(src))
    {
        if (length == 0)
        {
            if (cur != ESCAPE)
            {
                code[code_len++] = cur;
                length++;
            }
            else
            {
                code[code_len++] = ESCAPE;
                code[code_len++] = ESCAPE;
                flush(code, code_len, dst);
                length = code_len = 0;
            }
            
            cur = getc(src);
        }
        else if (length == 1)
        {
            if (cur != code[0])
            {
                flush(code, code_len, dst);
                length = code_len = 0;
            }
            else
            {
                length++;
                code[code_len++] = cur;
                cur = getc(src);
            }
        }
        else if (length == 2)
        {
            if (cur != code[1])
            {
                flush(code, code_len, dst);
                length = code_len = 0;
            }
            else
            {
                length++;
                code_len = 0;
                code[code_len++] = ESCAPE;
                code[code_len++] = cur;
                code[code_len++] = length;
                cur = getc(src);
            }
        }
        else if (length > 2)
        {
            if (cur != code[1] || length > 254)
            {
                flush(code, code_len, dst);
                length = code_len = 0;
            }
            else
            {
                code[code_len-1]++;
                length++;
                cur = getc(src);
            }
        }
    }

    flush(code, code_len, dst);
    fclose(dst);
}


/* Run-Length 압축을 복원 */
void run_length_decomp(FILE *src)
{
    int cur;
    char srcname[13];
    FILE *dst;
    int i = 0, j;
    int length;

    cur = getc(src);
    if (cur != IDENT1 || getc(src) != IDENT2)   /* Run-Length 압축 파일이 맞는지 확인 */
    {
        printf("\n Error : That file is not Run-Length Encoding file");
        fclose(src);
        exit(1);
    }


    while ((cur = getc(src)) != 0)       /* 헤더에서 파일 이름을 얻음 */
        srcname[i++] = cur;
    
    srcname[i] = 0;
    if ((dst = fopen(srcname, "wb")) == 0)
    {
        printf("\n Error : Disk full? ");
        fclose(dst);
        exit(1);
    }

    cur = getc(src);
    while (!feof(src))
    {
        if (cur != ESCAPE)
            putc(cur, dst);
        else
        {
            cur = getc(src);
            if (cur == ESCAPE)
                putc(ESCAPE, dst);
        
            else
            {
                length = getc(src);
                for (j = 0; j < length; j++)
                    putc(cur, dst);
            }
        }
        
        cur = getc(src);
        
    }

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
        printf("\n Usage : RUNLEN <a or x> <filename>");
        exit(1);
    }


    tstart = clock();       /* 시작 시각 기록 */
    
    s = file_length(argv[2]);   /* 원래 파일의 크기를 구함 */

    if ((src = fopen(argv[2], "rb")) == NULL)
    {
        printf("\n Error : That file does not exist.");
        exit(1);
    }
    
    
    if (strcmp(argv[1], "a") == 0)      /* 압축 */
    {
        run_length_comp(src, argv[2]);
        make_dstname(dstname, argv[2]);
        d = file_length(dstname);       /* 압축 파일의 크기를 구함 */
        printf("\nFile compressed to %d%%", (int)((double)d/s*100.));
    }
    else if (strcmp(argv[1], "x") == 0)     /* 압축의 해제 */
    {
        run_length_decomp(src);
        printf("\nFile decompressed & created.");
    }
    
    fclose(src);
    
    
    tend = clock();     /* 종료 시각 기록 */
    printf("\nTime elapsed %d ticks", tend - tstart);   /* 수행 시간 출력 : 단위 tick */
}

