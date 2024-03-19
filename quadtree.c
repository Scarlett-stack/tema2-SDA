/*BANU DARIA-315CC*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
struct pixel
{

    unsigned char red;
    unsigned char green;
    unsigned char blue;
};
struct Quadtree
{
    int arie_patrat; // are val diferita la decompreseie
    unsigned long long int value_mean;
    unsigned char tip_nod;
    unsigned char value_red;
    unsigned char value_green;
    unsigned char value_blue;
    struct Quadtree *top_left;
    struct Quadtree *top_right;
    struct Quadtree *down_right;
    struct Quadtree *down_left;
};
struct queue
{
    unsigned char tip;
    struct Quadtree *nod;
    struct Quadtree **v_copii;
    struct queue *next;
};
void freematrix(struct pixel **matrix, int width);
void freeq(struct queue *sant);
void freeQuadTree(struct Quadtree *cap);
void build_image(struct pixel **matrix2, int width, FILE *h);
void colorez_in_matrice(struct pixel **matrix2, struct Quadtree *root, int *frunze, int x, int y, int l);
void addc(struct queue *sant, struct Quadtree *node);
struct queue *read_decompress(struct queue *q, FILE *f, int l, int *h, int *fr, int *tt);
void printNivCurent(struct Quadtree *root, int h, FILE *g);
void printLvl(struct Quadtree *root, int h, FILE *g, int width);
int areamax(struct Quadtree *root, int *max);
struct Quadtree *build_tree(struct pixel **matrix, int factor, int *minsize, int *niv, int size, int x, int y, int *frunze);
int main(int argc, char *argv[])
{

    if (strcmp(argv[1], "-c1") == 0)
    {
        FILE *f = fopen(argv[argc - 2], "rb");
        char form[3];
        int colormax;
        int width, height;
        int i;
        fscanf(f, "%s", form);
        fscanf(f, "%d ", &width);
        fscanf(f, "%d\n", &height);
        fscanf(f, "%d", &colormax);
        printf("%s %d %d %d", form, width, height, colormax);
        char gunoi;
        fread(&gunoi, sizeof(char), 1, f);

        struct pixel **matrix = malloc(height * sizeof(struct pixel *));
        for (i = 0; i < height; i++)
        {
            matrix[i] = malloc(sizeof(struct pixel) * width);
            fread(matrix[i], sizeof(struct pixel), width, f);
        }
        fclose(f);

        int factor = atoi(argv[2]);
        printf("cine e factor %d", factor);
        FILE *g = fopen(argv[argc - 1], "wt");
        /* int j;
         for (i = 0; i < height; i++)
         {
             for (j = 0; j < width; j++)
                 fprintf(g, "%d %d %d * ", matrix[i][j].red, matrix[i][j].green, matrix[i][j].blue);
             fprintf(g, "\n");
         }*/
        struct Quadtree *root;
        int minsize = width;
        int niv = 1;
        int frunze = 0;
        root = build_tree(matrix, factor, &minsize, &niv, width, 0, 0, &frunze);
        // printf("ce inaltime am: %d\n", niv);
        printf("cate frunze am: %d\n", frunze);
        int m = 0;
        //int lmax = (int)sqrt(areamax(root, &m));
        // printf("ce areamxa am %d\n", lmax);
        fprintf(g, "%d\n", niv);
        fprintf(g, "%d\n", frunze);
        fprintf(g, "%d\n", (int)sqrt(areamax(root, &m)));
        fclose(g);
        freeQuadTree(root);
        freematrix(matrix, width);
    }
    if (strcmp(argv[1], "-c2") == 0)
    {
        FILE *f = fopen(argv[argc - 2], "rb");
        char form[3];
        int colormax;
        int width, height;
        int i;
        fscanf(f, "%s", form);
        fscanf(f, "%d ", &width);
        fscanf(f, "%d\n", &height);
        fscanf(f, "%d", &colormax);
        printf("%s %d %d %d", form, width, height, colormax);
        char gunoi;
        fread(&gunoi, sizeof(char), 1, f);

        struct pixel **matrix = malloc(height * sizeof(struct pixel *));
        for (i = 0; i < height; i++)
        {
            matrix[i] = malloc(sizeof(struct pixel) * width);
            fread(matrix[i], sizeof(struct pixel), width, f);
        }
        fclose(f);

        int factor = atoi(argv[2]);
        printf("cine e factor %d", factor);
        FILE *g = fopen(argv[argc - 1], "wb");
        struct Quadtree *root; // il pun in main sa nu ma complic cu void
        int minsize = width;
        int niv = 1;
        int frunze = 0;
        root = build_tree(matrix, factor, &minsize, &niv, width, 0, 0, &frunze);
        // printf("ce inaltime am: %d\n", niv);
        // printf("cate frunze am: %d\n", frunze);
        //int m = 0;
        //int lmax = (int)sqrt(areamax(root, &m));
        // printf("ce areamxa am %d\n", lmax);
        printLvl(root, niv, g, width);
        fclose(g);
        freematrix(matrix, width);
        freeQuadTree(root);
    }
    if (strcmp(argv[1], "-d") == 0)
    {

        FILE *f = fopen(argv[argc - 2], "rb");

        unsigned int latura;

        struct Quadtree *root;

        struct queue *head_copyq;

        struct queue *q = calloc(1, sizeof(struct queue)); // coada pt parinti
        q->next = NULL;

        fread(&latura, sizeof(latura), 1, f);
        printf("arie %d\n", latura);

        struct pixel **matrix2 = malloc(latura * sizeof(struct pixel *));
        int i;
        for (i = 0; i < latura; i++)
            matrix2[i] = malloc(latura * sizeof(struct pixel));

        int h, fr, tt;

        head_copyq = read_decompress(q, f, latura, &h, &fr, &tt);

        if (tt == 1)
        {
            printf("din tt 1: %d\n", head_copyq->nod->tip_nod);
            root = head_copyq->nod;
        }

        else
        {
            root = head_copyq->next->nod; // sper sa mearga manifesta intens
        }

        /*int altah = Depth(root);
         printf("alth : %d\n", altah);

         printf("inaltimea %d frunze %d total: funct %d\n", h, fr, tt);
         struct queue *d = head_copyq->next;
         printf("%d", d->tip);

         while (d != NULL)
         {
             printf("tip din main: %d\n", d->tip);
             printf("copii nodului curent : ");
             for (int i = 0; i < 4; i++)
                 printf(" %d ", d->v_copii[i]->tip_nod);
             printf(" latra : %d\n", d->nod->arie_patrat);
             printf("\n");
             d = d->next;
         }*/
        // trebuie verifict daca e doar un nod in arbore altfel ai seg fault
        FILE *fileh = fopen(argv[argc - 1], "wb");

        if (tt == 1)
        {
            int i, j;
            for (i = 0; i < latura; i++)
            {
                for (j = 0; j < latura; j++)
                {
                    matrix2[i][j].red = root->value_red;
                    matrix2[i][j].green = root->value_green;
                    matrix2[i][j].blue = root->value_blue;
                }
            }
            build_image(matrix2, latura, fileh);
        }
        else
        {
            colorez_in_matrice(matrix2, root, &fr, 0, 0, latura);

            build_image(matrix2, latura, fileh);
        }

        // am coada de parinti cu copii lor a trebui sa fac arborele acu
        // iau coada fac 2 functii una de build si una de insert vad daca merge asa sper ca da
        // printf("ce latura am: %d\n",latura);
        // printf("ce adancime : %d si tip %hhu\n", root->top_left->arie_patrat, root->top_left->tip_nod);
        // printf("ce culoare %hhu\n",root->top_left->value_red);
        // printf("e null? %d",root->top_left->top_left->top_left->top_left->top_left->arie_patrat);
        fclose(f);
        // free(q); //invalid read???
        freematrix(matrix2, latura);
        freeq(head_copyq);
        freeQuadTree(root);
    }
    return 0;
}
void build_image(struct pixel **matrix2, int width, FILE *h)
{

    fprintf(h, "P6\n");
    fprintf(h, "%d %d\n", width, width);
    int max = 255;
    fprintf(h, "%d\n", max);
    int i;
    for (i = 0; i < width; i++)
    {
        fwrite(matrix2[i], sizeof(struct pixel), width, h);
    }
    fclose(h);
}
void colorez_in_matrice(struct pixel **matrix2, struct Quadtree *root, int *frunze, int x, int y, int l)
{
    if (l == 0 || (*frunze <= 0))
        return;

    if (root->top_left == NULL && root->top_right == NULL && root->down_right == NULL && root->down_left == NULL) // e frunza
    {
        int i, j;
        for (i = x; i < x + l; i++)
        {
            for (j = y; j < y + l; j++)
            {
                matrix2[i][j].red = root->value_red;
                matrix2[i][j].green = root->value_green;
                matrix2[i][j].blue = root->value_blue;
            }
        }

        (*frunze) = (*frunze) - 1;
    }
    else
    {
        colorez_in_matrice(matrix2, root->top_left, frunze, x, y, l / 2);
        colorez_in_matrice(matrix2, root->top_right, frunze, x, y + l / 2, l / 2);
        colorez_in_matrice(matrix2, root->down_left, frunze, x + l / 2, y, l / 2);
        colorez_in_matrice(matrix2, root->down_right, frunze, x + l / 2, y + l / 2, l / 2);
    }
}
void freeQuadTree(struct Quadtree *cap)
{
    if (cap == NULL)
        return;

    freeQuadTree(cap->top_left);
    freeQuadTree(cap->top_right);
    freeQuadTree(cap->down_right);
    freeQuadTree(cap->down_left);

    free(cap);
    // cap = NULL;
}
void addc(struct queue *sant, struct Quadtree *node)
{

    if (sant->next == NULL)
    {
        sant->next = calloc(1, sizeof(struct queue));
        sant->next->next = NULL;
        sant->next->tip = node->tip_nod; // trb sa fie doar 0
        sant->next->nod = node;
        sant->next->v_copii = malloc(4 * sizeof(struct Quadtree *));
        // printf("sant next: tip %d\n", sant->next->tip);
    }
    else
    {
        struct queue *c = sant->next;
        while (c->next != NULL)
            c = c->next;
        c->next = calloc(1, sizeof(struct queue));
        c->next->tip = node->tip_nod;
        c->next->nod = node;
        c->next->v_copii = malloc(4 * sizeof(struct Quadtree *));
        // for (int i=0; i<=4; i++)
        // c->next->v_copii[i] = malloc(sizeof(struct Quadtree));
        c->next->next = NULL;
        // printf("c next: tip %d\n", c->next->tip);
    }
}
struct queue *read_decompress(struct queue *q, FILE *f, int l, int *h, int *fr, int *tt)
{
    int height = 0;
    int total_noduri = 1; // cu radacina
    int frunze = 0;

