#include <stdio.h>

unsigned int combine_4bytes(unsigned char data[], int start);
void print_header(unsigned char data[], int start, int len);

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
    printf("\n< ファイルタイプ >\n");
    print_header(header, 0, 2);

    //ファイルサイズの出力
    printf("\n< ファイルサイズ >\n");
    print_header(header, 2, 4);

    //4変数をunsigned intに結合
    unsigned int size = combine_4bytes(header, 2);
    printf("%dバイト\n", size);
}

//配列の4バイトを結合する
unsigned int combine_4bytes(unsigned char data[], int start)
{
    unsigned int result = 0, tmp;
    
    for(int i=0; i<4; i++)
    {
        tmp = (unsigned int)data[3-i + start];
        result = result | tmp << ((3-i) * 8);
    }

    return result;
}

void print_header(unsigned char data[], int start, int len)
{
    for(int i=0; i<len; i++)
    {
        printf("header[%d] = %02x ", start + i, data[start + i]);
    }
    printf("\n");
}