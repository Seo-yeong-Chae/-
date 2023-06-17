#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>

using namespace std;


#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4


class snake{

public:
    bool gameOver;
    int growthCnt, growthItemTime, growthItemX, growthItemY;
    int poisonCnt, poisonItemTime, poisonItemX, poisonItemY;
    int gateX1, gateY1, gateX2, gateY2, gateTime;
    int gItemCnt, pItemCnt, passGateCnt, maxLength, currentLength;
    int nTail, current_tick;
    int missonGItem, goalPItem, missonPassGate, missionMaxLength;
    int _x;
    int _y;
    snake();
    ~snake();
    void start();
    int keyControl();
    int drawTitle();
    void drawInfo();
    int selectStage();
    void drawMap(int* x, int* y);
    void gLoop(int s);
    void move(int* x, int* y);
    void growthItem();
    void poisonItem();
    void openGate();
    bool missionCheck();
    void drawVictory();
    int drawFail();
    void scoreBoard();
    int getScore();
    void stageClear();

};
int tailX[100], tailY[100];

snake::snake(){
    initscr();
    keypad(stdscr, TRUE);
    curs_set(0);
    noecho();

    srand(time(0));
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_CYAN);
    init_pair(2, COLOR_WHITE, COLOR_YELLOW);
    init_pair(3, COLOR_MAGENTA, COLOR_CYAN);
    init_pair(4, COLOR_BLACK, COLOR_RED);
    init_pair(5, COLOR_BLACK, COLOR_GREEN);
    init_pair(6, COLOR_BLACK, COLOR_CYAN);
    init_pair(7, COLOR_BLACK, COLOR_BLACK);
    init_pair(8, COLOR_BLUE, COLOR_WHITE);
}
snake::~snake(){
    endwin();
}

void snake::start()
{
    int menuCode = drawTitle();
    if (menuCode == 0){
        int stage = selectStage();
        switch (stage){
            case 0:
                gLoop(0);

                break;
            case 2:
                gLoop(1);
                break;
            case 4:
                gLoop(2);
                break;
            case 6:
                gLoop(3);
                break;
            case 8:
                clear();
                start();
                break;
        }
    }
    else if (menuCode == 2){
        drawInfo();
    }
    else if (menuCode == 4){
        endwin();
    }
}

int snake::keyControl(){
    int tmp = getch();

    switch (tmp){
        case KEY_LEFT:
            return LEFT;
            break;
        case KEY_UP:
            return UP;
            break;
        case KEY_DOWN:
            return DOWN;
            break;
        case KEY_RIGHT:

            return RIGHT;
            break;
        case ' ':
            return SUBMIT;
            break;
    }
    return 0;
}


// 초기 타이틀 화면
int snake::drawTitle(){
    printw("\n\n\n\n");
    printw("          ###     ##    #      #      #    #    #####    \n");
    printw("         #        # #   #     # #     #  #      #        \n");
    printw("         ####     #  #  #    #####    ##        ####     \n");
    printw("             #    #   # #    #   #    #  #      #        \n");
    printw("         ####     #    ##    #   #    #    #    #####    \n");
    bkgd(COLOR_PAIR(8));

    int y = 12;
    int x = 24;
    mvprintw(y, x-2, "> GAME START");
    mvprintw(y+2, x, "GAME INFO");
    mvprintw(y+4, x, "EXIT");

    refresh();
    while(1){
        int k = keyControl();
        switch(k){
            case UP: {
                if (y > 12){
                    mvprintw(y, x-2, " ");
                    mvprintw(--(--y), x-2, ">");
                }
                break;
            }
            case DOWN: {
                if (y < 16){
                    mvprintw(y, x-2, " ");
                    mvprintw(++(++y), x-2, ">");
                }
                break;
            }
            refresh();
            case SUBMIT:{
                return y-12;
            }
        }

    }
}

