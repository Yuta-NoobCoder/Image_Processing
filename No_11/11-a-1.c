#include <stdio.h>
#include <stdlib.h>

void processing(void);

int main(int argc, char *argv[])
{
    processing();
    return 0;
}

void processing(void)
{
    double x, y;
    double s, t, r0, r1;
    double mean;
    int p;

    int d[2][2] = {
        {10, 30},
        {20, 40}};

    printf("\n<使用する4つの画素値>\n");
    printf("%d %d\n", d[0][0], d[1][0]);
    printf("%d %d\n", d[0][1], d[1][1]);
    printf("\n内挿点を入力してください\n");
    printf("水平(0.0 ~ 1.0) : ");
    scanf("%lf", &x);
    printf("垂直(0.0 ~ 1.0) : ");
    scanf("%lf", &y);

    s = x;
    t = y;

    r0 = (1 - s) * d[0][0] + s * d[1][0];
    r1 = (1 - s) * d[0][1] + s * d[1][1];

    mean = (1 - t) * r0 + t * r1;

    printf("\n<内挿点の画素値>\n");
    printf("%.0f\n", mean);
}