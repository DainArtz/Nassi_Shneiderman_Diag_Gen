/*
$$\   $$\  $$$$$$\  $$$$$$$\   $$$$$$\
$$$\  $$ |$$  __$$\ $$  __$$\ $$  __$$\
$$$$\ $$ |$$ /  \__|$$ |  $$ |$$ /  \__|
$$ $$\$$ |\$$$$$$\  $$ |  $$ |$$ |$$$$\
$$ \$$$$ | \____$$\ $$ |  $$ |$$ |\_$$ |
$$ |\$$$ |$$\   $$ |$$ |  $$ |$$ |  $$ |
$$ | \$$ |\$$$$$$  |$$$$$$$  |\$$$$$$  |
\__|  \__| \______/ \_______/  \______/

        Nassi - Shneiderman
         Diagram Generator

 Balan Calin --- Rotariu George-Flavian
 No. of Code Lines: 1254 (17.12.2022)

*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <graphics.h>
#include <winbgim.h>
#include <windows.h>
#include <cstring>

using namespace std;

bool mainLoop=true; ///Controleaza functionarea programului
bool mainMenu=true; ///Ma aflu pe fereastra de meniu sau nu
char filePath[512]; ///Calea catre fisierul din care citesc pseudocod

#include "frontEnd.h"
#include "backEnd.h"

int main()
{
    initwindow(screen_width, screen_height, "Nassi-Shneiderman Diag Gen"); ///Am pus linia in afara functiei de mai jos ca sa pot apela functia de mai jos cand ies din fereastra pentru convert
    initialisation(); ///Initializez fereastra de desen grafic
    while (mainLoop) {
            if (mainMenu){ ///Daca sunt in meniul principal desenez butoanele
                if (convertButton(mainMenuBWidth1, mainMenuCenter-mainMenuBHeight, mainMenuBWidth2, mainMenuCenter+mainMenuBHeight)) ///Daca apas pe convert nu mai desenez meniul principal
                    fileProcessing(); ///Incep procesarea pseudocodului && desenez fereastra diagramei
                if (mainMenu){ ///Daca si dupa evaluarea statusului butonului CONVERT sunt in meniul principal, desenez restul butoanelor
                    if (loadButton(mainMenuBWidth1, mainMenuCenter+mainMenuBHeight*2, mainMenuBWidth2, mainMenuCenter+mainMenuBHeight*4)){
                            openDialogue(filePath); ///Deschid ferestra de dialog
                            pathProcessing(filePath); ///Procesez calea catre fisier
                            loadStatus(mainMenuBWidth2+10, mainMenuCenter+mainMenuBHeight*2, mainMenuBWidth2+10+mainMenuBHeight*2, mainMenuCenter+mainMenuBHeight*4); ///Redesenez indicatorul de status pentru load
                        }
                    if (exitButton(mainMenuBWidth1, mainMenuCenter+mainMenuBHeight*5, mainMenuBWidth2, mainMenuCenter+mainMenuBHeight*7))
                        mainLoop = false; ///Opresc functionarea programului
                }
            }
            else {
             if (backButton(0.02*screen_height, 0.02*screen_height, 0.08*screen_width, 0.08*screen_height)) ///Desenez butonul back doar in fereastra diagramei
                mainMenu = true; ///Revin in meniul principal
            }
    }
    return 0;
}
