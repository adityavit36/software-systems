#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

struct Courses {
    char courseId[50];
    char course_name[50];
    char department[50];
    int seats;
    int credits;
    int seats_available;
};

struct Prof {
    char key[MAX_USERNAME_LENGTH];
    char name[MAX_USERNAME_LENGTH];
    char department[MAX_PASSWORD_LENGTH];
    char designation[MAX_USERNAME_LENGTH];
    char address[MAX_USERNAME_LENGTH];
};

struct Stud {
    char name[50];
    char age[50];
    char key[50];
    char email[50];
    char address[50];
    char active;
};

int authenticate_user(const char *uname, const char *pword, int choice) {
    if (choice == 1) { // Admin Authetication
        int file_descriptor;
        char buffer[100];
        struct User user;
        int flag = 0;
        // Open the file for reading
        file_descriptor = open("Adminid.txt", O_RDONLY);
        if (file_descriptor == -1) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }
        int count = 0;// Read data from the file
        int bytes_read;
        while ((bytes_read = read(file_descriptor, buffer, sizeof(buffer)) > 0)) {
            char *token = strtok(buffer, " \n");  // Split by space and newline
            while (token != NULL) {
                strncpy(user.username, token, MAX_USERNAME_LENGTH);
                token = strtok(NULL, " \n");  // Move to the next token
                if (token != NULL) {
                    strncpy(user.password, token, MAX_PASSWORD_LENGTH);
                }
                if (strcmp(uname,user.username) == 0 && strcmp(pword,user.password) == 0) {
                    flag = 1;
                    break;
                }
                token = strtok(NULL, " \n");  // Move to the next token
            }
            if (flag) break;
        }

        if (bytes_read == -1) {
            perror("Error reading from file");
            close(file_descriptor);
            exit(EXIT_FAILURE);
        }

        // Close the file
        close(file_descriptor);
        return flag;
}

    if (choice == 2) { // Prof Authetication
        int flag = 0;
        int fd = open("Profid.txt", O_RDONLY);
        if (fd == -1) {
            perror("Error opening the file");
            return 1;
        }
        struct User searchPerson;
        ssize_t bytesRead;

        while ((bytesRead = read(fd, &searchPerson, sizeof(struct User))) > 0) {
            if (bytesRead != sizeof(struct User)) {
                perror("Error reading from the file");
                close(fd);
                return 1;
            } 
            if (strcmp(searchPerson.username, uname) == 0 && strcmp(searchPerson.password, pword) == 0) {//  found = 1;
                flag = 1;
                break;
            }
        }
        close(fd);
        return flag;
    }
    if (choice == 3) {
        int flag = 0;
        int fd = open("Studid.txt", O_RDONLY);
        if (fd == -1) {
            perror("Error opening the file");
            return 1;
        }
        struct User searchPerson;
        ssize_t bytesRead;

        while ((bytesRead = read(fd, &searchPerson, sizeof(struct User))) > 0) {
            if (bytesRead != sizeof(struct User)) {
                perror("Error reading from the file");
                close(fd);
                return 1;
            } 
            if (strcmp(searchPerson.username, uname) == 0 && strcmp(searchPerson.password, pword) == 0) {//  found = 1;
                flag = 1;
                break;
            }
        }
        close(fd);
        return flag;
    }
}

int search_key(const char *key) {
    int flag = 0;
    int fd = open("student.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening the file");
        return 1;
    }
    struct Stud searchPerson;
    ssize_t bytesRead;

    while ((bytesRead = read(fd, &searchPerson, sizeof(struct Stud))) > 0) {
        if (bytesRead != sizeof(struct Stud)) {
            perror("Error reading from the file");
            close(fd);
            return 1;
        } 
        if (strcmp(searchPerson.key, key) == 0) {//  found = 1;
            flag = 1;
            break;
        }
    }
    close(fd);
    return flag;
}

