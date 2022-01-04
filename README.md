# Self-Organizing Map

_Instructions ci-dessous pour exécuter le test_</br>

This is an implementation of a Self-Organizing Map Algorithm written in C.
The program is designed to work with .data format Datasets from the UCI Machine Learning Repository.
These can be found at the following link: https://archive.ics.uci.edu/ml/index.php

## Usage:
```
git clone https://github.com/GonzoDMX/Self-Organizing-Map.git
cd ~/Self-Organizing_Map
make
./som_test <PATH_TO_DATASET>
```

### Note:
To visualize the SOM the following dependencies are required: Python3, Pandas, matplotlib and seaborn

#### Datasets:
Datasets are not included with this repository. You can find datasets at the [UCI Machine Learning Repository](https://archive.ics.uci.edu), I reccomend iris, wine and abalone as agood starting point for tests.

#### Comment exécuter le programme pour l'évaluation
Installer les dépendances : Python 3, matplotlib, Pandas et Seaborn.
1. Compiler le programme :
```
git clone https://github.com/GonzoDMX/Self-Organizing-Map.git
cd ~/Self-Organizing_Map
make
```
2. Télécharger le dataset :
```
curl https://archive.ics.uci.edu/ml/machine-learning-databases/iris/iris.data -o iris.data
```
3. Exécuter le programme :
```
./somap iris.data
```
4. Répondez aux invites de configuration de la carte auto-organisatrice :
	- Entrer **5**,   pour selectionner le 5eme colonne (le colonne avec les noms des fleurs d'iris)
	- Entrer **n**,   pour sélectionner la taille de carte par défaut
	- Entrer **0**,   pour sélectionner le nombre d'itérations automatique (2000)
	- Entrer **0.7**, pour fixer le 'learning rate'
	- Entrer **0**,   pour sélectionner le delai par défaut (une courbe qui s'applique au 'learning rate')
5. Analyser les résultats :
Dans l'affichage du terminal.
- Inactif         = 0
- Iris-setosa     = 1
- Iris-versicolor = 2
- Iris-virginica  = 3</br>
Dans la représentation de la carte thermique.
- Inactif         = bleu foncé
- Iris-setosa     = bleu claire
- Iris-versicolor = jaune
- Iris-virginica  = rouge foncé
