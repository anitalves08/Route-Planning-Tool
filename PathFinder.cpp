#include <iostream>
#include <vector>

using namespace std;

#include "MutablePriorityQueue.h"
#include "Graph.h"
#include "Location.h"

void bestPath(Graph<Location> *graph, vector<pair<int,int>> res, int &min_time, int &index_park, int walking_time ) {
    //vetor res (id,walkings)
    for (int i=0;i<res.size();i++) {
        if (walking_time!=-1) {
            if (res[i].second==walking_time) {
                continue;
            }
        }
        int total_time = res[i].second + graph->getVertexSet()[res[i].first-1]->getDist();
        if (min_time > total_time) {
            min_time = total_time;
            index_park=i;
        }
        else if (min_time ==total_time) {
            if (res[index_park].second < res[i].second) {
                index_park=i;
            }
        }
    }
}

vector<int> getPath(Graph<Location> *graph, const int &source, const int &dest){
    vector<int> res;
    Vertex<Location> *d= graph->getVertexSet()[dest-1];
    if (d->getDist()==INT_MAX || d->getPath()==nullptr){
        cout<< "no Path exists" << endl;
        return res;
    }
    while(d!=nullptr){
        if (d->getInfo().id != source && d->getInfo().id != dest) {
            d->setProcessing(true);
        }
        res.push_back(d->getInfo().id);
        Edge<Location> *path=d->getPath();
        if(path==nullptr){ break;}
        path->setSelected(true);
        d=path->getOrig();
    }
    res.push_back(graph->getVertexSet()[dest-1]->getDist());
    return res;
}

void shortestPath(Graph<Location> *graph, const int &source) {
    MutablePriorityQueue<Vertex<Location>> q;
    for (Vertex<Location> *v : graph->getVertexSet()) {
        v->setDist(INT_MAX);
        v->setPath(nullptr);
        v->setVisited(false);
    }
    cout<< "origem" << source<<endl;
    Vertex<Location> *s = graph->getVertexSet()[source-1];

    //define o ponto de partida source com distancia 0
    s->setDist(0);
    s->setVisited(true);
    q.insert(s);
    while (!q.empty()) {
        Vertex<Location> *u = q.extractMin();
        for (Edge<Location> *e : u->getAdj()) {
            Vertex<Location> *v = e->getDest();
            if (v->isProcessing() || e->isSelected()) continue;
            if (v->getDist()> u->getDist() + e->getWeight()) {
                v->setDist(u->getDist() + e->getWeight());
                v->setPath(e);
                if (!v->isVisited()) { //se ele ainda nao tiver sido visitado é porque não está na priorityqueue
                    v->setVisited(true);
                    q.insert(v);
                }
                else {
                    q.decreaseKey(v);
                }
            }
        }
    }
}

vector<pair<int,int>> shortestPathWalking(Graph<Location> *graph, const int &dest, const int &source, const int &max_walking) {
    MutablePriorityQueue<Vertex<Location>> q;
    for (Vertex<Location> *v : graph->getVertexSet()) {
        v->setDist(INT_MAX);
        v->setPath(nullptr);
        v->setVisited(false);
    }
    Vertex<Location> *d = graph->getVertexSet()[dest-1];
    d->setDist(0);
    q.insert(d);
    vector<pair<int,int>> parking_nodes;
    vector<pair<int,int>> all_parking_nodes;
    d->setVisited(true);
    while (!q.empty()) {
        Vertex<Location> *u = q.extractMin();
        for (Edge<Location> *e : u->getAdj()) {
            Vertex<Location> *v = e->getDest();
            if (v->isProcessing() || e->isSelected() || v->getInfo().id == source) continue;
            if (v->getDist()> u->getDist() + e->getWalking()) {
                v->setDist(u->getDist() + e->getWalking());
                v->setPath(e);
                if (!v->isVisited()) {
                    if (v->getDist() <= max_walking) {
                        q.insert(v);
                        v->setVisited(true);
                        if (v->getInfo().parking == 1) {
                            parking_nodes.push_back(make_pair(v->getInfo().id,0));
                        }
                    }
                }
                else {
                    q.decreaseKey(v);
                }
            }
        }
    }
    for (int j=0 ; j<parking_nodes.size(); j++) {
        parking_nodes[j].second = graph->getVertexSet()[parking_nodes[j].first-1]->getDist();
    }
    return parking_nodes;
}
