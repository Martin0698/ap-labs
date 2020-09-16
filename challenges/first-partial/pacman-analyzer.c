#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>


struct package {
    char name[200];
    char install_date[200];
    char last_update[200];
    int updates;
    char removal_date[200];
};

struct package paquetes[5000];
int type(char* line);
char* getname(char* line);
char* getdate(char* line);
void analizeLog(char *logFile, char *report);
int get_line(FILE *file, char *buffer, size_t size);



//clasification type of packacges
int type (char* line){
    int start = 0;
    for( int i = 0; i < 2; i++){
        for(start; line[start] != '\0'; start++){
            if(line[start] == ']')
                break;
            
        }
        start += 2;
    }

    if(line[start] == 'i' && line[start + 1] == 'n' && line[start + 2] == 's' )
        return 1;
    if(line[start] == 'u' && line[start + 1] == 'p' && line[start + 2] == 'g' )
        return 2;
    if(line[start] == 'r' && line[start + 1] == 'e' && line[start + 2] == 'm' )
        return 3;
    return 0;
}

//Getter date
char* getdate(char* line){
    int size = 0;
    char *date;
    for (size; line[size] != ']'; size++);
    size++;
    date = calloc(1,size);
    int counter = 0;
    for (int i =0; i < size; i++, counter++){
        date[counter] = line[i];
    }
    return date;
}

//Getter name
char* getname(char* line){
    int counter = 0, start = 0, size = 0;

    for(int i = 0; i<2; i++){
        for (start; line[start] != ']'; start++);
        start += 2;
    }

    for (start; line[start] != ' '; start++);
    start++;
    for(int j = start + 1; line[j] != ' '; j++){
        size++;
    }
    char *name = calloc(1,size);

    for(int k = start; line[k] != ' '; k++, counter++){
        name[counter] = line[k];
    }
    return name;
    
}






//Get line implementation
int get_line(FILE *file, char *buffer, size_t size){
    if (size == 0)
        return 0;
    
    size_t current = 0;
    int c;

    while((c = (char) getc(file)) != '\n' && current < size){
        if(c == EOF){
            break;
        }
        buffer[current] = (char) c;
        current++;
    }
    if (current == 0)
        return 0;
    
    buffer[current] = '\0';
    return current;
}



//Analize the file and use the get line , get name, get date ando classify the type of packages 
void analizeLog(char *logFile, char *report) {
    printf("Generating Report from: [%s] log file\n", logFile);

    // Implement your solution here.

    char line[255];
    int c;

    FILE* file;
    file = fopen(logFile, "r");

    if(file == NULL){
        perror("Error opening the log file\n");
        exit(EXIT_FAILURE);
    }

    
    int w = open(report, O_WRONLY|O_CREAT|O_TRUNC,0644);
    if (w < 0){
        perror("Error opening or creating the report file");
        exit(EXIT_FAILURE);
    }

    int install = 0, 
        remove = 0, 
        upgrade = 0, 
        current = 0;
    while (c = get_line(file,line,255) > 0){
        int n = type(line);
        if(n==1){
            char* name = getname(line);
            char* date = getdate(line);
            strcpy(paquetes[current].name,name);
            strcpy(paquetes[current].install_date,date);
            paquetes[current].updates = 0;
            strcpy(paquetes[current].removal_date, "-");
            current++;
            install++;
        } else if (n==2){
            char* name = getname(line);
            char* date = getdate(line);
            for (int i =0; i < 1500; i++){
                if(strcmp(paquetes[i].name,name) == 0){
                    strcpy(paquetes[i].last_update,date);
                    if(paquetes[i].updates == 0)
                        upgrade++;
                    paquetes[i].updates++;
                    break;
                }
            }
        } else if(n==3){
            char* name = getname(line);
            char* date = getdate(line);
            for(int i = 0; i<1500; i++){
                if(strcmp(paquetes[i].name,name) == 0)
                    strcpy(paquetes[i].removal_date,date);
                break;
            }
            remove++;
        }
        
    }

    write(w, "Pacman Packages Report\n", strlen("Pacman Packages Report\n"));
    write(w,"----------------------\n",strlen("----------------------\n"));
    char aux[10];
    write(w, "Installed paquetes : ", strlen("Installed paquetes : "));
    sprintf(aux, "%d\n", install);
    write(w, aux, strlen(aux));
    write(w, "Upgraded paquetes : ",strlen("Upgraded paquetes : "));
    sprintf(aux, "%d\n", upgrade);
    write(w, aux, strlen(aux));
    write(w, "Removed paquetes : ",strlen("Removed paquetes : "));
    sprintf(aux, "%d\n", remove);
    write(w, aux, strlen(aux));
    write(w, "Current install : \n",strlen("Current install : "));
    sprintf(aux, "%d\n", (install-remove));
    write(w, aux, strlen(aux));

    write(w, "\n\nList of paquetes\n", strlen("\n\nList of paquetes\n"));
    write(w,"----------------------\n",strlen("----------------------\n"));
    for(int i = 0; i < 1500; i++){
        if(strcmp(paquetes[i].name, "") != 0){
            write(w, "- Package name         : ",strlen("- Package name         : "));
            write(w,paquetes[i].name, strlen(paquetes[i].name));
            write(w, "\n   - Install date      : ",strlen("\n   - Install date      : "));
            write(w,paquetes[i].install_date, strlen(paquetes[i].install_date));
            write(w, "\n   - Last update date  : ",strlen("\n   - Last update date  : "));
            write(w,paquetes[i].last_update, strlen(paquetes[i].last_update));
            write(w, "\n   - How many updates  : ",strlen("\n   - How many updates  : "));
            sprintf(aux, "%d", paquetes[i].updates);
            write(w,aux, strlen(aux));
            write(w, "\n   - Removal date      : ",strlen("\n   - Removal date      : "));
            write(w,paquetes[i].removal_date, strlen(paquetes[i].removal_date));
            write(w, "\n",strlen("\n"));
        } else if (strcmp(paquetes[i].name, "") == 0){
            break;
        }
    }

    if(close(w) < 0){
        perror("Error trying to close file");
        exit(1);
    }



    printf("Report is generated at: [%s]\n", report);
}



int main(int argc, char **argv) {

    if (argc < 5 || strcmp(argv[1],"-input") != 0 || strcmp(argv[3],"-report") != 0) {
        printf("Usage:./pacman-analizer.o -input <input_file.txt> -report <report_file.txt>\n");
        return 1;
    }
    analizeLog(argv[2],argv[4]);

    return 0;
}