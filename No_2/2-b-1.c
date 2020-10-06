#include <stdio.h>

int main(void)
{

    char *filename;
    int n, c;
    FILE *fp;

    printf("ファイル名を入力してください：");
    scanf("%s", filename);
    fp = fopen(filename, "wb");

    if (fp==NULL)
    {
        printf("ファイルをオープンできません.\n");
        return 0;
    }

    printf("ファイルをオープンしました.\n");
    printf("何バイト書き出しますか：");
    scanf("%d", &n);
    printf("0 以上 255 以下の値を %d 個入力して下さい.\n", n);
    for(int i=0; i<n; i++)
    {
        printf("No.%d : ", i+1);
        scanf("%d", &c);
        fputc(c, fp);
    }

    fclose(fp);
    printf("ファイルをクローズしました.\n");

    return 0;
}
