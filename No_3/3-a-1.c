#include <stdio.h>

unsigned int combine_4bytes(unsigned char data[], int start);
unsigned char header[54];
void get_data(void);

int main(void)
{
    get_data();
    return 0;
}

void get_data(void)
{
    char filename[20];
    int i, c;
    FILE *fp;

    printf("ファイル名を入力してください：");
    scanf("%s", filename);
    fp = fopen(filename, "rb");

    if (fp==NULL)
    {
        printf("ファイルをオープンできません.\n");
        return;
    }

    printf("ファイルをオープンしました.\n");
    
    //ヘッダーの読み出し
    c = fgetc(fp);
    for(int i=0; i<54; i++)
    {
        header[i] = (unsigned char)c;
        c = fgetc(fp);
    }

    //ファイルタイプの出力
    printf("< ファイルタイプ >\n");
    printf("header[0] = %02x  header[1] = %x\n", header[0], header[1]);

    //ファイルサイズの出力
    printf("< ファイルサイズ >\n");
    printf("header[2] = %02x  header[3] = %02x  header[4] = %02x  header[5] = %02x\n",
            header[2], header[3], header[4], header[5]);

    //ファイルサイズを4バイトの変数に結合
    unsigned int size = combine_4bytes(header, 2);
    printf("%xバイト\n", size);

    printf("<予約領域>\n");
    printf("header[6] = %02x  header[7] = %02x  header[8] = %02x  header[9] = %02x\n",
            header[6], header[7], header[8], header[9]);


    
    fclose(fp);
    printf("ファイルをクローズしました.\n");
}

//配列の4バイトを結合する
unsigned int combine_4bytes(unsigned char data[], int start)
{
    unsigned int result = 0, tmp;

    for(int i=3; i >= 0; i--)
    {
        tmp = (unsigned int)data[3-i + start];
        result = result | tmp << ((i+1) * 8);
    }

    return result;
}