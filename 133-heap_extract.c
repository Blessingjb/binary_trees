#include "binary_trees.h"

/**
 * binary_tree_height - Measures the height of a binary tree.
 * @tree: A pointer to the root node of the tree to measure the height of.
 * Return: The height of the tree, or 0 if tree is NULL.
 */
size_t binary_tree_height(const binary_tree_t *tree)
{
    size_t left_height = 0, right_height = 0;

    if (tree == NULL)
        return (0);

    if (tree->left)
        left_height = 1 + binary_tree_height(tree->left);
    if (tree->right)
        right_height = 1 + binary_tree_height(tree->right);

    return ((left_height > right_height) ? left_height : right_height);
}

/**
 * binary_tree_size - Measures the size of a binary tree.
 * @tree: A pointer to the root node of the tree to measure the size of.
 * Return: The size of the tree, or 0 if tree is NULL.
 */
size_t binary_tree_size(const binary_tree_t *tree)
{
    if (tree == NULL)
        return (0);

    return (binary_tree_size(tree->left) + 1 + binary_tree_size(tree->right));
}

/**
 * get_last_node - Gets the last node of the heap in level order.
 * @root: A pointer to the root node of the heap.
 * Return: A pointer to the last node of the heap, or NULL if root is NULL.
 */
heap_t *get_last_node(heap_t *root)
{
    int height = 0, size = 0, mask = 0;

    if (root == NULL)
        return (NULL);

    height = binary_tree_height(root);
    size = binary_tree_size(root);
    mask = 1 << (height - 1);

    while (mask > 0)
    {
        if (size & mask)
            root = root->right;
        else
            root = root->left;

        mask >>= 1;
    }

    return (root);
}

/**
 * heapify_down - Heapifies a Max Binary Heap node downwards.
 * @root: A pointer to the root node of the heap to heapify.
 */
void heapify_down(heap_t *root)
{
    heap_t *max_node = NULL, *temp = NULL;

    if (root == NULL)
        return;

    max_node = root;

    if (root->left && root->left->n > max_node->n)
        max_node = root->left;

    if (root->right && root->right->n > max_node->n)
        max_node = root->right;

    if (max_node != root)
    {
        temp = root->parent;
        if (root->left == max_node)
        {
            if (max_node->right != NULL)
                max_node->right->parent = root;

            root->left = max_node->right;
            max_node->right = root;
        }
        else
        {
            if (max_node->left != NULL)
                max_node->left->parent = root;

            root->right = max_node->left;
            max_node->left = root;
        }

        if (temp != NULL)
        {
            if (temp->left == root)
                temp->left = max_node;
            else
                temp->right = max_node;
        }

        max_node->parent = temp;
        root->parent = max_node;

        if (root == temp)
            temp->parent = max_node;

        heapify_down(root);
    }
}

/**
 * heap_extract
