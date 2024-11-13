I>
    2)
        En remplaçant getReal() par .reel et getImaginary() par .imaginaire, le compilateur affiche ce message d'erreur : src/complex.cpp:43:22: error: 'double Complex::reel' is private within this context.
    4)
        Oui, c'est possible d'ajouter un constructeur permettant l'initialisation d'un nombre complexe à partir de son module et de son argument en s'appuyant sur la représentation en corrdonnées polaires de ce complexe. On peut ajouter un constructeur qui prend le module, l'argument de ce complexe avec un 3ème paramètre 
        bool polaire qui sert à différencier ce constructeur de celui qui prend deux doubles pour la partie réelle et imaginaire, c'est-à-dire Complex(double a, double b).
    5)
        Pour autoriser les opérateurs de ce type, le meilleur moyen est de surcharger les opérateurs concernés comme des fonctions non-membres et de définir les versions compatibles avec un type Complex et un type double.
III>
    1)
        La fonction normalized fonctionne comme prévu. Elle crée un nouveau complexe sans modifier l'objet d'origine. On voit bien la création d'un objet temporaire pour le résultat, qui est ensuite détruit après avoir été utilisé.
    2)
        Par référence.
        La fonction rotate modifie correctement le complexe d'origine grâce au passage par référence. L'utilisation d'un objet temporaire montre comment les valeurs sont calculées avant d'être affectées au complexe modifié.
    3)
        La fonction maxModule retourne correctement le complexe ayant le plus grand module. Les copies temporaires montrent comment les objets sont manipulés sans affecter les originaux, ce qui est typique dans les fonctions renvoyant des objets par référence.
    4)
        La fonction racine_nieme fonctionne correctement en utilisant des objets temporaires pour les racines calculées et en les affectant au tableau passé en paramètre. La destruction des objets temporaires montre une bonne gestion de la mémoire et des ressources.
    5)
        ### Explications Ligne par Ligne:
            +++Complex(0, 0) @ ... : Création de `z1`.
            +++Complex(1, 1) @ ... : Création de `z2`.
            +++Complex(2, 2) @ ... : Création de `z3`.
            Calling foo() : Appel de la fonction `foo`.
            rrrComplex(1+i1) @ ... : Copie du paramètre `b` dans `foo`.
            rrrComplex(0+i0) @ ... : Copie du paramètre `a` dans `foo`.
            +++Complex(10, 10) @ ... : Création de `z` dans `foo`.
            op=Complex(0+i0) @ ... : Affectation de `a` à `z`.
            op=Complex(1+i1) @ ... : Affectation de `b` à `z`.
            op=Complex(1+i1) @ ... : Retour de `foo` dans `z3`.
            ---Complex(1+i1) @ ... : Destruction de `z` dans `foo`.
            ---Complex(0+i0) @ ... : Destruction de la copie de `a`.
            ---Complex(1+i1) @ ... : Destruction de la copie de `b`.
            End of main() : Fin de la fonction `main`.
            Destruction des Objets** : Destruction des objets `z3`, `z2`, et `z1` dans `main`.
        ### Conclusion:
            Chaque ligne de la trace montre clairement le cycle de vie des objets, avec les créations, copies, affectations et destructions explicites. Cette observation permet de mieux comprendre le comportement des constructeurs et des destructeurs en C++.