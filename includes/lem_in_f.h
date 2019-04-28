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

//tubes_utils
int				is_same_tube(t_tube tube1, t_tube tube2);
int				is_in_tab_tube(t_tube **tab, t_tube *to_find, int size);

//utils
unsigned long	hash(unsigned char *str);
int				line_len(char *str, int *i);
int				ft_min(int a, int b, int c);
int				ft_realloc(void **tab, int *size, int new_size, size_t type_size);
int 		    check_need_realloc(t_node *next);
t_node 			*get_right_node_in_tube(t_node* node, int i);

//print_utils
void			print_all_tube(t_objectif *obj);
void 			print_way(t_objectif *obj, t_solution best);

//resolv_init
int 			init_way(t_objectif *obj, t_way *way);
int				init_solution(t_objectif *obj, t_solution  *sol, t_queue *queue);
int				clone_way(t_objectif *obj, t_solution *sol, t_solution *cur);
void 			init_graph_bf(t_objectif *obj, int first_time);

//resolv_bf
t_way	 		*find_way_bf(t_objectif *obj);

//resolv
int				resolv(t_objectif *obj);
void 			make_way(t_objectif *obj, t_solution *sol);

//resolv_tmp
int				add_brother_in_queue(t_objectif *obj, t_node *node, t_queue *queue, int range);
int 			first_way(t_objectif *obj, t_solution *sol);
int				find_way(t_objectif *obj, t_solution *sol);

#endif


