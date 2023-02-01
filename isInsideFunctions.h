bool isInsideFunction(node *p);
bool isInsideIf(node *p);
bool isInsideWhile(node *p);
bool isInsideFor(node *p); ///verifica daca pozitia cursorului se afla in interiorul instructiunii din nodul p
bool isInsideUntil(node *p);
bool isInsideInstruction(node *p);

bool isInsideFunction(node *p)
{
    int mx, my;
    mx=mousex();
    my=mousey();
    return p->left <= mx && mx <= p->right && p->nivel1 <= my && my <= p->nivel1 + loopHeight;
}

bool isInsideIf(node *p)
{
    int mx, my;
    mx=mousex();
    my=mousey();
    return p->left <= mx && mx <= p->right && p->nivel1 <= my && my <= p->nivel1 + ifHeight;
}

bool isInsideWhile(node *p)
{
    int mx, my;
    mx=mousex();
    my=mousey();
    return p->left <= mx && mx <= p->right && p->nivel1 <= my && my <= p->nivel1 + loopHeight ||
           p->left <= mx && mx <= p->left + loopIndent && p->nivel1 <= my && my <= p->nivel2;
}

bool isInsideFor(node *p)
{
    int mx, my;
    mx=mousex();
    my=mousey();
    return p->left <= mx && mx <= p->right && p->nivel1 <= my && my <= p->nivel1 + loopHeight ||
           p->left <= mx && mx <= p->left + loopIndent && p->nivel1 <= my && my <= p->nivel2;
}

bool isInsideUntil(node *p)
{
    int mx, my;
    mx=mousex();
    my=mousey();
    return p->left <= mx && mx <= p->right && p->nivel2 - loopHeight <= my && my <= p->nivel2 ||
           p->left <= mx && mx <= p->left + loopIndent && p->nivel1 <= my && my <= p->nivel2;
}

bool isInsideInstruction(node *p)
{
    int mx, my;
    mx=mousex();
    my=mousey();
    return p->left <= mx && mx <= p->right && p->nivel1 <= my && my <= p->nivel1 + instructionHeight;
}
