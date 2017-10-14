#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define XU 3
#define YU 3

struct stage{
    int num[XU][YU];
    int count;
};

void fstgetin (struct stage *map);
int scdgetin (struct stage *map, int, int);
void moving (struct stage *map, int, int);
int judge (struct stage *map, int, int, int, int, int);
void outputhtml(struct stage);
void header(void);
void footer(void);
int outputdata(struct stage);

int main(int argc,char *argv[]){
    // 各種宣言 警告が出るので一応初期化しておく。
    int i, u;
    struct stage map;
    for(i=0; i<XU; i++){
        for(u=0; u<YU; u++){
            map.num[i][u] = 0;
        }
    }
    map.count = 0;
    // 引数がある場合、ファイルを読み込む。
    if (argc >= 2){
        int mx, my;
        mx = atoi(argv[1]);
        my = atoi(argv[2]);
        scdgetin(&map, mx, my);
    } else {
        // 引数がない場合、初回起動処理に移行。
        fstgetin(&map);
    }
    // HTMLの出力
    outputhtml(map);
    // ファイルの出力
    outputdata(map);
    return 0;
}

void fstgetin (struct stage *map){
    int mapseed[XU*YU];
    int i, u, e, j , t;
    // まず配列に0,1,2... と格納する。
    for (i=1; i < XU*YU; i++){
        mapseed[i] = i;
    }
    // それをシャッフルする。
    for(i=0; i < XU*YU; i++) {
        j = rand()%XU*YU;
        t = mapseed[i];
        mapseed[i] = mapseed[j];
        mapseed[j] = t;
    }
    // バラバラになった数字を配列に格納する。
    for(e=0, i=0; i<XU; i++){
        for(u=0; u<YU; u++){
            map->num[i][u] = mapseed[e];
            e++;
        }
    }
    // 右上を空白にする。
    map->num[0][0] = 0;
}

int scdgetin (struct stage *map, int x, int y){
    int i, u;
    // ファイルの読み込み
    FILE *fd;
    char fmap[32];
    fd = fopen("./temp/stage.dat","r");
    if(fd == NULL) {
        printf("File Pointer is NULL");
        return -1;
    }
    fgets(fmap, 32, fd);
    // 保存した配列の内容を読み込み
    for(i=0; i<XU; i++){
        for(u=0; u<YU; u++){
            if (i==0 && u ==0){
                map->num[0][0] = atoi(strtok(fmap, ","));
                printf("%d",map->num[0][0]);
            } else {
                map->num[i][u] = atoi(strtok(NULL, ","));
                printf("%d",map->num[i][u]);
            }
        }
    }
    map->count = atoi(strtok(NULL, ",")) + 1;
    fclose(fd);
    // 配列を動かす
    moving(map, x, y);
    return 0;
}

// 説明しよう！この関数は実行されると同時に指定された場所に隣接する空白に値を書き込む関数だ！
void moving (struct stage *map, int x, int y){
    int i, u;
    for (i=0;i<XU;i++){
        for (u=0;u<YU;u++){
            if(map->num[i][u] == 0 && judge(map, x, y, i, u, 0)){
                map->num[i][u] = map->num[x][y];
                map->num[x][y] = 0;
            }
        }
    }
}

// ココらへんの書き方下手くそ
int judge (struct stage *map, int x, int y, int i, int u, int getspace){
    if(getspace){
        int n, c;
        for (n=0;n<XU;n++){
            for (c=0;c<YU;c++){
                if(map->num[n][c] == 0){
                    i = n;
                    u = c;
                }
            }
        }
    }
    if((x == i && y == u - 1) || (x == i && y == u + 1) || (y == u && x == i + 1) || (y == u && x == i - 1)){
        return 1;
    } else {
        return 0;
    }
}

void outputhtml (struct stage map){
    // 各種宣言
    int i, u;
    // ヘッダの出力
    header();
    // ボディの出力
    printf("<table>\n");
    for (i=0; i<XU; i++){
        printf("<tr>\n");
        for (u=0; u<YU; u++){
            if (map.num[i][u] == 0){
                // 空白マスは空白表示
                printf("<td></td>\n");
            } else if (judge(&map, i, u, 0, 0, 1)){
                // 動けない場所にはリンクを貼らない。
                printf("<td><a href='pazzle.cgi?%d?%d'><img src='./temp/slide-%d.png'></td>\n", i, u, map.num[i][u]);
            } else {
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
    printf("Content-type: text/html; charset=shift_jis\n\n");
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
    for (i=0; i<XU; i++){
        for(u=0; u<YU; u++){
            fprintf(fp, "%d,", map.num[i][u]);
        }
    }
    fprintf(fp, "%d,E", map.count);
    fclose(fp);
    return 0;
}