#ifndef MEMBER_H
#define MEMBER_H
#include "Data.h"

void inputMember(Member *newMember);
void readMember(const char *filename);
void addMember();
Member* searchMember(char *IdentifyID);    
void deleteMember();
void storeMember();
#endif