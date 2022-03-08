#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/times.h>
#include <unistd.h>

#include "fourier.h"

// #define USE_RANDM

/**
 * @brief   fft测试
 *
 * @param   argc        参数个数
 * @param   argv        参数0 : 函数名
 *                      参数1 : 输入数据包含的波形数
 *                      参数2 : 输入数据采样数必须为2的N次方
 *                      参数3 : 重复计算次数 (便于计时)
 *                      参数4 : 可选(缺省值为0) - 快速傅里叶变换换标志
 *                          "-i" : inverse FFT (反变换)
 *                          其他 : forward FFT (正变换)
 *
 * @return  int         没太大意义
 */
int main(int argc, char *argv[])
{
    unsigned int i;
    unsigned int j;
    unsigned int MAXSIZE;       // 最大采样数
    unsigned int MAXWAVES;      // ? 叠加波形数
    unsigned int repeat_cnt;
    float *RealIn = NULL;       // 输入 实部
    float *ImagIn= NULL;        // 输入 虚部
    float *RealOut= NULL;       // 输出 实部
    float *ImagOut= NULL;       // 输出 虚部
    float *coeff= NULL;         // 系数
    float *amp= NULL;           // ?
    int invfft = 0;
    const char *path = "fourier_out.txt";
    const char *p_column = "index, RealIn, ImagIn, RealOut, ImagOut\n";
    char buf[100];



    /* 输入参数打印 */
    printf("argc: %d\n", argc);
    for (i = 0; i < argc; ++i) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }
    if (argc < 4) {
        printf("Usage: fft <waves> <length> -i\n");
        printf("-i performs an inverse fft\n");
        printf("make <waves> random sinusoids\n");
        printf("<length> is the number of samples\n");
        return -1;
    } else if (4 == argc) {
        invfft = 0;                             // 默认为0
    } else if (argc == 5) {
        invfft = !strncmp(argv[4], "-i", 2);    // 是否为 "-i"
    } else {
        printf("para error.\n");                // 参数输入有误
        return 0;
    }
    printf("invfft: %d\n", invfft);
    MAXWAVES = atoi(argv[1]);
    MAXSIZE = atoi(argv[2]);
    repeat_cnt = atoi(argv[3]);

    /* 申请内存 */
    RealIn = (float *)malloc(sizeof(float) * MAXSIZE);
    ImagIn = (float *)malloc(sizeof(float) * MAXSIZE);
    RealOut = (float *)malloc(sizeof(float) * MAXSIZE);
    ImagOut = (float *)malloc(sizeof(float) * MAXSIZE);
    coeff = (float *)malloc(sizeof(float) * MAXWAVES);
    amp = (float *)malloc(sizeof(float) * MAXWAVES);
    if (NULL == RealIn || NULL == ImagIn || NULL == RealOut || NULL == ImagOut || NULL == coeff || NULL == amp) {
        printf("malloc failed. exit.\n");
        return -1;
    }

    /* Makes MAXWAVES waves of random amplitude and period */
    for (i = 0; i < MAXWAVES; i++) {
#ifdef USE_RANDM
        srand(i);
        coeff[i] = rand() % 1000;
        amp[i] = rand() % 1000;
#else
        coeff[i] = (float)(i + 1) / MAXWAVES * 1000;
        amp[i] = (float)(i + 1) / MAXWAVES * 1000;
#endif
    }

#ifdef USE_RANDM
    for (i = 0; i < MAXSIZE; i++) {
        for (j = 0; j < MAXWAVES; j++) {
            /* randomly select sin or cos */
            if (rand() % 2 ) {
                RealIn[i] += coeff[j] * cos(amp[j] * i);
            } else {
                RealIn[i] += coeff[j] * sin(amp[j] * i);
            }
            ImagIn[i] = 0;
        }
    }
#else
    for (i = 0; i < MAXSIZE; i++) {
        for (j = 0; j < MAXWAVES; j++) {
            RealIn[i] += coeff[j] * sin(amp[j] * i);
            ImagIn[i] = 0;
        }
    }
#endif

    int sc_clk_tck;
    sc_clk_tck = sysconf(_SC_CLK_TCK);
    struct tms begin_tms, end_tms;
    clock_t begin, end;

    /* fft 计算 repeat_cnt 次*/
//    usleep(123456);
    begin = times(&begin_tms);
    for (i = 0; i < repeat_cnt; ++i) {
        fft_float(MAXSIZE, invfft, RealIn, ImagIn, RealOut, ImagOut);
    }
    end = times(&end_tms);
    double realTime = 0;
    printf("real time: %lf\n", realTime = (end - begin)*1000000 / (double)sc_clk_tck);

    /* 打印结果 */
    printf("samples num: %d\n", MAXSIZE);
    printf("waves num: %d\n", MAXWAVES);
    printf("repeat_cnt: %d\n", repeat_cnt);
    printf("inverse flg: %d\n", invfft);
/*    printf("\tt1: %llu\n", t1);
    printf("\tt2: %llu\n", t2);
*/
    printf("==> total time: %lf us\n", realTime);
    printf("==> single time: %lf us\n", (float)(realTime) / (float)repeat_cnt);
    printf("==> time per sample: %lf us\n\n", (float)(realTime) / (float)MAXSIZE / (float)repeat_cnt);

    /* 保存结果 */
/*  printf("is to store result...\n");
    int fd = open(path, O_CREAT | O_WRONLY);
    printf("fd: %d\n", fd);
    write(fd, p_column, strlen(p_column));
    for (i = 0; i < MAXSIZE; ++i) {
        memset(buf, 0, sizeof(buf));
        sprintf(buf, "%d, %f, %f, %f, %f\n", i, RealIn[i], ImagIn[i], RealOut[i], ImagOut[i]);
        lseek(fd, 0, SEEK_END);
        write(fd, buf, strlen(buf));
    }
    close(fd);
    printf("\n==> DONE~!\n");
*/
    /* 释放内存 */
    free(RealIn);
    free(ImagIn);
    free(RealOut);
    free(ImagOut);
    free(coeff);
    free(amp);
    return 0;
}
