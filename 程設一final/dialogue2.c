#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<mmsystem.h>
#include<time.h>
#include "console_draw3.h"
#include "kb_input2.h"
#include "image.h"
#include "font.h"
#include "audio.h"
#define dia_words 16
char dia[dia_words][30];
void dialogue2(void)
{
    FILE *fp;
    int nw, i, j;
    fp=fopen("dialogue2.txt", "r");
    nw=0;
    while(!feof(fp)&&nw<dia_words){
        fscanf(fp,"%s", dia[nw]);
        while(!feof(fp)&&fgetc(fp)!='\n');
        nw++;
    }
    for(i=0;i<dia_words;i++){
        for(j=0;j<strlen(dia[i]);j++){
            if(dia[i][j]=='_') dia[i][j] = ' ';
        }
    }
    fclose(fp);
    initializeKeyInput();

    int k=0;
    Image *dialogue1 = read_image("hans_dia.pixel","hans_dia.color");
    Image *dialogue2 = read_image("thief_dia.pixel","thief_dia.color");
    Font *large_font = read_font("font.txt");
    while(k<8){
        clearScreen();
        while(getKeyEventASCII()!=-1);
        if(k%2==0){
            show_image(dialogue1,0,0);
            putStringLarge(large_font,100,20,dia[2*k],0);
            putStringLarge(large_font,100,30,dia[2*k+1],0);
            drawCmdWindow();
            while(waitForKeyDown(10))  break;
        }
        else{
            show_image(dialogue2,0,0);
            putStringLarge(large_font,100,20,dia[2*k],0);
            putStringLarge(large_font,100,30,dia[2*k+1],0);
            drawCmdWindow();
            while(waitForKeyDown(10))  break;
        }
        k++;
    }
    clearScreen();
    destroy_image(dialogue1);
    destroy_image(dialogue2);
}
