#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definición de la estructura para una película
typedef struct Movie {
    char name[100];
    int year;
    char genre[50];
    float revenue;
} Movie;

// Definición del nodo del árbol binario de búsqueda
typedef struct TreeNode {
    Movie movie;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Función para crear un nuevo nodo del árbol
TreeNode* createNode(Movie movie) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->movie = movie;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Función para insertar una película en el árbol binario de búsqueda
TreeNode* insert(TreeNode* root, Movie movie) {
    if (root == NULL) {
        return createNode(movie);
    }

    if (movie.year < root->movie.year || 
       (movie.year == root->movie.year && strcmp(movie.name, root->movie.name) < 0)) {
        root->left = insert(root->left, movie);
    } else {
        root->right = insert(root->right, movie);
    }

    return root;
}

// Función para recorrer el árbol en inorden
void inorder(TreeNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("Nombre: %s, Año: %d, Género: %s, Recaudación: %.2fM\n", 
               root->movie.name, root->movie.year, root->movie.genre, root->movie.revenue);
        inorder(root->right);
    }
}

// Función para recorrer el árbol en preorden
void preorder(TreeNode* root) {
    if (root != NULL) {
        printf("Nombre: %s, Año: %d, Género: %s, Recaudación: %.2fM\n", 
               root->movie.name, root->movie.year, root->movie.genre, root->movie.revenue);
        preorder(root->left);
        preorder(root->right);
    }
}

// Función para recorrer el árbol en posorden
void postorder(TreeNode* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("Nombre: %s, Año: %d, Género: %s, Recaudación: %.2fM\n", 
               root->movie.name, root->movie.year, root->movie.genre, root->movie.revenue);
    }
}

// Función para buscar una película por nombre
TreeNode* searchByName(TreeNode* root, const char* name) {
    if (root == NULL || strcmp(root->movie.name, name) == 0) {
        return root;
    }

    if (strcmp(name, root->movie.name) < 0) {
        return searchByName(root->left, name);
    } else {
        return searchByName(root->right, name);
    }
}

// Función para mostrar todas las películas de un género específico
void showByGenre(TreeNode* root, const char* genre) {
    if (root != NULL) {
        showByGenre(root->left, genre);
        if (strcmp(root->movie.genre, genre) == 0) {
            printf("Nombre: %s, Año: %d, Género: %s, Recaudación: %.2fM\n", 
                   root->movie.name, root->movie.year, root->movie.genre, root->movie.revenue);
        }
        showByGenre(root->right, genre);
    }
}

// Función para encontrar los 3 fracasos taquilleros
void findLowestRevenue(TreeNode* root, Movie* lowest, int* count) {
    if (root != NULL) {
        findLowestRevenue(root->left, lowest, count);
        if (*count < 3) {
            lowest[*count] = root->movie;
            (*count)++;
        }
        findLowestRevenue(root->right, lowest, count);
    }
}

// Función para liberar la memoria del árbol
void freeTree(TreeNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    TreeNode* root = NULL;
    int option;
    char searchName[100], searchGenre[50];

    do {
        printf("\n1. Agregar película\n2. Mostrar inorden\n3. Mostrar preorden\n4. Mostrar posorden\n");
        printf("5. Buscar película por nombre\n6. Mostrar por género\n7. Mostrar 3 fracasos taquilleros\n0. Salir\n");
        printf("Elija una opción: ");
        if (scanf("%d", &option) != 1) { // Validación de entrada
            printf("Entrada inválida. Por favor, ingrese un número.\n");
            while (getchar() != '\n'); // Limpiar el buffer de entrada
            continue;
        }

        switch (option) {
            case 1: {
                Movie movie;
                printf("Ingrese el nombre de la película: ");
                getchar(); // Limpiar el buffer
                fgets(movie.name, sizeof(movie.name), stdin);
                movie.name[strcspn(movie.name, "\n")] = '\0'; // Eliminar salto de línea
                printf("Ingrese el año de realización: ");
                while (scanf("%d", &movie.year) != 1 || movie.year < 0) {
                    printf("Por favor, ingrese un año válido: ");
                    while (getchar() != '\n');
                }
                printf("Ingrese el género: ");
                getchar();
                fgets(movie.genre, sizeof(movie.genre), stdin);
                movie.genre[strcspn(movie.genre, "\n")] = '\0';
                printf("Ingrese la recaudación (en millones): ");
                while (scanf("%f", &movie.revenue) != 1 || movie.revenue < 0) {
                    printf("Por favor, ingrese una recaudación válida: ");
                    while (getchar() != '\n');
                }
                root = insert(root, movie);
                printf("Película agregada correctamente.\n");
                break;
            }
            case 2:
                if (root == NULL) {
                    printf("No hay películas registradas.\n");
                } else {
                    printf("Recorrido inorden:\n");
                    inorder(root);
                }
                break;
            case 3:
                if (root == NULL) {
                    printf("No hay películas registradas.\n");
                } else {
                    printf("Recorrido preorden:\n");
                    preorder(root);
                }
                break;
            case 4:
                if (root == NULL) {
                    printf("No hay películas registradas.\n");
                } else {
                    printf("Recorrido posorden:\n");
                    postorder(root);
                }
                break;
            case 5:
                printf("Ingrese el nombre de la película a buscar: ");
                getchar();
                fgets(searchName, sizeof(searchName), stdin);
                searchName[strcspn(searchName, "\n")] = '\0';
                TreeNode* result = searchByName(root, searchName);
                if (result != NULL) {
                    printf("Película encontrada: Nombre: %s, Año: %d, Género: %s, Recaudación: %.2fM\n", 
                           result->movie.name, result->movie.year, result->movie.genre, result->movie.revenue);
                } else {
                    printf("Película no encontrada.\n");
                }
                break;
            case 6:
                printf("Ingrese el género: ");
                getchar();
                fgets(searchGenre, sizeof(searchGenre), stdin);
                searchGenre[strcspn(searchGenre, "\n")] = '\0';
                if (root == NULL) {
                    printf("No hay películas registradas.\n");
                } else {
                    printf("Películas del género %s:\n", searchGenre);
                    showByGenre(root, searchGenre);
                }
                break;
            case 7: {
                if (root == NULL) {
                    printf("No hay películas registradas.\n");
                } else {
                    Movie lowest[3] = {{0}};
                    int count = 0;
                    findLowestRevenue(root, lowest, &count);
                    printf("Los 3 fracasos taquilleros son:\n");
                    for (int i = 0; i < count; i++) {
                        printf("Nombre: %s, Año: %d, Género: %s, Recaudación: %.2fM\n", 
                               lowest[i].name, lowest[i].year, lowest[i].genre, lowest[i].revenue);
                    }
                }
                break;
            }
            case 0:
                freeTree(root);
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opción inválida.\n");
        }
    } while (option != 0);

    return 0;
}