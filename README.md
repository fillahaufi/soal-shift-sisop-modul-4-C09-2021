# soal-shift-sisop-modul-4-C09-2021
# Laporan Resmi Modul 4 #

## Soal 1 ##
### Pengerjaan ###
#### Soal 1a. ####
1. Jika membuat direktori dengan awalan AtoZ maka direktori akan terendcode
2. menggunakan fungsi enkripsi :
```
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
```

#### Soal 1b. ####
1. Jika me-rename direktori dengan awalan AtoZ maka direktori akan terencode
2. tinggal menjalankan fungsi yang sama pada soal a kembali

#### Soal 1c. ####
1. Jika me-rename dengan menghilangkan AtoZ pada direktori maka isi folder akan ter-decode
2. Untuk dekrip tinggal menjalankan fungsi yang sama pada soal a kembali

#### Soal 1d. ####
1. Pembuatan log
2. Mkdir :
```
void logFileAtozMkdir(char *path) {
    FILE *f;
    f = fopen("atoz.log", "a+");
    //format nge-log yang mkdir tidak ditentukan
    fprintf(f, "mkdir: %s\n", path);
}
```
3. rename :
```
void logFileAtozRename(char *path1, char *path2) {
    FILE *f;
    f = fopen("atoz.log", "a+");
    fprintf(f, "%s-->%s\n", path1, path2);
}
```

#### Soal 1e. ####
1. Rekursif encode
2. menggunakan fungsi :
```
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
```

## Soal 2 ##
### Pengerjaan ###
#### Soal 2a. ####
1. Jika membuat direktori dengan awalan RX maka direktori akan terendcode dengan algoritma tambahan ROT13
2. Menggunakan fungsi :
```
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
```

#### Soal 2b. ####
1. Jika me-rename direktori dengan awalan RX maka direktori akan terencode dengan algoritma tambahan Vigenere Cipher
2. Fungsi VigenereCipher:
```
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
```

#### Soal 2c. ####
1. Jika me-rename dengan menghilangkan RX pada direktori maka isi folder akan ter-decode
2. Menggunakan fungsi yang sama pada soal 2 a maupun b

#### Soal 2d. ####
1. Pencatatan setiap mkdir atau rename kedalam log file
2. mkdir :
```
void logFileRXMkdir(char *path) {
    FILE *f;
    f = fopen("RX.log", "a+");
    //format nge-log yang mkdir tidak ditentukan
    fprintf(f, "mkdir: %s\n", path);
}
```
3. rename :
```
void logFileRXRename(char *path1, char *path2) {
    FILE *f;
    f = fopen("RX.log", "a+");
    fprintf(f, "%s-->%s\n", path1, path2);
}
```

#### Soal 2e. ####
Belum dapat menyelesaikan

## Soal 3 ## 
### Pengerjaan ###
Belum dapat menyelesaikan

## Soal 4 ##
Untuk memudahkan dalam memonitor kegiatan pada filesystem mereka Sin dan Sei membuat sebuah log system dengan spesifikasi sebagai berikut.
### Pengerjaan ###
Untuk mencatat log yang, dibuat fungsi, yaitu printlog() dan printlog2() Kedua fungsi ini sama, perbedaanya pda funsi printlog2() memiliki parameter input 2 path dimana fungsi akan mencatat log dengan 2 parameter.
#### Soal 4a. ####
Log system yang akan terbentuk bernama “SinSeiFS.log” pada direktori home pengguna (/home/[user]/SinSeiFS.log). Log system ini akan menyimpan daftar perintah system call yang telah dijalankan pada filesystem.
```
 file = fopen("/home/Naufaldillah/SinSeiFS.log", "a+");
```
#### Soal 4b. ####
Karena Sin dan Sei suka kerapian maka log yang dibuat akan dibagi menjadi dua level, yaitu INFO dan WARNING.
#### Soal 4c. ####
Untuk log level WARNING, digunakan untuk mencatat syscall rmdir dan unlink.
#### Soal 4d. ####
Sisanya, akan dicatat pada level INFO.
```
 if(level == 0) fprintf(file, "INFO");
    else if (level == 1) fprintf(file, "WARNING");
```
#### Soal 4e. ####
Format untuk logging yaitu:

[Level]::[dd][mm][yyyy]-[HH]:[MM]:[SS]:[CMD]::[DESC :: DESC]

Level : Level logging, dd : 2 digit tanggal, mm : 2 digit bulan, yyyy : 4 digit tahun, HH : 2 digit jam (format 24 Jam),MM : 2 digit menit, SS : 2 digit detik, CMD : System Call yang terpanggil, DESC : informasi dan parameter tambahan

```
 fprintf(file, "::%02d%02d%02d-%02d:%02d:%02d::%s::%s\n", (timestamp->tm_year+1900)%100, 
        timestamp->tm_mon+1, timestamp->tm_mday, timestamp->tm_hour, timestamp->tm_min, timestamp->tm_sec, command ,path + strlen(dirpath));
```
