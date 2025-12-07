#ifndef HASSE_H
#define HASSE_H


typedef struct {    
    int from;
    int to;
} t_link;

typedef struct {
    t_link *links;   /* tableau dynamique */
    int log_size;    /* nombre effectif d'éléments dans links */
    /* éventuellement int cap; mais pas nécessaire pour removeTransitiveLinks */
} t_hasse_link_array;

void removeTransitiveLinks(t_hasse_link_array *p_link_array);

#endif /* HASSE_H */



