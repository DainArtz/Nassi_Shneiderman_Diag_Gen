///Declaratii structuri de date
struct node
{
    bool isHovered;
    int nivel1, nivel2; ///nivelul la care incepe, respectiv se termina instructiunea
    int left, right; ///latimea instructiunii
    int indentationLevel;
    int nrOfDescendents;
    char type[256];
    char expression[512];
    node* descendents[128];
};

///Vector de radacini
node* mainRoots[128];
int maxIndexOfRoots;

///Stiva de parinti
node* stackOfParents[512];
int topOfStack;

///Constante de inaltime (si indentare)
int instructionHeight = 0.03 * screen_height;
int ifHeight = 0.05 * screen_height;
int loopHeight = 0.04 * screen_height;
int loopIndent = 0.02 * screen_width; ///Distanta la care se indenteaza elementele din cadrul instructiunilor repetitive

///Constante de culoare
int ifColor = COLOR(6, 158, 45), ifColorHover=COLOR(7, 197, 55);
int whileColor = COLOR(5, 142, 63), whileColorHover = COLOR(7, 197, 86);
int forColor = COLOR(4, 119, 59), forColorHover = COLOR(6, 157, 79);
int untilColor = COLOR(3, 96, 22), untilColorHover = COLOR(4, 139, 31);
int instructionColor = COLOR(3, 68, 12), instructionColorHover = COLOR(5, 118, 20);

void fileProcessing(); ///Procesarea fisierului selectat
void initializeazaNod(node *p, char *s); ///Initializarea nodului curent
int getIndentationLevel(char s[512]); ///Obtinerea nivelului de indentare a unui nod
bool isInstruction(char *s, char instruction[]); ///Ce fel de instructiune este pe linia curenta
char* extractExpression(char *s, int st, int dr); ///Extragem expresia din linia curenta
void setLeftRight(node *parent, node *son); ///Setam coordonatele stanga-dreapta a nodului curent in functie de coordonatele parintelui
void goThrough(); ///Controleaza interactiuniile cu diagrama
void drawDiagram (int &nivel); ///Desenarea intregii diagrame
int dfs(node *p, int nivel); ///Deseneaza diagrama unei singure functii sau proceduri
void trim(char s[], int st, int dr); ///Se asigura ca sirul de caractere ale unei instructiuni nu depaseste casuta alocata
void parcurge(); ///Apeleaza dfsHover() pentru fiecare radacina din mainRoots[]
bool dfsHover(node *p); ///Verifica daca dau hover unei instructiuni pentru o anumita radacina si redeseneaza nodurile afectate

#include "selectFile.h"
#include "drawFunctions.h"
#include "closeFunctions.h"
#include "isInsideFunctions.h"
#include "hoverFunctions.h"

