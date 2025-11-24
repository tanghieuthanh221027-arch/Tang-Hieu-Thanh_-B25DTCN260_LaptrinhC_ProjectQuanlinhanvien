#include <stdio.h>
#include <string.h>
	
#define MAX 100	
typedef struct {
	char empId[20];
	char name [50];
	char position [15];
	double baseSalary;
	int workDay ;
} Employee ;
typedef struct {
	char logId[20];
	char empId[20];
	char date[20];
	char status[10];
} TimeSheet ;
Employee employees [MAX];
int empCount = 0 ;
TimeSheet timeSheet [MAX];
int timeCount = 0 ;
	
int findEmpbyID (char Id[]) {
	for (int i = 0  ; i < empCount ; i++) {
		if (strcmp(Id, employees[i].empId) == 0) {
	        return i;
	        }
	    }
	return -1;
}
	
void genLogID (char logId[]) {
	sprintf(logId , "HC%04d" , timeCount + 1);
}
	
int checked (char empId[] , char date[]) {
	for (int i = 0 ; i < timeCount ; i++) {
	    if (strcmp(timeSheet[i].empId, empId) == 0 && strcmp(timeSheet[i].date, date) == 0) {
	        return 1 ;
	    }
	}
	return 0 ;
}
	
void addEmployee() {
    if (empCount >= MAX) {
        printf("Danh sach nhan vien day!\n");
        return;
    }

    Employee e;

    while (1) {
        getchar();
        printf("Nhap ma nhan vien: ");
        fgets(e.empId, sizeof(e.empId), stdin);
        e.empId[strcspn(e.empId, "\n")] = 0;

        if (strlen(e.empId) == 0)
            printf("Ma nhan vien khong duoc rong. Nhap lai!\n");
        else if (findEmpbyID(e.empId) != -1)
            printf("Ma nhan vien da ton tai. Nhap lai!\n");
        else
            break;
    }

    while (1) {
        printf("Nhap ten nhan vien: ");
        fgets(e.name, sizeof(e.name), stdin);
        e.name[strcspn(e.name, "\n")] = 0;
        if (strlen(e.name) == 0)
            printf("Ten khong duoc rong. Nhap lai!\n");
        else
            break;
    }

    while (1) {
        printf("Nhap chuc vu: ");
        fgets(e.position, sizeof(e.position), stdin);
        e.position[strcspn(e.position, "\n")] = 0;
        if (strlen(e.position) == 0)
            printf("Chuc vu khong duoc rong. Nhap lai!\n");
        else
            break;
    }

    while (1) {
        printf("Nhap luong co ban: ");
        scanf("%lf", &e.baseSalary);
        if (e.baseSalary <= 0)
        	printf("Luong co ban khong hop le !\n");
		else 
			break ;
		
    }

    while (1) {
    	printf("Nhap ngay cong : ");
    	scanf("%d" , &e.workDay);
    	if(e.workDay < 0)
    		printf("So ngay cong khong hop le !\n");
		else
			break;
		
	}
    employees[empCount++] = e;
    printf("Them nhan vien thanh cong!\n");
}

	
void updateEmployee() {
	char id[20] ;
	getchar();
	    
	printf("Nhap id nhan vien can cap nhat : ");
	fgets(id, 20, stdin);
	id[strcspn(id, "\n")] = '\0';
	
	int x = findEmpbyID(id);
	if (x == -1) {
	    printf("Khong tim thay nhan vien co ma %s!\n" , id);
	    return ;
	}
	getchar();
	while(1){
		printf("Nhap chuc vu moi : ");
		fgets(employees[x].position , 15 , stdin);
		employees[x].position[strcspn(employees[x].position , "\n")] = '\0';
		if(strlen(employees[x].position) == 0){
			printf("Chuc vu khong duoc de trong !\n");
		}else {
			break ;
		}
	}
	
	while(1){
		printf("Nhap luong co ban moi : ");
		scanf("%lf" , &employees[x].baseSalary);
		if(employees[x].baseSalary < 0){
			printf("Luong co ban phai duong !\n");
		}else {
			break ; 
		}
	}
	printf("Cap nhat ho so nhan vien thanh cong !\n");
}
	
