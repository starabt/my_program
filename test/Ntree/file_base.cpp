#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "file_base.h"
using std::cout;
using std::endl;
void get_time_str(time_t time,string &timeStr)
{
    char timeTmp[20]={0};
    struct tm localTime;
    localtime_r(&time,&localTime);
    snprintf(timeTmp,sizeof("1970-01-01 00:00:00"),"%04d-%02d-%02d %02d:%02d:%02d",localTime.tm_year+1900,localTime.tm_mon,\
        localTime.tm_mday,localTime.tm_hour,localTime.tm_min,localTime.tm_sec);
    timeStr = timeTmp;
    return ;
}
FILE_BASE::FILE_BASE():
file_type(UNKNOWN_FILE_TYPE),
fsize(0)
{}
FILE_BASE::~FILE_BASE()
{}
void FILE_BASE::init_file_msg(string name_,string path_,string time_,FILE_TYPE file_type_,long int size_)
{
    file_type = file_type_;
    fname = name_;
    fpath = path_;
    ftime = time_;
    fsize = size_;
    return;
}

FILE_NODE::FILE_NODE():
file_type(UNKNOWN_FILE_TYPE),
fatherNode(NULL),
symbol("1")
{

}
FILE_NODE::~FILE_NODE()
{}
FILE_NODE::FILE_NODE(const FILE_NODE& b)
{
    this->file_type = b.file_type;
    this->name = b.name;
    this->path = b.path;
    this->size = b.size;
    this->symbol = b.symbol;
    this->fatherNode = b.fatherNode;
    this->childrenNode.assign(b.childrenNode.begin(),b.childrenNode.end()) ;
}
void FILE_NODE::init_node(string symbol_)
{
    symbol = symbol_;
    return;
}
void FILE_NODE::init_file_msg(string name_,string path_,FILE_TYPE file_type_,long int size_)
{
    init_node(path_);
    file_type = file_type_;
    name = name_;
    path = path_;
    size = size_;
    return ;
}
FILE_CTRL::FILE_CTRL(string path)
{
    FileTree.init_tree(path);
}
FILE_CTRL::~FILE_CTRL()
{}
#if 1
/**
 * [FILE_CTRL::file_ctrl_scan_dir 遍历文件夹下的子文件夹和文件，存于N叉树]
 * @param dirPath   [待遍历的文件夹，建议绝对路径，最终的文件信息会带上一次为基础的路径信息]
 * @param file_tree [N叉树，存文件信息]
 * @param helpNode  [调用者可不传，主要用于递归遍历]
 */
