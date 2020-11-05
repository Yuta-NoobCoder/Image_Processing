#include <stdio.h>
#include <stdlib.h>

void get_data(char*);
void processing(void);
int combine_4bytes(unsigned char data[], int start);
void print_header(unsigned char data[], int start, int len);
void put_data(char*);

void rgb_to_ybr(void);
void ybr_to_rgb(void);

unsigned char header[54];
unsigned char imgin[3][512][512];  //入力画像データ
unsigned char imgout[3][512][512]; //出力画像データ

int height = 0;
int width = 0;
int insert_bits = 0;

int main(int argc, char *argv[])
{
    get_data(argv[1]);
    rgb_to_ybr();
    processing();
    ybr_to_rgb();
    put_data(argv[2]);

    return 0;
}

void rgb_to_ybr(void)
{
    double rgb[3];
    double d_ycbcr[3] = {0}; //演算時に積算されるため初期化
    int i_ycbcr[3];
    double factor[3][3] = {{0.2990, 0.5870, 0.1140},
                           {-0.1687, -0.3313, 0.5000},
                           {0.5000, -0.4187, -0.0813}};

    //色情報の表示(RGB)
    if (height <= 16 && width <= 16)
    {
        printf("\n< ------- 入力信号 ( RGB ) ------- >\n");
        printf("\n< R 信号 >\n");
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                printf("%02x ", imgin[2][i][j]);
            }
            printf("\n");
        }

        printf("\n< G 信号 >\n");
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                printf("%02x ", imgin[1][i][j]);
            }
            printf("\n");
        }

        printf("\n< B 信号 >\n");
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                printf("%02x ", imgin[0][i][j]);
            }
            printf("\n");
        }
    }

    //YCbCr化
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            rgb[0] = imgin[2][i][j]; //R
            rgb[1] = imgin[1][i][j]; //G
            rgb[2] = imgin[0][i][j]; //B

            //変換行列を適用
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    switch (j)
                    {
                    case 0:
                        d_ycbcr[i] += rgb[0] * factor[i][j];
                        break;
                    case 1:
                        d_ycbcr[i] += rgb[1] * factor[i][j];
                        break;
                    case 2:
                        d_ycbcr[i] += rgb[2] * factor[i][j];
                        break;
                    }
                }
            }
            //整数値化
            for (int i = 0; i < 3; i++)
            {
                //四捨五入
                if (d_ycbcr[i] < 0.0)
                    i_ycbcr[i] = (int)(d_ycbcr[i] - 0.5);
                else
                    i_ycbcr[i] = (int)(d_ycbcr[i] + 0.5);
                //オフセット(y信号以外)
                if (i != 0)
                    i_ycbcr[i] += 128;
                //範囲外処理(0 - 255)
                if (i_ycbcr[i] < 0)
                    i_ycbcr[i] = 0;
                else if (i_ycbcr[i] > 255)
                    i_ycbcr[i] = 255;
            }
            //変換結果を上書き
            imgin[2][i][j] = i_ycbcr[0]; //Y
            imgin[1][i][j] = i_ycbcr[1]; //Cb
            imgin[0][i][j] = i_ycbcr[2]; //Cr

            //変数をリセット
            d_ycbcr[0] = 0;
            d_ycbcr[1] = 0;
            d_ycbcr[2] = 0;
        }
    }
    //色情報の表示(YCbCr)
    if (height <= 16 && width <= 16)
    {
        printf("\n< ------- 入力信号 ( YCbCr ) ------- >\n");
        printf("\n< Y 信号 >\n");
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                printf("%02x ", imgin[2][i][j]);
            }
            printf("\n");
        }

        printf("\n< Cb 信号 >\n");
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                printf("%02x ", imgin[1][i][j]);
            }
            printf("\n");
        }

        printf("\n< Cr 信号 >\n");
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                printf("%02x ", imgin[0][i][j]);
            }
            printf("\n");
        }
    }
}

void ybr_to_rgb(void)
{
    double ycbcr[3];
    double d_rgb[3] = {0}; //演算時に積算されるため初期化
    int i_rgb[3];
    double factor[3][3] = {{1.0000, 0.0000, 1.4020},
                           {1.0000, -0.3441, -0.7141},
                           {1.0000, 1.7720, 0.0000}};
    //色情報の表示(YCbCr)
    if (height <= 16 && width <= 16)
    {
        printf("\n< ------- 出力信号 ( YCbCr ) ------- >\n");
        printf("\n< Y 信号 >\n");
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                printf("%02x ", imgout[2][i][j]);
            }
            printf("\n");
        }

        printf("\n< Cb 信号 >\n");
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                printf("%02x ", imgout[1][i][j]);
            }
            printf("\n");
        }

        printf("\n< Cr 信号 >\n");
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                printf("%02x ", imgout[0][i][j]);
            }
            printf("\n");
        }
    }

    //RGB化
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            ycbcr[2] = imgout[2][i][j];         //Y
            ycbcr[1] = imgout[1][i][j] - 128.0; //Cb
            ycbcr[0] = imgout[0][i][j] - 128.0; //Cr

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    switch (j)
                    {
                    case 0:
                        d_rgb[i] += ycbcr[2] * factor[i][j];
                        break;
                    case 1:
                        d_rgb[i] += ycbcr[1] * factor[i][j];
                        break;
                    case 2:
                        d_rgb[i] += ycbcr[0] * factor[i][j];
                        break;
                    }
                }
            }
            //整数値化
            for (int i = 0; i < 3; i++)
            {
                //四捨五入
                if (d_rgb[i] < 0.0)
                    i_rgb[i] = (int)(d_rgb[i] - 0.5);
                else
                    i_rgb[i] = (int)(d_rgb[i] + 0.5);

                //範囲外処理(0 - 255)
                if (i_rgb[i] < 0)
                    i_rgb[i] = 0;
                else if (i_rgb[i] > 255)
                    i_rgb[i] = 255;
            }
            //変換結果を上書き
            imgout[2][i][j] = i_rgb[0]; //B
            imgout[1][i][j] = i_rgb[1]; //G
            imgout[0][i][j] = i_rgb[2]; //R

            //変数をリセット
            d_rgb[0] = 0;
            d_rgb[1] = 0;
            d_rgb[2] = 0;
        }
    }
    //色情報の表示(RGB)
    if (height <= 16 && width <= 16)
    {
        printf("\n< ------- 出力信号 ( RGB ) ------- >\n");
        printf("\n< R 信号 >\n");
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                printf("%02x ", imgout[2][i][j]);
            }
            printf("\n");
        }

        printf("\n< G 信号 >\n");
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                printf("%02x ", imgout[1][i][j]);
            }
            printf("\n");
        }

        printf("\n< B 信号 >\n");
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                printf("%02x ", imgout[0][i][j]);
            }
            printf("\n");
        }
    }
}

