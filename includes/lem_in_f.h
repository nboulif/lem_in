/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_f.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 03:03:38 by nboulif           #+#    #+#             */
/*   Updated: 2019/09/05 18:43:36 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_F_H
# define LEM_IN_F_H

int				init_dist_deja_vu_lst(t_objectif *obj);
void			init_right_bf_utils(t_bf_utils *bf, t_edge *e, int mode);

void			bf_both_deja_vu(t_objectif *obj, t_bf_utils *bf, t_edge *e);
int				bf_other(t_objectif *obj, t_bf_utils *bf, t_edge *e);
void			check_bellman_ford(t_objectif *obj, t_edge *e, int mode);
void			apply_algo_bellman_ford_part_two(t_objectif *obj, int o);
int				apply_algo_bellman_ford(t_objectif *obj);

int				is_same_edge(t_edge edge1, t_edge edge2);
int				is_in_tab_edge(t_edge **tab, t_edge *to_find, int size);
t_node			*get_right_node_in_edge(t_edge *edge, t_node *node, int verif);

void			free_obj_part_two(t_objectif *obj);
void			free_obj(t_objectif *obj);
int				free_obj_and_print_error(t_objectif *obj, char *str);

int				read_all(char **str, int fd);
void			estimate_max_way(t_objectif *obj);
t_father		*alloc_t_father(t_objectif *obj, int mode);

void			create_node_tab_part_two(t_objectif *obj, int x, int *i,
				t_edge_link *e_ln);
void			create_node_tab(t_objectif *obj);
void			print_node_and_edge(char *str, int size);

int				init_max_father_in_node(t_objectif *obj);
int				lem_in(t_objectif *obj, char *str, int size);
int				main(int argc, char **argv);

int				create_output(t_solution *sol, t_string **output);
char			*ft_itoa_no_m_part_two(char *str, int n, int last, int size);
char			*ft_itoa_no_m(char *str, int n);
int				init_put_in_ouput(t_string *cur_ants, t_t_int index);
int				free_output_error(t_solution *sol, t_string **output, int i);

void			copy_in_ouput(t_string *cur_ants, t_string *str,
				t_node_link *node_lk, int nd);
int				put_in_ouput(t_objectif *obj, t_string
				*cur_ants, t_string *output, t_t_int index);
int				print_ants_part_three(t_objectif *obj, t_print_ant_utils *u);
int				print_ants_part_two(t_objectif *obj, t_print_ant_utils *u);
int				print_ants(t_objectif *obj);

int				check_atomic_part_two(t_objectif *obj, t_node *node);
int				check_atomic(t_objectif *obj, t_way *way);
int				find_way(t_objectif *obj);

void			evaluate_turn_solution(t_objectif *obj, t_solution *sol);
int				init_solver(t_objectif *obj);
void			next_to_best_sol(t_solution *best_sol, t_solution *next_sol);
int				resolv_part_init(t_objectif *obj, t_resolv_utils *u);
int				resolv(t_objectif *obj);

int				init_way(t_objectif *obj, t_way *way);
unsigned long	hash(unsigned char *str);
int				line_len(char *str, int *i);
int				ft_min(int a, int b, int c);
int				ft_realloc(void **tab, int *size,
				int new_size, size_t type_size);

void			merge_edge_part_two(t_solution *sol, t_e_ln_utils *e_ln_u,
				t_node *node_in, t_node *node_out);
int				merge_multiple_edge(t_solution *sol, t_e_ln_utils *e_ln_u);
void			merge_one_edge(t_solution *sol, t_e_ln_utils *e_ln_u);

void			set_way_len_with_fathers(t_solution *sol, t_node *end_node);
void			update_ways_len_with_node_lk(t_solution *sol);
t_node			*get_node_between_2_edge(t_edge *edge1, t_edge *edge2);
void			merge_multiple_disc_edge(t_solution *sol, t_e_ln_utils *e_ln_u);
int				pass_next_nodirs(t_e_ln_utils *e_ln_u);

void			merge_way_part_two(t_solution *sol, int *i,
				int *finish, t_e_ln_utils *e_ln_u);
void			merge_way(t_solution *sol);
void			init_make_way(t_objectif *obj, t_solution *sol,
				t_make_way_utils *u);
void			make_way_part_two(t_objectif *obj, t_solution *sol,
				t_make_way_utils *u);
int				make_way(t_objectif *obj, t_solution *sol);

#endif
