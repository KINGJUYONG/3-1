// BTreeMain.c
/* ��� ����
i : (Ű,��)�� ������ ���ڵ� ����
d : Ű�� ������ ���ڵ� ����
r : Ű�� ������ ���ڵ� �˻�
s : ����Ž��
? : �����������
a : ��� ������ ����(1����������)
*/
#include "BTree.h"
#define PAGE_SIZE 64

int main() {

	FILE *fp, *fp_backup, * fp_tmp;
	BTreeRecord record;
	char command;
	BOOL file_not_Exist;
	fp = fopen("data.txt", "r");   //Ʈ������ ȭ�� �����ϴ��� üũ
	if (fp == NULL) {
		file_not_Exist = TRUE;     //������ ��
		fp = fopen("data.txt", "w"); //ȭ�� ���� ����
	}
	else
		file_not_Exist =FALSE;
	fclose(fp);
	 	initBTree("data.txt", PAGE_SIZE, file_not_Exist); //���� ��������� �ʱ�ȭ. ����������� ��Ʈ������ ����

	while (1) {
		fflush(stdin); // ���۸� ����־� scanf�� �ǳʶ��� �ʰ� ��
		fflush(stdin);
		printf("\n\n\n");
		for (int k = 0; k < 2; k++) {
			for (int i = 0; i < 12; i++) {
				printf("==========");
			}
			printf("\n");
		}
		printf("h : ��� ������ ���� / a : ��� ������ ���� i : ���ڵ� input(�߰�) / r : ���ڵ� read(�˻�) / d : ���ڵ� delete(����)\ns : ���� �˻� / b : �����ؽ�Ʈȭ��(backup.txt)�� ����ϱ� / n : ������ȭ��(data.txt) �ʱ�ȭ / o : ������� ��������\nx : ����\n");
		for (int k = 0; k < 2; k++) {
			for (int i = 0; i < 12; i++) {
				printf("==========");
			}
			printf("\n");
		}
		printf("\n���ϴ� �޴��� �����ϼ��� : ");
		fscanf(stdin, " %c", &command);
		if (command == 'x' || command == 'X') break;
		switch (command) {
			case'I':
			case 'i':    //(Ű,��)�� ������ ���ڵ� ����
				printf("������ Ű�� ����� �Է��ϼ��� : ");
				fscanf(stdin, "%i %s", &record.key, &record.value);
				if (insertRecord(&record)) {
					printf("insert (%d, %s) : success\n", record.key, record.value);
				}
				else {
					printf("Insert (%d, %s) : fail\n", record.key, record.value);
				}
				break;
			case 'D' :
			case 'd' :     //Ű�� ������ ���ڵ� ����
				printf("������ Ű�� �Է��ϼ��� : ");
				fscanf(stdin, "%i", &record.key);
				if (deleteRecord(record.key)) {
					printf("Delete (%d) : success\n", record.key, record.value);
				} else {
					printf("Delete (%d) : fail\n", record.key);
				}
				break;
			case 'R' :
			case 'r':    //Ű�� ������ ���ڵ� �˻�
				printf("Ž���� Ű�� �Է��ϼ��� : ");
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
			case 'a':    //��������� �˻�
				retrieveAllPages();
				break;
			case 'H' :
			case 'h':    //������� ����
				Get_Header();
				break;
			case 'S' :
			case 's':    //�����˻�
				char findvalue[100]; // ����ڷκ��� ã�� �ε����� �Է¹޾� ���� Ž���� �����մϴ�.
				printf("�����˻����� ã�� �ε����� ����� �Է��ϼ��� : ");
				scanf("%s", &findvalue);
				linearSearch(findvalue); // �� �Լ��� �����صξ����ϴ�.
				break;
			case 'O':
			case 'o':    //���ȭ�� ��������
				fp = fopen("data.txt", "r"); // data�� �б� �������� ����
				fp_backup = fopen("backup.txt", "r"); // ����� �б� �������� ���ϴ�.
				if (fp_backup == NULL) { // ��� ������ ��������� 
					printf("��� ������ �����ϴ�.\n");
					break; // �����մϴ�.
				}
				else { // �׷��� ���� ���
					fclose(fp); // data�� �ݰ�, �б� �� ����� �ٽ� ���ϴ�.
					fp = fopen("data.txt", "w+");
					while (!feof(fp_backup)) // ������ ���� ��Ÿ���� ���� ���
					{
						char a;
						a = fgetc(fp_backup); // getc �޼���� �� ����Ʈ�� ������
						fputc(a, fp); // data�� �ҷ����Դϴ�.
					}
					printf("��� ������ ���������� �����Խ��ϴ�");
				}
				fclose(fp);
				fclose(fp_backup);
				break;
		
			case 'B':
			case 'b':    //�����ý�Ʈȭ��(backup.txt)�� ����ϱ�
				fp = fopen("data.txt", "r"); // data�� �б� �������� ����
				fp_backup = fopen("backup.txt", "r");// ����� �б� �������� ���ϴ�.
				if (fp_backup == NULL) { // ��� ������ ���������
					printf("������ ������ϴ�. ���� �����մϴ�.\n"); // ���� ���� ���� �����մϴ�.
					fp_backup = fopen("backup.txt", "w");
				}
				else { // �ƴ� ���
					printf("��� ������ �̹� �ֽ��ϴ�. ��� ������ backuptmp.txt�� �����մϴ�.\n");
					fp_tmp = fopen("backuptmp.txt", "w"); // �ι��� ��� ������ �����մϴ�.

					while (!feof(fp_backup)) // ��������� ���� ��Ÿ���� ������
					{
						int a;
						a = fgetc(fp_backup); // ��� ���Ͽ��� �� ����Ʈ�� �����ͼ�
						fputc(a, fp_tmp); // ��� ������ �Ű��ݴϴ�.(��� ������ ���ư��� ���� �����ϱ� ����)

					}
				}
				fclose(fp_backup); // ��� ������ �ݰ� �б�� ������� �ٽ� �����մϴ�.(�ִ°�� tmp�� �Ű��־ �ٽû����ص� ��� ����)
				fp_backup = fopen("backup.txt", "w+");
				while (!feof(fp)) // ���� ������ ������ ���� ������
				{
					char a;
					a = fgetc(fp); // �ѱ��ھ� ��� ���Ϸ� �Ű��ݴϴ�.
					fputc(a, fp_backup);

				}

				printf("����� �Ϸ�Ǿ����ϴ�");
				fclose(fp);
				fclose(fp_backup);
				fclose(fp_tmp);


				break;

				break;
			case 'N':
			case 'n':    //������ȭ�� �ʱ�ȭ
				fp = fopen("data.txt", "w+"); // ������ �� ���·� ���� ���ݴϴ�.
				fclose(fp);
				printf("�ʱ�ȭ �Ϸ�");
				break;
			default:
				printf("�߸��� �޴��Դϴ�. �ٽ� �Է����ּ���");
				
		}
	}
	closeBTree();
	return 0;
}