#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<mmsystem.h>
#include<time.h>
#include "console_draw3.h"
#include "kb_input2.h"
#include "image.h"
#include "font.h"
#include "audio.h"
#include "opening.h"
#define NUM_KEYS 3
#define num_words 12
#define HP_1 10
#define HP_2 10
#define HP_3 25
#define main_HP 5

int count1= HP_1;
int count2= HP_2;
int count3= HP_3;
int mainHP = main_HP;

int row_ch = 20;
int col_ch = 80;

int row_ch2 = 20;
int col_ch2 = 90;

int blood_row = 0;
int blood_col = 5;
int record_attack_1 = 0;
int record_attack_2 = 0;
int record_attack_3 = 0;
//void marshroom_attack(void);
//void attack_normal(void);
char dic[num_words][30];

void part_1(void)
{
    Audio arrow;
    openAudioFile("arrow.wav",&arrow);
    playAudio(&arrow);
    Font *large_font=read_font("font.txt");
    Image *ch2 = read_image("ch.pixel","ch.color");
    //Image *mon10 = read_image("mon10.pixel","mon10.color");
    Image *marshroom = read_image("marshroom.pixel","marshroom.color");
    Image *background = read_image("arrow.pixel","arrow.color");
    Image *blood = read_image("blood.pixel","blood.color");
    Image *main_blood = read_image("main_blood.pixel","main_blood.color");
    show_image(ch2,row_ch,col_ch);
    show_image(marshroom,200,71);
    show_image(background,0,0);
    show_image(blood,blood_row-(250/HP_1)*(HP_1 - count1),blood_col);
    show_image(main_blood,0-10*(5-mainHP),141);
    //saveScreen();
    drawCmdWindow();

    Audio laugh;
    openAudioFile("laugh.wav",&laugh);
    FILE *fp;
    char str[2]={0};
    int nw, i, j=0, k=0, o;
    /*
        if((fp=fopen("text.txt", "r"))==NULL){
        printf("Cannot!");
        exit(1);
    }*/
    fp=fopen("text_A&B.txt", "r");
    nw=0;
    while(!feof(fp)&&nw<num_words){
        fscanf(fp,"%s", dic[nw]);
        while(!feof(fp)&&fgetc(fp)!='\n');
        nw++;
    }
    /*
    for(i=0;i<num_words;i++){
        for(o=0;o<strlen(dic[i]);o++){
            if(dic[i][o]=='1') dic[i][o] = '¡ô';
            else if(dic[i][o]=='2') dic[i][o] = '¡÷';
            else if(dic[i][o]=='3') dic[i][o] = '¡õ';
            else if(dic[i][o]=='4') dic[i][o] = '¡ö';
        }
    }
    */
    fclose(fp);
    srand(time(NULL));
    int key_down[NUM_KEYS] = {0};
    /*
    int key_val[NUM_KEYS] = {VK_A, VK_B, VK_C, VK_D, VK_E, VK_F, VK_G, VK_H, VK_I, VK_J, VK_K,
    VK_L, VK_M, VK_N, VK_O, VK_P, VK_Q, VK_R, VK_S, VK_T, VK_U, VK_V, VK_W, VK_X, VK_Y, VK_Z, VK_SPACE};
    */
    int key_val[NUM_KEYS] = {VK_A, VK_B, VK_CONTROL};

    /*
    Audio test;
    openAudioFile("test_music.wav",&test);
    */

    while(1){
        i = rand()%num_words;
        int len = strlen(dic[i]);
        while(k < len){
            for (o = 0 ; o < NUM_KEYS ; o++)
            {
                putStringLarge(large_font, 90, 141, dic[i], 15);
                show_image(background,0,0);
                show_image(ch2,row_ch,col_ch);
                show_image(marshroom,200,71);
                show_image(blood,blood_row-(250/HP_1)*(HP_1 - count1),blood_col);
                show_image(main_blood,0-10*(5-mainHP),141);
                drawCmdWindow();

                if(KEY_DOWN(key_val[o]) && !key_down[o])

                {
                    key_down[o] = 1;
                    if(key_val[o]-VK_A+'A'==dic[i][k]){
                        str[0] = key_val[o]-VK_A+'A';
                        putStringLarge(large_font, 90+j, 148, str, 15);
                        j = j + 8;
                        k++;
                        Sleep(100);
                    }

                    else if(key_val[o]==VK_CONTROL){
                        attack_normal();
                        clearScreen();
                        k=0;
                        j=0;
                        if(count1<=0)   {
                                k = len;
                                record_attack_1 = 1;
                        }
                    }
                    else{
                        mainHP--;
                        //marshroom_attack();
                        if(mainHP!=0){
                            restartAudio(&laugh);
                            putStringLarge(large_font, 80, 155, "IDOIT", 4);
                            putStringLarge(large_font, 80, 162, "T R Y   A G A I N", 4);
                            playAudio(&laugh);
                        }
                        else {
                            pauseAudio(&laugh);
                            marshroom_attack();
                            Sleep(1500);
                            putStringLarge(large_font, 0, 141,"NO  BLOOD", 4);
                            drawCmdWindow();
                            putStringLarge(large_font,120,70,"You Lose",15);
                            putStringLarge(large_font,80,160,"HOW ABOUT GO HOME EAT PUDDING",15);
                            drawCmdWindow();
                            Sleep(3000);
                            while(waitForKeyDown(0.1)){
                                destroy_image(ch2);
                                destroy_image(marshroom);
                                destroy_image(background);
                                destroy_image(blood);
                                destroy_image(main_blood);
                                ending();
                            }
                        }
                        drawCmdWindow();
                        Sleep(500);
                        clearScreen();
                        k=0;
                        j=0;
                    }

                }
                if(KEY_UP(key_val[o]) && key_down[o])
                {
                    key_down[o] = 0;
                }
            }
        }
        /*clearScreen();
        putStringLarge(large_font, 90, 155, "A T T A C K        ", 12);
        show_image(background,0,0);
        show_image(ch2,row_ch,col_ch);
        show_image(marshroom,180,71);
        show_image(blood,blood_row-(250/HP_1)*(HP_1 - count1),blood_col);
        show_image(main_blood,0-10*(5-mainHP),141);
        drawCmdWindow();*/
        pauseAudio(&laugh);
        if(len==3&&record_attack_1!=1){
            special_1();
            count1 -= 6;
            clearScreen();
            show_image(background,0,0);
            show_image(ch2,row_ch,col_ch);
            show_image(marshroom,200,71);
            show_image(blood,blood_row-(250/HP_1)*(HP_1 - count1),blood_col);
            show_image(main_blood,0-10*(5-mainHP),141);
            if(count1<=0)   putStringLarge(large_font,120,70,"You Win",15);
            drawCmdWindow();
        }
        else if(len==5&&record_attack_1!=1){
            special_2();
            count1 -= 3;
            clearScreen();
            show_image(background,0,0);
            show_image(ch2,row_ch,col_ch);
            show_image(marshroom,200,71);
            show_image(blood,blood_row-(250/HP_1)*(HP_1 - count1),blood_col);
            show_image(main_blood,0-10*(5-mainHP),141);
            if(count1<=0)   putStringLarge(large_font,120,70,"You Win",15);
            drawCmdWindow();
        }
        else if(len==11&&record_attack_1!=1){
            special_3();
            count1 -= 9;
            clearScreen();
            show_image(background,0,0);
            show_image(ch2,row_ch,col_ch);
            show_image(marshroom,200,71);
            show_image(blood,blood_row-(250/HP_1)*(HP_1 - count1),blood_col);
            show_image(main_blood,0-10*(5-mainHP),141);
            if(count1<=0)   putStringLarge(large_font,120,70,"You Win",15);
            drawCmdWindow();
        }
        Sleep(500);
        clearScreen();
        i=0;
        k=0;
        j=0;
        if(count1<=0 || record_attack_1){
            destroy_image(ch2);
            destroy_image(marshroom);
            destroy_image(background);
            destroy_image(blood);
            destroy_image(main_blood);
            pauseAudio(&arrow);
            break;
        }


    }
    return;
}



