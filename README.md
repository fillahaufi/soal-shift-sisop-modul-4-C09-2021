# soal-shift-sisop-modul-4-C09-2021
# Laporan Resmi Modul 4 #

## Soal 1 ##
### Pengerjaan ###
#### Soal 1a. ####
#### Soal 1b. ####
#### Soal 1c. ####
#### Soal 1d. ####
#### Soal 1e. ####

## Soal 2 ##
### Pengerjaan ###
#### Soal 2a. ####
#### Soal 2b. ####
#### Soal 2c. ####
#### Soal 2d. ####
#### Soal 2e. ####

## Soal 3 ##
### Pengerjaan ###
#### Soal 3a. ####
#### Soal 3b. ####
#### Soal 3c. ####
#### Soal 3d. ####
#### Soal 3e. ####

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
