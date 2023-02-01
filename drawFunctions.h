int drawFunction(int left, int right, int nivel, char s[]);
int drawIf(int left, int right, int nivel, char s[]);
int drawLoop(int left, int right, int nivel, char s[], bool tip);
int drawUntil(int left, int right, int niv1, int niv2, char s[]);
int drawInstruction(int left, int right, int nivel, char s[]); ///Va desena un chenar in care se va afla instructiunea s

int drawFunction(int left, int right, int nivel, char s[])
{
    setfillstyle(1, instructionColor);
    setbkcolor(instructionColor);
    bar(left, nivel, right, nivel+loopHeight);
    line(left, nivel, right, nivel);
    line (left, nivel, left, nivel + loopHeight);
    line (right, nivel, right, nivel + loopHeight);
    line (left, nivel + loopHeight, right, nivel + loopHeight);
    settextstyle(8, HORIZ_DIR, 1);
    trim(s, left, right);
    outtextxy ((left + right) / 2, (nivel + nivel + loopHeight) / 2 + textheight(s) / 4, s);
    return nivel + loopHeight;
}

int drawIf (int left, int right, int nivel, char s[])
{
    setfillstyle(1, ifColor);
    setbkcolor(ifColor);
    line (left, nivel, right, nivel);
    bar(left, nivel, right, nivel+ifHeight);
    line (left, nivel, left, nivel + ifHeight);
    line (right, nivel, right, nivel + ifHeight);
    line (left, nivel + ifHeight, right, nivel + ifHeight);
    line (left, nivel, (left + right)/2, nivel + ifHeight);
    line ((left + right)/2, nivel + ifHeight, right, nivel);
    settextstyle(8, HORIZ_DIR, 1);
    trim(s, left, right);
    outtextxy((left + right) / 2, (nivel + nivel + instructionHeight) / 2 + textheight(s) / 4, s);
    outtextxy(left + textwidth("T"), (nivel + nivel + 2*instructionHeight)/2 + textheight("T") / 4, "T");
    outtextxy(right - textwidth("F"), (nivel + nivel + 2*instructionHeight)/2 + textheight("F") / 4, "F");
    return nivel + ifHeight;
}

int drawLoop (int left, int right, int nivel, char s[], bool tip)
{
    if (tip == 0)
        {
            setfillstyle(1, whileColor);
            setbkcolor(whileColor);
        }
        else
        {
            setfillstyle(1, forColor);
            setbkcolor(forColor);
        }
    bar(left, nivel, right, nivel+loopHeight);
    line(left, nivel, right, nivel);
    line (left, nivel, left, nivel + loopHeight);
    line (right, nivel, right, nivel + loopHeight);
    line (left + loopIndent, nivel + loopHeight, right, nivel + loopHeight);
    settextstyle(8, HORIZ_DIR, 1);
    trim(s, left, right);
    outtextxy ((left + right) / 2, (nivel + nivel + loopHeight) / 2 + textheight(s) / 4, s);
    return nivel + loopHeight;
}

int drawUntil (int left, int right, int niv1, int niv2, char s[])
{
    setfillstyle(1, untilColor);
    setbkcolor(untilColor);
    bar(left+loopIndent, niv2, right, niv2+loopHeight);
    bar(left, niv1, left+loopIndent, niv2+loopHeight);
    line(left+loopIndent, niv2, right, niv2);
    line(left, niv1, left+loopIndent, niv1);
    line(left+loopIndent, niv1, left+loopIndent, niv2);
    line(left, niv1, left, niv2+loopHeight);
    line (right, niv2, right, niv2 + loopHeight);
    line (left, niv2 + loopHeight, right, niv2 + loopHeight);
    settextstyle(8, HORIZ_DIR, 1);
    trim(s, left, right);
    outtextxy ((left + right) / 2, (niv2 + niv2 + loopHeight) / 2 + textheight(s) / 4, s);
    return niv2 + loopHeight;
}

int drawInstruction (int left, int right, int nivel, char s[])
{
    setfillstyle(1, instructionColor);
    setbkcolor(instructionColor);
    bar(left, nivel, right, nivel+instructionHeight);
    line (left, nivel, left, nivel + instructionHeight);
    line (right, nivel, right, nivel + instructionHeight);
    line (left, nivel + instructionHeight, right, nivel + instructionHeight);
    line (left, nivel, right, nivel);
    settextstyle(8, HORIZ_DIR, 1);
    trim(s, left, right);
    outtextxy ((left + right) / 2, (nivel + nivel + instructionHeight) / 2 + textheight(s) / 4, s);
    return nivel + instructionHeight;
}
