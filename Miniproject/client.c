#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int main() {
    int client_socket;
    struct sockaddr_in server_addr;

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Error creating client socket");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
            perror("Error connecting to server");
            exit(EXIT_FAILURE);
    }
    while(1) {    
        int choice, ans; 
        printf("Enter Choice for \n1.Admin\n2.Professor\n3.Student\n");
        scanf("%d",&choice);
        send(client_socket,&choice,sizeof(int),0);
        
        recv(client_socket, &ans, sizeof(int), 0);
        printf("Server's Response: %d", ans);
        if(ans == 1)
           printf("Admin\n");
        else if(ans == 2) 
           printf("Professor\n");
        else if (ans == 3) 
          printf("Student\n");
        else if (ans > 3) { 
          close(client_socket);
          exit(0);
        }
        char username[MAX_USERNAME_LENGTH];
        char password[MAX_PASSWORD_LENGTH];

        printf("Username: ");
        scanf("%s", username);
        printf("Password: ");
        scanf("%s", password);

        // Send username and password to the server
        send(client_socket, username, strlen(username), 0);
        send(client_socket, password, strlen(password), 0);

        char response[100]; // Receive the response from the server
        if (recv(client_socket, response, sizeof(response), 0) == -1) perror("Error receiving response");
        else  printf("Server response: %s\n", response);
        char ch = response[6]; //printf("%c\n",ch);
        if (ch == 's') {
            if (choice == 1) {
                int pick;
                printf("Welcome to Admin Menu.\n1.Add Student\n2.View Student Details\n3.Add Faculty\n4.View Faculty Details\n5.Activate Student\n6.Block Student\n7.Modify Student Details\n8.Modify Faculty Details\n9.Logout and Exit\n");
                printf("Pick Options from Admin Menu\n");
                scanf("%d",&pick);
                send(client_socket,&pick,sizeof(int),0);
                if (pick == 1) {
                    int age;
                    int key;
                    char name[50];
                    char email[50];
                    char address[50];
                    char password[50];
                    printf("Enter key for Student\n");
                    int found;
                    scanf("%d", &key);
                    send(client_socket, &key, sizeof(int), 0);
                    printf("Enter Age for Student\n");
                    scanf("%d", &age);
                    send(client_socket, &age, sizeof(int), 0);
                    printf("Enter Name for Student\n");
                    scanf("%s",name);
                    name[strlen(name)]='\0';
                    send(client_socket,name, strlen(name), 0);
                    printf("Enter Email for Student\n");
                    scanf("%s",email);
                    email[strlen(email)]='\0';
                    send(client_socket,email, strlen(email), 0);
                    printf("Enter Address for Student\n");
                    scanf("%s",address);
                    address[strlen(address)]='\0';
                    send(client_socket,address, strlen(address), 0);
                    printf("Enter password for Student\n");
                    scanf("%s", password);
                    password[strlen(password)]='\0';
                    send(client_socket,password, strlen(password), 0);
                }
                else if (pick == 2) {
                    char id[100];
                    printf("Enter Student's Key search the Record\n");
                    scanf("%s",id);
                    id[strlen(id)]='\0';
                    send(client_socket,id,strlen(id),0);
                }
                else if(pick == 3) {
                    int key;
                    char name[50];
                    char email[50];
                    char address[50];
                    char dept[50];
                    char design[50];
                    char password[50];
                    printf("Enter key for Professor\n");
                    scanf("%d", &key);
                    send(client_socket, &key, sizeof(int), 0);
                    printf("Enter Name for Professor\n");
                    scanf("%s",name);
                    name[strlen(name)]='\0';
                    send(client_socket,name, strlen(name), 0);
                    printf("Enter Designation for Professor\n");
                    scanf("%s", design);
                    design[strlen(design)]='\0';
                    send(client_socket,design, strlen(design), 0);
                    printf("Enter Department for Professor\n");
                    scanf("%s", dept);
                    dept[strlen(dept)]='\0';
                    send(client_socket,dept, strlen(dept), 0);
                    printf("Enter Address for Professor\n");
                    scanf("%s",address);
                    address[strlen(address)]='\0';
                    send(client_socket,address, strlen(address), 0);
                    printf("Enter Password for Professor\n");
                    scanf("%s", password);
                    password[strlen(password)]='\0';
                    send(client_socket,password, strlen(password), 0);
                }
                else if (pick == 4) {
                    printf("Enter Key to view Professor's Profile\n");
                    char act[80];
                    scanf("%s",act);
                    act[strlen(act)] = '\0';
                    send(client_socket,act,strlen(act),0);
                }
                else if (pick == 5) {
                    printf("Enter Key to Activate Student\n");
                    char act[80];
                    scanf("%s",act);
                    act[strlen(act)] = '\0';
                    send(client_socket,act,strlen(act),0);
                }
                else if (pick == 6) {
                    printf("Enter Key to Deactivate Student\n");
                    char act[80];
                    scanf("%s",act);
                    act[strlen(act)] = '\0';
                    send(client_socket,act,strlen(act),0);
                }
                else if (pick == 7) {
                    printf("What do you want to modify in student Details: \n1.Name\n2.Age\n3.Email Id\n4.Address\n");
                    int a;
                    scanf("%d",&a);
                    send(client_socket,&a,sizeof(int),0);
                    char ans[80];
                    char buffer[80];
                    printf("Enter Key for student\n");
                    scanf("%s",ans);
                    ans[strlen(ans)] = '\0';
                    send(client_socket,ans,strlen(ans),0);
                    printf("Enter data for student\n");
                    scanf("%s",buffer);
                    buffer[strlen(buffer)] = '\0';
                    send(client_socket,buffer,strlen(buffer),0);
                }
                else if (pick == 8) {
                    printf("What do you want to modify in Professor Details: \n1.Name\n2.Designation\n3.Department\n4.Address\n");
                    int a;
                    scanf("%d",&a);
                    send(client_socket,&a,sizeof(int),0);
                    char ans[80];
                    char buffer[80];
                    printf("Enter Key for student\n");
                    scanf("%s",ans);
                    ans[strlen(ans)] = '\0';
                    send(client_socket,ans,sizeof(ans),0);
                    printf("Enter data for student\n");
                    scanf("%s",buffer);
                    buffer[strlen(buffer)] = '\0';
                    send(client_socket,buffer,strlen(buffer),0);
                }
                else if (pick == 9){
                    close(client_socket);
                    exit(0);
                }
            }
            else if (choice == 2) {
                int pick;
                printf("Welcome to Faculty Menu.\n1.View Offering Courses\n2.Add New Course\n3.Remove Course from Catalog\n4.Update Course Details\n5.Change Password\n6.Logout and Exit\n");
                printf("Pick Options from Faculty Menu\n");
                scanf("%d",&pick);
                send(client_socket,&pick,sizeof(int),0);
                if (pick == 6) {
                    close(client_socket);
                    exit(0);
                }
            }
            else if (choice == 3) {
                int pick;
                printf("Welcome to Student Menu.\n1.View All Courses\n2.Enroll (New) Course\n3.Remove Course\n4.View Enrolled Course Details\n5.Change Password\n6. Logout and Exit\n");
                printf("Pick Options from Student Menu\n");
                scanf("%d",&pick);
                send(client_socket,&pick,sizeof(int),0);
                if (pick == 1) {
                }
                else if(pick == 3) {
                    
                }
                else if (pick == 5) {
                    printf("Enter New Password for Student\n");
                    char new_password[50];
                    scanf("%s",new_password);
                    new_password[strlen(new_password)] = '\0';
                    send(client_socket,new_password,strlen(new_password),0);
                    int msg;
                    recv(client_socket,&msg,sizeof(msg),0);
                    if (msg) printf("Student Password Updated Successfully\n");
                    else printf("Student Password Not Updated Successfully\n");
                }
                else if (pick == 6) {
                    close(client_socket);
                    exit(0);    
                }
            }
        }
    }
    close(client_socket);
    return 0;
}