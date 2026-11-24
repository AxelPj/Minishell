# Minishell

Bienvenue dans mon repository **Minishell** ! Ce projet consiste à écrire en C un petit interpréteur de commandes inspiré de `bash`. L'objectif est de comprendre ce qui se passe entre la saisie d'une ligne et l'exécution d'un programme : analyse de la ligne, expansion des variables, création de processus, pipes, redirections et gestion des signaux.

## Sommaire

- [À propos](#à-propos)
- [Fonctionnalités](#fonctionnalités)
- [Installation](#installation)
- [Utilisation](#utilisation)
- [Structure du projet](#structure-du-projet)
- [Contributions](#contributions)

## À propos

**Minishell** affiche une invite (`OH MI(ni)SHELL> `), lit la ligne avec `readline` et l'ajoute à l'historique. La ligne passe ensuite par plusieurs étapes :

1. **Vérification de la syntaxe** : quotes, parenthèses, accolades et crochets non fermés, pipes et redirections mal placés.
2. **Normalisation et découpage en tokens** : séparation des mots, des pipes et des redirections, en respectant les quotes.
3. **Expansion** des variables d'environnement (`$VAR`) et du code de retour (`$?`).
4. **Suppression des quotes**.
5. **Exécution** : les commandes sont lancées avec `fork` et `execve`, reliées par des pipes, avec leurs redirections.

Au démarrage, le shell copie l'environnement reçu et ne travaille ensuite que sur cette copie : `env`, `export`, `unset`, `cd` et l'expansion de `$VAR` la lisent ou la modifient, et c'est elle qui est transmise aux programmes lancés. L'environnement de l'ordinateur n'est jamais modifié. Le shell s'appuie sur **libmy**, une bibliothèque de fonctions utilitaires (chaînes, mémoire, affichage), et sur **get_next_line** pour lire les here-docs.

## Fonctionnalités

### 1. Commandes intégrées (built-ins)

- `echo` – Affiche ses arguments ; l'option `-n` (y compris `-nnn`, répétée ou non) supprime le retour à la ligne final.
- `cd` – Change de répertoire ; sans argument ou avec `~`, va dans `HOME` ; `cd -` revient dans `OLDPWD`. Met à jour `PWD` et `OLDPWD`.
- `pwd` – Affiche le répertoire courant.
- `export` – Ajoute ou modifie des variables ; sans argument, affiche l'environnement trié sous la forme `declare -x`. Les noms invalides sont refusés (`not a valid identifier`).
- `unset` – Supprime une ou plusieurs variables de l'environnement.
- `env` – Affiche l'environnement.
- `exit` – Quitte le shell, avec un code de retour optionnel ; un argument non numérique donne `numeric argument required` et le code 2.

### 2. Exécution des commandes externes

- Recherche de l'exécutable dans les dossiers de la variable `PATH`.
- Chemins absolus (`/bin/ls`) et relatifs (`./programme`).
- Messages d'erreur : commande introuvable (code 127), fichier inexistant, dossier, permission refusée.
- Le code de retour de la dernière commande est conservé et disponible avec `$?`.

### 3. Pipes et redirections

- `|` – Relie la sortie d'une commande à l'entrée de la suivante, sur un nombre quelconque de commandes.
- `<` – Redirige l'entrée depuis un fichier (si le fichier n'existe pas, la commande n'est pas lancée et `$?` vaut 1).
- `>` – Redirige la sortie vers un fichier (écrasement).
- `>>` – Redirige la sortie vers un fichier (ajout à la fin).
- `<<` – Here-doc : lit des lignes jusqu'au délimiteur donné.

### 4. Quotes et expansion

- Quotes simples `'...'` : aucun caractère n'est interprété.
- Quotes doubles `"..."` : les variables `$VAR` sont remplacées.
- `$?` est remplacé par le code de retour de la dernière commande.

### 5. Vérification de la syntaxe

Avant toute exécution, la ligne est refusée si elle contient :

- des quotes, parenthèses `()`, accolades `{}` ou crochets `[]` non fermés ;
- un pipe en début ou en fin de ligne, deux pipes à la suite ou `||` ;
- une redirection sans fichier ou suivie d'un autre opérateur.

Un message `syntax error` est alors affiché sur la sortie d'erreur et `$?` vaut 2.

### 6. Signaux et environnement

- `Ctrl-C` affiche une nouvelle invite sans quitter le shell ; dans un here-doc, il l'interrompt (code 130).
- `Ctrl-\` est ignoré par le shell ; les processus enfants retrouvent le comportement par défaut.
- `Ctrl-D` quitte le shell en renvoyant le code de la dernière commande.
- Au démarrage, `SHLVL` est incrémenté et `SHELL` vaut `minishell`.
- Lancé sans environnement (`env -i ./minishell`), le shell crée un environnement minimal : `SHELL`, `PWD`, `OLDPWD` et `SHLVL=1`.

## Installation

Le projet a besoin de la bibliothèque **GNU readline** :

- **Linux** : installez le paquet de développement (`sudo apt install libreadline-dev` sur Debian/Ubuntu).
- **macOS** : la version fournie par le système ne contient pas `rl_replace_line`. Installez GNU readline avec Homebrew (`brew install readline`) ; le Makefile la détecte automatiquement.

```sh
git clone https://github.com/AxelPj/Minishell.git
cd Minishell
make
```

Cette commande compile d'abord la bibliothèque `include/libmy/libmy.a`, puis génère l'exécutable `minishell`. Les fichiers objets sont placés dans le dossier `build/`.

Autres règles disponibles :

```sh
make clean    # supprime les fichiers objets (build/ et ceux de libmy)
make fclean   # supprime aussi l'exécutable et libmy.a
make re       # recompile tout
make debug    # recompile avec -fsanitize=address
```

## Utilisation

Lancez le shell :

```sh
./minishell
```

Quelques exemples de commandes :

```sh
OH MI(ni)SHELL> echo hello world
hello world
OH MI(ni)SHELL> export FOO=bar
OH MI(ni)SHELL> echo $FOO "$FOO" '$FOO'
bar bar $FOO
OH MI(ni)SHELL> ls Makefile | cat -e
Makefile$
OH MI(ni)SHELL> echo test > out.txt
OH MI(ni)SHELL> echo encore >> out.txt
OH MI(ni)SHELL> cat << FIN
> une ligne
> FIN
une ligne
OH MI(ni)SHELL> commande_inconnue
Command 'commande_inconnue' not found.
OH MI(ni)SHELL> echo $?
127
OH MI(ni)SHELL> exit 42
exit
```

Le fichier `rl.supp` permet d'ignorer les fuites internes de `readline` avec Valgrind (Linux) :

```sh
valgrind --leak-check=full --suppressions=rl.supp ./minishell
```

## Structure du projet

- `Makefile` : compile libmy puis minishell (règles `all`, `clean`, `fclean`, `re`, `debug`).
- `rl.supp` : suppressions Valgrind pour les fuites de `readline`.
- `include/header/minishell.h` : structures (`t_data`, `t_pars`, `t_exec`), types de tokens et prototypes du shell.
- `include/GNL/get_next_line.c` : lecture d'un fichier ligne par ligne, utilisée par le here-doc.
- `include/GNL/get_next_line.h` : en-tête de get_next_line.
- `include/libmy/libmy.h` : en-tête de la bibliothèque libmy.
- `include/libmy/Makefile` : compile `libmy.a`.
- `include/libmy/README.md` : documentation de libmy.
- `include/libmy/my_*.c` : un fichier par fonction de libmy (chaînes, mémoire, conversions, affichage sur un descripteur).
- `source/main.c` : boucle principale (invite, historique, enchaînement parsing/exécution) et signaux du shell.
- `source/parsing/syntax_utils/quote_utils.c` : vérification et traitement des quotes.
- `source/parsing/syntax_utils/pipe_utils.c` : erreurs de syntaxe liées aux pipes.
- `source/parsing/syntax_utils/redir_utils.c` : erreurs de syntaxe liées aux redirections.
- `source/parsing/syntax_utils/parens_utils.c` : parenthèses non fermées et vérification globale de la syntaxe.
- `source/parsing/syntax_utils/braces_utils.c` : accolades non fermées.
- `source/parsing/syntax_utils/brackets_utils.c` : crochets non fermés.
- `source/parsing/syntax_utils/delimiteur_utils.c` : repérage des délimiteurs (`|`, `<`, `>`, `<<`, `>>`).
- `source/parsing/input/input_normalizer.c` : ajoute des espaces autour des opérateurs pour faciliter le découpage.
- `source/parsing/input/input_processor.c` : fonctions de jointure utilisées pendant la normalisation.
- `source/parsing/tokenisation/split_modif.c` : découpe la ligne en tokens en respectant les quotes.
- `source/parsing/tokenisation/split_modif_utils.c` : saut des quotes et des mots pendant le découpage.
- `source/parsing/tokenisation/tokenisation.c` : détermine le type de chaque token et construit la liste `t_pars`.
- `source/parsing/expand/expand_var.c` : remplace les variables par leur valeur.
- `source/parsing/expand/split_expand.c` : découpe un token autour des `$` et retire les tokens vides.
- `source/parsing/expand/valid_expand.c` : repère les `$` à développer et les caractères valides d'un nom.
- `source/parsing/expand/expand_utils.c` : récupère la valeur d'une variable dans l'environnement.
- `source/parsing/delete_quote/del_q.c` : supprime les quotes des tokens.
- `source/parsing/export_in_tab/export_in_tab.c` : convertit la liste de tokens en tableaux d'arguments par commande.
- `source/built-in/my_echo.c` : built-in `echo`.
- `source/built-in/my_cd.c` : built-in `cd`.
- `source/built-in/cd_utils.c` : lecture et mise à jour des variables d'environnement pour `cd`.
- `source/built-in/my_pwd.c` : built-in `pwd`.
- `source/built-in/my_export.c` : built-in `export` et affichage trié de l'environnement.
- `source/built-in/export_utils.c` : validation des noms, ajout et mise à jour de variables.
- `source/built-in/my_unset.c` : built-in `unset`.
- `source/built-in/my_env.c` : built-in `env`.
- `source/built-in/my_exit.c` : built-in `exit` et libération de la mémoire avant de quitter.
- `source/built-in/shell_utils.c` : mise à jour de `SHLVL` et `SHELL`.
- `source/exec/main_exec.c` : création des processus enfants et lancement de l'exécution.
- `source/exec/init_exec.c` : initialisation de la structure d'exécution `t_exec`.
- `source/exec/exec_utils.c` : comptage des commandes, code de retour, exécution des built-ins.
- `source/exec/check_builtins.c` : reconnaît les built-ins et les exécute.
- `source/exec/commands.c` : exécution d'une commande externe avec `execve` et messages d'erreur.
- `source/exec/path.c` : recherche de l'exécutable dans `PATH`.
- `source/exec/pipes.c` : création et fermeture des pipes, attente des processus enfants.
- `source/exec/setup_fd.c` : branchement de l'entrée et de la sortie de chaque commande (`dup2`).
- `source/exec/free_exec.c` : libération de la mémoire liée à l'exécution.
- `source/redirections/setup_redir.c` : mise en place des redirections et du here-doc.
- `source/redirections/redir_utils.c` : gestion de chaque type de redirection (`<`, `>`, `>>`, `<<`).
- `source/redirections/redirection.c` : retire les redirections des arguments d'une commande.
- `source/utils/init_data.c` : initialisation de `t_data` et copie (ou création) de l'environnement.
- `source/utils/utils.c` : fonctions utilitaires diverses.
- `source/utils/utils_lst.c` : manipulation de la liste chaînée `t_pars`.
- `source/utils/free.c` : libération des structures du parsing.
- `source/utils/print_utils.c` : affichage des structures, pour le débogage.

## Contributions

Les contributions sont les bienvenues ! Pour proposer une modification :

1. Forker ce repository.
2. Créer une branche : `git checkout -b feature/nouvelle-fonctionnalite`
3. Committer : `git commit -m "Ajout d'une nouvelle fonctionnalité"`
4. Pousser : `git push origin feature/nouvelle-fonctionnalite`
5. Ouvrir une Pull Request.
