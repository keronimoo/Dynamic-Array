#include <stdio.h>
#include <stdlib.h>
typedef struct song {
    char* name;
    float duration;
} song;
typedef struct dynamic_array {
    int capacity;
    int size;
    void** elements;
} dynamic_array;
//KEREM YAVUZ ŞENYURT 290201100
//funcion prototypes
void init_array(dynamic_array* array);

void put_element(dynamic_array* array, void* element);

void remove_element(dynamic_array* array, int position);

void* get_element(dynamic_array* array, int position);

int compareStrings(char *s1, char *s2); // this function compares 2 strings.

int find_position(dynamic_array* array , char* songName);// compares if user input and song in the array matches with using compareStrings method. if does it return position of the matching element. 

void menu(); //prints menu

int main()
{
    dynamic_array songs;
    init_array(&songs);
    int userInput;
    while(1){
        menu();
        scanf("%d", &userInput);
        if (userInput == 1) {
            song* addSong = (song*)malloc(sizeof(song));
            addSong->name = (char*)malloc(64 * sizeof(char)); //max 64 chars
            printf("\nEnter the duration of the song: ");
            scanf("%f", &addSong->duration);
            fgetc(stdin);
            printf("\nEnter the name of the song: ");
            fgets(addSong->name , 64 , stdin);
            //fgets(addSong->name , 64 , stdin);

            
            put_element(&songs, addSong);
        }
        else if (userInput == 2) {
            //We have been told to assume user provides valid input
            char* songName = (char*)malloc(64 * sizeof(char)); // max 64 chars
            printf("\nEnter the name of the song: ");
            fgetc(stdin);
            fgets(songName, 64 , stdin);
            //scanf("%s", songName);
            int position = find_position(&songs , songName);
            remove_element(&songs , position);
        }
        else if (userInput == 3) {
            for (int i = 0; i < songs.size; i++) {
                song* listSongs = (song*)get_element(&songs, i);
                printf("\n\t%d. SONG NAME : %s \tSONG DURATION : %f" , i+1 , listSongs->name , listSongs->duration);
            }
            printf("\n--------------------------------------");
        }
        else if(userInput == 4){
            break;
        }
        else{
            printf("Invalid Input");
            break;
        }

    }
    return 0;
}
void init_array(dynamic_array* array) {
    array->capacity = 2; //initial capacity of the dynamic array must be 2
    array->size = 0; // initial size
    array->elements = (void**)malloc(2 * sizeof(void*)); // allocate 2 void* in the heap
    array->elements[0] = NULL; // assign NULL 
    array->elements[1] = NULL;
}
void put_element(dynamic_array* array, void* element) {
    if (array->size == array->capacity) {   
        array->capacity = array->capacity *2;
        void** newArray = (void**)malloc(array->capacity * sizeof(void*)); // new allocated elements array
        for (int i = 0; i < array->size; i++) {
            newArray[i] = array->elements[i];
        }
        for (int i = array->size; i < array->capacity; i++) { //NULL value for elements array elements that havent pointed to any valid songs
            newArray[i] = NULL;
        }
        free(array->elements);
        array->elements = newArray;
    }
    array->elements[array->size] = element;
    array->size++;
}
void remove_element(dynamic_array* array, int position) {
    
    
    if (array->size == array->capacity / 2) { //check if array size reached capacity / 2
        array->capacity = array->capacity /2; 
        void** newArray = (void**)malloc(array->capacity * sizeof(void*)); //newly allocated elements array
        for (int i = 0; i < array->size; i++) { 
            newArray[i] = array->elements[i];
        }
        free(array->elements); //deallocate the old elements
        array->elements = newArray;
    }
    for (int i = position; i < array->size - 1; i++) {
        array->elements[i] = array->elements[i + 1]; // shift element at given position to the end of the array
    }
    array->elements[array->size - 1] = NULL; // assing null to the last element
    array->size--;
    
}
void* get_element(dynamic_array* array, int position) {
    return array->elements[position];
}
int compareStrings(char *s1, char *s2){
    int i;
    while(s1[i] != '\0' && s2[i] != '\0'){
        if(s1[i] != s2[i]){
            return 1;
        }
        i++;
    }
    return 0;
}
int find_position(dynamic_array* array , char* songName){
    for (int i = 0; i < array->size; i++) {
    song* deleteSong = (song*)get_element(array, i);
    if (compareStrings(deleteSong->name , songName) ==0 ) {
        free(deleteSong->name);
        free(deleteSong);
        return i;
        }
    }
}
void menu(){
    printf("\n\n       MENU");
    printf("\n1. Add a song");
    printf("\n2. Delete a song");
    printf("\n3. List all songs ");
    printf("\n4. Exit ");
    printf("\nEnter your choice: ");
}