int activate_student(const char *login) {
    int flag = 0;
    if (!search_key(login)) return 0;
    int fd = open("student.txt", O_RDWR);
    if (fd == -1) {
        perror("Error opening the file");
        return 0;
    }
    struct Stud searchPerson;
    ssize_t bytesRead;
    while ((bytesRead = read(fd, &searchPerson, sizeof(struct Stud))) > 0) {
        if (bytesRead != sizeof(struct Stud)) {
            perror("Error reading from the file");
            close(fd);
            return 0;
        }
        if (strcmp(searchPerson.key, login) == 0) {
	        flag = 1;
            searchPerson.active = 'Y';
	        lseek(fd, -1 * sizeof(struct Stud),SEEK_CUR);
	        write(fd,&searchPerson,sizeof(struct Stud));
            break;
         }
    }
    close(fd);
    return flag;
}


int change_student_password(const char *login,const char *pword) {
    int flag = 0;
    if (!search_key(login))
       return 0;
    int fd = open("Studid.txt", O_RDWR);
    if (fd == -1) {
        perror("Error opening the file");
        return 0;
    }
    struct User searchPerson;
    ssize_t bytesRead;
    while ((bytesRead = read(fd, &searchPerson, sizeof(struct User))) > 0) {
        if (bytesRead != sizeof(struct User)) {
            perror("Error reading from the file");
            close(fd);
            return 0;
        }
        if (strcmp(searchPerson.username, login) == 0) {//  found = 1;
	        flag = 1;
            strcpy(searchPerson.password,pword);
	        lseek(fd, -1 * sizeof(struct User),SEEK_CUR);        
	        write(fd,&searchPerson,sizeof(struct User));
            break;
         }
    }
    close(fd);
    return flag;
}

int change_faculty_password(const char *login,const char *pword) {
    int flag = 0;
    if (!search_key(login)) return 0;
    int fd = open("Profid.txt", O_RDWR);
    if (fd == -1) {
        perror("Error opening the file");
        return 0;
    }
    struct User searchPerson;
    ssize_t bytesRead;
    while ((bytesRead = read(fd, &searchPerson, sizeof(struct User))) > 0) {
        if (bytesRead != sizeof(struct User)) {
            perror("Error reading from the file");
            close(fd);
            return 0;
        }
        if (strcmp(searchPerson.username, login) == 0) {//  found = 1;
	        flag = 1;
            strcpy(searchPerson.password,pword);
	        lseek(fd, -1 * sizeof(struct User),SEEK_CUR);        
	        write(fd,&searchPerson,sizeof(struct User));
            break;
         }
    }
    close(fd);
    return flag;
}

int add_student(int key, const char *uname, int age, const char *email, const char *addr,const char *pword) {
    int flag = 1;
    char str[10];
    sprintf(str, "%d", key);
    if (search_key(str)) return 0;
    int fd = open("student.txt",O_WRONLY | O_APPEND);
    char str1[10];
    sprintf(str1, "%d", age);
    struct Stud student;
    strcpy(student.key, str);
    strcpy(student.name, uname);
    strcpy(student.age, str1);
    strcpy(student.address, addr);
    strcpy(student.email, email);
    student.active = 'Y';
    ssize_t bytes_written = write(fd, &student, sizeof(struct Stud));
    if (bytes_written == -1) {
        flag = 0;
        perror("Error writing to the file");
        close(fd);
        return 1;
    }
    close(fd);
    int fd1 = open("Studid.txt",O_WRONLY | O_APPEND);
    char login[] = "MT2023";
    sprintf(login + strlen(login), "%d", key);
    struct User user;
    strcpy(user.username,login);
    strcpy(user.password,pword);
    printf("%s\n",user.username);
    printf("%s\n",user.password);
    bytes_written = write(fd1, &user, sizeof(struct User));
    if (bytes_written == -1) {
        flag = 0;
        perror("Error writing to the file");
        close(fd);
        return 1;
    }
    close(fd1);
    return flag;
}   