void attack_normal(void)
{
    int r = 20;
    int c = 55;

    Font *large_font=read_font("font.txt");
    Image *ch2 = read_image("ch.pixel","ch.color");
    Image *chattack = read_image("sun.pixel","sun.color");
    //Image *mon10 = read_image("mon10.pixel","mon10.color");
    Image *marshroom = read_image("marshroom.pixel","marshroom.color");
    Image *background = read_image("arrow.pixel","arrow.color");
    Image *blood = read_image("blood.pixel","blood.color");
    Image *main_blood = read_image("main_blood.pixel","main_blood.color");

            while(r<=180)
            {

                show_image(chattack,r,80);
                show_image(chattack,c,90);
                drawCmdWindow();
                r+=30;
                c+=30;
                Sleep(20);
                clearScreen();
                show_image(background,0,0);
                show_image(ch2,row_ch,col_ch);
                show_image(marshroom,200,71);
                show_image(blood,blood_row-(250/HP_1)*(HP_1 - count1),blood_col);
                show_image(main_blood,0-10*(5-mainHP),141);
                drawCmdWindow();
                if (c>=180)
                {
                    count1--;
                    clearScreen();

                    show_image(background,0,0);
                    show_image(ch2,row_ch,col_ch);
                    show_image(marshroom,180,71);
                    show_image(blood,blood_row-(250/HP_1)*(HP_1 - count1),blood_col);
                    show_image(main_blood,0-10*(5-mainHP),141);
                    putStringLarge(large_font,90,30,"87531",14);
                    drawCmdWindow();
                }
                if (count1<=0)
                {
                    putStringLarge(large_font,120,70,"You Win",15);
                    drawCmdWindow();
                    Sleep(500);
                    destroy_image(chattack);
                    clearScreen();
                    break;
                }
            }
    destroy_image(ch2);
    destroy_image(marshroom);
    destroy_image(background);
    destroy_image(blood);
    destroy_image(main_blood);
}
void marshroom_attack(void) //未完成
{
    Image *ch2 = read_image("ch.pixel","ch.color");
    //Image *mon10 = read_image("mon10.pixel","mon10.color");
    Image *marshroom2 = read_image("marshroom_attack.pixel","marshroom_attack.color");
    Image *background = read_image("arrow.pixel","arrow.color");
    Image *main_blood = read_image("main_blood.pixel","main_blood.color");

    int row_marshroom = 180;
    int col_marshroom = 71;
    int i;
    for(i=0;i<5;i++){
        clearScreen();
        show_image(background,0,0);
        show_image(ch2,row_ch,col_ch);
        show_image(marshroom2,row_marshroom,col_marshroom-10);
        show_image(main_blood,-40,141);
        col_marshroom -= 10;
        drawCmdWindow();
        Sleep(100);
    }
    for(i=0;i<5;i++){
        clearScreen();
        show_image(background,0,0);
        show_image(ch2,row_ch,col_ch);
        show_image(marshroom2,row_marshroom,col_marshroom+10);
        show_image(main_blood,-40,141);
        col_marshroom += 10;
        drawCmdWindow();
        Sleep(100);
    }
    for(i=0;i<10;i++){
        clearScreen();
        show_image(background,0,0);
        show_image(ch2,row_ch,col_ch-i*10);
        show_image(marshroom2,row_marshroom,col_marshroom);
        show_image(main_blood,-50,141);
        col_ch -= 10;
        drawCmdWindow();
        Sleep(30);
    }


    return;
}