// 게임 정보 화면
void snake::drawInfo(){
    clear();
    printw("\n\n\n\n");
    printw("                               < GAME INFORMAION >                           \n\n");
    printw(" 1. Use the arrow keys (<, ^, v, >) \n");
    printw(" 2. Snake cannot be moved in the opposite direction of the proceeding direction\n");
    printw("    (Failed to move to tail direction of snake)\n");
    printw(" 3. Snake cannot pass its body\n");
    printw(" 4. Snake cannot pass through the wall\n");
    printw(" 5. The movement of the snake in the head direction is shifted by tick\n");
    printw(" 6. Tail increases by 1 when snake acquires a Grow Item\n");
    printw(" 7. If you acquire a Poison Item for a snake, the tail is reduced by 1\n");
    printw(" 8. Snake fails if the body length is less than 3\n\n");
    printw("                       Press the <Spacebar> key to continue");
    border('|','|','_','_','o','o','o','o');


    refresh();
    while(1){
        if (keyControl() == SUBMIT){
            clear();
            start();
        }
    }
}

// 스테이지 선택 화면
int snake::selectStage(){
    int x = 24;
    int y = 6;
    clear();
    printw("\n\n");
    printw("                         [ Stage Select ]\n\n");
    mvprintw(y, x-2, "> Stage 1");
    mvprintw(y+2, x, "Stage 2");
    mvprintw(y+4, x, "Stage 3");
    mvprintw(y+6, x, "Stage 4");
    mvprintw(y+8, x, "Back");

    while(1){
        int n = keyControl();
        switch(n){
            case UP: {
                if(y>6){
                    mvprintw(y, x-2, " ");
                    mvprintw(--(--y), x-2, ">");
                }
                break;
            }
            case DOWN:{
                if(y<14){
                    mvprintw(y, x-2, " ");
                    mvprintw(++(++y), x-2, ">");
                }
                break;
            }
            case SUBMIT:{
                return y-6;
            }
        }
    }
}

// 클리어 화면
void snake::drawVictory(){
    clear();
    printw("\n\n\n\n\n\n");
    
    attron(COLOR_PAIR(3));
    printw("                          Congratulation!                          \n\n");
    attroff(COLOR_PAIR(3));
    printw("                        CLEAR ALL THE STAGES               \n\n\n\n\n\n");
    printw("                 Press the <Spacebar> key to Continue                 ");
    refresh();
    while(1){
        if (keyControl() == SUBMIT){
            clear();
            start();
        }
    }
}


// 실패 화면
int snake::drawFail(){
    clear();
    
    attron(COLOR_PAIR(4));
    printw("\n\n\n\n\n\n");
    printw("                           GAME OVER                           \n");
    attroff(COLOR_PAIR(4));
    printw("  ( You can play the game again by pressing 'Restart' button)  ");
    int y = 12;
    int x = 27;
    mvprintw(y, x-2, "> RESTART");
    mvprintw(y+2, x, "EXIT");


    refresh();
    while(1){
        int k = keyControl();
        switch(k){
            case UP: {
                if (y > 12){
                    mvprintw(y, x-2, " ");
                    mvprintw(--(--y), x-2, ">");
                }
                break;
            }
            case DOWN: { 
                if (y < 14){
                    mvprintw(y, x-2, " ");
                    mvprintw(++(++y), x-2, ">");
                }
                break;
            }
            refresh();
            case SUBMIT:{
                return y-12;
            }
        }

    }
}



// map
char tmpMap[25][51];

