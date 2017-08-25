#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "config.h"
#include "node_reg.h"
#include "mem.h"
#include "type.h"

#include "datamanager.h"

static void startup() __attribute__((constructor));
static void shutdown() __attribute__((destructor));

nodereg * node_reg = NULL;
type_reg * type_registry = NULL;

//Constructor/Destructor
void startup()
{
    config = getConfig();

    _handle = malloc(sizeof(HDTM));

    node_reg = malloc(sizeof(nodereg));
    node_reg->usedIdIndices = malloc(sizeof(int *) * config->maxNodes);
    node_reg->nodeTable = malloc(sizeof(node *) * config->maxNodes);

    for (unsigned i = 0; i < config->maxNodes; ++i){
        node_reg->nodeTable[i] = NULL;
    }

    node_reg->idTable = primeCipher(config->maxNodes);

    getNodeReg();
    initTypeRegistry();
    initKwRegistry();

    _setTypeRegistry(type_registry);

    dprint("Data Manager Loaded\r\n");
}

void shutdown()
{

    dprint("Data Manager Unloaded\r\n");
}