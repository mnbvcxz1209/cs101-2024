#include <stdio.h>

int main()
{
    FILE*fp;
    int a[] = {0,1,2};
    char b[] = "ABC";
    float c[] = {1.1,1.2,1.3};
    int ra[3];
    char rb[3];
    float rc[3];
    int i=0;
    fp = fopen("a.bin","wb+");
    fwrite(a,sizeof(a),1,fp);
    fwrite(b,sizeof(char),3,fp);
    fwrite(c,sizeof(c),1,fp);
    fseek(fp,0,SEEK_SET);
    fread(ra,sizeof(ra),1,fp);
    fread(rb,sizeof(rb),1,fp);
    fread(rc,sizeof(rc),1,fp);
    
    for(int i = 0;i<=2;i++)
    {
        printf("%d ",ra[i]);
    }
    printf("\n");
    for(int i = 0;i<=2;i++)
    {
        printf("%c ",rb[i]);
    }
     printf("\n");
    for(int i = 0;i<=2;i++)
    {
        printf("%f ",rc[i]);
    }
    return 0;
}