//part 2:
void part_2(void)
{
	mainHP = main_HP;
    clearScreen();

    Audio zei_music;
    openAudioFile("zei_music.wav",&zei_music);
    playAudio(&zei_music);

    Font *large_font=read_font("font.txt");
    Image *ch2 = read_image("ch.pixel","ch.color");
    //Image *mon10 = read_image("mon10.pixel","mon10.color");
    Image *zei = read_image("zei.pixel","zei.color");
    Image *background_fire = read_image("background_fire.pixel","background_fire.color");
    Image *blood = read_image("blood.pixel","blood.color");
    Image *main_blood = read_image("main_blood.pixel","main_blood.color");
    show_image(ch2,row_ch2,col_ch2);
    show_image(zei,210,60);
    show_image(background_fire,0,0);
    show_image(blood,blood_row-(250/HP_2)*(HP_2 - count2),blood_col);
    show_image(main_blood,0-10*(5-mainHP),141);
    //saveScreen();
    drawCmdWindow();

    Audio laugh;
    openAudioFile("laugh.wav",&laugh);
    FILE *fp;
    char str[2]={0};
    int nw, i, j=0, k=0, o;
    /*
        if((fp=fopen("text.txt", "r"))==NULL){
        printf("Cannot!");
        exit(1);
    }*/
    fp=fopen("text_A&B.txt", "r");
    nw=0;
    while(!feof(fp)&&nw<num_words){
        fscanf(fp,"%s", dic[nw]);
        while(!feof(fp)&&fgetc(fp)!='\n');
        nw++;
    }
    fclose(fp);
    srand(time(NULL));
    int key_down[NUM_KEYS] = {0};
    /*
    int key_val[NUM_KEYS] = {VK_A, VK_B, VK_C, VK_D, VK_E, VK_F, VK_G, VK_H, VK_I, VK_J, VK_K,
    VK_L, VK_M, VK_N, VK_O, VK_P, VK_Q, VK_R, VK_S, VK_T, VK_U, VK_V, VK_W, VK_X, VK_Y, VK_Z, VK_SPACE};
    */
    int key_val[NUM_KEYS] = {VK_A, VK_B, VK_CONTROL};

    while(1){
        i = rand()%num_words;
        int len = strlen(dic[i]);
        while(k < len){
            for (o = 0 ; o < NUM_KEYS ; o++)
            {
                putStringLarge(large_font, 90, 141, dic[i], 15);
                show_image(background_fire,0,0);
                show_image(ch2,row_ch2,col_ch2);
                show_image(zei,210,60);
                show_image(blood,blood_row-(250/HP_2)*(HP_2 - count2),blood_col);
                show_image(main_blood,0-10*(5-mainHP),141);
                //restoreScreen();
                drawCmdWindow();
                if(KEY_DOWN(key_val[o]) && !key_down[o])

                {
                    key_down[o] = 1;
                    if(key_val[o]-VK_A+'A'==dic[i][k]){
                        str[0] = key_val[o]-VK_A+'A';
                        putStringLarge(large_font, 90+j, 148, str, 15);
                        j = j + 8;
                        k++;
                        Sleep(100);
                    }

                    else if(key_val[o]==VK_CONTROL){
                        attack_normal_2();
                        clearScreen();
                        k=0;
                        j=0;
                        if(count2<=0)   {
                                k = len;
                                record_attack_2 = 1;
                        }
                    }
                    else{
                        mainHP--;
                        if(mainHP!=0){
                            restartAudio(&laugh);
                            putStringLarge(large_font, 80, 155, "IDOIT", 4);
                            putStringLarge(large_font, 80, 162, "T R Y   A G A I N", 4);
                            playAudio(&laugh);
                        }
                        else {
                            pauseAudio(&laugh);
                            zei_attack();
                            Sleep(1500);
                            putStringLarge(large_font, 0, 141,"NO  BLOOD", 4);
                            drawCmdWindow();
                            putStringLarge(large_font,120,70,"You Lose",15);
                            putStringLarge(large_font,80,160,"HOW ABOUT GO HOME EAT PUDDING",15);
                            drawCmdWindow();
                            Sleep(3000);
                            while(waitForKeyDown(0.1)){
                                destroy_image(ch2);
                                destroy_image(zei);
                                destroy_image(background_fire);
                                destroy_image(blood);
                                destroy_image(main_blood);
                                ending();
                            }
                        }
                        drawCmdWindow();
                        Sleep(500);
                        clearScreen();
                        k=0;
                        j=0;
                    }

                }
                if(KEY_UP(key_val[o]) && key_down[o])
                {
                    key_down[o] = 0;
                }
            }
        }

        /*clearScreen();
        putStringLarge(large_font, 90, 155, "A T T A C K        ", 12);
        show_image(background_fire,0,0);
        show_image(ch2,row_ch2,col_ch2);
        show_image(zei,210,60);
        show_image(blood,blood_row-(250/HP_2)*(HP_2 - count2),blood_col);
        show_image(main_blood,0-10*(5-mainHP),141);
        drawCmdWindow();*/
        pauseAudio(&laugh);

        if(len==3&&record_attack_2!=1){
            special_1();
            count2 -= 6;
            clearScreen();
            show_image(background_fire,0,0);
            show_image(ch2,row_ch2,col_ch2);
            show_image(zei,210,60);
            show_image(blood,blood_row-(250/HP_2)*(HP_2 - count2),blood_col);
            show_image(main_blood,0-10*(5-mainHP),141);
            if(count2<=0)   putStringLarge(large_font,120,70,"You Win",15);
            drawCmdWindow();
        }
        else if(len==5&&record_attack_2!=1){
            special_2();
            count2 -= 3;
            clearScreen();
            show_image(background_fire,0,0);
            show_image(ch2,row_ch2,col_ch2);
            show_image(zei,210,60);
            show_image(blood,blood_row-(250/HP_2)*(HP_2 - count2),blood_col);
            show_image(main_blood,0-10*(5-mainHP),141);
            if(count2<=0)   putStringLarge(large_font,120,70,"You Win",15);
            drawCmdWindow();
        }
        else if(len==11&&record_attack_2!=1){
            special_3();
            count2 -= 9;
            clearScreen();
            show_image(background_fire,0,0);
            show_image(ch2,row_ch2,col_ch2);
            show_image(zei,210,60);
            show_image(blood,blood_row-(250/HP_2)*(HP_2 - count2),blood_col);
            show_image(main_blood,0-10*(5-mainHP),141);
            if(count2<=0)   putStringLarge(large_font,120,70,"You Win",15);
            drawCmdWindow();
        }
        else {clearScreen();
        show_image(background_fire,0,0);
        show_image(ch2,row_ch2,col_ch2);
        show_image(zei,210,60);
        show_image(blood,blood_row-(250/HP_2)*(HP_2 - count2),blood_col);
        show_image(main_blood,0-10*(5-mainHP),141);
        drawCmdWindow();
        }
        Sleep(500);
        clearScreen();
        i=0;
        k=0;
        j=0;
        if(count2<=0 || record_attack_2)   {
            destroy_image(ch2);
            destroy_image(zei);
            destroy_image(background_fire);
            destroy_image(blood);
            destroy_image(main_blood);
            pauseAudio(&zei_music);
            break;
        }
    }
    return;
}

