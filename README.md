# 🐚 Simple Shell - hsh

![C](https://img.shields.io/badge/Language-C-blue.svg)
![Shell](https://img.shields.io/badge/Type-Shell-green.svg)
![Holberton](https://img.shields.io/badge/School-Holberton-red.svg)
![Status](https://img.shields.io/badge/Status-Complete-success.svg)

> Un interpréteur de commandes UNIX simple et fonctionnel, développé dans le cadre du programme Holberton School.

**📖 [Guide Interactif Complet du Projet](https://v0-shell-diagram.vercel.app/)**

---

## 📋 Table des matières

- [Description](#-description)
- [Requirements](#-requirements)
- [Installation & Compilation](#-installation--compilation)
- [Fonctionnement](#-fonctionnement)
- [Fonctions utilisées](#-fonctions-utilisées)
- [Architecture du projet](#-architecture-du-projet)
- [Exemples d'utilisation](#-exemples-dutilisation)
- [Man Page](#-man-page)
- [Bugs rencontrés](#-bugs-rencontrés)
- [Tests & Vérifications](#-tests--vérifications)
- [Auteurs](#-auteurs)

---

## 📝 Description

**hsh** est un interpréteur de commandes shell simple, inspiré de `/bin/sh`. Ce projet implémente les fonctionnalités de base d'un shell UNIX, capable de :

- ✅ Exécuter des commandes depuis le PATH
- ✅ Gérer les chemins absolus et relatifs
- ✅ Implémenter les commandes intégrées (`exit`, `env`)
- ✅ Fonctionner en mode interactif et non-interactif
- ✅ Gérer correctement la mémoire (sans fuites)
- ✅ Afficher des messages d'erreur formatés

Ce projet a été réalisé dans le cadre du cursus **Holberton School** et met en œuvre des concepts fondamentaux de la programmation système en C :
- Création et gestion de processus (`fork`, `execve`, `wait`)
- Manipulation de variables d'environnement
- Parsing et traitement de chaînes de caractères
- Gestion dynamique de la mémoire

---

## ⚙️ Requirements

### General

- **Éditeurs autorisés** : `vi`, `vim`, `emacs`
- **Système d'exploitation** : Ubuntu 20.04 LTS
- **Compilateur** : `gcc` avec les options `-Wall -Werror -Wextra -pedantic -std=gnu89`
- **Style de code** : Betty style
- **Contraintes** :
  - Tous les fichiers doivent se terminer par une nouvelle ligne
  - Maximum de **5 fonctions par fichier**
  - Pas de fuites mémoire
  - Un fichier `README.md` obligatoire
  - Tous les fichiers d'en-tête doivent avoir des include guards

### Output

Le programme doit produire **exactement** la même sortie que `/bin/sh`, y compris les messages d'erreur. La seule différence est le nom du programme qui doit correspondre à `argv[0]`.

**Exemple d'erreur** :
```bash
$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
```

---

## 🛠️ Installation & Compilation

### Cloner le repository
```bash
git clone https://github.com/votre-repo/simple_shell.git
cd simple_shell
```

### Compilation
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

### Vérifier la compilation
```bash
ls -l hsh
./hsh
```

---

## 🚀 Fonctionnement

### Mode Interactif

Le shell affiche un prompt `($) ` et attend une commande de l'utilisateur :

```bash
$ ./hsh
($) ls
AUTHORS  README.md  hsh  main.c  shell.h
($) pwd
/home/user/simple_shell
($) exit
$
```

### Mode Non-Interactif

Le shell lit les commandes depuis l'entrée standard sans afficher de prompt :

```bash
$ echo "ls" | ./hsh
AUTHORS  README.md  hsh  main.c
```

```bash
$ cat commands.txt | ./hsh
/home/user/simple_shell
AUTHORS  README.md  hsh
```

### Processus d'exécution

1. **Lecture** : Le shell lit une ligne avec `getline()`
2. **Parsing** : La ligne est découpée en arguments avec `strtok()`
3. **Vérification builtin** : Le shell vérifie si c'est une commande intégrée
4. **Recherche PATH** : Si ce n'est pas un builtin, le shell cherche la commande dans PATH
5. **Fork & Exec** : Le shell crée un processus enfant avec `fork()` et exécute la commande avec `execve()`
6. **Wait** : Le processus parent attend la fin de l'enfant avec `wait()`
7. **Retour** : Le shell affiche le prompt et recommence

---

## 📚 Fonctions utilisées

### Tableau des fonctions système et bibliothèque

| Fonction | Type | Description | Utilisation dans le projet |
|----------|------|-------------|----------------------------|
| `fork()` | System Call | Crée un nouveau processus | Créer un processus enfant pour exécuter les commandes |
| `execve()` | System Call | Exécute un programme | Remplacer le processus enfant par la commande à exécuter |
| `wait()` | System Call | Attend la fin d'un processus enfant | Attendre que la commande se termine |
| `getline()` | Library | Lit une ligne depuis stdin | Lire les commandes entrées par l'utilisateur |
| `strtok()` | Library | Découpe une chaîne en tokens | Parser la ligne de commande en arguments |
| `malloc()` | Library | Alloue de la mémoire dynamique | Allouer de l'espace pour les arguments et chemins |
| `free()` | Library | Libère la mémoire allouée | Nettoyer la mémoire après utilisation |
| `access()` | System Call | Vérifie les permissions d'un fichier | Vérifier si un fichier est exécutable |
| `isatty()` | Library | Teste si un descripteur est un terminal | Détecter le mode interactif/non-interactif |
| `printf()` | Library | Affiche du texte formaté | Afficher le prompt et les sorties |
| `fprintf()` | Library | Affiche du texte formaté sur stderr | Afficher les messages d'erreur |
| `perror()` | Library | Affiche un message d'erreur système | Afficher les erreurs système (fork, execve) |
| `exit()` | Library | Termine le programme | Sortir du shell avec un code de retour |
| `strcmp()` | Library | Compare deux chaînes | Vérifier les commandes builtins |
| `strncmp()` | Library | Compare n caractères de deux chaînes | Comparer les noms de variables d'environnement |
| `strlen()` | Library | Calcule la longueur d'une chaîne | Calculer les tailles pour allocation mémoire |
| `strcpy()` | Library | Copie une chaîne | Dupliquer les chemins et arguments |
| `sprintf()` | Library | Formate une chaîne | Construire les chemins complets (dir/command) |
| `fflush()` | Library | Vide un buffer de sortie | Forcer l'affichage du prompt |
| `WIFEXITED()` | Macro | Vérifie si un processus s'est terminé normalement | Vérifier le statut de sortie |
| `WEXITSTATUS()` | Macro | Récupère le code de sortie | Obtenir le code de retour de la commande |

### Variables externes

| Variable | Description | Utilisation |
|----------|-------------|-------------|
| `environ` | Tableau des variables d'environnement | Accéder aux variables comme PATH, HOME, USER |

---

## 🏗️ Architecture du projet

### Structure des fichiers

```
simple_shell/
│
├── shell.h              # Fichier d'en-tête principal
├── main.c               # Point d'entrée et boucle principale
├── builtins.c           # Implémentation des commandes intégrées
├── helpers.c            # Fonctions auxiliaires pour builtins
├── path.c               # Gestion de la recherche dans PATH
├── shell.c              # Exécution des commandes (fork/exec/wait)
├── utils.c              # Parsing et gestion mémoire
├── man_1_simple_shell   # Page de manuel
├── README.md            # Ce fichier
└── AUTHORS              # Liste des auteurs
```

### Détail des fichiers

#### `shell.h`
Fichier d'en-tête contenant :
- Tous les includes nécessaires (`stdio.h`, `stdlib.h`, `unistd.h`, etc.)
- Les prototypes de toutes les fonctions
- Les macros (`MAX_ARGS`)
- La déclaration externe de `environ`

#### `main.c`
- Fonction `main()` : Point d'entrée du programme
- Boucle infinie `while(1)` pour le shell
- Détection du mode interactif avec `isatty()`
- Lecture des commandes avec `getline()`
- Appel des fonctions de parsing et d'exécution
- Gestion du builtin `exit`

#### `utils.c`
- `parse_line()` : Découpe une ligne en tableau d'arguments
- `free_args()` : Libère la mémoire des arguments

#### `builtins.c` & `helpers.c`
- `is_builtin()` : Vérifie si une commande est un builtin
- `execute_builtin()` : Exécute les commandes `exit` et `env`
- `print_environment()` : Affiche toutes les variables d'environnement

#### `path.c`
- `_getenv()` : Récupère la valeur d'une variable d'environnement
- `check_absolute_path()` : Vérifie si c'est un chemin absolu/relatif
- `build_full_path()` : Construit un chemin complet (dir/command)
- `search_in_directories()` : Cherche dans les dossiers de PATH
- `find_in_path()` : Fonction principale de recherche de commande

#### `shell.c`
- `print_command_error()` : Affiche les erreurs de commande introuvable
- `execute_child_process()` : Exécute la commande dans le processus enfant
- `fork_and_execute()` : Crée le processus enfant et attend sa fin
- `execute_command()` : Fonction principale d'exécution

---

## 💻 Exemples d'utilisation

### Mode Interactif

```bash
$ ./hsh
($) /bin/ls
AUTHORS  README.md  builtins.c  helpers.c  hsh  main.c  path.c  shell.c  shell.h  utils.c
($) ls -l
total 64
-rw-r--r-- 1 user user   156 Jan 08 10:00 AUTHORS
-rw-r--r-- 1 user user  8234 Jan 08 12:00 README.md
-rw-r--r-- 1 user user  1234 Jan 08 10:30 builtins.c
...
($) pwd
/home/user/simple_shell
($) echo "Hello, World!"
Hello, World!
($) env
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
HOME=/home/user
USER=holberton
SHELL=/bin/bash
...
($) /bin/echo Holberton School
Holberton School
($) exit
$
```

### Mode Non-Interactif

#### Avec echo
```bash
$ echo "ls" | ./hsh
AUTHORS  README.md  hsh  main.c  shell.h

$ echo "pwd" | ./hsh
/home/user/simple_shell

$ echo "/bin/ls" | ./hsh
AUTHORS  README.md  hsh  main.c
```

#### Avec un fichier
```bash
$ cat test_commands.txt
/bin/ls
pwd
env

$ cat test_commands.txt | ./hsh
AUTHORS  README.md  hsh
/home/user/simple_shell
PATH=/usr/local/bin:/usr/bin:/bin
HOME=/home/user
...
```

#### Test d'erreur
```bash
$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found

$ echo "ls -z" | ./hsh
ls: invalid option -- 'z'
Try 'ls --help' for more information.
```

### Commandes supportées

#### Builtins
- `exit` - Quitte le shell
- `env` - Affiche les variables d'environnement

#### Commandes externes (exemples)
- `ls`, `ls -l`, `ls -la /tmp`
- `pwd`
- `echo "texte"`
- `/bin/ls`, `/bin/pwd` (chemins absolus)
- `./programme` (chemins relatifs)
- Toute commande disponible dans PATH

---

## 📖 Man Page

Une page de manuel complète est disponible dans le fichier `man_1_simple_shell`.

### Visualiser la man page

```bash
man ./man_1_simple_shell
```

ou

```bash
man -l man_1_simple_shell
```

La man page contient :
- Description complète du shell
- Syntaxe des commandes
- Liste des builtins
- Exemples d'utilisation
- Codes de sortie
- Variables d'environnement
- Limitations

---

## 🐛 Bugs rencontrés

Voici quelques bugs que nous avons rencontrés pendant le développement et comment nous les avons résolus :

### 1. **Memory Leak avec getline()**

**Problème** : Après plusieurs commandes, Valgrind détectait une fuite mémoire.

```
==12345== 1,024 bytes in 1 blocks are definitely lost
==12345==    at malloc (vg_replace_malloc.c:309)
==12345==    by getline (iogetline.c:120)
```

**Cause** : La variable `line` allouée par `getline()` n'était jamais libérée.

**Solution** : Ajouter `free(line)` avant de quitter le programme.

```c
// Dans main.c
free(line);
return (exit_status);
```

---

### 2. **Segmentation Fault sur commande vide**

**Problème** : Le shell plantait quand on appuyait sur Entrée sans taper de commande.

```bash
($) 
Segmentation fault (core dumped)
```

**Cause** : `args[0]` était NULL et on essayait de le passer à `strcmp()`.

**Solution** : Vérifier si `args[0]` est NULL avant de continuer.

```c
if (args[0] == NULL)
    return (0);
```

---

### 3. **Erreur de parsing avec espaces multiples**

**Problème** : La commande `"ls    -l"` (avec plusieurs espaces) créait des arguments vides.

**Cause** : `strtok()` ne gérait pas correctement les espaces multiples.

**Solution** : `strtok()` gère déjà ce cas ! Il saute automatiquement les délimiteurs consécutifs.

---

### 4. **PATH non trouvé**

**Problème** : Certaines commandes ne fonctionnaient pas alors qu'elles existaient.

```bash
($) ls
./hsh: 1: ls: not found
```

**Cause** : La fonction `_getenv()` ne cherchait pas correctement dans `environ`.

**Solution** : Vérifier que la comparaison se fait avec `name_len` et le caractère `=`.

```c
if (strncmp(environ[i], name, name_len) == 0 &&
    environ[i][name_len] == '=')
{
    return (environ[i] + name_len + 1);
}
```

---

### 5. **Prompt affiché en mode non-interactif**

**Problème** : Le prompt `($)` s'affichait même avec `echo "ls" | ./hsh`.

**Cause** : Pas de vérification du mode interactif.

**Solution** : Utiliser `isatty(STDIN_FILENO)` pour détecter le mode.

```c
interactive = isatty(STDIN_FILENO);
if (interactive)
    printf("($) ");
```

---

### 6. **Mauvais code de retour**

**Problème** : Le shell retournait toujours 0, même en cas d'erreur.

**Cause** : Le `exit_status` n'était pas mis à jour correctement.

**Solution** : Sauvegarder le statut de la dernière commande réussie dans `last_status`.

```c
if (exit_status != 256)
    last_status = exit_status;
```

---

### 7. **Double free sur command_path**

**Problème** : Erreur double free détectée par Valgrind.

```
==12345== Invalid free() / delete / delete[] / realloc()
```

**Cause** : `command_path` était libéré deux fois : dans l'enfant et dans le parent.

**Solution** : Libérer `command_path` uniquement dans le parent après `wait()`.

```c
// Dans fork_and_execute()
else
{
    wait(&status);
    free(command_path);  // Libérer ici seulement
    // ...
}
```

---

## ✅ Tests & Vérifications

### Tests de mémoire avec Valgrind

Tous nos tests passent **sans fuites mémoire** :

```bash
$ valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./hsh
```

**Résultat** :
```
==12345== HEAP SUMMARY:
==12345==     in use at exit: 0 bytes in 0 blocks
==12345==   total heap usage: 145 allocs, 145 frees, 12,456 bytes allocated
==12345==
==12345== All heap blocks were freed -- no leaks are possible
==12345==
==12345== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

### Test interactif complet

```bash
$ valgrind --leak-check=full ./hsh
($) ls
AUTHORS  README.md  hsh
($) pwd
/home/user/simple_shell
($) env
PATH=/usr/bin:/bin
HOME=/home/user
($) /bin/echo Test
Test
($) commande_fausse
./hsh: 1: commande_fausse: not found
($) exit
```

**Résultat Valgrind** : ✅ **0 bytes lost**

### Test non-interactif

```bash
$ echo -e "ls\npwd\nenv" | valgrind --leak-check=full ./hsh
```

**Résultat** : ✅ **No leaks possible**

### Tests de edge cases

#### Ligne vide
```bash
$ echo "" | ./hsh
# Aucune erreur
```

#### Commande inexistante
```bash
$ echo "commande_qui_nexiste_pas" | ./hsh
./hsh: 1: commande_qui_nexiste_pas: not found
```

#### Espaces multiples
```bash
$ echo "ls     -l" | ./hsh
# Fonctionne correctement
```

#### EOF (Ctrl+D)
```bash
($) ^D
$
# Sort proprement
```

### Vérification Betty

```bash
$ betty-style.pl *.c *.h
# Aucune erreur de style

$ betty-doc.pl *.c *.h
# Toutes les fonctions sont documentées
```

---

## 👥 Auteurs

Ce projet a été développé par :

- **Valentin Planchon** - [GitHub](https://github.com/ValentinCA28)
- **Maxim Dutruel** - [GitHub](https://github.com/maxim880000)

---

## 📚 Ressources

### Documentation officielle
- [Unix Shell](https://en.wikipedia.org/wiki/Unix_shell)
- [Thompson Shell](https://en.wikipedia.org/wiki/Thompson_shell)
- [Ken Thompson](https://en.wikipedia.org/wiki/Ken_Thompson)

### Man pages importante
- `man_1_simpl shell`


### Guides
- **[Guide Interactif Complet](https://v0-shell-diagram.vercel.app/)** - Explications détaillées du projet
- [Everything you need to know to start coding your own shell](https://intranet.hbtn.io/concepts/64)

---

## 🎓 Objectifs d'apprentissage

À la fin de ce projet, nous sommes capables d'expliquer :

### Questions générales
- ✅ Qui a conçu et implémenté le système d'exploitation Unix original
- ✅ Qui a écrit la première version du shell UNIX
- ✅ Qui a inventé le langage de programmation B (prédécesseur du C)
- ✅ Qui est Ken Thompson

### Concepts techniques
- ✅ Comment fonctionne un shell
- ✅ Qu'est-ce qu'un PID et un PPID
- ✅ Comment manipuler l'environnement du processus actuel
- ✅ Quelle est la différence entre une fonction et un appel système
- ✅ Comment créer des processus
- ✅ Quels sont les trois prototypes de `main`
- ✅ Comment le shell utilise PATH pour trouver les programmes
- ✅ Comment exécuter un autre programme avec `execve`
- ✅ Comment suspendre l'exécution d'un processus jusqu'à ce qu'un de ses enfants se termine
- ✅ Qu'est-ce que EOF / "end-of-file"

---

## 📜 Licence

Ce projet est réalisé dans le cadre du programme **Holberton School**. Il est destiné à des fins éducatives.

---

## 🙏 Remerciements

- **Holberton School** pour le projet et les ressources
- **Les pairs étudiants** pour l'entraide et les tests
- **La communauté open source** pour la documentation et les exemples

---

<div align="center">

**Holberton School - Simple Shell Project**

*Développé avec ❤️ par Valentin Planchon et Maxim Dutruel*

[⬆ Retour en haut](#-simple-shell---hsh)

</div>