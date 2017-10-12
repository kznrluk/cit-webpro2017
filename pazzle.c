#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define  BUFFER 1024
#define X 3
#define Y 3

int readfile(void);
int firstentry(void);


int main (int argc,char *argv[]){
    // 各種宣言
    int x, y, i, u;
    int map[X][Y];
    // 引数がある場合、ファイルを読み込む。
    if (argc == 2){
        printf("ファイル読み込み\n");
    }
    // 引数がない場合、初回起動処理に移行。
    else {
        int mapseed[X*Y];
        
        // まず配列に0,1,2... と格納する。
        for (i=0; i < X*Y; i++){
            mapseed[i] = i;
        }
        // それをシャッフルする。
        for(i=0; i<X*Y; i++){
            int j = rand()%X*Y;
            int t = mapseed[i];
            mapseed[i] = mapseed[j];
            mapseed[j] = t;
        }
        // バラバラになった数字を配列に格納する。
        for(i=0; i<X; i++){
            for(u=0; u<Y; u++){
                map[i][u] = mapseed[i+u];
            }
        }
        // 右上に空白を挿入する。
        map[0][0] = -1;
    }
    // Debug
    printf("DEBUG # ");
    for(i=0; i<X; i++){
        for(u=0; u<Y; u++){
            printf("%2d",map[i][u]);
        }
    }
    printf("\n");

    // クリックされた場所の隣に空白配列(-1)があるかどうかをチェックする。
    // checkarg();
    return 0;
}

int checkarg (int arg){
    
}

int output (int pieces){
    header();
    footer();
}

int header(){
    printf("Content-type: text/html\r\n");
    printf("\r\n");
    printf("<html>\r\n");
    printf("<body>\r\n");
    return 0;
}

int footer(){
    printf("<HTML>\r\n");
    printf("<BODY>\r\n");
    printf("</BODY>\r\n");
    printf("</HTML>\r\n\r\n");
    return 0;
}