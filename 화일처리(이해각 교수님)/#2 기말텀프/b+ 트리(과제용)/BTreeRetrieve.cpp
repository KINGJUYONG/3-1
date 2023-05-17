#include "BTree.h"
extern BufferManager *bufferManager;
extern BTreeHeader *bTreeHeader;
BOOL retrieveRecord(Key key, BTreeRecord *record) {
	/*인덱스 셋으로 부터 레코드 검색*/
	BTreePagePtr page=(BTreePagePtr)malloc(bufferManager->pageSize);
	int i=0;
	BOOL found=FALSE;
	if(findRecord(key, page)) {
		i=peek()->index;
		copyRecord(RECORDPTR(page)+i, record);
		found=TRUE;
	}
	free(page);
	return found;
}
BOOL findRecord(Key key, BTreePagePtr page) {
	/*Key를 가진 Record를 찾아가는 경로를 스택에 push하고
			도달한 Leaf를 page에 저장한다*/
	int i=0, targetPage=bTreeHeader->rootPage;
	bTreeHeader->stackPtr=0;
	readBTreePage(targetPage, page);
	while(ISLEAF(page) == FALSE) {
		for (i = 0; (i < KEYCNT(page)) && (KEY(page, i) < key); i++) {
			;
		}
		push(PAGENO(page), i);
		targetPage=CHILD(page, i);
		readBTreePage(targetPage, page);
	}
	for (i = 0; (i < KEYCNT(page)) && (RECORD(page, i).key < key); i++) {
		;
		}
	

	push(PAGENO(page), i);

	if((i < KEYCNT(page)) && (key == RECORD(page, i).key)) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

void Sequential_Backup(void) {

}
void Sequential_Search(void) {

}
void Get_Header(void) {
	/*헤더정보 가져오기*/
	printf("\n루트노드 페이지번호   : %d\n", bTreeHeader->rootPage);
	printf("리프노드 첫페이지번호 : %d\n", bTreeHeader->firstSequencePage);
	printf("B+ 트리의 차수        : %d\n", bTreeHeader->order); //(int)((pageSize - (정수4바이트) * 4) / (정수4바이트) * 2)) + 1;
	printf("내부노드 최소키 개수  : %d\n", bTreeHeader->minKey); //order / 2 - 1 + order % 2;
	printf("리프의 레코드 최대수  : %d\n", bTreeHeader->maxRecord); //pageSize - (정수4바이트) * 3) / (정수4바이트);
	printf("리프노드 최소키 개수  : %d\n", bTreeHeader->minRecord); // bTreeHeader->maxRecord / 2

}

void retrieveAllPages() {
	BTreePagePtr page = (BTreePagePtr)malloc(bufferManager->pageSize);
	int i = 1;
	while (readBTreePage(i, page)) {
		if (ISLEAF(page) == FALSE) {
			printf("페이지번호   : %d (내부노드)\n", PAGENO(page));
			printf("다음페이지   : %d\n", NEXT(page));
			printf("키의개수     : %d\n", KEYCNT(page));
			printf("키리스트     : ");
			for (int j = 0; (j < KEYCNT(page)); j++) {
				printf("%d, (%d), ", CHILD(page, j), KEY(page, j));
			}
			printf("%d\n", CHILD(page, KEYCNT(page)));
			printf("--------------------------------------\n");

		}
		else {
			printf("페이지번호 : %d (리프노드)\n", PAGENO(page));
			printf("레코드개수 : %d\n", KEYCNT(page));
			for (int j = 0; (j < KEYCNT(page)); j++) {
				printf("%d %s\n", RECORD(page, j).key, RECORD(page, j).value);
			}
			printf("다음페이지 : %d\n", NEXT(page));
			printf("--------------------------------------\n");
		}
		i++;
	}
}

void linearSearch(char value[100]) {
	int itn = 0;
	int i = 1;
	char findmyname[100];
	BTreePagePtr page = (BTreePagePtr)malloc(bufferManager->pageSize); // BTreePage포인터에 메모리를 할당해줍니다.
	while (readBTreePage(i, page)) { // BTree의 페이지를 읽어와서
		if (ISLEAF(page) == FALSE) {} // 리프노드인 경우 넘어가고
		else { // 아닌 경우
			for (int j = 0; (j < KEYCNT(page)); j++) {
				if (strcmp(RECORD(page, j).value, value) == 0) { // 사용자가 입력한 밸류와 해당 인덱스의 밸류를 비교한 뒤 일치한다면
					printf("\n%d페이지의 %d번째 인덱스에 있습니다.\n", PAGENO(page), j+1); // 해당 인덱스의 위치를 알려주고
					printf("key : %d, value : %s\n", RECORD(page, j).key, RECORD(page, j).value); // 정보를 출력합니다.
					itn++;
				}
			}
		}
		i++;
	}
	if (itn == 0) {
		printf("찾으시는 인덱스가 없습니다.");
	}
}