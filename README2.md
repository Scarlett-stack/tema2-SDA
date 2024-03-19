începem cu verificarea dacă primul argument al introducerii liniei de comandă este „-c1”. Dacă este, programul citește fișierul imagine specificat în penultimul argument al liniei de comandă folosind numele fișierului transmis în vectorul de argument, `argv`.

Programul citește metadatele fișierului, cum ar fi formatul, lățimea, înălțimea și valoarea maximă a culorii, folosind `fscanf()` și le stochează în variabilele corespunzătoare. Metadatele sunt tipărite pe consolă în scopuri de depanare.

Apoi, programul citește datele pixelului din fișier și le stochează într-o matrice 2D alocată dinamic, `matrice`, care este o structură de valori RGB. Fișierul este închis folosind `fclose()` după citire.

Apoi, programul citește al doilea argument transmis în linia de comandă, care este un factor de redimensionare, și îl convertește dintr-un șir într-un număr întreg folosind `atoi()`. Imaginea redimensionată va fi scoasă într-un fișier cu numele specificat în ultimul argument transmis în linia de comandă. Fișierul de ieșire este deschis în modul de scriere folosind `fopen()`.

Programul construiește o structură de date quadtree folosind datele pixelilor stocate în matricea „matrice”. Funcția `build_tree()` creează un quadtree de noduri care reprezintă imaginea. Împarte recursiv imaginea în pătrate mai mici, fiecare dintre acestea fiind reprezentat de un nod în arborele patru. 
minsize calcula cat e cel mai mic patrat
```
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
```

Funcția calculează valorile RGB medii și o valoare medie pentru fiecare pătrat, iar dacă valoarea medie este mai mică decât factorul de redimensionare, pătratul este un nod frunză în arborele patru. Dacă nu, pătratul este împărțit în patru pătrate mai mici, fiecare dintre acestea fiind reprezentat de un nod copil în quadtree.

```
for (i = x; i < x + size; i++)
        for (j = y; j < y + size; j++)
        {
            mean = mean + ((red - matrix[i][j].red) * (red - matrix[i][j].red)) + ((green - matrix[i][j].green) * (green - matrix[i][j].green)) + ((blue - matrix[i][j].blue) * (blue - matrix[i][j].blue));
        }
    mean = (unsigned long long int)mean / (3 * size * size);
```

Programul scrie apoi metadatele imaginii redimensionate, numărul de noduri quadtree și lungimea laterală maximă a frunzelor din quadtree în fișierul de ieșire folosind `fprintf()`. În cele din urmă, quadtree este eliberat folosind funcția `freeQuadTree()`, iar matricea `matrix` este eliberată folosind funcția `freematrix()`.

Funcția `printLvl` preia o rădăcină Quadtree și un întreg h reprezentând înălțimea Quadtree. Acesta scrie valorile nodului `Quadtree` la înălțimea specificată în fișierul de ieșire g. Funcția printNivCurent este o funcție de ajutor recursivă pentru `printLvl` care scrie valorile nodurilor la înălțimea curentă în fișierul de ieșire.

Pentru cea de a treia cerinta iau flagul -d si citesc din fiserul binar compresat. INteresant de remarcat ca intial nu am tratat cazul in care aveam un singur nod si mi-am cam luat sg faulturi la testee 6 si 7. Initial am gandit cerinta asta un pic diferit. Am rut sa impementez o coada pt parinti adoca pt cei de tip 0 si stiam ca urmatori 4 sunt copi lui. 

Dar cum fac asta? Aici a fost un midnfuck de vreo saptamana apoi can m-am apucta deimplementat am observat o chetie smechera. Daca retin coada asta intr-o lista iar in acea lista ma am un vector a carui lungime e sigur 4 de copii? Cireasa de pe tort a fost ca am retinut ca pointeri si asa a fost extrem de usor sa ii leg intre ei.

Nici nu imi imaginez cum ar suna asta cu recursivitate, probabil destul de complicat. Astfel coada asta a cam devenit inutila pentru ca nu scoteam din ea c doar o parcurgeeam si formam legaturile. In orice caz e struto-camila mea si o consider destul de misto mai ales ca nu am alta idee de implementare la chestia asta. Arborele a rezultat foarte usor dupa ce am legat pointerii intre ei, radacina gasindu-se ori in santinela daca are doa un nod copacul ori in sant->next daca avea mai multe noduri (vez var total sau tt)
Inapoi in main returnez capul listei si extrag root din ea.
Apoi e important s averific totalul de noduri and act accordingly. Adica reminder :
```
for (i = 0; i < latura; i++)
            {
                for (j = 0; j < latura; j++)
                {
                    matrix2[i][j].red = root->value_red;
                    matrix2[i][j].green = root->value_green;
                    matrix2[i][j].blue = root->value_blue;
                }
            }
```
atat aici . Daca in schimb are mai multe noduri atunci e necesara recursia deci o functie:
Lasam loc codului sa vorbeasca:
```
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
```
apelulrile sunt exact ca la functia initiala de buildQuadtree 

Apoi in build image pur si simplu scriu matricea in fisierul dat ca ultim argument.
Am luat 80 pe teste si 20 bonus. 