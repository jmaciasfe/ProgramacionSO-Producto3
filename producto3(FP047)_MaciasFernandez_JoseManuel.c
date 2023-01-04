#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#define MAX_IP_LEN 40
#define MAX_COMMAND_LEN 100
#define MAX_LINE_LEN 255

void leerArchivo();
void adaptadorRed();
void pingDNSs();
void arrancarPing(const char * ip);
void cambiarDns();


int main(){

    int opcion;
    char ip;

    //Menú para seleccionar que opción desea realizar el usuario.
    //Bucle generado para que una vez acabe con una acción se reinicie y el usuario pueda escoger que hacer. 

    do {
        printf("\nSeleccione que desee hacer\n");
        printf("\n1. Leer archivo DNSips.txt\n");
        printf("\n2. Ver informacion del DNS del adaptador que desee.\n");
        printf("\n3. Generar archivo .txt con el resultado ping de DNSips.txt\n");
        printf("\n4. Cambiar DNS(ejecutar .exe como administrador)\n");
        printf("\n5. Salir del programa\n");
        scanf("\n%i", &opcion); 

        switch (opcion){
            case 1: leerArchivo(); 
                    break;
            case 2: adaptadorRed(); 
                    break;  
            case 3: pingDNSs();
                    arrancarPing(ip);
                    break;
            case 4: cambiarDns(); 
                    break;
            case 5: printf("\nHas seleccionado salir del programa\n"); 
                     

        }

    }while (opcion != 5);
    
    system ("pause");

    return 0;
}

void leerArchivo(){

    char aux;
    FILE *f;
    char DNSips[100];
 
    //Preguntamos al usuario en que ruta está el archivo y guardamos la variable. 

    printf("\nIntroduce la ruta del archivo: ");
    scanf("%s", &DNSips);

    //Abrimos el archivo en modo lectura "r".
    f = fopen(DNSips, "r");
    //Bucle el cual nos indica si hay un error abriendo el archivo o si es correcto va leyendo linea por linea el contenido de este. 
    if (f == NULL){
        printf("\nError abriendo el archivo. \n");
        exit(1);
    }
    while (aux != EOF){
        aux = fgetc(f);
        printf("%c", aux);
    }

    fclose(f);

    system ("pause");
}

void adaptadorRed(){

    char command [100];
    char adaptador [50];
    
    //Con el comando ipconfig mostramos los diferentes adaptadores de red que tenemos en nuestro pc.
    strcpy(command, "ipconfig");
    system(command);
    //Preguntamos al usuario que adaptador de red desea ver la información relacionada con el DNS
    printf("\nDe que adaptador de red deseas ver la informacion DNS?\n");
    scanf("%s", &adaptador);
    //Mostramos al usuario que comandos usar para mostrar la información.
    printf("\nHas deseado ver la informacion DNS de %s\n", adaptador);
    printf("\nIntroduzca el siguiente comando: \n");
    printf("interface ip show dns \"%s\"\n", adaptador);
    printf("Escriba exit para salir una vez introducido el comando\n");


    strcpy(command, "netsh");
    system(command);
    //Una vez escritos los comandos nos aparece la información DNS del adaptador seleccionado

    printf("\nEsta es la configuracion DNS del adaptador %s\n", adaptador);


    system("pause");

}

void pingDNSs(){
    //Preguntamos al usuario que archivo quiere abrir y leer las ip's para hacer el ping
    FILE * f;
    char ip[MAX_IP_LEN] = { 0 };
    char DNSips [25];

    printf("Introduzca la ruta del archivo: ");
    scanf("%s", &DNSips);
    //Abre el archivo con las ip's
    f = fopen(DNSips, "r");
    if (f == NULL)
    {
        printf("Problemas de apertura del archivo\n");
    }
    else
    {
        while (fgets(ip, MAX_IP_LEN, f))//Una vez leida la ip entra en la función arrancar ping y nos muestra la información de la dirección ip.
        {
            arrancarPing(ip);
        }
 
        fclose(f);
    }
}

void arrancarPing(const char * ip){

    char line[MAX_LINE_LEN];
    char command[255];
    FILE * fp;
    //Una vez leida la dirección y hecho el ping, nos genera un archivo de texto con la información. 
    sprintf(command, "ping %s > respuesta_ping.txt", ip);

    system(command);
    fp = popen(command, "wt");

    if (fp == NULL)
    {
        return;
    }
 
    while (fgets(line, MAX_LINE_LEN, fp) != NULL)
    {
        printf("%s", line);
    }
    
    pclose(fp);

    printf("Archivo generado: respuesta_ping.txt");

}
    
void cambiarDns(){

    FILE * f;
    char aux;
    char archivo[100];
    char command[255];
    char adaptador [100];

    //Preguntamos al usuario por el archivo generado en el punto anterior para recuperar la información del ping
    printf("Ruta del archivo generado al hacer Ping en el apartado 3: ");
    scanf("%s", &archivo);

    f = fopen(archivo, "r");

    if (f == NULL){
        printf("\nError abriendo el archivo. \n");
        exit(1);
    }
    while (aux != EOF){
        aux = fgetc(f);
        printf("%c", aux);
    }

    fclose(f);

    system("pause");

    //Iniciamos el comando ipconfig para ver los distintos adaptadores y que el usuario pueda seleccionar uno. 
    strcpy(command, "ipconfig");
    system(command);
    //Mostramos al usuario los diferentes pasos que debe seguir para poder seleccionar el adaptador y como cambiar su DNS
    printf("\nDe los siguientes adaptadores seleccione uno para modificar la informacion DNS\n");
    printf("Que adaptador deseas modificar?\n");
    scanf("%s", &adaptador);
    printf("\nHas deseado modificar el DNS de %s\n", adaptador);
    printf("Para modificar el DNS introduzca el siguiente comando:\n");
    printf("interface ip set dns \"%s\" static [direccion DNS] primary\n", adaptador);
    printf("Recuerda poner el DNS que mejor resultado dio en el ping test de la opcion 3\n");
    printf("Recuerda teclear \"exit\" una vez ejecutado el comando\n");

    strcpy(command, "netsh");
    system(command);
    
    //Si el usuario desea ver el resultado de su DNS modificado puede volver a entrar en el punto 2 y verá el resultado de su modificación. 
    printf("\nHas modificado correctamente el DNS de la red \"%s\"\n", adaptador);
    printf("Si deseas ver el cambio ejecuta el punto 2 del programa\n");

    system ("pause");

}

