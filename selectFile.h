OPENFILENAME ofn; ///Obiectul ofn de tipul struct OPENFILENAME
char szFile[512];

void openDialogue(char s[512]); ///Deschiderea dialogului de selectare a fisierului din windows.h
void pathProcessing(char s[512]);

void openDialogue(char s[512])
{
    ///Initializarea lui ofn
    ZeroMemory(&ofn, sizeof(ofn)); ///Alocarea de memorie pentru ofn
    ofn.lStructSize = sizeof(ofn); ///Lungimea in bytes a structurii
    ofn.hwndOwner = NULL; ///Handle care indica faptul ca fereastra de dialog este independenta fata de orice alta fereastra deschisa
    ofn.lpstrFile = szFile; ///String-ul care va contine calea catre fisier
    ofn.lpstrFile[0] = '\0'; ///Calea initiala este null-a
    ofn.nMaxFile = sizeof(szFile); ///Marimea maxima a unei cai catre un fisier
    ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0"; ///Defineste meniul drop-down din ferestra de dialog care indica ce extensii sunt vizibile
    ofn.nFilterIndex = 2; ///Ce extensie este selectata initial din meniul drop-down de mai sus (TEXT)
    ofn.lpstrFileTitle = NULL; ///Numele fisierului selectat
    ofn.nMaxFileTitle = 0; ///Marimea maxima a numelui unui fisier selectat
    ofn.lpstrInitialDir = NULL; ///Directorul initial al dialogului
    ofn.lpstrTitle = "Select Nassi-Shneiderman Input"; ///Titlul ferestrei de dialog
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; ///Flag-uri care indica faptul ca fisierul cautat trebuie sa existe
    ///Deschiderea dialogului propriu-zis din windows.h
    if (GetOpenFileName(&ofn)) {
        strcpy(s, ofn.lpstrFile); ///Copiez calea obtinuta in parametrul s
        loadStatusState=1;
    } else {
        s[0]='\0';
        loadStatusState=0;
    }
}

void pathProcessing(char s[512])
{
    ///Procesez calea nou obtinuta astfel incat sa poata fi folosita cu fisierele din C
    ///Calea obtinuta este de forma: D:\HDD Storage\Storage\Nassi-Shneiderman\Nassi_Shneiderman_2
    ///Pentru a putea folosi fisiere din C calea trebuie sa fie de forma: D:\\HDD Storage\Storage\Nassi-Shneiderman/Nassi_Shneiderman_2
    if (s[0]=='\0')
        return;
    int lg=strlen(s);
    char d[512];
    s[2]='\0';
    strcpy(d, s);
    ///Codul 92 indica caracterul '\'
    d[2]=92;
    d[3]=92;
    strcat(d, s+3);
    s[2]=92;
    for (int i=lg; i>=0; i--)
        if (d[i]==92)
            {
                d[i]='/';
                break;
            }
    strcpy(s, d); ///Copiez rezultatul final in parametru
}
