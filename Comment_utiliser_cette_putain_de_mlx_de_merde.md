# MiniLibX -- Manuel Développeur Complet (Version Linux X11)

Auteur original : Olivier Crouzet\
Bibliothèque : MiniLibX (MLX)\
Plateforme : Linux (X11)\
Usage : Projets pédagogiques (42 et similaires)

------------------------------------------------------------------------

# Table des matières

1.  Introduction
2.  Architecture X11 et fonctionnement interne
3.  Initialisation de la bibliothèque
4.  Gestion des fenêtres
5.  Dessin direct dans une fenêtre
6.  Gestion avancée des couleurs
7.  Images et buffers mémoire (méthode recommandée)
8.  Gestion complète de la mémoire image
9.  Chargement d'images XPM
10. Boucle d'événements
11. Gestion des hooks (événements)
12. Gestion avancée des événements X11
13. Endianness et représentation mémoire
14. Compilation et linkage
15. Architecture interne de MiniLibX
16. Bonnes pratiques et optimisation
17. Erreurs fréquentes et debugging
18. Tableau récapitulatif des fonctions

------------------------------------------------------------------------

# 1. Introduction

MiniLibX est une bibliothèque graphique minimaliste construite au-dessus
de Xlib (X11).\
Elle permet de créer des fenêtres, dessiner des pixels, manipuler des
images et gérer les événements clavier/souris.

Elle est volontairement simple afin d'obliger le développeur à
comprendre :

-   La mémoire
-   Les buffers graphiques
-   L'architecture événementielle
-   Le rendu logiciel

MiniLibX ne fournit pas :

-   Accélération GPU
-   Double buffering automatique
-   Gestion FPS
-   Thread safety
-   Support PNG/JPEG natif

------------------------------------------------------------------------

# 2. Architecture X11

X11 fonctionne selon un modèle client/serveur.

-   Votre programme = client
-   X Server = serveur graphique

Votre programme envoie des requêtes de dessin. Le serveur envoie des
événements (clavier, souris, expose, fermeture).

La connexion est ouverte via :

``` c
void *mlx_init(void);
```

------------------------------------------------------------------------

# 3. Initialisation

## Prototype

``` c
void *mlx_init(void);
```

## Description

Initialise la connexion avec le serveur X.

## Retour

-   NULL en cas d'échec
-   Un pointeur valide (mlx_ptr) sinon

Ce pointeur est obligatoire pour toutes les autres fonctions.

------------------------------------------------------------------------

# 4. Gestion des fenêtres

## Création

``` c
void *mlx_new_window(void *mlx_ptr, int width, int height, char *title);
```

Crée une fenêtre.

Retour : - NULL si erreur - win_ptr sinon

## Nettoyage

``` c
int mlx_clear_window(void *mlx_ptr, void *win_ptr);
```

Efface la fenêtre (noir).

## Destruction

``` c
int mlx_destroy_window(void *mlx_ptr, void *win_ptr);
```

Libère la fenêtre côté serveur.

------------------------------------------------------------------------

# 5. Dessin direct (méthode lente)

## Pixel

``` c
int mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color);
```

Chaque appel communique avec X11. Très lent → déconseillé pour rendu
temps réel.

Coordonnées : - Origine en haut à gauche - X vers la droite - Y vers le
bas

## Texte

``` c
int mlx_string_put(void *mlx_ptr, void *win_ptr, int x, int y, int color, char *str);
```

Affiche une chaîne de caractères.

------------------------------------------------------------------------

# 6. Gestion des couleurs

Format standard :

    0xRRGGBB

Organisation mémoire (32 bits) :

    | 00 | RR | GG | BB |

Exemple :

``` c
int rouge = 0xFF0000;
int vert  = 0x00FF00;
int bleu  = 0x0000FF;
```

## Conversion serveur

``` c
unsigned int mlx_get_color_value(void *mlx_ptr, int color);
```

Convertit la couleur vers le format du serveur si nécessaire.

------------------------------------------------------------------------

# 7. Images (méthode recommandée)

La bonne pratique consiste à :

1.  Créer une image
2.  Modifier son buffer mémoire
3.  L'afficher en une seule fois

## Création

``` c
void *mlx_new_image(void *mlx_ptr, int width, int height);
```

## Accès aux données

``` c
char *mlx_get_data_addr(
    void *img_ptr,
    int *bits_per_pixel,
    int *size_line,
    int *endian
);
```

Renvoie un pointeur vers la mémoire brute.

Variables remplies :

-   bits_per_pixel
-   size_line (octets par ligne)
-   endian

------------------------------------------------------------------------

# 8. Manipulation mémoire image

