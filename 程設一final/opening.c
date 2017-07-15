#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>
#include "console_draw3.h"
#include "kb_input2.h"
#include "image.h"
#include "font.h"
#include "audio.h"
#include "opening.h"

void login(void)
{
    int flag;
    Image *maple_login = read_image("maple_login.pixel", "maple_login.color");
    Image *pig = read_image("pig.pixel","pig.color");
    Image *bpig = read_image("bpig.pixel","bpig.color");
    Image *fpig = read_image("fpig.pixel","fpig.color");
    while(1){

        flag = (flag+1)%3;
        if(flag==0){
            clearScreen();
            show_image(maple_login, 0, 0);
            show_image(pig,40,90);
            drawCmdWindow();
            Sleep(200);

        }else if(flag==1){
            clearScreen();
            show_image(maple_login, 0, 0);
            show_image(fpig,70,90);
            drawCmdWindow();
            Sleep(200);
        }else{
            clearScreen();
            show_image(maple_login, 0, 0);
            show_image(bpig,100,90);
            drawCmdWindow();
            Sleep(200);
        }
        if(waitForKeyDown(0.3)){
                break;
            }
    }
    destroy_image(maple_login);
    destroy_image(pig);
    destroy_image(bpig);
    destroy_image(fpig);
    return;
}

void chooseCharacter(int j)
{
    int key_val, loc[3]={105,145,200}, m, T=1, flag=1, i;
    Font *large_font = read_font("font.txt");
    Image *choose = read_image("choose.pixel","choose.color");
    Image *c1 = read_image("c1.pixel","c1.color");
    Image *c2 = read_image("c2.pixel","c2.color");
    Image *c3 = read_image("c3.pixel","c3.color");
    Image *p2 = read_image("p2.pixel","p2.color");
    Image *pig = read_image("pig.pixel","pig.color");
    Image *laugth = read_image("laugh.pixel","laugh.color");
    Image *laugth2 = read_image("joke.pixel","joke.color");
    Image *hans_dia = read_image("hans_dia.pixel","hans_dia.color");
    Image *thief_dia = read_image("thief_dia.pixel","thief_dia.color");
    //choose character
    while(T){
        clearScreen();
        KEY_DOWN(key_val);
        m=getKeyEventVirtual();
        switch(m){
            case VK_LEFT:
                if(j==0) j=2;
                else j--;
                break;
            case VK_RIGHT:
                if(j==2) j=0;
                else j++;
                break;
            case VK_RETURN:
                T=0;
                pauseAudio(&inmu);
                break;
        }
        KEY_UP(key_val);
        flag=(flag+1)%2;
        show_image(choose,0,0);
        show_image(c1,90,55);
        show_image(c2,125,55);
        show_image(c3,175,55);
        putStringLarge(large_font,loc[j],45,"v",14);
        if(flag)putStringLarge(large_font,80,141,"choose your character",15);
        else putStringLarge(large_font,80,141,"choose your character",7);
        drawCmdWindow();
        Sleep(100);
    }

    switch(j){
        case 1:
            clearScreen();
            show_image(laugth,0,0);
            drawCmdWindow();
            Sleep(3000);
            clearScreen();
            putStringLarge(large_font,70,50,"You cannot use this character",14);
            drawCmdWindow();
            Sleep(2000);
            clearScreen();
            putStringLarge(large_font,100,50,"Pay 10000 to unlock LOL",14);
            drawCmdWindow();
            Sleep(2000);
            chooseCharacter(j);
            break;
        case 2:
            clearScreen();
            show_image(laugth2,0,0);
            drawCmdWindow();
            Sleep(3000);
            clearScreen();
            putStringLarge(large_font,70,50,"You cannot use this character",14);
            drawCmdWindow();
            Sleep(2000);
            clearScreen();
            putStringLarge(large_font,100,50,"Pay 10000 to unlock LOL",14);
            drawCmdWindow();
            Sleep(2000);
            chooseCharacter(j);
            break;
        case 0:
            for(i=40;i<=200;i+=20){
                clearScreen();
                putStringLarge(large_font,135,60,"loading",14);
                show_image(p2,i,100);
                show_image(pig,i+70,130);
                drawCmdWindow();
                Sleep(200);
            }
            dialogue();
            clearScreen();
            putStringLarge(large_font,135,60,"start mission 1",14);
            drawCmdWindow();
            Sleep(1000);
            clearScreen();
            //part_1();
            //part_2();
            part_1();
            clearScreen();
            dialogue2();
            putStringLarge(large_font,135,60,"start mission 2",14);
            drawCmdWindow();
            Sleep(1000);
            clearScreen();
            part_2();
            clearScreen();
            dialogue3();
            putStringLarge(large_font,135,60,"Last mission",14);
            drawCmdWindow();
            Sleep(1000);
            clearScreen();
            part_3();
            dialogue_final();
            Good_ending();

    }
    //return;
}

int ending(void)
{
    int i;
    Font *large_font = read_font("font.txt");
    Image *dead = read_image("dead.pixel","dead.color");
    for(i=0;i<200;i+=5){
        clearScreen();
        show_image(dead,0,0);
        putStringLarge(large_font,10+i,141,"Bye Bye",14);
        drawCmdWindow();
    }
    destroy_image(dead);

    system("pause");
    return 0;
}
int Good_ending(void)
{
    int i;
    Font *large_font = read_font("font.txt");
    Image *GE = read_image("GEnding.pixel","GEnding.color");
    for(i=0;i<200;i+=5){
        clearScreen();
        show_image(GE,0,0);
        putStringLarge(large_font,10+i,141,"Bye Bye",14);
        drawCmdWindow();
    }
    Sleep(1000);
    destroy_image(GE);
    return 0;
}