int block_student(const char *login) {
int flag = 0;
    if (!search_key(login)) return 0;
    int fd = open("student.txt", O_RDWR);
    if (fd == -1) {
        perror("Error opening the file");
        return 0;
    }
    struct Stud searchPerson;
    ssize_t bytesRead;
    while ((bytesRead = read(fd, &searchPerson, sizeof(struct Stud))) > 0) {
        if (bytesRead != sizeof(struct Stud)) {
            perror("Error reading from the file");
            close(fd);
            return 0;
        }
        if (strcmp(searchPerson.key, login) == 0) {
	        flag = 1;
            searchPerson.active = 'D';
	        lseek(fd, -1 * sizeof(struct Stud),SEEK_CUR);
	        write(fd,&searchPerson,sizeof(struct Stud));
            break;
         }
    }
    close(fd);
    return flag;
}

int search_key_faculty(const char *login) {
    int flag = 0;
    int fd = open("faculty.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening the file");
        return 1;
    }
    struct Prof searchPerson;
    ssize_t bytesRead;

    while ((bytesRead = read(fd, &searchPerson, sizeof(struct Prof))) > 0) {
        if (bytesRead != sizeof(struct Prof)) {
            perror("Error reading from the file");
            close(fd);
            return 1;
        } 
        if (strcmp(searchPerson.key, login) == 0) {//  found = 1;
            flag = 1;
            break;
        }
    }
    close(fd);
    return flag;
}

int add_faculty(int key,const char *uname,const char *design,const char *dept,const char *addr,const char *pword) {
    int flag = 1;
    char str[10];
    sprintf(str, "%d", key);
    if (search_key_faculty(str)) return 0;
    int fd = open("faculty.txt",O_WRONLY | O_APPEND);
    struct Prof fac;
    strcpy(fac.key, str);
    strcpy(fac.name, uname);
    strcpy(fac.designation, design);
    strcpy(fac.address, addr);
    strcpy(fac.department, dept);
    ssize_t bytes_written = write(fd, &fac, sizeof(struct Prof));
    if(bytes_written == -1) {
       flag = 0;
       perror("Error writing to the file");
       close(fd);
       return 1;
    }
    close(fd);
    int fd1 = open("Profid.txt",O_WRONLY | O_APPEND);
    char login[] = "Prof";
    sprintf(login + strlen(login), "%d", key);
    struct User user;
    strcpy(user.username,login);
    strcpy(user.password,pword);
    bytes_written = write(fd1, &user, sizeof(struct User));
    if (bytes_written == -1) {
        flag = 0;
        perror("Error writing to the file");
        close(fd1);
        return 1;
    }
    close(fd1);
    return flag;
}

int modify_student(const char *login,int option, const char *pword) {
    int flag = 0;
    if (!search_key(login)) {
        printf("Student ID not found\n");
       return 0;
    }
    int fd = open("student.txt", O_RDWR);
    if (fd == -1) {
        perror("Error opening the file");
        return 0;
    }
    struct Stud searchPerson;
    ssize_t bytesRead;
    while ((bytesRead = read(fd, &searchPerson, sizeof(struct Stud))) > 0) {
        if (bytesRead != sizeof(struct Stud)) {
            perror("Error reading from the file");
            close(fd);
            return 0;
        }
       // printf("Inside loop\n");
        if (strcmp(searchPerson.key, login) == 0) {//  found = 1;
	        flag = 1;
            printf("%s\n", login);
            printf("%s\n", pword);
            if (option == 1)   strcpy(searchPerson.name,pword);
            if (option == 2)   strcpy(searchPerson.age,pword);
            if (option == 3)   strcpy(searchPerson.email,pword);
            if (option == 4)   strcpy(searchPerson.address,pword);
	        lseek(fd, -1 * sizeof(struct Stud),SEEK_CUR);
	        write(fd,&searchPerson,sizeof(struct Stud));
            break;
         }
    }
    close(fd);
    if (!flag) printf("Student data not modified\n");
    return flag;
}

