#include <stdio.h>
#include <stdlib.h>

void rgb_to_ybr(double color[]);
void ybr_to_rgb(double color[]);

double colorSpace[3]; //入力用

int main(void)
{

    printf("信号値を入力して下さい(実数値)\n");
    printf("R :");
    scanf("%lf", &colorSpace[0]);
    printf("G :");
    scanf("%lf", &colorSpace[1]);
    printf("B :");
    scanf("%lf", &colorSpace[2]);

    printf("\n<入力された RGB 信号(実数値)>\n");
    printf("R : %9.4f\n", colorSpace[0]);
    printf("G : %9.4f\n", colorSpace[1]);
    printf("B : %9.4f\n", colorSpace[2]);

    rgb_to_ybr(colorSpace);
    ybr_to_rgb(colorSpace);
}

void rgb_to_ybr(double color[])
{
    double rgb[3];
    int int_ycbcr[3];
    //値を退避
    for (int i = 0; i < 3; i++)
    {
        rgb[i] = color[i];
        color[i] = 0;
    }

    //変換行列
    double factor[3][3] = {{0.2990, 0.5870, 0.1140},
                           {-0.1687, -0.3313, 0.5000},
                           {0.5000, -0.4187, -0.0813}};

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            switch (j)
            {
            case 0:
                color[i] += rgb[0] * factor[i][j];
                break;
            case 1:
                color[i] += rgb[1] * factor[i][j];
                break;
            case 2:
                color[i] += rgb[2] * factor[i][j];
                break;
            }
        }
    }

    printf("\n<変換された YCbCr 信号(実数値)>\n");
    printf("Y  : %9.4f\n", color[0]);
    printf("Cb : %9.4f\n", color[1]);
    printf("Cr : %9.4f\n", color[2]);

    //整数値化
    for (int i = 0; i < 3; i++)
    {
        //四捨五入
        if (color[i] < 0.0)
        {
            int_ycbcr[i] = (int)(color[i] - 0.5);
        }
        else
            int_ycbcr[i] = (int)(color[i] + 0.5);
        //オフセット(y信号以外)
        if (i != 0)
            int_ycbcr[i] += 128;
        //範囲外処理(0 - 255)
        if (int_ycbcr[i] < 0)
            int_ycbcr[i] = 0;
        else if (int_ycbcr[i] > 255)
            int_ycbcr[i] = 255;
    }
    printf("\n<変換された YCbCr 信号(整数値)>\n");
    printf("Y  : %4d\n", int_ycbcr[0]);
    printf("Cb : %4d\n", int_ycbcr[1]);
    printf("Cr : %4d\n", int_ycbcr[2]);
}

void ybr_to_rgb(double color[])
{
    double ycbcr[3];
    int int_rgb[3];
    //値を退避
    for (int i = 0; i < 3; i++)
    {
        ycbcr[i] = color[i];
        color[i] = 0;
    }

    //変換行列
    double factor[3][3] = {{1.0000, 0.0000, 1.4020},
                           {1.0000, -0.3441, -0.7141},
                           {1.0000, 1.7720, 0.0000}};

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            switch (j)
            {
            case 0:
                color[i] += ycbcr[0] * factor[i][j];
                break;
            case 1:
                color[i] += ycbcr[1] * factor[i][j];
                break;
            case 2:
                color[i] += ycbcr[2] * factor[i][j];
                break;
            }
        }
    }

    printf("\n<再度変換された RGB 信号(実数値)>\n");
    printf("R : %9.4f\n", color[0]);
    printf("G : %9.4f\n", color[1]);
    printf("B : %9.4f\n", color[2]);

    //整数値化
    for (int i = 0; i < 3; i++)
    {
        //四捨五入
        if (color[i] < 0.0)
        {
            int_rgb[i] = (int)(color[i] - 0.5);
        }
        else
            int_rgb[i] = (int)(color[i] + 0.5);

        //範囲外処理(0 - 255)
        if (int_rgb[i] < 0)
            int_rgb[i] = 0;
        else if (int_rgb[i] > 255)
            int_rgb[i] = 255;
    }

    printf("\n<再度変換された RGB 信号(整数値)>\n");
    printf("R : %4d\n", int_rgb[0]);
    printf("G : %4d\n", int_rgb[1]);
    printf("B : %4d\n", int_rgb[2]);
}