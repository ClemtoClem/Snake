Ce jeu sera différent de l'original. Le serpent commencera avec un taille de 3 blocs. Le terrain sera très grand environ 500 par 500 bloc mais seulement 50 par 50 blocs seront visibles. A début de la partie le programme génèrera des arbres à plusieurs positions. un arbre sera représenté par un cercle vert plein. Les arbres grossirons au fur et à mesure de la partie et prendrons plus de place sur la grille du jeu (3x3 bloc au début et 6x6 bloc à maturité). En fonction du diamètre de son feuillage l'arbre pour générer des pommes qui tomberons à proximité de l'arbre (sur les cases libre de la grille). lorsque le serpent mange une pomme il grandi d'un case. Après 30 seconde fois la taille du serpent, le serpent aura digéré la pomme et déposera en queue des pépins qui seront représenté par des points noir. Les pépins donnerons naissance à un nouvel arbre qui grossira et générera des pommes.

Voici les étapes fonctionnelles du jeu:
- Terrain 500x500 (grille virtuelle, grille légèrement visible, bordure épaisse)
- Vue 50x50 blocs (viewport scrolling automatique autour du serpent)
- Serpent initial taille 3
- Générer initialement en 20 et 50 arbre jeune.
- Arbres représentés par des cercles verts pleins, taille évolutive 3x3 (jeune) → 6x6 (maturité)
- La pousse d'un arbre est lente et augmente plus l'arbre est gros.
- Arbres qui génèrent des pommes qui tombent autour (cases libres) en fonction du périmètre de l'arbre
- Un arbre jeune mettra plus de temps à générer un pomme qu'un arbre à maturité.
- Pomme mangée allonge le serpent d’une case
- Pomme visible dans le corps du serpent et reste visible à la case jusqu’à la queue
- Après passage du serpent sur une pomme mangée, laisse des pépins (points noirs)
- La germination des pépins sera différée entre 30s et 10 minutes, créant un nouvelle arbre

Il faudra gérer:
- Le mouvement contrôlable du serpent
- La collision du serpent avec les obstacles
    - Pomme -> le serpent mange la pomme -> 1+ en taille -> L’apparition des pépins en queue
    - pépins -> l'arbre ne pousse pas temps que le serpent est dessus
    - autre -> fin de la partie