void FILE_CTRL::file_ctrl_scan_dir(const string dirPath ,FILETREE& file_tree,int level,FILENODE *helpNode)
{
    printf("the localdir to scanf is:%s\n",dirPath.c_str() );
    if(helpNode==NULL)
    {
        if(file_tree.pRoot)
            helpNode=file_tree.pRoot;
        else
            return;
    }
    DIR *dir;  
    struct dirent *ptr;  
    struct stat sb;
    if ((dir=opendir(dirPath.c_str())) == NULL)  
    {  
        perror("Open dir error...");  
        return ;
    }  
    else
    {
        string time_str;
        long int file_size=0;
        
        FILE_BASE file_msg;
        while ((ptr=readdir(dir)) != NULL)  
        {  
            if(strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0)    ///current dir OR parrent dir  
                continue; 
            if(stat((dirPath+'/'+ptr->d_name).c_str(), &sb) >= 0)
            {
                get_time_str(sb.st_mtime,time_str);
                file_size = sb.st_size;
            } 
            if(ptr->d_type == DT_REG) //file 8
            {
                FILENODE newNode ;
                file_msg.init_file_msg(ptr->d_name,dirPath+'/'+ptr->d_name,time_str,TYPE_FILE,file_size);
                newNode.init_node(file_msg.fpath,&file_msg);
                file_tree.insert(&newNode,helpNode);
                // cout << ptr->d_name << endl;
                //printf("d_name:%s/%s\n",basePath,ptr->d_name);  
                // files.push_back(dirPath+'/'+ptr->d_name); 
            } 
            else if(ptr->d_type == DT_DIR) //dir 4
            {
                FILETREE tmpTree ;
                FILENODE tmpRoot ;
                // get_time_str(ptr->st_mtime,&time_str);
                file_msg.init_file_msg(ptr->d_name,dirPath+'/'+ptr->d_name,time_str,TYPE_DIR); 
                tmpRoot.init_node(file_msg.fpath,&file_msg);
                tmpTree.init_tree(&tmpRoot);
                if(level == 1)
                {
                    file_tree.insert(&tmpRoot,helpNode);
                    continue;
                }
                if(level > 1 )
                    level --;
                if(level >= 0)
                {
                    file_ctrl_scan_dir(tmpRoot.data.fpath,tmpTree,level,&tmpRoot);
                    file_tree.insert(&tmpRoot,helpNode);
                }   
            }   
            else 
                continue; 
        }  
        closedir(dir); 
    }
    return ;
}
void FILE_CTRL::file_ctrl_scan_dir_level(const string dirPath ,int level)
{
    file_ctrl_scan_dir(dirPath,FileTree,level,FileTree.pRoot);
}
/**
 * [FILE_CTRL::file_ctrl_get_nodes 获取所有节点，依据文件类型区分文件或文件夹]
 * @param dirPath   [要获取信息的文件夹，绝对路径与否跟scan_dir遍历时移植]
 * @param file_type_ [文件类型（文件或文件夹），依据此类型返回相应文件节点集合]
 */
vector<FILE_CTRL::FILENODE* > FILE_CTRL::file_ctrl_get_nodes(string dirPath,FILE_TYPE file_type_)
{
    if(dirPath=="NULL" && FileTree.pRoot)
        dirPath = FileTree.pRoot->symbol;
    FILENODE tmpNode;
    tmpNode.init_node(dirPath);
    vector<FILENODE* > fileNodes;
    vector<FILENODE* > dirNodes;
    if(FileTree.search(&tmpNode)!=NULL)
    {
        vector<FILENODE* > Nodes;
        Nodes = FileTree.get_allNodes(tmpNode);
        for(unsigned int i=0;i<Nodes.size();i++)
        {
            if(Nodes[i]->data.file_type == TYPE_FILE)
                fileNodes.push_back(Nodes[i]);
            else if(Nodes[i]->data.file_type == TYPE_DIR)
                dirNodes.push_back(Nodes[i]);
        }
        if(file_type_ == TYPE_FILE )
            return fileNodes;
        else if(file_type_ == TYPE_DIR)
            return dirNodes;

    }
    else
    {
        cout << "the file not exist:" << dirPath << endl;
    }
    return fileNodes;

}
/**
 * [FILE_CTRL::file_ctrl_get_files 获取所有文件节点节点]
 * @param dirPath   [要获取信息的文件夹，绝对路径与否跟scan_dir遍历时移植]
 */
vector<FILE_CTRL::FILENODE* > FILE_CTRL::file_ctrl_get_files(string dirPath)
{
    if(dirPath=="NULL" && FileTree.pRoot)
        dirPath = FileTree.pRoot->symbol;
    return  file_ctrl_get_nodes(dirPath,TYPE_FILE);
}
/**
 * [FILE_CTRL::file_ctrl_get_dirs 获取所有文件夹节点]
 * @param dirPath   [要获取信息的文件夹，绝对路径与否跟scan_dir遍历时移植]
 */
vector<FILE_CTRL::FILENODE* > FILE_CTRL::file_ctrl_get_dirs(string dirPath)
{
    if(dirPath=="NULL" && FileTree.pRoot)
        dirPath = FileTree.pRoot->symbol;
    return  file_ctrl_get_nodes(dirPath,TYPE_DIR);
}
/**
 * [FILE_CTRL::file_ctrl_get_file_num 获取文件数]
 * @param  dirPath [要获取信息的文件夹，绝对路径与否跟scan_dir遍历时移植]
 * @return         [文件数]
 */
