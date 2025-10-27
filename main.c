#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    float x, y, z;
} Vrh;

typedef struct {
    float normal[3];       
    Vrh vrh[3];            
    unsigned short boja;   
} Trokut;

typedef struct {
    Trokut* trokuti;
    int broj_trokuta;
} Objekt3D;

Objekt3D* ucitajBinSTL(char* naziv) {
    FILE* f = fopen(naziv, "rb");
    if (!f) return NULL;

    fseek(f, 80, SEEK_SET);

    int broj;
    fread(&broj, sizeof(int), 1, f);

    Objekt3D* obj = malloc(sizeof(Objekt3D));
    obj->broj_trokuta = broj;
    obj->trokuti = malloc(broj * sizeof(Trokut));

    for (int i = 0; i < broj; i++) {
        fread(obj->trokuti[i].normal, sizeof(float), 3, f);
        fread(&obj->trokuti[i].vrh, sizeof(Vrh), 3, f);
        fread(&obj->trokuti[i].boja, sizeof(short), 1, f);
    }

    fclose(f);
    return obj;
}

void zapisiBinSTL(char* naziv, Objekt3D* obj) {
    FILE* f = fopen(naziv, "wb");
    if (!f) return;

    char header[80] = { 0 };
    fwrite(header, 1, 80, f);
    fwrite(&obj->broj_trokuta, sizeof(int), 1, f);

    for (int i = 0; i < obj->broj_trokuta; i++) {
        fwrite(obj->trokuti[i].normal, sizeof(float), 3, f);
        fwrite(&obj->trokuti[i].vrh, sizeof(Vrh), 3, f);
        fwrite(&obj->trokuti[i].boja, sizeof(short), 1, f);
    }

    fclose(f);
}

void zapisiTxtSTL(char* naziv, Objekt3D* obj,char* ime) {
    FILE* f = fopen(naziv, "w");
    if (!f) return;

    fprintf(f, "solid %s\n", ime);

    for (int i = 0; i < obj->broj_trokuta; i++) {
        Trokut t = obj->trokuti[i];
        fprintf(f, "  facet normal %f %f %f\n", t.normal[0], t.normal[1], t.normal[2]);
        fprintf(f, "    outer loop\n");
        for (int j = 0; j < 3; j++)
            fprintf(f, "      vertex %f %f %f\n", t.vrh[j].x, t.vrh[j].y, t.vrh[j].z);
        fprintf(f, "    endloop\n");
        fprintf(f, "  endfacet\n");
    }

    fclose(f);
}

void obrisiObjekt3D(Objekt3D* obj) {
    if (!obj) return;
    free(obj->trokuti);
    free(obj);
}

int main() {
    Objekt3D* obj = ucitajBinSTL("primjerbin.stl");
    if (!obj) {
        printf("Neuspjelo čitanje STL datoteke!\n");
        return 1;
    }

    printf("Ucitano %d\n", obj->broj_trokuta);

    zapisiBinSTL("kopija_bin.stl", obj);
    zapisiTxtSTL("kopija_txt.stl", obj, "kopija");

    obrisiObjekt3D(obj);
    
    return 0;
}
