# Générateur de fichiers audio à partir de notes musicales

Ce projet permet de générer un fichier audio en format WAV à partir d'un fichier texte contenant une séquence de notes musicales. Chaque note est associée à une fréquence spécifique et la durée de chaque note est calculée en fonction du bpm.

## Fonctionnalités

- Lire un fichier texte contenant une séquence de notes et un tempo (BPM).
- Générer une onde sinusoïdale pour chaque note musicale.
- Créer un fichier audio au format WAV basé sur les notes lues.
- Supporter un tempo (BPM) qui ajuste la durée de chaque note.

## Format du fichier d'entrée

Le fichier texte d'entrée doit être structuré de la manière suivante :

1. La première ligne doit contenir un entier représentant le tempo (BPM).
2. Les lignes suivantes contiennent les notes musicales séparées par des espaces.

### Exemple de fichier `exemple.txt` :

