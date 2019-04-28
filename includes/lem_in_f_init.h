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

#ifndef __LEM_IN_F_INIT_H__
# define __LEM_IN_F_INIT_H__

//parsing
int				is_node(char *str, int *i);
int				is_node_cond(char *str, int *i);
int				count_node(char *str, t_objectif *info);
int				extract_info(t_objectif *obj, char *str);

//nodes_create
int				init_node(t_node *node, char *name, int nb_node);
t_node			*create_node(char *str, int *i, int nb_node);
int				exec_command(t_objectif *obj, char *str, int *i);
int				add_in_lst(t_node_link **link, t_node *node);
int				make_tab_node(t_objectif *obj, char *str, int *i);

//tubes_create
t_tube			create_tube(t_node *node1, t_node *node2);
t_node			*find_in_lst(t_objectif *obj, char *name, int size);
t_tube			next_tube(t_objectif *obj, char *str, int *i);
int				make_tab_tube(t_objectif *obj, char *str, int *i);

//resolv_init
void			delete_this_tube(t_node *node, t_tube *tube, t_objectif *obj);
void			delete_dead_end(t_objectif *obj);
int				create_tab_tube_in_node(t_objectif *obj);
int				link_node_and_tube(t_objectif *obj);
int				init_resolv(t_objectif *obj);

//zap
void			zap_line(char *str, int *i);
void			zap_comm(char *str, int *i);
void            print_ants(t_objectif *obj, t_solution *sol);


#endif


