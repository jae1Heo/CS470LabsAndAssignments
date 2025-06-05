#include "Jaewon_libFS2025.h"

// Global variables
FileEntry file_table[MAX_FILES];  // File table to track files
int file_count = 0;               // Number of files in the system

// Create a new file
int fileCreate(const char *filename) {

    // Check if file already exists
    for (int i = 0; i < file_count; i++) {
        if (strcmp(file_table[i].filename, filename) == 0) {
            printf("Error: File '%s' already exists.\n", filename);
            return -1;
        }
    }

    // Create the file on the local disk
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error: Unable to create file '%s'.\n", filename);
        return -1;
    }
    fclose(file);

    // Add file to the file table
    strcpy(file_table[file_count].filename, filename);
    file_table[file_count].size = 0;
    file_table[file_count].is_open = 0;  // File is closed
    file_count++;

    printf("File '%s' created successfully.\n", filename);
    return 0;
}

// Open a file
int fileOpen(const char *filename) {
    for (int i = 0; i < file_count; i++) {
        if (strcmp(file_table[i].filename, filename) == 0) {
            if (file_table[i].is_open) {
                printf("Error: File '%s' is already open.\n", filename);
                return -1;
            }
            file_table[i].is_open = 1;  // Mark file as open
            printf("File '%s' opened successfully.\n", filename);
            return i;  // Return file index
        }
    }

    printf("Error: File '%s' not found.\n", filename);
    return -1;
}

// Write data to a file
int fileWrite(int file_index, const char *data) {

    if (!file_table[file_index].is_open) {
        printf("Error: File '%s' is not open.\n", file_table[file_index].filename);
        return -1;
    }

    int data_size = strlen(data);
    if(data_size >= MAX_FILE_SIZE) {
        fprintf(stderr, "Error: Max size exceeded.\n");
        return -1;
    }

    // Write data to the local file
    FILE *file = fopen(file_table[file_index].filename, "w");
    if (!file) {
        printf("Error: Unable to open file '%s' for writing.\n", file_table[file_index].filename);
        return -1;
    }
    fwrite(data, 1, data_size, file);
    fclose(file);

    file_table[file_index].size = data_size;
    printf("Data written to file '%s' successfully.\n", file_table[file_index].filename);
    return 0;
}

// Read data from a file

int fileRead(int file_index) {
    // checks file existence
    if(!file_table[file_index].is_open) {
        fprintf(stderr, "Error: File \'%s\' is not open.\n", file_table[file_index].filename);
        return -1;
    }

    FILE* temp_pointer = fopen(file_table[file_index].filename, "r");
    if(temp_pointer == NULL) {
        fprintf(stderr, "Unable to open file \'%s\' for reading.\n", file_table[file_index].filename);
        return -1;
    }

    int bread = 0;
    char buf;
    // read each byte from the file
    while((bread = fread((void*)&buf, 1, 1, temp_pointer)) > 0){
        printf("%c", buf);
    }
    printf("\n");
    fclose(temp_pointer);

    return 0;

}


// Close a file
int fileClose(int file_index) {
    
    if(file_table[file_index].is_open) {
        file_table[file_index].is_open = 0; // if file at file_index is opened, close
    }
    else {
        fprintf(stderr, "Error: File \'%s\' is already closed.\n", file_table[file_index].filename);
        return -1;
    }

    fprintf(stdout, "Successfully closed the file \'%s\'.\n", file_table[file_index].filename);
    return 0;
}

// Delete a file

int fileDelete(const char *filename) {
    if(filename == NULL) {
        fprintf(stderr, "Error: Invalid filename.\n");
        return -1;
    }

    int file_len = strlen(filename);
    int found_index = -1;
    int i;
    int found_flag = 0;
    for(i = 0; i < file_count; i++) { // traverse through file table to check file exists
        found_flag = 1; // set the found flag to 1 at every beginning point of the loop
        
        if(strlen(file_table[i].filename) == file_len) { // if filename at current index has same length with target,
            for(int j = 0; j < file_len; j++) { // check by byte-by-byte
                if(file_table[i].filename[j] != filename[j]) {  // if filename is not matching,
                    found_flag = 0; // set the flag to 0
                    break; // escape the loop
                }
            }
        }
        else { // if length of filename is different, 
            found_flag = 0; // set the flag to 0
        }

        if(found_flag) { // if file at current index is matching,
            found_index = i; // save its index in the file table
            fprintf(stdout, "File \'%s\' found.\n", file_table[i].filename);
            break; // break the loop
        }
        
    }

    if(found_index < 0) { // if file not found, 
        fprintf(stderr, "File \'%s\' not found.\n", filename);
        return -1;
    }
    else {  // if found,

        /* build the shell command to delete the found file */
        char* temp = (char*)malloc(4 + FILENAME_MAX);
        strcpy(temp, "rm ");
        strcat(temp, filename);
        int ret = system(temp);
        
        if(ret == -1) { // if file cannot be deleted by system() call returns -1.
                        // this could happen if the current user is not owned the target file. 
            fprintf(stderr, "Cannot delete the file \'%s\'.\n", filename);
            return -1;
        }
        else {
            if(found_index + 1 == file_count) { // if file is located at the end of the table
                memset((void*)file_table[found_index].filename, 0, FILENAME_MAX);
                file_table[found_index].is_open = 0;
                file_table[found_index].size = 0;
            }
            else { // otherwise,
                for(i = found_index; i < file_count - 1; i++) { // shifting file info to left
                    file_table[i] = file_table[i + 1];
                }

                // erasing last shifted file's trace from the table
                memset((void*)file_table[file_count - 1].filename, 0, FILENAME_MAX);
                file_table[file_count - 1].is_open = 0;
                file_table[file_count - 1].size = 0;
            }
        
            file_count--; // decreasing filecount
            fprintf(stdout, "File \'%s\' deleted successfully.\n", filename);
        }

    }

    return 0;
    
}