void deleteEmployee() {
	char id[20];
	getchar();
		
	printf("Nhap id nhan vien muon xoa : ");
	fgets(id, 20, stdin);
	id[strcspn(id, "\n")] = '\0';
	
	int y = findEmpbyID(id);
	if (y == -1) {
	    printf("Khong tim thay nhan vien !\n");
	    return ;
	}
	int confirm ;
	printf("Xac nhan xoa nhan vien ? \n");
	scanf(" %d" , &confirm);
	
	if (confirm == 1) {
	    for (int i = y ; i < empCount - 1 ; i++ ) {
	        employees[i] = employees[i + 1];
	    }
	    empCount--;
	    printf("Da xoa nhan vien !\n");
	}else {
	    printf("Huy xoa nhan vien !\n");
	}
}
	
void printList () {
	if (empCount == 0) { 
	    printf("Danh sach trong !\n");
	    return ;
	}
	for (int i = 0 ; i < empCount ; i++) {
		printf("Thong tin nhan vien %d\n" , i + 1);
	    printf("Ten nhan vien : %s\n", employees[i].name);
	    printf("Chuc vu : %s\n", employees[i].position);
	    printf("Ma nhan vien : %s\n", employees[i].empId);
	    printf("Luong co ban : %.2lf\n", employees[i].baseSalary);
	    printf("Ngay cong : %d\n" , employees[i].workDay);
	}
}
	
void searchByName (){
	char findName[50];
		
	printf("Nhap ten nhan vien can tim : ");
	fgets(findName , 50 , stdin);
	findName[strcspn(findName , "\n")] = '\0';
	
	int flag = 0 ;		
	for (int i = 0 ; i < empCount ; i++){
		if(strstr(employees[i].name , findName) == 0){
			printf("Ma nhan vien : %s\n" , employees[i].empId);
			printf("Ten nhan vien : %s\n" , employees[i].name);
			printf("Luong co ban : %.2lf\n" , employees[i].baseSalary);
			printf("Ngay cong : %d\n" , employees[i].workDay);
			flag = 1; 
		}
	}
	if(!flag){
		printf("Khong tim thay nhan vien !\n");
	}
}
	
	
	
	
void addSampleList(){
	Employee e1 = {"HG001" , "Tran Minh Duc" , "Quan li" , 2000 , 5};
	Employee e2 = {"HG002" , "Phung Duy Dat" , "Nhan vien" , 1000 , 3};
	Employee e3 = {"HG003" , "Nguyen Minh Hieu" , "Pho giam doc" , 5000 , 8};
	employees[empCount++] = e1;
	employees[empCount++] = e2;
	employees[empCount++] = e3;
} 

int main () {
	int choice ;
	addSampleList();
	do {
	    printf("\n+----------Danh sach quan ly nhan vien va cham cong--------+\n");
	    printf("|1. Them moi nhan vien                                     |\n");
	    printf("|2. Cap nhat ho so nhan vien                               |\n");
	    printf("|3. Sa thai / nghi viec                                    |\n");
	    printf("|4. Hien thi danh sach nhan vien                           |\n");
	    printf("|5. Tra cuu thong tin nhan vien                            |\n");
	    printf("|6. Sap xep danh sach nhan vien theo luong co ban          |\n");
	    printf("|7. Cham ngay cong                                         |\n");
	    printf("|8. Xem bang cong                                          |\n");
	    printf("|9. Thoat                                                  |\n");
	    printf("+----------------------------------------------------------+\n");
	
	    printf("Nhap lua chon cua ban : ");
	    scanf("%d" , &choice);
	
	    switch (choice) {
	        case 1: addEmployee(); break;
	        case 2: updateEmployee(); break;
	        case 3: deleteEmployee(); break;
	        case 4: printList(); break;
			case 5: searchByName(); break;
	
	    }
	}while (choice != 9);
	return 0 ;
}
