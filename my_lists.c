#include "shell.h"

/**
 * add_node - functions that adds a node to the start of the list
 * @head: address of pointer to head node
 * @s: s field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *s, int num)
{
	list_t *new_head;

	/* checks if head pointer is NULL or empty */
	if (!head)
		return (NULL);
	/* allocates memory to the new node */
	new_head = malloc(sizeof(list_t));
	/* checks if new node is  NULL or empty */
	if (!new_head)
		return (NULL);
	/* initializes the new node to zero */
	_memset((void *)new_head, 0, sizeof(list_t));
	/* set n field in new node to n */
	new_head->num = num;
	/* s is not empty, allocate memory and copy string to it */
	if (s)
	{
		new_head->s = _strdup(s);
		/* checks if memory allocation and string duiplication were successful */
		if (!new_head->s)
		{
			free(new_head);
			return (NULL);
		}
	}
	/* make the new node's next point to the current head of the list */
	new_head->next = *head;
	/* update the head pointer to point to a new node, creating a new node */
	*head = new_head;
	/* returns a new node */
	return (new_head);
}

/**
 * add_node_end - function that adds a node to the end of the list
 * @head: points to pointer to head of a linked list
 * @s: field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *s, int num)
{
	list_t *new_node, *node;

	/* checks if head is empty */
	if (!head)
		return (NULL);

	/* point node to head of linked list */
	node = *head;
	/* allocates memory to new node */
	new_node = malloc(sizeof(list_t));
	/* checks if new node was is empty */
	if (!new_node)
		return (NULL);
	/* sets all bytes in memory to zero */
	_memset((void *)new_node, 0, sizeof(list_t));
	/* sets num field in new node */
	new_node->num = num;
	/* allocates memory for string field if it is NULL, and copies the string */
	if (s)
	{
		new_node->s = _strdup(s);
		/* checks if its successful */
		if (!new_node->s)
		{
			free(new_node);
			return (NULL);
		}
	}
	/* if node is not empty make it point to the new node */
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	/* returns pointer to new node */
	return (new_node);
}

/**
 * print_list_str - prints str field of list_t linked list
 * @head: pointer to head of the list
 *
 * Return: returns total number of list
 */
size_t print_list_str(const list_t *head)
{
	/* initialize the counter of nodes */
	size_t i = 0;
	/* loop through the list until head becomes NULL */
	while (head)
	{
		/* prints the str field of current node when it not NULL */
		_puts(head->s ? head->s : "(nil)");
		/* print newline to move to next line */
		_puts("\n");
		/* moves 'head' to the next node in the list */
		head = head->next;
		i++; /* increments the counter of nodes */
	}
	return (i);
}

/**
 * delete_node_at_index - deletes node at in a linked list
 * @head: double pointer to the head in the linked list
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int b = 0;
	/* checks if head or head pointer is NULL */
	if (!head || !*head)
		return (0);
	/* checks if index is zero then deletes first node */
	if (!index)
	{
		/* stores the current head  to node */
		node = *head;
		/* moves to next node */
		*head = (*head)->next;
		/* free the memory occupied by string in the node */
		free(node->s);
		/* free the memory occupied by the node */
		free(node);
		return (1);
	}
	/* initialize node to point to head of list */
	node = *head;
	while (node) /* transverse through the list */
	{
		if (b == index)
		{
			/* updates prev node to current */
			prev_node->next = node->next;
			/* free the memory occupied by stringin the node */
			free(node->s);
			/* free the memory occupied by the node */
			free(node);
			/* Returns 1 on success */
			return (1);
		}
		b++; /* increment the index counter */
		/* move previous node to current node */
		prev_node = node;
		/* move current node to next node */
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees memory allocated to linked list of files
 * @head_ptr: double pointer to the head of linked list
 *
 * Return: returns nothing
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	/* if the head_ptr or the pointer it points to is NULL then frees nothing */
	if (!head_ptr || !*head_ptr)
		return;
	/* head_ptr is stored in local variable (head) */
	head = *head_ptr;
	/* node is initialized to point to head */
	node = head;

	while (node)
	{
		/* pointer is saved to next node */
		next_node = node->next;
		/* current node is freed */
		free(node->s);
		/* frees memory allocated to current node */
		free(node);
		/* switching to the next node */
		node = next_node;
	}
	*head_ptr = NULL;
}
