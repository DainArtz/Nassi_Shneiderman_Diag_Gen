bool convertButton(int x1, int y1, int x2, int y2); ///Deseneaza butonul de CONVERT
bool loadButton(int x1, int y1, int x2, int y2); ///Deseneaza butonul de LOAD
bool exitButton(int x1, int y1, int x2, int y2); ///Deseneaza butonul de EXIT
bool backButton (int x1, int y1, int x2, int y2); ///Deseneaza butonul de BACK
bool saveButton (int x1, int y1, int x2, int y2); ///Deseneaza butonul de SAVE
bool scrollUpButton (int x1, int y1, int x2, int y2); ///Deseneaza butonul de UP
bool scrollDownButton (int x1, int y1, int x2, int y2); ///Deseneaza butonul de DOWN

bool convertButton(int x1, int y1, int x2, int y2)
{
    int mx, my, cx, cy; /// mx, my - Pozitia mouse-ului | cx, cy - Pozitia ultimului click
    mx=mousex();
    my=mousey();
    if (mx>=x1 && mx<=x2 && my>=y1 && my<=y2) {
        if (convertState!=2) { ///Highlight
            setfillstyle(1, COLOR(39, 174, 96));
            bar(x1, y1, x2, y2);
            setbkcolor(COLOR(39, 174, 96));
            outtextxy((x1+x2)/2, (y2+y1)/2 + textheight("Convert")/4, "Convert");
            convertState=2;
        }
        getmouseclick(WM_LBUTTONDOWN, cx, cy); ///Obtin coordonatele ultimului click
        if (cx>=x1 && cx<=x2 && cy>=y1 && cy<=y2) {
                clearmouseclick(WM_LBUTTONDOWN); ///Ma asigur ca nu mai am clickuri neprocesate in coada
                if (loadStatusState == 1){
                    mainMenu = false; ///Am apasat convert si nu mai sunt pe fereastra de meniu
                    diagramScreen();
                    return true;
                }
                return false; ///Nu exista fisier incarcat si nu am ce sa convertesc
            }

    }
    else {
        if (convertState!=1) {
            setfillstyle(1, COLOR(46, 204, 113)); ///Desenez butonul in mod normal
            bar(x1, y1, x2, y2);
            setbkcolor(COLOR(46, 204, 113));
            outtextxy((x1+x2)/2, (y2+y1)/2 + textheight("Convert")/4, "Convert");
            convertState=1;
        }
    }
    return false;
}

bool loadButton(int x1, int y1, int x2, int y2)
{
    int mx, my, cx, cy;
    mx=mousex();
    my=mousey();
    if (mx>=x1 && mx<=x2 && my>=y1 && my<=y2) {
        if (loadState!=2) {
            setfillstyle(1, COLOR(39, 174, 96));
            bar(x1, y1, x2, y2);
            setbkcolor(COLOR(39, 174, 96));
            outtextxy((x1+x2)/2, (y2+y1)/2 + textheight("Load")/4, "Load");
            loadState=2;
        }
        getmouseclick(WM_LBUTTONDOWN, cx, cy);
        if (cx>=x1 && cx<=x2 && cy>=y1 && cy<=y2) {
                clearmouseclick(WM_LBUTTONDOWN);
                return true;
            }

    }
    else {
        if (loadState!=1) {
            setfillstyle(1, COLOR(46, 204, 113));
            bar(x1, y1, x2, y2);
            setbkcolor(COLOR(46, 204, 113));
            outtextxy((x1+x2)/2, (y2+y1)/2 + textheight("Load")/4, "Load");
            loadState=1;
        }
    }
    return false;
}

bool exitButton(int x1, int y1, int x2, int y2)
{
    int mx, my, cx, cy;
    mx=mousex();
    my=mousey();
    if (mx>=x1 && mx<=x2 && my>=y1 && my<=y2) {
        if (exitState!=2) {
            setfillstyle(1, COLOR(39, 174, 96));
            bar(x1, y1, x2, y2);
            setbkcolor(COLOR(39, 174, 96));
            outtextxy((x1+x2)/2, (y2+y1)/2 + textheight("Exit")/4, "Exit");
            exitState=2;
        }
        getmouseclick(WM_LBUTTONDOWN, cx, cy);
        if (cx>=x1 && cx<=x2 && cy>=y1 && cy<=y2) {
                clearmouseclick(WM_LBUTTONDOWN);
                return true;
            }

    }
    else {
        if (exitState!=1) {
            setfillstyle(1, COLOR(46, 204, 113));
            bar(x1, y1, x2, y2);
            setbkcolor(COLOR(46, 204, 113));
            outtextxy((x1+x2)/2, (y2+y1)/2 + textheight("Exit")/4, "Exit");
            exitState=1;
        }
    }
    return false;
}

