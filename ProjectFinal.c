#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
char empId[20];
char name[50];
char position[15];
double baseSalary;
int workDay;
} Employee;

typedef struct {
	char logId[20];
	char empId[20];
	char date[20];
	char status[10];
}TimeSheet;

Employee employees[MAX];
int empCount = 0;
TimeSheet timeSheet[MAX];
int timeCount = 0;
//Ham tien ich tim kiem nhan vien bang id 
int findEmpByID(char id[]) {
for (int i = 0; i < empCount; i++) {
if (strcmp(employees[i].empId, id) == 0)
return i;
}
return -1;
}

void genLogID (char logId){
	sprintf("logId" , "HG%04f" , timeCount + 1);
}

int checked (char empId[] , char date[]){
	for(int i = 0 ; i < timeCount ; i++){
		if(strcmp(timeSheet[i].empId , empId) == 0 && strcmp(timeSheet[i].date , date) == 0){
			return 1 ; 
		}
	}
	return 0 ; 
}

// F01 - Them nhan vien moi 
void addEmployee() {
if (empCount >= MAX) {
printf("Danh sach nhan vien day!\n");
return;
}
Employee e;

while (getchar() != '\n');//clear buffer , tranh bi skip 

do {
    printf("Nhap ma nhan vien: ");
    fgets(e.empId, sizeof(e.empId), stdin);
    e.empId[strcspn(e.empId, "\n")] = '\0';
    if (strlen(e.empId) == 0)
        printf("Ma nhan vien khong duoc rong. Nhap lai!\n");
    else if (findEmpByID(e.empId) != -1)
        printf("Ma nhan vien da ton tai. Nhap lai!\n");
    else
        break;
} while (1);

do {
    printf("Nhap ten nhan vien: ");
    fgets(e.name, sizeof(e.name), stdin);
    e.name[strcspn(e.name, "\n")] = '\0';
    if (strlen(e.name) == 0)
        printf("Ten nhan vien khong duoc rong. Nhap lai!\n");
    else
        break;
} while (1);

do {
    printf("Nhap chuc vu: ");
    fgets(e.position, sizeof(e.position), stdin);
    e.position[strcspn(e.position, "\n")] = '\0';
    if (strlen(e.position) == 0)
        printf("Chuc vu khong duoc rong. Nhap lai!\n");
    else
        break;
} while (1);

do {
    printf("Nhap luong co ban: ");
    if (scanf("%lf", &e.baseSalary) != 1 || e.baseSalary <= 0) {
        printf("Luong khong hop le. Nhap lai!\n");
        while (getchar() != '\n');
    } else {
        while (getchar() != '\n');
        break;
    }
} while (1);

    int choose ;
    printf("1. Mac dinh Workday = 0 \n");
    printf("2. Yeu cau nguoi dung nhap Workday \n");
    printf("Chon cach hien thi :");
    scanf("%d" , &choose);
    if(choose != 1 && choose != 2){
    	printf("Lua chon khong hop le !\n");
    	return ;
	}
    if(choose == 1){
    	e.workDay = 0 ;
    	printf("Workday = 0\n");
	}else{
		do {
			printf("Nhap ngay cong : ");
			if(e.workDay < 0){
				printf("Ngay cong khong hop le !\n");
				while(getchar() != '\n');
			}else {
				while(getchar() != '\n');
				break ;
			}
		}while(1);
	}

employees[empCount++] = e;
printf("Them nhan vien thanh cong!\n");
}

//F02 - Cap nhat ho so nhan vien
void updateEmployee() {
char id[20];
while (getchar() != '\n');//clear buffer , tranh bi skip

printf("Nhap ma NV can cap nhat: ");
fgets(id, sizeof(id), stdin);
id[strcspn(id, "\n")] = '\0';

int idx = findEmpByID(id);
if (idx == -1) {
    printf("Khong tim thay nhan vien!\n");// tao bien voi ham tien ich da tao 
    return;
}

do {
    printf("Nhap chuc vu moi: ");
    fgets(employees[idx].position, sizeof(employees[idx].position), stdin);
    employees[idx].position[strcspn(employees[idx].position, "\n")] = '\0';
    if (strlen(employees[idx].position) == 0)
        printf("Chuc vu khong duoc rong. Nhap lai!\n");
    else
        break;
} while (1);

do {
    printf("Nhap luong co ban moi: ");
    if (scanf("%lf", &employees[idx].baseSalary) != 1 || employees[idx].baseSalary <= 0) {
        printf("Luong khong hop le. Nhap lai!\n");
        while (getchar() != '\n');
    } else {
        while (getchar() != '\n');
        break;
    }
} while (1);

printf("Cap nhat nhan vien thanh cong!\n");
}

