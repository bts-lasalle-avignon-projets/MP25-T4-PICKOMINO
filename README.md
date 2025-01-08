[![Makefile CI](https://github.com/bts-lasalle-avignon-projets/MP25-T4-PICKOMINO/actions/workflows/makefile.yml/badge.svg)](https://github.com/bts-lasalle-avignon-projets/MP25-T4-PICKOMINO/actions/workflows/makefile.yml) [![Format](https://github.com/bts-lasalle-avignon-projets/MP25-T4-PICKOMINO/actions/workflows/formatCheck.yml/badge.svg)](https://github.com/bts-lasalle-avignon-projets/MP25-T4-PICKOMINO/actions/workflows/formatCheck.yml)

# Mini-projet : Pickomino

- [Mini-projet : Pickomino](#mini-projet--pickomino)
  - [Présentation](#présentation)
  - [Utilisation](#utilisation)
  - [Changelog](#changelog)
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

### Version 1.1

- [x] Affiche le gagnant en fin de partie

### Version 1.0

- [x] Saisir le nombre de joueurs et leur nom
- [x] Jouer une partie
- [x] Afficher le déroulement d'une partie

## TODO

- [ ] Ajouter un menu
- [ ] Implémenter une intelligence artificielle pour permettre de jouer contre l'ordinateur
- [ ] Enregistrer les scores des parties pour un classement

## Défauts constatés non corrigés

- [ ] Lors de la saisie du nombre de joueurs, l'entrée d'un caractère non valide provoque un dysfonctionnement du jeu.

## Équipe de développement

- <a href= "https://github.com/clementBernard130">BERNARD Clément</a>
- <a href =https://github.com/ValentinBOUSQUET>BOUSQUET-SOLFRINI Valentin</a>

---
&copy; 2024-2025 LaSalle Avignon
