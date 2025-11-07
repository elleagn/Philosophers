# Philosphers

**Sujet**: Introduction au multithreading en C
**Objectif**: Implémenter le problème des philosophes avec gestion de threads et synchronisation.

## Description

Ce projet vise à explorer les bases du multithreading en C. Chaque philosophe est représenté par un thread, et le programme gère les ressources partagées (fourchettes) pour éviter les conflits et les blocages.

## Fonctionnalités principales

- Création et gestion de threads
- Synchronisation des threads pour l'accès aux ressources partagées
- Gestion des conditions de concurrence (mutex).

## Utilisation

Compiler le projet avec : 
```
make
```

Puis lancer avec : 
```
./philosophers number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

## Notes
Ce projet a été réalisé dans le cadre de l'école 42 pour pratiquer le multithreading en C.