Formule d'accès pixel :

``` c
char *dst = addr + (y * size_line + x * (bits_per_pixel / 8));
*(unsigned int *)dst = color;
```

Formule mathématique :

    offset = y * size_line + x * (bits_per_pixel / 8)

## Affichage image

``` c
int mlx_put_image_to_window(
    void *mlx_ptr,
    void *win_ptr,
    void *img_ptr,
    int x,
    int y
);
```

## Destruction

``` c
int mlx_destroy_image(void *mlx_ptr, void *img_ptr);
```

------------------------------------------------------------------------

# 9. Images XPM

MiniLibX supporte partiellement XPM.

## Depuis un fichier

``` c
void *mlx_xpm_file_to_image(
    void *mlx_ptr,
    char *filename,
    int *width,
    int *height
);
```

## Depuis la mémoire

``` c
void *mlx_xpm_to_image(
    void *mlx_ptr,
    char **xpm_data,
    int *width,
    int *height
);
```

Support : - Transparence - Format XPM uniquement

------------------------------------------------------------------------

# 10. Boucle principale

``` c
int mlx_loop(void *mlx_ptr);
```

Ne retourne jamais.

Fonctionnement : - Attend un événement - Appelle le hook associé -
Répète

------------------------------------------------------------------------

# 11. Hooks standards

## Clavier

``` c
int mlx_key_hook(void *win_ptr, int (*f)(), void *param);
```

Prototype callback :

``` c
int key_hook(int keycode, void *param);
```

## Souris

``` c
int mlx_mouse_hook(void *win_ptr, int (*f)(), void *param);
```

Prototype :

``` c
int mouse_hook(int button, int x, int y, void *param);
```

## Expose

``` c
int mlx_expose_hook(void *win_ptr, int (*f)(), void *param);
```

Appelé quand la fenêtre doit être redessinée.

## Loop Hook

``` c
int mlx_loop_hook(void *mlx_ptr, int (*f)(), void *param);
```

Exécuté quand aucun événement n'est en attente.

Utilisé pour : - Animation - Raycasting - Moteur de jeu simple

------------------------------------------------------------------------

# 12. Hook générique X11

``` c
int mlx_hook(void *win_ptr, int event, int mask, int (*f)(), void *param);
```

Exemple fermeture fenêtre :

``` c
mlx_hook(win, 17, 0, close_function, data);
```

17 = DestroyNotify

------------------------------------------------------------------------

# 13. Endianness

Retour de mlx_get_data_addr :

-   0 → little endian
-   1 → big endian

Important si serveur distant.

------------------------------------------------------------------------

# 14. Compilation

## Linux

``` bash
gcc main.c -lmlx -lXext -lX11 -lm
```

## Avec dossier local

``` bash
gcc main.c -Lmlx -lmlx -lXext -lX11
```

------------------------------------------------------------------------

# 15. Architecture interne

MiniLibX encapsule :

-   Display \*
-   Window
-   XImage
-   Colormap

C'est un wrapper léger autour de Xlib.

------------------------------------------------------------------------

# 16. Bonnes pratiques

-   Ne jamais utiliser mlx_pixel_put pour du rendu massif
-   Toujours utiliser un buffer image
-   Redessiner entièrement la scène à chaque frame
-   Libérer images et fenêtres proprement
-   Centraliser la structure globale (mlx_ptr, win_ptr, images)

------------------------------------------------------------------------

# 17. Erreurs fréquentes

-   Segfault → mauvais offset mémoire
-   Image noire → oubli mlx_put_image_to_window
-   Écran figé → oubli mlx_loop
-   Fuites mémoire → oubli mlx_destroy_image

------------------------------------------------------------------------

# 18. Tableau récapitulatif

  Catégorie   Fonction
  ----------- -------------------------
  Init        mlx_init
  Fenêtre     mlx_new_window
  Fenêtre     mlx_destroy_window
  Pixel       mlx_pixel_put
  Texte       mlx_string_put
  Image       mlx_new_image
  Image       mlx_get_data_addr
  Image       mlx_put_image_to_window
  Image       mlx_destroy_image
  XPM         mlx_xpm_file_to_image
  Loop        mlx_loop
  Hook        mlx_key_hook
  Hook        mlx_mouse_hook
  Hook        mlx_expose_hook
  Hook        mlx_loop_hook
  Avancé      mlx_hook

------------------------------------------------------------------------

# Conclusion

MiniLibX est volontairement minimaliste. Elle impose la compréhension
: - De la mémoire - Des buffers - De l'architecture événementielle - Du
rendu logiciel

Elle constitue une excellente base pour : - FdF - so_long - fractol -
cub3D - miniRT
