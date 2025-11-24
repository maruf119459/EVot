#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#define MAX_LENGTH 50
#define KEY_LENGTH 33


#ifndef AUTH_H //1
#define AUTH_H

int authenticateAdmin();
void forgotPassword();
void adminPanel();

#endif



#ifndef REGISTRATION_H //2
#define REGISTRATION_H

void registrationAdmin();

#endif



#ifndef VOTE_HANDLING_H //3
#define VOTE_HANDLING_H

void saveVote(char userID[15], char voteInput);
void deleteIllegalVote(char userID[15]);
int isVoted(char userID[15]);
int isBanned(char userID[15]);
void banID();
int isValid(char userID[15]);

#endif

#ifndef CANDIDATE_MANAGEMENT_H //4
#define CANDIDATE_MANAGEMENT_H

void createCandidateFiles();

#endif



#ifndef UTILITY_FUNCTIONS_H //5
#define UTILITY_FUNCTIONS_H

void cls();
void ccolor(int clr);
int extractYear(char userID[15]);
int extractRollNo(char userID[15]);
int checkBranchCode(char userID[15]);
int findYear(char chyear[5]);
void maskInput(char *input);
void convertToIDString(int value, char strValue[6]);
void convertToYearString(int value, char strValue[6]);
void createIDString(int value, char idString[15]);

#endif


#ifndef USER_INTERFACE_H //6
#define USER_INTERFACE_H

void pwellcome();
void loadingbar();

#endif



#ifndef FILE_OPERATIONS_H //7
#define FILE_OPERATIONS_H

void saveElectionInfoInFile();
void loadElectionInfoFromFile();

#endif


#ifndef ELECTION_MANAGEMENT_H //8
#define ELECTION_MANAGEMENT_H

void initiateNewElection();
void deleteIllegalVote(char userID[15]);
int getWinner();

#endif




#ifndef STUDENT_PALEN_H // 9
#define STUDENT_PALEN_H

void studentPanel();

#endif





struct currentValidID{
    int year;
    char branch[6];
    int totalVoters;
};
typedef struct candidate{
    int cid;
    char cname[20];
    int votes;
}CANDIDATE;


struct currentValidID currentValidID;
CANDIDATE candidateArray[20];
int numberOfCandidates;
char studentVotes[200];

void cls()
{

    system("cls");

}
void ccolor(int clr)
{
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, clr);
}

void pwellcome()
{
    ccolor(26);

    char welcome[50]="WELCOME";
    char welcome2[50]=" TO";
    char welcome3[70]=" ELECTRONIC VOTING";
    char welcome4[50]=" SYSTEM";
    printf("\n\n\n\n\n\t\t\t");
    for(int wlc=0; wlc<strlen(welcome); wlc++)
    {
        ccolor(120+(wlc*9));

        printf(" %c",welcome[wlc]);
        Sleep(200);
    }
    ccolor(27);
    printf(" ");
    for(int wlc2=0; wlc2<strlen(welcome2) ; wlc2++)
    {
        ccolor(160+(wlc2*9));

        printf(" %c",welcome2[wlc2]);
        Sleep(200);
    }
    ccolor(26);
    printf(" ");
    for(int wlc3=0; wlc3<strlen(welcome3) ; wlc3++)
    {
        if(welcome3[wlc3]=='E'){
            ccolor(120+(wlc3*4));
            printf(" %c",welcome3[wlc3]);
        }
        else{
            ccolor(160+(wlc3*9));

        printf(" %c",welcome3[wlc3]);
        }

        Sleep(200);
    }
    ccolor(26);
    printf(" ");
    for(int wlc3=0; wlc3<strlen(welcome4) ; wlc3++)
    {
        if(welcome4[wlc3]!='A' && welcome4[wlc3]!='E')
        {
            ccolor(121+(wlc3*4));

            printf(" %c",welcome4[wlc3]);
        }
        else
        {
            ccolor(11);

            printf(" %c",welcome4[wlc3]);
        }
        Sleep(200);
    }
    ccolor(26);

}
void loadingbar(void)
{
    ccolor(26);

    for (int i=15; i<=100; i+=5)
    {

        cls();
        ccolor(26);

        printf("\n\n\n\n\n\n\n\t\t\t\t");
        printf("%d %% Loading...\n\n\t\t",i);

        printf("");

        for (int j=0; j<i; j+=2)
        {

            ccolor(160+j);
            printf(" ");
            ccolor(26);

        }
        Sleep(100);
        if(i==90 || i==50 || i==96 || i==83)
        {
            Sleep(100);
        }

    }

}