    struct Quadtree *root = malloc(sizeof(struct Quadtree));

    fread(&root->tip_nod, sizeof(unsigned char), 1, f);
    //printf("%d\n", root->tip_nod);
    root->arie_patrat = l;
    //printf("%d**\n", root->arie_patrat);
    if (root->tip_nod == 1)
    {
        *tt = 1; // fra asta ai seg fault incearca sa nu ai alzeihmer frt
        fread(&root->value_red, sizeof(unsigned char), 1, f);
        fread(&root->value_green, sizeof(unsigned char), 1, f);
        fread(&root->value_blue, sizeof(unsigned char), 1, f);
        root->top_left = NULL;
        root->top_right = NULL;
        root->down_left = NULL;
        root->down_right = NULL;
        q->nod = root;
        q->tip = 1;
        // struct queue *head_copie = malloc(sizeof(struct queue));
        // head_copie->tip = 1;
        // head_copie->nod = root;
        // return head_copie;
        return q;
    }
    else
    {
        struct queue *head_copie = q;
        l = l / 2;
        addc(head_copie, root);
        q = q->next;
        int cnt = 0;
        unsigned char type;
        while (fread(&type, sizeof(unsigned char), 1, f) == 1)
        {

            total_noduri++;
            struct Quadtree *root1 = malloc(sizeof(struct Quadtree));
            root1->tip_nod = type;
            root1->arie_patrat = l;
            if (root1->tip_nod == 1)
            {
                fread(&root1->value_red, sizeof(unsigned char), 1, f);
                fread(&root1->value_green, sizeof(unsigned char), 1, f);
                fread(&root1->value_blue, sizeof(unsigned char), 1, f);
                root1->top_left = NULL;
                root1->top_right = NULL;
                root1->down_left = NULL;
                root1->down_right = NULL;
                q->v_copii[cnt] = root1; // retin copii primului din coada
                cnt++;
                frunze++;
            } // e de tip 0
            else
            {
                q->v_copii[cnt] = root1;
                cnt++;
                // trb sa il si adaugi ca viitor root
                addc(head_copie, root1);
            }
            // printf("cnt e si tip : %d %d\n",cnt, root1->tip_nod);
            if (cnt == 4) // am 4 copii --trb sa completez creanga
            {
                height = height + 1;
                // printez copii
                /* printf("copii nodului curent : ");
                 for (int i=0; i<4; i++)
                     printf(" %d ", q->v_copii[i]->tip_nod);
                 printf(" latra : %d\n",root1->arie_patrat);
                 printf("\n");*/
                q->nod->top_left = q->v_copii[0];
                q->nod->top_right = q->v_copii[1];
                q->nod->down_right = q->v_copii[2];
                q->nod->down_left = q->v_copii[3];
                q = q->next;
                l = l / 2; // trb sa divid patratul pt urmatorul nivel
                cnt = 0;
            }
        }

        // printf("inaltimea %d frunze %d total: funct %d\n",height,frunze,total_noduri);
        *h = height;
        *fr = frunze;
        *tt = total_noduri;
        // q = head_copie;
        // free(head_copie);
        return head_copie;
    }
}
void printNivCurent(struct Quadtree *root, int h, FILE *g)
{
    if (root == NULL)
        return;
    if (h == 1)
    {
        if (root->tip_nod == 0)
            fwrite(&root->tip_nod, sizeof(root->tip_nod), 1, g);
        else
        {
            fwrite(&root->tip_nod, sizeof(root->tip_nod), 1, g);
            fwrite(&root->value_red, sizeof(root->value_red), 1, g);
            fwrite(&root->value_green, sizeof(root->value_green), 1, g);
            fwrite(&root->value_blue, sizeof(root->value_blue), 1, g);
        }
    }
    else if (h > 1)
    {
        printNivCurent(root->top_left, h - 1, g);
        printNivCurent(root->top_right, h - 1, g);
        printNivCurent(root->down_right, h - 1, g);
        printNivCurent(root->down_left, h - 1, g);
    }
}
void printLvl(struct Quadtree *root, int h, FILE *g, int width)
{
    int i;
    fwrite(&width, sizeof(unsigned int), 1, g); // aici ai avut int dar nu a fost o problema
    for (i = 1; i <= h; i++)
        printNivCurent(root, i, g);
}
int areamax(struct Quadtree *root, int *max)
{
    if (root == NULL)
        return *max;

    if (root->down_left == NULL && root->down_right == NULL && root->top_left == NULL && root->top_right == NULL)
        return root->arie_patrat;
    int m0 = areamax(root->top_left, max);
    int m1 = areamax(root->top_right, max);
    int m2 = areamax(root->down_right, max);
    int m3 = areamax(root->down_left, max);

    if (m0 >= *max)
        *max = m0;
    if (m1 >= *max)
        *max = m1;
    if (m2 >= *max)
        *max = m2;
    if (m3 >= *max)
        *max = m3;
    return *max;
}
struct Quadtree *build_tree(struct pixel **matrix, int factor, int *minsize, int *niv, int size, int x, int y, int *frunze)
{
    struct Quadtree *root = (struct Quadtree *)malloc(sizeof(struct Quadtree));
    unsigned long long int red = 0;
    unsigned long long int green = 0;
    unsigned long long int blue = 0;
    unsigned long long int mean = 0;
    root->arie_patrat = size * size;

