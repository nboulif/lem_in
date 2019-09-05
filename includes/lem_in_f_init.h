/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_f_init.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 03:03:38 by nboulif           #+#    #+#             */
/*   Updated: 2019/09/04 17:23:06 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_F_INIT_H
# define LEM_IN_F_INIT_H

t_edge		create_edge(t_node *node1, t_node *node2);
t_node		*find_in_lst(t_objectif *obj, char *name, int size);
t_edge		next_edge(t_objectif *obj, char *str, int *i);
int			make_tab_edge(t_objectif *obj, char *str, int *i);

void		zap_line(char *str, int *i);
void		zap_comm(char *str, int *i);
int			number_check(char *str);
int			check_coord(char *str);

int			init_node(t_node *node, char *name, int nb_node, int size_name);
t_node		*malloc_node(int nb_node, int mode);

t_node		*create_node(char *str, int *i, int nb_node);
t_node_link	*malloc_node_lk(int nb_node, int mode);
int			add_in_lst(t_node_link **link, t_node *node, int nb_node);
int			exec_command(t_objectif *obj, char *str, int *i);
int			make_tab_node(t_objectif *obj, char *str, int *i);

int			is_node(char *str, int *i);
int			is_node_cond(char *str, int *i);
int			count_node(char *str, t_objectif *info);
int			create_lst_node_tab(t_objectif *obj);
int			extract_info(t_objectif *obj, char *str);

void		delete_this_edge(t_node *node, t_edge *edge, t_objectif *obj);
void		delete_dead_end(t_objectif *obj);

int			create_tab_edge_in_node(t_objectif *obj);
void		rec_init_lst_edge_ord_part_two(t_objectif *obj,
			t_queue queue, int *k);
int			rec_init_lst_edge_ord(t_objectif *obj);
int			link_node_and_edge(t_objectif *obj);
int			init_resolv(t_objectif *obj);

#endif
