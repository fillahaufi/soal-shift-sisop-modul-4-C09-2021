#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
#include <stdlib.h>
#include <ctype.h>

void printlog(char* command , int level, char* path){
    FILE* file;
    file = fopen("/home/Naufaldillah/SinSeiFS.log", "a+");
    time_t epoch;
    struct tm* timestamp;

    time(&epoch);
    timestamp= localtime (&epoch);
    if(level == 0) fprintf(file, "INFO");
    else if (level == 1) fprintf(file, "WARNING");
    fprintf(file, "::%02d%02d%02d-%02d:%02d:%02d::%s::%s\n", (timestamp->tm_year+1900)%100, 
        timestamp->tm_mon+1, timestamp->tm_mday, timestamp->tm_hour, timestamp->tm_min, timestamp->tm_sec, command ,path + strlen(dirpath));
    fclose(file);
}

void printlog2(char* command , int level, char* path, char* path2){
    FILE* file;
    file = fopen("/home/Naufaldillah/SinSeiFS.log", "a+");
    time_t epoch;
    struct tm* timestamp;

    time(&epoch);
    timestamp= localtime (&epoch);
    if(level == 0) fprintf(file, "INFO");
    else if (level == 1) fprintf(file, "WARNING");
    fprintf(file, "::%02d%02d%02d-%02d:%02d:%02d::%s::%s::%s\n", (timestamp->tm_year+1900)%100, 
        timestamp->tm_mon+1, timestamp->tm_mday, timestamp->tm_hour, timestamp->tm_min, timestamp->tm_sec, command ,path + strlen(dirpath), path2 + strlen(dirpath));
    fclose(file);
}

static const char *KEY = "SISOP";

static  const  char *dirpath = "/home/gian/Downloads";

// nmr 2 a;
void encryptrot13(char *string, int type) {
	printf("encrypt \n");
	if(!strcmp(string, ".") || !strcmp(string, "..")) return;
	
	char *token = strtok(string, ".");

	int end = strlen(token);

        if(type == 1){
		for(int i = 0; i < end; i++) {
		        if(string[i] >= 65 && string[i] <= 90) {
		                string[i] = string[i] + 13;
		                if(string[i] > 90) {
		                        string[i] = string[i] - 90 + 65 - 1;
		                }
		        } else if(string[i] >= 97 && string[i] <= 122) {
		                int j = (int)string[i];
		                j = j + 13;
		                if(j > 122) {
		                        j = j - 122 + 97 - 1;
		                }
		                string[i] = j;
		        } else {
		                string[i] = string[i];
			}
		}
	}
	else if (type ==2){
		for(int i = 0; i < end; i++) {
		        if(string[i] >= 65 && string[i] <= 90) {
		                string[i] = string[i] - 13;
		                if(string[i] > 90) {
		                        string[i] = string[i] + 90 - 65 + 1;
		                }
		        } else if(string[i] >= 97 && string[i] <= 122) {
		                int j = (int)string[i];
		                j = j - 13;
		                if(j > 122) {
		                        j = j + 122 - 97 + 1;
		                }
		                string[i] = j;
		        } else {
		                string[i] = string[i];
			}
		}
	}

}

void encryptAtoz(char *path) {
    if(!strcmp(path, ".") || !strcmp(path, "..")) return;

    //char temp[100];
    char *token = strtok(path, ".");

    int end = strlen(token);

    for (int i = 0; i < end; i++) {
        
        while(path[i]!='\0') {
            if(!((path[i]>=0&&path[i]<65)||(path[i]>90&&path[i]<97)||(path[i]>122&&path[i]<=127))) {

                if(path[i]>='A'&&path[i]<='Z') {
                    path[i] = 'Z'+'A'-path[i];
                    //printf("%c", ecryptPath);
                }
               
               if(path[i]>='a'&&path[i]<='z') {
                    path[i]  = 'z'+'a'-path[i];
                    //printf("%c", ecryptPath);
                }
               
            } 
                
            if(((path[i]>=0&&path[i]<65)||(path[i]>90&&path[i]<97)||(path[i]>122&&path[i]<=127))) {
                path[i]  = path[i];
                //printf("%c", ecryptPath);
                   
            }
    
            i++;
        }

    }  

}

void vigenereCipher(char* plainText){
	
	int i,j;
    	int msgLen = strlen(plainText);
    	int keyLen = strlen(KEY);
    	char newKey[msgLen];
    	char *encryptedMsg = malloc(msgLen);

    	if(!strcmp(plainText,".") || !strcmp(plainText,"..")) return plainText;
    	//generating new key
    	for(i = 0, j = 0; i < msgLen; ++i, ++j){
        	if(j == keyLen) j = 0;
 
        	newKey[i] = KEY[j];
   	}
 
    	newKey[i] = '\0';

    	//encryption
    	for(i = 0; i < msgLen; ++i){
        	if(plainText[i]=='.')
        	{
            		break;
        	}
        encryptedMsg[i] = ((plainText[i] + newKey[i]) % 26) + 'A';
   	}

    	while (plainText[i] != '\0'){
     		encryptedMsg[i] = plainText[i];
     		i++;
    	}

    	encryptedMsg[i] = '\0';

    	return encryptedMsg;
}


