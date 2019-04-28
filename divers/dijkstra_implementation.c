
typedef struct 	s_queue t_queue;
int		*dijksta(t_objectif *obj);


typedef struct 	s_queue
{
	t_node		*node;

	int			dist_from_start;

	t_queue		*prev;
	t_queue		*next;
}				t_queue;



int		temp_func()
{
	// node->id must equal to &node for unique ID

	t_node **main_list = @@@; // List of nodes with node->id as index
	t_node **sorted_list = ###; // List of nodes sorted by dist from Start
	t_node *sorted_chained_list = %%%; // Same as sorted_list but as Double Chained List

	// must have this list for each suurballe iterations...??

}

int		*dijksta(t_objectif *obj)
{
	int		i;
	int		*dist;
	int		*prev;
	t_node	*node;
	t_queue	*queue;

	dist = (*int)malloc(sizeof(int) * obj->nb_node);
	prev = (*int)malloc(sizeof(int) * obj->nb_node);

	ft_memset(dist, 9999, sizeof(int) * obj->nb_node);
	ft_memset(prev, 0, sizeof(int) * obj->nb_node);

	dist[obj->start_node->id] = 0;

	queue = sorted_chained_list; // same as in temp_func but with t_queue instead

	while(queue && *queue);
	{
		node = *queue->node;

		// remove and free current element;
		temp_queue = *queue;
		if (*queue->next)
		{
			queue = queue->next;
			queue->prev = NULL;
		}
		temp_queue = NULL;
		free(temp_queue);

		i = 0;
		while (i < node->nb_links)
		{
			if (node->tube[i]->node_2 == node && (node->tube[i]->direction == 3 || node->tube[i]->direction == 2))
			{
				if (dist[node->tube[i]->node_2->id] > dist[node->id] + node->tube[i]->weight_2)
				{
					dist[node->tube[i]->node_2->id] = dist[node->id] + node->tube[i]->weight_2;
					
					prev[node->tube[i]->node_2->id] = node->id;
					
					remove_node_from_queue(queue, node->tube[i]->node_2);
				}
			}
			// same but the other node_1 instead of node_2 in tube
			else if (node->tube[i]->node_1 == node && (node->tube[i]->direction == 3 || node->tube[i]->direction == 1))
			{
				if (dist[node->tube[i]->node_1->id] > dist[node->id] + node->tube[i]->weight_1)
				{
					dist[node->tube[i]->node_1->id] = dist[node->id] + node->tube[i]->weight_1;
					
					prev[node->tube[i]->node_1->id] = node->id;
					
					remove_node_from_queue(queue, node->tube[i]->node_1);
				}
			}
		}
	}	

	return (prev);
}
