/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_f.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 03:03:38 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/30 03:03:40 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LEM_IN_F_H__
# define __LEM_IN_F_H__

//edges_utils
int				is_same_edge(t_edge edge1, t_edge edge2);
int				is_in_tab_edge(t_edge **tab, t_edge *to_find, int size);
t_node 		    *get_right_node_in_edge(t_edge *edge, t_node *node, int verif);

//utils
unsigned long	hash(unsigned char *str);
int				line_len(char *str, int *i);
int				ft_min(int a, int b, int c);
int				ft_realloc(void **tab, int *size, int new_size, size_t type_size);
int 		    check_need_realloc(t_node *next);

//print_utils
void 			print_node_and_edge(char *str, int size);
void			print_all_edge(t_objectif *obj);
void 			print_way(t_objectif *obj, t_solution *sol);
void            print_way_status_before_merge(t_way *way);
void            print_way_status_after_merge(t_objectif *obj, t_way *way);

//resolv_init
int 			init_way(t_objectif *obj, t_way *way, int mode);
int				init_solution(t_objectif *obj, t_solution  *sol, t_queue *queue);
int				clone_way(t_objectif *obj, t_solution *sol, t_solution *cur);
void 			init_graph_bf(t_objectif *obj, int first_time);

//resolv_bf
int             find_way(t_objectif *obj, t_solution *sol);

//resolv
int				resolv(t_objectif *obj);

//Bellman Ford
int 			apply_algo_bellman_ford(t_objectif *obj, t_solution *sol);

//way
void            set_way_len_with_fathers(t_solution *sol, t_node *end_node);
void            update_ways_len_with_node_lk(t_solution *sol);
void            merge_way(t_objectif *obj, t_solution *sol);
int             make_way(t_objectif *obj, t_solution *sol);

//resolv_tmp
// int				add_brother_in_queue(t_objectif *obj, t_node *node, t_queue *queue, int range);
// int 			first_way(t_objectif *obj, t_solution *sol);
// int				find_way2(t_objectif *obj, t_solution *sol);

#endif