void recursiveRename(char *fromPath, int type) {
    DIR *dp;
    struct dirent *de;
    char file[100];
    char fileExt[100];
    char beforePath[1100];
    char afterPath[1100];

    dp = opendir(fromPath);

    if (dp == NULL) return;

    while ((de = readdir(dp)) != NULL) {
        if(strcmp(de->d_name, "..") == 0|| strcmp(de->d_name, ".") == 0) continue;
        if(de->d_type == DT_DIR) {
            strcpy(file, de->d_name);
            sprintf(beforePath, "%s/%s", fromPath, file);
            recursiveRename(beforePath, type);
        }
        //printf("de rename: %s\n", de->d_name);
        strcpy(file, de->d_name);
        strcpy(fileExt, file);
        sprintf(beforePath, "%s/%s", fromPath, file);
        //printf("ini file : %s\n", file);
        char *ext = strrchr(fileExt, '.');
	puts(file);
	
	if(type == 1)
		encryptAtoz(file);
	if ( type == 2){
		encryptAtoz(file);
		encryptrot13(file,1);
	}
	if( type == 3){
		encryptAtoz(file);		
		vigenereCipher(file);
	}	
		

        //printf("ini ext: %s\n", ext);

        if(ext != NULL) {
            sprintf(afterPath, "%s/%s%s", fromPath, file, ext);
            //printf("ini afterpath: %s\n", afterPath);
            rename(beforePath, afterPath);
        }

        else if(ext == NULL) {
            sprintf(afterPath, "%s/%s", fromPath, file);
            //printf("ini afterpath: %s\n", afterPath);
            rename(beforePath, afterPath);
        }

    }

    closedir(dp);

}

void logFileAtozRename(char *path1, char *path2) {
    FILE *f;
    f = fopen("atoz.log", "a+");
    fprintf(f, "%s-->%s\n", path1, path2);
}
void logFileRXRename(char *path1, char *path2) {
    FILE *f;
    f = fopen("RX.log", "a+");
    fprintf(f, "%s-->%s\n", path1, path2);
}

void logFileAtozMkdir(char *path) {
    FILE *f;
    f = fopen("atoz.log", "a+");
    //format nge-log yang mkdir tidak ditentukan
    fprintf(f, "mkdir: %s\n", path);
}

void logFileRXMkdir(char *path) {
    FILE *f;
    f = fopen("RX.log", "a+");
    //format nge-log yang mkdir tidak ditentukan
    fprintf(f, "mkdir: %s\n", path);
}

static  int  xmp_getattr(const char *path, struct stat *stbuf)
{
    int res;
    char fpath[1000];

    sprintf(fpath,"%s%s",dirpath,path);

    res = lstat(fpath, stbuf);

    if (res == -1) return -errno;

    return 0;
}

static int xmp_mkdir(const char *path, mode_t mode)
{
    int res;
    char fpath[1000];

    sprintf(fpath,"%s%s",dirpath,path);

    if(strstr(fpath, "AtoZ_")) {
        logFileAtozMkdir(fpath);
    }

    if(strstr(fpath, "RX_")) {
	printf("create log RX\n");
        logFileRXMkdir(fpath);
	recursiveRename(fpath,2);
    }

    res = mkdir(fpath, mode);
    if (res == -1)
        return -errno;

    return 0;
}



static int xmp_rename(const char *from, const char *to)
{
    int res;
    char fromPath[1000];
    char toPath[1000];

    sprintf(fromPath,"%s%s",dirpath,from);
    sprintf(toPath,"%s%s",dirpath,to);
    // atoz jadi normal decode
    if(strstr(fromPath, "AtoZ_")) {
        if(!strstr(toPath, "AtoZ_")) recursiveRename(fromPath,1);

    }if(strstr(fromPath, "RX_")) {
        if(!strstr(toPath, "RX_")) recursiveRename(fromPath,2);
	}

    // normal jadi atoz encode
    if(!strstr(fromPath, "AtoZ_")) {
        if(strstr(toPath, "AtoZ_")) recursiveRename(fromPath,1);

        logFileAtozRename(fromPath, toPath);

    }if(!strstr(fromPath, "RX_")) {
        if(strstr(toPath, "RX_")) recursiveRename(fromPath,2);

        logFileRXRename(fromPath, toPath);
    }

    //recursiveRename(fromPath);
    
    res = rename(fromPath, toPath);
    if (res == -1)
        return -errno;


    return 0;
}



static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi)
{
    char fpath[1000];
    if(strcmp(path,"/") == 0)
    {
        path=dirpath;
        sprintf(fpath,"%s",path);
    } else sprintf(fpath, "%s%s",dirpath,path);

    int res = 0;

    DIR *dp;
    struct dirent *de;
    (void) offset;
    (void) fi;

    dp = opendir(fpath);

    if (dp == NULL) return -errno;

    while ((de = readdir(dp)) != NULL) {
        struct stat st;

        memset(&st, 0, sizeof(st));

        st.st_ino = de->d_ino;
        st.st_mode = de->d_type << 12;
        res = (filler(buf, de->d_name, &st, 0));

        if(res!=0) break;
    }

    closedir(dp);

    return 0;
}



static int xmp_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
    char fpath[1000];
    if(strcmp(path,"/") == 0)
    {
        path=dirpath;

        sprintf(fpath,"%s",path);
    }
    else sprintf(fpath, "%s%s",dirpath,path);

    int res = 0;
    int fd = 0 ;

    (void) fi;

    fd = open(fpath, O_RDONLY);

    if (fd == -1) return -errno;

    res = pread(fd, buf, size, offset);

    if (res == -1) res = -errno;

    close(fd);

    return res;
}



static struct fuse_operations xmp_oper = {
    .getattr = xmp_getattr,
    .mkdir = xmp_mkdir,
    .rename = xmp_rename,
    .readdir = xmp_readdir,
    .read = xmp_read,
};



int  main(int  argc, char *argv[])
{
    umask(0);

    return fuse_main(argc, argv, &xmp_oper, NULL);
}