void get_data(char *filename)
{
    int i, c;
    FILE *fp;

    fp = fopen(filename, "rb");

    if (fp == NULL)
    {
        printf("入力ファイル名が入力されていないか、誤りがあります。\n");
        exit(1);
    }

    printf("ファイルをオープンしました.\n");

    //ヘッダーの読み出し
    for (int i = 0; i < 54; i++)
    {
        c = fgetc(fp);
        header[i] = (unsigned char)c;
    }

    //ファイルタイプの出力
    //printf("\n< ファイルタイプ >\n");
    //print_header(header, 0, 2);

    //ファイルサイズの出力
    printf("\n< ファイルサイズ >\n");
    //print_header(header, 2, 4);

    ////4変数をunsigned intに結合
    int size = combine_4bytes(header, 2);
    printf("%dバイト\n", size);

    //printf("\n< 予約領域 >\n");
    //print_header(header, 6, 4);

    //printf("\n< オフセット >\n");
    //print_header(header, 10, 4);

    int offset = combine_4bytes(header, 10);
    //printf("%dバイト\n", offset);

    //printf("\n< 情報ヘッダサイズ >\n");
    //print_header(header, 14, 4);

    printf("\n< 画像の幅 >\n");
    //print_header(header, 18, 4);

    width = combine_4bytes(header, 18);
    printf("%d 画素\n", width);

    printf("\n< 画像の高さ >\n");
    //print_header(header, 22, 4);

    height = combine_4bytes(header, 22);
    printf("%d ライン\n", height);

    //printf("\n< 色プレーン数 >\n");
    //print_header(header, 26, 2);

    //printf("\n< 1画素あたりのビット数 >\n");
    //print_header(header, 28, 2);

    //2変数を結合
    int bits = 256 * header[29] + header[28];
    //printf("%d ビット\n", bits);

    //printf("\n< 圧縮方式 >\n");
    //print_header(header, 30, 4);

    //printf("\n< 画像データサイズ >\n");
    //print_header(header, 34, 4);

    //printf("\n< 水平解像度 >\n");
    //print_header(header, 38, 4);

    //printf("\n< 垂直解像度 >\n");
    //print_header(header, 42, 4);

    //printf("\n< 色数 >\n");
    //print_header(header, 46, 4);

    //printf("\n< 重要な色数 >\n");
    //print_header(header, 50, 4);

    //printf("\n< 挿入ビット数 >\n");
    insert_bits = size - offset - width * height * (bits / 8);
    //printf("%d バイト\n", insert_bits);

    //画像データの読み出し
    for (int i = height - 1; i >= 0; i--) //Height
    {
        for (int j = 0; j < width; j++) //Width
        {
            for (int k = 0; k < 3; k++) //BGR
            {
                c = fgetc(fp);
                imgin[k][i][j] = (unsigned char)c;
            }
        }
    }

    fclose(fp);
    printf("\nファイルをクローズしました.\n");
}

void processing(void)
{
    for (int i = height - 1; i >= 0; i--) //Height
    {
        for (int j = 0; j < width; j++) //Width
        {
            for (int k = 0; k < 3; k++) //CbCrY
            {
                imgout[k][i][j] = k == 2 ? imgin[k][i][j] : 128; //Y信号のみ残す
            }
        }
    }
    printf("\n出力画像データを生成しました.\n");
}

void put_data(char *filename)
{
    int size, padding; //アラインメント用
    FILE *fp;

    fp = fopen(filename, "wb");

    if (fp == NULL)
    {
        printf("出力ファイル名が入力されていないか、誤りがあります。\n");
        exit(1);
    }
    printf("\nファイルをオープンしました.\n");

    //ヘッダーの書き出し
    for (int i = 0; i < 54; i++)
    {
        fputc(header[i], fp);
    }

    //画像データの書き出し
    for (int i = height - 1; i >= 0; i--) //Height
    {
        for (int j = 0; j < width; j++) //Width
        {
            for (int k = 0; k < 3; k++) //BGR
            {
                fputc(imgout[k][i][j], fp);
            }
        }
    }

    //4バイトアラインメント
    size = 54 + width * height * 3;
    padding = 4 - (size % 4);

    if (size % 4 != 0)
    {
        for (int i = 0; i < padding; i++)
        {
            fputc(0, fp);
        }
    }

    fclose(fp);
    printf("ファイルをクローズしました\n");
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