#define Maxsize 100
#define Disk 512
#define NumDisk 2038

typedef struct DirectoryNode_
{
	char name[9];
	int type;
	DirectoryNode_ *next;
	DirectoryNode_ *preDirFile;
	DirectoryNode_ *subFile;
	int size;
	int first;
	int last;
	int order;

}DirectoryNode;
typedef struct FileSys_
{
	int VacTable[NumDisk];
	DirectoryNode_ root;
	DirectoryNode_ Directory[NumDisk];
}FileSys,*filesys;

typedef struct 
{
	DirectoryNode_ *DirFile;
	char name[9];
}DateType;
typedef struct 
{
	DateType datea[MaxSize];
	int front,rear;
}Tp;
void InitQueue