void fileProcessing()
{
    int i, lg;
    FILE *fptr;
    fptr = fopen(filePath,"r");
    char s[512];
    maxIndexOfRoots=0;
    topOfStack=-1;
    node *p;
    char *q;
    while (fgets(s, 512, fptr)) {
        lg=strlen(s);
        s[lg-1]='\0';
        lg--;
        if (lg==0)
            continue;
        if (strstr(s, "BEGIN") || strstr (s, "END")) {
            continue;
        } else {
            p = new node;
            initializeazaNod(p, s);
            if (strcmp(p->type, "function") == 0 || strcmp(p->type, "procedure") == 0) {
                mainRoots[maxIndexOfRoots++]=p;
                topOfStack=-1;
                stackOfParents[++topOfStack]=p;
                p->left = 0.1 * screen_width;
                p->right = 0.9 * screen_width;
            } else if (strcmp(p->type, "if") == 0) {
                while (stackOfParents[topOfStack]->indentationLevel>=p->indentationLevel)
                        topOfStack--;
                setLeftRight (stackOfParents[topOfStack], p);
                stackOfParents[topOfStack]->descendents[stackOfParents[topOfStack]->nrOfDescendents]=p;
                stackOfParents[topOfStack]->nrOfDescendents++;
                stackOfParents[++topOfStack]=p;
            } else if (strcmp(p->type, "else") == 0) {
                while (stackOfParents[topOfStack]->indentationLevel >= p->indentationLevel) {
                    if (strstr (stackOfParents[topOfStack]->type, "if") && stackOfParents[topOfStack]->indentationLevel == p->indentationLevel)
                        break;
                    topOfStack--;
                }
                setLeftRight (stackOfParents[topOfStack], p);
                stackOfParents[topOfStack]->descendents[stackOfParents[topOfStack]->nrOfDescendents]=p;
                stackOfParents[topOfStack]->nrOfDescendents++;
                stackOfParents[++topOfStack]=p;
            } else if (strcmp(p->type, "while") == 0) {
                while (stackOfParents[topOfStack]->indentationLevel >= p->indentationLevel)
                        topOfStack--;
                setLeftRight (stackOfParents[topOfStack], p);
                stackOfParents[topOfStack]->descendents[stackOfParents[topOfStack]->nrOfDescendents]=p;
                stackOfParents[topOfStack]->nrOfDescendents++;
                stackOfParents[++topOfStack]=p;
            } else if (strcmp(p->type, "repeat") == 0) {
                while (stackOfParents[topOfStack]->indentationLevel>=p->indentationLevel)
                        topOfStack--;
                setLeftRight (stackOfParents[topOfStack], p);
                stackOfParents[topOfStack]->descendents[stackOfParents[topOfStack]->nrOfDescendents]=p;
                stackOfParents[topOfStack]->nrOfDescendents++;
                stackOfParents[++topOfStack]=p;
            } else if (strcmp(p->type, "until") == 0) { ///NU TREBUIE SA ALOC MEMORIE!
                while (stackOfParents[topOfStack]->indentationLevel>=p->indentationLevel) {
                    if (strstr(stackOfParents[topOfStack]->type, "repeat") && stackOfParents[topOfStack]->indentationLevel==p->indentationLevel)
                        break;
                    topOfStack--;
                }
                strcpy (stackOfParents[topOfStack]->expression, p->expression);
                strcpy (stackOfParents[topOfStack]->type, p->type);
                delete p;
            } else if (strcmp(p->type, "for") == 0) {
                while (stackOfParents[topOfStack]->indentationLevel >= p->indentationLevel)
                        topOfStack--;
                setLeftRight (stackOfParents[topOfStack], p);
                stackOfParents[topOfStack]->descendents[stackOfParents[topOfStack]->nrOfDescendents]=p;
                stackOfParents[topOfStack]->nrOfDescendents++;
                stackOfParents[++topOfStack]=p;
            } else {
                while (stackOfParents[topOfStack]->indentationLevel >= p->indentationLevel)
                        topOfStack--;
                setLeftRight (stackOfParents[topOfStack], p);
                stackOfParents[topOfStack]->descendents[stackOfParents[topOfStack]->nrOfDescendents]=p;
                stackOfParents[topOfStack]->nrOfDescendents++;

            }
        }
    }
    goThrough();
}

void initializeazaNod(node *p, char *s)
{
    int i;
    p->indentationLevel = getIndentationLevel(s);
    p->isHovered = 0;
    p->nivel1 = p->nivel2 = 0;
    for (i=strlen(s)-1; s[i] == ' '; i--);
        s[i+1] = '\0';
    p->nrOfDescendents = 0;
    if (isInstruction(s, "function"))
        {
            strcpy (p->type, "function");
            strcpy (p->expression, extractExpression(s, 8, strlen(s)-1));
            return;
        }
    if (isInstruction(s, "procedure"))
        {
            strcpy (p->type, "procedure");
            strcpy (p->expression, extractExpression(s, 9, strlen(s)-1));
            return;
        }
    if (isInstruction(s, "if"))
        {
            strcpy(p->type, "if");
            strcpy (p->expression, extractExpression(s, 2, strlen(s)-5));
            return;
        }
    if (isInstruction(s, "while"))
        {
            strcpy (p->type, "while");
            strcpy(p->expression, extractExpression(s, 5, strlen(s)-3));
            return;
        }
    if (isInstruction(s, "for"))
        {
            strcpy (p->type, "for");
            strcpy (p->expression, extractExpression(s, 3, strlen(s)-3));
            return;
        }
    if (isInstruction(s, "until"))
        {
            strcpy (p->type, "until");
            strcpy (p->expression, extractExpression(s, 5, strlen(s)-2));
            return;
        }
    if (isInstruction(s, "repeat"))
        {
            strcpy (p->type, "repeat");
            p->expression[0] = '\0';
            return;
        }
    if (isInstruction(s, "else"))
        {
            strcpy (p->type, "else");
            p->expression[0] = '\0';
            return;
        }
    strcpy (p->type, "instruction");
    strcpy (p->expression, s);
}

int getIndentationLevel(char s[512]) {
    int i=0, lg=strlen(s);
    while (s[i]==' ' && i<lg)
        i++;
    strcpy(s, s+i);
    return i;
}

