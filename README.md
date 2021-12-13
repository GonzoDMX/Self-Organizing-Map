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
To visualize the SOM the following dependencies are required: Python3, Pandas, matplotlib and seaborn

#### Datasets:
Datasets are not included with this repository. You can find datasets at the [UCI Machine Learning Repository](https://archive.ics.uci.edu), I reccomend iris, wine and abalone as agood starting point for tests.
