#ifndef FILE_BASE_H
#define FILE_BASE_H
#include <sys/stat.h>
#include <dirent.h> 
#include <cstring>
#include "Ntree.hpp"
using std::string;
using std::vector;
typedef enum FILE_TYPE_
{
	TYPE_FILE=0,
	TYPE_DIR,
	UNKNOWN_FILE_TYPE=0xff,
}FILE_TYPE;
/*no used*/
class FILE_NODE
{
public:
	FILE_NODE();
	~FILE_NODE();
	FILE_NODE(const FILE_NODE& b);
	FILE_NODE &operator=(FILE_NODE &b){
		this->file_type = b.file_type;
	    this->name = b.name;
	    this->path = b.path;
	    this->size = b.size;
		this->symbol = b.symbol;
		this->fatherNode = b.fatherNode;
		this->childrenNode.assign(b.childrenNode.begin(),b.childrenNode.end()) ;
		
		// for(int i=0;i<b.childrenNode.size();i++)
		// {
		// 	this->childrenNode.push_back(b.childrenNode[i]);
		// }
		return *this;
	}
	bool operator==(const FILE_NODE& p)
	{
		return this->symbol==p.symbol?true:false;
	}
//user data,
	FILE_TYPE file_type;
	string name;
	string path;
	long int size;
	void init_file_msg(string name_,string path_,FILE_TYPE file_type_=UNKNOWN_FILE_TYPE,long int size_=0);
//base info,can not lose
	void init_node(string symbol_);

	FILE_NODE *fatherNode;
	vector<FILE_NODE*> childrenNode;
	string symbol;
	vector<FILE_NODE*>::iterator it;


};


class FILE_BASE
{
public:
	FILE_BASE();
	virtual ~FILE_BASE();
	FILE_BASE &operator=(const FILE_BASE &b){
		this->file_type = b.file_type;
	    this->fname = b.fname;
	    this->fpath = b.fpath;
	    this->ftime = b.ftime;
	    this->fsize = b.fsize;
		return *this;
	}
	FILE_TYPE file_type;
	string fname;
	string fpath;
	string ftime;
	long int fsize;
	void init_file_msg(string name_,string path_,string time_,FILE_TYPE file_type_=UNKNOWN_FILE_TYPE,long int size_=0);
};


class FILE_CTRL
{
public:
	FILE_CTRL(string path);
	virtual ~FILE_CTRL();
	typedef TREE_NODE<FILE_BASE> FILENODE;
	typedef NTREE<FILENODE > FILETREE;
	FILETREE FileTree;
	void file_ctrl_scan_dir_level(const string dirPath ,int level=0);
	void file_ctrl_scan_dir(const string dirPath ,FILETREE& file_tree,int level = 0,FILENODE *helpNode=NULL);
	vector<FILENODE* > file_ctrl_get_files(string dirPath="NULL");
	vector<FILENODE* > file_ctrl_get_dirs(string dirPath="NULL");
	int file_ctrl_get_file_num(string dirPath="NULL");
	int file_ctrl_get_dir_num(string dirPath="NULL");
	string file_ctrl_get_oldest_node(string dirPath="NULL",bool is_leaf = true);

private:
	vector<FILENODE* > file_ctrl_get_nodes(string dirPath,FILE_TYPE file_type_=UNKNOWN_FILE_TYPE);
	int create_dir(const char *sPathName,int mode=0755);
	bool create_path(const string& path,FILE_TYPE file_type_,int mode=0755);
	bool file_ctrl_create_node(const string& path,FILE_TYPE file_type_=UNKNOWN_FILE_TYPE,int mode=0755);
};
#endif
