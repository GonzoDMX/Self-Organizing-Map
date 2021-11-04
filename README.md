# Self-Organizing Map

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
The feature maps created by this program are simply a distribution of Best Match Units displayed in a table. The node of the Best Match Unit is incremented for each vector in the Dataset that matches with it.
