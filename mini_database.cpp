#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//1.저장 2.수정 3.삭제 4.검색
//회원 이름(255) / 나이(200) / 이메일(예외처리)
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
	//@가 .보다 뒤에 있을 때, @와 .둘중 하나라도 없을 때 || @앞에 글자가 3개 미만일 때 || @와 .의 사이에 글자가 3개 미만일 때|| . 뒤의 글자가 3개 미만일 때 
	if (atsign_try >= dot_try || atsign_try < 3 || dot_try - (atsign_try + 1) < 3 || len < dot_try + 4)
		return 1;
	else
		return 2;
}
void save_user(userData *user){
	char answer ;
	int check = 0;
	do{
		printf("이름: ");
		scanf_s(" %[^\n]", user[list].name,255);
		printf("나이: ");
		scanf_s("%d", &user[list].age);
		printf("email: ");
		scanf_s("%s", user[list].email,255);
		check=check_email(user[list].email);
		if (check == 1){
			printf("이메일 주소형식이 맞지않습니다.\n");
			break;
		}
		list++;
		printf("계속 입력 할까요?(Y/N) : ");
		scanf_s(" %c", &answer,1);
		if (answer == 'N') {
			printf("입력이 완료되었습니다.\n");
		}
	}while (answer != 'N');
}

void revise_user(userData *user) {
	char input[255];
	char email[255];
	int revise_try = 0;
	printf("수정할 사람의 이름을 입력해주세요 : ");
	scanf_s(" %[^\n]", input,255);
	for (int i = 0; i < list; i++) {
		if (strcmp(input, user[i].name) == 0) {
			printf("%s님의 정보를 수정합니다.\n", input);
			printf("이름 : ");
			scanf_s(" %[^\n]", user[i].name, 255);
			printf("나이: ");
			scanf_s("%d", &user[i].age);
			printf("email: ");
			scanf_s("%s,", email, 255); revise_try++;
			int check = check_email(user[list].email);
			if (check == 1) {
				printf("이메일 주소형식이 맞지않습니다.\n");
				break;
			}
			strcpy(email, user[i].email);
		}
	}
	if (revise_try == 0) {
		printf("사용자 %s는 없습니다.\n", input);
	}	
}

void delete_user(userData *user){
	char input[255];
	int delete_try = 0;
	printf("삭제할 회원의 이름을 입력하세요 : ");
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
		printf("존재하지 않는 회원입니다.\n");
	}
	else {
		printf("%s 회원님의 정보가 삭제 완료되었습니다.\n", input);
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
	printf("\n1.신규회원 저장\n2.회원정보 수정\n3.회원 삭제\n4.모든 회원 리스트\n5.종료\n");
	printf("입력하세요>");
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
		case 5: printf("회원관리 프로그램을 종료합니다.\n"); break;
		default: printf("잘못 입력하셨습니다. 다시 입력해주세요.\n");
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
	printf("안녕하세요. 회원관리 프로그램입니다.\n원하시는 메뉴의 번호를 입력해 주세요.\n========\n\n");
	create_origin_user(fp,user);
	menu(user,fp);

	
	system("pause");
	return 0;
}