char map1[25][51] = {
        {"21111111111111111111111111111111111111111111111112"},
        {"10000000000000000000000000000000000000000000000001"},
        {"10000000000000000000000000000000000000000000000001"},
        {"10000000000000000000000000000000000000000000000001"},
        {"10000000000000000000034400000000000000000000000001"},
        {"10000000000000000000000000000000000000000000000001"},
        {"10000000000000000000000000000000000000000000000001"},
        {"10000000000000000000000000000000000000000000000001"},
        {"10000000000000000000000000000000000000000000000001"},
        {"10000000000000000000000000000000000000000000000001"},
        {"10000000000000000000000000000000000000000000000001"},
        {"10000000000000000000000000000000000000000000000001"},
        {"10000000000000000000000000000000000000000000000001"},
        {"10000000000000000000000000000000000000000000000001"},
        {"10000000000000000000000000000000000000000000000001"},
        {"10000000000000000000000000000000000000000000000001"},
        {"10000000000000000000000000000000000000000000000001"},
        {"10000000000000000000000000000000000000000000000001"},
        {"10000000000000000000000000000000000000000000000001"},
        {"10000000000000000000000000000000000000000000000001"},
        {"10000000000000000000000000000000000000000000000001"},
        {"10000000000000000000000000000000000000000000000001"},
        {"10000000000000000000000000000000000000000000000001"},
        {"10000000000000000000000000000000000000000000000001"},
        {"21111111111111111111111111111111111111111111111112"}
};
char map2[25][51] = {
    {"21111111111111111111111111111111111111111111111112"},
    {"10000000000000000000000000000000000000000000000001"},
    {"10000000000000000000000000000000000000000000000001"},
    {"10000000000000000000000000000000000000000000000001"},
    {"10000000000000000000000000000000000000000000000001"},
    {"10000000000000000000000000000000000000000000000001"},
    {"10000000111111111111111111111111111111110000000001"},
    {"10000000000000000000000000000000000000000000000001"},
    {"10000000000000000000000000000000000000000000000001"},
    {"10000000000000000000000000000000000000000000000001"},
    {"10000000000000000000000000000000000000000000000001"},
    {"10000000000000000000000000000000000000000000000001"},
    {"10000000111111111111111111111111111111110000000001"},
    {"10000000000000000000000000000000000000000000000001"},
    {"10000000000000000000000000000000000000000000000001"},
    {"10000000000000000000000000000000000000000000000001"},
    {"10000000000000000000000000000000000000000000000001"},
    {"10000000000000000000000000000000000000000000000001"},
    {"10000000111111111111111111111111111111110000000001"},
    {"10000000000000000000000000000000000000000000000001"},
    {"10000000000000000000000000000000000000000000000001"},
    {"10000000000000000000000000000000000000000000000001"},
    {"10000000000000000000003440000000000000000000000001"},
    {"10000000000000000000000000000000000000000000000001"},
    {"21111111111111111111111111111111111111111111111112"}
};
char map3[25][51] = {
    {"21111111111111111111111111112111111111111111111112"},
    {"10000000000000000000000000000000000000000000000001"},
    {"10000000000000000000000000000000000000000000000001"},
    {"10000000000000000000000000000000000000000000000001"},
    {"10000000000000000000000000000000000000000000000001"},
    {"10000000000000000000000000001000000000000000000001"},
    {"10000000000000000000000000001000000000000000000001"},
    {"10000000000000000000000000001000000000000000000001"},
    {"10000000000000000000000000001000000000000000000001"},
    {"10000000000000000000000000001000000000000000000001"},
    {"10000000000000000000000000001111111111111111111112"},
    {"10000000000000000000000000000000000000000000000001"},
    {"10000000000000000000034400000000000000000000000001"},
    {"10000000000000000000000000000000000000000000000001"},
    {"10000000000000000000000000000000000000000000000001"},
    {"21111111111111111111111000000000000000000000000001"},
    {"10000000000000000000001000000000000000000000000001"},
    {"10000000000000000000001000000000000000000000000001"},
    {"10000000000000000000001000000000000000000000000001"},
    {"10000000000000000000001000000000000000000000000001"},
    {"10000000000000000000001000000000000000000000000001"},
    {"10000000000000000000000000000000000000000000000001"},
    {"10000000000000000000000000000000000000000000000001"},
    {"10000000000000000000000000000000000000000000000001"},
    {"21111111111111111111112111111111111111111111111112"}
};

char map4[26][51] = {
    {"21111111111111111111111111111111111111111111111112"},
    {"10000000000000000000000000000000000000000000000001"},
    {"10000000000000000000000000000000000000000000000001"},
    {"10000000000000000000000000000000000000000000000001"},
    {"10000000000000011000000000000000110000000000000001"},
    {"10000000000000001100034400000001100000000000000001"},
    {"10000000000000000110000000000011000000000000000001"},
    {"10000000000000000011000000000110000000000000000001"},
    {"10000000000000000001100000001100000000000000000001"},
    {"10000000000000000000110000011000000000000000000001"},
    {"10000000000000000000011000110000000000000000000001"},
    {"10000000000000000000001101100000000000000000000001"},
    {"10000000000000000000000111000000000000000000000001"},
    {"10000000000000000000001101100000000000000000000001"},
    {"10000000000000000000011000110000000000000000000001"},
    {"10000000000000000000110000011000000000000000000001"},
    {"10000000000000000001100000001100000000000000000001"},
    {"10000000000000000011000000000110000000000000000001"},
    {"10000000000000000110000000000011000000000000000001"},
    {"10000000000000001100000000000001100000000000000001"},
    {"10000000000000011000000000000000110000000000000001"},
    {"10000000000000000000000000000000000000000000000001"},
    {"10000000000000000000000000000000000000000000000001"},
    {"10000000000000000000000000000000000000000000000001"},
    {"21111111111111111111111111111111111111111111111112"}
};


