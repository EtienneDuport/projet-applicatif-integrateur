/* 
 * File:   RO.h
 * Author: Etienne
 *
 * Created on 30 novembre 2015, 17:19
 */
#include <algorithm>    // std::sort
#include <stdio.h>
#include <vector>
#include <iostream>

#ifndef RO_H
#define	RO_H

vector<int> getNeighbours(vector<vector<int> > T, int vertice);
bool isConnex(vector<vector<int> > T, int source);
vector<Arete*> createEdges(vector<vector<int> > G);
vector<Arete*> sortEdges(vector<Arete*> edges);
int getNumberEdges(vector<vector<int> > T);
void removeEdge(vector<vector<int> > &T, Arete* edge);
void addEdge(vector<vector<int> > &T, Arete* edge);
bool kruskal(vector<vector<int> > &G, vector<vector<int> > &T);
void printGraph(vector<vector<int> > G);
void searchPath(vector<vector<int> > T, int currentVertex, vector<int> &visits, vector<int> &path);
vector<int> tsp(vector<vector<int> > &G, int start);


#endif	/* RO_H */

