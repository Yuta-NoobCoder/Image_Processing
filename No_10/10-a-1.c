#include <stdio.h>
#include <stdlib.h>

void processing(void);
int combine_4bytes(unsigned char data[], int start);
void print_header(unsigned char data[], int start, int len);

void rgb_to_ybr(void);

unsigned char header[54];
unsigned char imgin[3][512][512];  //入力画像データ
unsigned char imgout[3][512][512]; //出力画像データ

int height = 0;
int width = 0;
int insert_bits = 0;

int main(int argc, char *argv[])
{
    processing();
    return 0;
}

void processing(void)
{
    double x, y;
    int p;

    int d[2][2] = {
        {10, 30},
        {20, 40}};

    printf("\n<使用する4つの画素値>\n");
    printf("%d %d\n", d[0][0], d[1][0]);
    printf("%d %d\n", d[0][1], d[1][1]);
    printf("\n内挿点を入力してください\n");
    printf("水平(0.0 ~ 1.0) : ");
    scanf("%lf", &x);
    printf("垂直(0.0 ~ 1.0) : ");
    scanf("%lf", &y);

    p = d[(int)(x + 0.5)][(int)(y + 0.5)];

    printf("\n<内挿点の画素値>\n");
    printf("%d\n", p);
}

//配列の4バイトを結合する
int combine_4bytes(unsigned char data[], int start)
{
    int result = 0, factor = 1, tmp;

    for (int i = 3; i >= 0; i--)
    {
        tmp = data[start + i];
        for (int j = i; j > 0; j--)
        {
            factor *= 256;
        }
        result += factor * tmp;
        factor = 1;
    }
    return result;
}

void print_header(unsigned char data[], int start, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("header[%d] = %02x ", start + i, data[start + i]);
    }
    printf("\n");
}