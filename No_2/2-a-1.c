#include <stdio.h>

int main(void)
{

    char *filename;
    int bytes = 0;
    int c;

    FILE *fp;
    printf("ファイル名を入力してください：");
    scanf("%s", filename);
    fp = fopen(filename, "rb");

    if (fp == NULL)
    {
        printf("ファイルをオープンできません.\n");
        return 0;
    }

    printf("ファイルをオープンしました.\n");

    c = fgetc(fp);
    while (c != EOF)
    {
        printf("%d\n", c);
        c = fgetc(fp);
        bytes++;
    }

    printf("全部で %d バイト読み込みました．\n", bytes);

    fclose(fp);
    printf("ファイルをクローズしました.\n");

    return 0;
}
