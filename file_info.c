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
  printf("File size: %ld\n", sb.st_size);
  printf("Permissions: %ld\n", sb.st_mode);
  printf("Time of last access: %s\n", ctime(&(sb.st_atime)));
}
int main(){
  my_stat("text.txt");
}
