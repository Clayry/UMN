#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
int main() {
    char my_write_str[] = "1234567890";

    char my_read_str[100];

    char my_filename[] = "dummy.txt";

    int my_file_descriptor, close_err;

    my_file_descriptor = open(my_filename, O_RDWR | O_CREAT | O_TRUNC);

    write(my_file_descriptor, (void *)my_write_str, 10);

    fsync(my_file_descriptor);

    lseek(my_file_descriptor, 0, SEEK_SET);

    read(my_file_descriptor, (void *)my_read_str, 10);

    my_read_str[10] = '\0';

    printf("String read = %s.\n", my_read_str);

    close(my_file_descriptor);

    return 0;
}
