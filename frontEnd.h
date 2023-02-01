///Aici voi memora rezolutia ecranului curent
int screen_width = GetSystemMetrics(SM_CXSCREEN);
int screen_height = GetSystemMetrics(SM_CYSCREEN);

///Initializarea unor variabile care depind de rezolutia ecranului si asupra carora vom construi dependente
int mainMenuBWidth1=(screen_width/3), mainMenuBWidth2=(screen_width/3)*2; ///Stanga dreapta pentru butoanele din meniul principal
int mainMenuCenter=screen_height/2; ///Centrul ecranului
int mainMenuBHeight=(screen_height/100)*3; ///Inaltimea unui buton din MM

///Initializarea statusurilor butoanelor
///Scopul este de a redesena butoanele doar in
///cazul in care are loc o schimbare a statusului lor
int backState = 0, loadStatusState=0, convertState=0, loadState=0, exitState=0, scrollUpState=0, scrollDownState=0, saveState=0;

///Declaratii Functii
void drawTitle(); ///Deseneaza titlul in meniul principal
void initialisation(); ///Initializeaza instrumentele de desen
void diagramScreen(); ///Deseneaza cadrul specific diagramei
void loadStatus(int x1, int y1, int x2, int y2); ///Deseneaza indicatorul pentru LOAD: ROSU - Nu am selectat niciun fisier | VERDE - AM un fisier selectat cu o cale valida

#include "buttons.h"

void drawTitle()
{
    ///Dependenta a marimii textului fata de rezolutie
    setusercharsize(((3*screen_width)/1920), 1, ((4*screen_height)/1080), 1);
    outtextxy(screen_width/2, (mainMenuCenter-mainMenuBHeight)/2, "Nassi–Shneiderman Diag Gen");
}

void initialisation()
{
    backState = convertState = loadStatusState = loadState = exitState = scrollDownState = scrollUpState = saveState = 0;
    setbkcolor(COLOR(44, 62, 80));
    cleardevice();
    settextstyle(8, HORIZ_DIR, 0);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    drawTitle();
    setusercharsize(1, 1, 1, 1);
    loadStatus(mainMenuBWidth2+10, mainMenuCenter+mainMenuBHeight*2, mainMenuBWidth2+10+mainMenuBHeight*2, mainMenuCenter+mainMenuBHeight*4);
}

void diagramScreen()
{
    cleardevice(); ///Sterg meniul pricipal de pe ecran
    setbkcolor(COLOR(44, 62, 80));
    cleardevice();
}

void loadStatus(int x1, int y1, int x2, int y2)
{
    if (loadStatusState == 0) { ///ROSU
        setfillstyle(1, COLOR(231, 76, 60));
        bar(x1, y1, x2, y2);
    } else if (loadStatusState == 1) { ///VERDE
        setfillstyle(1, COLOR(46, 204, 113));
        bar(x1, y1, x2, y2);
    }
}
