
#ifndef CLIENT_STRUCT_H
#define CLIENT_STRUCT_H


#include "commands.h"
#include <iostream>


struct CMD_STRUCT{
    COMMAND cmd;
    std::string arg;
};


#endif //CLIENT_STRUCT_H
