#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define X 3
#define Y 3

// 構造体 二次元配列にするか 変数にするか
struct stage{
    int num[X][Y];
    int count;
};

void fstgetin (struct stage *map);
void scdgetin (struct stage *map, int, int);
void moving (struct stage *map, int, int);
int judge (struct stage *map, int, int, int, int, int);
int outputhtml(struct stage);
void header(void);
void footer(void);
int outputdata(struct stage);

int main (int argc,char *argv[]){
    // 各種宣言 警告が出るので一応初期化しておく。
    int i, u;
    struct stage map;
    for(i=0; i<X; i++){
        for(u=0; u<Y; u++){
            map.num[i][u] = 0;
        }
    }
    map.count = 0;
    // 引数がある場合、ファイルを読み込む。
    if (argc > 1){
        int mx, my;
        mx = atoi(argv[1]);
        my = atoi(argv[2]);
        scdgetin(&map, mx, my);
    }
    // 引数がない場合、初回起動処理に移行。
    else {
        fstgetin(&map);
    }
    // HTMLの出力
    outputhtml(map);
    // ファイルの出力
    outputdata(map);
    return 0;
}

void fstgetin (struct stage *map){
    int mapseed[X*Y];
    int i, u, e, j , t;
    // まず配列に0,1,2... と格納する。
    for (i=0; i < X*Y; i++){
        mapseed[i] = i;
    }
    // それをシャッフルする。
    for(i=0; i < X*Y; i++) {
        j = rand()%X*Y;
        t = mapseed[i];
        mapseed[i] = mapseed[j];
        mapseed[j] = t;
    }
    // バラバラになった数字を配列に格納する。
    for(e=0, i=0; i<X; i++){
        for(u=0; u<Y; u++){
            (*map).num[i][u] = mapseed[e];
            e++;
        }
    }
    // 右上を空白にする。
    (*map).num[0][0] = -1;
}

void scdgetin (struct stage *map, int x, int y){
    int i, u;
    // ファイルの読み込み
    FILE *fd;
    char fmap[32];
    fd = fopen("./temp/stage.dat","r");
    fgets(fmap, 32, fd);
    fclose(fd);
    // 保存した配列の内容を読み込み
    (*map).num[0][0] = atoi(strtok(fmap, ","));
    for(i=0; i<X; i++){
        for(u=0; u<Y; u++){
            (*map).num[i][u] = atoi(strtok(NULL, ","));
        }
    }
    (*map).count = atoi(strtok(NULL, ",")) + 1;
    // 配列を動かす
    moving(map, x, y);
}

// 説明しよう！この関数は実行されると同時に指定された場所に隣接する空白に値を書き込む関数だ！
void moving (struct stage *map, int x, int y){
    int i, u;
    for (i=0;i<X;i++){
        for (u=0;u<Y;u++){
            if((*map).num[i][u] == -1 && judge(x, y, i, u, 0)){
                (*map).num[i][u] = (*map).num[x][y];
                (*map).num[x][y] = -1;
            }
        }
    }
}

// ココらへんの書き方下手くそ
int judge (struct stage *map, int x, int y, int i, int u, int getspace){
    if(getspace){
        int n, c;
        for (n=0;n<X;n++){
            for (c=0;c<Y;c++){
                if((*map).num[i][u] == -1){
                    i = n;
                    u = c;
                }
            }
        }
    }
    if((x == i && y == u - 1) || (x == i && y == u + 1) || (y == u && x == i + 1) || (y == u && x == i - 1)){
        return 1;
    }
    else{
        return 0;
    }
}

int outputhtml (struct stage map){
    // 各種宣言
    int i, u;
    // ヘッダの出力
    header();
    // ボディの出力
    printf("<table>\n");
    for (i=0; i<X; i++){
        printf("<tr>\n");
        for (u=0; u<Y; u++){
            // 空白マスは空白表示
            if (map.num[i][u] == -1){
                printf("<td></td>\n");
            }
            // 動けない場所にはリンクを貼らない。
            else if (judge(i, u, 0, 0, 1)){
                printf("<td><a href='pazzle.cgi?%d?%d'><img src='./temp/slide-%d.png'></td>\n", i, u, map.num[i][u]);
            }
            else{
                printf("<td><img src='./temp/slide-%d.png'></td>\n", map.num[i][u]);
            }
        }
    }
    printf("</table>\n");
    printf("<h2>現在のスコア:%3d</h2>\n", map.count);
    // フッタの出力
    footer();
}

void header(void){
    printf("<!DOCTYPE html>\n");
    printf("<html>\r\n");
    printf("<meta charset=\"utf-8\">\n");
    printf("<title>SlidePazzle.cgi</title>\n");
    printf("<link href=\"css/bootstrap.css\" rel=\"stylesheet\">\n");
    printf("</head>\n");
    printf("<body>\n");
    printf("<h1>SlidePazzle with CGI/C</h1><br>\n");
}

void footer(void){
    printf("</body>\n");
    printf("</html>\n");
}
int outputdata(struct stage map){
    int i, u;
    FILE *fp;
    fp = fopen("./temp/stage.dat","w");
    for (i=0; i<X; i++){
        for(u=0; u<Y; u++){
            fprintf(fp, "%d,", map.num[i][u]);
        }
    }
    fprintf(fp, "%d", map.count);
    fclose(fp);
    return 0;
}