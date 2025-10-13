#include <stdio.h>
#include <stdlib.h>

// ----------------------
// 1. PODNIZ
// ----------------------
int* podniz(int* niz, int start, int stop) {
    if (start > stop || start < 0) return NULL;

    int duzina = stop - start + 1;
    int* novi = malloc(duzina * sizeof(int));
    if (novi == NULL) return NULL;

    for (int i = 0; i < duzina; i++)
        novi[i] = niz[start + i];

    return novi;
}

// ----------------------
// 2. FILTRIRAJ
// ----------------------
int* filtriraj(int* niz, int n, int th, int* nth) {
    *nth = 0;

    // Prebroji koliko elemenata prolazi filter
    for (int i = 0; i < n; i++)
        if (niz[i] < th)
            (*nth)++;

    int* novi = malloc((*nth) * sizeof(int));
    if (novi == NULL) return NULL;

    int j = 0;
    for (int i = 0; i < n; i++)
        if (niz[i] < th)
            novi[j++] = niz[i];

    return novi;
}

// ----------------------
// 3. PODIJELI
// ----------------------
int** podijeli(int* niz, int n) {
    int** rez = malloc(2 * sizeof(int*));
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

// ----------------------
// MAIN - demonstracija
// ----------------------
int main() {
    int niz[] = { 1, 5, 8, 2, 9, 3, 4, 7 };
    int n = sizeof(niz) / sizeof(niz[0]);

    printf("Originalni niz: ");
    for (int i = 0; i < n; i++) printf("%d ", niz[i]);
    printf("\n\n");

    // 1. Test podniz
    printf("Podniz od 2 do 5: ");
    int* pn = podniz(niz, 2, 5);
    for (int i = 0; i < 4; i++) printf("%d ", pn[i]);
    printf("\n");
    free(pn);

    // 2. Test filtriraj
    int nth;
    int* f = filtriraj(niz, n, 5, &nth);
    printf("Filtrirani (manji od 5): ");
    for (int i = 0; i < nth; i++) printf("%d ", f[i]);
    printf("\n");
    free(f);

    // 3. Test podijeli
    int** dijelovi = podijeli(niz, n);
    printf("Podijeljeni niz: \n");
    printf("Prvi dio: ");
    for (int i = 0; i < n / 2; i++) printf("%d ", dijelovi[0][i]);
    printf("\nDrugi dio: ");
    for (int i = 0; i < n - n / 2; i++) printf("%d ", dijelovi[1][i]);
    printf("\n");

    // Oslobodi memoriju
    free(dijelovi[0]);
    free(dijelovi[1]);
    free(dijelovi);

    return 0;
}
