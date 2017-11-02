#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>

char * get_permissions(int oct){
  char * per;
  if(oct == 0){
    per = "---";
    return per;
  }
  if(oct == 1){
    per = "--x";
    return per;
  }
  if(oct == 2){
    per = "-w-";
    return per;
  }
  if(oct == 3){
    per = "-wx";
    return per;
  }
  if(oct == 4){
    per = "r--";
    return per;
  }
  if(oct == 5){
    per = "r-x";
    return per;
  }
  if(oct == 6){
    per = "rw-";
    return per;
  }
  if(oct == 7){
    per = "rwx";
    return per;
  }
  
}

void to_str_per(mode_t oct){
  int user_per = oct / 064;
  user_per = user_per % 8;
  int group_per = oct / 8;
  group_per = group_per % 8;
  int other_per = oct % 8;

  char * user = get_permissions(user_per);
  char * group = get_permissions(group_per);
  char * other = get_permissions(other_per);

  char str[80];
  sprintf(str, "%s%s%s", user, group, other);
  printf("\tPermissions: %s\n\n", str);
}


void my_stat(char * file_name){
  int fd = open(file_name, O_RDONLY);
  struct stat sb;
  stat(file_name, &sb);

  //Printing out size
  size_t size = sb.st_size;
  printf("\nFile size: %lu\n", size);

  int gb = size / (1024 * 1024 * 1024); 
  size = size % (1024 * 1024 * 1024);
  int mb = size / (1024 * 1024);
  size = size % (1024 * 1024);
  int kb = size / 1024;
  size = size % 1024;
  int b = size;

  char str[256];
  sprintf(str, "File size: %dGB, %dMB, %dKB, %dB", gb, mb, kb, b);
  printf("\t%s\n\n", str);

  //Printing out permissions
  mode_t permis = sb.st_mode;
  printf("Permissions: %o\n", permis);
  to_str_per(permis);

  //Printing last access
  printf("Time of last access: %s\n", ctime(&(sb.st_atime)));

  close(fd);
}

int main(){
  my_stat("text.txt");
}
