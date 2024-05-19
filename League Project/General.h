//
//  General.h
//  FinalProject
//
//  Created by Ari Guterman on 15/03/2024.
//

#ifndef General_h
#define General_h

#define MAX_STR_LEN 255
#define IF_NOT_ALLOC(VAL){ \
                            if(!VAL) { \
                                free(VAL);\
                                return 0;}\
                                 \
                                }
#define IF_NOT_INIT(FUNCTION,VAL){ \
                                    if(!(FUNCTION(VAL))){ \
                                        free(VAL);     \
                                        return 0;         \
                                        }\
                                    }
#define IF_DIDNT_OPEN_FILE(FILE){ \
                                if(!FILE) \
                                    return 0; \
                                    }
#define WRONG_INDEX printf("Wrong Index\n");
#define SAVE_OR_OPEN_FILE(FUNCTION,STRUCT,FILE){ \
                                                if(!(FUNCTION(STRUCT,FILE))) { \
                                                    return 0;   }\
                                                    }

char*    getStrExactName(const char* msg);
char*    myGets(char* buffer, int size, FILE* source);
char*    getDynStr(char* str);

int loadClassFromBinary(void* val,size_t size,FILE* pFile);
int saveClassToBinary(void* val,size_t size,FILE* pFile);
char* readDynStringFromTextFile(FILE* fp);
int generalCompareFunction(const void *array,size_t size,size_t count, int func(const void*,const void*),const void* cmpVal) ;
#endif /* General_h */
