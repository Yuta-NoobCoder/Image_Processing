#include <stdio.h>
#include <stdlib.h>

void get_data(void);
void processing(void);
int combine_4bytes(unsigned char data[], int start);
void print_header(unsigned char data[], int start, int len);
void put_data(void);

unsigned char header[54];
unsigned char imgin[3][512][512];  //入力画像データ
unsigned char imgout[3][512][512]; //出力画像データ

int height = 0,
    width = 0, insert_bits = 0;

int main(void)
{
    get_data();
    processing();
    put_data();
    return 0;
}

void get_data(void)
{
    char filename[20];
    int i, c;
    FILE *fp;

    printf("入力ファイル名を入力してください：");
    scanf("%s", filename);
    fp = fopen(filename, "rb");

    if (fp == NULL)
    {
        printf("ファイルをオープンできません.\n");
        return;
    }

    printf("ファイルをオープンしました.\n");

    //ヘッダーの読み出し
    for (int i = 0; i < 54; i++)
    {
        c = fgetc(fp);
        header[i] = (unsigned char)c;
    }

    //ファイルタイプの出力
    printf("\n< ファイルタイプ >\n");
    print_header(header, 0, 2);

    //ファイルサイズの出力
    printf("\n< ファイルサイズ >\n");
    print_header(header, 2, 4);

    //4変数をunsigned intに結合
    int size = combine_4bytes(header, 2);
    printf("%dバイト\n", size);

    printf("\n< 予約領域 >\n");
    print_header(header, 6, 4);

    printf("\n< オフセット >\n");
    print_header(header, 10, 4);

    int offset = combine_4bytes(header, 10);
    printf("%dバイト\n", offset);

    printf("\n< 情報ヘッダサイズ >\n");
    print_header(header, 14, 4);

    printf("\n< 画像の幅 >\n");
    print_header(header, 18, 4);

    width = combine_4bytes(header, 18);
    printf("%d 画素\n", width);

    printf("\n< 画像の高さ >\n");
    print_header(header, 22, 4);

    height = combine_4bytes(header, 22);
    printf("%d ライン\n", height);

    printf("\n< 色プレーン数 >\n");
    print_header(header, 26, 2);

    printf("\n< 1画素あたりのビット数 >\n");
    print_header(header, 28, 2);

    //2変数を結合
    int bits = 256 * header[29] + header[28];
    printf("%d ビット\n", bits);

    printf("\n< 圧縮方式 >\n");
    print_header(header, 30, 4);

    printf("\n< 画像データサイズ >\n");
    print_header(header, 34, 4);

    printf("\n< 水平解像度 >\n");
    print_header(header, 38, 4);

    printf("\n< 垂直解像度 >\n");
    print_header(header, 42, 4);

    printf("\n< 色数 >\n");
    print_header(header, 46, 4);

    printf("\n< 重要な色数 >\n");
    print_header(header, 50, 4);

    printf("\n< 挿入ビット数 >\n");
    insert_bits = size - offset - width * height * (bits / 8);
    printf("%d バイト\n", insert_bits);

    //画像データの読み出し
    for (int i = height - 1; i >= 0; i--) //Height
    {
        for (int j = 0; j < width; j++) //Width
        {
            for (int k = 0; k < 3; k++) //BGR
            {
                c = fgetc(fp);
                imgin[2 - k][j][i] = (unsigned char)c;
            }
        }
    }

    fclose(fp);
    printf("\nファイルをクローズしました.\n");
}

void processing(void)
{

    if (height <= 16 && width <= 16)
    {
        printf("\n< R 信号 >\n");
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                printf("%02x ", imgin[0][j][i]);
            }
            printf("\n");
        }

        printf("\n< G 信号 >\n");
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                printf("%02x ", imgin[1][j][i]);
            }
            printf("\n");
        }

        printf("\n< B 信号 >\n");
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                printf("%02x ", imgin[2][i][j]);
            }
            printf("\n");
        }
    }
    else
    {
        printf("\n画像が大きすぎるためデータ表示を省略します.\n");
    }

    //入力画像をimgoutに格納
    for (int i = height - 1; i >= 0; i--) //Height
    {
        for (int j = 0; j < width; j++) //Width
        {
            for (int k = 0; k < 3; k++) //BGR
            {
                //RGBをBGRに反転
                imgout[k][j][i] = imgin[2 - k][j][i];
            }
        }
    }
    printf("\n出力画像データを生成しました.\n");
}

void put_data(void)
{
    char filename[20];
    int len; //アラインメント用
    FILE *fp;

    printf("\n出力ファイル名を入力してください：");
    scanf("%s", filename);
    fp = fopen(filename, "wb");

    if (fp == NULL)
    {
        printf("ファイルをオープンできません.\n");
        return;
    }
    printf("ファイルをオープンしました.\n");

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
                //RGBをBGRに反転
                fputc(imgout[k][j][i], fp);
            }
        }
        //ラインごとに4バイトのAlignmentを適用
        if (width % 4 != 0)
        {
            for (int i = 0; i < 4 - (width % 4); i++)
            {
                fputc(0, fp);
            }
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