[![Makefile CI](https://github.com/bts-lasalle-avignon-projets/MP25-T4-PICKOMINO/actions/workflows/makefile.yml/badge.svg)](https://github.com/bts-lasalle-avignon-projets/MP25-T4-PICKOMINO/actions/workflows/makefile.yml) [![Format](https://github.com/bts-lasalle-avignon-projets/MP25-T4-PICKOMINO/actions/workflows/formatCheck.yml/badge.svg)](https://github.com/bts-lasalle-avignon-projets/MP25-T4-PICKOMINO/actions/workflows/formatCheck.yml)

# Mini-projet : Pickomino

- [Mini-projet : Pickomino](#mini-projet--pickomino)
  - [Présentation](#présentation)
  - [Utilisation](#utilisation)
  - [Changelog](#changelog)
    - [Version 2.0](#version-20)
    - [Version 1.1](#version-11)
    - [Version 1.0](#version-10)
  - [TODO](#todo)
  - [Défauts constatés non corrigés](#défauts-constatés-non-corrigés)
  - [Équipe de développement](#équipe-de-développement)

---

## Présentation

[Pickomino](https://www.gigamic.com/jeux-d-ambiance/50-pickomino-4015682252513.html) est un jeu de société stratégique (édité par [Gigamic](https://www.gigamic.com/)) et amusant où les joueurs collectent des dominos en fonction des résultats de leurs lancers de dés.

## Utilisation

```bash
$ make

$ ./pickomino.out
```

![](./images/pickomino.gif)

## Changelog

### Version 2.0

- [x] Ajouter un menu
- [x] Implémenter une intelligence artificielle pour permettre de jouer contre l'ordinateur
- [x] Enregistrer les scores des parties pour un classement
- [x] Lors de la saisie du nombre de joueurs, l'entrée d'un caractère non valide provoque un dysfonctionnement du jeu.

### Version 1.1

- [x] Affiche le gagnant en fin de partie

### Version 1.0

- [x] Saisir le nombre de joueurs et leur nom
- [x] Jouer une partie
- [x] Afficher le déroulement d'une partie

## TODO

- [ ] Ajouter des niveaux de difficultés à l'IA
- [ ] Améliorer l'affichage
- [ ] Ajouter une option "rejouer" à la fin de chaque partie

## Défauts constatés non corrigés

- [ ] Le joueur n°1 ne commence pas lorsque plus de 2 joueurs participent
- [ ] Entrer un caractère incorrect dans le menu fait quitter le programme

## Équipe de développement

- <a href= "https://github.com/clementBernard130">BERNARD Clément</a>
- <a href =https://github.com/ValentinBOUSQUET>BOUSQUET-SOLFRINI Valentin</a>

---
&copy; 2024-2025 LaSalle Avignon
