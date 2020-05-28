#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//1.���� 2.���� 3.���� 4.�˻�
//ȸ�� �̸�(255) / ����(200) / �̸���(����ó��)
int list = 0;

typedef struct userData {
	char name[255];
	int age;
	char email[255];
}userData;

int check_email(char *email) {
	char ch;
	int len = strlen(email);
	int atsign_try = 0;
	int dot_try = 0;
	for (int i = 0; i < len; i++) {
		ch = email[i];
		if (ch == '@')break;
		atsign_try++;
	}	
	for (int i = 0; i < len; i++) {
		ch = email[i];
		if (ch == '.')break;
		dot_try++;
	}
	//@�� .���� �ڿ� ���� ��, @�� .���� �ϳ��� ���� �� || @�տ� ���ڰ� 3�� �̸��� �� || @�� .�� ���̿� ���ڰ� 3�� �̸��� ��|| . ���� ���ڰ� 3�� �̸��� �� 
	if (atsign_try >= dot_try || atsign_try < 3 || dot_try - (atsign_try + 1) < 3 || len < dot_try + 4)
		return 1;
	else
		return 2;
}
void save_user(userData *user){
	char answer ;
	int check = 0;
	do{
		printf("�̸�: ");
		scanf_s(" %[^\n]", user[list].name,255);
		printf("����: ");
		scanf_s("%d", &user[list].age);
		printf("email: ");
		scanf_s("%s", user[list].email,255);
		check=check_email(user[list].email);
		if (check == 1){
			printf("�̸��� �ּ������� �����ʽ��ϴ�.\n");
			break;
		}
		list++;
		printf("��� �Է� �ұ��?(Y/N) : ");
		scanf_s(" %c", &answer,1);
		if (answer == 'N') {
			printf("�Է��� �Ϸ�Ǿ����ϴ�.\n");
		}
	}while (answer != 'N');
}

void revise_user(userData *user) {
	char input[255];
	char email[255];
	int revise_try = 0;
	printf("������ ����� �̸��� �Է����ּ��� : ");
	scanf_s(" %[^\n]", input,255);
	for (int i = 0; i < list; i++) {
		if (strcmp(input, user[i].name) == 0) {
			printf("%s���� ������ �����մϴ�.\n", input);
			printf("�̸� : ");
			scanf_s(" %[^\n]", user[i].name, 255);
			printf("����: ");
			scanf_s("%d", &user[i].age);
			printf("email: ");
			scanf_s("%s,", email, 255); revise_try++;
			int check = check_email(user[list].email);
			if (check == 1) {
				printf("�̸��� �ּ������� �����ʽ��ϴ�.\n");
				break;
			}
			strcpy(email, user[i].email);
		}
	}
	if (revise_try == 0) {
		printf("����� %s�� �����ϴ�.\n", input);
	}	
}

void delete_user(userData *user){
	char input[255];
	int delete_try = 0;
	printf("������ ȸ���� �̸��� �Է��ϼ��� : ");
	scanf_s(" %[^\n]", input,255);
	for (int i = 0; i < list; i++) {
		if (strcmp(input, user[i].name) == 0) {
			for (int k = i; k < list; k++) {
				strcpy_s(user[k].name, user[k + 1].name);
				user[k].age = user[k + 1].age;
				strcpy_s(user[k].email, user[k + 1].email);
			}
			delete_try++;
		}
	}
	if (delete_try == 0) {
		printf("�������� �ʴ� ȸ���Դϴ�.\n");
	}
	else {
		printf("%s ȸ������ ������ ���� �Ϸ�Ǿ����ϴ�.\n", input);
		list--;
	}
}

void search_user(userData *user, FILE * fp) {
	fp = fopen("management_user.txt", "w");
	for (int i = 0; i < list; i++) {
		fprintf(fp,"%s / %d / %s\n", user[i].name, user[i].age, user[i].email);
		printf("%s / %d / %s\n", user[i].name, user[i].age, user[i].email);
	}
	fclose(fp);
}

void print_menu() {
	printf("\n1.�ű�ȸ�� ����\n2.ȸ������ ����\n3.ȸ�� ����\n4.��� ȸ�� ����Ʈ\n5.����\n");
	printf("�Է��ϼ���>");
}
void menu(userData *user,FILE *fp) {
	int input = 0; 
	do {
		print_menu();
		scanf_s("%d", &input);
		switch (input) {
		case 1: save_user(user); break;
		case 2: revise_user(user); break;
		case 3: delete_user(user); break;
		case 4: search_user(user,fp); break;
		case 5: printf("ȸ������ ���α׷��� �����մϴ�.\n"); break;
		default: printf("�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���.\n");
		}
	} while (input != 5);
	
}

void create_origin_user(FILE * fp, userData *user) {

	strcpy_s(user[list].name, "PARK GIL DONG");
	user[list].age = 22;
	strcpy_s(user[list].email, "parkpark@hotmail.com");
	list++;
	strcpy_s(user[list].name, "LEE GIL DONG ");
	user[list].age = 23;
	strcpy_s(user[list].email, "gildonglee@naver.com");
	list++;
	
}

int main(int argc ,char *argv[]) {
	FILE *fp = NULL;

	userData user[100] = { 0};
	printf("�ȳ��ϼ���. ȸ������ ���α׷��Դϴ�.\n���Ͻô� �޴��� ��ȣ�� �Է��� �ּ���.\n========\n\n");
	create_origin_user(fp,user);
	menu(user,fp);

	
	system("pause");
	return 0;
}