int FILE_CTRL::file_ctrl_get_file_num(string dirPath)
{
    vector<FILENODE* > tmpFiles;
    tmpFiles = file_ctrl_get_files(dirPath);
    return tmpFiles.size();
}
/**
 * [FILE_CTRL::file_ctrl_get_dir_num 获取文件夹数]
 * @param  dirPath [要获取信息的文件夹，绝对路径与否跟scan_dir遍历时移植]
 * @return         [文件夹数]
 */
int FILE_CTRL::file_ctrl_get_dir_num(string dirPath)
{
    vector<FILENODE* > tmpDirs;
    tmpDirs = file_ctrl_get_dirs(dirPath);
    return tmpDirs.size();
}

string FILE_CTRL::file_ctrl_get_oldest_node(string dirPath,bool is_leaf)
{
    if(dirPath=="NULL" && FileTree.pRoot)
        dirPath = FileTree.pRoot->symbol;
    FILENODE tmpNode;
    tmpNode.init_node(dirPath);
    FILE_BASE oldestFile;
    if(FileTree.search(&tmpNode)!=NULL)
    {
        
        vector<FILENODE* > Nodes;
        if(is_leaf)
            Nodes = FileTree.get_leavesNodes(tmpNode);
        else
            Nodes = FileTree.get_sonNodes(tmpNode);
        if(!Nodes.empty())
        {
            oldestFile = Nodes[0]->data;
            for(unsigned int  i = 1;i<Nodes.size();i++)
            {
                if(Nodes[i]->data.ftime<oldestFile.ftime)
                    oldestFile = Nodes[i]->data;
            }
            return oldestFile.fpath;
        }
            
    }
    else
    {
        cout << "the file not exist:" << dirPath << endl;
        return "NULL";
    }
    return "NULL";
}
/**
 * [FILE_CTRL::create_dir 递归创建文件夹]
 * @param  sPathName [文件夹路径]
 * @param  mode      [文件权限]
 * @return           [true：成功 false：失败]
 */
int FILE_CTRL::create_dir(const char *sPathName,int mode)
{
    if(sPathName == NULL)
        return -1;
    char DirName[256];  
    strcpy(DirName, sPathName);  
    int i,len = strlen(DirName);
    for(i=1; i<len; i++)  
    {  
        if(DirName[i]=='/')  
        {  
            DirName[i] = 0; 
            if(access(DirName, F_OK)!=0)  
            {  
                if(mkdir(DirName, mode)==-1)  
                {   
                    printf("mkdir   error\n");   
                    return -1;   
                }  
            }  
            DirName[i] = '/';  

        }  
    }  
    return 0;  
}
/**
 * [FILE_CTRL::create_path 创建文件路径，不加入文件树]
 * @param  path       [要创建的路径]
 * @param  file_type_ [文件类型]
 * @param  mode       [权限]
 * @return            [true：成功 false：失败]
 */
bool FILE_CTRL::create_path(const string& path,FILE_TYPE file_type_,int mode)
{
    if(path.empty() || file_type_ == UNKNOWN_FILE_TYPE )
        return false;
    string tmpName;
    string tmpDir;
    auto symb = path.find_last_of("/");
    if(symb != string::npos )
    {
        tmpName = path.substr(symb);
        tmpDir = path.substr(0,symb);
    }
    else
    {
        tmpName = path;
        tmpDir = path;
    }
    if(!create_dir(tmpDir.c_str(),mode))
        return false;
    int ret = -1;
    switch(file_type_)
    {
        case TYPE_FILE:
            ret = open(path.c_str(),O_CREAT,mode);
            if(ret > 0)
                close(ret);
            break;
        case TYPE_DIR:
            ret = mkdir(path.c_str(),mode);
            break;
        default:break;
    }
    if(ret >=0)
        return true;
    return false;

}
/**
 * [FILE_CTRL::file_ctrl_create_node 递归创建文件或文件夹，加入文件树中，但信息只是创建时的]
 * @param  path       [要创建的路径]
 * @param  file_type_ [文件类型]
 * @param  mode       [权限]
 * @return            [true：成功 false：失败]
 */