int extractYear(char userID[15])
{
    int year=0;
    char tmp;
    for(int i=0;i<4;i++){
        tmp=userID[i];
		year=(year*10)+(tmp-48);
    }
    return year;
}

int findYear(char chyear[5])
{
    int year=0;
    char tmp;
    for(int i=0;i<4;i++){
        tmp=chyear[i];
		year=(year*10)+(tmp-48);
    }
    return year;
}

int extractRollNo(char userID[15])
{
    int rollno=0;
    char tmp;
    for(int i=9;i<14;i++){
        tmp=userID[i];
		rollno=(rollno*10)+(tmp-48);
    }
    return rollno;
}


int checkBranchCode(char userID[15])
{
    char branchCode[6];
    for(int i=4;i<9;i++){
        branchCode[i-4]=userID[i];
    }
    branchCode[5]='\0';
    if(strcmp(branchCode,currentValidID.branch)==0)
        return 1;
    else
        return 0;
}

void maskInput(char *input) {
    char ch;
    int i = 0;
    while (1) {
        ch = _getch();
        if (ch == '\r') {
            input[i] = '\0';
            break;
        } else if (ch == 8 && i > 0) {
            printf("\b \b");
            i--;
        } else {
            input[i] = ch;
            printf("*");
            i++;
        }
    }
}

void generateKey(char key[]) {
    srand(time(NULL));

    for (int i = 0; i < 32; i++) {
        key[i] = 'A' + (rand() % 26);
    }
    key[32] = '\0';
}

void saveKeyToFile(char key[]) {
    FILE *file = fopen("key.txt", "w");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "%s\n", key);
    fclose(file);
}

void resizeKey(char *key, char *newKey, int textLen) {
    int keyLen = strlen(key);

    if (keyLen == textLen) {
        strcpy(newKey, key);
    }
    else if (keyLen > textLen) {
        strncpy(newKey, key, textLen);
        newKey[textLen] = '\0';
    }
    else {
        int i, j = 0;
        for (i = 0; i < textLen; i++) {
            newKey[i] = key[j];
            j++;
            if (j == keyLen) j = 0;
        }
        newKey[textLen] = '\0';
    }
}

void encryptOTP(char *plaintext, char *key, char *ciphertext) {
    int len = strlen(plaintext);

    for (int i = 0; i < len; i++) {
        int p = toupper(plaintext[i]) - 'A' + 1;
        int k = toupper(key[i]) - 'A' + 1;

        int c = p + k;
        if (c > 26) c -= 26;

        ciphertext[i] = (c - 1) + 'A';
    }
    ciphertext[len] = '\0';
}





void registrationAdmin() {
    char username[MAX_LENGTH];
    char id[MAX_LENGTH];
    char password[MAX_LENGTH];
    char key[KEY_LENGTH];

    char resizedKey[MAX_LENGTH];
    char encUsername[MAX_LENGTH];
    char encPassword[MAX_LENGTH];

    FILE *checkFile = fopen("admin.txt", "r");
    if (checkFile != NULL) {
        fseek(checkFile, 0, SEEK_END);
        if (ftell(checkFile) != 0) {
            fclose(checkFile);
            printf("\n\t\t\tYou are already registered.\n");
            printf("\t\t\tIf you forget your ID or username, contact IT.\n");
            printf("\t\t\tIf you forgot the password, choose 'forgot password'.\n");
            return;
        }
        fclose(checkFile);
    }

    printf("\n\t\t\tMust note username, ID, password.\n");

    printf("\n\t\t\tEnter username: ");
    maskInput(username);

    printf("\n\t\t\tEnter ID: ");
    maskInput(id);

    printf("\n\t\t\tEnter password: ");
    maskInput(password);

    // Generate OTP key
    generateKey(key);
    saveKeyToFile(key);

    /* ---------- Encrypt Username ---------- */
    resizeKey(key, resizedKey, strlen(username));
    encryptOTP(username, resizedKey, encUsername);

    /* ---------- Encrypt Password ---------- */
    resizeKey(key, resizedKey, strlen(password));
    encryptOTP(password, resizedKey, encPassword);

    FILE *file = fopen("admin.txt", "a");
    fprintf(file, "%s %s %s\n", encUsername, id, encPassword);
    fclose(file);

    printf("\n\t\t\tRegistration successful! (Encrypted)\n");
}


