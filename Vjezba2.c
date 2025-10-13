#include <stdio.h>
#include <stdlib.h>

void ispisi_niz(int *niz, int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", niz[i]);
    printf("\n");
}

int* podniz(int *niz, int start, int stop) {
    if (start > stop || start < 0) return NULL;

    int duzina = stop - start + 1;
    int *novi = malloc(duzina * sizeof(int));
    if (novi == NULL) return NULL;

    for (int i = 0; i < duzina; i++)
        novi[i] = niz[start + i];

    return novi;
}

int* filtriraj(int *niz, int n, int th, int *nth) {
    *nth = 0;

    for (int i = 0; i < n; i++)
        if (niz[i] < th)
            (*nth)++;

    int *novi = malloc((*nth) * sizeof(int));
    if (novi == NULL) return NULL;

    int j = 0;
    for (int i = 0; i < n; i++)
        if (niz[i] < th)
            novi[j++] = niz[i];

    return novi;
}
int** podijeli(int *niz, int n) {
    int **rez = malloc(2 * sizeof(int*));
    if (rez == NULL) return NULL;

    int polovina = n / 2;
    int vel1 = polovina;
    int vel2 = n - polovina;

    rez[0] = malloc(vel1 * sizeof(int));
    rez[1] = malloc(vel2 * sizeof(int));

    if (rez[0] == NULL || rez[1] == NULL) {
        free(rez[0]);
        free(rez[1]);
        free(rez);
        return NULL;
    }

    for (int i = 0; i < vel1; i++)
        rez[0][i] = niz[i];
    for (int i = 0; i < vel2; i++)
        rez[1][i] = niz[polovina + i];

    return rez;
}
int main() {
    int niz[] = {1, 5, 8, 2, 9, 3, 4, 7};
    int n = sizeof(niz) / sizeof(niz[0]);
    
    // 1. 
    printf("Podniz od 2 do 5: ");
    int *pn = podniz(niz, 2, 5);
    ispisi_niz(pn, 4);
    free(pn);

    // 2. 
    int nth;
    int *f = filtriraj(niz, n, 5, &nth);
    printf("Filtrirani (manji od 5): ");
    ispisi_niz(f, nth);
    free(f);

    // 3. 
    int **dijelovi = podijeli(niz, n);
    printf("Podijeljeni niz:\n");
    printf("Prvi dio: ");
    ispisi_niz(dijelovi[0], n / 2);
    printf("Drugi dio: ");
    ispisi_niz(dijelovi[1], n - n / 2);

    free(dijelovi[0]);
    free(dijelovi[1]);
    free(dijelovi);

    return 0;
}


