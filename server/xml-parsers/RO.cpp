/*
Etienne Duport / Richy Adjibodou
 */
#include <algorithm>    // std::sort
#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

struct Arete
{
    int u,v;//extremit�s
    int poids;//co�t du d�placement
};

// R�cup�re la liste des voisins d'un sommet
vector<int> getNeighbours(vector<vector<int> > T, int vertice){
    vector<int> neighbours;
    int i, v;
	
    for(i = 0 ; i < T.size() ; i++){
        if(T[vertice][i] > 0)
            neighbours.push_back(v);
    }
	
    return neighbours;
}

// Parcours du graphe
bool isConnex(vector<vector<int> > T, int source){
    int i;
	
	for (i = 0 ; i < T.size() ; i++){
		T[source][i] = 0;
		T[i][source] = 0;
	}
	
	
    vector<int> neighbours = getNeighbours(T,source);
    
    for(i = 0 ; i < neighbours.size() ; i++){
        if(neighbours[i] > 0){
			neighbours[i] = 0;
            isConnex(T,i);
		}
    }
    return true;
}

vector<Arete*> createEdges(vector<vector<int> > G){
	int i, j, length = G.size();
	vector<Arete*> edges;
	
	for(i = 0 ; i < length ; i++){
        for(j = i + 1 ; j < length ; j++){
            if(G[i][j] > 0){
                Arete e;
                e.poids=G[i][j];
                e.u = i;
                e.v = j;
				Arete* pointer = new Arete();
				*pointer = e;
                edges.push_back(pointer);
            }
        }
    }
	return edges;
}

vector<Arete*> sortEdges(vector<Arete*> edges){
	int i, c, nEdges = edges.size();
    bool marker;
	Arete* currentEdge = new Arete();
    
    for(i = 0 ; i < nEdges-1 ; i++)
    {
        
        c = i + 1;// Fixe l'index de l'ar�te � observer en premier, c-�-d la suivante

        do
        {
            currentEdge = edges[c-1];// Stocke l'ar�te courante
			marker = false;
            if (edges[c]->poids > currentEdge->poids)// Compare le poids de l'ar�te courante avec celle qu'on observe
            {
                edges[c-1] = edges[c];// Remplace l'ar�te courante par l'ar�te observ�e
				edges[c] = currentEdge;// L'ar�te courante stock�e est inject�e dans l'ar�te suivante
                marker = true;
            }
			c--;// Recule dans le tableau
            if (c < 1) // Une fois qu'on est arriv� en d�but de tableau on sort de la boucle do-while
                marker = false;
        }
        while(marker);
    }
	return edges;
}

int getNumberEdges(vector<vector<int> > T){
	int i, j, numberEdges = 0;
	for(i = 0 ; i < T.size() ; i++){
		for(j = i + 1 ; j < T.size() ; j++)
			if( T[i][j] > 0)
				numberEdges++;
	}
	return numberEdges;
}

void removeEdge(vector<vector<int> > &T, Arete* edge){
	T[edge->u][edge->v] = -1;
	T[edge->v][edge->u] = -1;
}

void addEdge(vector<vector<int> > &T, Arete* edge){
	T[edge->u][edge->v] = edge->poids;
	T[edge->v][edge->u] = edge->poids;
}

bool kruskal(vector<vector<int> > &G, vector<vector<int> > &T)
{
    int i, j, c, nVertices = G.size(), nEdges = 0;
    bool marker;
    
	// Cr�ation du tableau d'ar�tes de G tri�es par poids d�croissant
	vector<Arete*> edges = sortEdges(createEdges(G));
	
    T = G;
	
	// Affichage des ar�tes
    printf("\nEdges (%d in total):\n", getNumberEdges(T));
    for(i = 0 ; i < edges.size() ; i++){
        printf("%d - %d : %d\n", edges[i]->u, edges[i]->v, edges[i]->poids);
    }
	
	
	while(getNumberEdges(T) > nVertices-1){
	
		Arete* edge = new Arete();
		edge = edges[0]; // Premi�re ar�te pas encore consid�r�e du tableau d'ar�tes
		
		// Retire l'ar�te dans la matrice d'adjacence et dans le tableau de pointeurs
		removeEdge(T,edge);
		edges.erase(edges.begin());
		
		if(!isConnex(T,edge->u)){ // si T\edge n'est plus connexe, on remet edge 
			addEdge(T,edge);
			edges.insert(edges.begin(), edge);
		}
    }
    //T obtenu est un arbre couvrant de poids minimum
    return true;
}

void printGraph(vector<vector<int> > G){
	int i, j, nVertices = G.size();
	for(i = 0 ; i < nVertices ; i++)
    {
        if(i == 0){
            printf(" | ");
            for(j = 0 ; j < nVertices ; j++){
                printf("%d ", j);
            }
            printf("\n---");
            for(j = 0 ; j < nVertices ; j++){
                printf("--");
            }
            printf("\n");
        }
        printf("%d| ",i);
        for(j = 0 ; j < nVertices ; j++)
        {
            if(G[i][j] > 0)
				printf("%d ",G[i][j]);
            else printf(". ");
        }
        printf("\n");
    }
}

void searchPath(vector<vector<int> > T, int currentVertex, vector<int> &visits, vector<int> &path){
	
	int i;
	
	// Marque le sommet courant comme ayant �t� visit�
	visits[currentVertex] = 1;
	
	// Rajoute le sommet courant au chemin
	path.push_back(currentVertex);
	
	for ( i = 0 ; i < T.size() ; i++ ){
		if(T[currentVertex][i] > 0 && visits[i] != 1){
			searchPath(T, i, visits, path);// Recherche un chemin � partir d'un voisin non visit�
		}
	}
}

vector<int> tsp(vector<vector<int> > &G, int start)
{
    vector<int> visits(G.size()), path;
    vector<vector<int> > T;
    
    kruskal(G,T);
	
	// Affichage de l'arbre de poids minimum
	printf("\nTree :\n");
	printGraph(T);
	
    // Parcours en profondeur de l'arbre T pour donner un chemin qui commence au sommet 'start'
    searchPath(T, start, visits, path);
    
	return path;
}