// map 그리기
void snake::drawMap(int* x, int* y){
    clear();
    int h, w;

    for(h=0; h<26; h++){
        for(w=0; w<51; w++){
            char tmp = tmpMap[h][w];
            if (tmp == '0'){
                printw(" ");
            }
            else if (tmp == '1'){
                attron(COLOR_PAIR(7));
                printw("#");
                attroff(COLOR_PAIR(7));
            }
            else if (tmp == '2'){
                attron(COLOR_PAIR(7));
                printw("*");
                attroff(COLOR_PAIR(7));
            }
            else if (tmp == '3'){
                *x = h;
                *y = w;
                tailX[0] = h;
                tailY[0] = w;
                if (tailX[1] == 0 && tailY[1] == 0){
                    tailX[1] = h;
                    tailY[1] = w+1;
                    tailX[2] = h;
                    tailY[2] = w+2;
                }
                printw("O");
            }

            else if (tmp == '4'){
                printw("o");
            }
            else if (tmp == '5'){
                attron(COLOR_PAIR(5));
                printw("+");
                attroff(COLOR_PAIR(5));
            }
            else if (tmp == '6'){
                attron(COLOR_PAIR(4));
                printw("-");
                attroff(COLOR_PAIR(4));
            }
            else if (tmp == '7'){
                attron(COLOR_PAIR(2));
                printw("G");
                attroff(COLOR_PAIR(2));
            }
        }
        printw("\n");
    }

}

// growthItem 생성
void snake::growthItem(){

    if (growthItemTime >= 100){

        growthItemTime = 0;
        // item 제거
        if (tmpMap[growthItemX][growthItemY] == '3' || tmpMap[growthItemX][growthItemY] == '4'){}
        else if (!(growthItemX==0 && growthItemY==0)){
            tmpMap[growthItemX][growthItemY] = '0';
        }
        while (1){
            growthItemX = rand()%21+2;
            growthItemY = rand()%46+2;
            if (tmpMap[growthItemX][growthItemY] == '0'){
                break;
            }
        }
        tmpMap[growthItemX][growthItemY] = '5';
    }
    else{
        growthItemTime++;
    }
}

// poisonItem 생성
void snake::poisonItem(){

    if (poisonItemTime >= 80){

        poisonItemTime = 0;
        //item 제거
        if (tmpMap[poisonItemX][poisonItemY] == '3' || tmpMap[poisonItemX][poisonItemY] == '4'){}
        else if (!(poisonItemX==0 && poisonItemY==0)){
            tmpMap[poisonItemX][poisonItemY] = '0';
        }

        while (1){
            poisonItemX = rand()%21+2;
            poisonItemY = rand()%46+2;
            if (tmpMap[poisonItemX][poisonItemY] == '0'){
                break;
            }
        }
        tmpMap[poisonItemX][poisonItemY] = '6';
    }
    else{
        poisonItemTime++;
    }
}

// 게이트 생성
void snake::openGate(){
    if (gateTime >= 120){
        if (!(gateX1==0 && gateY1==0)){
            tmpMap[gateX1][gateY1] = '1';
        }
        if (!(gateX2==0 && gateY2==0)){
            tmpMap[gateX2][gateY2] = '1';
        }
        while (1){
            gateX1 = rand()%25;
            gateY1 = rand()%50;
            if (tmpMap[gateX1][gateY1] == '1'){
                break;
            }
        }
        while (1){
            gateX2 = rand()%25;
            gateY2 = rand()%50;
            if (tmpMap[gateX2][gateY2] == '1' && (gateX2 != gateX1 || gateY2 != gateY1)){
                break;
            }
        }
        tmpMap[gateX2][gateY2] = '7';
        tmpMap[gateX1][gateY1] = '7';
        gateTime = 0; 
    }
    else{
        gateTime++;
    }
}


