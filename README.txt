FONTIONNEMMENT DE L'APPLICATION :

	PROGRAMME CALCULANT L'ITINÉRAIRE LE PLUS RAPIDE ENTRE UNE STATION DE DÉPART
	ET UNE STATION D'ARRIVÉE TOUTES DEUX SAISIES PAR L'UTILISATEUR.
	FONCTIONNE UNIQUEMENT POUR LES LIGNES DE MÉTRO ! 

COMPILATION:
	On compile en tapant la commande "make" puis on éxécute le fichier main en tapant
	./main "station_depart" "station_arrivee" en remplaçant station_depart et 
	station_arrivee par celles qui sont voulues.
	 
INTERFACE:
	Le programme affiche l'itinéraire optimal, les correspondances s'il y en a 
	ainsi que le temps de trajet estimé.

FICHIERS : 
	connexions.csv : station_départ;station_arrivée;ligne;temps en min
	stations.csv : Nom;Latitude;Longitude
	lignes.csv : Nom,vitesse_rame,intervalle_temps,couleur

NB : 
	Le programme prend en compte le temps des correspondances fixé à 2 min pour toutes les stations, hors
	pour les plus grandes stations comme Gare du Nord, Saint-Lazare ou Chatelet qui elles ont un temps de correspondance 
	de 7 min. Le programme ne prend pas en charge le nombre de correspondances car s'il trouve un chemin plus optimal
	ayant énormément de correspondances, il (le chemin) primera sur les autres chemins.


Auteurs:
AMAIRI Tahar
BERBAGUI Amine
HACHANI Ghassen