int modify_faculty(const char *login,int option, const char *pword) {
    int flag = 0;
    if (!search_key_faculty(login)) return 0;
    int fd = open("faculty.txt", O_RDWR);
    if (fd == -1) {
        perror("Error opening the file");
        return 0;
    }
    struct Prof searchPerson;
    ssize_t bytesRead;
    while ((bytesRead = read(fd, &searchPerson, sizeof(struct Prof))) > 0) {
        if (bytesRead != sizeof(struct Prof)) {
            perror("Error reading from the file");
            close(fd);
            return 0;
        }
        if (strcmp(searchPerson.key, login) == 0) {//  found = 1;
	        flag = 1;
            if (option == 1)  strcpy(searchPerson.name,pword);
            if (option == 2)  strcpy(searchPerson.designation,pword);
            if (option == 3)  strcpy(searchPerson.department,pword);
            if (option == 4)  strcpy(searchPerson.address,pword);
	        lseek(fd, -1 * sizeof(struct Prof),SEEK_CUR);        
	        write(fd,&searchPerson,sizeof(struct Prof));
            break;
         }
    }
    close(fd);
    return flag;
}

void view_student(const char *buffer) {
    int fd = open("student.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening the file");
        return;
    }

    struct Stud searchPerson;
    char searchName[100];
    int found = 0;
    ssize_t bytesRead;

    while ((bytesRead = read(fd, &searchPerson, sizeof(struct Stud))) > 0) {
        if (bytesRead != sizeof(struct Stud)) {
            perror("Error reading from the file");
            close(fd);
            return;
        } 
        if (strcmp(searchPerson.key, buffer) == 0) {//  found = 1;
            printf("Record found:\n");
            printf("Key: %s\n", searchPerson.key);
            printf("Name: %s\n", searchPerson.name);
            printf("Email: %s\n", searchPerson.email);
            printf("Age: %s\n", searchPerson.age);
            printf("Address: %s\n", searchPerson.address);
            printf("Active Status: %c\n", searchPerson.active);
            found = 1;
            break;
        }
    }

    if (!found) printf("Record not found.\n");
    close(fd);
    return;
}
void view_faculty(const char *buffer) {
    int fd = open("faculty.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening the file");
        return;
    }

    struct Prof searchPerson;
    char searchName[100];
    int found = 0;
    ssize_t bytesRead;

    while ((bytesRead = read(fd, &searchPerson, sizeof(struct Prof))) > 0) {
        if (bytesRead != sizeof(struct Prof)) {
            perror("Error reading from the file");
            close(fd);
            return;
        } 
        if (strcmp(searchPerson.key, buffer) == 0) {
            printf("Record found:\n");
            printf("Key: %s\n", searchPerson.key);
            printf("Name: %s\n", searchPerson.name);
            printf("designation: %s\n", searchPerson.department);
            printf("address: %s\n", searchPerson.address);
            printf("designation: %s\n", searchPerson.designation);
            found = 1;
            break;
        }
    }

    if (!found) printf("Record not found.\n");
    close(fd);
    return;
}

