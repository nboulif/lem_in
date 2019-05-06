/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_s.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 03:03:30 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/30 03:03:31 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LEM_IN_S_H__
# define __LEM_IN_S_H__

typedef struct	s_node				t_node;
typedef struct	s_edge				t_edge;
typedef struct	s_father			t_father;
typedef struct	s_solution			t_solution;

// typedef struct				s_node_u_solve
// {
// 	int						D;
// 	int						last_D;
// 	t_edge					**father_edge;
// 	t_node					**father_node;
// 	t_edge					*in_a_way;
// 	int						nb_father_n;
// 	int						nb_father_t;
// 	int						i_nb_father;
// 	int						nb_of_inway;
// }							t_node_u_solve;

// NODE && EDGE REPRESENTATION

typedef struct				s_father
{
	t_node					*node;
	t_node					*node_out;
	t_edge					*edge;
	t_edge					*edge_out;
}							t_father;

typedef struct				s_node
{
	char					*name;
	unsigned long			id;
	int						nb_edge_o;
	int						nb_edge_f;
	t_edge					**edge;
	int						range;
	int						deja_vu_init;
	int						deja_vu;

	int						father_mode;

	// t_node_u_solve			u_sol;

	t_father				*fathers;

	t_edge					**father_edge;
	t_node					**father_node;
	
	t_edge					*in_a_way;
	int						nb_father_n;
	int						nb_father_t;
	int						i_nb_father;
	int						nb_of_inway;

	// for Bellman Ford
	int						D;
	int						last_D;

}							t_node;

typedef struct				s_node_link
{
	t_node					*node;
	struct	s_node_link		*prev;
	struct	s_node_link		*next;
	int						check;
}							t_node_link;

typedef struct				s_edge_link
{
	t_edge					*edge;
	struct	s_edge_link		*prev;
	struct	s_edge_link		*next;
}							t_edge_link;

typedef struct				s_edge
{
	t_node					*node1;
	t_node 					*node2;
	int						w1;	// weight node_1 to node_2
	int						w2;
	int						direction;
	int						deja_vu;
	int						deja_vu_init;
}							t_edge;

typedef struct				s_objectif
{
	t_node					*start_node;
	t_node					*end_node;
	t_node					**lst_node;
	t_node_link				**lst_node_lk;
	t_edge					*lst_edge;
	t_edge					**lst_edge_ord;
	int						nb_node;
	int						nb_edge;
	int						nb_edge_f;
	int						nb_ants;
	int 					max_way;
	int						max_link;
	int						dist_up;
	int						*dists;
	int						**deja_vus;
}							t_objectif;

// SOLVE

typedef struct 				s_way
{
	t_node_link				*nodes_lk;
	t_edge_link				*edges_lk;

	int						len;
	int						cost;
	int						nb_ants;
}							t_way;

typedef struct 				s_solution
{
	t_way					*way;
	int						nb_way;
	int						nb_turn;
	int						len;
}							t_solution;

typedef struct 				s_queue
{
	t_node					**node;
	int						size_queue;
	int						index;
}							t_queue;

// PRINT SOLVE

typedef struct 				s_string
{
	char					*chaine;
	int						index;
	int						size;
}							t_string;

typedef struct				s_t_int
{
	int						i;
	int						x;
	int						i_ants;
}							t_t_int;
#endif
