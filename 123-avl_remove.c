#include "binary_trees.h"
/**
 * avl_remove - removes a node from an AVL tree
 * @root: pointer to the root node of the tree
 * @value: value to remove from the tree
 *
 * Return: pointer to the new root node of the tree
 */
avl_t *avl_remove(avl_t *root, int value)
{
	avl_t *node, *parent, *temp, *successor;

	node = bst_search(root, value);
	if (!node)
		return (root);

	parent = node->parent;

	if (!node->left && !node->right) /* Case 1: node has no children */
	{
		if (!parent)
			root = NULL;
		else if (parent->left == node)
			parent->left = NULL;
		else
			parent->right = NULL;

		free(node);
	}
	else if (!node->left || !node->right) /* Case 2: node has one child */
	{
		temp = node->left ? node->left : node->right;

		if (!parent)
			root = temp;
		else if (parent->left == node)
			parent->left = temp;
		else
			parent->right = temp;
		temp->parent = parent;
		free(node);
	}
	else /* Case 3: node has two children */
	{
		successor = bst_find_min(node->right);
		node->n = successor->n;
		avl_remove(node->right, successor->n);
	}
	if (root) /* Rebalance the tree */
		root = avl_balance(root);
	return (root);
}
