#include <sys/inotify.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <ftw.h>
#include <fcntl.h> 
#include "logger.h" 

#define MAX_EVENTS 250
#define _XOPEN_SOURCE 500

#define TAMANO_BUFFER  (10 * (sizeof(struct inotify_event) + 1024 + 1))


int notificacion, eventos;

char buffer[TAMANO_BUFFER] __attribute__ ((aligned(8)));
ssize_t num_read;
char *pointer;    
struct inotify_event * evento;
int new_directory = 0;



int revisar_directorios(const char *path_name, const struct stat *sub_dirs, int tflag){
    eventos = inotify_add_watch(notificacion,path_name,IN_ALL_EVENTS);
    if(eventos == -1)
        return -1;
    if(new_directory == 0)
        infof("Watching : %s\n"),path_name;
    return 0;
}


static void mostrar_notificacion(struct inotify_event * notificacion_evento){
    char old_name[1024];
    if( notificacion_evento-> mask & IN_CREATE){
        if(evento -> mask & IN_ISDIR){
            infof("- [Directory - Create] - %s\n", notificacion_evento -> name);
            new_directory = 1;
        } else
            infof("- [File - Create] - %s\n",notificacion_evento->name);
        
    }

    if(notificacion_evento -> mask & IN_DELETE){
        if(evento -> mask & IN_ISDIR)
            infof("- [Directory - Removal] - %s\n",notificacion_evento->name);
        else
            infof("- [File - Removal] - %s\n",notificacion_evento->name);
        
    }

    if( notificacion_evento -> mask & IN_MODIFY){
        if(evento -> mask & IN_ISDIR)
            infof("- [Directory - Modify] - %s\n",notificacion_evento->name);
        else
            infof("- [File - Modify] - %s\n",notificacion_evento->name);
        
    }

    if(notificacion_evento -> mask & IN_MOVED_FROM)
        strcpy(old_name, notificacion_evento->name);
    
    if(notificacion_evento -> mask & IN_MOVED_TO){
        if(notificacion_evento -> cookie > 0){
            if(evento -> mask & IN_ISDIR)
                infof("- [Directory - Rename] - %s\n",notificacion_evento->name);
            else
                infof("- [File - Rename] - %s\n",notificacion_evento->name);
        }
        memset(old_name, 0, strlen(old_name));
    }
}






int main(int argc, char *argv[]){
    if(argc < 2 || strcmp(argv[1], "--help") == 0)
        errorf("Usage is: %s <PATHNAME>\n", argv[0]);
    if (argc < 2)
        exit(-1);
    if(argc == 2){
        notificacion = inotify_init();
        if(notificacion == -1){
            errorf("Error initializing inotify");
            exit(0);
        }
        ftw(argv[1], revisar_directorios, 2048);
        for(;;){
            num_read = read(notificacion, buffer, TAMANO_BUFFER);
            if(num_read == 0)
                infof("read() from inotify fd returned 0");

            for(pointer = buffer; pointer < buffer + num_read; ){
                evento = (struct inotify_event * ) pointer;
                mostrar_notificacion(evento);
                pointer += sizeof(struct inotify_event) + evento -> len;
            }

            if(new_directory == 1){
                ftw(argv[1], revisar_directorios, 2048);
                new_directory = 0;
            }    
        }
        inotify_rm_watch(notificacion, eventos);
        close(notificacion);
        return 0;
    }

    
    return 0;
}
