#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define X 3
#define Y 3

// 構造体 二次元配列にするか 変数にするか
struct stage{
    int num[X][Y];
};

int firstentry(void);
int outputhtml(struct stage, int count);
int header(void);
int footer(void);
int outputdata(struct stage, int count);

int main (int argc,char *argv[]){
    // 各種宣言
    int x, y, i, u, e, count;
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
    //if (checkarg()){    }
    outputhtml(map,count);
    // 現在状況をファイルへ出力
    outputdata(map,count);
    return 0;
}

// この処理は蛇足かも。
int moving (struct stage map, int x, int y, int move){
    int i, u;
    // 隣り合った数が-1の時
    // ネストの深さは闇の深さ。要改善。
    for (i=0;i<X;i++){
        for (u=0;u<Y;u++){
            if (map.num[i][u] == -1){
                if (x == i && y == u - 1 || x == i && y == u + 1 || y == u && x == i + 1 || y == u && x == i - 1){
                    if (move){
                        //移動処理
                        map.num[i][u] = map.num[x][y];
                        map.num[x][y] = -1;
                        return 0;
                    }
                    else{
                        return 0;
                    }
                }
            }
        }
    }
}

int outputhtml (struct stage map, int count){
    //各種宣言
    int i, u;
    //ヘッダの出力
    header();
    printf("<table>\n");
    //ボディの出力
    for (i=0; i<X; i++){
        printf("<tr>\n");
        for (u=0; u<Y; u++){
            if (map.num[i][u] == -1){
                printf("<td></td>\n");
            }
            else if (moving(map, i, u, 0)){
                printf("<td><img src='./temp/slide-%d.png'></td>\n", map.num[i][u]);
            }
            else{
                printf("<td><a href='pazzle.cgi?x=%d?y=%d'><img src='./temp/slide-%d.png'></td>\n", i, u, map.num[i][u]);
            }
        }
    }
    printf("</table>\n");
    printf("<h2>現在のスコア:%3d</h2>\n", count);
    // フッタの出力
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
int outputdata(struct stage map, int count){
    printf("a");
}