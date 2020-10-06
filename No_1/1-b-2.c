#include <stdio.h>

int main(void)
{

    int c, n = 0;
    unsigned char array[100];

    FILE *fp, *fp_cp;

    //読み込み部
    fp = fopen("test.bmp", "rb");
    if (fp == NULL)
    {
        printf("ファイルをオープンできません.\n");
        return 0;
    }
    printf("読み込み用ファイルをオープンしました.\n");

    c = fgetc(fp);
    while (c != EOF)
    {
        array[n] = (unsigned char)c;
        c = fgetc(fp);
        n++;
    }

    printf("%d 個のデータを読み込み,配列に格納しました.\n", n);
    fclose(fp);
    printf("読み込み用ファイルをクローズしました.\n");
    printf("配列の内容を表示します.\n");
    for (int i = 0; i < n; i++)
        printf("array[%d] = %d\n", i, array[i]);

    //書き込み部
    fp_cp = fopen("testcp.bmp", "wb");
    if (fp_cp == NULL)
    {
        printf("ファイルをオープンできません.\n");
        return 0;
    }
    printf("書き出し用ファイルをオープンしました.\n");

    for (int i = 0; i < n; i++)
        fputc((int)array[i], fp_cp);

    printf("配列に格納されていた%d個のデータを書き出しました.\n", n);
    fclose(fp_cp);
    printf("書き出し用ファイルをクローズしました.\n");
    return 0;
}