int authenticateAdmin() {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    char encUsername[MAX_LENGTH];
    char encPassword[MAX_LENGTH];
    char fileUsername[MAX_LENGTH];
    char fileId[MAX_LENGTH];
    char filePassword[MAX_LENGTH];
    char key[KEY_LENGTH];
    char resizedKey[MAX_LENGTH];

    FILE *keyFile = fopen("key.txt", "r");
    if (keyFile == NULL) {
        printf("\n\t\t\tKey not found! Registration might be required.\n");
        return 0;
    }
    fscanf(keyFile, "%s", key);
    fclose(keyFile);

    FILE *file = fopen("admin.txt", "r");
    if (file == NULL) {
        printf("\n\t\t\tYou have not registered yet, Please register first.\n");
        return 0;
    }

    // Get admin input
    printf("\n\t\t\tEnter username: ");
    maskInput(username);
    printf("\n\t\t\tEnter Password: ");
    maskInput(password);

    // Encrypt input using OTP key
    resizeKey(key, resizedKey, strlen(username));
    encryptOTP(username, resizedKey, encUsername);

    resizeKey(key, resizedKey, strlen(password));
    encryptOTP(password, resizedKey, encPassword);

    int found = 0;

    // Compare encrypted input with encrypted data in admin.txt
    while (fscanf(file, "%s %s %s", fileUsername, fileId, filePassword) != EOF) {
        if (strcmp(encUsername, fileUsername) == 0 && strcmp(encPassword, filePassword) == 0) {
            fclose(file);
            found = 1;
            return 1;
        }
    }

    if (found == 0) {
        printf("\n\t\t\tWrong password or username\n");
    }

    fclose(file);
    return 0;
}


