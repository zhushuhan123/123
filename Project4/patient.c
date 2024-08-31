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

// Function declarations
void addPatient();
void editPatient();
void deletePatient();
void queryPatient();
void printPatient(Patient p);
void saveToFile();
void loadFromFile();

int main() {
    int choice;

    loadFromFile();// ���ļ��м��ػ�������

    while (1) {

        printf("\nҽԺ���߹���ϵͳ\n");
        printf("1. ��ӻ���\n");
        printf("2. �༭����\n");
        printf("3. ɾ������\n");
        printf("4. ��ѯ����\n");
        printf("5. �˳�\n");
        printf("�������ѡ��: ");
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
            saveToFile();  //���˳�ǰ���������ݱ��浽�ļ���
            exit(0);
        default:
            printf("��Ч��ѡ��������һ�Ρ�\n");
        }
    }

    return 0;
}
//��ӻ���
void addPatient() {
    if (patientCount >= MAX_PATIENTS) {
        printf("��������������\n");
        return;
    }

    Patient p;
    printf("���뻼��������");
    fgets(p.name, MAX_NAME_LENGTH, stdin);
    p.name[strcspn(p.name, "\n")] = '\0';

    printf("���뻼�����䣺 ");
    scanf("%d", &p.age);
    getchar();

    printf("���뻼���Ա� ");
    scanf("%c", &p.gender);
    getchar();

    printf("���뻼����ϵ��ʽ�� ");
    fgets(p.contact, MAX_CONTACT_LENGTH, stdin);
    p.contact[strcspn(p.contact, "\n")] = '\0';

    printf("���뻼�ߵĲ�����ţ� ");
    fgets(p.zshMedRN, 20, stdin);
    p.zshMedRN[strcspn(p.zshMedRN, "\n")] = '\0';

    printf("���뻼�߲�ʷ�� ");
    fgets(p.zshMedH, MAX_MEDICAL_HISTORY_LENGTH, stdin);
    p.zshMedH[strcspn(p.zshMedH, "\n")] = '\0';

    patients[patientCount++] = p;
    printf("������Ϣ��ӳɹ���\n");
    //��ͣ����
    system("pause");
    //��տ���̨
    system("cls");

}
//�༭����
void editPatient() {
    char medicalRecordNumber[20];
    printf("����Ҫ�༭�Ļ��ߵĲ�����ţ� ");
    fgets(medicalRecordNumber, 20, stdin);
    medicalRecordNumber[strcspn(medicalRecordNumber, "\n")] = '\0';

    for (int i = 0; i < patientCount; i++) {
        if (strcmp(patients[i].zshMedRN, medicalRecordNumber) == 0) {
            printf("�༭�������Ϊ%s�Ļ��ߵ���ϸ��Ϣ\n", medicalRecordNumber);
            printf("���뻼�ߵ�������: ");
            fgets(patients[i].name, MAX_NAME_LENGTH, stdin);
            patients[i].name[strcspn(patients[i].name, "\n")] = '\0';

            printf("���뻼�ߵ�������: ");
            scanf("%d", &patients[i].age);

            printf("���뻼���µ���ϵ��ʽ: ");
            fgets(patients[i].contact, MAX_CONTACT_LENGTH, stdin);
            patients[i].contact[strcspn(patients[i].contact, "\n")] = '\0';
            getchar();

            printf("���뻼���µĲ�ʷ: ");
            fgets(patients[i].zshMedH, MAX_MEDICAL_HISTORY_LENGTH, stdin);
            patients[i].zshMedH[strcspn(patients[i].zshMedH, "\n")] = '\0';
            getchar();

            printf("������Ϣ�޸ĳɹ���\n");  
            //��ͣ����
            system("pause");
            //��տ���̨
            system("cls");
            return;
          

        }
    }
    printf("û���ҵ���Ӧ������ŵĻ��ߡ�\n", medicalRecordNumber);
    //��ͣ����
    system("pause");
    //��տ���̨
    system("cls");

}
//ɾ������
void deletePatient() {
    char medicalRecordNumber[20];
    printf("����Ҫɾ���Ļ��ߵĲ�����ţ� ");
    fgets(medicalRecordNumber, 20, stdin);
    medicalRecordNumber[strcspn(medicalRecordNumber, "\n")] = '\0';

    for (int i = 0; i < patientCount; i++) {
        if (strcmp(patients[i].zshMedRN, medicalRecordNumber) == 0) {
            for (int j = i; j < patientCount - 1; j++) {
                patients[j] = patients[j + 1];
            }
            patientCount--;
            printf("������Ϣɾ���ɹ���\n");
             //��ͣ����
            system("pause");
            //��տ���̨
            system("cls");
            return;           
          
        }
    }
    printf("û���ҵ��û��ߵ���Ϣ\n", medicalRecordNumber);
    //��ͣ����
    system("pause");
    //��տ���̨
    system("cls");

}
//��ѯ����
void queryPatient() {
    char keyword[MAX_NAME_LENGTH];
    printf("����Ҫ����������������ţ� ");
    fgets(keyword, MAX_NAME_LENGTH, stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    int found = 0;
    for (int i = 0; i < patientCount; i++) {
        if (strstr(patients[i].name, keyword) != NULL || strcmp(patients[i].zshMedRN, keyword) == 0) {
            printPatient(patients[i]);
            found = 1;
            //��ͣ����
            system("pause");
            //��տ���̨
            system("cls");
        }
    }
    if (!found) {
        printf("û���ҵ����и����ؼ��ֵĻ��ߡ�\n");
        //��ͣ����
        system("pause");
        //��տ���̨
        system("cls");

    }
}
//
void printPatient(Patient p) {
    printf("\n������Ϣ:\n");
    printf("����: %s\n", p.name);
    printf("����: %d\n", p.age);
    printf("�Ա�: %c\n", p.gender);
    printf("��ϵ��ʽ: %s\n", p.contact);
    printf("�������: %s\n", p.zshMedRN);
    printf("��ʷ: %s\n", p.zshMedH);
}
//���滼������
void saveToFile() {
    FILE* file = fopen(FILENAME, "wb");
    if (file == NULL) {
        perror("�޷����ļ�����д��");
        return;
    }
    fwrite(&patientCount, sizeof(int), 1, file);
    fwrite(patients, sizeof(Patient), patientCount, file);
    fclose(file);
    printf("�������ݱ��浽�ļ���\n");
}
//�����ļ��еĻ�������
void loadFromFile() {
    FILE* file = fopen(FILENAME, "rb");
    if (file == NULL) {
        perror("�޷��򿪻�����Ϣ�ļ����ж�ȡ");
        return;
    }
    fread(&patientCount, sizeof(int), 1, file);
    fread(patients, sizeof(Patient), patientCount, file);
    fclose(file);
    printf("���ļ��м��ػ������ݡ�\n");
}
