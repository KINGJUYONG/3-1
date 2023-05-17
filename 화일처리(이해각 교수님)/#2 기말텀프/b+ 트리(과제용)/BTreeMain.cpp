// BTreeMain.c
/* 명령 유형
i : (키,값)을 가지는 레코드 삽입
d : 키를 가지는 레코드 삭제
r : 키를 가지는 레코드 검색
s : 순차탐색
? : 헤더정보보기
a : 모든 페이지 보기(1페이지부터)
*/
#include "BTree.h"
#define PAGE_SIZE 64

int main() {

	FILE *fp, *fp_backup, * fp_tmp;
	BTreeRecord record;
	char command;
	BOOL file_not_Exist;
	fp = fopen("data.txt", "r");   //트리저장 화일 존재하는지 체크
	if (fp == NULL) {
		file_not_Exist = TRUE;     //없으면 참
		fp = fopen("data.txt", "w"); //화일 새로 생성
	}
	else
		file_not_Exist =FALSE;
	fclose(fp);
	 	initBTree("data.txt", PAGE_SIZE, file_not_Exist); //새로 만들었으면 초기화. 헤더페이지와 루트페이지 생성

	while (1) {
		fflush(stdin); // 버퍼를 비워주어 scanf를 건너뛰지 않게 함
		fflush(stdin);
		printf("\n\n\n");
		for (int k = 0; k < 2; k++) {
			for (int i = 0; i < 12; i++) {
				printf("==========");
			}
			printf("\n");
		}
		printf("h : 헤더 페이지 보기 / a : 모든 페이지 보기 i : 레코드 input(추가) / r : 레코드 read(검색) / d : 레코드 delete(삭제)\ns : 순차 검색 / b : 순차텍스트화일(backup.txt)로 백업하기 / n : 데이터화일(data.txt) 초기화 / o : 백업파일 가져오기\nx : 종료\n");
		for (int k = 0; k < 2; k++) {
			for (int i = 0; i < 12; i++) {
				printf("==========");
			}
			printf("\n");
		}
		printf("\n원하는 메뉴를 선택하세요 : ");
		fscanf(stdin, " %c", &command);
		if (command == 'x' || command == 'X') break;
		switch (command) {
			case'I':
			case 'i':    //(키,값)을 가지는 레코드 삽입
				printf("삽입할 키와 밸류를 입력하세요 : ");
				fscanf(stdin, "%i %s", &record.key, &record.value);
				if (insertRecord(&record)) {
					printf("insert (%d, %s) : success\n", record.key, record.value);
				}
				else {
					printf("Insert (%d, %s) : fail\n", record.key, record.value);
				}
				break;
			case 'D' :
			case 'd' :     //키를 가지는 레코드 삭제
				printf("삭제할 키를 입력하세요 : ");
				fscanf(stdin, "%i", &record.key);
				if (deleteRecord(record.key)) {
					printf("Delete (%d) : success\n", record.key, record.value);
				} else {
					printf("Delete (%d) : fail\n", record.key);
				}
				break;
			case 'R' :
			case 'r':    //키를 가지는 레코드 검색
				printf("탐색할 키를 입력하세요 : ");
				fscanf(stdin, "%i", &record.key);
				if (retrieveRecord(record.key, & record)) {
					printf(
						"Retrive (%d, %s) : success\n",
						record.key,
						record.value);
				} else {
					printf("Retrive (%d) : fail\n", record.key);
				}
				break;
			case 'A' :
			case 'a':    //모든페이지 검색
				retrieveAllPages();
				break;
			case 'H' :
			case 'h':    //헤더정보 보기
				Get_Header();
				break;
			case 'S' :
			case 's':    //순차검색
				char findvalue[100]; // 사용자로부터 찾을 인덱스를 입력받아 순차 탐색을 수행합니다.
				printf("순차검색으로 찾을 인덱스의 밸류를 입력하세요 : ");
				scanf("%s", &findvalue);
				linearSearch(findvalue); // 본 함수에 구현해두었습니다.
				break;
			case 'O':
			case 'o':    //백업화일 가져오기
				fp = fopen("data.txt", "r"); // data를 읽기 전용으로 열고
				fp_backup = fopen("backup.txt", "r"); // 백업도 읽기 전용으로 엽니다.
				if (fp_backup == NULL) { // 백업 파일이 비어있으면 
					printf("백업 파일이 없습니다.\n");
					break; // 종료합니다.
				}
				else { // 그렇지 않을 경우
					fclose(fp); // data를 닫고, 읽기 및 쓰기로 다시 엽니다.
					fp = fopen("data.txt", "w+");
					while (!feof(fp_backup)) // 파일의 끝이 나타나지 않을 경우
					{
						char a;
						a = fgetc(fp_backup); // getc 메서드로 한 바이트를 가져와
						fputc(a, fp); // data로 불러들입니다.
					}
					printf("백업 파일을 성공적으로 가져왔습니다");
				}
				fclose(fp);
				fclose(fp_backup);
				break;
		
			case 'B':
			case 'b':    //순차택스트화일(backup.txt)로 백업하기
				fp = fopen("data.txt", "r"); // data를 읽기 전용으로 열고
				fp_backup = fopen("backup.txt", "r");// 백업도 읽기 전용으로 엽니다.
				if (fp_backup == NULL) { // 백업 파일이 비어있으면
					printf("파일이 비었습니다. 새로 생성합니다.\n"); // 쓰기 모드로 새로 생성합니다.
					fp_backup = fopen("backup.txt", "w");
				}
				else { // 아닐 경우
					printf("백업 파일이 이미 있습니다. 백업 파일을 backuptmp.txt에 저장합니다.\n");
					fp_tmp = fopen("backuptmp.txt", "w"); // 두번쨰 백업 파일을 생성합니다.

					while (!feof(fp_backup)) // 백업파일의 끝이 나타나기 전까지
					{
						int a;
						a = fgetc(fp_backup); // 백업 파일에서 한 바이트를 가져와서
						fputc(a, fp_tmp); // 백업 템프로 옮겨줍니다.(백업 파일이 날아가는 것을 방지하기 위함)

					}
				}
				fclose(fp_backup); // 백업 파일을 닫고 읽기와 쓰기모드로 다시 생성합니다.(있는경우 tmp로 옮겨주어서 다시생성해도 상관 없음)
				fp_backup = fopen("backup.txt", "w+");
				while (!feof(fp)) // 원본 데이터 파일이 끝날 때까지
				{
					char a;
					a = fgetc(fp); // 한글자씩 백업 파일로 옮겨줍니다.
					fputc(a, fp_backup);

				}

				printf("백업이 완료되었습니다");
				fclose(fp);
				fclose(fp_backup);
				fclose(fp_tmp);


				break;

				break;
			case 'N':
			case 'n':    //데이터화일 초기화
				fp = fopen("data.txt", "w+"); // 파일을 빈 상태로 새로 써줍니다.
				fclose(fp);
				printf("초기화 완료");
				break;
			default:
				printf("잘못된 메뉴입니다. 다시 입력해주세요");
				
		}
	}
	closeBTree();
	return 0;
}