void zei_attack(void)
{
	int i;
    clearScreen();
    Image *background = read_image("background_fire.pixel","background_fire.color");
    Image *boss2 = read_image("zei_attack.pixel","zei_attack.color");
    Image *fire = read_image("fire.pixel","fire.color");
    Image *ch2 = read_image("ch.pixel","ch.color");
    Image *main_blood = read_image("main_blood.pixel","main_blood.color");
    show_image(background,0,0);
    show_image(boss2,210,60);
    show_image(ch2,row_ch2,col_ch2);
    show_image(main_blood,-40,141);
    for(i=200;i>=0;i-=50){
        show_image(fire,i,60);
        drawCmdWindow();
        Sleep(500);
    }
    return ;
}
void attack_normal_2(void)
{
    int r = 20;
    int c = 55;

    Font *large_font=read_font("font.txt");
    Image *ch2 = read_image("ch.pixel","ch.color");
    Image *chattack = read_image("sun.pixel","sun.color");
    //Image *mon10 = read_image("mon10.pixel","mon10.color");
    Image *zei = read_image("zei.pixel","zei.color");
    Image *background = read_image("background_fire.pixel","background_fire.color");
    Image *blood = read_image("blood.pixel","blood.color");
    Image *main_blood = read_image("main_blood.pixel","main_blood.color");

            while(r<=180)
            {

                show_image(chattack,r,90);
                show_image(chattack,c,100);
                drawCmdWindow();
                r+=30;
                c+=30;
                Sleep(20);
                clearScreen();
                show_image(background,0,0);
                show_image(ch2,row_ch2,col_ch2);
                show_image(zei,210,60);
                show_image(blood,blood_row-(250/HP_2)*(HP_2 - count2),blood_col);
                show_image(main_blood,0-10*(5-mainHP),141);
                drawCmdWindow();
                if (c>=180)
                {
                    count2--;
                    clearScreen();

                    show_image(background,0,0);
                    show_image(ch2,row_ch2,col_ch2);
                    show_image(zei,210,60);
                    show_image(blood,blood_row-(250/HP_2)*(HP_2 - count2),blood_col);
                    show_image(main_blood,0-10*(5-mainHP),141);
                    putStringLarge(large_font,90,30,"87531",14);
                    drawCmdWindow();
                }
                if (count2<=0)
                {
                    putStringLarge(large_font,120,70,"You Win",15);
                    drawCmdWindow();
                    Sleep(500);
                    destroy_image(chattack);
                    clearScreen();
                    break;
                }
            }
    destroy_image(ch2);
    destroy_image(zei);
    destroy_image(background);
    destroy_image(blood);
    destroy_image(main_blood);
}
void part_3(void)
{
	mainHP = main_HP;
    Audio dark;
    openAudioFile("dark.wav",&dark);
    playAudio(&dark);

    Font *large_font=read_font("font.txt");
    Image *ch2 = read_image("ch.pixel","ch.color");
    //Image *mon10 = read_image("mon10.pixel","mon10.color");
    Image *mon10 = read_image("mon10.pixel","mon10.color");
    Image *background = read_image("background.pixel","background.color");
    Image *blood = read_image("blood.pixel","blood.color");
    Image *main_blood = read_image("main_blood.pixel","main_blood.color");
    show_image(ch2,row_ch,col_ch-5);
    show_image(mon10,190,10);
    show_image(background,0,0);
    show_image(blood,blood_row-(250/HP_2)*(HP_2 - count2),blood_col);
    show_image(main_blood,0-10*(5-mainHP),141);
    drawCmdWindow();

    Audio laugh;
    openAudioFile("laugh.wav",&laugh);
    FILE *fp;
    char str[2]={0};
    int nw, i, j=0, k=0, o;
    fp=fopen("text_A&B.txt", "r");
    nw=0;
    while(!feof(fp)&&nw<num_words){
        fscanf(fp,"%s", dic[nw]);
        while(!feof(fp)&&fgetc(fp)!='\n');
        nw++;
    }
    fclose(fp);
    srand(time(NULL));
    int key_down[NUM_KEYS] = {0};
    int key_val[NUM_KEYS] = {VK_A, VK_B, VK_CONTROL};

    while(1){
        i = rand()%num_words;
        int len = strlen(dic[i]);
        while(k < len){
            for (o = 0 ; o < NUM_KEYS ; o++)
            {
                putStringLarge(large_font, 90, 141, dic[i], 15);
                show_image(background,0,0);
                show_image(ch2,row_ch,col_ch-5);
                show_image(mon10,190,10);
                show_image(blood,blood_row-(250/HP_3)*(HP_3 - count3),blood_col);
                show_image(main_blood,0-10*(5-mainHP),141);
                //restoreScreen();
                drawCmdWindow();
                if(KEY_DOWN(key_val[o]) && !key_down[o])

                {
                    key_down[o] = 1;
                    if(key_val[o]-VK_A+'A'==dic[i][k]){
                        str[0] = key_val[o]-VK_A+'A';
                        putStringLarge(large_font, 90+j, 148, str, 15);
                        j = j + 8;
                        k++;
                        Sleep(100);
                    }

                    else if(key_val[o]==VK_CONTROL){
                        attack_normal_3();
                        clearScreen();
                        k=0;
                        j=0;
                        if(count3<=0)   {
                                k = len;
                                record_attack_3 = 1;
                        }
                    }
                    else{
                        mainHP--;
                        if(mainHP!=0){
                            restartAudio(&laugh);
                            putStringLarge(large_font, 80, 155, "IDOIT", 4);
                            putStringLarge(large_font, 80, 162, "T R Y   A G A I N", 4);
                            playAudio(&laugh);
                        }
                        else {
                            pauseAudio(&laugh);
                            mon10_attack();
                            Sleep(1500);
                            putStringLarge(large_font, 0, 141,"NO  BLOOD", 4);
                            drawCmdWindow();
                            putStringLarge(large_font,120,70,"You Lose",15);
                            putStringLarge(large_font,80,160,"HOW ABOUT GO HOME EAT PUDDING",15);
                            drawCmdWindow();
                            Sleep(3000);
                            while(waitForKeyDown(0.1)){
                                destroy_image(ch2);
                                destroy_image(mon10);
                                destroy_image(background);
                                destroy_image(blood);
                                destroy_image(main_blood);
                                ending();
                            }
                        }
                        drawCmdWindow();
                        Sleep(500);
                        clearScreen();
                        k=0;
                        j=0;
                    }

                }
                if(KEY_UP(key_val[o]) && key_down[o])
                {
                    key_down[o] = 0;
                }
            }
        }
        /*
        clearScreen();
        putStringLarge(large_font, 90, 155, "A T T A C K        ", 12);
        show_image(background,0,0);
        show_image(ch2,row_ch,col_ch);
        show_image(mon10,180,95);
        show_image(blood,blood_row-(250/HP_3)*(HP_3 - count3),blood_col);
        show_image(main_blood,0-10*(5-mainHP),141);
        drawCmdWindow();*/
        pauseAudio(&laugh);

        if(len==3&&record_attack_3!=1){
            special_1();
            count3 -= 6;
            clearScreen();
            show_image(background,0,0);
            show_image(ch2,row_ch,col_ch-5);
            show_image(mon10,190,10);
            show_image(blood,blood_row-(250/HP_3)*(HP_3 - count3),blood_col);
            show_image(main_blood,0-10*(5-mainHP),141);
            if(count3<=0)   putStringLarge(large_font,120,70,"You Win",15);
            drawCmdWindow();
        }
        else if(len==5&&record_attack_3!=1){
            special_2();
            count3 -= 3;
            clearScreen();
            show_image(background,0,0);
            show_image(ch2,row_ch,col_ch-5);
            show_image(mon10,190,10);
            show_image(blood,blood_row-(250/HP_3)*(HP_3 - count3),blood_col);
            show_image(main_blood,0-10*(5-mainHP),141);
            if(count3<=0)   putStringLarge(large_font,120,70,"You Win",15);
            drawCmdWindow();
        }
        else if(len==11&&record_attack_3!=1){
            special_3();
            count3 -= 9;
            clearScreen();
            show_image(background,0,0);
            show_image(ch2,row_ch,col_ch-5);
            show_image(mon10,190,10);
            show_image(blood,blood_row-(250/HP_3)*(HP_3 - count3),blood_col);
            show_image(main_blood,0-10*(5-mainHP),141);
            if(count3<=0)   putStringLarge(large_font,120,70,"You Win",15);
            drawCmdWindow();

        }
        else {
        clearScreen();
        show_image(background,0,0);
        show_image(ch2,row_ch,col_ch-5);
        show_image(mon10,190,10);
        show_image(blood,blood_row-(250/HP_3)*(HP_3 - count3),blood_col);
        show_image(main_blood,0-10*(5-mainHP),141);
        drawCmdWindow();
        }
        Sleep(500);
        clearScreen();
        i=0;
        k=0;
        j=0;
        if(count3<=0 || record_attack_3)    {
            pauseAudio(&dark);
            destroy_image(ch2);
            destroy_image(mon10);
            destroy_image(background);
            destroy_image(blood);
            destroy_image(main_blood);
            break;
        }
    }
    return;
}

