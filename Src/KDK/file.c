#include "file.h"

//TODO use configs
int initFileBuffer(fileBuffer* buffer, Config * config){

    if (!buffer)
        return -1;

    buffer->_buffer = malloc(sizeof(_page));
    buffer->_numPages = 1;
    buffer->_handle = NULL;

    buffer->encoding = UTF_8;

    return 0;
}

int clearFileBuffer(fileBuffer* buffer){

    if (!buffer)
        return -1;

    for(size_t x = buffer->_numPages - 1; x > 1; --x){
        free(buffer->_buffer[x].memory);
        buffer->_buffer[x].memory = NULL;
        buffer->_buffer[x].index = NULL;
        buffer->_buffer[x].size = 0;
    }

    buffer->_select = buffer->_buffer;
    buffer->_handle = NULL;

    return 0;
}

int openFile(fileBuffer* buffer, char * filePath, fileEncoding encoding){

    if (buffer->_handle)
        return 1;

    buffer->_handle = fopen(filePath, "r");

    if (buffer->_handle == NULL)
        return 2;

    buffer->encoding = encoding;

    

    return 0;
}

int closeFile(fileBuffer* buffer, char * filePath){

    if (!fclose(buffer->_handle)){
        buffer->_handle = NULL;
        clearFileBuffer(buffer);//NESTED SCRIPTS?
    }

    return 0;
}

fchar * fReadLineBuffer(fileBuffer*buffer){

    return NULL;
}

fchar fReadCharBuffer(fileBuffer*buffer){

    return 0;
}