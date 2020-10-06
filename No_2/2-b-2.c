#include <stdio.h>
#include <stdlib.h>

int main(void)
{

    char fname_original[20];
    char fname_copied[20];
    int c, n = 0;
    unsigned char array[100];

    FILE *fp, *fp_cp;

    printf("コピー元のファイル名を入力してください：");
    scanf("%s", fname_original);

    printf("コピー先のファイル名を入力してください：");
    scanf("%s", fname_copied);


    //読み込み部
    fp = fopen(fname_original, "rb");
    if (fp == NULL)
    {
        printf("ファイルをオープンできません.\n");
        return 0;
    }
    printf("%sをオープンしました.\n", fname_original);

    c = fgetc(fp);
    while (c != EOF)
    {
        array[n] = (unsigned char)c;
        c = fgetc(fp);
        n++;
    }

    printf("%d 個のデータを読み込み,配列に格納しました.\n", n);
    
    fclose(fp);
    printf("%sをクローズしました.\n", fname_original);

    printf("配列の内容を表示します.\n");
    for (int i = 0; i < n; i++)
        printf("array[%d] = %d\n", i, array[i]);

    //書き込み部
    fp_cp = fopen(fname_copied, "wb");
    if (fp_cp == NULL)
    {
        printf("ファイルをオープンできません.\n");
        return 0;
    }
    printf("%sをオープンしました.\n", fname_copied);

    for (int i = 0; i < n; i++)
        fputc((int)array[i], fp_cp);

    printf("配列に格納されていた%d個のデータを書き出しました.\n", n);
    fclose(fp_cp);
    printf("%sをクローズしました.\n", fname_copied);
    return 0;
}