void mon10_attack(void)
{
	int i;
    clearScreen();
    Image *background = read_image("background.pixel","background.color");
    Image *boss3 = read_image("mon10.pixel","mon10.color");
    Image *ch2 = read_image("ch.pixel","ch.color");
    Image *main_blood = read_image("main_blood.pixel","main_blood.color");
    Image *sky[3];
    sky[0] = read_image("skyangry.pixel","skyangry.color");
    sky[1] = read_image("skyangry1.pixel","skyangry1.color");
    sky[2] = read_image("skyangry2.pixel","skyangry2.color");
    show_image(background,0,0);
    show_image(boss3,210,10);
    show_image(ch2,row_ch,col_ch-5);
    show_image(main_blood,-40,141);
 //   show_image(boss2,205,50);
    for(i=2;i>=0;i--){
        show_image(sky[i],0,0);
        drawCmdWindow();
        if(i==2) Sleep(400);
        Sleep(300);
    }
    return ;
}

void attack_normal_3(void)
{
    int r = 20;
    int c = 55;

    Font *large_font=read_font("font.txt");
    Image *ch2 = read_image("ch.pixel","ch.color");
    Image *chattack = read_image("sun.pixel","sun.color");
    //Image *mon10 = read_image("mon10.pixel","mon10.color");
    Image *mon10 = read_image("mon10.pixel","mon10.color");
    Image *background = read_image("background.pixel","background.color");
    Image *blood = read_image("blood.pixel","blood.color");
    Image *main_blood = read_image("main_blood.pixel","main_blood.color");

            while(r<=180)
            {

                show_image(chattack,r,90);
                show_image(chattack,c,100);
                drawCmdWindow();
                r+=30;
                c+=30;
                Sleep(20);
                clearScreen();
                show_image(background,0,0);
                show_image(ch2,row_ch,col_ch-5);
                show_image(mon10,190,10);
                show_image(blood,blood_row-(250/HP_3)*(HP_3 - count3),blood_col);
                show_image(main_blood,0-10*(5-mainHP),141);
                drawCmdWindow();
                if (c>=180)
                {
                    count3--;
                    clearScreen();

                    show_image(background,0,0);
                    show_image(ch2,row_ch,col_ch-5);
                    show_image(mon10,190,10);
                    show_image(blood,blood_row-(250/HP_3)*(HP_3 - count3),blood_col);
                    show_image(main_blood,0-10*(5-mainHP),141);
                    putStringLarge(large_font,90,30,"87531",14);
                    drawCmdWindow();
                }
                if (count3<=0)
                {
                    putStringLarge(large_font,120,70,"You Win",15);
                    drawCmdWindow();
                    Sleep(500);
                    destroy_image(chattack);
                    clearScreen();
                    break;
                }
            }
    destroy_image(ch2);
    destroy_image(mon10);
    destroy_image(background);
    destroy_image(blood);
    destroy_image(main_blood);
}
void special_1(void)
{
    int i ,j = 0;
    Font *large_font=read_font("font.txt");
    Image *ch = read_image("kill.pixel","kill.color");
    show_image(ch,210,70);
    drawCmdWindow();
    for (i = 0;i<6;i++)
    {
        putStringLarge(large_font,210,34+j,"81000",14);
        j+=6;
    }
    drawCmdWindow();
    Sleep(200);


}
void special_2(void)
{
    int count = 8;
    int i ,j = 0;
    Font *large_font=read_font("font.txt");
    Image *ch = read_image("yell.pixel","yell.color");
    show_image(ch,160,70);
    show_image(ch,160,40);
    drawCmdWindow();
	for (i = 0;i<count;i++)
	{
    	putStringLarge(large_font,160,22+j,"99999",14);
        j+=6;
    }
    drawCmdWindow();
    Sleep(200);
}
void special_3(void)
{
    int count = 10;
    int i ,j = 0;
    Font *large_font=read_font("font.txt");
    Image *ch = read_image("finaltest.pixel","finaltest.color");
    Image *smoke = read_image("smoke.pixel","smoke.color");
    show_image(ch,50,60);
    drawCmdWindow();
    for(i=0;i<9;i++){
        show_image(smoke,60+j,70);
        show_image(smoke,60+j,60);
        show_image(smoke,60+j,50);
        show_image(smoke,60+j,40);
        drawCmdWindow();
        j += 20;
    }
    j=0;
	for (i = 0;i<count;i++)
	{
    	putStringLarge(large_font,145,40+j,"1499999",14);
        j+=6;
    }
    drawCmdWindow();
    Sleep(200);
}
