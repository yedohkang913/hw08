#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>

void my_stat(char * file_name){
  int fd = open(file_name, O_RDONLY);
  struct stat sb;
  stat(file_name, &sb);

  size_t size = sb.st_size;
  printf("File size: %lu\n", size);
  int gb = size / (1024 * 1024 * 1024); 
  size = size % (1024 * 1024 * 1024);
  int mb = size / (1024 * 1024);
  size = size % (1024 * 1024);
  int kb = size / 1024;
  size = size % 1024;
  int b = size;

  char str[256];
  sprintf(str, "File size: %dGB, %dMB, %dKB, %dB", gb, mb, kb, b);
  puts(str);

  mode_t permis = sb.st_mode;
  printf("Permissions: %o\n", permis);
  
  printf("Time of last access: %s\n", ctime(&(sb.st_atime)));
}
int main(){
  my_stat("text.txt");
}