bool isInstruction (char *s, char instruction[])
{
    int i=strlen(instruction);
    if (!(s[i] == ' ' || s[i] == '\0')) return 0;
    for (i=i-1; i>=0; i--)
        if (s[i] != instruction[i]) return 0;
    return 1;
}

char* extractExpression(char *s, int st, int dr)
{
    int i;
    for (i=dr; s[i] == ' '; i--);
    s[i+1] = '\0';
    for (i=st; s[i] == ' '; i++);
    strcpy (s, s+i);
}

void setLeftRight (node *parent, node *son)
{
    int left = parent->left, right = parent->right;
    if (strcmp (parent->type, "while") == 0 || strcmp (parent->type, "for") == 0 || strcmp (parent->type, "repeat") == 0)
        {
            son->left = parent->left + loopIndent;
            son->right = parent->right;
            return;
        }
    if (strcmp (parent->type, "if") == 0)
        if (strcmp(son->type, "else") == 0)
            {
                son->left = (parent->left + parent->right) / 2;
                son->right = parent->right;
                return;
            }
            else
            {
                son->left = parent->left;
                son->right = (parent->left + parent->right) / 2;
                return;
            }
    if (strcmp (parent->type, "function") == 0 || strcmp (parent->type, "procedure") == 0 || strcmp (parent->type, "else") == 0)
        {
            son->left = parent->left;
            son->right = parent->right;
            return;
    }
}

void goThrough()
{
    int i, nivel;
    int scrollOffset=0.15 * screen_height;
    nivel=scrollOffset;
    setbkcolor(COLOR(44, 62, 80));
    drawDiagram(nivel);
    while (true) {
            parcurge(); ///verific daca dau hover peste instructiuni
            if (scrollDownButton(0.92*screen_width, 0.10*screen_height, 0.98*screen_width, 0.16*screen_height) == true)
                {
                    cleardevice();
                    setbkcolor(COLOR(44, 62, 80));
                    scrollOffset-=500;
                    nivel=scrollOffset;
                    drawDiagram(nivel);
                    scrollUpState = scrollDownState = backState = saveState = 0;
                }
            if (scrollUpButton(0.92*screen_width, 0.02*screen_height, 0.98*screen_width, 0.08*screen_height) == true)
                {
                    cleardevice();
                    setbkcolor(COLOR(44, 62, 80));
                    scrollOffset+=500;
                    nivel=scrollOffset;
                    drawDiagram(nivel);
                    scrollUpState = scrollDownState = backState = saveState = 0;
                }
            if (backButton(0.02*screen_height, 0.02*screen_height, 0.08*screen_width, 0.08*screen_height) == true)
                {
                    mainMenu = true;
                    break;
                }
            if (saveButton(0.02*screen_height, 0.10*screen_height, 0.08*screen_width, 0.16*screen_height) == true)
                writeimagefile(NULL, 0.1*screen_width-1, 0, 0.9*screen_width+1, screen_height);
            setbkcolor(COLOR(44, 62, 80));
    }
}

void drawDiagram (int &nivel)
{
    int i;
    setlinestyle(0, 1, 2);
    for (i=0; i<maxIndexOfRoots; i++) {
        line (0.1 * screen_width, nivel, 0.9 * screen_width, nivel);
        nivel = dfs(mainRoots[i], nivel);
        nivel += instructionHeight;
    }
}

int dfs(node *p, int nivel)
{
    int i, nivelNou = nivel;
    char *q;
    q = new char[512];
    *q = 0;
    if (p==NULL)
        return nivel;
    p->nivel1 = nivel;
    if (strcmp (p->type, "instruction") == 0)
       nivelNou = drawInstruction (p->left, p->right, nivelNou, p->expression);
       else
       {
            strcpy (q, p->type);
            strcat (q, " ");
            strcat (q, p->expression);
            if (strcmp (p->type, "while") == 0)
                nivelNou = drawLoop (p->left, p->right, nivelNou, q , 0);
                else
                if (strcmp (p->type, "for") == 0)
                    nivelNou = drawLoop (p->left, p->right, nivelNou, q, 1);
                    else
                    if (strcmp (p->type, "if") == 0)
                        nivelNou = drawIf (p->left, p->right, nivelNou, q);
                        else
                        if (strcmp (p->type, "function") == 0 || strcmp (p->type, "procedure") == 0)
                            nivelNou = drawFunction (p->left, p->right, nivelNou, q);
       }
    if (p->nrOfDescendents == 0) {delete q; p->nivel2 = nivelNou; return nivelNou;}
    for (i=0; i < (p->nrOfDescendents)-1; i++)
        nivelNou = dfs(p->descendents[i], nivelNou);
    if (strcmp (p->descendents[i]->type, "else") == 0)
       nivelNou = max (dfs (p->descendents[i], nivel + ifHeight), nivelNou);
       else
       nivelNou = dfs (p->descendents[i], nivelNou);
    closeInstruction (p, nivel, nivelNou);
    if (strcmp (p->type, "until") == 0)
       nivelNou = drawUntil (p->left, p->right, nivel, nivelNou, q);
    p->nivel2 = nivelNou;
    delete q;
    return nivelNou;
}

