#ifndef CLOX_OBJECT_H
#define CLOX_OBJECT_H

#include "chunk.h"
#include "common.h"
#include "table.h"
#include "value.h"

#define OBJ_TYPE(value) (AS_OBJ(value)->type)

#define IS_CLASS(value)    isObjType(value, OBJ_CLASS)
#define IS_CLOSURE(value)  isObjType(value, OBJ_CLOSURE)
#define IS_FUNCTION(value) isObjType(value, OBJ_FUNCTION)
#define IS_INSTANCE(value) isObjType(value, OBJ_INSTANCE)
#define IS_NATIVE(value)   isObjType(value, OBJ_NATIVE)
#define IS_STRING(value)   isObjType(value, OBJ_STRING)

#define AS_CLASS(value)    ((ObjClass*) AS_OBJ(value))
#define AS_CLOSURE(value)  ((ObjClosure*) AS_OBJ(value))
#define AS_FUNCTION(value) ((ObjFunction*) AS_OBJ(value))
#define AS_INSTANCE(value) ((ObjInstance*) AS_OBJ(value))
#define AS_NATIVE(value)   (((ObjNative*) AS_OBJ(value))->function)
#define AS_STRING(value)   ((ObjString*) AS_OBJ(value))
#define AS_C_STRING(value) (((ObjString*) AS_OBJ(value))->chars)

typedef enum {
    OBJ_CLASS,
    OBJ_CLOSURE,
    OBJ_FUNCTION,
    OBJ_INSTANCE,
    OBJ_NATIVE,
    OBJ_STRING,
    OBJ_UPVALUE,
} ObjType;

struct Obj {
    ObjType type;
    bool isMarked;
    Obj* next;
};

void printObject(Value value);

static inline bool isObjType(Value value, ObjType type) {
    return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

struct ObjClass {
    Obj obj;
    ObjString* name;
};

ObjClass* newClass(ObjString* name);

struct ObjClosure {
    Obj obj;
    ObjFunction* function;
    ObjUpvalue** upvalues;
    int upvalueCount;
};

ObjClosure* newClosure(ObjFunction* function);

struct ObjFunction {
    Obj obj;
    int arity;
    int upvalueCount;
    Chunk chunk;
    ObjString* name;
};

ObjFunction* newFunction();

struct ObjInstance {
    Obj obj;
    ObjClass* class;
    Table fields;
};

ObjInstance* newInstance(ObjClass* class);

typedef Value (*NativeFn)(int argCount, Value* args);

struct ObjNative {
    Obj obj;
    NativeFn function;
};

ObjNative* newNative(NativeFn function);

struct ObjString {
    Obj obj;
    int length;
    char* chars;
    uint32_t hash;
};

ObjString* takeString(char* chars, int length);
ObjString* copyString(char const* chars, int length);

struct ObjUpvalue {
    Obj obj;
    Value* location;
    Value closed;
    ObjUpvalue* next;
};

ObjUpvalue* newUpvalue(Value* slot);

#endif // CLOX_OBJECT_H