void forgotPassword() {
    char username[MAX_LENGTH];
    char id[MAX_LENGTH];
    char fileUsername[MAX_LENGTH];
    char fileId[MAX_LENGTH];
    char filePassword[MAX_LENGTH];
    char newPassword[MAX_LENGTH];
    char key[KEY_LENGTH];
    char resizedKey[MAX_LENGTH];
    char encUsername[MAX_LENGTH];
    char encNewPassword[MAX_LENGTH];

    // Load OTP key
    FILE *keyFile = fopen("key.txt", "r");
    if (keyFile == NULL) {
        printf("\n\t\t\tKey not found! Cannot reset password.\n");
        return;
    }
    fscanf(keyFile, "%s", key);
    fclose(keyFile);

    // Get user input
    printf("\n\t\t\tEnter username: ");
    maskInput(username);
    printf("\t\t\tEnter ID: ");
    maskInput(id);

    // Encrypt the entered username for comparison
    resizeKey(key, resizedKey, strlen(username));
    encryptOTP(username, resizedKey, encUsername);

    FILE *file = fopen("admin.txt", "r");
    if (file == NULL) {
        printf("\n\t\t\tYou have not registered yet, Please register first.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("\n\t\t\tCannot create temporary file.\n");
        fclose(file);
        return;
    }

    int updated = 0;

    while (fscanf(file, "%s %s %s", fileUsername, fileId, filePassword) != EOF) {
        if (strcmp(encUsername, fileUsername) == 0 && strcmp(id, fileId) == 0) {
            // User matched, get new password
            printf("\n\t\t\tEnter new password: ");
            maskInput(newPassword);

            // Encrypt new password with OTP key
            resizeKey(key, resizedKey, strlen(newPassword));
            encryptOTP(newPassword, resizedKey, encNewPassword);

            fprintf(tempFile, "%s %s %s\n", fileUsername, fileId, encNewPassword);
            printf("\n\t\t\tPassword updated successfully!\n");
            updated = 1;
        } else {
            // Copy existing data unchanged
            fprintf(tempFile, "%s %s %s\n", fileUsername, fileId, filePassword);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (updated) {
        remove("admin.txt");
        rename("temp.txt", "admin.txt");
    } else {
        printf("\n\t\t\tInvalid username or ID. Password not updated.\n");
        remove("temp.txt");
    }
}


void convertToIDString(int value, char strValue[6])
{
    sprintf(strValue, "%05d", value);
}

void convertToYearString(int value, char strValue[6])
{
    sprintf(strValue, "%04d", value);
}

void createIDString(int value, char idString[15])
{
    char yearStr[6];
    convertToYearString(currentValidID.year, yearStr);

    char valueStr[6];
    convertToIDString(value, valueStr);

    strcpy(idString, yearStr);
    strcat(idString, currentValidID.branch);
    strcat(idString, valueStr);
}



void banID()
{
    ccolor(26);
    printf("\n\t\t\tCreating Banned.txt...\n");
    FILE *fp=fopen("Banned.txt", "w");
    if(fp==NULL)
    {
        printf("\t\t\tError: Banned.txt not created.\n");
        fclose(fp);
        return;
    }
    printf("\t\t\tJust Enter last roll no to ban\n\t\t\tPress 0 to exit... ");
    int input;
    while(1)
    {
        printf("\n\t\t\tEnter Number: ");
        scanf("%d",&input);
        if(input < 0 || input > currentValidID.totalVoters)
        {
            printf("\n\t\t\tInvalid Id\n");
            return;
        }

        char outputID[15];
        createIDString(input, outputID);

        int location = extractRollNo(outputID);
        int candidateIndex = studentVotes[location - 1] - '1';

        if (candidateIndex >= 0 && candidateArray[candidateIndex].votes > 0)
        {
            FILE *fk,*fcp;
            char filename[20];
            char line[20];

            sprintf(filename,"candidate%d.txt",candidateArray[studentVotes[location-1]-49].cid);
            candidateArray[studentVotes[location-1]-49].votes--;
            studentVotes[location-1]='0';
            if ((fk = fopen(filename,"r")) == NULL)
            {
                printf("\n\t\t\tFile cannot be opened...Operation Failed\n");
                return;
            }
            printf("\n\t\t\tDeleting in process...\n ");
            if ((fcp = fopen("tmp.txt","w")) == NULL)
            {
                printf("\n\t\t\tFile cannot be opened...Operation Failed\n");
                return;
            }

            while (!feof(fk))
            {
                fscanf(fk,"%s",line);
                fprintf(fcp,"%s\n",line);
            }
            fclose(fk);
            fclose(fcp);
            if ((fk = fopen(filename,"w")) == NULL)
            {
                printf("\n\t\t\tFile cannot be opened...Operation Failed\n");
                return;
            }
            int numFromFile;
            char cnameFromFile[20];
            fcp = fopen("tmp.txt","r");
            fscanf(fcp,"%d",&numFromFile);
            fprintf(fk,"%d",numFromFile-1);
            fscanf(fcp,"%s",cnameFromFile);
            fprintf(fk,"\n%s",cnameFromFile);
            while(!feof(fcp))
            {
                fscanf(fcp,"%d",&numFromFile);
                if(numFromFile!=location)
                    fprintf(fk,"\n%d",numFromFile);
            }
            fclose(fk);
            fclose(fcp);
            remove("tmp.txt");
            Sleep(300);
            Sleep(300);
            Sleep(300);
            Sleep(300);
            Sleep(300);
            printf("\n\t\t\tVote deleted successfully\n\t\t\tPress 0 to exit.....\n");
        }

        if(input==0)
            break;
        studentVotes[input-1]='$';
        fprintf(fp,"%d\n",input);
    }
    fclose(fp);
    printf("\t\t\tBan ID Created Successfully\n");
}


void createCandidateFiles(){
    ccolor(26);
    printf("\n\t\t\tCreating candidate files...\n");
    FILE *fp;
	char filename[20];
    for(int i = 1;i <= numberOfCandidates; i++){
        sprintf(filename,"candidate%d.txt",i);
		fp=fopen(filename,"w");
        fprintf(
            fp,"0\n%s",
            candidateArray[i-1].cname
        );
		fclose(fp);
    }
    printf("\t\t\tCreated Files successfully\n");
}

void deleteIllegalVote(char userID[15])
{
    ccolor(26);
    FILE *fp, *fcp;
    char filename[20];
    char line[20];
    int found = 0;
    int year = extractYear(userID);
    if (year != currentValidID.year)
    {
        found = 1;
    }
    if (checkBranchCode(userID) == 0)
    {
        found = 1;
    }

    int location = extractRollNo(userID);
    if (location > currentValidID.totalVoters || location < 0)
    {
        found = 1;
    }
    if (found == 1)
    {
        printf("\n\t\t\tInvalid Id\n");
        return;
    }

    int candidateIndex = studentVotes[location - 1] - '1';

    if (candidateIndex < 0 || candidateArray[candidateIndex].votes == 0)
    {
        printf("\n\t\t\tVote not found. This student has not voted yet.\n");
        return;
    }

    sprintf(filename, "candidate%d.txt", candidateArray[studentVotes[location - 1] - 49].cid);
    candidateArray[studentVotes[location - 1] - 49].votes--;
    studentVotes[location - 1] = '0';
    if ((fp = fopen(filename, "r")) == NULL)
    {
        printf("\n\t\t\tVoting has not started yet. Operation Failed\n");
        return;
    }
    printf("\n\t\t\tDeleting in process...\n ");
    if ((fcp = fopen("tmp.txt", "w")) == NULL)
    {
        printf("\n\t\t\tFile cannot be opened...Operation Failed\n");
        return;
    }

    while (!feof(fp))
    {
        fscanf(fp, "%s", line);
        fprintf(fcp, "%s\n", line);
    }
    fclose(fp);
    fclose(fcp);
    if ((fp = fopen(filename, "w")) == NULL)
    {
        printf("\n\t\t\tFile cannot be opened...Operation Failed\n");
        return;
    }
    int numFromFile;
    char cnameFromFile[20];
    fcp = fopen("tmp.txt", "r");
    fscanf(fcp, "%d", &numFromFile);
    fprintf(fp, "%d", numFromFile - 1);
    fscanf(fcp, "%s", cnameFromFile);
    fprintf(fp, "\n%s", cnameFromFile);
    while (!feof(fcp))
    {
        fscanf(fcp, "%d", &numFromFile);
        if (numFromFile != location)
            fprintf(fp, "\n%d", numFromFile);
    }
    fclose(fp);
    fclose(fcp);
    remove("tmp.txt");
    Sleep(300);
    Sleep(300);
    Sleep(300);
    Sleep(300);
    Sleep(300);
    printf("\n\t\t\tVote deleted successfully\n\t\t\tPress any key to continue...\n");
    getch();
}


int getWinner(){
    int maxV = -1;
    int winnerCid;
    for(int i = 0;i < numberOfCandidates; i++){
        if(candidateArray[i].votes > maxV) {
            winnerCid = candidateArray[i].cid;
            maxV = candidateArray[i].votes;
        }
        else if(candidateArray[i].votes == maxV) {
            return -1;
        }
    }
    return winnerCid;
}

void initiateNewElection()
{
    ccolor(26);
    char yearr[5];
    printf("\n\t\t\tNew Election Initiation:\n");

    while (1) {
        printf("\n\t\t\tElections for which Year (4-digit '2022'): ");
        scanf("%4s", yearr);

        if (strlen(yearr) != 4) {
            printf("\t\t\tThis year is invalid. Please enter a valid 4-digit year.\n");
        } else {
            currentValidID.year = findYear(yearr);
            break;
        }
    }
    while (1) {
        printf("\t\t\tEnter batch code (5 characters '00038'): ");
        scanf("%5s", currentValidID.branch);

        if (strlen(currentValidID.branch) != 5) {
            printf("\t\t\tThis branch code is invalid. Please enter a valid 5-character branch code.\n");
        } else {
            break;
        }
    }
    printf("\t\t\tEnter max roll no (total voters or student):");
    scanf("%d",&currentValidID.totalVoters);
    printf("\t\t\tEnter the no. of candidates:");
    scanf("%d",&numberOfCandidates);

   for (int i = 0; i < currentValidID.totalVoters; i++)
    {
        studentVotes[i] = '0';
    }

    for (int i = 0;i < numberOfCandidates; i++)
    {
        candidateArray[i].cid=i+1;
        printf("\t\t\tEnter name of candidate %d: ",i+1);
        scanf(" %s",candidateArray[i].cname);
        candidateArray[i].votes=0;
    }
    return;
}

void saveElectionInfoInFile(){
    ccolor(26);
    printf("\t\t\tSaving Election Info in File...\n");
    FILE *fp = fopen("ElectionInfo.txt", "w");
    if(fp==NULL)
    {
        printf("\n\t\t\tError in file creation\n");
        fclose(fp);
        return;
    }
    fprintf(
        fp,"%d\n%s\n%d\n%d",
        currentValidID.year,
        currentValidID.branch,
        currentValidID.totalVoters,
        numberOfCandidates
    );
    fclose(fp);
    printf("\t\t\tSaved Successfully : )");
}

void loadElectionInfoFromFile()
{
    ccolor(26);
    FILE *f1,*f2,*f3;
    f1=fopen("ElectionInfo.txt","r");
    if(f1==NULL)
        printf("\t\t\tNot Exist");
    fscanf(f1,"%d",&currentValidID.year);
    fseek(f1,2,SEEK_CUR);
    fscanf(f1,"%s",currentValidID.branch);
    fseek(f1,2,SEEK_CUR);
    fscanf(f1,"%d",&currentValidID.totalVoters);
    fseek(f1,2,SEEK_CUR);
    fscanf(f1,"%d",&numberOfCandidates);
    fclose(f1);


    for (int i = 0; i < currentValidID.totalVoters; i++)
    {
        studentVotes[i] = '0';
    }
    for(int i=1;i<=numberOfCandidates;i++)
    {
        int location;
        char filename[20];
        sprintf(filename,"candidate%d.txt",i);
        f2=fopen(filename,"r+");
        candidateArray[i-1].cid=i;
        fscanf(f2,"%d",&candidateArray[i-1].votes);
        fscanf(f2,"%s",candidateArray[i-1].cname);
        while(!feof(f2)){
            fscanf(f2,"%d",&location);
            studentVotes[location-1] = i+48;
        }
        fclose(f2);
    }


    int location;
    f3=fopen("banned.txt","r+");
    while(!feof(f3)){
        fscanf(f3,"%d",&location);
        studentVotes[location-1] = '$';
    }
    fclose(f3);
    printf("\n\t\t\tWait few seconds.");
    Sleep(300);
    Sleep(300);
    Sleep(300);
    Sleep(300);
    Sleep(300);
    printf("\n\t\t\tSystem reload previous vote.\n");

}

void adminPanel()
{
    ccolor(26);
    while(1){
       char option;
        printf("\n\t\t\t1.Registation\n\t\t\t2.Log in\n\t\t\t3.Forgot Password\n\t\t\t4.Go Home Page\n\t\t\tOption:");
        scanf(" %c",&option);
        switch(option)
        {
            case '1':
                cls();
                registrationAdmin();

                break;
            case '2':
                cls();
                while(1){
                    if(authenticateAdmin() != 1){
                        break;
                    }
                    printf("\n\n\t\t\tLOGGED IN SUCCESSFULLY (Press Enter)");
                    getch();
                    printf("\n");

                    while(1)
                    {
                        ccolor(26);
                        char inputID[15];
                        char input;char banInp;int WinnerCid, totalVotedNow=0;
                        printf("\n\t\t\t1.New Election\n\t\t\t2.Continue Previous Election\n\t\t\t3.Delete Illegal Vote\n\t\t\t4.Ban User IDs\n\t\t\t5.Result\n\t\t\t6.Logout\n\t\t\tOption:");
                        scanf(" %c",&input);
                        switch(input)
                        {
                            case '1':
                                cls();
                                initiateNewElection();saveElectionInfoInFile();createCandidateFiles();break;
                            case '2':
                                cls();
                                loadElectionInfoFromFile();break;
                            case '3':
                                cls();
                                printf("\n\t\t\tEnter user ID to delete its vote: ");scanf("%s",inputID);deleteIllegalVote(inputID);break;
                            case '4':
                                cls();
                                printf("\t\t\tDo you want to ban particular ID's?\n\t\t\tPress 1 if yes or any other key to continue...");
                                scanf(" %c",&banInp);
                                if(banInp=='1')
                                    {
                                        banID();
                                    }

                                break;
                            case '5':
                                cls();
                                WinnerCid = getWinner();
                                if(candidateArray[WinnerCid-1].votes == 0)
                                {
                                 printf("\n\t\t\tFull Result or Vote taking not start yet.\n\t\t\tYou again take Vote.\n");
                                 break;
                                }
                                else if(WinnerCid != -1)
                                {
                                    printf("\n\t\t\tWinner is %s with %d votes\n",candidateArray[WinnerCid-1].cname,candidateArray[WinnerCid-1].votes);
                                }
                                else
                                {
                                    printf("\n\t\t\tIts A TIE\n");
                                }

                                for(int i=0;i<numberOfCandidates;i++)
                                {
                                    totalVotedNow+=candidateArray[i].votes;
                                    printf("\t\t\t%d. %s -> %d votes\n",candidateArray[i].cid,candidateArray[i].cname,candidateArray[i].votes);
                                }
                                printf("\n\t\t\tVoting Percentage: %d %%\n\n",(totalVotedNow*100)/currentValidID.totalVoters);

                                break;
                            case '6':
                                cls();
                                return;
                                cls();
                            default:
                                printf("\t\t\tInvalid Option");
                                getch();

                        }
                    }
                }
                break;
            case '3':
                cls();
                forgotPassword();
                break;
            case '4':
                return;
                cls();
            default:
                printf("\t\t\tInvalid Option");
                getch();
        }


    }
};


int isValid(char userID[15])
{
    if(strlen(userID)!=14)
        return 0;

    int inputedYear=extractYear(userID);
    int inputedRollNo = extractRollNo(userID);

    if(inputedYear!=currentValidID.year || checkBranchCode(userID)!=1 || inputedRollNo>currentValidID.totalVoters)
        return 0;

    return 1;
}

int isVoted(char userID[15])
{
    int location=extractRollNo(userID);
    if(studentVotes[location-1]=='0')
        return 0;
    else
        return 1;
}

int isBanned(char userID[15]){
    int location=extractRollNo(userID);
    if(studentVotes[location-1]=='$')
        return 1;
    else
        return 0;
}

void saveVote(char userID[15],char voteInput)
{
    char filename[20];
    sprintf(filename,"candidate%d.txt",voteInput-48);
    FILE *fp = fopen(filename,"r+");
    int location=extractRollNo(userID);
    studentVotes[location-1]=voteInput;
    candidateArray[voteInput-49].votes++;
    fseek(fp, 0, SEEK_SET);
    fprintf(fp,"%d\n",candidateArray[voteInput-49].votes);
    fseek(fp, 0, SEEK_END);
    fprintf(fp,"\n%d",location);
    fclose(fp);
}


void studentPanel()
{
    ccolor(26);
    char userID[15];
    char voteInput;
    while(1)
	{
		printf("\n\n\t\t\t  To exit press 0");
		printf("\n\n\t\t\t  Student id must be 15 digit.\n\t\t\t  Like 20210003200001 (1st 4 digit year, 2nd 5 digit batch code, 3rd 5 digit roll number)");
        printf("\n\t\t\t  Enter user ID:");
        scanf("%s",userID);
        if(strcmp(userID, "0")==0)
				return;
        if(isValid(userID)!=1)
        {
            printf("\n\t\t\t  Invalid User ID(Press Enter)");
            getch();
            continue;
        }
        if(isBanned(userID)!=0)
        {
            printf("\n\t\t\tThis User ID is currently banned...\n\t\t\tContact Admin for the reason...(Press Enter to continue)");
            getch();
            continue;
        }
        if(isVoted(userID)!=0)
        {
            printf("\n\t\t\t  Your PRN entered is already voted\n\t\t\t  Contact Admin for furthur query");
            getch();
            continue;
        }
        printf("\n\n\t\t\t  Candidates for election:");
		for (int i = 0; i < numberOfCandidates; i++)
        {
            printf("\n\t\t\t  %d. %s",i+1,candidateArray[i].cname);
        }
        printf("\n\n\t\t\t  Your Vote(Enter Number):");
        voteInput=getch();
        printf("*");
        if(voteInput-48 < 1 || voteInput-48 > numberOfCandidates)
        {
            printf("\n\t\t\tInvalid Vote\n\t\t\tTry Again...");
            getch();
            continue;
        }
        saveVote(userID,voteInput);
        printf("\n\n\t\t\tThanks for your precious vote(Press Enter)");
        getch();
    }
}

int main(){
    cls();
    ccolor(26);
    system(">>>>>>>>>>> ELECTRONIC VOTING SYSTEM <<<<<<<<<<<<");


    loadingbar();
    cls();
    pwellcome();
    Sleep(300);
    cls();
    while(1){
        printf("\n\t\t\t   1.Student panel \n\t\t\t   2.Admin panel \n\t\t\t   3.Exit \n\t\t\t   Option:");
		char input;
        scanf(" %c",&input);

        switch(input){
            case '1':
                cls();
                studentPanel();
                cls();
                break;
            case '2':
                cls();
                adminPanel();
                cls();
                break;
            case '3':
                return 0;
            default:
                printf("\n\t\t\tInvalid option");
                getch();
        }
    }
    return 0;
}
