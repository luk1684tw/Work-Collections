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
int main(void)
{
    int i,flag=0;
       //music
    initializeKeyInput();
    Font *large_font = read_font("font.txt");

    openAudioFile("maplestory_login.wav", &inmu);
    playAudio(&inmu);

    login();
    //choose channel(animation)
    Image *channel = read_image("channel.pixel","channel.color");
    for(i=20;i>=0;i--){
        clearScreen();
        show_image(channel,0,i);
        drawCmdWindow();
        Sleep(2);
    }
    flag=0;
    //clean up buffer
    while(getKeyEventASCII() == -1) break;
    //choose channel
    while(1){
        show_image(channel,0,0);
        flag=(flag+1)%2;
        if(flag){
            putStringLarge(large_font,90,141,"press space to start",15);
            Sleep(200);

        }else{
            putStringLarge(large_font,90,141,"press space to start",7);
            Sleep(200);
        }
        drawCmdWindow();
        if(waitForKeyDown(0.3)){
            while(getKeyEventASCII() == -1) break;
            break;
        }
    }
    destroy_image(channel);

    chooseCharacter(0);

    system("pause");
    return 0;
}
