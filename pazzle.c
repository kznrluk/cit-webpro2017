#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define  BUFFER 1024
#define X 3
#define Y 3

// 構造体 二次元配列にするか 変数にするか
struct stage{
    int num[X][Y];
};

int readfile(void);
int firstentry(void);
int output(struct stage);
int header(void);
int footer(void);

int main (int argc,char *argv[]){
    // 各種宣言
    int x, y, i, u;
    struct stage map;
    // 引数がある場合、ファイルを読み込む。
    if (argc == 2){
        printf("ファイル読み込み\n");
    }
    // 引数がない場合、初回起動処理に移行。
    else {
        int size = X * Y;
        int mapseed[size];
        // まず配列に0,1,2... と格納する。
        for (i=0; i < size; i++){
            mapseed[i] = i;
        }
        // それをシャッフルする。
        for(int i = 0; i < size; i++) {
            int j = rand()%size;
            int t = mapseed[i];
            mapseed[i] = mapseed[j];
            mapseed[j] = t;
        }
        // バラバラになった数字を配列に格納する。
        int e = 0;
        for(i=0; i<X; i++){
            for(u=0; u<Y; u++){
                map.num[i][u] = mapseed[e];
                e++;
            }
        }
        // 右上に空白を挿入する。
        map.num[0][0] = -1;
    }
    // Debug
    printf("<-- DEBUG # ");
    for(i=0; i<X; i++){
        for(u=0; u<Y; u++){
            printf("%2d",map.num[i][u]);
        }
    }
    printf(" -->\n");

    // クリックされた場所の隣に空白配列(-1)があるかどうかをチェックする。
    // checkarg();
    output(map);
    return 0;
}

int checkarg (int arg){
    
}

int output (struct stage map){
    //各種宣言
    int i, u;
    //ヘッダの出力
    header();
    printf("<table>\n");
    //ボディの出力
    for (i=0; i<X; i++){
        printf("<tr>\n");
        for(u=0; u<Y; u++){
            if (map.num[i][u] == -1){
                printf("<td></td>\n");
            }
            else{
                printf("<td><a href='pazzle.cgi?x=%d?y=%d'><img src='./temp/slide-%d.png'>\n", i, u, map.num[i][u]);
            }
        }
    }
    printf("</table>\n");
    //フッタの出力
    footer();
}

int header(void){
    printf("<!DOCTYPE html>\n");
    printf("<html>\r\n");
    printf("<meta charset=\"utf-8\">\n");
    printf("<title>SlidePazzle.cgi</title>\n");
    printf("<link href=\"css/bootstrap.css\" rel=\"stylesheet\">\n");
    printf("</head>\n");
    printf("<body>\n");
    printf("<h1>SlidePazzle with CGI/C</h1><br>\n");
    return 0;
}

int footer(void){
    printf("</body>\n");
    printf("</html>\n");
    return 0;
}