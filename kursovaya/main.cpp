#include <iostream>
#include "DatabaseConnector.h"
#include "Interface.h"
#include "Connection_of_client.h"
#include "Calculate.h"
#include "Errors.h"
#include "Logger.h"

int main(int argc,const char** argv)
{
    Interface UI;
    UI.comm_proc(argc,argv);
    return 0;
}
