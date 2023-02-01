void hoverFunction(node *p, bool tip);
void hoverIf(node *p, bool tip);
void hoverWhile(node *p, bool tip);
void hoverFor(node *p, bool tip); ///deseneaza pe ecran instructiunea corespunzatoare lui p, cu highlight sau fara, in functie de valoarea parametrului tip
void hoverUntil(node *p, bool tip);
void hoverInstruction(node *p, bool tip);

void hoverFunction(node *p, bool tip)
{
    if (tip == 1)
       {
            setfillstyle(1, instructionColorHover);
            setbkcolor(instructionColorHover);
       }
       else
       {
            setfillstyle(1, instructionColor);
            setbkcolor(instructionColor);
       }
    bar(p->left, p->nivel1, p->right, p->nivel1 + loopHeight);
    line(p->left, p->nivel1, p->right, p->nivel1);
    line(p->right, p->nivel1, p->right, p->nivel1 + loopHeight);
    line(p->right, p->nivel1 + loopHeight, p->left, p->nivel1 + loopHeight);
    line(p->left, p->nivel1 + loopHeight, p->left, p->nivel1);
    char s[512];
    strcpy(s, p->type);
    strcat(s, " ");
    strcat(s, p->expression);
    trim(s, p->left, p->right);
    settextstyle(8, HORIZ_DIR, 1);
    outtextxy ((p->left + p->right) / 2, (p->nivel1 + p->nivel1 + loopHeight) / 2 + textheight(s) / 4, s);
}

void hoverIf(node *p, bool tip)
{
    if (tip==1)
        {
            setfillstyle(1, ifColorHover);
            setbkcolor(ifColorHover);
        }
        else
        {
            setfillstyle(1, ifColor);
            setbkcolor(ifColor);
        }
    bar(p->left, p->nivel1, p->right, p->nivel1 + ifHeight);
    line(p->left, p->nivel1, p->right, p->nivel1);
    line(p->left, p->nivel1, p->left, p->nivel1 + ifHeight);
    line(p->left, p->nivel1 + ifHeight, p->right, p->nivel1 + ifHeight);
    line(p->right, p->nivel1, p->right, p->nivel1 + ifHeight);
    line(p->left, p->nivel1, (p->left + p->right) / 2, p->nivel1 + ifHeight);
    line((p->left + p->right) / 2, p->nivel1 + ifHeight, p->right, p->nivel1);
    char s[512];
    strcpy(s, p->type);
    strcat(s, " ");
    strcat(s, p->expression);
    trim(s, p->left, p->right);
    settextstyle(8, HORIZ_DIR, 1);
    outtextxy((p->left + p->right) / 2, (p->nivel1 + p->nivel1 + instructionHeight) / 2 + textheight(s) / 4, s);
    outtextxy(p->left + textwidth("T"), (p->nivel1 + p->nivel1 + 2*instructionHeight)/2 + textheight("T") / 4, "T");
    outtextxy(p->right - textwidth("F"), (p->nivel1 + p->nivel1 + 2*instructionHeight)/2 + textheight("F") / 4, "F");
}

void hoverWhile(node *p, bool tip)
{
    if (tip == 1)
        {
            setfillstyle(1, whileColorHover);
            setbkcolor(whileColorHover);
        }
        else
        {
            setfillstyle(1, whileColor);
            setbkcolor(whileColor);
        }
    bar(p->left, p->nivel1, p->right, p->nivel1 + loopHeight);
    bar(p->left, p->nivel1 + loopHeight, p->left + loopIndent, p->nivel2);
    line(p->left, p->nivel1, p->right, p->nivel1);
    line(p->left, p->nivel1, p->left, p->nivel2);
    line(p->left, p->nivel2, p->left + loopIndent, p->nivel2);
    line(p->left + loopIndent, p->nivel2, p->left + loopIndent, p->nivel1 + loopHeight);
    line(p->left + loopIndent, p->nivel1 + loopHeight, p->right, p->nivel1 + loopHeight);
    line(p->right, p->nivel1 + loopHeight, p->right, p->nivel1);
    char s[512];
    strcpy(s, p->type);
    strcat(s, " ");
    strcat(s, p->expression);
    trim(s, p->left, p->right);
    settextstyle(8, HORIZ_DIR, 1);
    outtextxy ((p->left + p->right) / 2, (p->nivel1 + p->nivel1 + loopHeight) / 2 + textheight(s) / 4, s);
}

