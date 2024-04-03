#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
    int receipt_id;
    int receipt_price;
    char receipt_time[32];
    int lotto_set[5][7];
} lotto_record_t;

void lottoGen(int);
void winLotto();
void out2Txt(lotto_record_t,int);
int out2Bin(lotto_record_t);
int readBin();

int main()
{
    int input;

    system("chcp 65001");

    printf("請問您要買幾組樂透彩︰ ");
    scanf("%d", &input);
    getchar();

    if (input==0){
        winLotto();
    }
    else{
        lottoGen(input);
    }

    return 0;
}

void lottoGen(int k){
    int myRow;
    int myColumn;
    int idx;
    int r;
    lotto_record_t myLotto;
    time_t t = time(NULL);
    char *ct = ctime(&t);

    myLotto.receipt_price = k*100;          //產生購買價格

                                            //產生購買日期
    strncpy(myLotto.receipt_time, ct, sizeof(myLotto.receipt_time));

    srand(1);

    for ( myRow=0 ; myRow<5 ; myRow++ ){
        for ( myColumn=0; myColumn<7; myColumn++){
            myLotto.lotto_set[myRow][myColumn]=0;
        }
    }
                                            //產生樂透號碼
    for ( myRow=0 ; myRow<k ; myRow++ ){
        for ( myColumn=0 ; myColumn<7 ; myColumn++ ){
            myLotto.lotto_set[myRow][myColumn] = rand()%69+1;

            for ( idx=myColumn-1 ; idx>=0 ; idx--){
                if ( myLotto.lotto_set[myRow][idx] == myLotto.lotto_set[myRow][myColumn] ){
                    idx=-1;
                    myColumn--;
                }
            }
        }
    }
    r = out2Bin(myLotto);
    out2Txt(myLotto,r);

}

                                            //寫入二進位檔
int out2Bin(lotto_record_t olotto){
    int num;
    FILE *fptr;

    num=readBin();
    olotto.receipt_id=num;

    fptr=fopen("record.bin","ab");
    fwrite(&olotto, sizeof(lotto_record_t),1,fptr);
    fclose(fptr);
    return num;
}

                                            //讀取二進位檔筆數
int readBin(){
    int cnt=0;
    FILE *fptr;
    lotto_record_t buffer;

    fptr = fopen("record.bin","rb");

    if (fptr == NULL){
        return 1;
    }

    do {
        fread(&buffer, sizeof(lotto_record_t),1,fptr);
        cnt++;
    } while (!feof(fptr));

    fclose(fptr);
    return cnt;
}

                                            //寫入文字檔
void out2Txt(lotto_record_t alotto, int z){
    int x;
    int y;
    int i;
    char temp1[5];
    char fn[]="lotto[00000].txt";
    char temp2[]="=                          =";

    sprintf(temp1,"%05d",z);
    for (i=6; i<11 ; i++){
        fn[i]=temp1[i-6];
    }

    FILE *fptr;
    fptr = fopen(fn,"w");

    fprintf(fptr,"========= lotto649 =========\n");
    fprintf(fptr,"========+ No.%05d +========\n",z);
    for ( i=0 ; i<24 ;i++ ){
        temp2[i+2]=alotto.receipt_time[i];
    }
    fprintf(fptr,"%s\n",temp2);

    for ( x=0 ; x<5 ;x++){
        fprintf(fptr,"[%1d]:",x+1);

        for ( y=0 ; y<7 ; y++){
            if ( alotto.lotto_set[x][y] > 0 ){
                fprintf(fptr," %02d",alotto.lotto_set[x][y]);
            }
            else{
                fprintf(fptr," --");
            }
        }

        fprintf(fptr,"\n");
    }
    fprintf(fptr,"========= csie@CGU =========\n");
    fclose(fptr);
}

                                            //對奬
void winLotto(){
    int win[3]={70,70,70};
    int num;
    int flag=0;
    int x;
    int y;
    int i;
    char str[80];
    char delim[]=" ";

    FILE *fptr;
    lotto_record_t buffer;

    printf("請輸入中奬號碼(最多三個)︰");
    gets(str);

    char *token=strtok(str,delim);
    printf("輸入中奬號碼為︰ ");
    for ( i=0 ; token!=NULL && i<3 ; i++ ){
        win[i]=atoi(token);
        printf("%02d ", win[i]);
        token=strtok(NULL, delim);
    }

    printf("\n");
    printf("以下為中奬彩券︰\n");

    num=readBin();

    fptr = fopen("record.bin","rb");

    for ( i=0 ; i<num-1 ; i++ ){
        fread(&buffer, sizeof(lotto_record_t),1,fptr);

        for( x=0 ; x<5 ; x++ ){
            for( y=0 ; y<7 ; y++){
                if ( (buffer.lotto_set[x][y]==win[0]) || (buffer.lotto_set[x][y]==win[1]) || (buffer.lotto_set[x][y]==win[2]) ){
                    flag=1;
                }
            }
            if ( flag==1 ){
                printf("彩券 No. %d\n", buffer.receipt_id);
                printf("售出時間︰%s", buffer.receipt_time);
                printf("號碼︰ %02d %02d %02d %02d %02d %02d %02d\n\n", buffer.lotto_set[x][0], buffer.lotto_set[x][1], buffer.lotto_set[x][2],\
                    buffer.lotto_set[x][3], buffer.lotto_set[x][4], buffer.lotto_set[x][5], buffer.lotto_set[x][6]);
            }
            flag=0;
        }
    }

    fclose(fptr);
}

