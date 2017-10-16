#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define XU 3
#define YU 3

struct stage{
    int num[XU][YU];
    int sx;
    int sy;
    int count;
    int clear;
};

void firstentry (struct stage *map);
int  continuation (struct stage *map, int, int);
void moving (struct stage *map, int, int);
int  judge (struct stage *map, int, int);
void outputhtml (struct stage);
int  ifclear (struct stage);
int  outputdata (struct stage);
void header (struct stage map);
void writecookie (struct stage map);
void footer (void);

int main (int argc, char *argv[]){
    int i, u;
    struct stage map;
    for(i = 0; i < XU; i++){
        for(u = 0; u < YU; u++){
            map.num[i][u] = 0;
        }
    }
    map.count = 0;
    map.sx = 0;
    map.sy = 0;
    map.clear = 0;

    if(argc == 3){
        continuation(&map, atoi(argv[1]), atoi(argv[2]));
    } else if (argc == 1) {
        firstentry(&map);
    } else {
        printf("Arg Error.\n");
        return -1;
    }
    outputhtml(map);
    outputdata(map);
    return 0;
}

void firstentry (struct stage *map){
    int mapseed[XU*YU];
    int i, u, e, j, t;
    for(i = 0; i < XU*YU; i++){
        mapseed[i] = i;
    }
    for(i = 0; i < XU*YU; i++) {
        j = rand()%XU*YU;
        t = mapseed[i];
        mapseed[i] = mapseed[j];
        mapseed[j] = t;
    }
    for(e = 0 , i = 0; i < XU; i++){
        for(u = 0; u < YU; u++){
            map->num[i][u] = mapseed[e];
            e++;
        }
    }
    map->num[0][0] = -1;
    map->sx = 0;
    map->sy = 0;
}

int continuation (struct stage *map, int x, int y){
    int i, u;
    char *cookie;
    int count = 0;

    if((cookie = getenv("HTTP_COOKIE")) != NULL) {
        printf("%s",cookie);
    }


    FILE *fd;
    char fmap[32];
    fd = fopen("./temp/stage.dat","r");
    if(fd == NULL) {
        printf("File Pointer is NULL");
        return -1;
    }
    fgets(fmap, 32, fd);
    for(i = 0; i < XU; i++){
        for(u = 0; u < YU; u++){
            if (i == 0 && u == 0){
                map->num[0][0] = atoi(strtok(fmap, ","));
            } else {
                map->num[i][u] = atoi(strtok(NULL, ","));
            }
            if (map->num[i][u] == -1){
                map->sx = i;
                map->sy = u;
            }
        }
    }
    map->count = atoi(strtok(NULL, ",")) + 1;
    fclose(fd);
    moving(map, x, y);
    map->clear = ifclear(*map);
    return 0;
}

void moving (struct stage *map, int x, int y){
    if(judge(map, x, y)){
        map->num[map->sx][map->sy] = map->num[x][y];
        map->num[x][y] = -1;
        map->sx = x;
        map->sy = y;
    }
}

int judge (struct stage *map, int x, int y){
    if ((x == map->sx && y == map->sy - 1) || (x == map->sx && y == map->sy + 1)
     || (y == map->sy && x == map->sx + 1) || (y == map->sy && x == map->sx - 1)){
        return 1;
    } else {
        return 0;
    }
}

void outputhtml (struct stage map){
    int i, u;
    header(map);
    if (map.clear){
        printf("<h1>CLEAR!!!!!</h1>");
    }
    printf("<table>\n");
    for (i = 0; i < XU; i++){
        printf("<tr>\n");
        for (u = 0; u < YU; u++){
            if (map.num[i][u] == -1){
                printf("<td></td>\n");
            } else {
                printf("<td>");
                if (judge(&map, i, u)){
                    printf("<a href='puzzle.cgi?%d+%d'>", i, u);
                }
                printf("<img src='./temp/slide-%d.png'></td>\n", map.num[i][u]);
            }
        }
    }
    printf("</table>\n");
    printf("<h2>Score :%3d</h2>\n", map.count);
    footer();
}

int ifclear(struct stage map){
    int i, u;
    int count = 0;
    int s = 0;
    for(i = 0; i < XU; i++){
        for(u = 0; u < YU; u++){
            if(map.num[i][u] == count){
                s++;
            }
            count++;
        }
    }
    if (s == XU*YU - 1){
        return 1;
    } else {
        return 0;
    }
}

void header(struct stage map){
    printf("Content-type: text/html; charset=utf-8\n\n");
    // writecookie(map);
    printf("<!DOCTYPE html>\n");
    printf("<html>\r\n");
    printf("<title>SlidePuzzle.cgi</title>\n");
    printf("<link href=\"css/bootstrap.css\" rel=\"stylesheet\">\n");
    printf("</head>\n");
    printf("<body>\n");
    printf("<h1>SlidePuzzle with CGI/C</h1><br>\n");
}

void writecookie(struct stage map){
    int i, u;
    printf("Set-Cookie: stage=");
    for (i = 0; i < XU; i++){
        for(u = 0; u < YU; u++){
            printf("%d,", map.num[i][u]);
        }
    }
    printf("%d,E; path=/;\n\n", map.count);
}

void footer(void){
    printf("</body>\n");
    printf("</html>\n");
}

int outputdata(struct stage map){
    int i, u;
    FILE *fp;
    fp = fopen("./temp/stage.dat","w");
    for (i = 0; i < XU; i++){
        for(u = 0; u < YU; u++){
            fprintf(fp, "%d,", map.num[i][u]);
        }
    }
    fprintf(fp, "%d,E", map.count);
    fclose(fp);
    return 0;
}