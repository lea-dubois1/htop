#ifndef HTOP_DATAMANAGER_H
#define HTOP_DATAMANAGER_H

#define BASE_DIR_NAME "/proc"

typedef struct processData Process;
struct processData
{
    int id;
    char *name;
};

int getNumberProcesses(char *dirName);
Process* getData();

#endif //HTOP_DATAMANAGER_H
