#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct {
    int x;
    float y;
} Ponto;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <arquivo.csv>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s\n", argv[1]);
        return 1;
    }

    int count = 0;
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        count++;
    }

    Ponto *pontos = (Ponto *)malloc(count * sizeof(Ponto));
    if (pontos == NULL) {
        printf("Erro ao alocar memória\n");
        fclose(file);
        return 1;
    }

    rewind(file);

    int soma_x = 0;
    float soma_y = 0.0;
    for (int i = 0; i < count; i++) {
        fscanf(file, "%d,%f", &pontos[i].x, &pontos[i].y);
        soma_x += pontos[i].x;
        soma_y += pontos[i].y;
    }
    float media_x = (float)soma_x / count;
    float media_y = soma_y / count;

    float numerador = 0.0;
    float denominador = 0.0;
    for (int i = 0; i < count; i++) {
        numerador += (pontos[i].x - media_x) * (pontos[i].y - media_y);
        denominador += pow((pontos[i].x - media_x), 2);
    }
    float coef_angular = numerador / denominador;

    float coef_linear = media_y - (coef_angular * media_x);

    printf("y = %.2fx + %.2f\n", coef_angular, coef_linear);

    free(pontos);
    fclose(file);

    return 0;
}