void trim(char s[], int st, int dr)
{
    int lg = textwidth(s), nr = strlen(s);
    char c[2]; c[1]=0;
    if (dr-st >= lg) return;
    if (dr-st < 5) {strcpy(s, "..."); return;}
    lg += textwidth("...");
    while (nr && dr-st < lg)
        {
            c[0]=s[nr-1];
            lg -= textwidth(c);
            s[nr-1] = 0;
            nr--;
        }
    strcat(s, "...");
}

void parcurge()
{
    int i;
    for (i=0; i<maxIndexOfRoots; i++)
        dfsHover(mainRoots[i]);
}

bool dfsHover(node *p) ///returneaza 1 daca p apartine/ 0 altfel
{
    int i;
    bool apartine=0; /// apartine este 1 daca mouseul se afla pe un nod din subarborele coresp. lui p/ 0 altfel
    if (p == NULL) return 0;
    for (i=0; i<p->nrOfDescendents; i++)
        if (dfsHover(p->descendents[i]))
            apartine = 1;
    if (strcmp(p->type, "if") == 0)
        {
            if (isInsideIf(p) || apartine)
                apartine = 1;
            if (apartine == 1 && p->isHovered == 0)
                {
                    hoverIf(p, apartine);
                    p->isHovered = 1;
                }
                else
                if (apartine == 0 && p->isHovered == 1)
                    {
                        hoverIf(p, apartine);
                        p->isHovered = 0;
                    }
        }
    if (strcmp(p->type, "for") == 0)
        {
            if (isInsideFor(p)|| apartine)
                apartine = 1;
            if (apartine == 1 && p->isHovered == 0)
                {
                    hoverFor(p, apartine);
                    p->isHovered = 1;
                }
                else
                if (apartine == 0 && p->isHovered == 1)
                    {
                        hoverFor(p, apartine);
                        p->isHovered = 0;
                    }
        }
    if (strcmp(p->type, "while") == 0)
        {
            if (isInsideWhile(p) || apartine)
                apartine = 1;
            if (apartine == 1 && p->isHovered == 0)
                {
                    hoverWhile(p, apartine);
                    p->isHovered = 1;
                }
                else
                if (apartine == 0 && p->isHovered == 1)
                    {
                        hoverWhile(p, apartine);
                        p->isHovered = 0;
                    }
        }
    if (strcmp(p->type, "until") == 0)
        {
            if (isInsideUntil(p) || apartine)
                apartine = 1;
            if (apartine == 1 && p->isHovered == 0)
                {
                    hoverUntil(p, apartine);
                    p->isHovered = 1;
                }
                else
                if (apartine == 0 && p->isHovered == 1)
                    {
                        hoverUntil(p, apartine);
                        p->isHovered = 0;
                    }
        }
    if (strcmp(p->type, "instruction") == 0)
        {
            if (isInsideInstruction(p) || apartine)
                apartine = 1;
            if (apartine == 1 && p->isHovered == 0)
                {
                    hoverInstruction(p, apartine);
                    p->isHovered = 1;
                }
                else
                if (apartine == 0 && p->isHovered == 1)
                    {
                        hoverInstruction(p, apartine);
                        p->isHovered = 0;
                    }
        }
    if (strcmp(p->type, "function") == 0|| strcmp(p->type, "procedure") == 0)
        {
            if (isInsideFunction(p) || apartine)
                apartine = 1;
            if (apartine == 1 && p->isHovered == 0)
                {
                    hoverFunction(p, apartine);
                    p->isHovered = 1;
                }
                else
                if (apartine == 0 && p->isHovered == 1)
                    {
                        hoverFunction(p, apartine);
                        p->isHovered = 0;
                    }
        }
    return apartine;
}