bool FILE_CTRL::file_ctrl_create_node(const string& path,FILE_TYPE file_type_,int mode)
{ 
    if(!path.empty() && file_type_ != UNKNOWN_FILE_TYPE)
    {
        FILE_BASE tmpFile;
        string tmpName;
        auto symb = path.find_last_of("/");
        if(symb != string::npos )
        {
            tmpName = path.substr(symb);
        }
        else
        {
            tmpName = path;
        }
        string tmpTime;
        get_time_str(time(NULL),tmpTime);
        if(create_path(path,file_type_,mode))
        {
            tmpFile.init_file_msg(tmpName,path,tmpTime,file_type_,0);
            return true;
        }
    }
    return false;
}
#endif
#if 1
int main()
{
    FILE_NODE file0;
    file0.init_node("0");
    FILE_NODE file1;
    FILE_NODE *file2;
    file1.init_node("1");
    file1.fatherNode = &file0;
    file1.name="test";
    file1.path="./test";
    file1.size=12234;
    FILE_NODE file3=file1;
    FILE_NODE file4;
    file4.init_file_msg("test2","./test2");
    file4.fatherNode = &file3;
    file2=new FILE_NODE(file1);
    printf("%s\n",file1==file3?"true":"false" );
    printf("file2:father:%s,symbole:%s,name:%s,path:%s,size:%ld\n",file2->fatherNode-> symbol.c_str(),file2->symbol.c_str(),file2->name.c_str(),file2->path.c_str(),file2->size );
    printf("file3:father:%s,symbole:%s,name:%s,path:%s,size:%ld\n",file3.fatherNode-> symbol.c_str(),file3.symbol.c_str(),file3.name.c_str(),file3.path.c_str(),file3.size );
    printf("file4:father:%s,symbole:%s,name:%s,path:%s,size:%ld\n",file4.fatherNode-> symbol.c_str(),file4.symbol.c_str(),file4.name.c_str(),file4.path.c_str(),file4.size );
    // FILETREE fileTree;
    string scan_path = "../Ntree";
    FILE_CTRL fileCtrl(scan_path);
    // FILE_CTRL::FILENODE fileRoot;
    // fileRoot.init_node(scan_path);
    // fileCtrl.FileTree.init_tree(scan_path);
    // fileCtrl.file_ctrl_scan_dir(scan_path,fileCtrl.FileTree);
    fileCtrl.file_ctrl_scan_dir_level(scan_path,2);
    fileCtrl.FileTree.display(fileCtrl.FileTree.pRoot);
    printf("leaves:%d\n",fileCtrl.FileTree.get_leavesNum(*fileCtrl.FileTree.pRoot) );
    vector<FILE_CTRL::FILENODE* > nodes;
    nodes = fileCtrl.file_ctrl_get_files("../Ntree/tes");
    // nodes = fileCtrl.FileTree.get_allNodes(*fileCtrl.FileTree.pRoot);
    for(int i=0;i<nodes.size();i++)
    {
        cout << nodes[i]->symbol << ":" << nodes[i]->data.ftime << " " <<endl;
    }
    cout << endl;
    cout << "oldest leaf:" << fileCtrl.file_ctrl_get_oldest_node(scan_path) <<endl;

    FILE_CTRL::FILENODE nodeTmp;
    nodeTmp.init_node("../Ntree/test/a.out");
    fileCtrl.FileTree.search(&nodeTmp);
    // cout << "tmpNode: type:" << nodeTmp.data.file_type << " ,son:" << nodeTmp.childrenNode[0]->symbol << endl;
    fileCtrl.FileTree.deinit_tree();
    return 0;
}
#endif