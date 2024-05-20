/* 
Written by Anders-Erik.
2024-05-20
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define INVISICOMMAND_SIZE 48
#define INVISIBYTE_SIZE 24



/* var-1, var-2, var-3, var-4 */
unsigned char vars[4] = {0, 0, 0, 0};

/* parse three real bytes and return 1 or 0 */
int getInvisibit(const unsigned char *subgroup);

/* parse one Invisibyte and return the integer value represented by that invisibyte */
int processInvisibyte(const unsigned char *group, size_t size);

/* the two arguments are parsed bytes */
int executeCommand(int action, int value);





int main(int argc, char *argv[]){
    // printf("%d %d %d", asdf, asdf, asdf);

    // printf("Hello from Compiled InvisiLang! \n");
   
    // Get CLI flags
    // int cliIndex = 1;
    int printCommandsFlag = 0;
    int filenameCliIndex = 1;
    switch (argc)
    {
        case 1:
            printf("No script file specified! \n");
            return 1;
            break;
        
        case 2:
            break;
        
        case 3:
            
            if(0 == strcmp(argv[1], "-p")){
                printf("Print Commands mode: \n");
            } else {
                printf("Unknown cli argument. Exiting. \n");
                return EXIT_FAILURE;
            }
            printCommandsFlag = 1;
            filenameCliIndex = 2;
            break;
        
        default:
            printf("Only one command-flag allowed! \n");
            break;
    }



    // Grab Script File
    const char *scriptName = argv[filenameCliIndex];
    FILE *scriptFile = fopen(scriptName, "rb");
    if (!scriptFile) {
        perror("Error opening script file. ");
        return EXIT_FAILURE;
    }


    // Check First bytes file
    unsigned char firstThreeBytes[3];
    fread(firstThreeBytes, 1, 3, scriptFile);

    // Check last byte
    unsigned char lastByte;
    fseek(scriptFile, -1, SEEK_END);
    fread(&lastByte, 1, 1, scriptFile);
    
    // set for parsing of commands
    rewind(scriptFile);
    fseek(scriptFile, 3, SEEK_SET);





    unsigned char buffer[INVISICOMMAND_SIZE];
    unsigned char actionBuffer[INVISIBYTE_SIZE];
    unsigned char valueBuffer[INVISIBYTE_SIZE];
    size_t bytesRead;





    // Program Execution
    int action;
    int value;
    while ((bytesRead = fread(buffer, 1, INVISICOMMAND_SIZE, scriptFile)) == INVISICOMMAND_SIZE) {
        
        // Process each group of 24 bytes
        // Also gcc is complaning about this block of code!!
        strcpy(actionBuffer, &buffer[0]);
        action = processInvisibyte(actionBuffer, INVISIBYTE_SIZE);
        strcpy(valueBuffer, &buffer[INVISIBYTE_SIZE]);
        value = processInvisibyte(valueBuffer, INVISIBYTE_SIZE);

        // Execute program or print parsed commands?
        if(printCommandsFlag){
            printf("%02x, %02x \n", action, value);
        } else {
            executeCommand(action, value);
        }


    }



    fclose(scriptFile);

    // printf("Bye from Compiled InvisiLang! \n");

    return EXIT_SUCCESS;
}





int getInvisibit(const unsigned char *subgroup) {
    unsigned int value = (subgroup[0] << 16) | (subgroup[1] << 8) | subgroup[2];

    if(value == 0xE2808B) {
        return 0;
    } else if (value == 0xE2808C) {
        return 1;
    } else {
        return 2;
    }

}



int processInvisibyte(const unsigned char *group, size_t size) {


    if (size != INVISIBYTE_SIZE) {
        fprintf(stderr, "Invalid invisibyte size\n");
        return 1000;
    }
    
    int invisibyte = 0;
    int result = 0;
    for (size_t i = 0; i < size; i += 3) {
        result = getInvisibit(&group[i]);
        if(result == 2){
            printf("ERROR PARSING INVISIBIT!");
        }
        invisibyte += result;
        invisibyte = invisibyte << 1;
        // printf("%d", result);
    }
    invisibyte = invisibyte >> 1;
    // printf("\n");
    // printf("Invisibyte: %c", invisibyte);
    // printf("\n");

    return invisibyte;
}





int executeCommand(int action, int value){
    
    double numerator;
    double denominator;
    char *format;
    if(value == 1){
        format = "%d";
    } else if (value == 2){
        format = "%02x";
    } else {
        format = "%c";
    }


    switch (action)
    {

    // Print
    case 0x00:
        printf(format, vars[0]);
        break;
    case 0x01:
        printf("%c", vars[1]);
        break;
    case 0x02:
        printf("%c", vars[2]);
        break;
    case 0x03:
        printf("%c", vars[3]);
        break;
    case 0x05:
        printf(format, value);
        break;


    // Variables
    case 0x10:
        vars[0] = value;
        break;
    case 0x11:
        vars[1] = value;
        break;
    case 0x12:
        vars[2] = value;
        break;
    case 0x13:
        vars[3] = value;
        break;


    // Move
    case 0x20:
        vars[value] = vars[0];
        break;
    case 0x21:
        vars[value] = vars[1];
        break;
    case 0x22:
        vars[value] = vars[2];
        break;
    case 0x23:
        vars[value] = vars[3];
        break;

    // Math
    case 0x30:
        vars[0] = vars[0] + value;
        break;
    case 0x31:
        vars[0] = vars[0] + vars[1];
        break;
    case 0x32:
        vars[0] = vars[0] - value;
        break;
    case 0x33:
        vars[0] = vars[0] - vars[1];
        break;
    case 0x34:
        vars[0] = vars[0] * value;
        break;
    case 0x35:
        vars[0] = vars[0] * vars[1];
        break;
    case 0x36:
        numerator = (double) vars[0];
        denominator = (double) value; 
        vars[0] = (int) (numerator / denominator);
        break;
    case 0x37:
        numerator = (double) vars[0];
        denominator = (double) vars[1];
        vars[0] = (int) (numerator / denominator);
        break;
    case 0x38:
        numerator = (double) vars[0];
        denominator = (double) value; 
        vars[0] = (int) 100 * (numerator / denominator);
        break;
    case 0x39:
        numerator = (double) vars[0];
        denominator = (double) vars[1]; 
        vars[0] = (int) 100 * (numerator / denominator);
        break;


    default:
        break;
    }

    return 0;
}