//F03 - Quan li nhan vien : Sa thai / Nghi viec 
void deleteEmployee() {
char id[20];
while (getchar() != '\n');// clear buffer , tranh bi skip

printf("Nhap ma NV muon xoa: ");
fgets(id, sizeof(id), stdin);
id[strcspn(id, "\n")] = '\0';

int idx = findEmpByID(id);  // tao bien voi ham tien ich da tao 
if (idx == -1) {
    printf("Khong tim thay nhan vien!\n");
    return;
}

int confirm;
printf("Xac nhan xoa nhan vien (1: Co, 0: Khong)? ");// bien xac nhan xem co muon xoa nhan vien khong ?
scanf("%d", &confirm);
while (getchar() != '\n');

if (confirm == 1) {
    for (int i = idx; i < empCount - 1; i++)
        employees[i] = employees[i + 1];
    empCount--;
    printf("Da xoa nhan vien co ma %s!\n" , id);// Nhap 1 - dong y xoa nhan vien
} else {
    printf("Huy xoa nhan vien!\n");// Nhap 0 - Huy xoa nhan vien
}
}

//F04 - Hien thi danh sach nhan vien 
void printList() {
if (empCount == 0) {
printf("Danh sach trong!\n"); 
return;
}
 	printf("+----+------------+----------------------+---------------+------------+----------+\n");
    printf("| STT| Ma NV      | Ten NV               | Chuc vu       | Luong      | Ngay cong|\n");
    printf("+----+------------+----------------------+---------------+------------+----------+\n");
for (int i = 0; i < empCount; i++) {
    printf("| %2d | %-10s | %-20s | %-10s    | %10.2lf | %8d |\n",
        i + 1,
        employees[i].empId,
        employees[i].name,
        employees[i].position,
        employees[i].baseSalary,
        employees[i].workDay);
	}
	printf("+----+------------+----------------------+---------------+------------+----------+\n");
}

void searchByName() {
char name[50];
while(getchar() != '\n');

printf("Nhap ten nhan vien can tim: ");
fgets(name, sizeof(name), stdin);
name[strcspn(name, "\n")] = '\0';

int found = 0; // Tao bien co
for (int i = 0; i < empCount; i++) {
    if (strstr(employees[i].name, name) != NULL) { // dung ham strstr kiem tra chuoi name co la chuoi con cua employees[i].name khong ?
        printf("\nMa NV: %s\nTen NV: %s\nChuc vu: %s\nLuong: %.2lf\nNgay cong: %d\n",
               employees[i].empId, employees[i].name, employees[i].position,
               employees[i].baseSalary, employees[i].workDay);
        found = 1; // Bien co duoc bat len
    }
}
if (!found)
    printf("Khong tim thay nhan vien!\n"); // khac bien co thi bao khong tim thay nhan vien 
}

//F06 - Sap xep nhan vien theo luong co ban tang dan / giam dan
void sortByBasesalary (){
	if(empCount == 0){
		printf("Danh sach nhan vien hien tai dang trong!\n");
		return ; 
	}
	int option ;
	while(getchar() != '\n');
	
	printf("1. Tang dan\n");
	printf("2. Giam dan\n");
	printf("Chon cach sap xep : \n");
	scanf("%d" , &option);
	
	if(option != 1 && option != 2){
		printf("Lua chon sap xep khong hop le !\n");
		return ;
	}
	for (int i = 0 ; i < empCount - 1; i++){
		for(int j = i + 1 ; j < empCount ; j++){
			int swap = 0 ;
			if(option == 1 && employees[i].baseSalary > employees[j].baseSalary){
				swap = 1 ;
			}
			if(option == 2 && employees[i].baseSalary < employees[j].baseSalary){
				swap = 1 ;
			}
			if(swap){
				Employee temp = employees[i];
				employees[i] = employees[j];
				employees[j] = temp ;
			}
		}
	}
	if(option == 1 ){
		printf("Da sap xep danh sach nhan vien tang dan theo luong !\n");
	}else {
		printf("Da sap xep danh sach nhan vien giam dan theo luong !\n");
	}
}


void addSampleList() {  // tao 1 danh sach nhan vien co san 
Employee e1 = {"HG001", "Tran Minh Duc", "Quan li", 2000, 5};
Employee e2 = {"HG002", "Phung Duy Dat", "Nhan vien", 1000, 3};
Employee e3 = {"HG003", "Nguyen Minh Hieu", "Giam doc", 5000, 8};
employees[empCount++] = e1;
employees[empCount++] = e2;
employees[empCount++] = e3;
}

int main (){
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
	// Menu
	    printf("Nhap lua chon cua ban : ");
	    scanf("%d" , &choice);
	// Yeu cau nguoi dung nhap lua chon 
	    switch (choice) {
	        case 1: addEmployee(); break;
	        case 2: updateEmployee(); break;
	        case 3: deleteEmployee(); break;
	        case 4: printList(); break;
			case 5: searchByName(); break;
			case 6: sortByBasesalary(); break ;
	    }
	    //dung switch case de chay tuong ung voi lua chon nguoi dung nhap vao
	}while (choice != 9);
	return 0 ;
}
