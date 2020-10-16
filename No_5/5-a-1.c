#include <stdio.h>
#include <stdlib.h>

void rgb_to_ybr(double r, double g, double b);
void ybr_to_rgb(double y, double cb, double cr);

double colorSpace[3]; //入力用
double  ybr[3], rgb[3]; //変換結果の格納用

int main(void)
{

    double r, g, b;

    printf("信号値を入力して下さい(実数値)\n");
    printf("R :");
    scanf("%lf", &r);
    printf("G :");
    scanf("%lf", &g);
    printf("B :");
    scanf("%lf", &b);
    
    printf("\n<入力された RGB 信号(実数値)>\n");
    printf("R : %9.4f\n", r);
    printf("G : %9.4f\n", g);
    printf("B : %9.4f\n", b);

    rgb_to_ybr(r,g,b); // 計算結果はybr[]に格納
    ybr_to_rgb(ybr[0], ybr[1], ybr[2]); // 計算結果はrgb[]に格納, 今回は未使用
}

void rgb_to_ybr(double r, double g, double b)
{
    //変換行列
    double factor[3][3] = {
        {0.2990, 0.5870, 0.1140},
        {-0.1687, -0.3313, 0.5000},
        {0.5000, -0.4187, -0.0813}
    };

    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            switch (j)
            {
            case 0:
                ybr[i] += r * factor[i][j];
                break;
            case 1:
                ybr[i] += g * factor[i][j];
                break;
            case 2:
                ybr[i] += b * factor[i][j];
                break;            
            }
        }
    }

    printf("\n<変換された YCbCr 信号(実数値)>\n");
    printf("Y  : %9.4f\n", ybr[0]);
    printf("Cb : %9.4f\n", ybr[1]);
    printf("Cr : %9.4f\n", ybr[2]);
}

void ybr_to_rgb(double y, double cb, double cr)
{


    //変換行列
    double factor[3][3] = {
        {1.0000, 0.0000, 1.4020},
        {1.0000, -0.3441, -0.7141},
        {1.0000, 1.7720, 0.0000}
    };

    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            switch (j)
            {
            case 0:
                rgb[i] += y * factor[i][j];
                break;
            case 1:
                rgb[i] += cb * factor[i][j];
                break;
            case 2:
                rgb[i] += cr * factor[i][j];
                break;            
            }
        }
    }
    printf("\n<再度変換された RGB 信号(実数値)>\n");
    printf("R : %9.4f\n", rgb[0]);
    printf("G : %9.4f\n", rgb[1]);
    printf("B : %9.4f\n", rgb[2]);
}
