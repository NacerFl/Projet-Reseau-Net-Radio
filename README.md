# ProjetReseau


ATTENTION OUVRIR LE GESTIONNAIRE AVANT LE DIFFUSEUR SINON LE DIFFUSEUR NE PREND PAS EN COMPTE LE GESTIONNAIRE


Un diffuseur capable de  à la fois :
- De Broadcast sur son port et adresse de multidiffusion
- De recevoir sur son port TCP des messages de type MSG et des requetes de type LAST d'un utilisateur et d'y répondre
- De communiquer en continu avec un Gestionnaire
- Une commande exit qui permet à tout moment de sortir du diffuseur

Un Gestionnaire: (EN JAVA) capable d'enregister un ou plusieurs diffuseurs (grace à des thread et une liste de diffuseurs) et maintenir la connexion avec eux.

Un Utilisateur: capable de communiquer avec un diffuseur de lui envoyer des messages de type MESS et des messages de type LAST, et de recevoir des messages envoyé par le diffuseur

Attention Utilisateur prend en parametre un fichier config.txt qui contient son port et adresse 

Et un MakeFile qui gere les fichiers C et JAVA

Nous avons décidé comme extension de faire le Gestionnaire en JAVA et d'assurer la connexion entre le Diffuseur en C et le Gestionnaire en Java.

## MARCHE À SUIVRE:

> make

>java Gestionnaire < Insérer PORT> //ex: 5555
  
>./Diffuseur
  
>./Utilisateur
  
>./clientmulti //permet d'afficher les message multi diffusés



