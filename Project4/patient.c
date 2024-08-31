#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 100
#define MAX_NAME_LENGTH 100
#define MAX_CONTACT_LENGTH 20
#define MAX_MEDICAL_HISTORY_LENGTH 256
#define FILENAME "patients.dat"

typedef struct {
    char name[MAX_NAME_LENGTH];
    int age;
    char gender;
    char contact[MAX_CONTACT_LENGTH];
    char zshMedRN[20];
    char zshMedH[MAX_MEDICAL_HISTORY_LENGTH];
} Patient;

Patient patients[MAX_PATIENTS];
int patientCount = 0;

// 函数声明
void addPatient();
void editPatient();
void deletePatient();
void queryPatient();
void printPatient(Patient p);
void saveToFile();
void loadFromFile();

int main() {
    int choice;

    loadFromFile();// 从文件中加载患者数据

    while (1) {

        printf("\n医院患者管理系统\n");
        printf("1. 添加患者\n");
        printf("2. 编辑患者\n");
        printf("3. 删除患者\n");
        printf("4. 查询患者\n");
        printf("5. 退出\n");
        printf("输入你的选择: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1:
            addPatient();
            break;
        case 2:
            editPatient();
            break;
        case 3:
            deletePatient();
            break;
        case 4:
            queryPatient();
            break;
        case 5:
            saveToFile();  //在退出前将患者数据保存到文件中
            exit(0);
        default:
            printf("无效的选择。请再试一次。\n");
        }
    }

    return 0;
}
//添加患者
void addPatient() {
    if (patientCount >= MAX_PATIENTS) {
        printf("病人名单已满。\n");
        return;
    }

    Patient p;
    printf("输入患者姓名：");
    fgets(p.name, MAX_NAME_LENGTH, stdin);
    p.name[strcspn(p.name, "\n")] = '\0';

    printf("输入患者年龄： ");
    scanf("%d", &p.age);
    getchar();

    printf("输入患者性别： ");
    scanf("%c", &p.gender);
    getchar();

    printf("输入患者联系方式： ");
    fgets(p.contact, MAX_CONTACT_LENGTH, stdin);
    p.contact[strcspn(p.contact, "\n")] = '\0';

    printf("输入患者的病历编号： ");
    fgets(p.zshMedRN, 20, stdin);
    p.zshMedRN[strcspn(p.zshMedRN, "\n")] = '\0';

    printf("输入患者病史： ");
    fgets(p.zshMedH, MAX_MEDICAL_HISTORY_LENGTH, stdin);
    p.zshMedH[strcspn(p.zshMedH, "\n")] = '\0';

    patients[patientCount++] = p;
    printf("患者信息添加成功。\n");
    //暂停程序
    system("pause");
    //清空控制台
    system("cls");

}
//编辑患者
void editPatient() {
    char medicalRecordNumber[20];
    printf("输入要编辑的患者的病历编号： ");
    fgets(medicalRecordNumber, 20, stdin);
    medicalRecordNumber[strcspn(medicalRecordNumber, "\n")] = '\0';

    for (int i = 0; i < patientCount; i++) {
        if (strcmp(patients[i].zshMedRN, medicalRecordNumber) == 0) {
            printf("编辑病例编号为%s的患者的详细信息\n", medicalRecordNumber);
            printf("输入患者的新姓名: ");
            fgets(patients[i].name, MAX_NAME_LENGTH, stdin);
            patients[i].name[strcspn(patients[i].name, "\n")] = '\0';

            printf("输入患者的新年龄: ");
            scanf("%d", &patients[i].age);

            printf("输入患者新的联系方式: ");
            fgets(patients[i].contact, MAX_CONTACT_LENGTH, stdin);
            patients[i].contact[strcspn(patients[i].contact, "\n")] = '\0';
            getchar();

            printf("输入患者新的病史: ");
            fgets(patients[i].zshMedH, MAX_MEDICAL_HISTORY_LENGTH, stdin);
            patients[i].zshMedH[strcspn(patients[i].zshMedH, "\n")] = '\0';
            getchar();

            printf("患者信息修改成功。\n");  
            //暂停程序
            system("pause");
            //清空控制台
            system("cls");
            return;
          

        }
    }
    printf("没有找到对应病历编号的患者。\n", medicalRecordNumber);
    //暂停程序
    system("pause");
    //清空控制台
    system("cls");

}
//删除患者
void deletePatient() {
    char medicalRecordNumber[20];
    printf("输入要删除的患者的病历编号： ");
    fgets(medicalRecordNumber, 20, stdin);
    medicalRecordNumber[strcspn(medicalRecordNumber, "\n")] = '\0';

    for (int i = 0; i < patientCount; i++) {
        if (strcmp(patients[i].zshMedRN, medicalRecordNumber) == 0) {
            for (int j = i; j < patientCount - 1; j++) {
                patients[j] = patients[j + 1];
            }
            patientCount--;
            printf("患者信息删除成功。\n");
             //暂停程序
            system("pause");
            //清空控制台
            system("cls");
            return;           
          
        }
    }
    printf("没有找到该患者的信息\n", medicalRecordNumber);
    //暂停程序
    system("pause");
    //清空控制台
    system("cls");

}
//查询患者
void queryPatient() {
    char keyword[MAX_NAME_LENGTH];
    printf("输入要搜索的姓名或病历编号： ");
    fgets(keyword, MAX_NAME_LENGTH, stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    int found = 0;
    for (int i = 0; i < patientCount; i++) {
        if (strstr(patients[i].name, keyword) != NULL || strcmp(patients[i].zshMedRN, keyword) == 0) {
            printPatient(patients[i]);
            found = 1;
            //暂停程序
            system("pause");
            //清空控制台
            system("cls");
        }
    }
    if (!found) {
        printf("没有找到具有给定关键字的患者。\n");
        //暂停程序
        system("pause");
        //清空控制台
        system("cls");

    }
}
//查询后显示信息
void printPatient(Patient p) {
    printf("\n患者信息:\n");
    printf("姓名: %s\n", p.name);
    printf("年龄: %d\n", p.age);
    printf("性别: %c\n", p.gender);
    printf("联系方式: %s\n", p.contact);
    printf("病历编号: %s\n", p.zshMedRN);
    printf("病史: %s\n", p.zshMedH);
}
//保存患者数据
void saveToFile() {
    FILE* file = fopen(FILENAME, "wb");
    if (file == NULL) {
        perror("无法打开文件进行写入");
        return;
    }
    fwrite(&patientCount, sizeof(int), 1, file);
    fwrite(patients, sizeof(Patient), patientCount, file);
    fclose(file);
    printf("患者数据保存到文件。\n");
}
//加载文件中的患者数据
void loadFromFile() {
    FILE* file = fopen(FILENAME, "rb");
    if (file == NULL) {
        perror("无法打开患者信息文件进行读取");
        return;
    }
    fread(&patientCount, sizeof(int), 1, file);
    fread(patients, sizeof(Patient), patientCount, file);
    fclose(file);
    printf("从文件中加载患者数据。\n");
}
