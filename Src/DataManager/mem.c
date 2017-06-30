#include <stdlib.h>

#include "KNX_Hash.h"

#include "type.h"
#include "mem.h"
#include "node_reg.h"

memTree * createMemTree()
{
    memTree * ret = malloc(sizeof(memTree));

    ret->mode = tm_binary;
    ret->root = NULL;

    return ret;
}

leaf * leafLookup(memTree * tree, unsigned long hash){

    leaf * itr = tree->root;
    
    while (itr != NULL){
        if (itr->data->hash == hash)
            return itr;
        
        if (hash < itr->data->hash){
            itr = itr->left;
        } else {
            itr = itr->right;
        }
    }

    return itr;
}

int destroyLeaf(memTree * tree, unsigned long hash){

    leaf * l = leafLookup(tree, hash);
    if (l==NULL)
        return 1;

    leaf * sub = NULL;
    
    if (l->right){
        sub = l->right;
        while (l->left)
            l=l->left;
    } else {
        sub = l->left;
    }

    sub->left = l->left;
    sub->right = l->right;
    sub->parent = l->parent;

    if (sub->left) sub->left->parent = sub;
    if (sub->right) sub->right->parent = sub;
    if (sub->parent){
        if (l == l->parent->left)
            l->parent->left = sub;
        else
            l->parent->right = sub;
    }

    if (l->data->data) 
        free(l->data->data);
    free(l->data);
    free(l);

    return 0;
}

//recursively destroy branches
int destroyBranch(){
    return 0;
}

int destroyMemTree(memTree * tree)
{
    int ret = destroyBranch(tree->root);
    
    if (ret) return ret;
    
    free(tree);

    return 0;
}

int addToTree(memTree * tree, leaf * l){
    if (tree->root == NULL){
        tree->root = l;
        return 0;
    }

    leaf * itr = tree->root;

    while(1){
        if (l->data->hash < itr->data->hash){
            if (itr->left == NULL){
                l->parent = itr;
                itr->left = l;
                return 0;
            } else {
                itr = itr->left;
            }
        } else if (l->data->hash > itr->data->hash){
            if (itr->right == NULL){
                l->parent = itr;
                itr->right = l;
                return 0;
            } else {
                itr = itr->right;
            }
        } else {
            //TODO throw redef err
            return 1;
        }
    }

    return 2;
}

obj * createObject(memTree * tree, char * name, unsigned type, void * data)
{
    obj * var = malloc(sizeof(obj));
    var->hash = FNV_1a_32(name);
    var->type = type;
    var->data = data;

    leaf * l = malloc(sizeof(leaf));
    l->data = var;
    l->left = NULL;
    l->right = NULL;
    l->parent = NULL;

    if (addToTree(tree, l))
        return NULL;

    return var;
}

int destroyObject(memTree*tree, char * str)
{
    unsigned long hash = FNV_1a_32(str);

    destroyLeaf(tree, hash);
    return 0;
}