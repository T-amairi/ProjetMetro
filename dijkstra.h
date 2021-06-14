#ifndef _AQR_TOPO_
#define _AQR_TOPO_
#endif
Un_truc *extraire_deb_liste(Un_elem **liste);
Un_truc *extraire_liste(Un_elem **liste, Un_truc *truc);
void dijkstra(Un_elem *liste_sta, Un_truc *sta_dep);
Un_elem *cherche_chemin(Un_truc *sta_arr);