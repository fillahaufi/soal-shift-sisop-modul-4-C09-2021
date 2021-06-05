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
