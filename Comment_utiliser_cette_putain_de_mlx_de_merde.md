MiniLibX – Manuel Développeur Complet

Version Linux (X11)
Auteur original : Olivier Crouzet
Bibliothèque minimale graphique pour projets pédagogiques

Table des matières

Architecture générale

Initialisation

Gestion des fenêtres

Dessin direct

Gestion des images (buffer mémoire)

Gestion des couleurs

Chargement XPM

Boucle événementielle

Hooks d’événements

Hook générique X11

Architecture interne (fonctionnement bas niveau)

Modèle mémoire des images

Gestion endian

Compilation et linking

Limitations connues

Tableau complet des fonctions

1. Architecture générale

MiniLibX est un wrapper minimal autour de Xlib (X11).

Elle fournit :

Gestion connexion serveur X

Création de fenêtres

Dessin pixel

Images mémoire

Gestion événements clavier/souris

Accès partiel aux événements X11

Elle ne fournit pas :

Primitive graphique avancée

Double buffering automatique

Gestion FPS

Pipeline graphique

Accélération GPU directe

2. Initialisation
mlx_init
void *mlx_init(void);

Description

Initialise la connexion vers le serveur X.

Retour

NULL si échec

pointeur interne de contexte (mlx_ptr)

Rôle interne

Appel XOpenDisplay

Création contexte interne MLX

Initialisation structures internes

3. Gestion des fenêtres
mlx_new_window
void *mlx_new_window(void *mlx_ptr, int width, int height, char *title);

Description

Crée une fenêtre X11.

Paramètres
Paramètre	Description
mlx_ptr	Contexte MLX
width	Largeur
height	Hauteur
title	Titre fenêtre
Retour

NULL si échec

pointeur fenêtre (win_ptr)

mlx_clear_window
int mlx_clear_window(void *mlx_ptr, void *win_ptr);


Efface la fenêtre en noir.

mlx_destroy_window
int mlx_destroy_window(void *mlx_ptr, void *win_ptr);


Détruit la fenêtre X11 associée.

4. Dessin direct
mlx_pixel_put
int mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color);

Description

Dessine un pixel via XDrawPoint.

Limitation

Chaque appel = communication X11 → lent.

mlx_string_put
int mlx_string_put(void *mlx_ptr, void *win_ptr, int x, int y, int color, char *str);


Affiche texte via XDrawString.

5. Gestion des images (mode recommandé)
mlx_new_image
void *mlx_new_image(void *mlx_ptr, int width, int height);


Crée un buffer image côté client.

mlx_get_data_addr
char *mlx_get_data_addr(
    void *img_ptr,
    int *bits_per_pixel,
    int *size_line,
    int *endian
);

Retour
Variable	Description
bits_per_pixel	Profondeur (souvent 32)
size_line	Octets par ligne
endian	0 = little, 1 = big

Retourne pointeur brut vers buffer mémoire.

Accès pixel mémoire
char *pixel;

pixel = addr + (y * line_len + x * (bpp / 8));
*(unsigned int *)pixel = color;

mlx_put_image_to_window
int mlx_put_image_to_window(
    void *mlx_ptr,
    void *win_ptr,
    void *img_ptr,
    int x,
    int y
);


Copie le buffer image vers la fenêtre.

mlx_destroy_image
int mlx_destroy_image(void *mlx_ptr, void *img_ptr);


Libère image.

6. Gestion des couleurs

Format standard :

0xRRGGBB


Structure mémoire :

| 0 | R | G | B |

mlx_get_color_value
unsigned int mlx_get_color_value(void *mlx_ptr, int color);


Convertit RGB vers format serveur X.

7. Chargement XPM
mlx_xpm_to_image
void *mlx_xpm_to_image(
    void *mlx_ptr,
    char **xpm_data,
    int *width,
    int *height
);

mlx_xpm_file_to_image
void *mlx_xpm_file_to_image(
    void *mlx_ptr,
    char *filename,
    int *width,
    int *height
);

Notes

Support transparence

Parser XPM interne (non Xpm lib standard)

Support partiel du format

8. Boucle événementielle
mlx_loop
int mlx_loop(void *mlx_ptr);

Fonctionnement interne

Boucle infinie :

while (1)
{
    wait_event();
    dispatch_event();
}


Ne retourne jamais.

9. Hooks d’événements
mlx_key_hook
int mlx_key_hook(void *win_ptr, int (*f)(), void *param);


Prototype :

int key_hook(int keycode, void *param);

mlx_mouse_hook
int mlx_mouse_hook(void *win_ptr, int (*f)(), void *param);


Prototype :

int mouse_hook(int button, int x, int y, void *param);

mlx_expose_hook
int mlx_expose_hook(void *win_ptr, int (*f)(), void *param);


Prototype :

int expose_hook(void *param);

mlx_loop_hook
int mlx_loop_hook(void *mlx_ptr, int (*f)(), void *param);


Appelé lorsqu’aucun événement n’est en attente.

Utilisé pour moteurs temps réel.

10. Hook générique X11
mlx_hook
int mlx_hook(
    void *win_ptr,
    int event,
    int mask,
    int (*f)(),
    void *param
);


Permet d’intercepter tout événement X11.

Exemple fermeture Linux :

mlx_hook(win, 17, 0, close, data);

11. Architecture interne MLX

Internellement :

mlx_ptr contient :

Display*

Screen*

Root window

Colormap

Les images sont des XImage

Les fenêtres sont des Window X11

MLX est un wrapper léger.

12. Modèle mémoire image

Mémoire linéaire :

addr
↓
[ pixel ][ pixel ][ pixel ] ...


Offset calcul :

offset = y * size_line + x * (bpp / 8)

13. Endian

endian retourné par mlx_get_data_addr :

0 → little endian

1 → big endian

Important si :

Machine ≠ serveur X

Profondeur ≠ 32 bits

14. Compilation

Linux :

gcc main.c -lmlx -lXext -lX11 -lm


Avec dossier local :

gcc main.c -Lmlx -lmlx -lXext -lX11

15. Limitations

Pas de gestion GPU directe

Pas de primitives géométriques

Pas de double buffer automatique

Pas multi-thread safe

Pas gestion FPS

Pas support PNG/JPEG natif

16. Tableau complet des fonctions
Catégorie	Fonction
Initialisation	mlx_init
Fenêtre	mlx_new_window
Fenêtre	mlx_clear_window
Fenêtre	mlx_destroy_window
Pixel	mlx_pixel_put
Texte	mlx_string_put
Image	mlx_new_image
Image	mlx_get_data_addr
Image	mlx_put_image_to_window
Image	mlx_destroy_image
Couleur	mlx_get_color_value
XPM	mlx_xpm_to_image
XPM	mlx_xpm_file_to_image
Loop	mlx_loop
Hook	mlx_key_hook
Hook	mlx_mouse_hook
Hook	mlx_expose_hook
Hook	mlx_loop_hook
Hook avancé	mlx_hook
Conclusion

MiniLibX est :

Un wrapper minimal X11

Une base pédagogique

Suffisante pour :

FdF

so_long

fractol

cub3D

miniRT

Elle impose de comprendre :

mémoire

buffer

gestion événements

architecture moteur graphique