int main(void) {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Error creating server socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(12345);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error binding server socket");
        exit(EXIT_FAILURE);
    }


    if (listen(server_socket, 5) == -1) {
        perror("Error listening for connections");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening for incoming connections...\n");
    int flag = 0;
    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_socket == -1) 
         perror("Error accepting client connection");
     
    while (1) { // Accept incoming connection
        int choice, found = 0;
        char user_name[80];
        printf("Accepted connection from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        recv(client_socket, &choice, sizeof(int), 0);
        found = choice;
        if (choice == 1) {
            found = 1;
            printf("Client is Admin\n");
        }
        else if (choice == 2) {
            found = 2;
            printf("Client is Professor\n");
        }
        else if (choice == 3) {
            found = 3;
            printf("Client is Student\n");
        }
        send(client_socket,&found,sizeof(found), 0);
        if (choice > 3) {
            flag = 1;
            close(client_socket);
            close(server_socket);
            exit(0);
        }
        
        char username[MAX_USERNAME_LENGTH];
        char password[MAX_PASSWORD_LENGTH];
        if (recv(client_socket, username, sizeof(username), 0) == -1) {
            perror("Error receiving username");
            close(client_socket);
            continue;
        }
        if (recv(client_socket, password, sizeof(password), 0) == -1) {
            perror("Error receiving password");
            close(client_socket);
            continue;
        } // Authenticate the user
        int succ = 0;
        if (authenticate_user(username, password,choice)) {
            const char *success_message = "Login successful";
            strcpy(user_name,username);
            succ = 1;
            send(client_socket, success_message, strlen(success_message), 0);
            printf("Login successful for user: %s\n", username);
        } 
        else {
            const char *failure_message = "Login failed";
            send(client_socket, failure_message, strlen(failure_message), 0);
            printf("Login failed for user: %s\n", username);
        }
        if(succ) {
            if (choice == 1) {
                int pick;
                recv(client_socket, &pick, sizeof(int), 0);
                if (pick == 1) {
                    printf("Add Student\n");
                    int key;
                    int found = 1;
                    char name[50];
                    int age_student = 0;
                    char email[50];
                    char addr[50];
                    char pword[50];
                    char buffer[50];
                    recv(client_socket, &key, sizeof(int), 0);
                    recv(client_socket, &age_student, sizeof(int), 0);
                    recv(client_socket,buffer, sizeof(buffer), 0);
                    strcpy(name,buffer);
                    bzero(buffer,sizeof(buffer));
                    recv(client_socket, buffer, sizeof(buffer), 0);
                    strcpy(email,buffer);        
                    bzero(buffer,sizeof(buffer));
                    recv(client_socket, buffer, sizeof(buffer), 0);
                    strcpy(addr,buffer);        
                    bzero(buffer,sizeof(buffer));
                    recv(client_socket, buffer, sizeof(buffer), 0);
                    strcpy(pword,buffer);
                    bzero(buffer,sizeof(buffer));
                    if(add_student(key,name,age_student,email,addr,pword)) {
                        printf("Data Added Successfully\n");
                    }
                    else printf("Student Data Already Exists\n");
                }
                else if (pick == 2) {
                    printf("View Student Details\n");
                    char buffer[80];
                    recv(client_socket,buffer,sizeof(buffer),0);
                    view_student(buffer);
                }
                else if (pick == 3) {
                    printf("Add Faculty\n");
                    int key;
                    char name[50];
                    int age_student = 0;
                    char design[50];
                    char addr[50];
                    char pword[50];
                    char dept[50];
                    char buffer[50];
                    recv(client_socket, &key, sizeof(int), 0);
                    recv(client_socket,buffer, sizeof(buffer), 0);
                    strcpy(name,buffer);
                    bzero(buffer,sizeof(buffer));
                    recv(client_socket, buffer, sizeof(buffer), 0);
                    strcpy(design,buffer);        
                    bzero(buffer,sizeof(buffer));
                    recv(client_socket, buffer, sizeof(buffer), 0);
                    strcpy(dept,buffer);        
                    bzero(buffer,sizeof(buffer));
                    recv(client_socket, buffer, sizeof(buffer), 0);
                    strcpy(addr,buffer);
                    bzero(buffer,sizeof(buffer));
                    recv(client_socket, buffer, sizeof(buffer), 0);
                    strcpy(pword,buffer);
                    bzero(buffer,sizeof(buffer));
                    if(add_faculty(key,name,design,dept,addr,pword)) printf("Professor Data Added Successfully\n");
                }
                else if (pick == 4) {
                    char buffer[80];
                    printf("View Faculty Details\n"); 
                    recv(client_socket,buffer,sizeof(buffer),0);
                    view_faculty(buffer);
                }
                else if (pick == 5) {
                    char buffer[80];
                    recv(client_socket,buffer,sizeof(buffer),0);
                    printf("Activate Student Id\n");
                    if(activate_student(buffer)) printf("Student Data Activated Successfully\n");
                    else printf("Student Data Not Activated\n");
                }
                else if (pick == 6) {
                    printf("Block Student id\n");
                    char buffer[80];
                    recv(client_socket,buffer,sizeof(buffer),0);
                    if(block_student(buffer)) printf("Student Data Blocked Successfully\n");
                    else printf("Student Data Not Activated\n");
                }
                else if (pick == 7) {
                    printf("Modify Student Details\n");
                    char buffer[80]; // key
                    char ans[80];
                    char data[80];
                    int option;// option
                    recv(client_socket,&option,sizeof(int),0);
                    recv(client_socket,buffer,sizeof(buffer),0);
                    strcpy(data,buffer);
                    bzero(buffer,sizeof(buffer));
                    recv(client_socket,buffer,sizeof(buffer),0);
                    strcpy(ans,buffer);
                    bzero(buffer,sizeof(buffer));
                    if (modify_student(data,option,ans)) printf("Student Data Modified Successfully\n");
                    else printf("Student Data Not Modified\n");
                }
                else if (pick == 8) {
                    printf("Modify Faculty details\n");
                    char buffer[80]; // key
                    char ans[80];
                    char data[80];
                    int option;// option
                    recv(client_socket,&option,sizeof(int),0);
                    recv(client_socket,buffer,sizeof(buffer),0);
                    strcpy(data,buffer); // Key
                    bzero(buffer,sizeof(buffer));
                    recv(client_socket,buffer,sizeof(buffer),0);
                    strcpy(ans,buffer); // modi
                    if (modify_faculty(data,option,ans)) printf("Faculty Data Modified Successfully\n");
                    else printf("Faculty Data Not Modified\n");
                }
                else if (pick == 9) {
                    printf("Logout and Exit\n");
                    flag = 1;
                    close(client_socket);
                    close(server_socket);
                    exit(0);
                }
            }
            else if (choice == 2) {
                int pick;
                recv(client_socket, &pick, sizeof(int), 0);
                if (pick == 1) {

                }
                else if (pick == 2) {

                }
                else if (pick == 3) {

                }
                else if (pick == 4) {

                }
                else if (pick == 5) {
                    char buffer[80];
                    char pword[80];
                    int msg = 0;
                    recv(client_socket,buffer,sizeof(buffer),0);
                    strcpy(pword,buffer);
                    bzero(buffer,sizeof(buffer));
                    if (change_faculty_password(user_name, pword)) {
                        msg = 1;
                        send(client_socket,&msg,sizeof(msg),0);
                    }
                    else send(client_socket,&msg,sizeof(msg),0);
                }
                else if (pick == 6) {
                    flag = 1;
                    close(client_socket);
                    close(server_socket);
                    exit(0);
                }
            }
            else if (choice == 3) {
                int pick;
                recv(client_socket, &pick, sizeof(int), 0);
                if (pick == 1) {

                }
                else if (pick == 2) {

                }
                else if (pick == 3) {

                }
                else if (pick == 4) {

                }
                else if (pick == 5) {
                    char buffer[80];
                    char pword[80];
                    int msg = 0;
                    recv(client_socket,buffer,sizeof(buffer),0);
                    strcpy(pword,buffer);
                    bzero(buffer,sizeof(buffer));
                    if (change_student_password(user_name, pword)) {
                        msg = 1;
                        send(client_socket,&msg,sizeof(msg),0);
                    }
                    else send(client_socket,&msg,sizeof(msg),0);
                }
                else if (pick == 6) {
                    flag = 1;
                    close(client_socket);
                    close(server_socket);
                    exit(0);
                }
            }
        }
    }
    if (flag == 0) {
        close(server_socket);
        close(client_socket);
        exit(0);
    }
    return 0;
}