    int i, j;
    for (i = x; i < x + size; i++)
        for (j = y; j < y + size; j++)
        {
            red = red + matrix[i][j].red;
            green = green + matrix[i][j].green;
            blue = blue + matrix[i][j].blue;
        }
    red = red / (size * size);
    green = green / (size * size);
    blue = blue / (size * size);
    printf("valorile medii rosu %lld green %lld blue %lld\n", red, green, blue);
    root->value_red = red;
    root->value_green = green;
    root->value_blue = blue;
    for (i = x; i < x + size; i++)
        for (j = y; j < y + size; j++)
        {
            mean = mean + ((red - matrix[i][j].red) * (red - matrix[i][j].red)) + ((green - matrix[i][j].green) * (green - matrix[i][j].green)) + ((blue - matrix[i][j].blue) * (blue - matrix[i][j].blue));
        }
    mean = (unsigned long long int)mean / (3 * size * size);
    root->value_mean = mean;
    printf("din functie mean: %lld si size %d si red %lld green %lld blu %lld \n", root->value_mean, size, red, green, blue);
    if (mean <= factor)
    { 
        (*frunze) = (*frunze) + 1;
        root->tip_nod = 1;
        root->down_left = NULL;
        root->down_right = NULL;
        root->top_left = NULL;
        root->top_right = NULL;
        return root;
    }
    else
    {
        root->tip_nod = 0; // eventual daca va fi frunza se facw 1 in if acela
        if (size / 2 < (*minsize))
        {
            (*niv) = (*niv) + 1;
            (*minsize) = size / 2;
        }
        root->top_left = build_tree(matrix, factor, minsize, niv, size / 2, x, y, frunze);
        root->top_right = build_tree(matrix, factor, minsize, niv, size / 2, x, y + size / 2, frunze);
        root->down_right = build_tree(matrix, factor, minsize, niv, size / 2, x + size / 2, y + size / 2, frunze);
        root->down_left = build_tree(matrix, factor, minsize, niv, size / 2, x + size / 2, y, frunze);
        return root;
    }
}
void freeq(struct queue *sant)
{
    struct queue *aucs;
    while (sant != NULL)
    {
        aucs = sant;
        sant = sant->next;
        free(aucs->v_copii);
        free(aucs);
    }
}
void freematrix(struct pixel **matrix, int width)
{
    int i;
    for (i = 0; i < width; i++)
        free(matrix[i]);
    free(matrix);
}