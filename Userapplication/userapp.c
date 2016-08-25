#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
int main(int argc, char const *argv[]) {
  /* code */
int device;
device = open("/dev/s3495671Device", O_RDWR);
if (device == -1 ){
  printf("%s\n","Error in opening device");
  return EXIT_FAILURE;
}
int s = 0;
char bufferW[100];
char bufferR[100];
char c;
int i;

while(s == 0){
printf("%s\n%s\n", "1.read","2.write");

// printf("%s\n",buffeT);
  if(1 == scanf("\n%c",&c)){
    if (c == '1'){
      read(device,bufferR,sizeof(bufferR));
      printf("Read:%s",bufferR);
    }
    if(c == '2'){
      if (fgets(bufferW,sizeof(bufferW)-1,stdin)){
         i = strlen(bufferW);
         if(bufferW[i] =='n'){
           bufferW[i] = ' ';
         }
         printf("%s\n",bufferW );
          write(device,bufferW,sizeof(bufferW));
      }

    }
    if(c == 'q'){
      return EXIT_SUCCESS;
    }
  }

}
  return 0;
}

// #include <stdio.h>
// #include <fcntl.h>
//
//
// main ( ) {
//         int i,fd;
//         char ch, write_buf[100], read_buf[100];
//
//         fd = open("/dev/chard", O_RDWR);
//
//         if (fd == -1)
//         {
//                 printf("Error in opening file \n");
//                 exit(-1);
//         }
//         printf ("Press r to read from device or w to write the device ");
//         scanf ("%c", &ch);
//
//
//         switch (ch) {
//                 case 'w':
//                        printf (" Enter the data to be written into device");
//                         scanf (" %[^\n]", write_buf);
//                         write(fd, write_buf, sizeof(write_buf));
//                         break;
//                 case 'r':
//
//                         read(fd, read_buf, sizeof(read_buf));
//                         printf ("The data in the device is %s\n", read_buf);
//                         break;
//
//                 default:
//                         printf("Wrong choice \n");
//                         break;
//         }
//         close(fd);
// }
