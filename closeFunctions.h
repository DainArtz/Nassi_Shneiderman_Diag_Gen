void closeInstruction(node *p, int nivel, int nivelNou);
void closeIf(int left, int right, int niv1, int niv2);
void closeLoop(int left, int right, int niv1, int niv2, bool tip);

void closeInstruction(node *p, int nivel, int nivelNou)
{
    if (strcmp (p->type, "if") == 0)
       closeIf (p->left, p->right, nivel + ifHeight, nivelNou);
    if (strcmp (p->type, "while") == 0)
       closeLoop (p->left, p->right, nivel + loopHeight, nivelNou, 0);
    if (strcmp (p->type, "for") == 0)
       closeLoop (p->left, p->right, nivel + loopHeight, nivelNou, 1);
}

void closeIf(int left, int right, int niv1, int niv2)
{
    line (left, niv1, left, niv2);
    line (right, niv1, right, niv2);
    line (left, niv2, right, niv2);
}

void closeLoop(int left, int right, int niv1, int niv2, bool tip)
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
    bar(left, niv1, left+loopIndent, niv2);
    line(left+loopIndent, niv1, left+loopIndent, niv2);
    line (left, niv1, left, niv2);
    line (left, niv2, left + loopIndent, niv2);
}