void hoverFor (node *p, bool tip)
{
    if (tip == 1)
        {
            setfillstyle(1, forColorHover);
            setbkcolor(forColorHover);
        }
        else
        {
            setfillstyle(1, forColor);
            setbkcolor(forColor);
        }
    bar(p->left, p->nivel1, p->right, p->nivel1 + loopHeight);
    bar(p->left, p->nivel1 + loopHeight, p->left + loopIndent, p->nivel2);
    line(p->left, p->nivel1, p->right, p->nivel1);
    line(p->left, p->nivel1, p->left, p->nivel2);
    line(p->left, p->nivel2, p->left + loopIndent, p->nivel2);
    line(p->left + loopIndent, p->nivel2, p->left + loopIndent, p->nivel1 + loopHeight);
    line(p->left + loopIndent, p->nivel1 + loopHeight, p->right, p->nivel1 + loopHeight);
    line(p->right, p->nivel1 + loopHeight, p->right, p->nivel1);
    char s[512];
    strcpy(s, p->type);
    strcat(s, " ");
    strcat(s, p->expression);
    trim(s, p->left, p->right);
    settextstyle(8, HORIZ_DIR, 1);
    outtextxy ((p->left + p->right) / 2, (p->nivel1 + p->nivel1 + loopHeight) / 2 + textheight(s) / 4, s);
}

void hoverUntil(node *p, bool tip)
{
    if (tip == 1)
        {
            setfillstyle(1, untilColorHover);
            setbkcolor(untilColorHover);
        }
        else
        {
            setfillstyle(1, untilColor);
            setbkcolor(untilColor);
        }
    bar(p->left, p->nivel2 - loopHeight, p->right, p->nivel2);
    bar(p->left, p->nivel1, p->left + loopIndent, p->nivel2 - loopHeight);
    line(p->right, p->nivel2, p->left, p->nivel2);
    line(p->left, p->nivel2, p->left, p->nivel1);
    line(p->left, p->nivel1, p->left + loopIndent, p->nivel1);
    line(p->left + loopIndent, p->nivel1, p->left + loopIndent, p->nivel2 - loopHeight);
    line(p->left + loopIndent, p->nivel2 - loopHeight, p->right, p->nivel2 - loopHeight);
    line(p->right, p->nivel2 - loopHeight, p->right, p->nivel2);
    char s[512];
    strcpy(s, p->type);
    strcat(s, " ");
    strcat(s, p->expression);
    trim(s, p->left, p->right);
    settextstyle(8, HORIZ_DIR, 1);
    outtextxy ((p->left + p->right) / 2, (p->nivel2 - loopHeight + p->nivel2 - loopHeight + loopHeight) / 2 + textheight(s) / 4, s);
}

void hoverInstruction(node *p, bool tip)
{
    if (tip == 1)
        {
            setfillstyle(1, instructionColorHover);
            setbkcolor(instructionColorHover);
        }
        else
        {
            setfillstyle(1, instructionColor);
            setbkcolor(instructionColor);
        }
    bar(p->left, p->nivel1, p->right, p->nivel2);
    line(p->left, p->nivel1, p->right, p->nivel1);
    line(p->right, p->nivel1, p->right, p->nivel2);
    line(p->right, p->nivel2, p->left, p->nivel2);
    line(p->left, p->nivel2, p->left, p->nivel1);
    char s[512];
    strcpy(s, p->expression);
    trim(s, p->left, p->right);
    settextstyle(8, HORIZ_DIR, 1);
    outtextxy ((p->left + p->right) / 2, (p->nivel1 + p->nivel1 + instructionHeight) / 2 + textheight(p->expression) / 4, p->expression);
}
