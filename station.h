typedef struct _une_station
{
	char *nom; //Le nom
	struct _un_truc **tab_con; //Tableau des connexions
	unsigned int nb_con; //Nombre de connexions
	struct _un_truc *con_pcc; //Connexion du plus court chemin
	struct _une_ligne *ligne; //Ligne
} Une_station;
