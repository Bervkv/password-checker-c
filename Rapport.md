# Outil de vérification de robustesse des mots de passe
### Rapport à destination d'un dirigeant non technique

## Le problème

La majorité des failles de sécurité en entreprise ne viennent pas d'attaques sophistiquées, mais de mots de passe faibles ou réutilisés. Un employé qui choisit "Entreprise2024!" pense avoir un mot de passe solide : il coche toutes les cases habituelles (majuscule, chiffre, symbole), alors qu'il s'agit en réalité d'un des tout premiers mots de passe qu'un attaquant essaierait, car ce type de schéma est extrêmement courant.

## Ce que fait l'outil

Cet outil analyse un mot de passe et détecte automatiquement ce qu'un simple formulaire de saisie ne peut pas voir :

- **Un mot de passe "qui a l'air fort" mais qui ne l'est pas** : par exemple `p@ssw0rd`, qui semble varié, mais qui est en réalité une variante maquillée de "password", l'un des mots de passe les plus utilisés au monde.
- **Des schémas prévisibles** : répétitions (`aaaa`), suites logiques (`abc123`), que les employés utilisent souvent sans s'en rendre compte.
- **Une correspondance avec les mots de passe déjà connus des attaquants** : comparaison automatique avec une liste de plus de 10 000 mots de passe parmi les plus fréquemment compromis.

## Pourquoi c'est important pour l'entreprise

Un mot de passe compromis est encore aujourd'hui l'une des causes les plus fréquentes d'intrusion informatique, que ce soit pour accéder à une messagerie professionnelle, un système de facturation, ou un poste de contrôle industriel. Renforcer les mots de passe est l'une des mesures de sécurité les moins coûteuses et les plus efficaces qu'une entreprise puisse mettre en place, et cet outil permet de le vérifier concrètement plutôt que de se fier à des règles de formulaire trop simples.

## En résumé

Ce n'est pas un outil qui *impose* des règles, c'est un outil qui *révèle* les angles morts que les règles classiques ("8 caractères, une majuscule, un chiffre") laissent passer. Il peut être intégré à un processus d'intégration des nouveaux employés, à un audit périodique des accès, ou utilisé ponctuellement lors d'un contrôle de sécurité.