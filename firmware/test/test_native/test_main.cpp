#include <unity.h>
#include "../lib/NexusShell.hpp"



void setUp(){

}
void tearDown(){}

void test_shell_parser(){
    NexusShell shell{};
    shell.parse("WRITE:1");
    
}

int main(){
    UNITY_BEGIN();

    return UNITY_END();
    
}
