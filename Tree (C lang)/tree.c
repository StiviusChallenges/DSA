#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int key;
    int value;
    struct Node* left;
    struct Node* right;
} Node;

// TODO
// RemoveKey
// Pair (key/value)
// Tree instead of root

typedef struct Tree
{
    Node* root;
} Tree;

Tree* CreateTree()
{
    Tree* new_tree = malloc(sizeof(Tree));
    new_tree->root = NULL;
    return new_tree;
}

void DeleteTree(Node* root)
{
    if(root)
    {
        if(root->left)
            DeleteTree(root->left);
        if(root->right)
            DeleteTree(root->right);
        free(root);
    }
}

Node* AddPair(Node* root, int key, int value)
{
    if(!root)
    {
        root = malloc(sizeof(Node));
        root->left = NULL;
        root->right = NULL;
        root->key = key;
        root->value = value;
    }
    else
    {
        if(root->key > key)
            root->left = AddPair(root->left, key, value);
        else if(root->key < key)
            root->right = AddPair(root->right, key, value);
        else
        	root->value = value;
    }
    return root;
}

int GetHeight(Node* root)
{
    if(root)
    {
        int max;
        max = GetHeight(root->left) > GetHeight(root->right) ? GetHeight(root->left) : GetHeight(root->right);
        return max + 1;
    }
    return 0;
}

Node* RemoveKey(Node* root, int key)
{
    if(root)
    {
    	if(root->key > key)
            root->left = RemoveKey(root->left, key);
        else if(root->key < key)
            root->right = RemoveKey(root->right, key);
        else
        {
        	if(!root->left && !root->right)
        	{
        		free(root);
        		return NULL;
        	}
        	else if(!root->left)
    		{
    			root->key = root->left->key;
    			root->value = root->left->value;
    			root->right = root->left->right;
    			root->left = root->left->left;
    			free(root->left);
    			return root;
    		}
        	else if(!root->right)
    		{
    			root->key = root->right->key;
    			root->value = root->right->value;
    			root->left = root->right->left;
    			root->right = root->right->right;
    			free(root->right);
    			return root;
    		}
        	else 
        	{
        		if(!root->right->left)
        		{
        			root->key = root->right->key;
        			root->value = root->right->value;
        			root->right = root->right->right;
        			free(root->right);
        			return root;
        		}
        		else
        		{
        			Node* parent = NULL;
        			Node* cursor = root->right;
        			while(cursor->left != NULL)
        			{
        				parent = cursor;
        				cursor = cursor->left;
        			}
        			root->key = cursor->key;
        			root->value = cursor->value;
        			parent = RemoveKey(parent, cursor->key);
        			return root;
        		}
        	}
        }
        return root;
    }
    return NULL;
}

Node* FindKey(Node* root, int key)
{
    if(root)
    {
        if(root->key == key)
            return root;
        else
        {
            if(root->key > key)
                return FindKey(root->left, key);
            else
                return FindKey(root->right, key);
        }
    }
    return NULL;
}

int FindValue(Node* root, int key)
{
    if(root)
    {
        if(root->key == key)
            return root->value;
        else
        {
            if(root->key > key)
                return FindValue(root->left, key);
            else
                return FindValue(root->right, key);
        }
    }
    return -1;
}

int main()
{
    Tree* tree = CreateTree();
    tree->root = AddPair(tree->root,5,0);
    tree->root = AddPair(tree->root,11,2);
    tree->root = AddPair(tree->root,13,4);
    tree->root = AddPair(tree->root,12,4);
    tree->root = AddPair(tree->root,18,5);
    tree->root = AddPair(tree->root,17,6);
    tree->root = AddPair(tree->root,16,6);
    tree->root = AddPair(tree->root,15,6);
    RemoveKey(tree->root,13);
    Node* val = FindKey(tree->root,12);
    if(!tree->root->right->right->right->left->left)
    	printf("%s\n", "NOT EXIST");
    else
    	printf("%s\n", "EXIST");
    printf("%d\n", tree->root->right->right->right->left->left->key);
    Node* val2 = FindKey(tree->root,13);
    int height = GetHeight(tree->root);
    int value = FindValue(tree->root,5);
    printf("%d\n", height);
    DeleteTree(tree->root);
    return 0;
}
