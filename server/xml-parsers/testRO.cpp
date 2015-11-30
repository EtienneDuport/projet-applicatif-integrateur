
int main (int argn, char* args[])
{
    int nVertices, nEdges=0, nMax=0, i, j, k=0;
    
	// Demande du nombre de sommets du graphe
	printf("Enter the number of patients to visit : ");
    scanf("%d", &nVertices);
	
	// Création du graphe sous forme de matrice d'adjacence et initialisation des poids à -1
    vector<vector<int> > G(nVertices);
    for(i=0; i < nVertices ; i++) G[i].resize(nVertices,-1);
    
    // Saisie du graphe
    for(i = 0 ; i < nVertices ; i++)
    {
        for(j = i + 1 ; j < nVertices ; j++)
        {
			printf("\nEnter the length of the path between [%d] and [%d] : ",i,j);
			scanf("%d",&k);
			G[i][j] = k;
			G[j][i] = k;
			nEdges++;
        }
    }
	
	// Affichage du graphe
    printf("\nNumber of Edges : %d\n\n",nEdges);
    printGraph(G);
	
	// Demande du point de départ du chemin
    k=0;
    printf("Enter the first patient to visit : ");
    scanf("%d",&k);
	
	// Création du chemin
    vector<int> path = tsp(G,k);
    
	// Affichage du chemin
    printf("Itinerary : ");
    for(i = 0 ; i < path.size() ; i++)
		printf("%d ", path[i]);
	
    return 0;

}
