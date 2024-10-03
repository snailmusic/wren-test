#include <stdio.h>
#include <string.h>
#include "wren.h"

void mathSex(WrenVM* vm) {
    double a = wrenGetSlotDouble(vm, 1);
    double b = wrenGetSlotDouble(vm, 2);
    wrenSetSlotDouble(vm, 0, 2.0);
}

void writeFn(WrenVM * vm, const char * text) {
    printf("%s", text);
}

void errorFn(WrenVM* vm, WrenErrorType errorType,
             const char* module, const int line,
             const char* msg)
{
  switch (errorType)
  {
    case WREN_ERROR_COMPILE:
    {
      printf("[%s line %d] [Error] %s\n", module, line, msg);
    } break;
    case WREN_ERROR_STACK_TRACE:
    {
      printf("[%s line %d] in %s\n", module, line, msg);
    } break;
    case WREN_ERROR_RUNTIME:
    {
      printf("[Runtime Error] %s\n", msg);
    } break;
  }
}

WrenForeignMethodFn bindForeignMethod(
    WrenVM* vm,
    const char* module,
    const char* className,
    bool isStatic,
    const char* signature
)
{
    printf(":3\n");

    if (strcmp(module, "main") == 0)
    {
        if (strcmp(className, "Math") == 0)
        {
            if (isStatic && strcmp(signature, "sex(_,_)") == 0)
            {
                return mathSex;
            }
        }
    }
    return NULL;
}

int main(void) {
    FILE* fptr;
    fptr = fopen("hi.wren", "r");

    if (fptr == NULL) {
        printf("ensure hi.wren exists in ur pwd!!!!! dumas...\n");
        exit(0);
    }

    fseek(fptr, 0L, SEEK_END);
    long int sz = ftell(fptr);
    fseek(fptr, 0L, SEEK_SET);

    char* source;
    // allocate 4 kb for loading of file (may expand later)
    source = (char*)malloc(sz);

    if (source == NULL) {
        printf("shit. memory wasn't allocated :/");
        exit(-1);
    }

    char ch;
    long int i = 0;
    while ((ch = fgetc(fptr)) != EOF) {
        // printf("%c", ch);
        source[i] = ch;
        i++;
    }

    WrenConfiguration config;
    wrenInitConfiguration(&config);
        config.writeFn = &writeFn;
        config.errorFn = &errorFn;
        config.bindForeignMethodFn = &bindForeignMethod;
    
    WrenVM* vm = wrenNewVM(&config);

    wrenEnsureSlots(vm, 8);
    WrenInterpretResult result = wrenInterpret(
        vm,
        "main",
        source
    );

    wrenEnsureSlots(vm, 1);
    WrenHandle* slay = wrenMakeCallHandle(vm, "slay()");
    wrenGetVariable(vm, "main", "Fancy", 0);
    WrenHandle* fancyClass = wrenGetSlotHandle(vm, 0);
    wrenCall(vm, slay);
    wrenSetSlotHandle(vm, 0, fancyClass);
    wrenCall(vm, slay);
    wrenSetSlotHandle(vm, 0, fancyClass);
    wrenCall(vm, slay);

    WrenHandle* bottles = wrenMakeCallHandle(vm, "ninebottles(_)");
    wrenSetSlotHandle(vm, 0, fancyClass);
    wrenSetSlotDouble(vm, 1, 3.0);
    wrenCall(vm, bottles);

    

    free(source);
    wrenFreeVM(vm);
    return 0;
}