bool backButton (int x1, int y1, int x2, int y2)
{
    int mx, my, cx, cy;
    mx=mousex();
    my=mousey();
    if (mx>=x1 && mx<=x2 && my>=y1 && my<=y2) {
        if (backState!=2) {
            setfillstyle(1, COLOR(39, 174, 96));
            bar(x1, y1, x2, y2);
            setbkcolor(COLOR(39, 174, 96));
            settextstyle(8, HORIZ_DIR, 0);
            outtextxy((x1+x2)/2, (y2+y1)/2 + textheight("BACK")/4, "BACK");
            backState=2;
        }
        getmouseclick(WM_LBUTTONDOWN, cx, cy);
        if (cx>=x1 && cx<=x2 && cy>=y1 && cy<=y2) {
                clearmouseclick(WM_LBUTTONDOWN);
                mainMenu = true;
                initialisation();
                return true;
            }

    }
    else {
        if (backState!=1) {
            setfillstyle(1, COLOR(46, 204, 113));
            bar(x1, y1, x2, y2);
            setbkcolor(COLOR(46, 204, 113));
            settextstyle(8, HORIZ_DIR, 0);
            outtextxy((x1+x2)/2, (y2+y1)/2 + textheight("BACK")/4, "BACK");
            backState=1;
        }
    }
    return false;
}

bool saveButton (int x1, int y1, int x2, int y2)
{
    int mx, my, cx, cy;
    mx=mousex();
    my=mousey();
    if (mx>=x1 && mx<=x2 && my>=y1 && my<=y2) {
        if (saveState!=2) {
            setfillstyle(1, COLOR(39, 174, 96));
            bar(x1, y1, x2, y2);
            setbkcolor(COLOR(39, 174, 96));
            settextstyle(8, HORIZ_DIR, 0);
            outtextxy((x1+x2)/2, (y2+y1)/2 + textheight("SAVE")/4, "SAVE");
            saveState=2;
        }
        getmouseclick(WM_LBUTTONDOWN, cx, cy);
        if (cx>=x1 && cx<=x2 && cy>=y1 && cy<=y2) {
                clearmouseclick(WM_LBUTTONDOWN);
                return true;
            }

    }
    else {
        if (saveState!=1) {
            setfillstyle(1, COLOR(46, 204, 113));
            bar(x1, y1, x2, y2);
            setbkcolor(COLOR(46, 204, 113));
            settextstyle(8, HORIZ_DIR, 0);
            outtextxy((x1+x2)/2, (y2+y1)/2 + textheight("SAVE")/4, "SAVE");
            saveState=1;
        }
    }
    return false;
}

bool scrollUpButton (int x1, int y1, int x2, int y2)
{
    int mx, my, cx, cy;
    mx=mousex();
    my=mousey();
    if (mx>=x1 && mx<=x2 && my>=y1 && my<=y2) {
        if (scrollUpState!=2) {
            setfillstyle(1, COLOR(39, 174, 96));
            bar(x1, y1, x2, y2);
            setbkcolor(COLOR(39, 174, 96));
            settextstyle(8, HORIZ_DIR, 0);
            outtextxy((x1+x2)/2, (y2+y1)/2 + textheight("UP")/4, "UP");
            scrollUpState=2;
        }
        getmouseclick(WM_LBUTTONDOWN, cx, cy);
        if (cx>=x1 && cx<=x2 && cy>=y1 && cy<=y2) {
                clearmouseclick(WM_LBUTTONDOWN);
                return true;
            }

    }
    else {
        if (scrollUpState!=1) {
            setfillstyle(1, COLOR(46, 204, 113));
            bar(x1, y1, x2, y2);
            setbkcolor(COLOR(46, 204, 113));
            settextstyle(8, HORIZ_DIR, 0);
            outtextxy((x1+x2)/2, (y2+y1)/2 + textheight("UP")/4, "UP");
            scrollUpState=1;
        }
    }
    return false;
}

bool scrollDownButton (int x1, int y1, int x2, int y2)
{
    int mx, my, cx, cy;
    mx=mousex();
    my=mousey();
    if (mx>=x1 && mx<=x2 && my>=y1 && my<=y2) {
        if (scrollDownState!=2) {
            setfillstyle(1, COLOR(39, 174, 96));
            bar(x1, y1, x2, y2);
            setbkcolor(COLOR(39, 174, 96));
            settextstyle(8, HORIZ_DIR, 0);
            outtextxy((x1+x2)/2, (y2+y1)/2 + textheight("DOWN")/4, "DOWN");
            scrollDownState=2;
        }
        getmouseclick(WM_LBUTTONDOWN, cx, cy);
        if (cx>=x1 && cx<=x2 && cy>=y1 && cy<=y2) {
                clearmouseclick(WM_LBUTTONDOWN);
                return true;
            }

    }
    else {
        if (scrollDownState!=1) {
            setfillstyle(1, COLOR(46, 204, 113));
            bar(x1, y1, x2, y2);
            setbkcolor(COLOR(46, 204, 113));
            settextstyle(8, HORIZ_DIR, 0);
            outtextxy((x1+x2)/2, (y2+y1)/2 + textheight("DOWN")/4, "DOWN");
            scrollDownState=1;
        }
    }
    return false;
}