int snake::getScore() {
        return maxLength*10 + gItemCnt*5 - pItemCnt*3 + passGateCnt*20 + currentLength;
}

bool snake::missionCheck(){

    if (gItemCnt >= missonGItem && passGateCnt >= missonPassGate && maxLength >= missionMaxLength){
        return true;
    }
    return false;
    
}

// 점수판
void snake::scoreBoard(){
    
    mvprintw(0, 60, "*************************");
    mvprintw(1, 60, "*------SCORE BOARD------*");
    mvprintw(2, 60, "*  Score : %d           *", snake::getScore());
    mvprintw(3, 60, "*  B (+10pts) : %d / %d   *", currentLength, maxLength);
    mvprintw(4, 60, "*  + (+5pts) : %d        *", gItemCnt);
    mvprintw(5, 60, "*  - (-3pts) : %d        *", pItemCnt);
    mvprintw(6, 60, "*  G (+20pts) : %d       *", passGateCnt);
    mvprintw(7, 60, "*************************");

    mvprintw(10, 60, "*************************");
    mvprintw(11, 60, "*-----MISSION BOARD-----*");
    mvprintw(12, 60, "*  B : %d                *", missionMaxLength);
    mvprintw(13, 60, "*  + : %d                *", missonGItem);
    mvprintw(14, 60, "*  - : %d                *", goalPItem);
    mvprintw(15, 60, "*  G : %d                *", missonPassGate);
    mvprintw(16, 60, "*************************");

    if (maxLength >= missionMaxLength){
        mvprintw(12, 82, "V");
    }
    if (gItemCnt >= missonGItem){
        mvprintw(13, 82, "V");
    }
    if (passGateCnt >= missonPassGate){
        mvprintw(15, 82, "V");
    }
    if (pItemCnt < goalPItem){
        mvprintw(14, 82, "V");
    }
    refresh();
}

// 스테이지 클리어
void snake::stageClear(){
    clear();
    printw("\n\n\n\n\n\n");
    
    attron(COLOR_PAIR(8));
    printw("                          Congratulation!\n\n");
    attroff(COLOR_PAIR(8));
    printw("                        YOU CLEARED THIS STAGE\n\n");
    printw("                         You Got %d Score \n\n\n\n", getScore());
    printw("                      Press Any Key to Continue");
    refresh();
    getch();

}
// gameLoop
void snake::gLoop(int mapCode){
    int x, y;
    nodelay(stdscr, true);
    gItemCnt = 0;
    pItemCnt = 0;
    passGateCnt = 0;
    maxLength = 3;
    currentLength = 3;
    growthItemTime=100;
    poisonItemTime=65;
    gateTime = 120;
    growthItemX = 0;
    growthItemY = 0;
    poisonItemX = 0;
    poisonItemY = 0;
    gateX1 = 0;
    gateY1 = 0;
    gateX2 = 0;
    gateY2 = 0;
    nTail=2;
    _x = 0;
    _y = -1;
    tailX[1] = 0;
    tailY[1] = 0;
    gameOver = false;
    missonGItem = rand()%4+1;
    goalPItem = rand()%4+1;
    missonPassGate = rand()%3+1;
    missionMaxLength = rand()%3+4;

    // mapCode에 맞는 map을 tmpMap에 복사
    if(mapCode == 0){
        memcpy(tmpMap, map1, sizeof(tmpMap));
    }
    else if(mapCode == 1){
        memcpy(tmpMap, map2, sizeof(tmpMap));
    }
    else if(mapCode == 2){
        memcpy(tmpMap, map3, sizeof(tmpMap));
    }
    else if(mapCode == 3){
        memcpy(tmpMap, map4, sizeof(tmpMap));
    }
    while(!(gameOver || missionCheck())){
        drawMap(&x, &y);
        scoreBoard();
        move(&x, &y);
        growthItem();
        poisonItem();
        usleep(200000);
        openGate();

    }
    // gameOver 시 실행
    if (gameOver){
        nodelay(stdscr, false);
        int menuCode = drawFail();
        if (menuCode == 0){
            snake::gLoop(mapCode);
        }
        else if (menuCode == 2){
            endwin();
        }

    }
    // mission clear 시 실행
    if (missionCheck()){
        
        nodelay(stdscr, false);
        // 다음 스테이지
        if (mapCode < 3){
            stageClear();
            snake::gLoop(mapCode+1);
        }
        // 클리어
        else{
            drawVictory();
        }

    }

}

void snake::move(int* x, int* y){
    // snake body 이동
    tmpMap[tailX[nTail]][tailY[nTail]] = '0';
    for (int i=nTail; i>0; i--){
        tailX[i] = tailX[i-1];
        tailY[i] = tailY[i-1];
        tmpMap[tailX[i]][tailY[i]] = '4';
    }

    int tmp = getch();

    switch(tmp){
        case KEY_UP:
            _x = -1;
            _y = 0;
            break;
        case KEY_DOWN:
            _x = 1;
            _y = 0;
            break;
        case KEY_RIGHT:
            _x = 0;
            _y = 1;
            break;
        case KEY_LEFT:
            _x = 0;
            _y = -1;
            break;
    }

    *x += _x;
    *y += _y;

    char mapObject = tmpMap[*x][*y];

    //충돌부분, snake의 헤드가 1(벽)에 닿거나 4(몸통)에 닿으면 게임종료
    //진행방향과 역방향 입력받으면 종료시키는 부분도 inx[0]헤드가 inx[1]몸통과 만나기때문에 게임종료됨
    if (mapObject == '1' || mapObject == '4'){
        gameOver = true;
    }

    // gate1 in -> gate2 out
    if (*x == gateX1 && *y == gateY1){
        passGateCnt++;
        if ((120-gateTime) < nTail){
            gateTime = 119 -nTail;
        };
        if (tmpMap[gateX2+_x][gateY2+_y] == '0'){
            *x = gateX2+_x;
            *y = gateY2+_y;

        }
        else if (tmpMap[gateX2][gateY2-1] == '0'){
            _x = 0;
            _y = -1;
            *x = gateX2;
            *y = gateY2-1;
        }
        else if (tmpMap[gateX2-1][gateY2] == '0'){
            _x = -1;
            _y = 0;
            *x = gateX2-1;
            *y = gateY2;
        }
        else if (tmpMap[gateX2][gateY2+1] == '0'){
            _x = 0;
            _y = 1;
            *x = gateX2;
            *y = gateY2+1;
        }
        else if (tmpMap[gateX2+1][gateY2] == '0'){
            _x = +1;
            _y = 0;
            *x = gateX2+1;
            *y = gateY2;
        }
    }
    // gate2 in -> gate1 out
    if (*x == gateX2 && *y == gateY2){
        passGateCnt++;
        if ((120-gateTime) < nTail){
            gateTime = 119 -nTail;
        };
        if (tmpMap[gateX1+_x][gateY1+_y] == '0'){
            *x = gateX1+_x;
            *y = gateY1+_y;

        }
        else if (tmpMap[gateX1][gateY1-1] == '0'){
            _x = 0;
            _y = -1;
            *x = gateX1;
            *y = gateY1-1;
        }
        else if (tmpMap[gateX1-1][gateY1] == '0'){
            _x = -1;
            _y = 0;
            *x = gateX1-1;
            *y = gateY1;
        }
        else if (tmpMap[gateX1][gateY1+1] == '0'){
            _x = 0;
            _y = 1;
            *x = gateX1;
            *y = gateY1+1;
        }
        else if (tmpMap[gateX1+1][gateY1] == '0'){
            _x = 1;
            _y = 0;
            *x = gateX1+1;
            *y = gateY1;
        }

    }

    // get growthItem
    if (mapObject == '5'){
        gItemCnt++;
        growthItemTime = 100;
        nTail++;
        if (nTail+1 > maxLength){
            maxLength = nTail+1;
        }
        currentLength = nTail+1;
        tailX[nTail] = *x-_x;
        tailY[nTail] = *y-_y;
        tmpMap[tailX[nTail]][tailY[nTail]] = '4';
    }
    // get poisonItem
    if (mapObject == '6'){
        pItemCnt++;
        tmpMap[tailX[nTail]][tailY[nTail]] = '0';
        poisonItemTime = 80;
        nTail--;
        currentLength--;
        if (nTail <=1){
            gameOver = true;
        }
    }

    // head 이동
    tmpMap[*x][*y] = '3';



}


#endif